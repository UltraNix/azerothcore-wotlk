#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"

enum CuratorTexts
{
    SAY_AGGRO,
    SAY_SUMMON,
    SAY_EVOCATE,
    SAY_ENRAGE,
    SAY_KILL,
    SAY_DEATH,
};

enum CuratorSpells
{
    SPELL_HATEFUL_BOLT          = 30383,
    SPELL_EVOCATION             = 30254,
    SPELL_ARCANE_INFUSION       = 30403,
    SPELL_ASTRAL_DECONSTRUCTION = 30407,
};

enum CuratorEvents
{
    EVENT_KILL_TALK             = 1,
    EVENT_HATEFUL_BOLT,
    EVENT_EVOCATION,
    EVENT_ASTRAL_FLARE,
    EVENT_BERSERK
};

struct boss_curatorAI : public BossAI
{
    boss_curatorAI(Creature* creature) : BossAI(creature, TYPE_CURATOR), _enraged(false) { }

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
        summons.Summon(summon);
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f))
        {
            if (summon->IsAIEnabled)
                summon->AI()->AttackStart(target);
            summon->AddThreat(target, 1000.0f);
        }

        summon->SetInCombatWithZone();
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
                Position pos;
                me->GetRandomNearPosition(pos, 10.0f);
                me->SummonCreature(17096, pos);
                me->ModifyPowerPct(POWER_MANA, -10.0f);
                if (me->GetPowerPct(POWER_MANA) < 10.0f)
                {
                    Talk(SAY_EVOCATE);
                    DoCastSelf(SPELL_EVOCATION);
                    events.DelayEvents(20s);
                    events.Repeat(20s);
                }
                else
                {
                    if (urand(0, 1))
                        Talk(SAY_SUMMON);

                    events.Repeat(10s);
                }
                break;
        }
    }

    private:
        bool _enraged;
};

void AddSC_boss_curator()
{
    new CreatureAILoader<boss_curatorAI>("boss_curator");
}
