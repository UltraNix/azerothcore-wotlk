#include "WorldCache.h"
#include "Config.h"

#include "Containers.h"

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

void WorldCache::LoadWardenLuaChecks()
{
    uint32 oldMSTime = getMSTime();

    auto* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_WARDEN_LUA_CHECKS);
    auto result = WorldDatabase.Query(stmt);

    if (!result)
    {
        sLog->outString(">> Loaded 0 warden lua checks. Table is empty!");
        sLog->outString();
        return;
    }

    do
    {
        WardenLuaCheck check;
        Field* field = result->Fetch();
        uint32 checkId = field[0].GetUInt32();
        check._checkId = checkId;
        check._luaCode = field[1].GetString();
        WardenLuaCheckType _type = static_cast<WardenLuaCheckType>(field[2].GetUInt32());
        check._checkType = _type;
        check._description = field[3].GetString();
        check._falsePositiveProbability = field[4].GetString();

        if (_type == WARDEN_LUA_FRAME_CREATION || _type == WARDEN_LUA_ADDON_SENDER_CREATION)
            _wardenLuaMandatoryCheckIDs.push_back(checkId);
        else
            _wardenLuaCheckIDs.push_back(checkId);

        _wardenLuaChecksPool[checkId] = std::move(check);
    } while (result->NextRow());

    sLog->outString(">> Loaded warden lua checks in %u ms", GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

WardenLuaCheck const* WorldCache::GetWardenCheckFor(uint32 const& checkId)
{
    auto const itr = _wardenLuaChecksPool.find(checkId);
    return itr != _wardenLuaChecksPool.end() ? &itr->second : nullptr;
}

std::vector<uint32> WorldCache::GetLuaCheckIDs(bool mandatory)
{
    if (mandatory)
        return _wardenLuaMandatoryCheckIDs;

    return _wardenLuaCheckIDs;
}
