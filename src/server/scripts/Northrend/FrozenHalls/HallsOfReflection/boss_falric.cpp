#include "ScriptPCH.h"
#include "halls_of_reflection.h"

enum FalricYells
{
    SAY_AGGRO               = 50,
    SAY_SLAY_1              = 51,
    SAY_SLAY_2              = 52,
    SAY_DEATH               = 53,
    SAY_IMPENDING_DESPAIR   = 54,
    SAY_DEFILING_HORROR     = 55
};

enum FalricSpells
{
    SPELL_QUIVERING_STRIKE  = 72422,
    SPELL_IMPENDING_DESPAIR = 72426,
    SPELL_DEFILING_HORROR   = 72435,
};

enum FalricEvents
{
    EVENT_AGGRO             = 1,
    EVENT_QUIVERING_STRIKE,
    EVENT_IMPENDING_DESPAIR,
    EVENT_DEFILING_HORROR,
    EVENT_UNROOT,
    EVENT_KILL_TALK
};

struct boss_falricAI : public BossAI
{
    boss_falricAI(Creature* creature) : BossAI(creature, DATA_FALRIC) { }

    void Reset() override
    {
        _hopelessnessCount = 0;
        me->SetAttackable(false);
        me->SetControlled(false, UNIT_STATE_ROOT);
        _Reset();
        instance->SetData(DATA_FALRIC, NOT_STARTED);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        me->SetAttackable(true);
        events.ScheduleEvent(EVENT_QUIVERING_STRIKE, 5s);
        events.ScheduleEvent(EVENT_IMPENDING_DESPAIR, 11s);
        events.ScheduleEvent(EVENT_DEFILING_HORROR, 20s);
        _EnterCombat();
    }

    void DoAction(int32 actionId) override
    {
        if (actionId != 1)
            return;

        Talk(SAY_AGGRO);
        _events.ScheduleEvent(EVENT_AGGRO, 8s);
    }

    uint32 GetHopelessnessID(uint32 count) const
    {
        switch (count)
        {
            case 0:
                return IsHeroic() ? 72390 : 72395;
            case 1:
                return IsHeroic() ? 72391 : 72396;
            case 2:
                return IsHeroic() ? 72393 : 72397;
        }

        return 0;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        if (me->HealthBelowPctDamaged(100 - 25 * (_hopelessnessCount + 1), damage))
        {
            uint32 spellId = GetHopelessnessID(_hopelessnessCount);
            if (_hopelessnessCount)
                me->RemoveOwnedAura(GetHopelessnessID(_hopelessnessCount - 1));
            DoCastAOE(spellId, true);
            ++_hopelessnessCount;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_AGGRO)
            me->SetInCombatWithZone();

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_AGGRO:
                    me->SetInCombatWithZone();
                    break;
                case EVENT_QUIVERING_STRIKE:
                    DoCastVictim(SPELL_QUIVERING_STRIKE);
                    events.Repeat(5s);
                    break;
                case EVENT_IMPENDING_DESPAIR:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                    {
                        Talk(SAY_IMPENDING_DESPAIR);
                        DoCast(target, SPELL_IMPENDING_DESPAIR);
                    }
                    events.Repeat(12s);
                    break;
                case EVENT_DEFILING_HORROR:
                    Talk(SAY_DEFILING_HORROR);
                    DoCastAOE(SPELL_DEFILING_HORROR);
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    events.DelayEventsToMax(5000, 1);
                    events.ScheduleEvent(EVENT_UNROOT, 4s);
                    events.Repeat(20s);
                    break;
                case EVENT_UNROOT:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        if (!me->HasUnitState(UNIT_STATE_ROOT))
            DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        _JustDied();
        instance->SetData(DATA_FALRIC, DONE);
    }

    void KilledUnit(Unit* /*who*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(RAND(SAY_SLAY_1, SAY_SLAY_2));
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void EnterEvadeMode() override
    {
        me->SetControlled(false, UNIT_STATE_ROOT);
        ScriptedAI::EnterEvadeMode();
        if (_events.GetTimeUntilEvent(EVENT_AGGRO))
            Reset();
    }

    private:
        EventMap _events;
        uint8 _hopelessnessCount;
};

void AddSC_boss_falric()
{
    new CreatureAILoader<boss_falricAI>("boss_falric");
}