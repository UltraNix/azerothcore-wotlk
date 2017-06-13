#ifndef TRINITY_CONFUSEDGENERATOR_H
#define TRINITY_CONFUSEDGENERATOR_H

#include "MovementGenerator.h"
#include "PathGenerator.h"
#include "Timer.h"

template<class T>
class ConfusedMovementGenerator : public MovementGeneratorMedium< T, ConfusedMovementGenerator<T> >
{
    public:
        explicit ConfusedMovementGenerator() : _path(nullptr), _timer(0), _reference(0.f, 0.f, 0.f), _interrupt(false) { }
        ~ConfusedMovementGenerator();

        MovementGeneratorType GetMovementGeneratorType() { return CONFUSED_MOTION_TYPE; }

        void DoInitialize(T*);
        void DoFinalize(T*);
        void DoReset(T*);
        bool DoUpdate(T*, uint32);

    private:
        PathGenerator* _path;
        TimeTracker _timer;
        G3D::Vector3 _reference;
        bool _interrupt;
};

#endif
