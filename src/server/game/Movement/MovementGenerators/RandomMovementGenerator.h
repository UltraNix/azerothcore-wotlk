#ifndef TRINITY_RANDOMMOTIONGENERATOR_H
#define TRINITY_RANDOMMOTIONGENERATOR_H

#include "MovementGenerator.h"
#include "PathGenerator.h"

template<class T>
class RandomMovementGenerator : public MovementGeneratorMedium< T, RandomMovementGenerator<T> >
{
    public:
        explicit RandomMovementGenerator(float distance = 0.0f) : _path(nullptr), _timer(0), _reference(), _wanderDistance(distance), _interrupt(false) { }
        ~RandomMovementGenerator();

        MovementGeneratorType GetMovementGeneratorType() { return RANDOM_MOTION_TYPE; }

        void DoInitialize(T*);
        void DoFinalize(T*);
        void DoReset(T*);
        bool DoUpdate(T*, uint32);

    private:
        void SetRandomLocation(T*);

        PathGenerator* _path;
        TimeTracker _timer;
        Position _reference;
        float _wanderDistance;
        bool _interrupt;
};

#endif
