
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "blackwing_lair.h"

enum Say
{
    SAY_AGGRO,
    SAY_LEASH
};

enum Spells
{
    SPELL_CLEAVE            = 26350,
    SPELL_BLASTWAVE         = 23331,
    SPELL_MORTALSTRIKE      = 24573,
    SPELL_KNOCKBACK         = 25778
};

enum Events
{
    EVENT_CLEAVE            = 1,
    EVENT_BLASTWAVE,
    EVENT_MORTALSTRIKE,
    EVENT_KNOCKBACK,
    EVENT_CHECK
};

struct boss_broodlordAI : public BossAI
{
    boss_broodlordAI(Creature* creature) : BossAI(creature, BOSS_BROODLORD) { }

    void EnterCombat(Unit* /*who*/) override
    {
        if (instance->GetBossState(BOSS_VAELASTRAZ) != DONE)
        {
            EnterEvadeMode();
            return;
        }

        _EnterCombat();
        Talk(SAY_AGGRO);

        events.ScheduleEvent(EVENT_CLEAVE, 8000);
        events.ScheduleEvent(EVENT_BLASTWAVE, 12000);
        events.ScheduleEvent(EVENT_MORTALSTRIKE, 20000);
        events.ScheduleEvent(EVENT_KNOCKBACK, 30000);
        events.ScheduleEvent(EVENT_CHECK, 1000);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CLEAVE:
                DoCastVictim(SPELL_CLEAVE);
                events.ScheduleEvent(EVENT_CLEAVE, 7000);
                break;
            case EVENT_BLASTWAVE:
                DoCastVictim(SPELL_BLASTWAVE);
                events.ScheduleEvent(EVENT_BLASTWAVE, urand(8000, 16000));
                break;
            case EVENT_MORTALSTRIKE:
                DoCastVictim(SPELL_MORTALSTRIKE);
                events.ScheduleEvent(EVENT_MORTALSTRIKE, urand(25000, 35000));
                break;
            case EVENT_KNOCKBACK:
                DoCastVictim(SPELL_KNOCKBACK);
                if (DoGetThreat(me->GetVictim()))
                    DoModifyThreatPercent(me->GetVictim(), -50);
                events.ScheduleEvent(EVENT_KNOCKBACK, urand(15000, 30000));
                break;
            case EVENT_CHECK:
                if (me->GetDistance(me->GetHomePosition()) > 150.0f)
                {
                    Talk(SAY_LEASH);
                    EnterEvadeMode();
                }
                events.ScheduleEvent(EVENT_CHECK, 1000);
                break;
        }
    }
};

void AddSC_boss_broodlord()
{
    new CreatureAILoader<boss_broodlordAI>("boss_broodlord");
}
