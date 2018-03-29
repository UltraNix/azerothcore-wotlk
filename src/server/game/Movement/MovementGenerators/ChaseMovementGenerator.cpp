//#include "ChaseMovementGenerator.hpp"
//
//#include "Player.h"
//#include "Creature.h"
//#include "MoveSplineInit.h"
//#include "CreatureAI.h"
//#include "Spell.h"
//
//namespace Movement
//{
//    //! #TODO: move to config
//    const uint32 DEFAULT_UPDATE_TIMER = 1 * 1000;
//
//    ChaseMovementGenerator::ChaseMovementGenerator( Unit* target, float offset, float angle )
//        : m_angle( angle )
//        , m_target( target )
//        , m_extOffset( offset )
//        , m_updateTimer( DEFAULT_UPDATE_TIMER )
//    {
//    }
//
//    MovementGeneratorType ChaseMovementGenerator::GetMovementGeneratorType()
//    {
//        return CHASE_MOTION_TYPE;
//    }
//
//    void ChaseMovementGenerator::DoInitialize( Unit* owner )
//    {
//        //! creature
//        owner->SetWalk( false );
//
//        owner->AddUnitState( UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE );
//
//        const float offset = m_extOffset > 0.0f ? m_extOffset : owner->GetCombatReach();
//
//        const float minRange = owner->GetCombatReach();
//        const float maxRange = minRange + owner->GetObjectSize();
//
//        m_offset = Range< float >{ minRange, maxRange };
//    }
//
//    void ChaseMovementGenerator::DoReset( Unit* owner )
//    {
//        DoInitialize( owner );
//    }
//
//    void ChaseMovementGenerator::DoFinalize( Unit* owner )
//    {
//        owner->ClearUnitState( UNIT_STATE_CHASE | UNIT_STATE_CHASE_MOVE );
//    }
//
//    bool ChaseMovementGenerator::DoUpdate( Unit* owner, uint32 diff )
//    {
//        if ( !m_target->IsInWorld() )
//            return false;
//
//        if ( m_asyncPath.IsValid() )
//        {
//            //! path was requested in the past and result is now ready
//            if ( m_asyncPath.IsReady() )
//            {
//                auto path = std::move( m_asyncPath.GetPath() );
//                if ( path.type & PATHFIND_NOPATH )
//                    return true;
//
//                Movement::MoveSplineInit spline( owner );
//                spline.MovebyPath( path.points );
//                spline.SetFacing( m_target );
//                spline.SetWalk( false );
//                spline.Launch();
//            }
//
//            owner->AddUnitState( UNIT_STATE_CHASE_MOVE );
//            return true;
//        }
//
//        //! #TODO: research it and cast owner only once
//        if ( Creature* creature = owner->ToCreature() )
//        {
//            creature->SetCannotReachTarget( false );
//        }
//
//        if ( IsUnitNotAllowedToMove( owner ) )
//        {
//            if ( !owner->IsStopped() )
//            {
//                owner->StopMoving();
//            }
//            return true;
//        }
//
//        if ( !m_updateTimer.Update( diff ) )
//            return true;
//
//        m_updateTimer.Reset( DEFAULT_UPDATE_TIMER );
//
//        //! #TODO: research it and cast owner only once
//        if ( Creature* creature = owner->ToCreature() )
//        {
//            creature->SetCannotReachTarget( !m_target->isInAccessiblePlaceFor( creature ) );
//        }
//
//        G3D::Vector3 destPosition = owner->movespline->FinalDestination();
//        G3D::Vector3 const targetPosition = m_target->GetPosition();
//        G3D::Vector3 const& currPosition = owner->movespline->CurrentDestination();
//
//        //! we are on spline, destination needs to be corrected
//        if ( owner->movespline->onTransport )
//        {
//            if ( TransportBase* transport = owner->GetDirectTransport() )
//            {
//                transport->CalculatePassengerPosition( destPosition.x, destPosition.y, destPosition.z );
//            }
//        }
//
//        G3D::Vector3 direction( targetPosition - currPosition );
//        const float targetDistance = direction.length();
//
//        direction /= targetDistance;
//
//        bool recalculatePath = false;
//        if ( owner->movespline->Finalized() )
//        {
//            MovementInform( owner );
//
//            //! we are to far away from target
//            recalculatePath = targetDistance > m_offset.max;
//        }
//        else
//        {
//            //! target moved to far away from out destination
//            recalculatePath = ( targetPosition - destPosition ).length() > m_offset.max;
//        }
//
//        if ( !recalculatePath )
//            return true;
//
//        const float offset = ( m_offset.max + m_offset.min ) / 2.0f;
//
//        AsyncPathGeneratorContext context( owner, targetPosition - direction * offset );
//        m_asyncPath = std::move( GetPathGenerator().RequestPath( context ) );
//
//        return true;
//    }
//
//    void ChaseMovementGenerator::MovementInform( Unit* owner )
//    {
//        if ( owner->IsWithinMeleeRange( m_target ) )
//        {
//            owner->Attack( m_target, true );
//        }
//
//        if ( m_angle <= 0.0f && !owner->HasInArc( 0.01f, m_target ) )
//        {
//            owner->SetInFront( m_target );
//        }
//
//        if ( Creature* creature = owner->ToCreature() )
//        {
//            CreatureAI* creatureAI = creature->AI();
//            creatureAI->MovementInform( CHASE_MOTION_TYPE, m_target->GetGUIDLow() );
//        }
//    }
//
//    Unit* ChaseMovementGenerator::GetTarget() const
//    {
//        return nullptr;
//    }
//
//    bool ChaseMovementGenerator::IsUnitNotAllowedToMove( Unit* owner )
//    {
//        bool isNotAllowedToMove = owner->HasUnitState( UNIT_STATE_NOT_MOVE );   //! unit is rooted/stunned/distracted
//        isNotAllowedToMove |= owner->IsMovementPreventedByCasting();            //! unit is casting
//
//        return isNotAllowedToMove;
//    }
//
//    Movement::PointsArray ChaseMovementGenerator::GetPathToDestination( Unit* owner, const G3D::Vector3 & dest ) const
//    {
//        Movement::PointsArray result;
//
//        PathGenerator generator( owner );
//        if ( generator.CalculatePath( dest, false ) )
//        {
//            result = std::move( generator.StealPath() );
//        }
//
//        //! should not happen
//        if ( generator.GetPathType() & PATHFIND_NOPATH )
//        {
//            result.push_back( owner->GetPosition() );
//            result.push_back( dest );
//        }
//
//        return result;
//    }
//}
