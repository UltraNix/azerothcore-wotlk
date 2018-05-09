#include "FollowMovementGenerator.hpp"

#include "Unit.h"
#include "MoveSplineInit.h"
#include "CreatureAI.h"
#include "Player.h"
namespace Movement
{
    uint32 FollowMovementGenerator::FOLLOW_UPDATE_TIMER = 300;
    uint32 FollowMovementGenerator::FOLLOW_START_TIMER = 100;
    float FollowMovementGenerator::FOLLOW_MAX_PATH_LENGTH = 60.0f;

    FollowMovementGenerator::FollowMovementGenerator( Unit* target, float maxOffset, float angle )
        : TargetedMovementGeneratorBase( target )
        , m_offset( std::max( 0.0f, maxOffset ) )
        , m_angle( angle )
        , m_isTargetMoving( false )
        , m_lastTargetDistance( 0.0f )
        , m_needsMovementInform( false )
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

        owner->AddUnitState( UNIT_STATE_FOLLOW | UNIT_STATE_FOLLOW_MOVE );

        ForceNewPath();
    }

    void FollowMovementGenerator::DoFinalize( Unit* owner )
    {
        m_asyncPath.Invalidate();

        owner->ClearUnitState( UNIT_STATE_FOLLOW | UNIT_STATE_FOLLOW_MOVE );

        SynchronizeSpeed( owner );
    }

    void FollowMovementGenerator::DoReset( Unit* owner )
    {
        DoInitialize( owner );
    }

    G3D::Vector3 GetAbsolutePositionForSpline( Unit* owner, G3D::Vector3 position )
    {
        //! we are on transport, position needs to be corrected
        if ( owner->movespline->onTransport )
        {
            if ( TransportBase* transport = owner->GetDirectTransport() )
            {
                transport->CalculatePassengerPosition( position.x, position.y, position.z );
            }
        }

        return position;
    }

    bool FollowMovementGenerator::DoUpdate( Unit* owner, uint32 diff )
    {
        if ( !i_target.isValid() || !i_target->IsInWorld() )
            return false;

        if ( HandleAsyncPathRequest( owner ) )
            return true;

        if ( !m_updateTimer.Update( diff ) )
            return true;

        bool isOwnerMoving = owner->HasUnitState( UNIT_STATE_FOLLOW_MOVE );
        if ( IsMovementSuspended( owner ) )
        {
            if ( isOwnerMoving )
            {
                StopMoving( owner, true );
            }

            return ResetTimerAndReturn( FOLLOW_START_TIMER );
        }

        m_isTargetMoving = ( ( G3D::Vector3 )i_target->GetPosition() - m_lastTargetPosition ).length() > 0.05f && i_target->isMoving();

        G3D::Vector3 targetPosition = m_isTargetMoving ? i_target->CalculateFuturePosition( ( ( float )FOLLOW_UPDATE_TIMER / IN_MILLISECONDS ) ) : ( G3D::Vector3 )i_target->GetPosition();
        G3D::Vector3 currPosition = !owner->movespline->Finalized() ? GetAbsolutePositionForSpline( owner, owner->movespline->CurrentDestination() ) : owner->GetPosition();

        m_lastTargetDistance = G3D::Vector3( targetPosition - currPosition ).length();
        if ( !m_forceNewPath && m_lastTargetDistance < ( m_offset + 0.25f ) )
        {
            if ( isOwnerMoving && !m_isTargetMoving )
            {
                StopMoving( owner );
            }

            if ( m_needsMovementInform )
            {
                MovementInform( owner );
            }

            return ResetTimerAndReturn( FOLLOW_START_TIMER );
        }

        UpdateCurrDestination( targetPosition );

        //! spline in progress, check our destination for path recalculation
        if ( !m_forceNewPath && !owner->movespline->Finalized() )
        {
            G3D::Vector3 splineDestination = GetAbsolutePositionForSpline( owner, owner->movespline->FinalDestination() );

            //! spline destination is still in range, we do NOT need new path
            const float distance = G3D::Vector3( m_currDestination - splineDestination ).length();
            if ( distance <= 0.25f )
                return ResetTimerAndReturn( owner->movespline->timeElapsed() > FOLLOW_UPDATE_TIMER ? FOLLOW_UPDATE_TIMER : FOLLOW_START_TIMER );
        }

        RequestPathToCurrDestination( owner );
        return ResetTimerAndReturn( FOLLOW_UPDATE_TIMER );
    }

    void FollowMovementGenerator::MovementInform( Unit* owner )
    {
        m_needsMovementInform = false;

        if ( Creature* creature = owner->ToCreature() )
        {
            CreatureAI* creatureAI = creature->AI();
            creatureAI->MovementInform( FOLLOW_MOTION_TYPE, i_target->GetGUIDLow() );
        }
    }

    Unit* FollowMovementGenerator::GetTarget() const
    {
        return *i_target;
    }

    void FollowMovementGenerator::unitSpeedChanged()
    {
        ForceNewPath();
    }

    void FollowMovementGenerator::ForceNewPath()
    {
        m_forceNewPath = true;
        ResetTimerAndReturn( 0 );
    }

    void FollowMovementGenerator::RequestPathToCurrDestination( Unit* owner )
    {
        if ( MMAP::MMapFactory::IsPathfindingEnabled( owner->FindMap() ))
        {
            bool forceDest = i_target->GetTypeId() == TYPEID_PLAYER && i_target->ToPlayer()->IsGameMaster();     // .npc follow always force dest
            forceDest |= owner->GetTypeId() == TYPEID_UNIT && owner->IsPet();                                    // pets should always force dest
            forceDest |= owner->GetTransport() != nullptr && owner->GetTransport() == i_target->GetTransport();  // No mmaps on transports

            AsyncPathGeneratorContext context( owner, m_currDestination, forceDest );
            context.SetFallbackOrigin( m_lastTargetPosition );
            context.DisableExtendedPolySearch();

            m_asyncPath = std::move( GetPathGenerator().RequestPath( context ) );
        }
        else
        {
            PathPromise promise;
            m_asyncPath = AsyncPathResult( promise.get_future() );

            //! Move to target position if height diff is to big
            Position pos( m_lastTargetPosition.x, m_lastTargetPosition.y, m_lastTargetPosition.z );
            i_target->MovePositionToFirstCollision( pos, m_offset, m_angle );

            m_currDestination = pos;

            promise.set_value( { PATHFIND_SHORTCUT, PointsArray{ owner->GetPosition(), G3D::Vector3{ pos } } } );
        }
    }

    void FollowMovementGenerator::UpdateCurrDestination( const G3D::Vector3 & position )
    {
        m_lastTargetPosition = position;

        m_currDestination = position;
        m_currDestination.x += m_offset * cos( i_target->GetOrientation() + m_angle );
        m_currDestination.y += m_offset * sin( i_target->GetOrientation() + m_angle );
    }

    void FollowMovementGenerator::SynchronizeSpeed( Unit* owner ) const
    {
        if ( !IS_PLAYER_GUID( owner->GetOwnerGUID() ) || !owner->IsInWorld() || !i_target.isValid() || i_target->GetGUID() != owner->GetOwnerGUID() )
            return;

        //! synchronize speed
        owner->UpdateSpeed( MOVE_WALK );
        owner->UpdateSpeed( MOVE_RUN );
        owner->UpdateSpeed( MOVE_SWIM );
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

                m_needsMovementInform = true;
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
        SynchronizeSpeed( owner );

        const float pathLength = path.GetPathLength();
        const bool isInArena = owner->GetMap()->IsBattleArena();

        Movement::MoveSplineInit spline( owner );
        if ( path.type & PATHFIND_NOPATH || ( isInArena && path.type & PATHFIND_INCOMPLETE && abs( m_currDestination.z - path.points.back().z ) > 1.0f ) )
        {
            spline.MoveTo( m_lastTargetPosition );
        }
        else if ( !isInArena && ( pathLength >= FOLLOW_MAX_PATH_LENGTH && ( pathLength / m_lastTargetDistance ) >= 1.5f ) )
        {
            spline.MoveTo( m_currDestination );
        }
        else
        {
            spline.MovebyPath( path.points );
        }

        bool isWalking = i_target->IsWalking();
        isWalking |= i_target->IsCreature() && i_target->movespline->isWalking();

        spline.SetWalk( isWalking );
        spline.SetSmooth();
        spline.Launch();

        //! real destination after movemap transform
        m_currDestination = GetAbsolutePositionForSpline( owner, owner->movespline->FinalDestination() );

        owner->AddUnitState( UNIT_STATE_FOLLOW_MOVE );
    }

    void FollowMovementGenerator::StopMoving( Unit* owner, bool finalizeSpline )
    {
        owner->ClearUnitState( UNIT_STATE_FOLLOW_MOVE );

        if ( finalizeSpline && !owner->movespline->Finalized() )
        {
            owner->StopMoving();
        }

        m_asyncPath.Invalidate();
    }
}
