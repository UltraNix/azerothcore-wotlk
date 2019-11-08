#pragma once

#include "Common.h"

enum WardenLuaCheckType : uint32
{
    WARDEN_LUA_PONG                 = 1,
    WARDEN_LUA_TRAP,
    //! clean client will always answer
    //! unlocked client will not answer
    WARDEN_LUA_PONG_2,
    //! send before everything else
    WARDEN_LUA_FRAME_CREATION,
    WARDEN_LUA_ADDON_SENDER_CREATION,

    MAX_WARDEN_LUA_TYPES
};

struct WardenLuaCheck
{
    uint32 _checkId = 0;
    std::string _luaCode = "";
    WardenLuaCheckType _checkType = MAX_WARDEN_LUA_TYPES;
    std::string _description = "";
    std::string _falsePositiveProbability = "";
};
using WardenLuaStore = std::unordered_map<uint32 /*checkId*/, WardenLuaCheck /*struct*/>;

struct HellforgeStatValues
{
    uint32 StatValue;
    float StatVariance;
};
using HellforgeStats = std::unordered_map<uint32, HellforgeStatValues>;

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
private:
    WorldCache() { }

    std::vector<uint32> _duelResetSpellIDs;
    HellforgeStats _hellforgeStatValues;

    WardenLuaStore _wardenLuaChecksPool;
    std::vector<uint32> _wardenLuaCheckIDs;
    std::vector<uint32> _wardenLuaMandatoryCheckIDs;

protected:
    WorldCache(WorldCache const&)               = delete;
    WorldCache(WorldCache &&)                   = delete;
    WorldCache& operator=(WorldCache const&)    = delete;
    WorldCache& operator=(WorldCache &&)        = delete;
};

#define sWorldCache WorldCache::GetInstance()
