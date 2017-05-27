#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Spells
{
    SPELL_GEHENNAS_CURSE        = 19716,
    SPELL_RAIN_OF_FIRE          = 19717,
    SPELL_SHADOW_BOLT           = 19728,
};

enum Events
{
    EVENT_GEHENNAS_CURSE        = 1,
    EVENT_RAIN_OF_FIRE,
    EVENT_SHADOW_BOLT_RANDOM,
    EVENT_SHADOW_BOLT_VICTIM
};

class boss_gehennas : public CreatureScript
{
    public:
        boss_gehennas() : CreatureScript("boss_gehennas") { }

        struct boss_gehennasAI : public BossAI
        {
            boss_gehennasAI(Creature* creature) : BossAI(creature, BOSS_GEHENNAS) { }

            void EnterCombat(Unit* /*victim*/)
            {
                _EnterCombat();
                events.ScheduleEvent(EVENT_GEHENNAS_CURSE, urand(5000, 10000));
                events.ScheduleEvent(EVENT_RAIN_OF_FIRE, urand(6000, 12000));
                events.ScheduleEvent(EVENT_SHADOW_BOLT_RANDOM, urand(3000, 6000));
                events.ScheduleEvent(EVENT_SHADOW_BOLT_VICTIM, urand(3000, 6000));
            }

            void EnterEvadeMode() override
            {
                std::list<Creature*> addList;
                me->GetCreatureListWithEntryInGrid(addList, 11661, 100.0f);
                if (!addList.empty())
                {
                    for (auto itr : addList)
                    {
                        if (!itr->IsAlive())
                            itr->Respawn();
                        if (itr->IsAIEnabled)
                            itr->AI()->EnterEvadeMode();
                    }
                }
                CreatureAI::EnterEvadeMode();
            }

            void ExecuteEvent(uint32 eventId) override
            {
                switch (eventId)
                {
                    case EVENT_GEHENNAS_CURSE:
                        DoCastVictim(SPELL_GEHENNAS_CURSE);
                        events.ScheduleEvent(EVENT_GEHENNAS_CURSE, urand(25000, 30000));
                        break;
                    case EVENT_RAIN_OF_FIRE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                            DoCast(target, SPELL_RAIN_OF_FIRE);
                        events.ScheduleEvent(EVENT_RAIN_OF_FIRE, urand(6000, 12000));
                        break;
                    case EVENT_SHADOW_BOLT_RANDOM:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                            DoCast(target, SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT_RANDOM, urand(3000, 6000));
                        break;
                    case EVENT_SHADOW_BOLT_VICTIM:
                        DoCastVictim(SPELL_SHADOW_BOLT);
                        events.ScheduleEvent(EVENT_SHADOW_BOLT_VICTIM, urand(3000, 6000));
                    default:
                        break;
                }
            }
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return new boss_gehennasAI(creature);
        }
};

void AddSC_boss_gehennas()
{
    new boss_gehennas();
}
