/*
* Copyright (C) 2015-2015 Theatre of Dreams
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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "InstanceScript.h"
#include "old_scarlet_monastery.h"

DoorData const doorData[] =
{
    { GO_GARDEN_ENTRANCE_DOORS,         DATA_MAZIN_SOULSTEALER,     DOOR_TYPE_ROOM,     BOUNDARY_S },
    { GO_GARDEN_EXIT_DOORS,             DATA_MAZIN_SOULSTEALER,     DOOR_TYPE_PASSAGE,  BOUNDARY_N },
    { GO_HALL_OF_CHAMPIONS_ENTRANCE_1,  DATA_JAVIER_VOIDBRINGER,    DOOR_TYPE_ROOM,     BOUNDARY_S },
    { GO_HALL_OF_CHAMPIONS_ENTRANCE_2,  DATA_JAVIER_VOIDBRINGER,    DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HALL_OF_CHAMPIONS_EXIT_DOORS,  DATA_JAVIER_VOIDBRINGER,    DOOR_TYPE_PASSAGE,  BOUNDARY_N },
    { GO_BACK_ROOM_DOORS,               DATA_REAST,                 DOOR_TYPE_ROOM,     BOUNDARY_N },
    { GO_MAIN_HALL_DOORS,               DATA_REAST,                 DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_CATHEDRAL_DOORS,               DATA_MADANTUL_RADA,         DOOR_TYPE_ROOM,     BOUNDARY_W },
    { GO_COURTYARD_DOORS,               DATA_MADANTUL_RADA,         DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_CATHEDRAL_DOORS,               DATA_DESSEMBRAE,            DOOR_TYPE_ROOM,     BOUNDARY_W },
};

class instance_old_scarlet_monastery : public InstanceMapScript
{
    public:
        instance_old_scarlet_monastery() : InstanceMapScript("instance_old_scarlet_monastery", 44) { }

        struct instance_old_scarlet_monastery_InstanceMapScript : public InstanceScript
        {
            instance_old_scarlet_monastery_InstanceMapScript(InstanceMap* map) : InstanceScript(map)
            {
                SetBossNumber(EncounterCount);
                LoadDoorData(doorData);
                javierVoidbringerGUID = 0;
                soulstealerGUID = 0;
                thrallGUID = 0;
                sylvanasGUID = 0;
                kelthuzadGUID = 0;
                backHallDoorsGUID = 0;
                devalethKilled = false;
                reastGUID = 0;
                madanGUID = 0;
                dessembraeGUID = 0;
                devalethGUID = 0;
                resetTimer = 2000;
            }

            void OnPlayerEnter(Player* player) override
            {
                // 15% ICC buff
                //player->AddAura(player->GetTeamId() == TEAM_ALLIANCE ? 73825 : 73819, player);
            }

            void OnCreatureCreate(Creature* creature) override
            {
                switch (creature->GetEntry())
                {
                    case NPC_JAVIER_VOIDBRINGER:
                        javierVoidbringerGUID = creature->GetGUID();
                        break;
                    case NPC_MAZIN_SOULSTEALER:
                        soulstealerGUID = creature->GetGUID();
                        break;
                    case NPC_SOUL_THRALL:
                        thrallGUID = creature->GetGUID();
                        break;
                    case NPC_SOUL_SYLVANAS:
                        sylvanasGUID = creature->GetGUID();
                        break;
                    case NPC_SOUL_KELTHUZAD:
                        kelthuzadGUID = creature->GetGUID();
                        break;
                    case NPC_REAST:
                        reastGUID = creature->GetGUID();
                        break;
                    case NPC_MADANTUL_RADA:
                        madanGUID = creature->GetGUID();
                        break;
                    case NPC_DESSEMBRAE:
                        dessembraeGUID = creature->GetGUID();
                        break;
                    case NPC_DEVALETH:
                        devalethGUID = creature->GetGUID();
                        break;
                    default:
                        break;
                }
            }

            bool IsResurrectionPrevented() override
            {
                if (GetBossState(DATA_DEVALETH) == IN_PROGRESS)
                    return true;

                return false;
            }

            void OnCreatureRemove(Creature* creature) override
            {
            }

            void OnGameObjectCreate(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_GARDEN_ENTRANCE_DOORS:
                    case GO_GARDEN_EXIT_DOORS:
                    case GO_HALL_OF_CHAMPIONS_ENTRANCE_1:
                    case GO_HALL_OF_CHAMPIONS_ENTRANCE_2:
                    case GO_HALL_OF_CHAMPIONS_EXIT_DOORS:
                    case GO_BACK_ROOM_DOORS:
                    case GO_MAIN_HALL_DOORS:
                    case GO_COURTYARD_DOORS:
                    case GO_CATHEDRAL_DOORS:
                        AddDoor(go, true);
                        break;
                    case GO_GARDEN_SECRET_DOORS:
                        gardenDoorsGUID = go->GetGUID();
                        break;
                    case GO_BACK_HALL_DOORS:
                        backHallDoorsGUID = go->GetGUID();
                        if (devalethKilled)
                            HandleGameObject(0, true, go);
                        break;
                    case GO_ENTRANCE_DOORS:
                        if (go->GetPositionY() < 0.0f)
                            go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_INTERACT_COND);
                        break;
                    default:
                        break;
                }
            }

            void OnGameObjectRemove(GameObject* go) override
            {
                switch (go->GetEntry())
                {
                    case GO_GARDEN_ENTRANCE_DOORS:
                    case GO_GARDEN_EXIT_DOORS:
                    case GO_HALL_OF_CHAMPIONS_ENTRANCE_1:
                    case GO_HALL_OF_CHAMPIONS_ENTRANCE_2:
                    case GO_HALL_OF_CHAMPIONS_EXIT_DOORS:
                    case GO_BACK_ROOM_DOORS:
                    case GO_MAIN_HALL_DOORS:
                    case GO_COURTYARD_DOORS:
                    case GO_CATHEDRAL_DOORS:
                        AddDoor(go, false);
                        break;
                    default:
                        break;
                }
            }

            void OnUnitDeath(Unit* unit) override { }

            uint64 GetData64(uint32 type) const override
            {
                switch (type)
                {
                    case DATA_JAVIER_VOIDBRINGER:
                        return javierVoidbringerGUID;
                    case DATA_MAZIN_SOULSTEALER:
                        return soulstealerGUID;
                    case NPC_SOUL_THRALL:
                        return thrallGUID;
                    case NPC_SOUL_SYLVANAS:
                        return sylvanasGUID;
                    case NPC_SOUL_KELTHUZAD:
                        return kelthuzadGUID;
                    case GO_GARDEN_SECRET_DOORS:
                        return gardenDoorsGUID;
                    case GO_BACK_HALL_DOORS:
                        return backHallDoorsGUID;
                    case DATA_REAST:
                        return reastGUID;
                    case DATA_MADANTUL_RADA:
                        return madanGUID;
                    case DATA_DESSEMBRAE:
                        return dessembraeGUID;
                    default:
                        break;
                }
                return 0;
            }

            bool SetBossState(uint32 type, EncounterState state) override
            {
                if (!InstanceScript::SetBossState(type, state))
                    return false;

                switch (type)
                {
                    case DATA_MAZIN_SOULSTEALER:
                        if (state == DONE || state == NOT_STARTED)
                            HandleGameObject(gardenDoorsGUID, false);
                        break;
                    case DATA_DEVALETH:
                        if (state == DONE)
                            HandleGameObject(backHallDoorsGUID, true);
                        break;
                    default:
                        break;
                }
                return true;
            }

            void SetData(uint32 type, uint32 data) override
            {
                switch (type)
                {
                    case DATA_DEVALETH_DEATH:
                        devalethKilled = true;
                        HandleGameObject(backHallDoorsGUID, true);
                        break;
                    default:
                        break;
                }
            }

            bool CheckRequiredBosses(uint32 bossId, Player const* player = NULL) const override
            {
                switch (bossId)
                {
                        // without breaks!
                    case DATA_DESSEMBRAE:
                        if (GetBossState(DATA_MADANTUL_RADA) != DONE)
                            return false;
                    case DATA_MADANTUL_RADA:
                        if (GetBossState(DATA_REAST) != DONE)
                            return false;
                    case DATA_REAST:
                        if (GetBossState(DATA_JAVIER_VOIDBRINGER) != DONE)
                            return false;
                    case DATA_JAVIER_VOIDBRINGER:
                        if (GetBossState(DATA_MAZIN_SOULSTEALER) != DONE)
                            return false;
                    case DATA_MAZIN_SOULSTEALER:
                        return true;
                }
                return true;
            }

            std::string GetSaveData() override
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "O S M " << GetBossSaveData() << ' ' << devalethKilled;
                OUT_SAVE_INST_DATA_COMPLETE;
                return saveStream.str();
            }

            void Load(char const* str) override
            {
                if (!str)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(str);

                char dataHead1, dataHead2, dataHead3;

                std::istringstream loadStream(str);
                loadStream >> dataHead1 >> dataHead2 >> dataHead3;

                if (dataHead1 == 'O' && dataHead2 == 'S' && dataHead3 == 'M')
                {
                    for (uint8 i = 0; i < EncounterCount; ++i)
                    {
                        uint32 tmpState;
                        loadStream >> tmpState;
                        if (tmpState == IN_PROGRESS || tmpState > SPECIAL)
                            tmpState = NOT_STARTED;

                        SetBossState(i, EncounterState(tmpState));
                    }
                    loadStream >> devalethKilled;
                }
                else
                    OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }

            void Update(uint32 diff) override
            {
                if (resetTimer <= diff)
                {
                    for (uint32 i = 0; i < EncounterCount; ++i)
                        if (GetBossState(i) == IN_PROGRESS)
                            if (!instance->GetPlayersCountExceptGMs())
                                if (Creature* boss = instance->GetCreature(GetData64(i)))
                                    boss->AI()->EnterEvadeMode();
                    resetTimer = 2000;
                }
                else resetTimer -= diff;
            }

        protected:
            uint64 javierVoidbringerGUID;
            uint64 soulstealerGUID;
            uint64 thrallGUID;
            uint64 sylvanasGUID;
            uint64 kelthuzadGUID;
            uint64 gardenDoorsGUID;
            uint64 backHallDoorsGUID;
            uint64 reastGUID;
            uint64 madanGUID;
            uint64 dessembraeGUID;
            uint64 devalethGUID;
            bool devalethKilled;
            uint32 resetTimer;
        };

        InstanceScript* GetInstanceScript(InstanceMap* map) const override
        {
            return new instance_old_scarlet_monastery_InstanceMapScript(map);
        }
};

void AddSC_instance_old_scarlet_monastery()
{
    new instance_old_scarlet_monastery();
}