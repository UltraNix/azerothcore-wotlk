#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "blackwing_lair.h"

enum Spells
{
    SPELL_THRASH            = 3391,
    SPELL_SHADOWFLAME       = 22539,
    SPELL_WINGBUFFET        = 23339,
    SPELL_FLAMEBUFFET       = 23341
};

enum Events
{
    EVENT_SHADOWFLAME       = 1,
    EVENT_WINGBUFFET,
    EVENT_FLAMEBUFFET,
    EVENT_THRASH
};

struct boss_firemawAI : public BossAI
{
    boss_firemawAI(Creature* creature) : BossAI(creature, BOSS_FIREMAW) { }

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
        events.ScheduleEvent(EVENT_FLAMEBUFFET, 5000);
        events.ScheduleEvent(EVENT_THRASH, 5000);
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
                if (DoGetThreat(me->GetVictim()))
                    DoModifyThreatPercent(me->GetVictim(), -75);
                events.ScheduleEvent(EVENT_WINGBUFFET, 30000);
                break;
            case EVENT_FLAMEBUFFET:
                DoCastVictim(SPELL_FLAMEBUFFET);
                events.ScheduleEvent(EVENT_FLAMEBUFFET, 5000);
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

void AddSC_boss_firemaw()
{
    new CreatureAILoader<boss_firemawAI>("boss_firemaw");
}
