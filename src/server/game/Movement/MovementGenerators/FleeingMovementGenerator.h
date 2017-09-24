#ifndef TRINITY_FLEEINGMOVEMENTGENERATOR_H
#define TRINITY_FLEEINGMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "Timer.h"
#include "PathGenerator.h"

template<class T>
class FleeingMovementGenerator : public MovementGeneratorMedium< T, FleeingMovementGenerator<T> >
{
    public:
        explicit FleeingMovementGenerator(uint64 fleeTargetGUID) : _path(nullptr), _fleeTargetGUID(fleeTargetGUID), _timer(0), _interrupt(false) { }
        ~FleeingMovementGenerator();

        MovementGeneratorType GetMovementGeneratorType() { return FLEEING_MOTION_TYPE; }

        void DoInitialize(T*);
        void DoFinalize(T*);
        void DoReset(T*);
        bool DoUpdate(T*, uint32);

    private:
        void SetTargetLocation(T*);
        void GetPoint(T*, Position &position);

        PathGenerator* _path;
        uint64 _fleeTargetGUID;
        TimeTracker _timer;
        bool _interrupt;
};

class TimedFleeingMovementGenerator : public FleeingMovementGenerator<Creature>
{
    public:
        explicit TimedFleeingMovementGenerator(uint64 fleeTargetGUID, uint32 time) : FleeingMovementGenerator<Creature>(fleeTargetGUID), _totalFleeTime(time) { }

        MovementGeneratorType GetMovementGeneratorType() { return TIMED_FLEEING_MOTION_TYPE; }
        bool Update(Unit*, uint32) override;
        void Finalize(Unit*) override;

    private:
        TimeTracker _totalFleeTime;
};

#endif