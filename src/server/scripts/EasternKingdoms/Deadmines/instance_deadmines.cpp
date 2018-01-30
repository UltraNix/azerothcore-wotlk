#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "deadmines.h"

DoorData const doorData[] =
{
    { GO_FACTORY_DOOR,   BOSS_RHAHK_ZOR,    DOOR_TYPE_PASSAGE },
    { 0,                 0,                 DOOR_TYPE_ROOM    }
};

ObjectData const creatureData[] =
{
    { NPC_MR_SMITE, BOSS_MR_SMITE },
    { 0                , 0 } // END
};

ObjectData const gameObjectData[] =
{
    { GO_FACTORY_DOOR, DATA_FACTORY_DOOR },
    { GO_IRON_CLAD_DOOR, DATA_IRON_CLAD_DOOR },
    { 0                         , 0 } // END
};

struct instance_deadmines_InstanceMapScript : public InstanceScript
{
    instance_deadmines_InstanceMapScript(Map* map) : InstanceScript(map) 
    { 
        SetBossNumber(MAX_ENCOUNTERS);
        LoadDoorData(doorData);
        LoadObjectData(creatureData, gameObjectData);
    }

    void Initialize() override
    {
        _cannonEventState = false;
    }

    std::string GetSaveData() override
    {
        std::ostringstream saveStream;
        saveStream << "D E " << GetBossSaveData() << _cannonEventState;
        return saveStream.str();
    }

    uint32 GetData(uint32 type) const override
    {
        switch (type)
        {
            case DATA_CANNON_EVENT:
                return _cannonEventState;
        }

        return 0;
    }

    void SetData(uint32 type, uint32 data) override
    {
        switch (type)
        {
            case DATA_CANNON_EVENT:
                _cannonEventState = data;
                break;
        }

        if (data == 1)
            SaveToDB();
    }


    void OnGameObjectCreate(GameObject* go) override
    {
        if (go->GetEntry() == GO_IRON_CLAD_DOOR)
            if (_cannonEventState)
                go->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);

        InstanceScript::OnGameObjectCreate(go);
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

        if (dataHead1 == 'D' && dataHead2 == 'E')
        {
            for (uint32 i = 0; i < MAX_ENCOUNTERS; ++i)
            {
                uint32 tmpState;
                loadStream >> tmpState;
                if (tmpState == IN_PROGRESS || tmpState == FAIL || tmpState == SPECIAL)
                    tmpState = NOT_STARTED;

                if (tmpState < TO_BE_DECIDED)
                    SetBossState(i, EncounterState(tmpState));
            }

            loadStream >> _cannonEventState;
        }
        else
            OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }

    private:
        bool _cannonEventState;
};

void AddSC_instance_deadmines()
{
    new InstanceMapScriptLoader<instance_deadmines_InstanceMapScript>("instance_deadmines", 36);
}
