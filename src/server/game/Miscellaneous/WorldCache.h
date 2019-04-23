#include "Common.h"

#pragma once

class WorldCache
{
public:
    static WorldCache& GetInstance();

    void Initialize();
    std::vector<uint32> & GetAurasToResetAfterDuel();

private:
    WorldCache() { }

    //! get auras from config that ought to be checked and removed when duel starts
    void LoadDuelResetAuras();

    std::vector<uint32> _duelResetSpellIDs;

protected:
    WorldCache(WorldCache const&)               = delete;
    WorldCache(WorldCache &&)                   = delete;
    WorldCache& operator=(WorldCache const&)    = delete;
    WorldCache& operator=(WorldCache &&)        = delete;
};
