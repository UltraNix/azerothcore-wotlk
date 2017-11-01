#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "onyxias_lair.h"

ObjectData const creatureData[] =
{
    { DATA_ONYXIA, NPC_ONYXIA },
    { 0          ,          0 } // END
};

struct instance_onyxias_lair_InstanceMapScript : public InstanceScript
{
    instance_onyxias_lair_InstanceMapScript(Map* map) : InstanceScript(map) 
    {
        LoadObjectData(creatureData, nullptr);
        SetBossNumber(MAX_ENCOUNTER);
    };

    bool SetBossState(uint32 type, EncounterState state) override
    {
        if (!InstanceScript::SetBossState(type, state))
            return false;

        if (state == NOT_STARTED)
        {
            for (std::vector<uint64>::iterator itr = _minions.begin(); itr != _minions.end(); ++itr)
                if (Creature* minion = instance->GetCreature(*itr))
                    minion->DespawnOrUnsummon();
            _minions.clear();
        }

        return true;
    }

    void OnCreatureCreate(Creature* creature) override
    {
        switch (creature->GetEntry())
        {
            case NPC_ONYXIAN_WHELP:
            case NPC_ONYXIAN_LAIR_GUARD:
                _minions.push_back(creature->GetGUID());
                break;
        }
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case GO_WHELP_SPAWNER:
                go->CastSpell((Unit*)nullptr, 17646);
                if (Creature* onyxia = GetCreature(DATA_ONYXIA))
                    if (onyxia->IsAIEnabled)
                        onyxia->AI()->DoAction(-1);
                break;
        }
    }

    std::string GetSaveData() override
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "O L " << GetBossSaveData();

        OUT_SAVE_INST_DATA_COMPLETE;
        return saveStream.str();
    }

    void Load(char const* data) override
    {
        if (!data)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }

        OUT_LOAD_INST_DATA(data);

        char dataHead1, dataHead2;

        std::istringstream loadStream(data);
        loadStream >> dataHead1 >> dataHead2;

        if (dataHead1 == 'O' && dataHead2 == 'L')
        {
            EncounterState states[MAX_ENCOUNTER];

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                uint32 tmpState;
                loadStream >> tmpState;
                if (tmpState == IN_PROGRESS || tmpState > TO_BE_DECIDED)
                    tmpState = NOT_STARTED;
                states[i] = EncounterState(tmpState);
            }

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                SetBossState(i, states[i]);
        }
        else
            OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }

private:
    std::vector<uint64> _minions;
};

void AddSC_instance_onyxias_lair()
{
    new InstanceMapScriptLoader<instance_onyxias_lair_InstanceMapScript>("instance_onyxias_lair", 249);
}