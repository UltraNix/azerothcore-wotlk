#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"

enum GreenskinSpells
{
    SPELL_CLEAVE            = 15284,
    SPELL_POISONED_HARPOON  = 5208
};

struct boss_captain_greenskinAI : public BossAI
{
    boss_captain_greenskinAI(Creature* creature) : BossAI(creature, BOSS_CAPTAIN_GREENSKIN) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        scheduler.Schedule(1s, 7s, [this](TaskContext task) 
        {
            DoCastVictim(SPELL_CLEAVE);
            task.Repeat(10s, 15s);
        });
        scheduler.Schedule(10s, 12s, [this](TaskContext task) 
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0f, true, -SPELL_POISONED_HARPOON))
                DoCast(target, SPELL_POISONED_HARPOON);
            task.Repeat(25s, 35s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }
};

void AddSC_boss_captain_greenskin()
{
    new CreatureAILoader<boss_captain_greenskinAI>("boss_captain_greenskin");
}