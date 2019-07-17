#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "blackwing_lair.h"
#include "Player.h"

ObjectData const creatureData[] =
{
    { NPC_RAZORGORE,       BOSS_RAZORGORE },
    { NPC_VAELASTRAZ,      DATA_VAELASTRAZ_THE_CORRUPT },
    { NPC_BROODLORD,       DATA_BROODLORD_LASHLAYER },
    { NPC_FIREMAW,         DATA_FIREMAW },
    { NPC_EBONROC,         DATA_EBONROC },
    { NPC_FLAMEGOR,        DATA_FLAMEGOR },
    { NPC_CHROMAGGUS,      DATA_CHROMAGGUS },
    { NPC_NEFARIAN,        DATA_NEFARIAN },
    { NPC_VICTOR_NEFARIUS, DATA_LORD_VICTOR_NEFARIUS },
    { 0,                   0 } // END
};

DoorData const doorData[] =
{
    { GO_RAZORGORE_GATE_ENTER   , BOSS_RAZORGORE, DOOR_TYPE_ROOM },
    { GO_RAZORGORE_GATE_EXIT    , BOSS_RAZORGORE, DOOR_TYPE_PASSAGE },
    { 0                         , 0             , DOOR_TYPE_ROOM    } // END
};

struct instance_blackwing_lair_InstanceMapScript : public InstanceScript
{
    instance_blackwing_lair_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetBossNumber(EncounterCount);
        LoadDoorData(doorData);
        LoadObjectData(creatureData, nullptr);
        // Vaelastrasz the Corrupt
        VaelastraszDoorGUID = 0;
        // Broodlord Lashlayer
        BroodlordDoorGUID = 0;
        // Chormaggus
        ChrommagusDoorGUID = 0;
        NefarianDoorGUID = 0;
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case 175185: // Door
                VaelastraszDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_VAELASTRAZ) == DONE, go);
                break;
            case 180424: // Door
                BroodlordDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_BROODLORD) == DONE, go);
                break;
            case 185483: // Door
                ChrommagusDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_FIREMAW) == DONE && GetBossState(BOSS_EBONROC) == DONE && GetBossState(BOSS_FLAMEGOR) == DONE, go);
                break;
            case 181125: // Door
                NefarianDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_CHROMAGGUS) == DONE, go);
                break;
        }

        InstanceScript::OnGameObjectCreate(go);
    }

    bool SetBossState(uint32 type, EncounterState state) override
    {
        // pussywizard:
        if (GetBossState(type) == DONE && state != DONE) // prevent undoneing a boss xd
            return false;

        if (!InstanceScript::SetBossState(type, state))
            return false;

        switch (type)
        {
            case BOSS_VAELASTRAZ:
                HandleGameObject(VaelastraszDoorGUID, state == DONE);
                break;
            case BOSS_BROODLORD:
                HandleGameObject(BroodlordDoorGUID, state == DONE);
                break;
            case BOSS_FIREMAW:
            case BOSS_EBONROC:
            case BOSS_FLAMEGOR:
                HandleGameObject(ChrommagusDoorGUID, GetBossState(BOSS_FIREMAW) == DONE && GetBossState(BOSS_EBONROC) == DONE && GetBossState(BOSS_FLAMEGOR) == DONE);
                break;
            case BOSS_CHROMAGGUS:
                HandleGameObject(NefarianDoorGUID, state == DONE);
                break;
            case BOSS_NEFARIAN:
                switch (state)
                {
                    case NOT_STARTED:
                        if (Creature* nefarian = GetCreature(DATA_NEFARIAN))
                            nefarian->DespawnOrUnsummon();
                        break;
                    case FAIL:
                        _events.ScheduleEvent(EVENT_RESPAWN_NEFARIUS, 15*IN_MILLISECONDS*MINUTE);
                        SetBossState(BOSS_NEFARIAN, NOT_STARTED);
                        break;
                    default:
                        break;
                }
                break;
        }
        return true;
    }

    void Update(uint32 diff) override
    {
        if (_events.Empty())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_RESPAWN_NEFARIUS:
                    if (Creature* nefarius = GetCreature(DATA_LORD_VICTOR_NEFARIUS))
                    {
                        nefarius->SetPhaseMask(1, true);
                        nefarius->setActive(true);
                        nefarius->Respawn();
                        nefarius->GetMotionMaster()->MoveTargetedHome();
                    }
                    break;
            }
        }
    }

    protected:
        // Misc
        EventMap _events;

        // Vaelastrasz the Corrupt
        uint64 VaelastraszDoorGUID;

        // Broodlord Lashlayer
        uint64 BroodlordDoorGUID;

        // 3 Dragons
        uint64 ChrommagusDoorGUID;

        // Chormaggus
        uint64 NefarianDoorGUID;
};

void AddSC_instance_blackwing_lair()
{
    new InstanceMapScriptLoader<instance_blackwing_lair_InstanceMapScript>(BRLScriptName, 469);
}
