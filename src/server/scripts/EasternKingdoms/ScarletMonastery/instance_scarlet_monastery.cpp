/*
REWRITTEN BY XINEF
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"

uint32 const GO_HEROD_DOOR = 101854;

class instance_scarlet_monastery : public InstanceMapScript
{
    public:
        instance_scarlet_monastery() : InstanceMapScript("instance_scarlet_monastery", 189) { }

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_scarlet_monastery_InstanceMapScript(map);
        }

        struct instance_scarlet_monastery_InstanceMapScript : public InstanceScript
        {
            instance_scarlet_monastery_InstanceMapScript(Map* map) : InstanceScript(map) { }

            //void OnGameObjectCreate(GameObject* go) override
            //{
            //    switch (go->GetEntry())
            //    {
            //        case GO_HEROD_DOOR:
            //        {
            //            if (IsLFGInstance())
            //                HandleGameObject(0, true, go);
            //            break;
            //        }
            //        default:
            //            break;
            //    }
            //}
        };
};

void AddSC_instance_scarlet_monastery()
{
    new instance_scarlet_monastery();
}
