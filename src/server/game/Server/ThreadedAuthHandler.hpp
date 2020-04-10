#pragma once

#include "Threading/SyncQueue.hpp"
#include "WorldPacket.h"

#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <memory>

class WorldSocket;
class WorldSession;
class World;

enum ARstates
{
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

    ARstates                   state;
    PreparedQueryResultFuture  accountIdCallback;
    QueryResultHolderFuture    verifyCallback; 
    WorldPacket                packet;
    WorldSocket *              socket;
};

using AuthRequestQueue = Threading::SyncQueue< std::unique_ptr< AuthRequest > >;

class ThreadedAuthHandler
{
public:
    friend class World;

    ThreadedAuthHandler() = default;

    void                Initialize( size_t /*threadsCount*/ );
    void                Shutdown();

    void                QueueAuthRequest( WorldSocket * socket, WorldPacket packet );
    void                QueueAuthRequest( std::unique_ptr< AuthRequest > && request );

protected:
    //! Call only from world thread
    void                CollectSessions( World * world );
    void                HandleRequest( std::unique_ptr< AuthRequest > && request );

    AuthRequestQueue                m_queue;

    std::mutex                      m_mutex;
    std::vector< WorldSession * >   m_sessions;

    using ThreadPool = std::vector< std::thread >;
    ThreadPool                      m_pool;
};

ThreadedAuthHandler &   GetAuthHandler();
