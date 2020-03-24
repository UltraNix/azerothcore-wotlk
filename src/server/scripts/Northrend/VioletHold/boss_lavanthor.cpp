#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"

enum XevozzSpells
{
    SPELL_CAUTERIZING_FLAMES                    = 59466, // Only in heroic
    SPELL_FIREBOLT                              = 54235,
    SPELL_FLAME_BREATH                          = 54282,
    SPELL_LAVA_BURN                             = 54249
};

struct boss_lavanthorAI : public BossAI
{
    boss_lavanthorAI(Creature* creature) : BossAI(creature, DATA_LAVANTHOR) { }

    void Reset() override
    {
        me->SetWalk(true);
        _Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->SetWalk(false);
        _EnterCombat();
        scheduler.Schedule(1s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                DoCast(target, SPELL_FIREBOLT);
            task.Repeat(5s, 13s);
        });

        scheduler.Schedule(5s, [this](TaskContext task)
        {
            DoCastAOE(SPELL_FLAME_BREATH);
            task.Repeat(10s, 15s);
        });

        scheduler.Schedule(10s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f))
                DoCast(target, SPELL_LAVA_BURN);
            task.Repeat(15s, 23s);
        });

        if (IsHeroic())
        {
            scheduler.Schedule(3s, [this](TaskContext task)
            {
                DoCastSelf(SPELL_CAUTERIZING_FLAMES);
                task.Repeat(10s, 16s);
            });
        }
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
        instance->SetData(DATA_HANDLE_CELLS, DATA_LAVANTHOR);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }
};

void AddSC_boss_lavanthor()
{
    new CreatureAILoader<boss_lavanthorAI>("boss_lavanthor");
}
