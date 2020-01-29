#pragma once

#include "Threading/SyncQueue.hpp"
#include "WorldPacket.h"

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>

class WorldSocket;
class WorldSession;
class World;

struct AuthRequest
{
    AuthRequest( WorldSocket * s, WorldPacket && p )
        : socket( s )
        , packet( std::move( p ) )
    {
    }

    AuthRequest( const AuthRequest & ) = delete;
    AuthRequest & operator=( const AuthRequest & ) = delete;

    AuthRequest( AuthRequest && rhs )
    {
        *this = std::move( rhs );
    }

    AuthRequest & operator=( AuthRequest && rhs )
    {
        socket = rhs.socket;
        packet = std::move( rhs.packet );
        return *this;
    }

    WorldPacket     packet;
    WorldSocket *   socket;
};

using AuthRequestQueue = Threading::SyncQueue< AuthRequest >;

class ThreadedAuthHandler
{
public:
    friend class World;

    ThreadedAuthHandler();

    void                Initialize( size_t /*threadsCount*/ );
    void                Shutdown();

    void                QueueAuthRequest( WorldSocket * socket, WorldPacket packet );

protected:
    //! Call only from world thread
    void                CollectSessions( World * world );
    void                HandleRequest( AuthRequest request );

    std::atomic_bool    m_shutdown;
    AuthRequestQueue    m_queue;

    std::mutex                      m_mutex;
    std::vector< WorldSession * >   m_sessions;

    using ThreadPool = std::vector< std::thread >;
    ThreadPool          m_pool;
};

ThreadedAuthHandler &   GetAuthHandler();
