/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "karazhan.h"
#include <array>

#define MAX_ENCOUNTER      12

 /*
 0  - Attumen + Midnight (optional)
 1  - Moroes
 2  - Maiden of Virtue (optional)
 3  - Hyakiss the Lurker /  Rokad the Ravager  / Shadikith the Glider
 4  - Opera Event
 5  - Curator
 6  - Shade of Aran (optional)
 7  - Terestian Illhoof (optional)
 8  - Netherspite (optional)
 9  - Chess Event
 10 - Prince Malchezzar
 11 - Nightbane
 */

ObjectData const creatureData[] =
{
    { NPC_KILREK            , DATA_KILREK },
    { NPC_TERESTIAN         , BOSS_TERESTIAN },
    { NPC_MOROES            , BOSS_MOROES },
    { NPC_MALCHEZAAR        , BOSS_MALCHEZZAR },
    { NPC_NETHERSPITE       , BOSS_NETHERSPITE },
    { NPC_NIGHTBANE         , BOSS_NIGHTBANE },
    { NPC_IMAGE_OF_MEDIVH   , DATA_IMAGE_OF_MEDIVH },
    { NPC_ECHO_OF_MEDIVH    , DATA_ECHO_OF_MEDIVH },
    { NPC_ROMULO            , DATA_ROMULO },
    { NPC_JULIANNE          , DATA_JULIANNE },
    { NPC_BARNES            , DATA_BARNES },
    { NPC_CRONE             , DATA_CRONE },
    { NPC_DOROTHEE          , DATA_DOROTHEE },
    { NPC_STRAWMAN          , DATA_STRAWMAN },
    { NPC_TINHEAD           , DATA_TINHEAD },
    { NPC_ROAR              , DATA_ROAR },
    { 0                     , 0 } // END
};

ObjectData const gameObjectData[] =
{
    { GO_STAGEDOORLEFT          , DATA_GO_STAGEDOORLEFT },
    { GO_STAGEDOORRIGHT         , DATA_GO_STAGEDOORRIGHT },
    { GO_CURTAINS               , DATA_GO_CURTAINS },
    { GO_LIBRARY_DOOR           , DATA_GO_LIBRARY_DOOR },
    { GO_MASSIVE_DOOR           , DATA_GO_MASSIVE_DOOR },
    { GO_SIDE_ENTRANCE_DOOR     , DATA_GO_SIDE_ENTRANCE_DOOR },
    { GO_GAME_DOOR              , DATA_GO_GAME_DOOR },
    { GO_GAME_EXIT_DOOR         , DATA_GO_GAME_EXIT_DOOR },
    { GO_NETHER_DOOR            , DATA_GO_NETHER_DOOR },
    { GO_MASTERS_TERRACE_DOOR_1 , DATA_MASTERS_TERRACE_DOOR_1 },
    { GO_MASTERS_TERRACE_DOOR_2 , DATA_MASTERS_TERRACE_DOOR_2 },
    { GO_DUST_COVERED_CHEST     , DATA_DUST_COVERED_CHEST },
    { GO_BLACKENED_URN          , DATA_GO_BLACKENED_URN },
    { 0                         ,            0 } // END
};

DoorData const doorData[] =
{
    { GO_MASSIVE_DOOR          , BOSS_NETHERSPITE  , DOOR_TYPE_ROOM },
    { GO_NETHER_DOOR           , BOSS_MALCHEZZAR   , DOOR_TYPE_ROOM },
    { 0,                         0,                  DOOR_TYPE_ROOM } // END
};

enum ServantQuartersGUIDs : uint8
{
    GUID_HYAKISS,
    GUID_SHADIKITH,
    GUID_ROKAD
};

struct instance_karazhan_InstanceMapScript : public InstanceScript
{
    instance_karazhan_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetHeaders(DataHeader);
        SetBossNumber(MAX_ENCOUNTER);
        LoadObjectData(creatureData, gameObjectData);
        LoadDoorData(doorData);

        _servantQuarterGUIDs = { 0, 0, 0 };
        _servantQuartersKills = 0;
        _selectedRare = RAND(NPC_SHADIKITH_THE_GLIDER, NPC_HYAKISS_THE_LURKER, NPC_ROKAD_THE_RAVAGER);
        _operaEvent = RAND(OPERA_EVENT_RED_RIDING_HOOD, OPERA_EVENT_WIZARD_OF_OZ, OPERA_EVENT_ROMULO_AND_JULIANNE);
        _servantQuarterBossAggroed = false;
    }

    void SetData(uint32 field, uint32 data) override
    {
        switch (field)
        {
            case DATA_SERVANT_QUARTERS_AGGRO:
                _servantQuarterBossAggroed = static_cast<bool>(data);
                break;
            case DATA_SERVANT_QUARTERS_TRASH:
                if (++_servantQuartersKills >= 56)
                    for (auto guid : _servantQuarterGUIDs)
                        if (Creature* creature = instance->GetCreature(guid))
                            if (creature->IsAIEnabled && creature->GetEntry() == GetData(DATA_SELECTED_RARE))
                                creature->AI()->DoAction(0);
                break;
            default:
                break;
        }

        SaveToDB();
    }

    bool SetBossState(uint32 type, EncounterState state) override
    {
        if (GetBossState(type) == DONE && state != DONE)
            return false;

        if (!InstanceScript::SetBossState(type, state))
            return false;

        if (type == BOSS_SERVANT_QUARTERS && state == IN_PROGRESS)
            SetData(DATA_SERVANT_QUARTERS_AGGRO, 1);

        // i don't think it should be here
        if (type == BOSS_OPERA)
        {
            if (auto barnes = GetCreature(DATA_BARNES))
            {
                if (barnes->IsAIEnabled)
                {
                    switch (state)
                    {
                        case DONE:
                            barnes->AI()->DoAction(0);
                            break;
                        case FAIL:
                            barnes->AI()->DoAction(1);
                            barnes->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            break;
                        case IN_PROGRESS:
                            barnes->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            break;
                    }
                }
            }
        }

        if (type == BOSS_CHESS && state == DONE)
            DoRespawnGameObject(GetGameObject(DATA_DUST_COVERED_CHEST)->GetGUID(), DAY);

        return true;
    }

    void OnCreatureCreate(Creature* creature) override
    {
        switch (creature->GetEntry())
        {
            case NPC_HYAKISS_THE_LURKER:
                _servantQuarterGUIDs[GUID_HYAKISS] = creature->GetGUID();
                break;
            case NPC_SHADIKITH_THE_GLIDER:
                _servantQuarterGUIDs[GUID_SHADIKITH] = creature->GetGUID();
                break;
            case NPC_ROKAD_THE_RAVAGER:
                _servantQuarterGUIDs[GUID_ROKAD] = creature->GetGUID();
                break;
            default:
                break;
        }

        InstanceScript::OnCreatureCreate(creature);
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case GO_STAGEDOORLEFT:
            case GO_STAGEDOORRIGHT:
            case GO_CURTAINS:
                if (GetBossState(BOSS_OPERA) == DONE)
                    go->SetGoState(GO_STATE_ACTIVE);
                break;
            case GO_SIDE_ENTRANCE_DOOR:
                if (GetBossState(BOSS_SERVANT_QUARTERS) == DONE)
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                else
                    go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
                break;
        }

        InstanceScript::OnGameObjectCreate(go);
    }

    uint32 GetData(uint32 data) const override
    {
        switch (data)
        {
            case DATA_SELECTED_RARE:
                return _selectedRare;
            case DATA_OPERA_PERFORMANCE:
                return _operaEvent;
            case DATA_SERVANT_QUARTERS_AGGRO:
                return static_cast<uint32>(_servantQuarterBossAggroed);
        }

        return 0;
    }

    void WriteSaveDataMore(std::ostringstream& data) override
    {
        data << _servantQuartersKills << ' ' << _selectedRare << ' ' << _operaEvent << ' ' << _servantQuarterBossAggroed;
    }

    void ReadSaveDataMore(std::istringstream& data) override
    {
        data >> _servantQuartersKills;
        data >> _selectedRare;
        data >> _operaEvent;
        data >> _servantQuarterBossAggroed;
    }

    private:
        uint32 _servantQuartersKills;
        uint32 _selectedRare;
        uint32 _operaEvent;
        bool _servantQuarterBossAggroed;
        std::array<uint64, 3> _servantQuarterGUIDs;
};

void AddSC_instance_karazhan()
{
    new InstanceMapScriptLoader<instance_karazhan_InstanceMapScript>("instance_karazhan", 532);
}
