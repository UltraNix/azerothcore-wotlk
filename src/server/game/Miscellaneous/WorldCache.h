#pragma once

#include "TaskScheduler.h"
#include "WardenDefines.hpp"

class ChatHandler;

struct HellforgeStatValues
{
    uint32 StatValue;
    float StatVariance;
};
using HellforgeStats = std::unordered_map<uint32, HellforgeStatValues>;

constexpr uint32 MIN_ITEMS_GATHERED_REQUIRED{ 20 };
using GatheringTimeStamp = std::chrono::time_point<std::chrono::steady_clock>;
using GatheringClock = std::chrono::steady_clock;
struct GatheringPlayerEntry
{
private:
    uint32 gatheredItemsSoFar = 0;
public:
    GatheringTimeStamp firstGatheredItemTime;
    GatheringTimeStamp lastGatheredItemTime;
    void IncrementGatheredItems() { ++gatheredItemsSoFar; }
    uint32 GetTotalGatheredItems() const { return gatheredItemsSoFar; }
    void SetGatheredItemsSoFar(uint32 val) { gatheredItemsSoFar = val; }
};
using PlayersGatheringStore = std::unordered_map<uint64, GatheringPlayerEntry>;

class WorldCache
{
public:
    static WorldCache& GetInstance();

    /*** DUEL RELATED ***/
    //! get auras from config that ought to be checked and removed when duel starts
    void LoadDuelResetAuras();
    std::vector<uint32> & GetAurasToResetAfterDuel();

    /*** HELLFORGE ***/
    //! loads various stats of bosses for custom hellforge instance (hellforge_boss_stats table in world database)
    void LoadHellforgeBossValues();
    void GetStatValue(uint32 statId, HellforgeStatValues& stat);
    HellforgeStats GetStatValues(std::vector<uint32> _statIds);

    /*** Warden related ***/
    void LoadWardenLuaChecks();
    WardenLuaCheck const* GetWardenCheckFor(uint32 const& /*id*/);
    std::vector<uint32> GetLuaCheckIDs(bool mandatory = false);
    //! checks whether relaying information to webhooks for that checkId is enabled
    bool CanRelayLuaResult(uint32 checkId) const;
    void ReloadLuaResultDisables();
    bool IsLuaCheckDisabled(uint32 checkId) const;
    void ReloadDisabledLuaChecks();

    /** Currently gathering listing **/
    void AddOrUpdateFishingList(uint64 /*guid*/);
    void ListCurrentFishers(ChatHandler* /*handler*/);

    void AddOrUpdateHerbalismList(uint64 /*guid*/);
    void ListCurrentHerbalists(ChatHandler* /*handler*/);

    void AddOrUpdateMiningList(uint64 /*guid*/);
    void ListCurrentMiners(ChatHandler* /*handler*/);

    /** Generic **/
    void OnWorldUpdate(uint32 diff);

    void LoadBossRecordAllowedMaps();
    bool CanAnnounceBossRecordForMap(uint32 mapId) const;
    bool IsWintergraspBattleActive() const;
    void SetWintergraspBattleState(bool /*active*/);
private:
    WorldCache();

    //! Misc
    std::vector<uint32> _duelResetSpellIDs;
    HellforgeStats _hellforgeStatValues;

    //! Gatherers list stuff
    PlayersGatheringStore _playersCurrentlyFishing;
    PlayersGatheringStore _playersCurrentlyHerbing;
    PlayersGatheringStore _playersCurrentlyMining;

    void AddOrUpdateGatheringList(uint64 /*guid*/, PlayersGatheringStore& /*store*/);
    void ListCurrentGatherers(ChatHandler* /*handler*/, PlayersGatheringStore& /*store*/, std::string /*gathererName*/, std::string /*itemName*/, std::string /*verb*/);
    void UpdateGatherers();
    void UpdateGatherersList(PlayersGatheringStore& /*store*/);

    //! Warden lua
    WardenLuaStore _wardenLuaChecksPool;
    std::vector<uint32> _disabledRelayCheckIDs;
    std::vector<uint32> _disabledLuaChecks;
    std::vector<uint32> _wardenLuaCheckIDs;
    std::vector<uint32> _wardenLuaMandatoryCheckIDs;
    std::set<uint32>    _bossRecordsAllowedMaps;

    TaskScheduler scheduler;
    bool _isGathererListLocked;
    bool _isWintergraspWarActive;

protected:
    WorldCache(WorldCache const&)               = delete;
    WorldCache(WorldCache &&)                   = delete;
    WorldCache& operator=(WorldCache const&)    = delete;
    WorldCache& operator=(WorldCache &&)        = delete;
};

#define sWorldCache WorldCache::GetInstance()
