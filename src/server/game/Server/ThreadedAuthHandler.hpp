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

enum ARstates {
    STATE_BEGIN = 0,
    STATE_ACCOUNT = 1,
    STATE_VERIFY = 2
};

struct AuthRequest
{
    AuthRequest( WorldSocket * s, WorldPacket && p )
        : socket( s )
        , state( ARstates::STATE_BEGIN )
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
        state  = rhs.state;
        accountIdCallback = std::move( rhs.accountIdCallback );
        verifyCallback = std::move( rhs.verifyCallback );
        return *this;
    }

    ARstates state;
    PreparedQueryResultFuture accountIdCallback;
    QueryResultHolderFuture   verifyCallback; 
    WorldPacket     packet;
    WorldSocket *   socket;
};

using AuthRequestQueue = Threading::SyncQueue< AuthRequest >;

class ThreadedAuthHandler
{
public:
    friend class World;

    ThreadedAuthHandler() = default;

    void                Initialize( size_t /*threadsCount*/ );
    void                Shutdown();

    void                QueueAuthRequest( WorldSocket * socket, WorldPacket packet );

protected:
    //! Call only from world thread
    void                CollectSessions( World * world );
    void                HandleRequest( AuthRequest request );

    AuthRequestQueue    m_queue;

    std::mutex                      m_mutex;
    std::vector< WorldSession * >   m_sessions;

    using ThreadPool = std::vector< std::thread >;
    ThreadPool                      m_pool;
};

ThreadedAuthHandler &   GetAuthHandler();
