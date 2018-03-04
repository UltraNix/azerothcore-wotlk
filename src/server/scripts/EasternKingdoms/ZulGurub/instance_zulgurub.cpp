/*
 * Copyright (C)
 * Copyright (C)
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

/* ScriptData
SDName: Instance_ZulGurub
SD%Complete: 80
SDComment: Missing reset function after killing a boss for Ohgan, Thekal.
SDCategory: Zul'Gurub
EndScriptData */

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "zulgurub.h"
#include "GameObjectAI.h"

#include <array>

DoorData const doorData[] =
{
    { GO_FORCEFIELD, DATA_ARLOKK, DOOR_TYPE_ROOM, BOUNDARY_NONE },
    { 0,             0,           DOOR_TYPE_ROOM, BOUNDARY_NONE } // END
};

class instance_zulgurub : public InstanceMapScript
{
    public: instance_zulgurub(): InstanceMapScript(ZGScriptName, 309) { }

        struct instance_zulgurub_InstanceMapScript : public InstanceScript
        {
            instance_zulgurub_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                SetBossNumber(EncounterCount);
                LoadDoorData(doorData);
            }

            void Initialize() override
            {
                _zealotLorkhanGUID = 0;
                _zealotZathGUID = 0;
                _highPriestTekalGUID = 0;
                _jindoTheHexxerGUID = 0;
                _vilebranchSpeakerGUID = 0;
                _arlokkGUID = 0;
                _goGongOfBethekkGUID = 0;
            }

            bool IsEncounterInProgress() const override
            {
                // not active in Zul'Gurub
                return false;
            }

            void OnCreatureCreate(Creature* creature) override
            {
                switch (creature->GetEntry())
                {
                    case NPC_ZEALOT_LORKHAN:
                        _zealotLorkhanGUID = creature->GetGUID();
                        break;
                    case NPC_ZEALOT_ZATH:
                        _zealotZathGUID = creature->GetGUID();
                        break;
                    case NPC_HIGH_PRIEST_THEKAL:
                        _highPriestTekalGUID = creature->GetGUID();
                        break;
                    case NPC_JINDO_THE_HEXXER:
                        _jindoTheHexxerGUID = creature->GetGUID();
                        break;
                    case NPC_VILEBRANCH_SPEAKER:
                        _vilebranchSpeakerGUID = creature->GetGUID();
                        break;
                    case NPC_ARLOKK:
                        _arlokkGUID = creature->GetGUID();
                        break;
                }
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_FORCEFIELD:
                        AddDoor(go, true);
                        break;
                    case GO_GONG_OF_BETHEKK:
                        _goGongOfBethekkGUID = go->GetGUID();
                        if (GetBossState(DATA_ARLOKK) == DONE)
                            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                        else
                            go->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_FORCEFIELD:
                        AddDoor(go, false);
                        break;
                    default:
                        break;
                }
            }

            uint64 GetData64(uint32 uiData) const
            {
                switch (uiData)
                {
                    case DATA_LORKHAN:
                        return _zealotLorkhanGUID;
                        break;
                    case DATA_ZATH:
                        return _zealotZathGUID;
                        break;
                    case DATA_THEKAL:
                        return _highPriestTekalGUID;
                        break;
                    case DATA_JINDO:
                        return _jindoTheHexxerGUID;
                        break;
                    case NPC_ARLOKK:
                        return _arlokkGUID;
                        break;
                    case GO_GONG_OF_BETHEKK:
                        return _goGongOfBethekkGUID;
                        break;
                }
                return 0;
            }

            std::string GetSaveData() override
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "Z G " << GetBossSaveData();

                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(const char* str) override
            {
                if (!str)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(str);

                char dataHead1, dataHead2;

                std::istringstream loadStream(str);
                loadStream >> dataHead1 >> dataHead2;

                if (dataHead1 == 'Z' && dataHead2 == 'G')
                {
                    for (uint32 i = 0; i < EncounterCount; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;
                        SetBossState(i, EncounterState(tmpState));
                    }
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
        private:
            //If all High Priest bosses were killed. Lorkhan, Zath and Ohgan are added too.
            //Storing Lorkhan, Zath and Thekal because we need to cast on them later. Jindo is needed for healfunction too.

            uint64 _zealotLorkhanGUID;
            uint64 _zealotZathGUID;
            uint64 _highPriestTekalGUID;
            uint64 _jindoTheHexxerGUID;
            uint64 _vilebranchSpeakerGUID;
            uint64 _arlokkGUID;
            uint64 _goGongOfBethekkGUID;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_zulgurub_InstanceMapScript(map);
        }
};

/* Edge of Madness */
enum EdgeOfMadnessMisc
{
    SPELL_RED_LIGHTNING = 24240,

    EVENT_RENATAKI      = 29,
    EVENT_WUSH          = 30,
    EVENT_GRILEK        = 27,
    EVENT_HAZZA         = 28,

    EVENT_MAP_ONE       = 1,
    EVENT_MAP_TWO       = 2,
    EVENT_MAP_THREE     = 3
};

std::array<uint32, 4> eventIds =
{
    EVENT_RENATAKI,
    EVENT_WUSH,
    EVENT_GRILEK,
    EVENT_HAZZA
};

Position airPortalPos = { -11890.91f, -1901.96f, 70.49f };
Position spawnBossPos = { -11893.74f, -1902.78f, 65.14f, 0.84f };

class go_brazzier_of_madness : public GameObjectScript
{
public:
    go_brazzier_of_madness() : GameObjectScript("go_brazzier_of_madness") { }

    struct go_brazzier_of_madness_AI : public GameObjectAI
    {
        go_brazzier_of_madness_AI(GameObject* go) : GameObjectAI(go)
        {
            instance = go->GetInstanceScript();
            airGUID = 0;
            fireGUID = 0;
            soundGUID = 0;
            bossEntry = 0;
            events.Reset();
        }

        void OnStateChanged(uint32 /*state*/, Unit* /*stateChanger*/) override
        {
            if (!instance)
            {
                std::cout << "nie weszlo 1\n";
                return;
            }

            if (instance->GetData(DATA_EDGE_OF_MADNESS) == DONE)
            {
                std::cout << "nie weszlo 1\n";
                return;
            }

            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
            uint32 eventActive = 0;
            for (auto i : eventIds)
            {
                if (sGameEventMgr->IsActiveEvent(i))
                {
                    eventActive = i;
                    break;
                }
            }

            std::cout << "eventActive: " << eventActive << std::endl;
            switch (eventActive)
            {
                case EVENT_RENATAKI:
                    bossEntry = NPC_EDGE_RENE;
                    break;
                case EVENT_WUSH:
                    bossEntry = NPC_EDGE_WUSH;
                    break;
                case EVENT_GRILEK:
                    bossEntry = NPC_EDGE_GRILEK;
                    break;
                case EVENT_HAZZA:
                    bossEntry = NPC_EDGE_GRILEK;
                    break;
                default:
                    break;
            }

            events.ScheduleEvent(EVENT_MAP_ONE, 1s);
        }

        void UpdateAI(uint32 diff) override
        {
            if (!instance)
                return;

            events.Update(diff);

            while (uint32 eventid = events.ExecuteEvent())
            {
                switch (eventid)
                {
                    case EVENT_MAP_ONE:
                        if (GameObject* air = go->SummonGameObject(GO_TROLL_AIR_PORTAL, airPortalPos.GetPositionX(), airPortalPos.GetPositionY(), airPortalPos.GetPositionZ(), 0.93f, 0, 0, 0, 0, 0))
                            airGUID = air->GetGUID();

                        if (GameObject* fire = go->SummonGameObject(GO_TROLL_FIRE_PORTAL, airPortalPos.GetPositionX(), airPortalPos.GetPositionY(), airPortalPos.GetPositionZ(), 0.93f, 0, 0, 0, 0, 0))
                            fireGUID = fire->GetGUID();

                        if (GameObject* sound = go->SummonGameObject(GO_TROLL_SOUND_PORTAL, airPortalPos.GetPositionX(), airPortalPos.GetPositionY(), airPortalPos.GetPositionZ(), 0.93f, 0, 0, 0, 0, 0))
                            soundGUID = sound->GetGUID();

                        events.ScheduleEvent(EVENT_MAP_TWO, 8s);
                        break;
                    case EVENT_MAP_TWO:
                        if (!bossEntry)
                            break;

                        if (Creature* boss = instance->instance->SummonCreature(bossEntry, spawnBossPos))
                            boss->AI()->DoCast(SPELL_RED_LIGHTNING);

                        if (GameObject* air = ObjectAccessor::GetGameObject(*go, airGUID))
                            air->Delete();

                        if (GameObject* fire = ObjectAccessor::GetGameObject(*go, fireGUID))
                            fire->Delete();

                        if (GameObject* sound = ObjectAccessor::GetGameObject(*go, soundGUID))
                            sound->Delete();
                        break;
                    default:
                        break;
                }
            }
        }

    private:
        InstanceScript * instance;
        EventMap events;
        uint64 airGUID;
        uint64 fireGUID;
        uint64 soundGUID;
        uint32 bossEntry;
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_brazzier_of_madness_AI(go);
    }
};

void AddSC_instance_zulgurub()
{
    new instance_zulgurub();

    new go_brazzier_of_madness();
}
