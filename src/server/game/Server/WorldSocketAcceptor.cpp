#include "WorldSocketAcceptor.h"

#include "Log.h"

int WorldSocketAcceptor::handle_timeout(const ACE_Time_Value& /*current_time*/, const void* /*act = 0*/)
{
    sLog->outBasic("Resuming acceptor");
    reactor()->cancel_timer(this, 1);
    return reactor()->register_handler(this, ACE_Event_Handler::ACCEPT_MASK);
}

int WorldSocketAcceptor::handle_accept_error(void)
{
#if defined(ENFILE) && defined(EMFILE)
    if (errno == ENFILE || errno == EMFILE)
    {
        sLog->outError("Out of file descriptors, suspending incoming connections for 10 seconds");
        reactor()->remove_handler(this, ACE_Event_Handler::ACCEPT_MASK | ACE_Event_Handler::DONT_CALL);
        reactor()->schedule_timer(this, NULL, ACE_Time_Value(10));
    }
#endif
    return 0;
}
