#include "WorldCache.h"
#include "Config.h"

WorldCache& WorldCache::GetInstance()
{
    static WorldCache instance;

    return instance;
}

std::vector<uint32> & WorldCache::GetAurasToResetAfterDuel()
{
    return _duelResetSpellIDs;
}

void WorldCache::LoadDuelResetAuras()
{
    uint32 oldMSTime = getMSTime();

    std::string spellListId = sConfigMgr->GetStringDefault("DuelResetSpellIds", "");
    if (!spellListId.empty())
    {
        Tokenizer toks (spellListId, ';');
        for (auto && token : toks)
            _duelResetSpellIDs.push_back(atoi(token));
    }

    sLog->outString(">> Loaded duel reset auras in %u ms", GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void WorldCache::LoadHellforgeBossValues()
{
    uint32 oldMSTime = getMSTime();
    _hellforgeStatValues.clear();

    auto* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_HELLFORGE_STAT);
    auto result = WorldDatabase.Query(stmt);

    if (!result)
    {
        sLog->outString(">> Loaded 0 hellforge boss stats. DB table hellforge_boss_stats is empty!");
        sLog->outString();
        return;
    }

    do
    {
        Field* field = result->Fetch();
        uint32 statId = field[0].GetUInt32();

        HellforgeStatValues val;
        val.StatValue = field[1].GetUInt32();
        val.StatVariance = field[2].GetFloat();

        _hellforgeStatValues[statId] = val;
    } while (result->NextRow());

    sLog->outString(">> Loaded hellforge boss value stats in %u ms", GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void WorldCache::GetStatValue(uint32 statId, HellforgeStatValues& stat)
{
    auto itr = _hellforgeStatValues.find(statId);
    if (itr == _hellforgeStatValues.end())
        return;

    stat = itr->second;
}

HellforgeStats WorldCache::GetStatValues(std::vector<uint32> _statIds)
{
    HellforgeStats _tempUMap;
    for (auto && id : _statIds)
    {
        auto iterator = _hellforgeStatValues.find(id);
        if (iterator == _hellforgeStatValues.end())
        {
            sLog->outError("WorldCache::GetStatValues called with an id (%d) that doesnt exist in _hellforgeStatValues", id);
            ASSERT(false);
            break;
        }

        _tempUMap[id] = iterator->second;
    }

    return _tempUMap;
}

