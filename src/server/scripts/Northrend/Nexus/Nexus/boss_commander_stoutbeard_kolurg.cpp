#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "nexus.h"

enum Spells
{
    SPELL_BATTLE_SHOUT              = 31403,
    SPELL_CHARGE                    = 60067,
    SPELL_FRIGHTENING_SHOUT         = 19134,
    SPELL_WHIRLWIND                 = 38618
};

enum Events
{
    EVENT_BATTLE_SHOUT               = 1,
    EVENT_FRIGHTENING_SHOUT,
    EVENT_WHIRLWIND,
    EVENT_COMMANDER_CHARGE,
};

enum Says
{
    SAY_AGGRO,
    SAY_DEATH,
    SAY_KILL 
};

struct boss_commander_stoutbeardAI : BossAI
{
    explicit boss_commander_stoutbeardAI(Creature* creature) : BossAI(creature, DATA_COMMANDER_EVENT) {}

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
                
        events.ScheduleEvent(EVENT_BATTLE_SHOUT, 0);
        events.ScheduleEvent(EVENT_FRIGHTENING_SHOUT, 10000);
        events.ScheduleEvent(EVENT_WHIRLWIND, 15000);
        events.ScheduleEvent(EVENT_COMMANDER_CHARGE, 1000);
        me->RemoveAllAuras();
    }

    void KilledUnit(Unit* who) override
    {
        if (who->IsPlayer())
            Talk(SAY_KILL);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }
            
    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_BATTLE_SHOUT:
                DoCastSelf(SPELL_BATTLE_SHOUT, true);
                events.ScheduleEvent(EVENT_BATTLE_SHOUT, 120000);
                break;
            case EVENT_FRIGHTENING_SHOUT:
                DoCastAOE(SPELL_FRIGHTENING_SHOUT);
                events.Repeat(urand(15000, 20000));
                break;
            case EVENT_WHIRLWIND:
                DoCastSelf(SPELL_WHIRLWIND);
                events.Repeat(16000);
                break;
            case EVENT_COMMANDER_CHARGE:
                if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 25.0f, true))
                    DoCast(target, SPELL_CHARGE);
                events.Repeat(20000);
                break;
            default:
                break;
        }
    }
};

void AddSC_boss_commander_stoutbeard()
{
    new CreatureAILoader<boss_commander_stoutbeardAI>("boss_commander_stoutbeard");
}
