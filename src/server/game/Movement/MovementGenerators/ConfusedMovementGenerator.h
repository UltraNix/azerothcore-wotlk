
#ifndef TRINITY_CONFUSEDGENERATOR_H
#define TRINITY_CONFUSEDGENERATOR_H

#include "MovementGenerator.h"
#include "Timer.h"

#define MAX_CONF_WAYPOINTS 24 //! Allows a twelve second confusion if i_nextMove always is the absolute minimum timer.

template<class T>
class ConfusedMovementGenerator : public MovementGeneratorMedium< T, ConfusedMovementGenerator<T> >
{
    public:
        explicit ConfusedMovementGenerator( float extendedRange = 0.0f ) : i_extendedRange( extendedRange ) {}

        void                    DoInitialize( T* );
        void                    DoFinalize( T* );
        void                    DoReset( T* );
        bool                    DoUpdate( T*, uint32 );

        MovementGeneratorType   GetMovementGeneratorType() { return CONFUSED_MOTION_TYPE; }

    private:
        void                    _InitSpecific(T*, bool &, bool &);

        float                   i_extendedRange;
        Movement::PointsArray   i_waypoints;
};
#endif
