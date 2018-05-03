#ifndef FollowMovementGenerator_hpp__
#define FollowMovementGenerator_hpp__

#include "MovementGenerator.h"
#include "ThreadedPathGenerator.hpp"
#include "FollowerReference.h"
#include "TargetedMovementGenerator.h"

class Unit;

namespace Movement
{
    class FollowMovementGenerator : public MovementGeneratorMedium< Unit, FollowMovementGenerator >, protected TargetedMovementGeneratorBase
    {
    public:
        static uint32 FOLLOW_UPDATE_TIMER;
        static uint32 FOLLOW_START_TIMER;
        static float FOLLOW_MAX_PATH_LENGTH;

        FollowMovementGenerator( Unit* target, float maxOffset = 0.0f, float angle = 0.0f );

        MovementGeneratorType GetMovementGeneratorType() override;

        virtual void        DoInitialize( Unit* );
        virtual void        DoFinalize( Unit* );
        virtual void        DoReset( Unit* );
        virtual bool        DoUpdate( Unit*, uint32 );

        virtual void        MovementInform( Unit* );

        Unit*               GetTarget() const;
        float               GetLastTargetDistance() const;

    protected:
        void                RequestPath( Unit* owner, const G3D::Vector3 & position );
        void                SynchronizeSpeed( Unit* owner ) const;
        bool                IsMovementSuspended( Unit* owner ) const;

        bool                HandleAsyncPathRequest( Unit* owner );

        bool                ResetTimerAndReturn( uint32_t interval );
        bool                CanReachTarget( Unit* owner, Unit* target ) const;

        void                MoveByPath( Unit* owner, Movement::Path & path );

        bool                IsStillMoving( Unit* owner ) const;
        void                StopMoving( Unit* owner );

        AsyncPathResult     m_asyncPath;
        float               m_offset;
        float               m_angle;
        TimeTrackerSmall    m_updateTimer;

        bool                m_needsMovementInform;
        bool                m_targetIsUnreachable;
        float               m_lastTargetDistance;
        G3D::Vector3        m_lastTargetPosition;
        G3D::Vector3        m_lastTargetRealPosition;
    };
}

#endif // FollowMovementGenerator_hpp__