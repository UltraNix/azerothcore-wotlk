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

/** \file WorldSocketMgr.cpp
*  \ingroup u2w
*  \author Derex <derex101@gmail.com>
*/

#include "WorldSocketMgr.h"

#include <ace/ACE.h>
#include <ace/Log_Msg.h>
#include <ace/Reactor.h>
#include <ace/Reactor_Impl.h>
#include <ace/TP_Reactor.h>
#include <ace/Dev_Poll_Reactor.h>
#include <ace/Guard_T.h>
#include <ace/Atomic_Op.h>
#include <ace/os_include/arpa/os_inet.h>
#include <ace/os_include/netinet/os_tcp.h>
#include <ace/os_include/sys/os_types.h>
#include <ace/os_include/sys/os_socket.h>

#include <set>

#include "Log.h"
#include "Common.h"
#include "Config.h"
#include "DatabaseEnv.h"
#include "WorldSocket.h"
#include "WorldSocketAcceptor.h"
#include "ScriptMgr.h"

/**
* This is a helper class to WorldSocketMgr, that manages
* network threads, and assigning connections from acceptor thread
* to other network threads
*/


WorldSocketMgr::WorldSocketMgr() :
    m_SockOutKBuff(-1),
    m_SockOutUBuff(65536),
    m_UseNoDelay(true)
{
}

WorldSocketMgr::~WorldSocketMgr()
{
    m_Acceptors.clear();
    m_SocketThreads.clear();
}

int WorldSocketMgr::StartReactiveIO( std::vector<ACE_UINT16> & ports, const char* address)
{
    m_UseNoDelay = sConfigMgr->GetBoolDefault ("Network.TcpNodelay", true);

    int num_threads = sConfigMgr->GetIntDefault ("Network.Threads", 1);
    if (num_threads <= 0)
    {
        sLog->outError("Network.Threads is wrong in your config file");
        return -1;
    }

    sLog->outBasic ("Max allowed socket connections %d", ACE::max_handles());

    // -1 means use default
    m_SockOutKBuff = sConfigMgr->GetIntDefault ("Network.OutKBuff", -1);
    m_SockOutUBuff = sConfigMgr->GetIntDefault ("Network.OutUBuff", 65536);

    if (m_SockOutUBuff <= 0)
    {
        sLog->outError("Network.OutUBuff is wrong in your config file");
        return -1;
    }

    for ( ACE_UINT16 port : ports )
    {
        ACE_INET_Addr listen_addr( port, address );

        auto context = std::make_unique< AcceptorContext >();
        context->m_acceptor = std::make_unique< WorldSocketAcceptor >();
        context->m_reactorThread = std::make_unique< ReactorRunnable >();

        if ( context->Start( listen_addr ) == -1 )
            return -1;

        m_Acceptors.emplace_back( std::move( context ) );
    }

    m_SocketThreads.resize( num_threads );
    for ( size_t i = 0; i < num_threads; ++i )
    {
        m_SocketThreads[ i ] = std::make_unique< ReactorRunnable >();
        m_SocketThreads[ i ]->Start();
    }

    return 0;
}

int
WorldSocketMgr::StartNetwork ( std::vector<ACE_UINT16> & ports, const char* address)
{
    if (!sLog->IsOutDebug())
        ACE_Log_Msg::instance()->priority_mask (LM_ERROR, ACE_Log_Msg::PROCESS);

    if ( StartReactiveIO( ports, address ) == -1 )
        return -1;

    sScriptMgr->OnNetworkStart();

    return 0;
}

void
WorldSocketMgr::StopNetwork()
{
    for ( auto && context : m_Acceptors )
    {
        context->Stop();
    }

    for ( auto && runnable : m_SocketThreads )
    {
        runnable->Stop();
    }

    Wait();

    sScriptMgr->OnNetworkStop();
}

void
WorldSocketMgr::Wait()
{
    for ( auto && context : m_Acceptors )
    {
        context->Wait();
    }

    for ( auto && runnable : m_SocketThreads )
    {
        runnable->Wait();
    }
}

int
WorldSocketMgr::OnSocketOpen (WorldSocket* sock)
{
    // set some options here
    if (m_SockOutKBuff >= 0)
    {
        if (sock->peer().set_option (SOL_SOCKET,
            SO_SNDBUF,
            (void*) & m_SockOutKBuff,
            sizeof (int)) == -1 && errno != ENOTSUP)
        {
            sLog->outError("WorldSocketMgr::OnSocketOpen set_option SO_SNDBUF");
            return -1;
        }
    }

    static const int ndoption = 1;

    // Set TCP_NODELAY.
    if (m_UseNoDelay)
    {
        if (sock->peer().set_option (ACE_IPPROTO_TCP,
            TCP_NODELAY,
            (void*)&ndoption,
            sizeof (int)) == -1)
        {
            sLog->outError("WorldSocketMgr::OnSocketOpen: peer().set_option TCP_NODELAY errno = %s", ACE_OS::strerror (errno));
            return -1;
        }
    }

    sock->m_OutBufferSize = static_cast<size_t> (m_SockOutUBuff);

    ASSERT( !m_SocketThreads.empty() );

    auto runnable = std::min_element( m_SocketThreads.begin(), m_SocketThreads.end(), []( auto && lhs, auto && rhs )
    {
        return lhs->Connections() < rhs->Connections();
    } );

    return (*runnable)->AddSocket( sock );
}

int WorldSocketMgr::AcceptorContext::Start( ACE_INET_Addr addr )
{
    if ( m_acceptor->open( addr, m_reactorThread->GetReactor(), ACE_NONBLOCK ) == -1 )
    {
        sLog->outError( "Failed to open acceptor, check if the port is free" );
        return -1;
    }

    m_reactorThread->Start();

    return 0;
}

void WorldSocketMgr::AcceptorContext::Stop()
{
    m_acceptor->close();
    m_reactorThread->Stop();
}

void WorldSocketMgr::AcceptorContext::Wait()
{
    m_reactorThread->Wait();
}


ReactorRunnable::ReactorRunnable() :
    m_Reactor( 0 ),
    m_Connections( 0 ),
    m_ThreadId( -1 )
{
    ACE_Reactor_Impl* imp;

#if defined (ACE_HAS_EVENT_POLL) || defined (ACE_HAS_DEV_POLL)

    imp = new ACE_Dev_Poll_Reactor();

    imp->max_notify_iterations( 128 );
    imp->restart( 1 );

#else

    imp = new ACE_TP_Reactor();
    imp->max_notify_iterations( 128 );

#endif

    m_Reactor = new ACE_Reactor( imp, 1 );
}

ReactorRunnable::~ReactorRunnable()
{
    Stop();
    Wait();

    delete m_Reactor;
}

void ReactorRunnable::Stop()
{
    m_Reactor->end_reactor_event_loop();
}

int ReactorRunnable::Start()
{
    if ( m_ThreadId != -1 )
        return -1;

    return ( m_ThreadId = activate() );
}

void ReactorRunnable::Wait()
{
    ACE_Task_Base::wait();
}

long ReactorRunnable::Connections()
{
    return static_cast< long > ( m_Connections.value() );
}

int ReactorRunnable::AddSocket( WorldSocket* sock )
{
    TRINITY_GUARD( ACE_Thread_Mutex, m_NewSockets_Lock );

    ++m_Connections;
    sock->AddReference();
    sock->reactor( m_Reactor );
    m_NewSockets.insert( sock );

    sScriptMgr->OnSocketOpen( sock );

    return 0;
}

ACE_VERSIONED_NAMESPACE_NAME::ACE_Reactor* ReactorRunnable::GetReactor()
{
    return m_Reactor;
}

void ReactorRunnable::AddNewSockets()
{
    TRINITY_GUARD( ACE_Thread_Mutex, m_NewSockets_Lock );

    if ( m_NewSockets.empty() )
        return;

    for ( SocketSet::const_iterator i = m_NewSockets.begin(); i != m_NewSockets.end(); ++i )
    {
        WorldSocket* sock = ( *i );

        if ( sock->IsClosed() )
        {
            sScriptMgr->OnSocketClose( sock, true );

            sock->RemoveReference();
            --m_Connections;
        }
        else
            m_Sockets.insert( sock );
    }

    m_NewSockets.clear();
}

int ReactorRunnable::svc()
{
    ;//sLog->outStaticDebug ("Network Thread Starting");

    ACE_ASSERT( m_Reactor );

    SocketSet::iterator i, t;

    while ( !m_Reactor->reactor_event_loop_done() )
    {
        // dont be too smart to move this outside the loop
        // the run_reactor_event_loop will modify interval
        ACE_Time_Value interval( 0, 10000 );

        if ( m_Reactor->run_reactor_event_loop( interval ) == -1 )
            break;

        AddNewSockets();

        for ( i = m_Sockets.begin(); i != m_Sockets.end();)
        {
            if ( ( *i )->Update() == -1 )
            {
                t = i;
                ++i;

                ( *t )->CloseSocket();

                sScriptMgr->OnSocketClose( ( *t ), false );

                ( *t )->RemoveReference();
                --m_Connections;
                m_Sockets.erase( t );
            }
            else
                ++i;
        }
    }

    ;//sLog->outStaticDebug ("Network Thread exits");

    return 0;
}
