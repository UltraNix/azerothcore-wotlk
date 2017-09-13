#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "trial_of_the_crusader.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "GridNotifiers.h"

enum JaraxxusTexts
{
    SAY_INTRO,
    SAY_AGGRO,
    EMOTE_LEGION_FLAME,
    EMOTE_NETHER_PORTAL,
    SAY_MISTRESS_OF_PAIN,
    EMOTE_INCINERATE,
    SAY_INCINERATE,
    EMOTE_INFERNAL_ERUPTION,
    SAY_INFERNAL_ERUPTION,
    SAY_KILL_PLAYER,
    SAY_DEATH,
    SAY_BERSERK
};

enum JaraxxusNPCs
{
    NPC_LEGION_FLAME = 34784,
    NPC_INFERNAL_VOLCANO = 34813,
    NPC_FEL_INFERNAL = 34815,
    NPC_NETHER_PORTAL = 34825,
    NPC_MISTRESS_OF_PAIN = 34826,
};

enum JaraxxusSpells
{
    SPELL_NETHER_POWER = 66228,
    SPELL_INCINERATE_FLESH = 66237,
    SPELL_FEL_FIREBALL = 66532,
    SPELL_FEL_LIGHTNING = 66528,
    SPELL_TOUCH_OF_JARAXXUS = 66209,
    SPELL_LEGION_FLAME = 66197,
    SPELL_LEGION_FLAME_NPC_AURA = 66201,
    SPELL_SUMMON_VOLCANO = 66258,
    SPELL_SUMMON_NETHER_PORTAL = 66269,

    SPELL_FEL_STEAK = 66494,
    SPELL_FEL_STEAK_MORPH = 66493,

    SPELL_SHIVAN_SLASH = 66378,
    SPELL_SPINNING_PAIN_SPIKE = 66283,
    SPELL_MISTRESS_KISS = 66336,
    SPELL_MISTRESS_KISS_PERIODIC_DUMMY = 66334, // also 67905, 67906, 67907
    SPELL_MISTRESS_KISS_INTERRUPT = 66359,

    SPELL_CHAINS = 67924,
    SPELL_BERSERK = 64238
};

enum JaraxxusEvents
{
    EVENT_SPELL_FEL_FIREBALL = 1,
    EVENT_SPELL_FEL_LIGHTNING,
    EVENT_SPELL_INCINERATE_FLESH,
    EVENT_SPELL_NETHER_POWER,
    EVENT_SPELL_LEGION_FLAME,
    EVENT_SPELL_TOUCH_OF_JARAXXUS,
    EVENT_SUMMON_VOLCANO,
    EVENT_SUMMON_NETHER_PORTAL,

    EVENT_SPELL_FEL_STEAK,

    EVENT_SPELL_SHIVAN_SLASH,
    EVENT_SPELL_SPINNING_PAIN_SPIKE,
    EVENT_SPELL_MISTRESS_KISS,
};

struct boss_jaraxxusAI : public BossAI
{
    boss_jaraxxusAI(Creature* creature) : BossAI(creature, TYPE_JARAXXUS)
    {
        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
        me->SetReactState(REACT_PASSIVE);
    }

    void Reset() override
    {
        _Reset();
        instance->SetData(TYPE_JARAXXUS, NOT_STARTED);

        // checked for safety
        while (Creature* c = me->FindNearestCreature(NPC_INFERNAL_VOLCANO, 500.0f, true))
            c->DespawnOrUnsummon();
        while (Creature* c = me->FindNearestCreature(NPC_NETHER_PORTAL, 500.0f, true))
            c->DespawnOrUnsummon();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        events.Reset();
        events.RescheduleEvent(EVENT_SPELL_FEL_FIREBALL, 5000);
        events.RescheduleEvent(EVENT_SPELL_FEL_LIGHTNING, urand(10000, 15000));
        events.RescheduleEvent(EVENT_SPELL_INCINERATE_FLESH, urand(24000, 26000));
        events.RescheduleEvent(EVENT_SPELL_NETHER_POWER, urand(25000, 45000));
        events.RescheduleEvent(EVENT_SPELL_LEGION_FLAME, 30000);
        events.RescheduleEvent(EVENT_SUMMON_NETHER_PORTAL, 20000); // it schedules EVENT_SUMMON_VOLCANO

        Talk(SAY_AGGRO);
        instance->SetData(TYPE_JARAXXUS, IN_PROGRESS);
    }

    void SpellHit(Unit* caster, const SpellInfo* spell) override
    {
        switch (spell->Id)
        {
        case 66228:
        case 67106:
        case 67107:
        case 67108:
            if (Aura* a = me->GetAura(spell->Id))
                a->SetStackAmount(spell->StackAmount);
            break;
        case 30449:
        {
            if (!caster)
                return;
            uint32 id = 0;
            switch (me->GetMap()->GetDifficulty())
            {
            case 0: id = 66228; break;
            case 1: id = 67106; break;
            case 2: id = 67107; break;
            case 3: id = 67108; break;
            }
            if (Aura* a = me->GetAura(id))
            {
                if (a->GetStackAmount() > 1)
                    a->ModStackAmount(-1);
                else
                    a->Remove();
                caster->CastSpell(caster, SPELL_NETHER_POWER, true);
            }
        }
        break;
        default:
            break;
        }
    }

    void HandleSpawnLOS(uint32 summonId) const
    {
        if (Unit* summon = me->FindNearestCreature(summonId, 250.0f))
            if (!summon->IsWithinLOSInMap(me))
                summon->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case EVENT_SPELL_FEL_FIREBALL:
            DoCastVictim(SPELL_FEL_FIREBALL);
            events.Repeat(urand(10000, 15000));
            break;
        case EVENT_SPELL_FEL_LIGHTNING:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                DoCast(target, SPELL_FEL_LIGHTNING);
            events.Repeat(urand(10000, 15000));
            break;
        case EVENT_SPELL_INCINERATE_FLESH:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
            {
                Talk(EMOTE_INCINERATE, target);
                Talk(SAY_INCINERATE);
                DoCast(target, SPELL_INCINERATE_FLESH);
            }
            events.Repeat(urand(20000, 25000));
            break;
        case EVENT_SPELL_NETHER_POWER:
            DoCastSelf(SPELL_NETHER_POWER);
            events.DelayEvents(5000);
            events.Repeat(urand(25000, 45000));
            break;
        case EVENT_SPELL_LEGION_FLAME:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.0f, true))
            {
                Talk(EMOTE_LEGION_FLAME, target);
                DoCast(target, SPELL_LEGION_FLAME);
            }
            events.Repeat(30000);
            break;
        case EVENT_SPELL_TOUCH_OF_JARAXXUS:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                DoCast(target, SPELL_TOUCH_OF_JARAXXUS);
            events.Repeat(urand(10000, 15000));
            break;
        case EVENT_SUMMON_NETHER_PORTAL:
            Talk(EMOTE_NETHER_PORTAL);
            Talk(SAY_MISTRESS_OF_PAIN);
            DoCastAOE(SPELL_SUMMON_NETHER_PORTAL);
            HandleSpawnLOS(34825);
            events.RescheduleEvent(EVENT_SUMMON_VOLCANO, 60000);
            break;
        case EVENT_SUMMON_VOLCANO:
            Talk(EMOTE_INFERNAL_ERUPTION);
            Talk(SAY_INFERNAL_ERUPTION);
            DoCastAOE(SPELL_SUMMON_VOLCANO);
            HandleSpawnLOS(34813);
            events.RescheduleEvent(EVENT_SUMMON_NETHER_PORTAL, 60000);
            break;
        default:
            break;
        }
    }

    void JustDied(Unit* /*killer*/)
    {
        std::list<Creature*> flameList;
        me->GetCreatureListWithEntryInGrid(flameList, NPC_LEGION_FLAME, 250.0f);
        me->GetCreatureListWithEntryInGrid(flameList, NPC_INFERNAL_VOLCANO, 250.0f);
        me->GetCreatureListWithEntryInGrid(flameList, NPC_NETHER_PORTAL, 250.0f);
        me->GetCreatureListWithEntryInGrid(flameList, NPC_FEL_INFERNAL, 250.0f);
        me->GetCreatureListWithEntryInGrid(flameList, NPC_MISTRESS_OF_PAIN, 250.0f);

        if (!flameList.empty())
            for (auto itr : flameList)
                itr->DespawnOrUnsummon();

        _JustDied();
        Talk(SAY_DEATH);
        instance->SetData(TYPE_JARAXXUS, DONE);
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_LEGION_FLAME);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void EnterEvadeMode() override
    {
        events.Reset();
        summons.DespawnAll();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        instance->SetData(TYPE_FAILED, 1);
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}
};

struct npc_fel_infernalAI : public ScriptedAI
{
    npc_fel_infernalAI(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        if (IsHeroic() && Is25ManRaid())
        {
            me->SetMaxHealth(519000);
            me->SetFullHealth();
        }

        if (Unit* target = me->SelectNearestTarget(200.0f))
        {
            AttackStart(target);
            DoZoneInCombat();
        }

        _events.Reset();
        _events.RescheduleEvent(EVENT_SPELL_FEL_STEAK, urand(7000, 20000));
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SPELL_FEL_STEAK:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 44.0f, true))
                {
                    DoResetThreat();
                    me->AddThreat(target, 50000.0f);
                    DoCast(target, SPELL_FEL_STEAK_MORPH, true);
                    DoCast(target, SPELL_FEL_STEAK, true);
                    _events.Repeat(30000);
                }
                else
                    _events.Repeat(5000);
                break;
            default:
                break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(10000);
    }

    void EnterEvadeMode() override
    {
        me->DespawnOrUnsummon();
    }

private:
    EventMap _events;
};

struct npc_mistress_of_painAI : public ScriptedAI
{
    npc_mistress_of_painAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    void Reset() override
    {
        if (Unit* target = me->SelectNearestTarget(200.0f))
        {
            AttackStart(target);
            DoZoneInCombat();
        }
        _events.Reset();
        _events.RescheduleEvent(EVENT_SPELL_SHIVAN_SLASH, urand(10000, 20000));
        _events.RescheduleEvent(EVENT_SPELL_SPINNING_PAIN_SPIKE, urand(22000, 30000));
        if (IsHeroic())
            _events.RescheduleEvent(EVENT_SPELL_MISTRESS_KISS, urand(10000, 15000));
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SPELL_SHIVAN_SLASH:
                DoCastVictim(SPELL_SHIVAN_SLASH);
                _events.Repeat(urand(15000, 25000));
                break;
            case EVENT_SPELL_SPINNING_PAIN_SPIKE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 140.0f, true))
                    DoCast(target, SPELL_SPINNING_PAIN_SPIKE);
                _events.Repeat(urand(25000, 30000));
                break;
            case EVENT_SPELL_MISTRESS_KISS:
                DoCastAOE(SPELL_MISTRESS_KISS);
                _events.Repeat(urand(25000, 35000));
                break;
            default:
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(10000);
    }

    void EnterEvadeMode() override
    {
        me->DespawnOrUnsummon();
    }

private:
    EventMap _events;
};

class spell_toc25_mistress_kiss_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_toc25_mistress_kiss_AuraScript)

        bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MISTRESS_KISS, SPELL_MISTRESS_KISS_INTERRUPT, SPELL_MISTRESS_KISS_PERIODIC_DUMMY });
    }

    void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetTarget())
                if (target->HasUnitState(UNIT_STATE_CASTING))
                {
                    caster->CastSpell(target, 66359, true);
                    SetDuration(0);
                }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_toc25_mistress_kiss_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_mistress_kiss_area_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_mistress_kiss_area_SpellScript)

        void FilterTargets(std::list<WorldObject*>& targets)
    {
        auto is25ManRaid = false;
        auto caster = GetCaster();
        if (auto map = caster->GetMap())
            if (map->Is25ManRaid())
                is25ManRaid = true;

        // get a list of players with mana
        targets.remove_if(Trinity::ObjectTypeIdCheck(TYPEID_PLAYER, false));
        targets.remove_if(Trinity::PowerCheck(POWER_MANA, false));
        targets.remove_if(Trinity::UnitAuraCheck(true, SPELL_MISTRESS_KISS));

        if (targets.empty())
            return;

        Trinity::Containers::RandomResizeList(targets, is25ManRaid ? 5 : 1);
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetHitUnit(), uint32(GetEffectValue()), true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mistress_kiss_area_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_mistress_kiss_area_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void AddSC_boss_jaraxxus()
{
    new CreatureAILoader<boss_jaraxxusAI>("boss_jaraxxus");
    new CreatureAILoader<npc_fel_infernalAI>("npc_fel_infernal");
    new CreatureAILoader<npc_mistress_of_painAI>("npc_mistress_of_pain");
    new AuraScriptLoaderEx<spell_toc25_mistress_kiss_AuraScript>("spell_toc25_mistress_kiss");
    new SpellScriptLoaderEx<spell_mistress_kiss_area_SpellScript>("spell_mistress_kiss_area");
}
