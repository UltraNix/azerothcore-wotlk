/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "karazhan.h"
#include "ScriptedCreature.h"

enum CuratorSays
{
    SAY_AGGRO,
    SAY_SUMMON,
    SAY_EVOCATE,
    SAY_ENRAGE,
    SAY_KILL,
    SAY_DEATH
};

enum CuratorSpells
{
    SPELL_HATEFUL_BOLT              = 30383,
    SPELL_EVOCATION                 = 30254,
    SPELL_ARCANE_INFUSION           = 30403,
    SPELL_ASTRAL_DECONSTRUCTION     = 30407,
    SPELL_SUMMON_FLARE_FRONT_RIGHT  = 30236,
    SPELL_SUMMON_FLARE_FRONT_LEFT   = 30239,
    SPELL_SUMMON_FLARE_BACK_RIGHT   = 30240,
    SPELL_SUMMON_FLARE_BACK_LEFT    = 30241,
    SPELL_FLARE_AGGRO               = 29856
};

enum CuratorEvents
{
    EVENT_KILL_TALK                 = 1,
    EVENT_HATEFUL_BOLT,
    EVENT_EVOCATION,
    EVENT_ASTRAL_FLARE,
    EVENT_BERSERK
};

struct boss_curatorAI : public BossAI
{
    boss_curatorAI(Creature* creature) : BossAI(creature, BOSS_CURATOR), _enraged(false) { }

    void Reset() override
    {
        _Reset();
        me->RemoveAurasDueToSpell(SPELL_ARCANE_INFUSION);
        _enraged = false;
        me->ApplySpellImmune(0, IMMUNITY_DAMAGE, SPELL_SCHOOL_MASK_ARCANE, true);
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_PERIODIC_MANA_LEECH, true);
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_POWER_BURN, true);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_KILL);
            events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        events.ScheduleEvent(EVENT_HATEFUL_BOLT, 10s);
        events.ScheduleEvent(EVENT_ASTRAL_FLARE, 6s);
        events.ScheduleEvent(EVENT_BERSERK, 10min);
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (!_enraged && me->HealthBelowPctDamaged(15, damage))
        {
            _enraged = true;
            events.CancelEvent(EVENT_ASTRAL_FLARE);
            DoCastSelf(SPELL_ARCANE_INFUSION, true);
            Talk(SAY_ENRAGE);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->IsAIEnabled)
            summon->AI()->DoCastSelf(SPELL_FLARE_AGGRO);

        if (urand(0, 1))
            Talk(SAY_SUMMON);

        BossAI::JustSummoned(summon);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_BERSERK:
                Talk(SAY_ENRAGE);
                me->InterruptNonMeleeSpells(true);
                DoCastSelf(SPELL_ASTRAL_DECONSTRUCTION, true);
                break;
            case EVENT_HATEFUL_BOLT:
                if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 1, 40.0f))
                    DoCast(target, SPELL_HATEFUL_BOLT);
                if (!events.GetNextEventTime(EVENT_BERSERK))
                    events.Repeat(5.0s, 7.5s);
                else
                    events.Repeat(10s, 15s);
                break;
            case EVENT_ASTRAL_FLARE:
                DoCastSelf(RAND(SPELL_SUMMON_FLARE_BACK_LEFT, SPELL_SUMMON_FLARE_BACK_RIGHT, SPELL_SUMMON_FLARE_FRONT_LEFT, SPELL_SUMMON_FLARE_FRONT_RIGHT), true);
                me->ModifyPowerPct(POWER_MANA, -10.0f);
                if (me->GetPowerPct(POWER_MANA) < 10.0f)
                    events.ScheduleEvent(EVENT_EVOCATION, 0s);
                else
                    events.Repeat(10s);
                break;
            case EVENT_EVOCATION:
                Talk(SAY_EVOCATE);
                DoCastSelf(SPELL_EVOCATION);
                events.DelayEvents(20s);
                events.ScheduleEvent(EVENT_ASTRAL_FLARE, 20s);
                break;
            default:
                break;
        }
    }

    private:
        bool _enraged;
};

// 29856 - Astral Flare
class spell_curator_aggro_flare_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_curator_aggro_flare_SpellScript);

    bool Load() override
    {
        return GetCaster()->IsCreature();
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, [](WorldObject* target) { return target->IsPlayer(); }, 1);
    }

    void OnDummyEffect(SpellEffIndex /*effIndex*/)
    {
        if (Player* target = GetHitPlayer())
        {
            GetCaster()->AddThreat(target, 1000.0f, SPELL_SCHOOL_MASK_ARCANE);
            GetCaster()->GetMotionMaster()->MoveFollow(target, GetCaster()->GetCombatReach(), 0.0f);
        }
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_curator_aggro_flare_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_curator_aggro_flare_SpellScript::OnDummyEffect, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_curator()
{
    new CreatureAILoader<boss_curatorAI>("boss_curator");
    new SpellScriptLoaderEx<spell_curator_aggro_flare_SpellScript>("spell_curator_aggro_flare");
}
