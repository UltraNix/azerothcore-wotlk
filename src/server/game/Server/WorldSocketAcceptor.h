

/** \addtogroup u2w User to World Communication
 *  @{
 *  \file WorldSocketMgr.h
 */

#ifndef __WORLDSOCKETACCEPTOR_H_
#define __WORLDSOCKETACCEPTOR_H_

#include "Common.h"

#include <ace/Acceptor.h>
#include <ace/SOCK_Acceptor.h>

#include "WorldSocket.h"

class WorldSocketAcceptor : public ACE_Acceptor<WorldSocket, ACE_SOCK_Acceptor>
{
public:
    WorldSocketAcceptor(void) { }
    virtual ~WorldSocketAcceptor(void)
    {
        if (reactor())
            reactor()->cancel_timer(this, 1);
    }

protected:

    virtual int handle_timeout(const ACE_Time_Value& /*current_time*/, const void* /*act = 0*/);

    virtual int handle_accept_error(void);
};

#endif /* __WORLDSOCKETACCEPTOR_H_ */
/// @}
