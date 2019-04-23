#include "WorldCache.h"
#include "Config.h"

WorldCache& WorldCache::GetInstance()
{
    static WorldCache instance;

    return instance;
}

void WorldCache::Initialize()
{
    //! ToDo: cache bunch of other stuff
    uint32 oldMSTime = getMSTime();

    LoadDuelResetAuras();

    sLog->outString(">> Loaded World Cache in %u ms", GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

std::vector<uint32> & WorldCache::GetAurasToResetAfterDuel()
{
    return _duelResetSpellIDs;
}

void WorldCache::LoadDuelResetAuras()
{
    std::string spellListId = sConfigMgr->GetStringDefault("DuelResetSpellIds", "");
    if (!spellListId.empty())
    {
        Tokenizer toks (spellListId, ';');
        for (auto && token : toks)
            _duelResetSpellIDs.push_back(atoi(token));
    }
}
