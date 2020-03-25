#ifndef _MAP_UPDATER_H_INCLUDED
#define _MAP_UPDATER_H_INCLUDED

#include <ace/Thread_Mutex.h>
#include <ace/Condition_Thread_Mutex.h>

#include "DelayExecutor.h"
#include "World.h"

#include <functional>

class Map;

class MapUpdater
{
    public:

        MapUpdater();
        virtual ~MapUpdater();

        int schedule_update(Map& map, ACE_UINT32 diff, ACE_UINT32 s_diff);
        int schedule_lfg_update(ACE_UINT32 diff);
        int schedule_task( std::function< void() > task );

        int wait();

        int activate(size_t num_threads);

        int deactivate();

        bool activated();

    private:

        DelayExecutor m_executor;
        ACE_Thread_Mutex m_mutex;
        ACE_Condition_Thread_Mutex m_condition;
        size_t pending_requests;

        friend class MapUpdateRequest;
        friend class LFGUpdateRequest;
        friend class TaskRequest;

        void update_finished();
};

#endif //_MAP_UPDATER_H_INCLUDED
