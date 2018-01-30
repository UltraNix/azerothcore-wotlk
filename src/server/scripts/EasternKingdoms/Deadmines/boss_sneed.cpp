#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"

enum SneedSpells
{
    // Sneed
    SPELL_DISARM            = 6713,

    // Sneed's Shredder
    SPELL_TERRIFY           = 7399,
    SPELL_DISTRACTING_PAIN  = 3603,
    SPELL_EJECT_SNEED       = 5141
};

struct boss_sneedAI : public BossAI
{
    boss_sneedAI(Creature* creature) : BossAI(creature, BOSS_SNEED) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        scheduler.Schedule(1s, 17s, [this](TaskContext task) 
        {
            DoCastVictim(SPELL_DISARM);
            task.Repeat(20s, 25s);
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

struct npc_sneed_shredderAI : public ScriptedAI
{
    npc_sneed_shredderAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(7s, [this](TaskContext task) 
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 5.0f, true, -SPELL_TERRIFY))
                DoCast(target, SPELL_TERRIFY);
            task.Repeat(15s);
        });
        _scheduler.Schedule(4s, [this](TaskContext task) 
        {
            DoCastVictim(SPELL_DISTRACTING_PAIN);
            task.Repeat(15s);
        });
    }

    void JustDied(Unit* /*killer*/) override
    {
        DoCastAOE(SPELL_EJECT_SNEED);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff,
            std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
};

void AddSC_boss_sneed()
{
    new CreatureAILoader<boss_sneedAI>("boss_sneed");
    new CreatureAILoader<npc_sneed_shredderAI>("npc_sneed_shredder");
}