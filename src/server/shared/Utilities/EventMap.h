#include "Common.h"
#include "Duration.h"
#include "Util.h"

#ifndef _EVENT_MAP_H_
#define _EVENT_MAP_H_

class EventMap
{
        /**
        * Internal storage type.
        * Key: Time as uint32 when the event should occur.
        * Value: The event data as uint32.
        *
        * Structure of event data:
        * - Bit  0 - 15: Event Id.
        * - Bit 16 - 23: Group
        * - Bit 24 - 31: Phase
        * - Pattern: 0xPPGGEEEE
        */
        typedef std::multimap<uint32, uint32> EventStore;

    public:
        EventMap() : _time(0), _phase(0), _lastEvent(0) { }

        /**
        * @name Reset
        * @brief Removes all scheduled events and resets time and phase.
        */
        void Reset()
        {
            _eventMap.clear();
            _time = 0;
            _phase = 0;
        }

        /**
        * @name Update
        * @brief Updates the timer of the event map.
        * @param time Value in ms to be added to time.
        */
        void Update(uint32 time)
        {
            _time += time;
        }

        /**
        * @name GetTimer
        * @return Current timer in ms value.
        */
        uint32 GetTimer() const
        {
            return _time;
        }

        /**
        * @name GetPhaseMask
        * @return Active phases as mask.
        */
        uint8 GetPhaseMask() const
        {
            return _phase;
        }

        /**
        * @name Empty
        * @return True, if there are no events scheduled.
        */
        bool Empty() const
        {
            return _eventMap.empty();
        }

        /**
        * @name SetPhase
        * @brief Sets the phase of the map (absolute).
        * @param phase Phase which should be set. Values: 1 - 8. 0 resets phase.
        */
        void SetPhase(uint8 phase)
        {
            if (!phase)
                _phase = 0;
            else if (phase <= 8)
                _phase = uint8(1 << (phase - 1));
        }

        /**
        * @name AddPhase
        * @brief Activates the given phase (bitwise).
        * @param phase Phase which should be activated. Values: 1 - 8
        */
        void AddPhase(uint8 phase)
        {
            if (phase && phase <= 8)
                _phase |= uint8(1 << (phase - 1));
        }

        /**
        * @name RemovePhase
        * @brief Deactivates the given phase (bitwise).
        * @param phase Phase which should be deactivated. Values: 1 - 8.
        */
        void RemovePhase(uint8 phase)
        {
            if (phase && phase <= 8)
                _phase &= uint8(~(1 << (phase - 1)));
        }

        /**
        * @name ScheduleEvent
        * @brief Creates new event entry in map.
        * @param eventId The id of the new event.
        * @param time The time until the event occurs as std::chrono floating point type.
        * @param group The group which the event is associated to. Has to be between 1 and 8. 0 means it has no group.
        * @param phase The phase in which the event can occur. Has to be between 1 and 8. 0 means it can occur in all phases.
        */
        template<class Rep, class Period>
        void ScheduleEvent(uint32 eventId, const std::chrono::duration<Rep, Period>& time, uint32 group = 0, uint8 phase = 0)
        {
            ScheduleEvent(eventId, std::chrono::duration_cast<Milliseconds>(time).count(), group, phase);
        }

        /**
        * @name ScheduleEvent
        * @brief Creates new event entry in map.
        * @param eventId The id of the new event.
        * @param minTime The minimum time until the event occurs as std::chrono floating point type.
        * @param maxTime The maximum time until the event occurs as std::chrono floating point type.
        * @param group The group which the event is associated to. Has to be between 1 and 8. 0 means it has no group.
        * @param phase The phase in which the event can occur. Has to be between 1 and 8. 0 means it can occur in all phases.
        */
        template<class Rep, class Period>
        void ScheduleEvent(uint32 eventId, const std::chrono::duration<Rep, Period>& minTime, const std::chrono::duration<Rep, Period>& maxTime, uint32 group = 0, uint8 phase = 0)
        {
            ScheduleEvent(eventId, urand(std::chrono::duration_cast<Milliseconds>(minTime).count(), std::chrono::duration_cast<Milliseconds>(maxTime).count()), group, phase);
        }

        /**
        * @name ScheduleEvent
        * @brief Creates new event entry in map.
        * @param eventId The id of the new event.
        * @param time The time in milliseconds until the event occurs.
        * @param group The group which the event is associated to. Has to be between 1 and 8. 0 means it has no group.
        * @param phase The phase in which the event can occur. Has to be between 1 and 8. 0 means it can occur in all phases.
        */
        void ScheduleEvent(uint32 eventId, uint32 time, uint32 group = 0, uint8 phase = 0)
        {
            if (group && group <= 8)
                eventId |= (1 << (group + 15));

            if (phase && phase <= 8)
                eventId |= (1 << (phase + 23));

            _eventMap.insert(EventStore::value_type(_time + time, eventId));
        }

        /**
        * @name RescheduleEvent
        * @brief Cancels the given event and reschedules it.
        * @param eventId The id of the event.
        * @param time The time until the event occurs as std::chrono floating point type.
        * @param group The group which the event is associated to. Has to be between 1 and 8. 0 means it has no group.
        * @param phase The phase in which the event can occur. Has to be between 1 and 8. 0 means it can occur in all phases.
        */
        template<class Rep, class Period>
        void RescheduleEvent(uint32 eventId, const std::chrono::duration<Rep, Period>& time, uint32 group = 0, uint8 phase = 0)
        {
            RescheduleEvent(eventId, std::chrono::duration_cast<Milliseconds>(time).count(), group, phase);
        }

        /**
        * @name RescheduleEvent
        * @brief Cancels the given event and reschedules it.
        * @param eventId The id of the event.
        * @param minTime The minimum time until the event occurs as std::chrono floating point type.
        * @param maxTime The maximum time until the event occurs as std::chrono floating point type.
        * @param group The group which the event is associated to. Has to be between 1 and 8. 0 means it has no group.
        * @param phase The phase in which the event can occur. Has to be between 1 and 8. 0 means it can occur in all phases.
        */
        template<class Rep, class Period>
        void RescheduleEvent(uint32 eventId, const std::chrono::duration<Rep, Period>& minTime, const std::chrono::duration<Rep, Period>& maxTime, uint32 group = 0, uint8 phase = 0)
        {
            RescheduleEvent(eventId, urand(std::chrono::duration_cast<Milliseconds>(minTime).count(), std::chrono::duration_cast<Milliseconds>(maxTime).count()), group, phase);
        }

        /**
        * @name RescheduleEvent
        * @brief Cancels the given event and reschedules it.
        * @param eventId The id of the event.
        * @param time The time in milliseconds until the event occurs.
        * @param group The group which the event is associated to. Has to be between 1 and 8. 0 means it has no group.
        * @param phase The phase in which the event can occur. Has to be between 1 and 8. 0 means it can occur in all phases.
        */
        void RescheduleEvent(uint32 eventId, uint32 time, uint32 group = 0, uint8 phase = 0)
        {
            CancelEvent(eventId);
            ScheduleEvent(eventId, time, group, phase);
        }

        /**
        * @name RepeatEvent
        * @brief Repeats the mostly recently executed event.
        * @param time Time as floating point std::chrono until the event occurs.
        */
        template<class Rep, class Period>
        void Repeat(const std::chrono::duration<Rep, Period>& time)
        {
            Repeat(std::chrono::duration_cast<Milliseconds>(time).count());
        }

        /**
        * @name RepeatEvent
        * @brief Repeats the mostly recently executed event.
        * @param minTime Minimum time as floating point std::chrono until the event occurs.
        * @param maxTime Maximum time as floating point std::chrono until the event occurs.
        */
        template<class Rep, class Period>
        void Repeat(const std::chrono::duration<Rep, Period>& minTime, const std::chrono::duration<Rep, Period>& maxTime)
        {
            Repeat(std::chrono::duration_cast<Milliseconds>(minTime).count(), std::chrono::duration_cast<Milliseconds>(maxTime).count());
        }

        /**
        * @name RepeatEvent
        * @brief Repeats the mostly recently executed event.
        * @param time Time until the event occurs.
        */
        void Repeat(uint32 time)
        {
            _eventMap.insert(EventStore::value_type(_time + time, _lastEvent));
        }

        /**
        * @name RepeatEvent
        * @brief Repeats the mostly recently executed event, Equivalent to Repeat(urand(minTime, maxTime).
        * @param minTime Minimum time until the event occurs.
        * @param maxTime Maximum time until the event occurs.
        */
        void Repeat(uint32 minTime, uint32 maxTime)
        {
            Repeat(urand(minTime, maxTime));
        }

        /**
        * @name ExecuteEvent
        * @brief Returns the next event to execute and removes it from map.
        * @return Id of the event to execute.
        */
        uint32 ExecuteEvent()
        {
            while (!Empty())
            {
                EventStore::iterator itr = _eventMap.begin();

                if (itr->first > _time)
                    return 0;
                else if (_phase && (itr->second & 0xFF000000) && !((itr->second >> 24) & _phase))
                    _eventMap.erase(itr);
                else
                {
                    uint32 eventId = (itr->second & 0x0000FFFF);
                    _lastEvent = itr->second; // include phase/group
                    _eventMap.erase(itr);
                    return eventId;
                }
            }

            return 0;
        }

        /**
        * @name DelayEvents
        * @brief Delay all events of the same group.
        * @param delay Amount of delay in ms as floating point std::chrono::duration.
        * @param group Group of the events.
        */
        template<class Rep, class Period>
        void DelayEvents(const std::chrono::duration<Rep, Period>& delay, uint32 group)
        {
            DelayEvents(std::chrono::duration_cast<Milliseconds>(delay).count(), group);
        }

        /**
        * @name DelayEvents
        * @brief Delays all events in the map. If delay is greater than or equal internal timer, delay will be 0.
        * @param delay Amount of delay in ms as floating point std::chrono::duration.
        */
        template<class Rep, class Period>
        void DelayEvents(const std::chrono::duration<Rep, Period>& delay)
        {
            DelayEvents(std::chrono::duration_cast<Milliseconds>(delay).count());
        }

        /**
        * @name DelayEvents
        * @brief Delays all events in the map. If delay is greater than or equal internal timer, delay will be equal to internal timer.
        * @param delay Amount of delay.
        */
        void DelayEvents(uint32 delay)
        {
            _time = delay < _time ? _time - delay : 0;
        }

        /**
        * @name DelayEvents
        * @brief Delay all events of the same group.
        * @param delay Amount of delay.
        * @param group Group of the events.
        */
        void DelayEvents(uint32 delay, uint32 group)
        {
            if (!group || group > 8 || Empty())
                return;

            EventStore delayed;

            for (EventStore::iterator itr = _eventMap.begin(); itr != _eventMap.end();)
            {
                if (itr->second & (1 << (group + 15)))
                {
                    delayed.insert(EventStore::value_type(itr->first + delay, itr->second));
                    _eventMap.erase(itr++);
                }
                else
                    ++itr;
            }

            _eventMap.insert(delayed.begin(), delayed.end());
        }

        /**
        * @name CancelEvent
        * @brief Cancels all events of the specified id.
        * @param eventId Event id to cancel.
        */
        void CancelEvent(uint32 eventId)
        {
            if (Empty())
                return;

            for (EventStore::iterator itr = _eventMap.begin(); itr != _eventMap.end();)
            {
                if (eventId == (itr->second & 0x0000FFFF))
                    _eventMap.erase(itr++);
                else
                    ++itr;
            }
        }

        /**
        * @name CancelEventGroup
        * @brief Cancel events belonging to specified group.
        * @param group Group to cancel.
        */
        void CancelEventGroup(uint32 group)
        {
            if (!group || group > 8 || Empty())
                return;

            for (EventStore::iterator itr = _eventMap.begin(); itr != _eventMap.end();)
            {
                if (itr->second & (1 << (group + 15)))
                    _eventMap.erase(itr++);
                else
                    ++itr;
            }
        }

        /**
        * @name GetNextEventTime
        * @brief Returns closest occurence of specified event.
        * @param eventId Wanted event id.
        * @return Time of found event.
        */
        uint32 GetNextEventTime(uint32 eventId) const
        {
            if (Empty())
                return 0;

            for (EventStore::const_iterator itr = _eventMap.begin(); itr != _eventMap.end(); ++itr)
                if (eventId == (itr->second & 0x0000FFFF))
                    return itr->first;

            return 0;
        }

        /**
        * @name GetNextEventTime
        * @return Time of next event.
        */
        uint32 GetNextEventTime() const
        {
            return Empty() ? 0 : _eventMap.begin()->first;
        }

        /**
        * @name IsInPhase
        * @brief Returns whether event map is in specified phase or not.
        * @param phase Wanted phase.
        * @return True, if phase of event map contains specified phase.
        */
        bool IsInPhase(uint8 phase) const
        {
            return phase <= 8 && (!phase || _phase & (1 << (phase - 1)));
        }

        /**
        * @name GetTimeUntilEvent
        * @brief Returns time in milliseconds until next event.
        * @param eventId of the event.
        * @return Time of next event.
        */
        uint32 GetTimeUntilEvent(uint32 eventId) const
        {
            for (EventStore::const_iterator itr = _eventMap.begin(); itr != _eventMap.end(); ++itr)
                if (eventId == (itr->second & 0x0000FFFF))
                    return itr->first - _time;

            return std::numeric_limits<uint32>::max();
        }

        void RepeatEvent(uint32 time)
        {
            if (Empty())
                return;

            uint32 eventId = _eventMap.begin()->second;
            _eventMap.erase(_eventMap.begin());
            ScheduleEvent(eventId, time);
        }

        /**
        * @name PopEvent
        * @brief Remove the first event in the map.
        */
        void PopEvent()
        {
            if (!Empty())
                _eventMap.erase(_eventMap.begin());
        }

        /**
        * @name GetEvent
        * @brief Returns the next event to execute.
        * @return Id of the event to execute.
        */
        uint32 GetEvent()
        {
            while (!Empty())
            {
                EventStore::iterator itr = _eventMap.begin();

                if (itr->first > _time)
                    return 0;
                else if (_phase && (itr->second & 0xFF000000) && !(itr->second & (_phase << 24)))
                    _eventMap.erase(itr);
                else
                    return (itr->second & 0x0000FFFF);
            }

            return 0;
        }

        void SetTimer(uint32 time)
        {
            _time = time;
        }

        void DelayEventsToMax(uint32 delay, uint32 group)
        {
            for (EventStore::iterator itr = _eventMap.begin(); itr != _eventMap.end();)
            {
                if (itr->first < _time + delay && (group == 0 || ((1 << (group + 15)) & itr->second)))
                {
                    ScheduleEvent(itr->second, delay);
                    _eventMap.erase(itr);
                    itr = _eventMap.begin();
                }
                else
                    ++itr;
            }
        }

    private:
        /**
        * @name _time
        * @brief Internal timer.
        *
        * This does not represent the real date/time value.
        * It's more like a stopwatch: It can run, it can be stopped,
        * it can be resetted and so on. Events occur when this timer
        * has reached their time value. Its value is changed in the
        * Update method.
        */
        uint32 _time;

        /**
        * @name _phase
        * @brief Phase mask of the event map.
        *
        * Contains the phases the event map is in. Multiple
        * phases from 1 to 8 can be set with SetPhase or
        * AddPhase. RemovePhase deactives a phase.
        */
        uint8 _phase;

        /**
        * @name _eventMap
        * @brief Internal event storage map. Contains the scheduled events.
        *
        * See typedef at the beginning of the class for more
        * details.
        */
        EventStore _eventMap;

        /**
        * @name _lastEvent
        * @brief Stores information on the most recently executed event
        */
        uint32 _lastEvent;
};

#endif