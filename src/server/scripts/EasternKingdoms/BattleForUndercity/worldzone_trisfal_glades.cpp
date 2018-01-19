
#include "CreatureGroups.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "battle_for_undercity.h"

class worldzone_trisfal_glades : public WorldMapZoneScript
{
    public:
        worldzone_trisfal_glades() : WorldMapZoneScript("worldzone_trisfal_glades") { }

        struct worldzone_trisfal_glades_WorldMapZoneScript : public WorldZoneScript
        {
            worldzone_trisfal_glades_WorldMapZoneScript() : WorldZoneScript() { }

            bool Preparing[2];
            bool BattleTimerState[2];
            uint32 BattleTimer[2];
            bool StartBattle[2];
            bool BattleFor[MAX_BATTLING_AREAS];
            bool Secured[MAX_BATTLING_AREAS];
            bool ResetBattle;
            uint32 ResetTimer;

            uint64 JainaGUID;
            uint64 SylvanasGUID;
            uint64 WaveTriggerGUID;

            std::list<uint64> AllianceSpawns;

            void Initialize() 
            {
                for (uint8 i = 0; i < MAX_BATTLING_AREAS; ++i)
                {
                    BattleFor[i] = false;
                    Secured[i] = false;

                    if (i > 1)
                        continue;

                    Preparing[i] = true;
                    StartBattle[i] = false;
                    BattleTimerState[i] = false;
                    BattleTimer[i] = 0;
                }

                ResetBattle     = false;
                ResetTimer      = 0;

                JainaGUID       = 0;
                SylvanasGUID    = 0;
                WaveTriggerGUID = 0;

                AllianceSpawns.clear();
            }

            void OnCreatureCreate(Creature* creature) 
            {
                switch (creature->GetEntry())
                {
                    case NPC_JAINA_PROUDMORE:
                        JainaGUID = creature->GetGUID();
                        break;
                    case NPC_SYLVANAS:
                        SylvanasGUID = creature->GetGUID();
                        creature->Mount(10719);
                        break;
                    case NPC_WAVES_TRIGGER:
                        WaveTriggerGUID = creature->GetGUID();
                        break;
                    case NPC_STORMWIND_ELITE_A:
                    case NPC_ALLIANCE_SIEGE:
                        AllianceSpawns.push_back(creature->GetGUID());
                        break;
                    case NPC_FLYING_MACHINE:
                        creature->m_CombatDistance = 50.0f;
                        break;
                }
            }

            void OnUnitDeath(Unit* unit) 
            {
                if (unit->GetTypeId() != TYPEID_UNIT)
                    return;

                switch (unit->GetEntry())
                {
                    case NPC_STORMWIND_ELITE_A:
                    case NPC_ALLIANCE_SIEGE:
                        AllianceSpawns.remove(unit->GetGUID());
                        break;
                }
            }

            void FillInitialWorldStates(WorldPacket& data, Player* player) override
            {
                if (player)
                    if (player->GetTeamId() == TEAM_ALLIANCE)
                    {
                        data << uint32(WORLDSTATE_UNDERCITY_CONTROLLED_A) << uint32(Preparing[TEAM_ALLIANCE]);
                        data << uint32(WORLDSTATE_MANHUNT_TIMER_STATE) << uint32(BattleTimerState[TEAM_ALLIANCE]);
                        data << uint32(WORLDSTATE_MANHUNT_TIMER) << uint32(BattleTimer[TEAM_ALLIANCE]);
                        data << uint32(WORLDSTATE_MANHUNT_BEGUN) << uint32(StartBattle[TEAM_ALLIANCE]);
                        data << uint32(WORLDSTATE_BATTLING_SEWERS) << uint32(BattleFor[SEWERS]);
                        data << uint32(WORLDSTATE_SECURED_SEWERS) << uint32(Secured[SEWERS]);
                        data << uint32(WORLDSTATE_BATTLING_APOTHECARIUM) << uint32(BattleFor[APOTHECARIUM]);
                        data << uint32(WORLDSTATE_SECURED_APOTHECARIUM) << uint32(Secured[APOTHECARIUM]);
                    }
                    else
                    {
                        data << uint32(WORLDSTATE_UNDERCITY_CONTROLLED_H) << uint32(Preparing[TEAM_HORDE]);
                        data << uint32(WORLDSTATE_BATTLE_TIMER_STATE) << uint32(BattleTimerState[TEAM_HORDE]);
                        data << uint32(WORLDSTATE_BATTLE_TIMER) << uint32(BattleTimer[TEAM_HORDE]);
                        data << uint32(WORLDSTATE_BATTLE_BEGUN) << uint32(StartBattle[TEAM_HORDE]);
                        data << uint32(WORLDSTATE_BATTLING_COURTYARD) << uint32(BattleFor[COURTYARD]);
                        data << uint32(WORLDSTATE_CONTROLL_COURTYARD) << uint32(Secured[COURTYARD]);
                        data << uint32(WORLDSTATE_BATTLING_INNER_SANCTUM) << uint32(BattleFor[INNER_SANCTUM]);
                        data << uint32(WORLDSTATE_CONTROLL_INNER_SANCTUM) << uint32(Secured[INNER_SANCTUM]);
                        data << uint32(WORLDSTATE_BATTLING_ROYAL_QUARTER) << uint32(BattleFor[ROYAL_QUARTER]);
                        data << uint32(WORLDSTATE_CONTROLL_ROYAL_QUARTER) << uint32(Secured[ROYAL_QUARTER]);
                        data << uint32(WORLDSTATE_RESET_BATTLE) << uint32(ResetBattle);
                        data << uint32(WORLDSTATE_RESET_TIMER) << uint32(ResetTimer);
                    }
            }

            void SetData(uint32 type, uint32 data) 
            {
                switch (type)
                {
                    // Alliance
                    case WORLDSTATE_UNDERCITY_CONTROLLED_A:
                        Preparing[TEAM_ALLIANCE] = bool(data);
                        break;
                    case WORLDSTATE_MANHUNT_TIMER_STATE:
                        BattleTimerState[TEAM_ALLIANCE] = bool(data);
                        break;
                    case WORLDSTATE_MANHUNT_TIMER:
                        BattleTimer[TEAM_ALLIANCE] = data;
                        break;
                    case WORLDSTATE_MANHUNT_BEGUN:
                        StartBattle[TEAM_ALLIANCE] = bool(data);
                        break;
                    case WORLDSTATE_BATTLING_SEWERS:
                        BattleFor[SEWERS] = bool(data);
                        break;
                    case WORLDSTATE_SECURED_SEWERS:
                        Secured[SEWERS] = bool(data);
                        break;
                    case WORLDSTATE_BATTLING_APOTHECARIUM:
                        BattleFor[APOTHECARIUM] = bool(data);
                        break;
                    case WORLDSTATE_SECURED_APOTHECARIUM:
                        Secured[APOTHECARIUM] = bool(data);
                        break;

                    // Horde
                    case WORLDSTATE_UNDERCITY_CONTROLLED_H:
                        Preparing[TEAM_HORDE] = bool(data);
                        break;
                    case WORLDSTATE_BATTLE_TIMER_STATE:
                        BattleTimerState[TEAM_HORDE] = bool(data);
                        break;
                    case WORLDSTATE_BATTLE_TIMER:
                        BattleTimer[TEAM_HORDE] = data;
                        break;
                    case WORLDSTATE_BATTLE_BEGUN:
                        StartBattle[TEAM_HORDE] = bool(data);
                        break;
                    case WORLDSTATE_BATTLING_COURTYARD:
                        BattleFor[COURTYARD] = bool(data);
                        break;
                    case WORLDSTATE_CONTROLL_COURTYARD:
                        Secured[COURTYARD] = bool(data);
                        break;
                    case WORLDSTATE_BATTLING_INNER_SANCTUM:
                        BattleFor[INNER_SANCTUM] = bool(data);
                        break;
                    case WORLDSTATE_CONTROLL_INNER_SANCTUM:
                        Secured[INNER_SANCTUM] = bool(data);
                        break;
                    case WORLDSTATE_BATTLING_ROYAL_QUARTER:
                        BattleFor[ROYAL_QUARTER] = bool(data);
                        break;
                    case WORLDSTATE_CONTROLL_ROYAL_QUARTER:
                        Secured[ROYAL_QUARTER] = bool(data);
                        break;
                    case WORLDSTATE_RESET_BATTLE:
                        ResetBattle = bool(data);
                        break;
                    case WORLDSTATE_RESET_TIMER:
                        ResetTimer = data;
                        break;
                }
            }

            uint64 GetData64(uint32 data) const
            {
                switch (data)
                {
                    case DATA_JAINA:
                        return JainaGUID;
                    case DATA_SYLVANAS:
                        return SylvanasGUID;
                    case DATA_WAVES_TRIGGER:
                        return WaveTriggerGUID;
                    case DATA_GET_ENEMY:
                        return Trinity::Containers::SelectRandomContainerElement(AllianceSpawns);
                }

                return 0;
            }
        };

        WorldZoneScript* GetWorldZoneScript() const override
        {
            return new worldzone_trisfal_glades_WorldMapZoneScript();
        }
};


void AddSC_worldzone_trisfal_glades()
{
    new worldzone_trisfal_glades();
}
