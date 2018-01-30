#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"

enum GilnidSpells
{
    SPELL_MOLTEN_METAL = 5213
};

enum GilnidSays
{
    SAY_AGGRO,
};

struct boss_gilnidAI : public BossAI
{
    boss_gilnidAI(Creature* creature) : BossAI(creature, BOSS_GILNID) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        scheduler.Schedule(1s, 6s, [this](TaskContext task) 
        {
            DoCastVictim(SPELL_MOLTEN_METAL);
            task.Repeat(15s, 25s);
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

void AddSC_boss_gilnid()
{
    new CreatureAILoader<boss_gilnidAI>("boss_gilnid");
}
