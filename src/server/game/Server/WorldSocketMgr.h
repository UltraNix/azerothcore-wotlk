
/** \addtogroup u2w User to World Communication
 *  @{
 *  \file WorldSocketMgr.h
 *  \author Derex <derex101@gmail.com>
 */

#ifndef __WORLDSOCKETMGR_H
#define __WORLDSOCKETMGR_H

#include <ace/Basic_Types.h>
#include <ace/Singleton.h>
#include <ace/Thread_Mutex.h>
#include <vector>
#include <memory>
#include "ace/Atomic_Op_T.h"
#include "WorldSocketAcceptor.h"

class WorldSocket;
class ReactorRunnable;
class ACE_Event_Handler;

class ReactorRunnable : protected ACE_Task_Base
{
public:

    ReactorRunnable();
    virtual ~ReactorRunnable();

    void    Stop();
    int     Start();

    void    Wait();

    long    Connections();

    int     AddSocket( WorldSocket* sock );

    ACE_Reactor* GetReactor();

protected:
    virtual int svc();

private:
    typedef ACE_Atomic_Op<ACE_SYNCH_MUTEX, long> AtomicInt;
    typedef std::deque<WorldSocket*> SocketQueue;

    ACE_Reactor*        m_Reactor;
    AtomicInt           m_Connections;
    int                 m_ThreadId;

    SocketQueue         m_Sockets;
    SocketQueue         m_NewSockets;
    ACE_Thread_Mutex    m_NewSocketsMutex;
};

/// Manages all sockets connected to peers and network threads
class WorldSocketMgr
{
public:
    friend class WorldSocket;
    friend class ACE_Singleton<WorldSocketMgr, ACE_Thread_Mutex>;

    int     StartNetwork( std::vector<ACE_UINT16> & ports, const char* address);
    void    StopNetwork();
    void    Wait();

private:
    int     OnSocketOpen(WorldSocket* sock);
    int     StartReactiveIO( std::vector<ACE_UINT16> & ports, const char* address);

private:
    WorldSocketMgr();
    virtual ~WorldSocketMgr();

    int     m_SockOutKBuff;
    int     m_SockOutUBuff;
    bool    m_UseNoDelay;

    struct AcceptorContext
    {
        int     Start( ACE_INET_Addr addr );
        void    Stop();
        void    Wait();

        std::unique_ptr<WorldSocketAcceptor> m_acceptor      = nullptr;
        std::unique_ptr<ReactorRunnable>     m_reactorThread = nullptr;
    };

    std::vector< std::unique_ptr<ReactorRunnable> > m_SocketThreads;
    std::vector< std::unique_ptr<AcceptorContext> > m_Acceptors;
};

#define sWorldSocketMgr ACE_Singleton<WorldSocketMgr, ACE_Thread_Mutex>::instance()

#endif
/// @}
