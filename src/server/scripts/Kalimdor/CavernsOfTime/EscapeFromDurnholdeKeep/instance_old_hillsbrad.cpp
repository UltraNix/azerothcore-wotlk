#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"
#include "old_hillsbrad.h"
#include "Player.h"

const Position instancePositions[INSTANCE_POSITIONS_COUNT] =
{
    { 2188.18f, 228.90f, 53.025f, 1.77f  },          // Orcs Gather Point 1
    { 2103.23f, 93.55f, 53.096f, 3.78f   },          // Orcs Gather Point 2
    { 2128.43f, 71.01f, 64.42f, 1.74f    }           // Lieutenant Drake Summon Position
};

const Position thrallPositions[THRALL_POSITIONS_COUNT] =
{
    { 2181.37f, 119.15f, 89.45f, 5.75f   },          // After wearing armor
    { 2096.09f, 195.91f, 65.22f, 2.45f   },          // After Fourth Ambush
    { 2062.9f, 229.93f, 64.454f, 2.45f   },          // After Captain Skarloc death
    { 2486.91f, 626.356f, 58.0761f, 0.0f },          // Arrived at Tarren Mill
    { 2660.47f, 659.223f, 62.0f, 5.78f   }           // Taretha Met
};

ObjectData const creatureData[] =
{
    { NPC_THRALL    , DATA_THRALL   },
    { NPC_TARETHA   , DATA_TARETHA  },
    { 0             , 0             } // END
};

struct instance_old_hillsbrad_InstanceMapScript : public InstanceScript
{
    instance_old_hillsbrad_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetHeaders(DataHeader);
        LoadObjectData(creatureData, nullptr);
        _encounterProgress = 0;
        _barrelCount = 0;
        _attemptsCount = 0;

        _initialFlamesSet.clear();
        _finalFlamesSet.clear();
        _prisonersSet.clear();
        _events.Reset();
    }

    void OnPlayerEnter(Player* player) override
    {
        auto const& players = instance->GetPlayers();
        if (players.getSize() == 1)
            CleanupInstance();

        EnsureGridLoaded();

        if (_encounterProgress < ENCOUNTER_PROGRESS_BARRELS)
            player->SendUpdateWorldState(WORLD_STATE_BARRELS_PLANTED, _barrelCount);
    }

    void CleanupInstance()
    {
        if (_encounterProgress == ENCOUNTER_PROGRESS_NONE)
            return;

        _events.ScheduleEvent(EVENT_INITIAL_BARRELS_FLAME, 0);
        _events.ScheduleEvent(EVENT_FINAL_BARRELS_FLAME, 0);

        if (_encounterProgress == ENCOUNTER_PROGRESS_BARRELS)
            _events.ScheduleEvent(EVENT_SUMMON_LIEUTENANT, 0);
        else
            SetData(DATA_THRALL_REPOSITION, 2);
    }

    void OnCreatureCreate(Creature* creature) override
    {
        switch (creature->GetEntry())
        {
            case NPC_THRALL:
                if (_encounterProgress == ENCOUNTER_PROGRESS_FINISHED)
                    creature->SetVisible(false);
                else
                    Reposition(creature);
                break;
            case NPC_ORC_PRISONER:
                _prisonersSet.emplace(creature->GetGUID());
                break;
            case NPC_TARETHA:
                if (_encounterProgress == ENCOUNTER_PROGRESS_FINISHED)
                    creature->SetVisible(false);
                break;
            case NPC_SKARLOC_MOUNT:
                creature->SetImmuneToAll(true);
                break;
        }

        InstanceScript::OnCreatureCreate(creature);
    }

    void OnGameObjectCreate(GameObject* go) override
    {
        switch (go->GetEntry())
        {
            case GO_BARREL:
                if (_encounterProgress >= ENCOUNTER_PROGRESS_BARRELS)
                    go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                break;
            case GO_PRISON_DOOR:
                if (_encounterProgress >= ENCOUNTER_PROGRESS_THRALL_ARMORED)
                    go->SetGoState(GO_STATE_ACTIVE);
                break;
            case GO_ROARING_FLAME:
                // Xinef: hack in DB to distinguish final / initial flames
                if (go->GetPhaseMask() & 0x2)
                    _finalFlamesSet.emplace(go->GetGUID());
                else
                    _initialFlamesSet.emplace(go->GetGUID());
                break;
            default:
                break;
        }

        InstanceScript::OnGameObjectCreate(go);
    }

    void SetData(uint32 type, uint32 data) override
    {
        switch (type)
        {
            case DATA_THRALL_REPOSITION:
                if (data > 1)
                    _events.ScheduleEvent(EVENT_THRALL_REPOSITION, data == 2 ? 0s : 10s);
                else if (auto thrall = GetCreature(DATA_THRALL))
                    Reposition(thrall);
                return;
            case DATA_ESCORT_PROGRESS:
                if (data > _encounterProgress)
                {
                    _encounterProgress = data;
                    SaveToDB();
                }
                break;
            case DATA_BOMBS_PLACED:
                if (_barrelCount >= 5 || _encounterProgress > ENCOUNTER_PROGRESS_NONE)
                    return;

                DoUpdateWorldState(WORLD_STATE_BARRELS_PLANTED, ++_barrelCount);
                if (_barrelCount == 5)
                {
                    _events.ScheduleEvent(EVENT_INITIAL_BARRELS_FLAME, 4s);
                    _events.ScheduleEvent(EVENT_FINAL_BARRELS_FLAME, 12s);
                    _events.ScheduleEvent(EVENT_SUMMON_LIEUTENANT, 18s);
                }
                break;
            case DATA_THRALL_ADD_FLAG:
                if (auto thrall = GetCreature(DATA_THRALL))
                    thrall->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                break;
            default:
                break;
        }
    }

    uint32 GetData(uint32 data) const override
    {
        if (data == DATA_ESCORT_PROGRESS)
            return _encounterProgress;
        else if (data == DATA_ATTEMPTS_COUNT)
            return _attemptsCount;
        return 0;
    }

    void Update(uint32 diff) override
    {
        _events.Update(diff);

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_INITIAL_BARRELS_FLAME:
                    for (auto const& pos : instancePositions)
                        instance->LoadGrid(pos.GetPositionX(), pos.GetPositionY());

                    for (auto const guid : _prisonersSet)
                    {
                        if (auto orc = instance->GetCreature(guid))
                        {
                            uint8 index = orc->GetDistance(instancePositions[0]) < 80.0f ? 0 : 1;
                            auto pos(instancePositions[index]);
                            orc->MovePosition(pos, frand(1.0f, 3.0f) + 15.0f * static_cast<float>(rand_norm()), static_cast<float>(rand_norm()) * static_cast<float>(2 * M_PI));
                            orc->GetMotionMaster()->MovePoint(1, pos);
                            orc->SetStandState(UNIT_STAND_STATE_STAND);
                        }
                    }

                    for (auto const guid : _initialFlamesSet)
                    {
                        if (auto go = instance->GetGameObject(guid))
                        {
                            go->SetRespawnTime(0);
                            go->UpdateObjectVisibility(true);
                        }
                    }
                    break;
                case EVENT_FINAL_BARRELS_FLAME:
                    for (auto const& pos : instancePositions)
                        instance->LoadGrid(pos.GetPositionX(), pos.GetPositionY());

                    if (_encounterProgress == ENCOUNTER_PROGRESS_NONE)
                    {
                        auto const& players = instance->GetPlayers();
                        for (auto const& ref : players)
                            if (auto player = ref.GetSource())
                                player->KilledMonsterCredit(NPC_LODGE_QUEST_TRIGGER, 0);
                    }

                    for (auto const guid : _finalFlamesSet)
                    {
                        if (auto go = instance->GetGameObject(guid))
                        {
                            go->SetRespawnTime(0);
                            go->UpdateObjectVisibility(true);
                        }
                    }

                    for (auto const guid : _prisonersSet)
                        if (auto orc = instance->GetCreature(guid))
                            if (!urand(0, 4))
                                orc->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);

                    SetData(DATA_ESCORT_PROGRESS, ENCOUNTER_PROGRESS_BARRELS);
                    DoUpdateWorldState(WORLD_STATE_BARRELS_PLANTED, 0);
                    break;
                case EVENT_SUMMON_LIEUTENANT:
                    instance->LoadGrid(instancePositions[2].GetPositionX(), instancePositions[2].GetPositionY());
                    if (auto drake = instance->SummonCreature(NPC_LIEUTENANT_DRAKE, instancePositions[2]))
                        if (drake->IsAIEnabled)
                            drake->AI()->Talk(0);
                    break;
                case EVENT_THRALL_REPOSITION:
                    if (auto thrall = GetCreature(DATA_THRALL))
                    {
                        if (!thrall->IsAlive())
                        {
                            ++_attemptsCount;
                            EnsureGridLoaded();
                            thrall->SetVisible(false);
                            Reposition(thrall);
                            thrall->setDeathState(DEAD);
                            thrall->Respawn();
                            thrall->SetVisible(true);
                            SaveToDB();
                        }
                        else if (thrall->IsAIEnabled)
                            thrall->AI()->Reset();
                    }
                    break;
                default:
                    break;
            }
        }
    }

    void Reposition(Creature* thrall) const
    {
        switch (auto data = GetData(DATA_ESCORT_PROGRESS))
        {
            case ENCOUNTER_PROGRESS_THRALL_ARMORED:
            case ENCOUNTER_PROGRESS_AMBUSHES_1:
            case ENCOUNTER_PROGRESS_SKARLOC_KILLED:
            case ENCOUNTER_PROGRESS_TARREN_MILL:
            case ENCOUNTER_PROGRESS_TARETHA_MEET:
                thrall->UpdatePosition(thrallPositions[data - ENCOUNTER_PROGRESS_THRALL_ARMORED], true);
                thrall->SetHomePosition(thrallPositions[data - ENCOUNTER_PROGRESS_THRALL_ARMORED]);
                thrall->SetFacingTo(thrallPositions[data - ENCOUNTER_PROGRESS_THRALL_ARMORED].GetOrientation());
                break;
            default:
                break;
        }
    }

    void EnsureGridLoaded() const
    {
        for (auto const& pos : thrallPositions)
            instance->LoadGrid(pos.GetPositionX(), pos.GetPositionY());
    }

    void WriteSaveDataMore(std::ostringstream& data) override
    {
        data << _encounterProgress << ' ' << _attemptsCount;
    }

    void ReadSaveDataMore(std::istringstream& data) override
    {
        data >> _encounterProgress;
        data >> _attemptsCount;
    }

    private:
        uint32 _encounterProgress, _barrelCount, _attemptsCount;
        std::unordered_set<uint64> _initialFlamesSet, _finalFlamesSet, _prisonersSet;
        EventMap _events;
};

void AddSC_instance_old_hillsbrad()
{
    new InstanceMapScriptLoader<instance_old_hillsbrad_InstanceMapScript>("instance_old_hillsbrad", 560);
}
