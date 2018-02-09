/*
REWRITTEN BY XINEF
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Group.h"

uint32 const GO_HEROD_DOOR = 101854;

class instance_scarlet_monastery : public InstanceMapScript
{
    public:
        instance_scarlet_monastery() : InstanceMapScript("instance_scarlet_monastery", 189) { }


        struct instance_scarlet_monastery_InstanceMapScript : public InstanceScript
        {
            instance_scarlet_monastery_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                _goHerodDoorGUID = 0;
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_HEROD_DOOR:
                    {
                        _goHerodDoorGUID = go->GetGUID();
                        break;
                    }
                    default:
                        break;
                }
            }

            void OnPlayerEnter(Player* player) override
            {
                if (player && player->GetGroup() && player->GetGroup()->isLFGGroup())
                    if (GameObject* doors = instance->GetGameObject(_goHerodDoorGUID))
                        HandleGameObject(0, true, doors);
            }
        private:
            uint64 _goHerodDoorGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_scarlet_monastery_InstanceMapScript(map);
        }
};

void AddSC_instance_scarlet_monastery()
{
    new instance_scarlet_monastery();
}
