#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "forge_of_souls.h"
#include "Player.h"

ObjectData const creatureData[] =
{
    { NPC_BRONJAHM      , DATA_BRONJAHM },
    { NPC_DEVOURER      , DATA_DEVOURER },
    { NPC_SYLVANAS_PART1, DATA_LEADER },
    { NPC_JAINA_PART1   , DATA_LEADER },
    { NPC_SYLVANAS_PART2, DATA_LEADER_2 },
    { NPC_JAINA_PART2   , DATA_LEADER_2 },
    { NPC_LORALEN       , DATA_GUARD },
    { NPC_ELANDRA       , DATA_GUARD },
    { NPC_KALIRA        , DATA_GUARD_2 },
    { NPC_KORELN        , DATA_GUARD_2 },
    { 0                 ,            0 } // END
};

struct instance_forge_of_souls_InstanceScript : public InstanceScript
{
    instance_forge_of_souls_InstanceScript(Map* map) : InstanceScript(map)
    {
        LoadTrashMapInfoData();
        SetBossNumber(MAX_ENCOUNTER);
        LoadObjectData(creatureData, nullptr);
        _teamInInstance = TEAM_NEUTRAL;
    }

    void OnPlayerEnter(Player* plr) override
    {
        // this will happen only after crash and loading the instance from db
        if (GetBossState(DATA_BRONJAHM) == DONE && GetBossState(DATA_DEVOURER) == DONE && !GetCreature(DATA_LEADER_2))
            instance->SummonCreature(NPC_SYLVANAS_PART2, { 5658.15f, 2502.564f, 708.83f, 0.885207f });
    }

    void OnCreatureCreate(Creature* creature) override
    {
        if (_teamInInstance == TEAM_NEUTRAL)
        {
            Map::PlayerList const &players = instance->GetPlayers();
            if (!players.isEmpty())
                if (Player* player = players.begin()->GetSource())
                    if (!player->IsGameMaster())
                        _teamInInstance = player->GetTeamId();
        }

        switch (creature->GetEntry())
        {
            case NPC_SYLVANAS_PART1:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_JAINA_PART1);

                if (GetBossState(DATA_BRONJAHM) == DONE && GetBossState(DATA_DEVOURER) == DONE)
                    creature->SetVisible(false);
                break;
            case NPC_SYLVANAS_PART2:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_JAINA_PART2);
                break;
            case NPC_LORALEN:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_ELANDRA);

                if (GetBossState(DATA_BRONJAHM) == DONE && GetBossState(DATA_DEVOURER) == DONE)
                    creature->SetVisible(false);
                break;
            case NPC_KALIRA:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_KORELN);

                if (GetBossState(DATA_BRONJAHM) == DONE && GetBossState(DATA_DEVOURER) == DONE)
                    creature->SetVisible(false);
                break;
        }

        InstanceScript::OnCreatureCreate(creature);
    }

    bool SetBossState(uint32 type, EncounterState state) override
    {
        if (!InstanceScript::SetBossState(type, state))
            return false;

        if (type == DATA_DEVOURER && state == DONE && GetBossState(DATA_BRONJAHM) == DONE)
            HandleOutro();

        return true;
    }

    void HandleOutro()
    {
        if (!GetCreature(DATA_LEADER_2))
            if (Creature* leader = instance->SummonCreature(NPC_SYLVANAS_PART2, outroSpawnPoint))
                if (Creature* boss = GetCreature(DATA_DEVOURER))
                {
                    float angle = boss->GetAngle(leader);
                    leader->GetMotionMaster()->MovePoint(1, boss->GetPositionX() + 10.0f*cos(angle), boss->GetPositionY() + 10.0f*sin(angle), boss->GetPositionZ());
                }

        for (int8 i = 0; outroPositions[i].entry[_teamInInstance] != 0; ++i)
            if (Creature* summon = instance->SummonCreature(outroPositions[i].entry[_teamInInstance], outroPositions[i].startPosition))
                summon->GetMotionMaster()->MovePath(outroPositions[i].pathId, false);
    }

    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "F S " << GetBossSaveData();

        OUT_SAVE_INST_DATA_COMPLETE;
        return saveStream.str();
    }

    void Load(char const* data)
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

        if (dataHead1 == 'F' && dataHead2 == 'S')
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
    TeamId _teamInInstance;
};

void AddSC_instance_forge_of_souls()
{
    new InstanceMapScriptLoader<instance_forge_of_souls_InstanceScript>("instance_forge_of_souls", 632);
}
