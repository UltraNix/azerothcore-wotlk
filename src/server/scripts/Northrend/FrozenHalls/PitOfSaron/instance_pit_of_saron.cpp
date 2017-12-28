#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "pit_of_saron.h"
#include "Player.h"

ObjectData const creatureData[] =
{
    { NPC_TYRANNUS_EVENT    , DATA_TYRANNUS_EVENT_GUID },
    { NPC_SYLVANAS_PART1    , DATA_LEADER_FIRST_GUID },
    { NPC_JAINA_PART1       , DATA_LEADER_FIRST_GUID },
    { NPC_SYLVANAS_PART2    , DATA_LEADER_SECOND_GUID },
    { NPC_JAINA_PART2       , DATA_LEADER_SECOND_GUID },
    { NPC_LORALEN           , DATA_GUARD_1_GUID },
    { NPC_ELANDRA           , DATA_GUARD_1_GUID },
    { NPC_KALIRA            , DATA_GUARD_2_GUID },
    { NPC_KORELN            , DATA_GUARD_2_GUID },
    { NPC_GARFROST          , DATA_GARFROST },
    { NPC_ICK               , DATA_ICK },
    { NPC_KRICK             , DATA_KRICK },
    { NPC_TYRANNUS          , DATA_TYRANNUS },
    { NPC_RIMEFANG          , DATA_RIMEFANG_GUID },
    { NPC_GORKUN_IRONSKULL_2, DATA_MARTIN_OR_GORKUN_GUID },
    { NPC_MARTIN_VICTUS_2   , DATA_MARTIN_OR_GORKUN_GUID },
    { NPC_SINDRAGOSA        , DATA_SINDRAGOSA_GUID },
    { 0                     ,            0 } // END
};

ObjectData const gameObjectData[] =
{
    { GO_ICE_WALL      , DATA_ICE_WALL },
    { GO_HOR_PORTCULLIS, DATA_PORTCULLIS },
    { 0                , 0 } //END
};

struct instance_pit_of_saron_InstanceMapScript : public InstanceScript
{
    instance_pit_of_saron_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        LoadObjectData(creatureData, gameObjectData);
        _teamInInstance = TEAM_NEUTRAL;
        _instanceProgress = INSTANCE_PROGRESS_NONE;
        _firstNecrolyteGUID = 0;
        _secondNecrolyteGUID = 0;
        _dontLookUp = true;
        SetBossNumber(MAX_ENCOUNTER);
    }

    void OnPlayerEnter(Player* /*player*/) override
    {
        float x = LeaderIntroPos.GetPositionX(), y = LeaderIntroPos.GetPositionY();
        if (!instance->IsGridLoaded(x, y))
            instance->LoadGrid(x, y);
    }

    void AssignTeamId()
    {
        Map::PlayerList const &players = instance->GetPlayers();
        if (!players.isEmpty())
            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                if (Player* player = itr->GetSource())
                    if (!player->IsGameMaster())
                    {
                        _teamInInstance = player->GetTeamId();
                        break;
                    }
    }

    uint32 GetCreatureEntry(uint32 /*guidLow*/, CreatureData const* data)
    {
        if (_teamInInstance == TEAM_NEUTRAL)
            AssignTeamId();

        uint32 entry = data->id;
        switch (entry)
        {
            case NPC_RESCUED_ALLIANCE_SLAVE:
                if (_teamInInstance == TEAM_HORDE)
                    return 0;
                break;
            case NPC_RESCUED_HORDE_SLAVE:
                if (_teamInInstance == TEAM_ALLIANCE)
                    return 0;
                break;
        }

        return entry;
    }

    void OnCreatureCreate(Creature* creature) override
    {
        if (_teamInInstance == TEAM_NEUTRAL)
            AssignTeamId();

        switch (creature->GetEntry())
        {
            case NPC_SYLVANAS_PART1:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_JAINA_PART1);

                switch (_instanceProgress)
                {
                case INSTANCE_PROGRESS_FINISHED_INTRO:
                    creature->SetPosition(LeaderIntroPos);
                    break;
                case INSTANCE_PROGRESS_FINISHED_KRICK_SCENE:
                case INSTANCE_PROGRESS_AFTER_WARN_1:
                case INSTANCE_PROGRESS_AFTER_WARN_2:
                case INSTANCE_PROGRESS_AFTER_TUNNEL_WARN:
                case INSTANCE_PROGRESS_TYRANNUS_INTRO:
                    creature->SetPosition(SBSLeaderEndPos);
                    break;
                }
                break;
            case NPC_SYLVANAS_PART2:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_JAINA_PART2);
                break;
            case NPC_TYRANNUS_EVENT:
                switch (_instanceProgress)
                {
                case INSTANCE_PROGRESS_FINISHED_INTRO:
                    creature->SetPosition(SBSTyrannusStartPos);
                    break;
                case INSTANCE_PROGRESS_FINISHED_KRICK_SCENE:
                    creature->SetPosition(PTSTyrannusWaitPos1);
                    break;
                case INSTANCE_PROGRESS_AFTER_WARN_1:
                    creature->SetPosition(PTSTyrannusWaitPos2);
                    break;
                case INSTANCE_PROGRESS_AFTER_WARN_2:
                    creature->SetPosition(PTSTyrannusWaitPos3);
                    break;
                case INSTANCE_PROGRESS_AFTER_TUNNEL_WARN:
                case INSTANCE_PROGRESS_TYRANNUS_INTRO:
                    creature->SetPosition(SBSTyrannusStartPos);
                    break;
                }

                break;
            case NPC_LORALEN:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_ELANDRA);
                break;
            case NPC_KALIRA:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_KORELN);
                break;
            case NPC_HORDE_SLAVE_1:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_ALLIANCE_SLAVE_1);
                break;
            case NPC_HORDE_SLAVE_2:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_ALLIANCE_SLAVE_2);
                break;
            case NPC_HORDE_SLAVE_3:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_ALLIANCE_SLAVE_3);
                break;
            case NPC_HORDE_SLAVE_4:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_ALLIANCE_SLAVE_4);
                break;
            case NPC_GORKUN_IRONSKULL_1:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_MARTIN_VICTUS_1);
                break;
            case NPC_FREED_SLAVE_1_HORDE:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_FREED_SLAVE_1_ALLIANCE);
                break;
            case NPC_FREED_SLAVE_2_HORDE:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_FREED_SLAVE_2_ALLIANCE);
                break;
            case NPC_FREED_SLAVE_3_HORDE:
                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_FREED_SLAVE_3_ALLIANCE);
                break;
            case NPC_GORKUN_IRONSKULL_2:
                if (Creature* martinOrGorkun = GetCreature(DATA_MARTIN_OR_GORKUN_GUID))
                {
                    if (martinOrGorkun->IsAIEnabled)
                        martinOrGorkun->AI()->DoAction(1); // despawn summons
                    martinOrGorkun->DespawnOrUnsummon();
                }

                if (_teamInInstance == TEAM_ALLIANCE)
                    creature->UpdateEntry(NPC_MARTIN_VICTUS_2);
                break;
            case NPC_RIMEFANG:
                if (GetBossState(DATA_TYRANNUS) == DONE)
                    creature->SetVisible(false);
                break;
            case NPC_TYRANNUS:
                if (Creature* tyrannus = GetCreature(NPC_TYRANNUS))
                    tyrannus->DespawnOrUnsummon();

                if (GetBossState(DATA_TYRANNUS) == DONE)
                    creature->SetVisible(false);
                break;
        }

        InstanceScript::OnCreatureCreate(creature);
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case GO_ICE_WALL:
                if (GetBossState(DATA_GARFROST) == DONE && GetBossState(DATA_ICK) == DONE)
                    go->SetGoState(GO_STATE_ACTIVE);
                break;
            case GO_HOR_PORTCULLIS:
                if (GetBossState(DATA_TYRANNUS) == DONE)
                    go->SetGoState(GO_STATE_ACTIVE);
                break;
        }

        InstanceScript::OnGameObjectCreate(go);
    }

    bool SetBossState(uint32 type, EncounterState state) override
    {
        if (GetBossState(type) == DONE && state != DONE)
            return false;

        if (!InstanceScript::SetBossState(type, state))
            return false;

        if (GetBossState(DATA_GARFROST) == DONE)
            instance->SummonCreature(NPC_GORKUN_IRONSKULL_1, FBSSpawnPos);

        if (GetBossState(DATA_ICK) == DONE && GetBossState(DATA_GARFROST) == DONE)
            if (GameObject* iceWall = GetGameObject(DATA_ICE_WALL))
                iceWall->SetGoState(GO_STATE_ACTIVE);

        if (GetBossState(DATA_TYRANNUS) == DONE)
            instance->SummonCreature(NPC_SYLVANAS_PART2, TSLeaderSpawnPos);

        return true;
    }

    void SetData(uint32 type, uint32 data) override
    {
        switch (type)
        {
            case DATA_INSTANCE_PROGRESS:
                if (_instanceProgress < data)
                {
                    _instanceProgress = data;
                    if (_instanceProgress == INSTANCE_PROGRESS_TYRANNUS_INTRO && instance->GetDifficulty() == DUNGEON_DIFFICULTY_HEROIC && _dontLookUp) // achiev Don't Look Up (4525)
                        DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 72845);
                }
                break;
            case DATA_ACHIEV_DONT_LOOK_UP:
                _dontLookUp = false;
                break;
        }

        if (type == DATA_INSTANCE_PROGRESS)
            SaveToDB();
    }

    void SetData64(uint32 type, uint64 data) override
    {
        switch (type)
        {
            case DATA_NECROLYTE_1_GUID:
                _firstNecrolyteGUID = data;
                break;
            case DATA_NECROLYTE_2_GUID:
                _secondNecrolyteGUID = data;
                break;
        }
    }

    uint32 GetData(uint32 type) const override
    {
        switch (type)
        {
            case DATA_INSTANCE_PROGRESS:
                return _instanceProgress;
            case DATA_TEAMID_IN_INSTANCE:
                return _teamInInstance;
        }

        return 0;
    }

    uint64 GetData64(uint32 type) const override
    {
        switch (type)
        {
            case DATA_NECROLYTE_1_GUID:
                return _firstNecrolyteGUID;
            case DATA_NECROLYTE_2_GUID:
                return _secondNecrolyteGUID;
        }

        return 0;
    }

    std::string GetSaveData() override
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "P S " << GetBossSaveData() << _instanceProgress;

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

        if (dataHead1 == 'P' && dataHead2 == 'S')
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

            uint32 progress;
            loadStream >> progress;
            _instanceProgress = progress;

        }
        else
            OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }

    private:
        TeamId _teamInInstance;
        uint32 _instanceProgress;
        uint64 _firstNecrolyteGUID;
        uint64 _secondNecrolyteGUID;
        bool _dontLookUp;
};

void AddSC_instance_pit_of_saron()
{
    new InstanceMapScriptLoader<instance_pit_of_saron_InstanceMapScript>("instance_pit_of_saron", 658);
}
