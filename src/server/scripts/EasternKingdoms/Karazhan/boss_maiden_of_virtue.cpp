/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"

enum MaidenSpells
{
    SPELL_REPENTANCE    = 29511,
    SPELL_HOLY_FIRE     = 29522,
    SPELL_HOLY_WRATH    = 32445,
    SPELL_HOLY_GROUND   = 29523,
    SPELL_BERSERK       = 26662
};

enum MaidenYells
{
    SAY_AGGRO,
    SAY_SLAY,
    SAY_REPENTANCE,
    SAY_DEATH
};

enum MaidenEvents
{
    EVENT_REPENTANCE    = 1,
    EVENT_HOLY_FIRE,
    EVENT_HOLY_WRATH,
    EVENT_ENRAGE,
    EVENT_KILL_TALK
};

struct boss_maiden_of_virtueAI : public BossAI
{
    boss_maiden_of_virtueAI(Creature* creature) : BossAI(creature, BOSS_MAIDEN) { }

    void EnterEvadeMode() override
    {
        me->RemoveAurasDueToSpell(SPELL_HOLY_GROUND);
        BossAI::EnterEvadeMode();
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        _JustDied();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);

        DoCastSelf(SPELL_HOLY_GROUND, true);
        events.ScheduleEvent(EVENT_REPENTANCE, 33s, 45s);
        events.ScheduleEvent(EVENT_HOLY_FIRE, 1s);
        events.ScheduleEvent(EVENT_HOLY_WRATH, 15s, 25s);
        events.ScheduleEvent(EVENT_ENRAGE, 10min);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_REPENTANCE:
                DoCastVictim(SPELL_REPENTANCE);
                Talk(SAY_REPENTANCE);
                events.Repeat(35s);
                break;
            case EVENT_HOLY_FIRE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_HOLY_FIRE);
                events.Repeat(8s, 19s);
                break;
            case EVENT_HOLY_WRATH:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 80.0f, true))
                    DoCast(target, SPELL_HOLY_WRATH);
                events.Repeat(15s, 25s);
                break;
            case EVENT_ENRAGE:
                DoCastSelf(SPELL_BERSERK, true);
                break;
            default:
                break;
        }
    }
};

void AddSC_boss_maiden_of_virtue()
{
    new CreatureAILoader<boss_maiden_of_virtueAI>("boss_maiden_of_virtue");
}
