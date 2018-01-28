/*
REWRITTEN BY XINEF
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "deadmines.h"
#include "GameObjectAI.h"

class instance_deadmines : public InstanceMapScript
{
    public:
        instance_deadmines() : InstanceMapScript("instance_deadmines", 36) { }

        struct instance_deadmines_InstanceMapScript : public InstanceScript
        {
            instance_deadmines_InstanceMapScript(Map* map) : InstanceScript(map)
            {
            }

            void Initialize()
            {
                memset(&_encounters, 0, sizeof(_encounters));
                _factoryDoors = 0;
                _factoryDoorLever = 0;
            }

            void OnGameObjectCreate(GameObject* gameobject)
            {
                switch (gameobject->GetEntry())
                {
                    case GO_IRON_CLAD_DOOR:
                        if (_encounters[TYPE_CANNON] == DONE)
                            HandleGameObject(0, true, gameobject);
                        break;
                    case GO_DOOR_LEVE_FIRST_BOSS:
                        _factoryDoorLever = gameobject->GetGUID();
                        break;
                    case GO_FACTORY_DOOR:
                        _factoryDoors = gameobject->GetGUID();
                        if (_encounters[TYPE_RHAHK_ZOR] == DONE)
                        {
                            HandleGameObject(0, true, gameobject);

                            if (GameObject* lever = instance->GetGameObject(_factoryDoorLever))
                                lever->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                        }
                        break;
                }
            }

            uint64 GetData64(uint32 data) const override
            {
                switch (data)
                {
                    case GO_FACTORY_DOOR:
                        return _factoryDoors;
                }

                return 0;
            }

            void SetData(uint32 type, uint32 data)
            {
                switch (type)
                {
                    case TYPE_RHAHK_ZOR:
                        if (GameObject* lever = instance->GetGameObject(_factoryDoorLever))
                            lever->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                        _encounters[type] = data;
                        break;
                    case TYPE_CANNON:
                        _encounters[type] = data;
                        break;
                }

                if (data == DONE)
                    SaveToDB();
            }

            std::string GetSaveData()
            {
                std::ostringstream saveStream;
                saveStream << "D E " << _encounters[0] << ' ' << _encounters[1];
                return saveStream.str();
            }

            void Load(const char* in)
            {
                if (!in)
                    return;

                char dataHead1, dataHead2;
                std::istringstream loadStream(in);
                loadStream >> dataHead1 >> dataHead2;
                if (dataHead1 == 'D' && dataHead2 == 'E')
                {
                    for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                    {
                        loadStream >> _encounters[i];
                        if (_encounters[i] == IN_PROGRESS)
                            _encounters[i] = NOT_STARTED;
                    }
                }
            }

        private:
            uint32 _encounters[MAX_ENCOUNTERS];
            uint64 _factoryDoors;
            uint64 _factoryDoorLever;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_deadmines_InstanceMapScript(map);
        }
};

struct go_deadmines_lever_first_bossAI : public GameObjectAI
{
public:
    go_deadmines_lever_first_bossAI(GameObject* go) : GameObjectAI(go) { }

    void OnStateChanged(uint32 state, Unit* player) override
    {
        //GameObjectAI::OnStateChanged(state, player);

        if (!player)
            return;

        if (InstanceScript* instance = player->GetInstanceScript())
        {
            if (GameObject* doors = ObjectAccessor::GetGameObject(*player, instance->GetData64(GO_FACTORY_DOOR)))
            {
                if (doors->GetGoState() == GO_STATE_ACTIVE)
                    doors->SetGoState(GO_STATE_READY);
                else
                    doors->SetGoState(GO_STATE_ACTIVE);
            }
        }
    }
};

void AddSC_instance_deadmines()
{
    new instance_deadmines();
    new GameObjectAILoader<go_deadmines_lever_first_bossAI>("go_deadmines_lever_first_boss");
}
