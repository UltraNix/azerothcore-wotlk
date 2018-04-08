/*
REWRITTEN BY XINEF
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "azjol_nerub.h"
#include "SpellScript.h"

DoorData const doorData[] =
{
    { GO_KRIKTHIR_DOORS,    DATA_KRIKTHIR_THE_GATEWATCHER_EVENT,    DOOR_TYPE_PASSAGE,        BOUNDARY_NONE },
    { GO_ANUBARAK_DOORS1,    DATA_ANUBARAK_EVENT,    DOOR_TYPE_ROOM,        BOUNDARY_NONE },
    { GO_ANUBARAK_DOORS2,    DATA_ANUBARAK_EVENT,    DOOR_TYPE_ROOM,        BOUNDARY_NONE },
    { GO_ANUBARAK_DOORS3,    DATA_ANUBARAK_EVENT,    DOOR_TYPE_ROOM,        BOUNDARY_NONE },
    { 0,                    0,                        DOOR_TYPE_ROOM,     BOUNDARY_NONE }
};

ObjectData const creatureData[] =
{
    { NPC_KRIKTHIR_THE_GATEWATCHER,        DATA_KRIKTHIR_THE_GATEWATCHER_EVENT },
    { NPC_HADRONOX,        DATA_HADRONOX_EVENT },
    { NPC_ANUBARAK,        DATA_ANUBARAK_EVENT },
    { NPC_WATCHER_NARJIL,  DATA_WATCHER_GASHRA },
    { NPC_WATCHER_GASHRA,  DATA_WATCHER_SILTHIK },
    { NPC_WATCHER_SILTHIK, DATA_WATCHER_NARJIL },
    { 0,                   0 } // END
};

class instance_azjol_nerub : public InstanceMapScript
{
    public:
        instance_azjol_nerub() : InstanceMapScript("instance_azjol_nerub", 601) { }

        struct instance_azjol_nerub_InstanceScript : public InstanceScript
        {
            instance_azjol_nerub_InstanceScript(Map* map) : InstanceScript(map)
            {
                SetHeaders("AN");
                SetBossNumber(3);
                LoadDoorData(doorData);
                _krikthirGUID = 0;
                _hadronoxGUID = 0;
                LoadObjectData(creatureData, nullptr);
            };

            void OnCreatureCreate(Creature* creature) override
            {
                switch (creature->GetEntry())
                {
                    case NPC_KRIKTHIR_THE_GATEWATCHER:
                        _krikthirGUID = creature->GetGUID();
                        break;
                    case NPC_HADRONOX:
                        _hadronoxGUID = creature->GetGUID();
                        break;
                    case NPC_SKITTERING_SWARMER:
                    case NPC_SKITTERING_INFECTIOR:
                        if (Creature* krikthir = instance->GetCreature(_krikthirGUID))
                            krikthir->AI()->JustSummoned(creature);
                        break;
                    case NPC_ANUB_AR_CHAMPION:
                    case NPC_ANUB_AR_NECROMANCER:
                    case NPC_ANUB_AR_CRYPTFIEND:
                        if (Creature* hadronox = instance->GetCreature(_hadronoxGUID))
                            hadronox->AI()->JustSummoned(creature);
                        break;

                }

                InstanceScript::OnCreatureCreate(creature);
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_KRIKTHIR_DOORS:
                    case GO_ANUBARAK_DOORS1:
                    case GO_ANUBARAK_DOORS2:
                    case GO_ANUBARAK_DOORS3:
                        AddDoor(go, true);
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_KRIKTHIR_DOORS:
                    case GO_ANUBARAK_DOORS1:
                    case GO_ANUBARAK_DOORS2:
                    case GO_ANUBARAK_DOORS3:
                        AddDoor(go, false);
                        break;
                }
            }

            bool SetBossState(uint32 id, EncounterState state) override
            {
                return InstanceScript::SetBossState(id, state);
            }

        private:
            uint64 _krikthirGUID;
            uint64 _hadronoxGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap *map) const
        {
            return new instance_azjol_nerub_InstanceScript(map);
        }
};

void AddSC_instance_azjol_nerub()
{
   new instance_azjol_nerub();
}
