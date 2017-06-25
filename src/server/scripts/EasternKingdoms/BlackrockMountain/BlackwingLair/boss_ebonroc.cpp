#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "blackwing_lair.h"

enum Spells
{
    SPELL_THRASH                = 3391,
    SPELL_SHADOWFLAME           = 22539,
    SPELL_WINGBUFFET            = 23339,
    SPELL_SHADOWOFEBONROC       = 23340
};

enum Events
{
    EVENT_SHADOWFLAME           = 1,
    EVENT_WINGBUFFET,
    EVENT_SHADOWOFEBONROC,
    EVENT_THRASH
};

struct boss_ebonrocAI : public BossAI
{
    boss_ebonrocAI(Creature* creature) : BossAI(creature, BOSS_EBONROC) { }

    void EnterCombat(Unit* /*who*/) override
    {
        if (instance->GetBossState(BOSS_BROODLORD) != DONE)
        {
            EnterEvadeMode();
            return;
        }
        _EnterCombat();

        events.ScheduleEvent(EVENT_SHADOWFLAME, urand(10000, 20000));
        events.ScheduleEvent(EVENT_WINGBUFFET, 30000);
        events.ScheduleEvent(EVENT_SHADOWOFEBONROC, urand(8000, 10000));
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SHADOWFLAME:
                DoCastVictim(SPELL_SHADOWFLAME);
                events.ScheduleEvent(EVENT_SHADOWFLAME, urand(10000, 20000));
                break;
            case EVENT_WINGBUFFET:
                DoCastVictim(SPELL_WINGBUFFET);
                events.ScheduleEvent(EVENT_WINGBUFFET, 30000);
                break;
            case EVENT_SHADOWOFEBONROC:
                DoCastVictim(SPELL_SHADOWOFEBONROC);
                events.ScheduleEvent(EVENT_SHADOWOFEBONROC, urand(8000, 10000));
                break;
            case EVENT_THRASH:
                DoCast(me, SPELL_THRASH);
                events.ScheduleEvent(EVENT_THRASH, 18000);
                break;
            default:
                break;
        }
    }
};

void AddSC_boss_ebonroc()
{
    new CreatureAILoader<boss_ebonrocAI>("boss_ebonroc");
}
