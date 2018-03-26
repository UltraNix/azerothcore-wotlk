#include "RandomMovementGenerator.h"
#include "Creature.h"
#include "Map.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "PathGenerator.h"
#include "ThreadedPathGenerator.hpp"

template<class T>
RandomMovementGenerator<T>::~RandomMovementGenerator() { }

template<>
RandomMovementGenerator<Creature>::~RandomMovementGenerator()
{
}

template<class T>
void RandomMovementGenerator<T>::DoInitialize(T*) { }

template<>
void RandomMovementGenerator<Creature>::DoInitialize(Creature* owner)
{
    if (!owner || !owner->IsAlive())
        return;

    owner->AddUnitState(UNIT_STATE_ROAMING);
    _reference = owner->GetPosition();
    owner->StopMoving();

    if (!_wanderDistance)
        _wanderDistance = owner->GetRespawnRadius();

    _timer.Reset(0);
}

template<class T>
void RandomMovementGenerator<T>::DoFinalize(T*) { }

template<>
void RandomMovementGenerator<Creature>::DoFinalize(Creature* owner)
{
    owner->ClearUnitState(UNIT_STATE_ROAMING);
    owner->StopMoving();
    owner->SetWalk(false);
}

template<class T>
void RandomMovementGenerator<T>::DoReset(T*) { }

template<>
void RandomMovementGenerator<Creature>::DoReset(Creature* owner)
{
    DoInitialize(owner);
}

template<class T>
void RandomMovementGenerator<T>::SetRandomLocation(T*) { }

template<>
void RandomMovementGenerator<Creature>::SetRandomLocation(Creature* owner)
{
    if (!owner)
        return;

    if (owner->HasUnitState(UNIT_STATE_NOT_MOVE))
        _interrupt = true;
    else if (owner->IsMovementPreventedByCasting())
        _interrupt = true;

    if (_interrupt)
    {
        owner->StopMoving();
        return;
    }

    owner->AddUnitState(UNIT_STATE_ROAMING_MOVE);

    Position position(_reference);
    float distance = frand(0.f, 1.f) * _wanderDistance;
    float angle = Position::RandomOrientation();
    owner->MovePositionToFirstCollision(position, distance, angle);

    AsyncPathGeneratorContext context( owner, { position.m_positionX, position.m_positionY, position.m_positionZ } );
    context.SetPathLengthLimit( 30.0f );

    m_pathRequest = Movement::GetPathGenerator().RequestPath( context );
}

template<class T>
bool RandomMovementGenerator<T>::DoUpdate(T*, uint32)
{
    return false;
}

template<>
bool RandomMovementGenerator<Creature>::DoUpdate(Creature* owner, uint32 diff)
{
    if (!owner || !owner->IsAlive())
        return false;

    if ( m_pathRequest.IsValid() && m_pathRequest.IsReady() )
    {
        auto path = std::move( m_pathRequest.GetPath() );

        if ( !( path.type & ( PATHFIND_NORMAL | PATHFIND_NOT_USING_PATH ) ) )
        {
            _timer.Reset( 100 );
            return true;
        }

        Movement::MoveSplineInit init( owner );
        init.MovebyPath( path.points );
        init.SetWalk( true );
        int32 traveltime = init.Launch();

        uint32 resetTimer = urand( 0, 1 ) ? urand( 5000, 10000 ) : urand( 250, 500 );
        _timer.Reset( traveltime + resetTimer );
        return true;
    }

    _interrupt = false;

    if (owner->HasUnitState(UNIT_STATE_NOT_MOVE))
        _interrupt = true;
    else if (owner->IsMovementPreventedByCasting())
        _interrupt = true;

    _timer.Update(diff);
    if (!_interrupt && _timer.Passed() && owner->movespline->Finalized())
    {
        SetRandomLocation( owner );
    }

    return true;
}
