/*
 * Copyright (C) 
 * Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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

class WorldSocket;
class ReactorRunnable;
class ACE_Event_Handler;
class WorldSocketAcceptor;

/// Manages all sockets connected to peers and network threads
class WorldSocketMgr
{
public:
    friend class WorldSocket;
    friend class ACE_Singleton<WorldSocketMgr, ACE_Thread_Mutex>;

    /// Start network, listen at address:port .
    int StartNetwork( std::vector<ACE_UINT16> & ports, const char* address);

    /// Stops all network threads, It will wait for all running threads .
    void StopNetwork();

    /// Wait untill all network threads have "joined" .
    void Wait();

private:
    int OnSocketOpen(WorldSocket* sock);

    int StartReactiveIO( std::vector<ACE_UINT16> & ports, const char* address);

private:
    WorldSocketMgr();
    virtual ~WorldSocketMgr();

    int m_SockOutKBuff;
    int m_SockOutUBuff;
    bool m_UseNoDelay;

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
