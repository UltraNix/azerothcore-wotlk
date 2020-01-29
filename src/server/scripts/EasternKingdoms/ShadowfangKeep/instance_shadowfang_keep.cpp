/*
 * Copyright (C) 2018-2019 Sunwell <https://sunwell.pl/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptedCreature.h"
#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "shadowfang_keep.h"
#include "TemporarySummon.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "SpellScript.h"

ObjectData const creatureData[] =
{
    { NPC_HORDE_ESCORT   , DATA_HORDE_ESCORT    },
    { NPC_ALLIANCE_ESCORT, DATA_ALLIANCE_ESCORT },
    { NPC_ARCHMAGE_ARUGAL, BOSS_ARUGAL          },
    { NPC_FENRUS         , BOSS_FENRUS          },
    { 0                  , 0                    } // END
};

ObjectData const gameObjectData[] =
{
    { GO_HORDE_LEVER     , DATA_HORDE_LEVER     },
    { GO_ALLIANCE_LEVER  , DATA_ALLIANCE_LEVER  },
    { GO_COURTYARD_DOOR  , DATA_COURTYARD_DOOR  },
    { GO_SORCERER_DOOR   , DATA_SORCERER_DOOR   },
    { 0                  , 0                    } // END
};

DoorData const doorData[] =
{
    { GO_ARUGAL_DOOR  , BOSS_NANDOS, DOOR_TYPE_PASSAGE  },
    { 0               , 0          , DOOR_TYPE_ROOM     } // END
};

struct instance_shadowfang_keep_InstanceMapScript : public InstanceScript
{
    instance_shadowfang_keep_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetHeaders(DataHeader);
        SetBossNumber(MAX_ENCOUNTERS);
        LoadDoorData(doorData);
        LoadObjectData(creatureData, gameObjectData);
        _courtyardDone = false;
        _fenrusGateOpen = false;
        _voidwalkerCount = 0;
    }

    void OnCreatureCreate(Creature* creature) override
    {
        switch (creature->GetEntry())
        {
            case NPC_HORDE_ESCORT:
            case NPC_ALLIANCE_ESCORT:
                if (sWorld->getBoolConfig(CONFIG_CROSSFACTION_RDF))
                {
                    creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    creature->setFaction(31);
                }
                break;
            case NPC_ARUGAL_VOIDWALKER:
                _voidwalkers.emplace_back(creature->GetGUID());
                break;
            case NPC_FENRUS:
                if (GetBossState(BOSS_FENRUS) == DONE && !_fenrusGateOpen)
                {
                    _fenrusGateOpen = true;
                    if (GameObject* door = GetGameObject(DATA_SORCERER_DOOR))
                        HandleGameObject(0, true, door);
                }

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
            case GO_HORDE_LEVER:
            case GO_ALLIANCE_LEVER:
            {
                TeamId team = GetTeamIdOfPlayers(sWorld->getBoolConfig(CONFIG_CROSSFACTION_RDF));
                if (GetBossState(BOSS_RETHILGORE) == DONE)
                    if ((team == TEAM_HORDE && go->GetEntry() == GO_HORDE_LEVER) || (team == TEAM_ALLIANCE && go->GetEntry() == GO_ALLIANCE_LEVER))
                        go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                break;
            }
            case GO_COURTYARD_DOOR:
                HandleGameObject(0, _courtyardDone, go);
                break;
            case GO_SORCERER_DOOR:
                HandleGameObject(0, _fenrusGateOpen, go);
                break;
            default:
                break;
        }

        InstanceScript::OnGameObjectCreate(go);
    }

    void SetData(uint32 type, uint32 /*data*/) override
    {
        switch (type)
        {
            case DATA_COURTYARD:
                _courtyardDone = true;
                if (GameObject* door = GetGameObject(DATA_COURTYARD_DOOR))
                    HandleGameObject(0, true, door);
                SaveToDB();
                break;
            case DATA_VOIDWALKER_EVENT:
                _events.ScheduleEvent(EVENT_ARUGAL_FENRUS, 0s);
                break;
            case DATA_VOIDWALKER_DIES:
                if (++_voidwalkerCount == 4)
                {
                    _fenrusGateOpen = true;
                    if (GameObject* door = GetGameObject(DATA_SORCERER_DOOR))
                        HandleGameObject(0, true, door);
                }

                break;
            default:
                break;
        }
    }

    uint32 GetData(uint32 type) const override
    {
        if (type == DATA_COURTYARD)
            return _courtyardDone;
        return 0;
    }

    TeamId GetTeamIdOfPlayers(bool crossFaction)
    {
        if (crossFaction)
        {
            uint32 hordePlayers = 0;
            uint32 alliancePlayers = 0;
            for (auto const& ref : instance->GetPlayers())
                if (Player* player = ref.GetSource())
                {
                    switch (player->GetTeamId())
                    {
                        case TEAM_ALLIANCE:
                            ++alliancePlayers;
                            break;
                        case TEAM_HORDE:
                            ++hordePlayers;
                            break;
                        default:
                            break;
                    }
                }

            if (hordePlayers == alliancePlayers)
                return RAND(TEAM_HORDE, TEAM_ALLIANCE);
            else
                return hordePlayers > alliancePlayers ? TEAM_HORDE : TEAM_ALLIANCE;
        }

        for (auto const& ref : instance->GetPlayers())
            if (Player* player = ref.GetSource())
                return player->GetTeamId();

        return TEAM_NEUTRAL;
    }

    bool SetBossState(uint32 type, EncounterState state) override
    {
        if (!InstanceScript::SetBossState(type, state))
            return false;

        if (type == BOSS_RETHILGORE && state == DONE)
        {
            if (Creature* horde = GetCreature(DATA_HORDE_ESCORT))
                if (horde->IsAIEnabled)
                    horde->AI()->Talk(4);

            _events.ScheduleEvent(EVENT_TALK_ALLIANCE, 4s);

            TeamId team = GetTeamIdOfPlayers(sWorld->getBoolConfig(CONFIG_CROSSFACTION_RDF));
            if (GameObject* lever = GetGameObject(team == TEAM_HORDE ? DATA_HORDE_LEVER : DATA_ALLIANCE_LEVER))
                lever->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);

            return true;
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
                case EVENT_ARUGAL_FENRUS:
                    if (Creature* archmage = GetCreature(BOSS_ARUGAL))
                    {
                        if (Creature* summon = archmage->SummonCreature(archmage->GetEntry(), { -138.640f, 2170.159f, 136.577f, 2.737f }, TEMPSUMMON_TIMED_DESPAWN, 10000))
                        {
                            summon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            summon->SetReactState(REACT_DEFENSIVE);
                            if (summon->IsAIEnabled)
                            {
                                summon->AI()->DoCast(summon, 15742, true); // visual spawn
                                summon->AI()->Talk(0);
                            }

                            _events.ScheduleEvent(EVENT_ARUGAL_FENRUS_SPAWN, 4s);
                        }
                    }
                    break;
                case EVENT_ARUGAL_FENRUS_SPAWN:
                    if (Creature* archmage = GetCreature(BOSS_ARUGAL))
                        archmage->SummonCreatureGroup(0);
                    break;
                case EVENT_TALK_ALLIANCE:
                    if (Creature* alliance = GetCreature(DATA_ALLIANCE_ESCORT))
                        if (alliance->IsAIEnabled)
                            alliance->AI()->Talk(4);
                    break;
                default:
                    break;
            }
        }
    }

    void WriteSaveDataMore(std::ostringstream& data) override
    {
        data << _courtyardDone << ' ' << _fenrusGateOpen;
    }

    void ReadSaveDataMore(std::istringstream& data) override
    {
        data >> _courtyardDone;
        data >> _fenrusGateOpen;
    }

    private:
        bool _courtyardDone;
        bool _fenrusGateOpen;
        EventMap _events;
        uint32 _voidwalkerCount;
        std::vector<uint64> _voidwalkers;
};

void AddSC_instance_shadowfang_keep()
{
    new InstanceMapScriptLoader<instance_shadowfang_keep_InstanceMapScript>("instance_shadowfang_keep", 33);
}
