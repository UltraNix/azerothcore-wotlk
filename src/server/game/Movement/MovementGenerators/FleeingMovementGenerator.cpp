#include "VMapFactory.h"
#include "CreatureAI.h"
#include "ObjectAccessor.h"
#include "Creature.h"
#include "Player.h"
#include "PathGenerator.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "FleeingMovementGenerator.h"

#define MIN_QUIET_DISTANCE 15.f
#define MAX_QUIET_DISTANCE 30.f

template<class T>
FleeingMovementGenerator<T>::~FleeingMovementGenerator()
{
    delete _path;
}

template<class T>
void FleeingMovementGenerator<T>::DoInitialize(T* owner)
{
    if (!owner)
        return;

    owner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);
    owner->AddUnitState(UNIT_STATE_FLEEING);
    SetTargetLocation(owner);
}

template<class T>
void FleeingMovementGenerator<T>::DoFinalize(T *) { }

template<>
void FleeingMovementGenerator<Player>::DoFinalize(Player* owner)
{
    owner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);
    owner->ClearUnitState(UNIT_STATE_FLEEING);
    owner->StopMoving();
}

template<>
void FleeingMovementGenerator<Creature>::DoFinalize(Creature* owner)
{
    owner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);
    owner->ClearUnitState(UNIT_STATE_FLEEING | UNIT_STATE_FLEEING_MOVE);
    if (owner->GetVictim())
        owner->SetTarget(owner->GetVictim()->GetGUID());
}

template<class T>
void FleeingMovementGenerator<T>::DoReset(T* owner)
{
    DoInitialize(owner);
}

template<class T>
bool FleeingMovementGenerator<T>::DoUpdate(T* owner, uint32 diff)
{
    if (!owner || !owner->IsAlive())
        return false;

    if (owner->HasUnitState(UNIT_STATE_NOT_MOVE))
    {
        _interrupt = true;
        owner->StopMoving();
        return true;
    }
    else
        _interrupt = false;

    _timer.Update(diff);
    if (!_interrupt && _timer.Passed() && owner->movespline->Finalized())
        SetTargetLocation(owner);

    return true;
}

template<class T>
void FleeingMovementGenerator<T>::SetTargetLocation(T* owner)
{
    if (!owner)
        return;

    if (owner->HasUnitState(UNIT_STATE_NOT_MOVE))
    {
        _interrupt = true;
        owner->StopMoving();
        return;
    }

    owner->AddUnitState(UNIT_STATE_FLEEING_MOVE);

    Position destination;
    owner->GetPosition(&destination);
    GetPoint(owner, destination);

    Position currentPosition;
    owner->GetPosition(&currentPosition);
    if (!VMAP::VMapFactory::createOrGetVMapManager()->isInLineOfSight(owner->GetMapId(), currentPosition.m_positionX, currentPosition.m_positionY, currentPosition.m_positionZ + 2.0f, destination.GetPositionX(), destination.GetPositionY(), destination.GetPositionZ() + 2.0f))
    {
        _timer.Reset(200);
        return;
    }

    if (!_path)
        _path = new PathGenerator(owner);

    _path->SetPathLengthLimit(30.0f);
    bool result = _path->CalculatePath(destination.GetPositionX(), destination.GetPositionY(), destination.GetPositionZ());
    if (!result || (_path->GetPathType() & (PATHFIND_NOPATH | PATHFIND_INCOMPLETE)))
    {
        _timer.Reset(100);
        return;
    }

    Movement::MoveSplineInit init(owner);
    init.MovebyPath(_path->GetPath());
    init.SetWalk(false);
    int32 traveltime = init.Launch();
    _timer.Reset(traveltime + urand(800, 1500));
}

template<class T>
void FleeingMovementGenerator<T>::GetPoint(T* owner, Position &position)
{
    float casterDistance, casterAngle;
    if (Unit* fleeTarget = ObjectAccessor::GetUnit(*owner, _fleeTargetGUID))
    {
        casterDistance = fleeTarget->GetDistance(owner);
        if (casterDistance > 0.2f)
            casterAngle = fleeTarget->GetAngle(owner);
        else
            casterAngle = Position::RandomOrientation();
    }
    else
    {
        casterDistance = 0.0f;
        casterAngle = Position::RandomOrientation();
    }

    float distance, angle;
    if (casterDistance < MIN_QUIET_DISTANCE)
    {
        distance = frand(0.8f, 1.3f) * (MIN_QUIET_DISTANCE - (casterDistance / 2));
        angle = casterAngle + frand(-static_cast<float>(M_PI) / 4, static_cast<float>(M_PI) / 4);
    }
    else if (casterDistance > MAX_QUIET_DISTANCE)
    {
        distance = frand(0.5f, 1.0f) * (MAX_QUIET_DISTANCE - MIN_QUIET_DISTANCE);
        angle = static_cast<float>(M_PI) + casterAngle + frand(-static_cast<float>(M_PI) / 4, static_cast<float>(M_PI) / 4);
    }
    else
    {
        distance = frand(0.7f, 1.0f) * (MAX_QUIET_DISTANCE - MIN_QUIET_DISTANCE);
        angle = Position::RandomOrientation();
    }

    angle -= owner->GetOrientation();
    owner->MovePositionToFirstCollision(position, distance, angle);
}

template FleeingMovementGenerator<Player>::~FleeingMovementGenerator();
template FleeingMovementGenerator<Creature>::~FleeingMovementGenerator();
template void FleeingMovementGenerator<Player>::DoInitialize(Player*);
template void FleeingMovementGenerator<Creature>::DoInitialize(Creature*);
template void FleeingMovementGenerator<Player>::DoReset(Player*);
template void FleeingMovementGenerator<Creature>::DoReset(Creature*);
template bool FleeingMovementGenerator<Player>::DoUpdate(Player*, uint32);
template bool FleeingMovementGenerator<Creature>::DoUpdate(Creature*, uint32);
template void FleeingMovementGenerator<Player>::SetTargetLocation(Player*);
template void FleeingMovementGenerator<Creature>::SetTargetLocation(Creature*);
template void FleeingMovementGenerator<Player>::GetPoint(Player*, Position &);
template void FleeingMovementGenerator<Creature>::GetPoint(Creature*, Position &);

//---- TimedFleeingMovementGenerator

bool TimedFleeingMovementGenerator::Update(Unit* owner, uint32 time_diff)
{
    if (!owner->IsAlive())
        return false;

    _totalFleeTime.Update(time_diff);
    if (_totalFleeTime.Passed())
        return false;

    return MovementGeneratorMedium< Creature, FleeingMovementGenerator<Creature> >::Update(owner, time_diff);
}

void TimedFleeingMovementGenerator::Finalize(Unit* owner)
{
    owner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_FLEEING);
    owner->ClearUnitState(UNIT_STATE_FLEEING);
    owner->StopMoving();
    if (Unit* victim = owner->GetVictim())
    {
        if (owner->IsAlive())
        {
            owner->AttackStop();
            owner->ToCreature()->AI()->AttackStart(victim);
        }
    }
}
