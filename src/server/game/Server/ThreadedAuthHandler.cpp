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

    m_queue.emplace( std::make_unique< AuthRequest >( socket, std::move( packet ) ) );
}

void ThreadedAuthHandler::QueueAuthRequest( std::unique_ptr< AuthRequest > && request )
{
    m_queue.push( std::move( request ) );
}

template<typename T>
struct AuthQueryObserver : public ACE_Future_Observer< T >
{
    AuthQueryObserver( std::unique_ptr< AuthRequest > && request, ARstates nextState )
        : m_request( std::move( request ) )
    {
        m_request->state = nextState;
    }

    std::unique_ptr< AuthRequest > m_request;

    void update( const ACE_Future<T> & future ) override
    {
        GetAuthHandler().QueueAuthRequest( std::move( m_request ) );

        delete this;
    }
};

void ThreadedAuthHandler::HandleRequest( std::unique_ptr< AuthRequest > && request )
{
    PROFILE_SCOPE( "HandleAuth" );

    WorldSocket * socket = request->socket;
    if ( socket->IsClosed() )
    {
        socket->RemoveReference();
        return;
    }

    switch(request->state)
    {
        case ARstates::STATE_BEGIN:
        {
            if (socket->HandleAuthHello( request->packet, request->accountIdCallback ))
            {
                auto observer = new AuthQueryObserver<PreparedQueryResult>( std::move( request ), ARstates::STATE_ACCOUNT );
                if (observer->m_request->accountIdCallback.attach( observer ) == -1)
                {
                    sLog->outError("ThreadedAuthHandler::HandleRequest unable to attach observer to accountIdCallback");
                    socket->RemoveReference();

                    delete observer;
                }
            }
            else
            {
                socket->RemoveReference();
            }
            break;
        }
        case ARstates::STATE_ACCOUNT:
        {
            PreparedQueryResult result;
            request->accountIdCallback.get(result);

            if (socket->HandleAuthAccount( request->packet, result, request->verifyCallback ))
            {
                auto observer = new AuthQueryObserver<SQLQueryHolder*>( std::move( request ), ARstates::STATE_VERIFY );
                if (observer->m_request->verifyCallback.attach(observer) == -1)
                {
                    sLog->outError( "ThreadedAuthHandler::HandleRequest unable to attach observer to verifyCallback" );
                    socket->RemoveReference();

                    delete observer;
                }
            }
            else
            {
                socket->RemoveReference();
            }
            break;
        }
        case ARstates::STATE_VERIFY:
        {
            SQLQueryHolder* result;
            request->verifyCallback.get(result);

            WorldSession* session = socket->HandleAuthSession( request->packet, (AuthQueryHolder*)result);
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
