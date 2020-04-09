#include "Creature.h"
#include "MapManager.h"
#include "ConfusedMovementGenerator.h"
#include "VMapFactory.h"
#include "MoveSplineInit.h"
#include "MoveSpline.h"
#include "Player.h"
#include "SpellAuraEffects.h"

template<>
void ConfusedMovementGenerator<Creature>::DoInitialize(Creature* unit)
{
    InitIsSmallPath(unit);
    unit->AddUnitState(UNIT_STATE_CONFUSED);
    unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->StopMoving();
    _waterOK = unit->ToCreature()->CanSwim();
    _landOK = unit->ToCreature()->CanWalk();

    _timer.Reset(0);
    unit->GetPosition(_reference.x, _reference.y, _reference.z);
}

template<>
void ConfusedMovementGenerator<Player>::DoInitialize(Player* unit)
{
    InitIsSmallPath(unit);
    unit->AddUnitState(UNIT_STATE_CONFUSED);
    unit->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->StopMoving();
    _waterOK = _landOK = true;

    _timer.Reset(0);
    unit->GetPosition(_reference.x, _reference.y, _reference.z);
}

template<class T>
void ConfusedMovementGenerator<T>::InitIsSmallPath(T* unit)
{
    for (AuraEffect* aurEff : unit->GetAuraEffectsByType(SPELL_AURA_MOD_CONFUSE))
    {
        SpellInfo const* spellInfo = aurEff->GetSpellInfo();
        int32 bp = spellInfo->Effects[aurEff->GetEffIndex()].BasePoints;
        if (++bp == 0)
        {
            _smallPath = true;
            break;
        }
    }
}

template<class T>
void ConfusedMovementGenerator<T>::DoReset(T* unit)
{
    DoInitialize(unit);
}

template<class T>
void ConfusedMovementGenerator<T>::SetLocation(T* unit)
{
    if (!unit)
        return;

    if (unit->HasUnitState(UNIT_STATE_NOT_MOVE))
        _interrupt = true;

    if (_interrupt)
    {
        unit->StopMoving();
        return;
    }

    float speedFactor = unit->GetSpeedRate(MOVE_RUN);
    Map* map = unit->GetMap();
    float dist = (_smallPath ? 1.2f : frand(1.5f, 2.0f) + speedFactor * 2.0f) + _extendedRange;
    float angle = Position::RandomOrientation();
    Position pos(_reference.x, _reference.y, _reference.z);
    Position lastGoodPosition(pos);

    float step = dist / CONFUSED_MOVEMENT_STEP_AMOUNT;
    for (uint32 idx = 0; idx < CONFUSED_MOVEMENT_STEP_AMOUNT; ++idx)
    {
        pos.m_positionX += std::cos(angle) * step;
        pos.m_positionY += std::sin(angle) * step;
        unit->UpdateAllowedPositionZ(pos.m_positionX, pos.m_positionY, pos.m_positionZ);

        if (!_landOK && !_waterOK)
            break;

        bool posInWater = map->IsInWater(pos.m_positionX, pos.m_positionY, pos.m_positionZ);
        if (posInWater && !_waterOK)
            break;

        if (!posInWater && fabs(lastGoodPosition.GetPositionZ() - pos.GetPositionZ()) > 1.0f)
            break;

        if (!unit->IsWithinLOS(pos.m_positionX, pos.m_positionY, pos.m_positionZ))
            break;

        lastGoodPosition = pos;
    }

    AsyncPathGeneratorContext context(unit, { lastGoodPosition.m_positionX, lastGoodPosition.m_positionY, lastGoodPosition.m_positionZ });
    context.SetPathLengthLimit(30.0f);
    _pathRequest = Movement::GetPathGenerator().RequestPath(context);
}

template<class T>
bool ConfusedMovementGenerator<T>::DoUpdate(T* unit, uint32 diff)
{
    if (!unit || !unit->IsAlive())
        return false;

    if (unit->HasUnitState(UNIT_STATE_NOT_MOVE))
    {
        _interrupt = true;
        unit->StopMoving();
        return true;
    }
    else
        _interrupt = false;

    if (_pathRequest.IsValid() && _pathRequest.IsReady())
    {
        if (_interrupt)
            return _pathRequest.Invalidate(), true;

        auto path = std::move(_pathRequest.GetPath());
        if (path.type & (PATHFIND_NOPATH | PATHFIND_INCOMPLETE | PATHFIND_SHORTCUT))
        {
            _timer.Reset(100);
            return true;
        }

        unit->AddUnitState(UNIT_STATE_CONFUSED_MOVE);
        Movement::MoveSplineInit init(unit);
        init.MovebyPath(path.points);
        //init.SetWalk(true);
        int32 traveltime = init.Launch();
        _timer.Reset(traveltime + _smallPath ? 250 : urand(800, 1000));
        return true;
    }

    _timer.Update(diff);
    if (!_interrupt && _timer.Passed() && unit->movespline->Finalized())
        SetLocation(unit);

    return true;
}

template<>
void ConfusedMovementGenerator<Player>::DoFinalize(Player* unit)
{
    unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->ClearUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_CONFUSED_MOVE);
    unit->StopMoving();
}

template<>
void ConfusedMovementGenerator<Creature>::DoFinalize(Creature* unit)
{
    unit->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_CONFUSED);
    unit->ClearUnitState(UNIT_STATE_CONFUSED | UNIT_STATE_CONFUSED_MOVE);
    if (unit->GetVictim())
        unit->SetTarget(unit->GetVictim()->GetGUID());

    unit->StopMoving();
}

template void ConfusedMovementGenerator<Player>::DoInitialize(Player*);
template void ConfusedMovementGenerator<Creature>::DoInitialize(Creature*);
template void ConfusedMovementGenerator<Player>::DoReset(Player*);
template void ConfusedMovementGenerator<Creature>::DoReset(Creature*);
template bool ConfusedMovementGenerator<Player>::DoUpdate(Player*, uint32 diff);
template bool ConfusedMovementGenerator<Creature>::DoUpdate(Creature*, uint32 diff);
