#include "FollowMovementGenerator.hpp"

#include "Unit.h"
#include "MoveSplineInit.h"
#include "CreatureAI.h"

namespace Movement
{
    uint32 FollowMovementGenerator::FOLLOW_UPDATE_TIMER = 300;
    uint32 FollowMovementGenerator::FOLLOW_START_TIMER = 100;
    float FollowMovementGenerator::FOLLOW_MAX_PATH_LENGTH = 60.0f;

    FollowMovementGenerator::FollowMovementGenerator( Unit* target, float maxOffset, float angle )
        : TargetedMovementGeneratorBase( target )
        , m_offset( std::max( 0.0f, maxOffset ) )
        , m_angle( angle )
        , m_lastTargetDistance( 0.0f )
        , m_targetIsUnreachable( false )
    {
        m_offset += i_target->GetObjectSize();
    }

    MovementGeneratorType FollowMovementGenerator::GetMovementGeneratorType()
    {
        return FOLLOW_MOTION_TYPE;
    }

    void FollowMovementGenerator::DoInitialize( Unit* owner )
    {
        m_asyncPath.Invalidate();

        owner->AddUnitState( UNIT_STATE_FOLLOW );
    }

    void FollowMovementGenerator::DoFinalize( Unit* owner )
    {
        m_asyncPath.Invalidate();

        owner->ClearUnitState( UNIT_STATE_FOLLOW );
    }

    void FollowMovementGenerator::DoReset( Unit* owner )
    {
        DoInitialize( owner );
    }

    bool FollowMovementGenerator::DoUpdate( Unit* owner, uint32 diff )
    {
        if ( !i_target.isValid() || !i_target->IsInWorld() )
            return false;

        if ( HandleAsyncPathRequest( owner ) )
            return true;

        if ( !m_updateTimer.Update( diff ) )
            return true;

        if ( IsMovementSuspended( owner ) )
        {
            if ( IsStillMoving( owner ) )
            {
                StopMoving( owner, false );
            }

            return ResetTimerAndReturn( FOLLOW_START_TIMER );
        }

        SynchronizeSpeed( owner );

        G3D::Vector3 targetPosition = i_target->CalculateFuturePosition( ( ( float )FOLLOW_UPDATE_TIMER / IN_MILLISECONDS ) );
        G3D::Vector3 currPosition = !owner->movespline->Finalized() ? owner->movespline->CurrentDestination() : owner->GetPosition();

        float targetDistance = G3D::Vector3( targetPosition - currPosition ).length();

        targetPosition.x += m_offset * cos( i_target->GetOrientation() + m_angle );
        targetPosition.y += m_offset * sin( i_target->GetOrientation() + m_angle );

        //! we are near target and target is not moving, we can stop our movement
        if ( abs( targetDistance - m_offset ) <= 0.25f )
        {
            if ( IsStillMoving( owner ) && !i_target->isMoving() && owner->movespline->Finalized() )
            {
                StopMoving( owner, true );
            }

            return ResetTimerAndReturn( FOLLOW_START_TIMER );
        }

        m_lastTargetDistance = targetDistance;
        m_lastTargetPosition = targetPosition;

        //! spline in progress, check our destination for path recalculation
        if ( !owner->movespline->Finalized() )
        {
            G3D::Vector3 destPosition = owner->movespline->FinalDestination();

            //! we are on transport, destination needs to be corrected
            if ( owner->movespline->onTransport )
            {
                if ( TransportBase* transport = owner->GetDirectTransport() )
                {
                    transport->CalculatePassengerPosition( destPosition.x, destPosition.y, destPosition.z );
                }
            }

            //! spline destination is still in range, we do NOT need new path
            const float destDistance = G3D::Vector3( targetPosition - destPosition ).length();
            if ( destDistance <= 0.25f )
                return ResetTimerAndReturn( owner->movespline->timeElapsed() > FOLLOW_UPDATE_TIMER ? FOLLOW_UPDATE_TIMER : FOLLOW_START_TIMER );
        }

        AsyncPathGeneratorContext context( owner, targetPosition, false );
        m_asyncPath = std::move( GetPathGenerator().RequestPath( context ) );

        return ResetTimerAndReturn( FOLLOW_UPDATE_TIMER );
    }

    void FollowMovementGenerator::MovementInform( Unit* owner )
    {
        if ( Creature* creature = owner->ToCreature() )
        {
            CreatureAI* creatureAI = creature->AI();
            creatureAI->MovementInform( FOLLOW_MOTION_TYPE, i_target->GetGUIDLow() );
        }
    }

    Unit* FollowMovementGenerator::GetTarget() const
    {
        return nullptr;
    }

    float FollowMovementGenerator::GetLastTargetDistance() const
    {
        return m_lastTargetDistance;
    }

    void FollowMovementGenerator::SynchronizeSpeed( Unit* owner ) const
    {
        //! synchronize speed
        owner->UpdateSpeed( MOVE_WALK );
        owner->UpdateSpeed( MOVE_RUN );
    }

    bool FollowMovementGenerator::IsMovementSuspended( Unit* owner ) const
    {
        bool suspendMovement = owner->HasUnitState( UNIT_STATE_NOT_MOVE );
        suspendMovement |= owner->IsMovementPreventedByCasting();

        return suspendMovement;
    }

    bool FollowMovementGenerator::HandleAsyncPathRequest( Unit* owner )
    {
        if ( m_asyncPath.IsValid() )
        {
            if ( IsMovementSuspended( owner ) )
            {
                m_asyncPath.Invalidate();
                return false;
            }

            if ( m_asyncPath.IsReady() )
            {
                Path path( m_asyncPath.GetPath() );
                MoveByPath( owner, path );
            }

            return true;
        }

        return false;
    }

    bool FollowMovementGenerator::ResetTimerAndReturn( uint32_t interval )
    {
        return m_updateTimer.Reset( interval ), true;
    }

    bool FollowMovementGenerator::CanReachTarget( Unit* owner, Unit* target ) const
    {
        MovementInfo const& movementInfo = target->m_movementInfo;

        return !movementInfo.HasMovementFlag( MOVEMENTFLAG_FALLING | MOVEMENTFLAG_FALLING_FAR | MOVEMENTFLAG_FALLING_SLOW );
    }

    void FollowMovementGenerator::MoveByPath( Unit* owner, Movement::Path & path )
    {
        const float pathLength = path.GetPathLength();

        bool checkPathLength = !owner->GetMap()->IsBattleArena();

        Movement::MoveSplineInit spline( owner );
        if ( path.type & PATHFIND_NOPATH || checkPathLength && ( pathLength >= FOLLOW_MAX_PATH_LENGTH && ( pathLength / m_lastTargetDistance ) >= 1.5f ) )
        {
            spline.MoveTo( m_lastTargetPosition );
        }
        else
        {
            spline.MovebyPath( path.points );
        }

        spline.SetWalk( i_target->IsWalking() );
        spline.SetSmooth();
        spline.Launch();

        owner->AddUnitState( UNIT_STATE_FOLLOW_MOVE );
    }

    bool FollowMovementGenerator::IsStillMoving( Unit* owner ) const
    {
        return owner->HasUnitState( UNIT_STATE_FOLLOW_MOVE );
    }

    void FollowMovementGenerator::StopMoving( Unit* owner, bool movementInform )
    {
        owner->ClearUnitState( UNIT_STATE_FOLLOW_MOVE );

        if ( !owner->movespline->Finalized() )
        {
            owner->StopMoving();
        }

        m_asyncPath.Invalidate();

        if ( movementInform )
        {
            MovementInform( owner );
        }
    }
}
