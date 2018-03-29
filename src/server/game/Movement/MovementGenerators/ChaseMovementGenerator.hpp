#ifndef ChaseMovementGenerator_hpp__
#define ChaseMovementGenerator_hpp__

#include "MovementGenerator.h"
#include "ThreadedPathGenerator.hpp"

class Unit;

namespace Movement
{
    template< typename T >
    struct Range
    {
        T min;
        T max;
    };

    //class ChaseMovementGenerator : public MovementGeneratorMedium< Unit, ChaseMovementGenerator >
    //{
    //public:
    //    ChaseMovementGenerator( Unit* target, float offset = 0.0f, float angle = 0.0f );

    //    MovementGeneratorType GetMovementGeneratorType() override;

    //    virtual void    DoInitialize( Unit* );
    //    virtual void    DoFinalize( Unit* );
    //    virtual void    DoReset( Unit* );
    //    virtual bool    DoUpdate( Unit*, uint32 );

    //    virtual void    MovementInform( Unit* );

    //    Unit*           GetTarget() const;

    //protected:
    //    bool            IsUnitNotAllowedToMove( Unit* target );

    //    PointsArray     GetPathToDestination( Unit* owner, const G3D::Vector3 & dest ) const;

    //    AsyncPathResult         m_asyncPath;
    //    Range< float >          m_offset;
    //    Unit*                   m_target;

    //    float                   m_angle;
    //    float                   m_extOffset;

    //    TimeTrackerSmall        m_updateTimer;
    //};
}

#endif // ChaseMovementGenerator_hpp__