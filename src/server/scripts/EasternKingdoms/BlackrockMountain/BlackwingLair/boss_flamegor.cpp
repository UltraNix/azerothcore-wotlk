#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "blackwing_lair.h"

enum Emotes
{
    EMOTE_FRENZY            = 0,
};

enum Spells
{
    SPELL_THRASH             = 3391,
    SPELL_SHADOWFLAME        = 22539,
    SPELL_WINGBUFFET         = 23339,
    SPELL_FRENZY             = 23342  //This spell periodically triggers fire nova
};

enum Events
{
    EVENT_SHADOWFLAME        = 1,
    EVENT_WINGBUFFET,
    EVENT_FRENZY,
    EVENT_THRASH
};

class boss_flamegor : public CreatureScript
{
    public:
        boss_flamegor() : CreatureScript("boss_flamegor") { }

        struct boss_flamegorAI : public BossAI
        {
            boss_flamegorAI(Creature* creature) : BossAI(creature, BOSS_FLAMEGOR) { }

            void EnterCombat(Unit* /*who*/)
            {
                if (instance->GetBossState(BOSS_BROODLORD) != DONE)
                {
                    EnterEvadeMode();
                    return;
                }
                _EnterCombat();

                events.ScheduleEvent(EVENT_SHADOWFLAME, urand(10000, 20000));
                events.ScheduleEvent(EVENT_WINGBUFFET, 30000);
                events.ScheduleEvent(EVENT_FRENZY, 10000);
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
                    case EVENT_FRENZY:
                        Talk(EMOTE_FRENZY);
                        DoCast(me, SPELL_FRENZY);
                        events.ScheduleEvent(EVENT_FRENZY, urand(8000, 10000));
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

        CreatureAI* GetAI(Creature* creature) const
        {
            return GetInstanceAI<boss_flamegorAI>(creature);
        }
};

void AddSC_boss_flamegor()
{
    new boss_flamegor();
}
