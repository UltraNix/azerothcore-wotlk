#include "Common.h"

#pragma once

struct HellforgeStatValues
{
    uint32 StatValue;
    float StatVariance;
};

typedef std::unordered_map<uint32, HellforgeStatValues> HellforgeStats;

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

private:
    WorldCache() { }

    std::vector<uint32> _duelResetSpellIDs;
    HellforgeStats _hellforgeStatValues;

protected:
    WorldCache(WorldCache const&)               = delete;
    WorldCache(WorldCache &&)                   = delete;
    WorldCache& operator=(WorldCache const&)    = delete;
    WorldCache& operator=(WorldCache &&)        = delete;
};

#define sWorldCache WorldCache::GetInstance()
