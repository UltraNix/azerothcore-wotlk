#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Spells
{
    SPELL_IMPENDING_DOOM    = 19702,
    SPELL_LUCIFRON_CURSE    = 19703,
    SPELL_SHADOW_SHOCK      = 20603,
};

enum Events
{
    EVENT_IMPENDING_DOOM    = 1,
    EVENT_LUCIFRON_CURSE    = 2,
    EVENT_SHADOW_SHOCK      = 3,
};

struct boss_lucifronAI : public BossAI
{
    boss_lucifronAI(Creature* creature) : BossAI(creature, BOSS_LUCIFRON) { }

    void EnterCombat(Unit* /*victim*/)
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_IMPENDING_DOOM, 10000);
        events.ScheduleEvent(EVENT_LUCIFRON_CURSE, 20000);
        events.ScheduleEvent(EVENT_SHADOW_SHOCK, 6000);
    }

    void EnterEvadeMode() override
    {
        std::list<Creature*> addList;
        me->GetCreatureListWithEntryInGrid(addList, 12119, 100.0f);
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
            case EVENT_IMPENDING_DOOM:
                DoCastVictim(SPELL_IMPENDING_DOOM);
                events.ScheduleEvent(EVENT_IMPENDING_DOOM, 20000);
                break;
            case EVENT_LUCIFRON_CURSE:
                DoCastVictim(SPELL_LUCIFRON_CURSE);
                events.ScheduleEvent(EVENT_LUCIFRON_CURSE, 15000);
                break;
            case EVENT_SHADOW_SHOCK:
                DoCastVictim(SPELL_SHADOW_SHOCK);
                events.ScheduleEvent(EVENT_SHADOW_SHOCK, 6000);
                break;
            default:
                break;
        }
    }
};

void AddSC_boss_lucifron()
{
    new CreatureAILoader<boss_lucifronAI>("boss_lucifron");
}
