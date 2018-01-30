#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"
#include "GameObjectAI.h"

enum RhahkzorSpells
{
    SPELL_RHAHKZOR_SLAM = 6304
};

enum RhahkzorTexts
{
    SAY_AGGRO
};

struct boss_rhahkzorAI : public BossAI
{
    boss_rhahkzorAI(Creature* creature) : BossAI(creature, BOSS_RHAHK_ZOR) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        scheduler.Schedule(1s, 8s, [this](TaskContext task) 
        {
            DoCastVictim(SPELL_RHAHKZOR_SLAM);
            task.Repeat(11s, 17s);
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

struct go_deadmines_lever_first_bossAI : public GameObjectAI
{
    public:
        go_deadmines_lever_first_bossAI(GameObject* go) : GameObjectAI(go) { }

        void OnStateChanged(uint32 state, Unit* player) override
        {
            if (!player)
                return;

            if (InstanceScript* instance = player->GetInstanceScript())
            {
                if (GameObject* door = instance->GetGameObject(DATA_FACTORY_DOOR))
                {
                    if (door->GetGoState() == GO_STATE_ACTIVE)
                        door->SetGoState(GO_STATE_READY);
                    else
                        door->SetGoState(GO_STATE_ACTIVE);
                }
            }
        }
};

void AddSC_boss_rhahk_zor()
{
    new CreatureAILoader<boss_rhahkzorAI>("boss_rhahkzor");
    new GameObjectAILoader<go_deadmines_lever_first_bossAI>("go_deadmines_lever_first_boss");
}
