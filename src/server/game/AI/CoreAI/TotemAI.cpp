

#include "TotemAI.h"
#include "Totem.h"
#include "Creature.h"
#include "DBCStores.h"
#include "ObjectAccessor.h"
#include "SpellMgr.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

int TotemAI::Permissible(Creature const* creature)
{
    if (creature->IsTotem())
        return PERMIT_BASE_PROACTIVE;

    return PERMIT_BASE_NO;
}

TotemAI::TotemAI(Creature* c) : CreatureAI(c), i_victimGuid(0)
{
    ASSERT(c->IsTotem());
}

void TotemAI::SpellHit(Unit* /*caster*/, const SpellInfo* spellInfo)
{
}

void TotemAI::DoAction(int32 param)
{
}

void TotemAI::MoveInLineOfSight(Unit* /*who*/)
{
}

void TotemAI::EnterEvadeMode()
{
    me->CombatStop(true);
}

void TotemAI::UpdateAI(uint32 /*diff*/)
{
    if (me->ToTotem()->GetTotemType() != TOTEM_ACTIVE)
        return;

    if (!me->IsAlive() || me->IsNonMeleeSpellCast(false))
        return;

    // Search spell
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(me->ToTotem()->GetSpell());
    if (!spellInfo)
        return;

    // Get spell range
    float max_range = spellInfo->GetMaxRange(false);

    // SPELLMOD_RANGE not applied in this place just because not existence range mods for attacking totems

    auto IsViableTarget = [this, max_range](Unit* target, Unit* owner) -> bool
    {
        if (!target)
            return false;

        if (!owner->IsInCombat() || !target->IsInCombat())
            return false;

        if (!target->isTargetableForAttack(false, me))
            return false;

        if (!target->IsValidAttackTarget(owner))
            return false;

        if (!me->IsWithinDistInMap(target, max_range))
            return false;

        if (target->IsFriendlyTo(owner))
            return false;

        return true;
    };

    if (Unit* owner = me->ToTotem()->GetSummoner())
    {
        if (IsViableTarget(ObjectAccessor::GetUnit(*me, owner->GetTarget()), owner))
            i_victimGuid = owner->GetTarget();
        else
        {
            Unit* target = nullptr;
            Trinity::NearestUnfriendlyInCombatWithOwnerNoTotemUnitInObjectRangeCheck u_check(me, me, owner, max_range);
            Trinity::UnitLastSearcher<Trinity::NearestUnfriendlyInCombatWithOwnerNoTotemUnitInObjectRangeCheck> checker(me, target, u_check);
            me->VisitNearbyObject(max_range, checker);
            if (target)
                i_victimGuid = target->GetGUID();
        }
    }

    if (Unit* victim = ObjectAccessor::GetUnit(*me, i_victimGuid))
    {
        me->SetInFront(victim);                         // client change orientation by self
        me->CastSpell(victim, me->ToTotem()->GetSpell(), false);
    }
    else
        i_victimGuid = 0;
}

void TotemAI::AttackStart(Unit* /*victim*/)
{
    // Sentry totem sends ping on attack
    if (me->GetEntry() == SENTRY_TOTEM_ENTRY && me->GetOwner()->GetTypeId() == TYPEID_PLAYER)
    {
        WorldPacket data(MSG_MINIMAP_PING, (8+4+4));
        data << me->GetGUID();
        data << me->GetPositionX();
        data << me->GetPositionY();
        me->GetOwner()->ToPlayer()->GetSession()->SendPacket(&data);
    }
}
