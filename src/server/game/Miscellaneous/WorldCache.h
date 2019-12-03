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

constexpr uint32 MIN_FISH_CAUGHT_REQUIRED{ 20 };
using FishingTimeStamp = std::chrono::time_point<std::chrono::steady_clock>;
using FishingClock = std::chrono::steady_clock;
struct FishingPlayerEntry
{
private:
    uint32 fishCaughtSoFar = 0;
public:
    FishingTimeStamp firstCaughtFishTime;
    FishingTimeStamp lastCaughtFishTime;
    void IncrementFishCaught() { ++fishCaughtSoFar; }
    uint32 GetTotalFishCaught() const { return fishCaughtSoFar; }
    void SetFishCaughtSoFar(uint32 val) { fishCaughtSoFar = val; }
};
using PlayersFishingStore = std::unordered_map<uint64, FishingPlayerEntry>;

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
    bool CanRelayLuaResult(uint32 checkId);
    void ReloadLuaResultDisables();

    /** Currently fishing listing **/
    void AddOrUpdateFishingList(uint64 guid);
    void ListCurrentFishers(ChatHandler* /*hadnler*/);

    /** Generic **/
    void OnWorldUpdate(uint32 diff);

    void LoadBossRecordAllowedMaps();
    bool CanAnnounceBossRecordForMap(uint32 mapId) const;
private:
    WorldCache();

    //! Misc
    std::vector<uint32> _duelResetSpellIDs;
    HellforgeStats _hellforgeStatValues;
    PlayersFishingStore _playersCurrentlyFishing;
    void UpdateFishingList();

    //! Warden lua
    WardenLuaStore _wardenLuaChecksPool;
    std::vector<uint32> _disabledRelayCheckIDs;
    std::vector<uint32> _wardenLuaCheckIDs;
    std::vector<uint32> _wardenLuaMandatoryCheckIDs;
    std::set<uint32>    _bossRecordsAllowedMaps;

    TaskScheduler scheduler;
    bool _isFisherListLocked;

protected:
    WorldCache(WorldCache const&)               = delete;
    WorldCache(WorldCache &&)                   = delete;
    WorldCache& operator=(WorldCache const&)    = delete;
    WorldCache& operator=(WorldCache &&)        = delete;
};

#define sWorldCache WorldCache::GetInstance()
