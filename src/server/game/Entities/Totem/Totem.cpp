

#include "Totem.h"
#include "Log.h"
#include "Group.h"
#include "ObjectMgr.h"
#include "Opcodes.h"
#include "Player.h"
#include "SpellAuraEffects.h"
#include "SpellMgr.h"
#include "SpellInfo.h"
#include "WorldPacket.h"

Totem::Totem(SummonPropertiesEntry const* properties, uint64 owner) : Minion(properties, owner, false)
{
    m_unitTypeMask |= UNIT_MASK_TOTEM;
    m_duration = 0;
    m_type = TOTEM_PASSIVE;
}

void Totem::Update(uint32 time)
{
    if (!GetOwner()->IsAlive() || !IsAlive())
    {
        UnSummon();                                         // remove self
        return;
    }

    if (m_duration <= time)
    {
        UnSummon();                                         // remove self
        return;
    }
    else
        m_duration -= time;

    Creature::Update(time);
}

void Totem::InitStats(uint32 duration)
{
    m_duration = duration;

    // client requires SMSG_TOTEM_CREATED to be sent before adding to world and before removing old totem
    // Xinef: Set level for Unit totems
    if (Unit* owner = ObjectAccessor::FindUnit(m_owner))
    {
        if (owner->GetTypeId() == TYPEID_PLAYER && m_Properties->Slot >= SUMMON_SLOT_TOTEM && m_Properties->Slot < MAX_TOTEM_SLOT)
        {
            WorldPacket data(SMSG_TOTEM_CREATED, 1 + 8 + 4 + 4);
            data << uint8(m_Properties->Slot - 1);
            data << uint64(GetGUID());
            data << uint32(duration);
            data << uint32(GetUInt32Value(UNIT_CREATED_BY_SPELL));
            owner->ToPlayer()->SendDirectMessage(&data);

            // set display id depending on caster's race
            SetDisplayId(owner->GetModelForTotem(PlayerTotemType(m_Properties->Id)));
        }

        SetLevel(owner->getLevel());
    }

    Minion::InitStats(duration);

    // Get spell cast by totem
    if (SpellInfo const* totemSpell = sSpellMgr->GetSpellInfo(GetSpell()))
        if (totemSpell->CalcCastTime())   // If spell has cast time -> its an active totem
            m_type = TOTEM_ACTIVE;
}

class DelayedTotemInitCastSpell : public BasicEvent
{
    public:
        explicit DelayedTotemInitCastSpell(Totem* me) : _me(me) {}

        bool Execute(uint64 /*time*/, uint32 /*diff*/) override
        {
            _me->CastSpell(_me, _me->GetSpell(), true);
            return true;
        }

    private:
        Totem* _me;
};

void Totem::InitSummon()
{
    // Delay init cast by one world tick to emulate proper cast order from retail
    if (m_type == TOTEM_PASSIVE && GetSpell())
        m_Events.AddEvent(new DelayedTotemInitCastSpell(this), m_Events.CalculateTime(1));

    // Some totems can have both instant effect and passive spell
    if(GetSpell(1))
        CastSpell(this, GetSpell(1), true);

    // xinef: this is better than the script, 100% sure to work
    if(GetEntry() == SENTRY_TOTEM_ENTRY)
    {
        SetReactState(REACT_AGGRESSIVE);
        GetOwner()->CastSpell(this, 6277, true);
    }

    this->GetMotionMaster()->MoveFall();
}

void Totem::UnSummon(uint32 msTime)
{
    if (msTime)
    {
        m_Events.AddEvent(new ForcedUnsummonDelayEvent(*this), m_Events.CalculateTime(msTime));
        return;
    }

    CombatStop();
    RemoveAurasDueToSpell(GetSpell(), GetGUID());

    Unit *m_owner = GetOwner();
    // clear owner's totem slot
    for (uint8 i = SUMMON_SLOT_TOTEM; i < MAX_TOTEM_SLOT; ++i)
    {
        if (m_owner->m_SummonSlot[i] == GetGUID())
        {
            m_owner->m_SummonSlot[i] = 0;
            break;
        }
    }

    m_owner->RemoveAurasDueToSpell(GetSpell(), GetGUID());

    // Remove Sentry Totem Aura
    if (GetEntry() == SENTRY_TOTEM_ENTRY)
        m_owner->RemoveAurasDueToSpell(SENTRY_TOTEM_SPELLID);

    //remove aura all party members too
    if (Player* owner = m_owner->ToPlayer())
    {
        owner->SendAutoRepeatCancel(this);

        if (SpellInfo const* spell = sSpellMgr->GetSpellInfo(GetUInt32Value(UNIT_CREATED_BY_SPELL)))
            owner->SendCooldownEvent(spell, 0, NULL, false);

        if (Group* group = owner->GetGroup())
        {
            for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
            {
                Player* target = itr->GetSource();
                if (target && target->IsInMap(owner) && group->SameSubGroup(owner, target))
                    target->RemoveAurasDueToSpell(GetSpell(), GetGUID());
            }
        }
    }

    AddObjectToRemoveList();
}

bool Totem::IsImmunedToSpellEffect(SpellInfo const* spellInfo, uint32 index) const
{
    // xinef: immune to all positive spells, except of stoneclaw totem absorb and sentry totem bind sight
    // totems positive spells have unit_caster target
    if (spellInfo->Effects[index].Effect != SPELL_EFFECT_DUMMY &&
        spellInfo->Effects[index].Effect != SPELL_EFFECT_SCRIPT_EFFECT &&
        spellInfo->Effects[index].Effect != SPELL_EFFECT_CHARGE &&
        spellInfo->IsPositive() && spellInfo->Effects[index].TargetA.GetTarget() != TARGET_UNIT_CASTER &&
        spellInfo->Effects[index].TargetA.GetCheckType() != TARGET_CHECK_ENTRY && spellInfo->Id != 55277 && spellInfo->Id != 6277)
        return true;

    switch (spellInfo->Effects[index].ApplyAuraName)
    {
        // i think its wrong (xinef)
        //case SPELL_AURA_PERIODIC_LEECH:
        case SPELL_AURA_PERIODIC_DAMAGE:
        case SPELL_AURA_PERIODIC_DAMAGE_PERCENT:
        case SPELL_AURA_MOD_FEAR:
        case SPELL_AURA_TRANSFORM:
            return true;
        default:
            break;
    }

    return Creature::IsImmunedToSpellEffect(spellInfo, index);
}
