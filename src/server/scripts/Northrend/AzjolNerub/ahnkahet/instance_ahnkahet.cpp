#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ahnkahet.h"

ObjectData const creatureData[] =
{
    { NPC_ELDER_NADOX           , BOSS_NADOX    },
    { NPC_PRINCE_TALDARAM       , BOSS_TALDARAM },
    { NPC_JEDOGA_SHADOWSEEKER   , BOSS_JEDOGA   },
    { NPC_HERALD_JOLAZJ         , BOSS_VOLAZJ   },
    { NPC_AMANITAR              , BOSS_AMANITAR },
    { 0                         ,             0 } // END
};

ObjectData const gameObjectData[] =
{
    { GO_TALDARAM_SHIELD  , DATA_TALDARAM_SHIELD },
    { 0                         , 0 } // END
};

DoorData const doorData[] =
{
    //{ GO_TALDARAM_SHIELD, BOSS_TALDARAM, DOOR_TYPE_PASSAGE },
    { GO_TALDARAM_WEB_GATE, BOSS_TALDARAM, DOOR_TYPE_PASSAGE },
    { 0,             0,          DOOR_TYPE_ROOM } // END
};

struct instance_ahnkahet_InstanceMapScript : public InstanceScript
{
    instance_ahnkahet_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetBossNumber(MAX_ENCOUNTER);
        LoadObjectData(creatureData, gameObjectData);
        LoadDoorData(doorData);
    };

    void Initialize() override
    {
        memset(_spheres, NOT_STARTED, sizeof(_spheres));
    }

    void SetData(uint32 type, uint32 data)
    {
        switch (type)
        {
            case DATA_SPHERE_EVENT_1:
                _spheres[0] = data;
                break;
            case DATA_SPHERE_EVENT_2:
                _spheres[1] = data;
                break;
        }

        SaveToDB();
    }
    
    void OnPlayerEnter(Player* player) override
    {
        if (player && player->HasAura(57055))
            if (GetBossState(BOSS_AMANITAR) != IN_PROGRESS)
                player->RemoveAurasDueToSpell(57055);
    }

    uint32 GetData(uint32 type) const override
    {
        switch (type)
        {
            case DATA_SPHERE_EVENT_1:
                return _spheres[0];
            case DATA_SPHERE_EVENT_2:
                return _spheres[1];
        }

        return 0;
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case GO_TALDARAM_SPHERE_1:
                if (_spheres[0] == DONE)
                {
                    go->SetGoState(GO_STATE_ACTIVE);
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                }
                else
                    go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                break;
            case GO_TALDARAM_SPHERE_2:
                if (_spheres[1] == DONE)
                {
                    go->SetGoState(GO_STATE_ACTIVE);
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                }
                else
                    go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                break;
            default:
                break;
        }

        InstanceScript::OnGameObjectCreate(go);
    }

    std::string GetSaveData() override
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "A K " << GetBossSaveData() << _spheres[0] << ' ' << _spheres[1];

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

        if (dataHead1 == 'A' && dataHead2 == 'K')
        {
            for (uint32 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                uint32 tmpState;
                loadStream >> tmpState;
                if (tmpState == IN_PROGRESS || tmpState == FAIL || tmpState == SPECIAL)
                    tmpState = NOT_STARTED;

                if (tmpState < TO_BE_DECIDED)
                    SetBossState(i, EncounterState(tmpState));
            }

            loadStream >> _spheres[0];
            loadStream >> _spheres[1];
        }
        else
            OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }

    private:
        uint32 _spheres[2];
};

void AddSC_instance_ahnkahet()
{
    new InstanceMapScriptLoader<instance_ahnkahet_InstanceMapScript>("instance_ahnkahet", 619);
}
