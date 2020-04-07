#include "ThreadedAuthHandler.hpp"

#include "WorldSocket.h"
#include "WorldPacket.h"
#include "World.h"
#include "Log.h"
#include "Profiler.h"

void ThreadedAuthHandler::Initialize( size_t threadsCount )
{
    m_pool.reserve( threadsCount );

    for ( size_t idx = 0u; idx < threadsCount; ++idx )
    {
        m_pool.emplace_back( [this]
        {
            while ( !m_queue.is_closed() )
            {
                auto request = m_queue.pop();
                if ( !request )
                    continue;

                try
                {
                    HandleRequest( std::move( *request ) );
                }
                catch (ByteBufferException &)
                {
                    sLog->outError("ThreadedAuthHandler::HandleRequest ByteBufferException occured while parsing auth request.");
                }
            }
        } );
    }

    sLog->outString( ">> Auth handler initialized." );
}

void ThreadedAuthHandler::Shutdown()
{
    m_queue.close();

    for ( auto & thread : m_pool )
    {
        if ( thread.joinable() )
            thread.join();
    }
}

void ThreadedAuthHandler::CollectSessions( World* world )
{
    PROFILE_SCOPE( "CollectSessions" );

    std::unique_lock< std::mutex > lock( m_mutex );
    for ( WorldSession * session : m_sessions )
    {
        world->AddSession( session );
    }

    m_sessions.clear();
}

void ThreadedAuthHandler::QueueAuthRequest( WorldSocket * socket, WorldPacket packet )
{
    //! Make sure no one destroys our socket
    socket->AddReference();

    m_queue.emplace( socket, std::move( packet ) );
}

void ThreadedAuthHandler::HandleRequest( AuthRequest request )
{
    PROFILE_SCOPE( "HandleAuth" );

    WorldSocket * socket = request.socket;
    if ( socket->IsClosed() )
    {
        socket->RemoveReference();
        return;
    }
    switch(request.state)
    {
        case ARstates::STATE_BEGIN:
            if (!socket->HandleAuthHello(request.packet, request.accountIdCallback))
            {
                socket->RemoveReference();
            }
            else
            {
                request.state = ARstates::STATE_ACCOUNT;
                m_queue.push( std::move(request) );
            }
            break;
        case ARstates::STATE_ACCOUNT:
        {
            if (!request.accountIdCallback.ready())
            {
                m_queue.push( std::move(request) );
                return; // back into queue
            }
            PreparedQueryResult result;
            request.accountIdCallback.get(result);
            if (!socket->HandleAuthAccount(request.packet, result, request.verifyCallback))
            {
                socket->RemoveReference();
            }
            else
            {
                request.state = ARstates::STATE_VERIFY;
                m_queue.push( std::move(request) );
            }
            break;
        }
        case ARstates::STATE_VERIFY:
        {
            if (!request.verifyCallback.ready())
            {
                m_queue.push( std::move(request) );
                return; // back into queue
            }
            SQLQueryHolder* result;
            request.verifyCallback.get(result);
            WorldSession* session = socket->HandleAuthSession( request.packet, (AuthQueryHolder*)result);
            delete result;
            if ( session != nullptr )
            {
                std::unique_lock< std::mutex > lock( m_mutex );
                m_sessions.push_back( session );
            }
            socket->RemoveReference();
            break;
        }
    }
}

ThreadedAuthHandler & GetAuthHandler()
{
    static ThreadedAuthHandler s_handler;
    return s_handler;
}
