#include "ThreadedAuthHandler.hpp"
#include "WorldSocket.h"
#include "WorldPacket.h"

ThreadedAuthHandler::ThreadedAuthHandler()
    : m_shutdown( false )
{

}

void ThreadedAuthHandler::Initialize( size_t threadsCount )
{
    m_pool.reserve( threadsCount );

    for ( size_t idx = 0u; idx < threadsCount; ++idx )
    {
        m_pool.push_back( std::thread( [this]
        {
            while ( !m_shutdown )
            {
                auto request = m_queue.pop();
                HandleRequest( std::move( request ) );
            }
        } ) );
    }

    sLog->outString( ">> Auth handler initialized." );
}

void ThreadedAuthHandler::Shutdown()
{
    m_shutdown = true;
    for ( auto & thread : m_pool )
    {
        thread.join();
    }
}

void ThreadedAuthHandler::CollectSessions( World* world )
{
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
    WorldSocket * socket = request.socket;
    if ( !socket->IsClosed() )
    {
        WorldSession* session = socket->HandleAuthSession( request.packet );
        if ( session != nullptr )
        {
            std::unique_lock< std::mutex > lock( m_mutex );
            m_sessions.push_back( session );
        }
    }

    socket->RemoveReference();
}

ThreadedAuthHandler & GetAuthHandler()
{
    static ThreadedAuthHandler s_handler;
    return s_handler;
}
