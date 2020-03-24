
#ifndef TRINITY_TARGETEDMOVEMENTGENERATOR_H
#define TRINITY_TARGETEDMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "FollowerReference.h"
#include "Timer.h"
#include "Unit.h"
#include "ThreadedPathGenerator.hpp"

class TargetedMovementGeneratorBase
{
    public:
        TargetedMovementGeneratorBase(Unit* target) { i_target.link(target, this); }
        void stopFollowing() { }
    protected:
        FollowerReference i_target;
};

template<class T, typename D>
class TargetedMovementGeneratorMedium : public MovementGeneratorMedium< T, D >, public TargetedMovementGeneratorBase
{
    protected:
        TargetedMovementGeneratorMedium(Unit* target, float offset, float angle) :
            TargetedMovementGeneratorBase(target), lastPathingFailMSTime(0),
            i_recheckDistance(0), i_recheckDistanceForced(2500), i_recheckBackout(0), i_offset(offset), i_angle(angle),
            i_recalculateTravel(false), i_targetReached(false)
        {
        }

    public:
        bool DoUpdate(T*, uint32);
        Unit* GetTarget() const { return i_target.getTarget(); }

        void unitSpeedChanged() { i_recalculateTravel = true; }

    protected:
        void _setTargetLocation(T* owner, bool initial, bool InBounds = false);
        bool _handleAsyncPathRequest( T* owner );

        std::pair<Movement::AsyncPathResult, bool > m_pathRequest;

        Position lastOwnerXYZ;
        Position lastTargetXYZ;

        TimeTrackerSmall i_recheckDistance;
        TimeTrackerSmall i_recheckDistanceForced;
        TimeTrackerSmall i_recheckBackout;
        float i_offset;
        float i_angle;
        bool i_recalculateTravel : 1;
        bool i_targetReached : 1;
        uint32 lastPathingFailMSTime;
};

template<class T>
class ChaseMovementGenerator : public TargetedMovementGeneratorMedium<T, ChaseMovementGenerator<T> >
{
    public:
        ChaseMovementGenerator(Unit* target)
            : TargetedMovementGeneratorMedium<T, ChaseMovementGenerator<T> >(target) {}
        ChaseMovementGenerator(Unit* target, float offset, float angle)
            : TargetedMovementGeneratorMedium<T, ChaseMovementGenerator<T> >(target, offset, angle) {}
        ~ChaseMovementGenerator() {}

        MovementGeneratorType GetMovementGeneratorType() { return CHASE_MOTION_TYPE; }

        void DoInitialize(T*);
        void DoFinalize(T*);
        void DoReset(T*);
        void MovementInform(T*);

        static void _clearUnitStateMove(T* u) { u->ClearUnitState(UNIT_STATE_CHASE_MOVE); }
        static void _addUnitStateMove(T* u)  { u->AddUnitState(UNIT_STATE_CHASE_MOVE); }
        bool EnableWalking() const { return false;}
        bool _lostTarget(T* u) const { return u->GetVictim() != this->GetTarget(); }
        void _reachTarget(T*);
};

#endif
