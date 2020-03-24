#include "shadowfang_keep.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum RethilgoreSpells
{
    SPELL_SOUL_DRAIN = 7295
};

struct boss_rethilgoreAI : public BossAI
{
    boss_rethilgoreAI(Creature* creature) : BossAI(creature, BOSS_RETHILGORE) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        scheduler.Schedule(1s, 6s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
            {
                DoCast(target, SPELL_SOUL_DRAIN);
                task.Repeat(8s, 12s);
            }
            else
                task.Repeat(2s, 3s);
        });
    }
};

void AddSC_boss_rethilgore()
{
    new CreatureAILoader<boss_rethilgoreAI>("boss_rethilgore");
}
