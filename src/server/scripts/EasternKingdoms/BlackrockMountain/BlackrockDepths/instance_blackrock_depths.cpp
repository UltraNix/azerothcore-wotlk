/*
 * Copyright (C)
 * Copyright (C)
 *
 * This program is free software; you + redistribute it and/or modify it
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
#include "blackrock_depths.h"
#include "Group.h"
#include "Hellforge/hellforge.hpp"

#define TIMER_TOMBOFTHESEVEN    15000
#define MAX_ENCOUNTER           6

enum Creatures
{
    NPC_EMPEROR             = 9019,
    NPC_PHALANX             = 9502,
    NPC_ANGERREL            = 9035,
    NPC_DOPEREL             = 9040,
    NPC_HATEREL             = 9034,
    NPC_VILEREL             = 9036,
    NPC_SEETHREL            = 9038,
    NPC_GLOOMREL            = 9037,
    NPC_DOOMREL             = 9039,
    NPC_MAGMUS              = 9938,
    NPC_MOIRA               = 8929,
    NPC_ROCKNOT             = 9503,

    NPC_WATCHMAN_DOOMGRIP   = 9476
};

enum GameObjects
{
    GO_ARENA1               = 161525,
    GO_ARENA2               = 161522,
    GO_ARENA3               = 161524,
    GO_ARENA4               = 161523,
    GO_SHADOW_LOCK          = 161460,
    GO_SHADOW_MECHANISM     = 161461,
    GO_SHADOW_GIANT_DOOR    = 157923,
    GO_SHADOW_DUMMY         = 161516,
    GO_BAR_KEG_SHOT         = 170607,
    GO_BAR_KEG_TRAP         = 171941,
    GO_BAR_DOOR             = 170571,
    GO_TOMB_ENTER           = 170576,
    GO_TOMB_EXIT            = 170577,
    GO_LYCEUM               = 170558,
    GO_SF_N                 = 174745, // Shadowforge Brazier North
    GO_SF_S                 = 174744, // Shadowforge Brazier South
    GO_GOLEM_ROOM_N         = 170573, // Magmus door North
    GO_GOLEM_ROOM_S         = 170574, // Magmus door Soutsh
    GO_THRONE_ROOM          = 170575, // Throne door
    GO_SPECTRAL_CHALICE     = 164869,
    GO_CHEST_SEVEN          = 169243
};

//! this is only used for hellforge at the moment
ObjectData const creatureData[] =
{
    { NPC_BOSS_ONE,         DATA_BOSS_ONE       },
    { NPC_BOSS_TWO,         DATA_BOSS_TWO       },
    { NPC_BOSS_THREE,       DATA_BOSS_THREE     },
    { NPC_BOSS_FOUR,        DATA_BOSS_FOUR      },
    { NPC_BOSS_FIVE,        DATA_BOSS_FIVE      },
    { NPC_WANDENER,         DATA_NPC_WANDERER   },
    { NPC_WANDERER_CHAMPION,DATA_NPC_WANDERER_CHAMPION },
    { NPC_GAUNTLET_CONTROLLER, DATA_GAUNTLET_CONTROLLER },
    { NPC_CHAMPION_COCCON,  DATA_NPC_CHAMPION_COCCON},
    {NPC_TRASH_HELLFORGE_DEFENDER, DATA_NPC_TRASH_HELLFORGE_DEFENDER},
    { 0,                    0                   }
};

ObjectData const gameobjectData[] =
{
    { GO_BOSS_TWO_CAGE,     DATA_GO_BOSS_TWO_CAGE       },
    { GO_HELLFORGE_GATE_1,  DATA_GO_GAUNTLET_DOORS      },
    { GO_HELLFORGE_GATE_2,  DATA_GO_GAUNTLET_DOORS2     },
    { GO_HELLFORGE_GATE_8,  DATA_GO_FIRST_BOSS_ENTRANCE },
    { 0,                0                               }
};

DoorData const doorData[] =
{
    { GO_HELLFORGE_GATE_3,  DATA_BOSS_FOUR,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_HELLFORGE_GATE_4,  DATA_BOSS_FIVE,     DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_GATE_5,  DATA_BOSS_FOUR,     DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_GATE_6,  DATA_BOSS_THREE,    DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_HELLFORGE_GATE_7,  DATA_BOSS_THREE,    DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    //{ GO_HELLFORGE_GATE_8,  DATA_BOSS_ONE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_GATE_9,  DATA_BOSS_ONE,      DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_HELLFORGE_GATE_10, DATA_BOSS_ONE,      DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_BOSS_FOUR_STONES,  DATA_BOSS_FOUR,     DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { GO_HELLFORGE_SIGN_0, DATA_BOSS_FIVE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_SIGN_1, DATA_BOSS_FIVE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_SIGN_2, DATA_BOSS_FIVE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_SIGN_3, DATA_BOSS_FIVE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_SIGN_4, DATA_BOSS_FIVE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_SIGN_5, DATA_BOSS_FIVE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_SIGN_6, DATA_BOSS_FIVE,      DOOR_TYPE_ROOM,     BOUNDARY_NONE },
    { GO_HELLFORGE_GATE_11,DATA_BOSS_FIVE,      DOOR_TYPE_PASSAGE,  BOUNDARY_NONE },
    { 0,             0,                         DOOR_TYPE_ROOM,     BOUNDARY_NONE } // END
};

class instance_blackrock_depths : public InstanceMapScript
{
public:
    instance_blackrock_depths() : InstanceMapScript("instance_blackrock_depths", 230) { }

    struct instance_blackrock_depths_InstanceMapScript : public InstanceScript
    {
        instance_blackrock_depths_InstanceMapScript(Map* map) : InstanceScript(map) { }

        void Initialize()
        {
            /* Hellforge */
            SetBossNumber(HELLFORGE_BOSS_COUNT);

            //! Load hellforge boss states
            LoadObjectData(creatureData, gameobjectData);
            LoadDoorData(doorData);

            memset(&encounter, 0, sizeof(encounter));
            EmperorGUID = 0;
            PhalanxGUID = 0;
            MagmusGUID = 0;
            MoiraGUID = 0;
            RocknotGUID = 0;

            GoArena1GUID = 0;
            GoArena2GUID = 0;
            GoArena3GUID = 0;
            GoArena4GUID = 0;
            GoShadowLockGUID = 0;
            GoShadowMechGUID = 0;
            GoShadowGiantGUID = 0;
            GoShadowDummyGUID = 0;
            GoBarKegGUID = 0;
            GoBarKegTrapGUID = 0;
            GoBarDoorGUID = 0;
            GoTombEnterGUID = 0;
            GoTombExitGUID = 0;
            GoLyceumGUID = 0;
            GoSFSGUID = 0;
            GoSFNGUID = 0;
            GoGolemNGUID = 0;
            GoGolemSGUID = 0;
            GoThroneGUID = 0;
            GoChestGUID = 0;
            GoSpectralChaliceGUID = 0;

            BarAleCount = 0;
            GhostKillCount = 0;
            TombEventStarterGUID = 0;
            TombTimer = TIMER_TOMBOFTHESEVEN;
            TombEventCounter = 0;
            OpenedCoofers = 0;

            for (uint8 i = 0; i < 7; ++i)
                TombBossGUIDs[i] = 0;

            _hellforgeGauntletState = false;
            _hellforgeFirstRoomTrashCount = 0;
            _hellforgeSnakeRoomTrashCount = 0;
            _hellforgeDwarfRoomTrashCount = 0;
        }

        void OnCreatureCreate(Creature* creature) override
        {
            InstanceScript::OnCreatureCreate(creature);
            if ((creature->IsDungeonBoss() || creature->isWorldBoss()) && creature->GetEntry() >= NPC_BOSS_ONE)
                creature->SetCanMissSpells(false);

            switch (creature->GetEntry())
            {
                case NPC_EMPEROR: EmperorGUID = creature->GetGUID(); break;
                case NPC_PHALANX: PhalanxGUID = creature->GetGUID(); break;
                case NPC_MOIRA: MoiraGUID = creature->GetGUID(); break;
                case NPC_ROCKNOT: RocknotGUID = creature->GetGUID(); break;
                case NPC_DOOMREL: TombBossGUIDs[0] = creature->GetGUID(); break;
                case NPC_DOPEREL: TombBossGUIDs[1] = creature->GetGUID(); break;
                case NPC_HATEREL: TombBossGUIDs[2] = creature->GetGUID(); break;
                case NPC_VILEREL: TombBossGUIDs[3] = creature->GetGUID(); break;
                case NPC_SEETHREL: TombBossGUIDs[4] = creature->GetGUID(); break;
                case NPC_GLOOMREL: TombBossGUIDs[5] = creature->GetGUID(); break;
                case NPC_ANGERREL: TombBossGUIDs[6] = creature->GetGUID(); break;
                case NPC_MAGMUS:
                    MagmusGUID = creature->GetGUID();
                    if (!creature->IsAlive())
                        HandleGameObject(GetData64(DATA_THRONE_DOOR), true); // if Magmus is dead open door to last boss
                    break;
                case NPC_TRASH_HELLFORGE_BERSERKER:
                case NPC_TRASH_HELLFORGE_ADHERENT:
                case NPC_TRASH_UNLIVING_DRUID:
                case NPC_TRASH_HELLFORGE_FALLEN_FANATIC:
                case NPC_TRASH_HELLFORGE_WITCH_DOCTOR:
                case NPC_TRASH_HELLFORGE_CHAMPION:
                case NPC_TRASH_HELLFORGE_PRIEST:
                case NPC_TRASH_HELLFORGE_KNIGHT:
                case NPC_TRASH_HELLFORGE_SPY:
                    if (!creature->IsAlive())
                        break;
                    if (IsInFirstRoom(creature))
                        ++_hellforgeFirstRoomTrashCount;
                    else if (IsInSnakeRoom(creature))
                        ++_hellforgeSnakeRoomTrashCount;
                    else if (IsInDwarfRoom(creature))
                        ++_hellforgeDwarfRoomTrashCount;
                    break;
            }
        }

        void OnUnitDeath(Unit* unit) override
        {
            Creature* creature = unit->ToCreature();
            if (!creature)
                return;

            switch (creature->GetEntry())
            {
            case NPC_TRASH_HELLFORGE_BERSERKER:
            case NPC_TRASH_HELLFORGE_ADHERENT:
            case NPC_TRASH_UNLIVING_DRUID:
            case NPC_TRASH_HELLFORGE_FALLEN_FANATIC:
            case NPC_TRASH_HELLFORGE_WITCH_DOCTOR:
            case NPC_TRASH_HELLFORGE_CHAMPION:
            case NPC_TRASH_HELLFORGE_PRIEST:
            case NPC_TRASH_HELLFORGE_KNIGHT:
            case NPC_TRASH_HELLFORGE_SPY:
                if (IsInFirstRoom(creature))
                {
                    if (!_hellforgeFirstRoomTrashCount)
                        break;
                    if (--_hellforgeFirstRoomTrashCount == 0)
                    {
                        if (Creature * wanderer = GetCreature(DATA_NPC_WANDERER))
                            if (wanderer->IsAIEnabled)
                                wanderer->GetAI()->DoAction(ACTION_KILLED_TRASH);
                    }
                }
                else if (IsInSnakeRoom(creature))
                {
                    if (!_hellforgeSnakeRoomTrashCount)
                        break;
                    if (--_hellforgeSnakeRoomTrashCount == 0)
                    {
                        if (Creature * defender = GetCreature(DATA_NPC_TRASH_HELLFORGE_DEFENDER))
                            if (defender->IsAIEnabled)
                                defender->GetAI()->DoAction(ACTION_SHOW_COCCON);
                        if (Creature * coccon = GetCreature(DATA_NPC_CHAMPION_COCCON))
                            if (coccon->IsAIEnabled)
                                coccon->GetAI()->DoAction(ACTION_SHOW_COCCON);
                    }
                }
                else if (IsInDwarfRoom(creature) && _hellforgeDwarfRoomTrashCount)
                {
                    if (--_hellforgeDwarfRoomTrashCount == 0)
                        if (Creature * dwarf = GetCreature(DATA_BOSS_FOUR))
                            dwarf->MonsterYell("What is going on here?!", LANG_UNIVERSAL, dwarf);
                }
                break;
            }
        }

        bool CheckRequiredBosses(uint32 bossId, Player const* /*player*/) const override
        {
            switch (bossId)
            {
                case DATA_BOSS_TWO:
                    return GetBossState(DATA_BOSS_ONE) == DONE;
                case DATA_BOSS_THREE:
                    return GetBossState(DATA_BOSS_TWO) == DONE;
                case DATA_BOSS_FOUR:
                    return GetBossState(DATA_BOSS_THREE) == DONE;
                case DATA_BOSS_FIVE:
                    return GetBossState(DATA_BOSS_FOUR) == DONE && _hellforgeGauntletState;
            }

            return true;
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            InstanceScript::OnGameObjectCreate(go);
            switch (go->GetEntry())
            {
                case GO_ARENA1: GoArena1GUID = go->GetGUID(); break;
                case GO_ARENA2: GoArena2GUID = go->GetGUID(); break;
                case GO_ARENA3: GoArena3GUID = go->GetGUID(); break;
                case GO_ARENA4: GoArena4GUID = go->GetGUID(); break;
                case GO_SHADOW_LOCK: GoShadowLockGUID = go->GetGUID(); break;
                case GO_SHADOW_MECHANISM: GoShadowMechGUID = go->GetGUID(); break;
                case GO_SHADOW_GIANT_DOOR: GoShadowGiantGUID = go->GetGUID(); break;
                case GO_SHADOW_DUMMY: GoShadowDummyGUID = go->GetGUID(); break;
                case GO_BAR_KEG_SHOT: GoBarKegGUID = go->GetGUID(); break;
                case GO_BAR_KEG_TRAP: GoBarKegTrapGUID = go->GetGUID(); break;
                case GO_BAR_DOOR: GoBarDoorGUID = go->GetGUID(); break;
                case GO_TOMB_ENTER: GoTombEnterGUID = go->GetGUID(); break;
                case GO_TOMB_EXIT:
                    GoTombExitGUID = go->GetGUID();
                    if (GhostKillCount >= 7)
                        HandleGameObject(0, true, go);
                    else
                        HandleGameObject(0, false, go);
                    break;
                case GO_LYCEUM:
                    GoLyceumGUID = go->GetGUID();
                    if (instance->IsHeroic() && GetBossState(DATA_BOSS_THREE) != DONE)
                        HandleGameObject(0, false, go);
                    break;
                case GO_SF_S: GoSFSGUID = go->GetGUID(); break;
                case GO_SF_N: GoSFNGUID = go->GetGUID(); break;
                case GO_GOLEM_ROOM_N: GoGolemNGUID = go->GetGUID(); break;
                case GO_GOLEM_ROOM_S: GoGolemSGUID = go->GetGUID(); break;
                case GO_THRONE_ROOM: GoThroneGUID = go->GetGUID(); break;
                case GO_CHEST_SEVEN: GoChestGUID = go->GetGUID(); break;
                case GO_SPECTRAL_CHALICE: GoSpectralChaliceGUID = go->GetGUID(); break;
                    /*hellforge*/
                case GO_HELLFORGE_GATE_1:
                case GO_HELLFORGE_GATE_2:
                {
                    if (_hellforgeGauntletState)
                        go->SetGoState(GO_STATE_ACTIVE);
                    break;
                }
                case GO_HELLFORGE_GATE_8:
                    if (GetBossState(DATA_BOSS_ONE) == DONE)
                        HandleGameObject(0, true, go);
                    break;
                default:
                    break;
            }

            if (go->GetEntry() >= GO_HELLFORGE_GATE_1 && go->GetEntry() < (GO_HELLFORGE_GATE_1 + MAX_HELLFORGE_GATES))
            {
                //! but exclude gauntlet doors, they do not belong to any boss
                if (go->GetEntry() != GO_HELLFORGE_GATE_1  && go->GetEntry() != GO_HELLFORGE_GATE_2)
                    AddDoor(go, true);
            }
        }

        void OnPlayerEnter(Player* player) override
        {
            if (player && player->GetGroup() && player->GetGroup()->isLFGGroup())
                if (GameObject* doors = instance->GetGameObject(GoLyceumGUID))
                    HandleGameObject(0, true, doors);
        }

        bool SetBossState(uint32 type, EncounterState state) override
        {
            if (!InstanceScript::SetBossState(type, state))
                return false;

            SaveBRD();
            return true;
        }

        void SetData64(uint32 type, uint64 data) override
        {
            switch (type)
            {
                case DATA_EVENSTARTER:
                    TombEventStarterGUID = data;
                    if (!TombEventStarterGUID)
                        TombOfSevenReset();//reset
                    else
                        TombOfSevenStart();//start
                    break;
                case DATA_REVIVE_TRASH:
                    HandleTrashRevive(data);
                    break;
            }
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
                case TYPE_RING_OF_LAW:
                    encounter[0] = data;
                    break;
                case TYPE_VAULT:
                    encounter[1] = data;
                    break;
                case TYPE_BAR:
                    if (data == SPECIAL)
                        ++BarAleCount;
                    else
                        encounter[2] = data;
                    break;
                case TYPE_TOMB_OF_SEVEN:
                    encounter[3] = data;
                    break;
                case TYPE_LYCEUM:
                    encounter[4] = data;
                    break;
                case TYPE_IRON_HALL:
                    encounter[5] = data;
                    break;
                case DATA_GHOSTKILL:
                    GhostKillCount += data;
                    break;
                case DATA_OPEN_COFFER_DOORS:
                {
                    OpenedCoofers += 1;
                    if (OpenedCoofers == 12)
                    {
                        Position pos = { 812.15f, -348.91f, -50.579f, 0.7f };
                        if (TempSummon* summon = instance->SummonCreature(NPC_WATCHMAN_DOOMGRIP, pos))
                            summon->SetTempSummonType(TEMPSUMMON_MANUAL_DESPAWN);
                    }
                    break;
                }
                case DATA_HELLFORGE_GAUNTLET_DONE:
                {
                    _hellforgeGauntletState = true;
                    break;
                }
                default:
                    break;
            }

            if (data == DONE || GhostKillCount >= 7)
                SaveBRD();
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
                case TYPE_RING_OF_LAW:
                    return encounter[0];
                case TYPE_VAULT:
                    return encounter[1];
                case TYPE_BAR:
                    if (encounter[2] == IN_PROGRESS && BarAleCount == 3)
                        return SPECIAL;
                    else
                        return encounter[2];
                case TYPE_TOMB_OF_SEVEN:
                    return encounter[3];
                case TYPE_LYCEUM:
                    return encounter[4];
                case TYPE_IRON_HALL:
                    return encounter[5];
                case DATA_GHOSTKILL:
                    return GhostKillCount;
                case DATA_GET_HELLFORGE_GAUNTLET_STATE:
                    return _hellforgeGauntletState;
                case DATA_GET_HELLFORGE_FIRST_ROOM_TRASH_COUNT:
                    return _hellforgeFirstRoomTrashCount;
                case DATA_GET_HELLFORGE_SNAKE_ROOM_TRASH_COUNT:
                    return _hellforgeSnakeRoomTrashCount;
                case DATA_GET_HELLFORGE_DWARF_ROOM_TRASH_COUNT:
                    return _hellforgeDwarfRoomTrashCount;
            }
            return 0;
        }

        uint64 GetData64(uint32 data) const override
        {
            switch (data)
            {
                case DATA_EMPEROR:
                    return EmperorGUID;
                case DATA_PHALANX:
                    return PhalanxGUID;
                case DATA_MOIRA:
                    return MoiraGUID;
                case DATA_ROCKNOT:
                    return RocknotGUID;
                case DATA_ARENA1:
                    return GoArena1GUID;
                case DATA_ARENA2:
                    return GoArena2GUID;
                case DATA_ARENA3:
                    return GoArena3GUID;
                case DATA_ARENA4:
                    return GoArena4GUID;
                case DATA_GO_BAR_KEG:
                    return GoBarKegGUID;
                case DATA_GO_BAR_KEG_TRAP:
                    return GoBarKegTrapGUID;
                case DATA_GO_BAR_DOOR:
                    return GoBarDoorGUID;
                case DATA_EVENSTARTER:
                    return TombEventStarterGUID;
                case DATA_SF_BRAZIER_N:
                    return GoSFNGUID;
                case DATA_SF_BRAZIER_S:
                    return GoSFSGUID;
                case DATA_THRONE_DOOR:
                    return GoThroneGUID;
                case DATA_GOLEM_DOOR_N:
                    return GoGolemNGUID;
                case DATA_GOLEM_DOOR_S:
                    return GoGolemSGUID;
                case DATA_GO_CHALICE:
                    return GoSpectralChaliceGUID;
            }
            return 0;
        }

        void TombOfSevenEvent()
        {
            if (GhostKillCount < 7 && TombBossGUIDs[TombEventCounter])
            {
                if (Creature* boss = instance->GetCreature(TombBossGUIDs[TombEventCounter]))
                {
                    boss->setFaction(FACTION_HOSTILE);
                    boss->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
                    if (Unit* target = boss->SelectNearestTarget(500))
                        boss->AI()->AttackStart(target);
                }
            }
        }

        void Update(uint32 diff) override
        {
            if (TombEventStarterGUID && GhostKillCount < 7)
            {
                if (TombTimer <= diff)
                {
                    TombTimer = TIMER_TOMBOFTHESEVEN;
                    ++TombEventCounter;
                    TombOfSevenEvent();
                    // Check Killed bosses
                    for (uint8 i = 0; i < 7; ++i)
                    {
                        if (Creature* boss = instance->GetCreature(TombBossGUIDs[i]))
                        {
                            if (!boss->IsAlive())
                            {
                                GhostKillCount = i + 1;
                            }
                        }
                    }
                }
                else TombTimer -= diff;
            }
            if (GhostKillCount >= 7 && TombEventStarterGUID)
                TombOfSevenEnd();
        }

        std::string GetSaveData() override
        {
            return str_data;
        }

        void SaveBRD()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << encounter[0] << ' ' << encounter[1] << ' ' << encounter[2] << ' '
                << encounter[3] << ' ' << encounter[4] << ' ' << encounter[5] << ' ' << GhostKillCount << ' ' << GetBossSaveData() /*<< ' '*/ << _hellforgeGauntletState;

            str_data = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }

        void Load(const char* in) override
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            std::istringstream loadStream(in);
            loadStream >> encounter[0] >> encounter[1] >> encounter[2] >> encounter[3]
                >> encounter[4] >> encounter[5] >> GhostKillCount;

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (encounter[i] == IN_PROGRESS)
                    encounter[i] = NOT_STARTED;
            if (GhostKillCount > 0 && GhostKillCount < 7)
                GhostKillCount = 0;//reset tomb of seven event
            if (GhostKillCount >= 7)
                GhostKillCount = 7;

            for (uint32 i = 0; i < HELLFORGE_BOSS_COUNT; ++i)
            {
                uint32 tmpState;
                loadStream >> tmpState;
                if (tmpState == IN_PROGRESS || tmpState == FAIL || tmpState == SPECIAL)
                    tmpState = NOT_STARTED;

                if (tmpState < TO_BE_DECIDED)
                    SetBossState(i, EncounterState(tmpState));
            }

            loadStream >> _hellforgeGauntletState;

            // Load grids at Wanderer's and Champion's spawn positions to be sure that their states are loaded correctly even if no one is near them (for example after server crash)
            instance->LoadGrid(1380.31f, -824.81f);
            instance->LoadGrid(1380.47f, -386.52f);

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void TombOfSevenReset()
        {
            HandleGameObject(GoTombExitGUID, false);//event reseted, close exit door
            HandleGameObject(GoTombEnterGUID, true);//event reseted, open entrance door
            for (uint8 i = 0; i < 7; ++i)
            {
                if (Creature* boss = instance->GetCreature(TombBossGUIDs[i]))
                {
                    if (!boss->IsAlive())
                    {//do not call EnterEvadeMode(), it will create infinite loops
                        boss->Respawn();
                        boss->RemoveAllAuras();
                        boss->DeleteThreatList();
                        boss->CombatStop(true);
                        boss->LoadCreaturesAddon(true);
                        boss->GetMotionMaster()->MoveTargetedHome();
                        boss->SetLootRecipient(NULL);
                    }
                    boss->setFaction(FACTION_FRIEND);
                }
            }
            GhostKillCount = 0;
            TombEventStarterGUID = 0;
            TombEventCounter = 0;
            TombTimer = TIMER_TOMBOFTHESEVEN;
            SetData(TYPE_TOMB_OF_SEVEN, NOT_STARTED);
        }

        void TombOfSevenStart()
        {
            HandleGameObject(GoTombExitGUID, false);//event started, close exit door
            HandleGameObject(GoTombEnterGUID, false);//event started, close entrance door
            SetData(TYPE_TOMB_OF_SEVEN, IN_PROGRESS);
        }

        void TombOfSevenEnd()
        {
            DoRespawnGameObject(GoChestGUID, DAY);
            HandleGameObject(GoTombExitGUID, true);//event done, open exit door
            HandleGameObject(GoTombEnterGUID, true);//event done, open entrance door
            TombEventStarterGUID = 0;
            SetData(TYPE_TOMB_OF_SEVEN, DONE);
        }

        bool IsInFirstRoom(Creature* creature) const
        {
            Position pos = creature->GetHomePosition();
            return (pos.GetPositionX() > 1331.85f && pos.GetPositionX() < 1429.27f && pos.GetPositionY() < -719.09f && pos.GetPositionY() > -810.85f);
        }

        bool IsInSnakeRoom(Creature* creature) const
        {
            Position pos = creature->GetHomePosition();
            return (pos.GetPositionX() > 1291.16f && pos.GetPositionX() < 1475.46f && pos.GetPositionY() < -334.28f && pos.GetPositionY() > -551.90f);
        }

        bool IsInDwarfRoom(Creature* creature) const
        {
            Position pos = creature->GetHomePosition();
            return (pos.GetPositionX() > 1073.69f && pos.GetPositionX() < 1199.39f && pos.GetPositionY() < -112.59f && pos.GetPositionY() > -225.46f);
        }

        void HandleTrashRevive(uint64 guid)
        {
            Unit* unit = sObjectAccessor->FindUnit(guid);
            if (!unit || !unit->IsCreature())
                return;

            Creature* creature = unit->ToCreature();
            switch (unit->GetEntry())
            {
                case NPC_TRASH_HELLFORGE_BERSERKER:
                case NPC_TRASH_HELLFORGE_ADHERENT:
                case NPC_TRASH_UNLIVING_DRUID:
                case NPC_TRASH_HELLFORGE_FALLEN_FANATIC:
                case NPC_TRASH_HELLFORGE_WITCH_DOCTOR:
                case NPC_TRASH_HELLFORGE_CHAMPION:
                case NPC_TRASH_HELLFORGE_PRIEST:
                case NPC_TRASH_HELLFORGE_KNIGHT:
                case NPC_TRASH_HELLFORGE_SPY:
                    if (!creature->IsAlive())
                        break;
                    if (IsInFirstRoom(creature))
                        ++_hellforgeFirstRoomTrashCount;
                    else if (IsInSnakeRoom(creature))
                        ++_hellforgeSnakeRoomTrashCount;
                    else if (IsInDwarfRoom(creature))
                        ++_hellforgeDwarfRoomTrashCount;
                    break;
            }
        }

    private:
        uint32 encounter[MAX_ENCOUNTER];
        std::string str_data;

        uint64 EmperorGUID;
        uint64 PhalanxGUID;
        uint64 MagmusGUID;
        uint64 MoiraGUID;
        uint64 RocknotGUID;

        uint64 GoArena1GUID;
        uint64 GoArena2GUID;
        uint64 GoArena3GUID;
        uint64 GoArena4GUID;
        uint64 GoShadowLockGUID;
        uint64 GoShadowMechGUID;
        uint64 GoShadowGiantGUID;
        uint64 GoShadowDummyGUID;
        uint64 GoBarKegGUID;
        uint64 GoBarKegTrapGUID;
        uint64 GoBarDoorGUID;
        uint64 GoTombEnterGUID;
        uint64 GoTombExitGUID;
        uint64 GoLyceumGUID;
        uint64 GoSFSGUID;
        uint64 GoSFNGUID;
        uint64 GoGolemNGUID;
        uint64 GoGolemSGUID;
        uint64 GoThroneGUID;
        uint64 GoChestGUID;
        uint64 GoSpectralChaliceGUID;

        uint32 BarAleCount;
        uint32 GhostKillCount;
        uint64 TombBossGUIDs[7];
        uint64 TombEventStarterGUID;
        uint32 TombTimer;
        uint32 TombEventCounter;
        uint32 OpenedCoofers;

        bool _hellforgeGauntletState;
        uint32 _hellforgeFirstRoomTrashCount;
        uint32 _hellforgeSnakeRoomTrashCount;
        uint32 _hellforgeDwarfRoomTrashCount;
    };

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_blackrock_depths_InstanceMapScript(map);
    }
};

void AddSC_instance_blackrock_depths()
{
    new instance_blackrock_depths();
}
