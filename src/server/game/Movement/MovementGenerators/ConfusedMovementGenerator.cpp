#include "Creature.h"
#include "Player.h"
#include "PathGenerator.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "ConfusedMovementGenerator.h"

template<class T>
ConfusedMovementGenerator<T>::~ConfusedMovementGenerator()
{
    delete _path;
}

template<class T>
void ConfusedMovementGenerator<T>::DoInitialize(T* owner)
{
    if (!owner || !owner->IsAlive())
        return;

    owner->AddUnitState(UNIT_STATE_CONFUSED);
    owner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    owner->StopMoving();

    _timer.Reset(0);
    owner->GetPosition(_reference.x, _reference.y, _reference.z);
}

template<class T>
void ConfusedMovementGenerator<T>::DoReset(T* owner)
{
    DoInitialize(owner);
}

template<class T>
bool ConfusedMovementGenerator<T>::DoUpdate(T* owner, uint32 diff)
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

    // waiting for next move
    _timer.Update(diff);
    if (!_interrupt && _timer.Passed() && owner->movespline->Finalized())
    {
        // start moving
        owner->AddUnitState(UNIT_STATE_CONFUSED_MOVE);

        Position destination(_reference.x, _reference.y, _reference.z);
        float distance = 4.0f * frand(0.0f, 1.0f) - 2.0f;
        float angle = Position::RandomOrientation();
        owner->MovePositionToFirstCollision(destination, distance, angle);

        if (!_path)
            _path = new PathGenerator(owner);

        _path->SetPathLengthLimit(30.0f);
        bool result = _path->CalculatePath(destination.GetPositionX(), destination.GetPositionY(), destination.GetPositionZ());
        if (!result || (_path->GetPathType() & (PATHFIND_NOPATH | PATHFIND_INCOMPLETE | PATHFIND_SHORTCUT)))
        {
            _timer.Reset(100);
            return true;
        }

        Movement::MoveSplineInit init(owner);
        init.MovebyPath(_path->GetPath());
        init.SetWalk(true);
        int32 traveltime = init.Launch();
        _timer.Reset(traveltime + urand(800, 1500));
    }

    return true;
}

template<class T>
void ConfusedMovementGenerator<T>::DoFinalize(T*) { }

template<>
void ConfusedMovementGenerator<Player>::DoFinalize(Player* unit)
{
    unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->ClearUnitState(UNIT_STATE_CONFUSED);
    unit->StopMoving();
}

template<>
void ConfusedMovementGenerator<Creature>::DoFinalize(Creature* unit)
{
    unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->ClearUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_CONFUSED_MOVE);
    if (unit->GetVictim())
        unit->SetTarget(unit->GetVictim()->GetGUID());
}

template ConfusedMovementGenerator<Player>::~ConfusedMovementGenerator();
template ConfusedMovementGenerator<Creature>::~ConfusedMovementGenerator();
template void ConfusedMovementGenerator<Player>::DoInitialize(Player*);
template void ConfusedMovementGenerator<Creature>::DoInitialize(Creature*);
template void ConfusedMovementGenerator<Player>::DoReset(Player*);
template void ConfusedMovementGenerator<Creature>::DoReset(Creature*);
template bool ConfusedMovementGenerator<Player>::DoUpdate(Player*, uint32 diff);
template bool ConfusedMovementGenerator<Creature>::DoUpdate(Creature*, uint32 diff);