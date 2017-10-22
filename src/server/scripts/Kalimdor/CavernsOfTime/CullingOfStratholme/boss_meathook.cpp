#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "culling_of_stratholme.h"

enum MeathookSpells
{
    SPELL_CONSTRICTING_CHAINS   = 52696,
    SPELL_DISEASE_EXPULSION     = 52666,
    SPELL_FRENZY                = 58841
};

enum MeathookEvents
{
    EVENT_CONSTRICTING_CHAINS   = 1,
    EVENT_DISEASE_EXPULSION,
    EVENT_FRENZY,
    EVENT_KILL_TALK
};

enum MeathookYells
{
    SAY_AGGRO,
    SAY_SLAY,
    SAY_SPAWN,
    SAY_DEATH
};

struct boss_meathookAI : public BossAI
{
    boss_meathookAI(Creature* creature) : BossAI(creature, DATA_MEATHOOK)
    {
        Talk(SAY_SPAWN);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        _EnterCombat();
        events.RescheduleEvent(EVENT_CONSTRICTING_CHAINS, urand(7000, 11000));
        events.RescheduleEvent(EVENT_DISEASE_EXPULSION, 2000);
        events.RescheduleEvent(EVENT_FRENZY, urand(13000, 17000));
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY);
            events.ScheduleEvent(EVENT_KILL_TALK, 6000);
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CONSTRICTING_CHAINS:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, -20.0f, true))
                    DoCast(target, SPELL_CONSTRICTING_CHAINS);
                else if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 100.0f, true))
                    DoCast(target, SPELL_CONSTRICTING_CHAINS);
                else
                    DoCastVictim(SPELL_CONSTRICTING_CHAINS);
                events.Repeat(urand(10000, 15000));
                break;
            case EVENT_DISEASE_EXPULSION:
                DoCastAOE(SPELL_DISEASE_EXPULSION);
                events.Repeat(3500);
                break;
            case EVENT_FRENZY:
                DoCastSelf(SPELL_FRENZY);
                events.Repeat(urand(13000, 17000));
                break;
            default:
                break;
        }
    }
};

void AddSC_boss_meathook()
{
    new CreatureAILoader<boss_meathookAI>("boss_meathook");
}
