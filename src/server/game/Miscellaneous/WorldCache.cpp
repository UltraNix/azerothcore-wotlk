#include "WorldCache.h"
#include "Config.h"
#include "Player.h"
#include "Containers.h"
#include "Chat.h"
#include "fmt/format.h"

#include <chrono>
#include <ctime>

WorldCache& WorldCache::GetInstance()
{
    static WorldCache instance;

    return instance;
}

WorldCache::WorldCache()
{
    _playersCurrentlyFishing.clear();
    scheduler.ClearValidator();

    scheduler.Schedule(2min, [this](TaskContext func)
    {
        UpdateFishingList();
        func.Repeat(2min);
    });
}

void WorldCache::OnWorldUpdate(uint32 diff)
{
    scheduler.Update(diff);
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
        if (!field[5].GetBool())
            _disabledRelayCheckIDs.push_back(checkId);

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

bool WorldCache::CanRelayLuaResult(uint32 checkId) const
{
    if (_disabledRelayCheckIDs.empty())
        return true;

    return std::find(_disabledRelayCheckIDs.begin(), _disabledRelayCheckIDs.end(), checkId) == _disabledRelayCheckIDs.end();
}

bool WorldCache::IsLuaCheckDisabled(uint32 checkId) const
{
    if (_disabledLuaChecks.empty())
        return false;

    return std::find(_disabledLuaChecks.begin(), _disabledLuaChecks.end(), checkId) != _disabledLuaChecks.end();
}

void WorldCache::ReloadLuaResultDisables()
{
    _disabledRelayCheckIDs.clear();
    uint32 oldMSTime = getMSTime();

    auto* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_WARDEN_LUA_CHECK_STATUS);
    auto result = WorldDatabase.Query(stmt);

    if (!result)
    {
        sLog->outString(">> Loaded 0 warden lua check statuses. Table is empty!");
        sLog->outString();
        return;
    }

    do
    {
        WardenLuaCheck check;
        Field* field = result->Fetch();
        uint32 checkId = field[0].GetUInt32();
        bool ShouldRelay = field[1].GetBool();

        if (!ShouldRelay)
            _disabledRelayCheckIDs.push_back(checkId);
    } while (result->NextRow());

    sLog->outString(">> Loaded warden lua check statuses in %u ms", GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void WorldCache::ReloadDisabledLuaChecks()
{
    _disabledLuaChecks.clear();
    uint32 oldMSTime = getMSTime();

    std::string disabledChecksString = sConfigMgr->GetStringDefault("WardenLua.DisabledChecks", "");
    if (!disabledChecksString.empty())
    {
        Tokenizer toks(disabledChecksString, ';');
        for (auto&& check : toks)
            _disabledLuaChecks.push_back(atoi(check));
    }

    sLog->outString(">> Loaded disabled lua checks in %u ms", GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void WorldCache::AddOrUpdateFishingList(uint64 guid)
{
    if (_isFisherListLocked)
        return;

    auto result = _playersCurrentlyFishing.find(guid);
    FishingPlayerEntry fishEntry;
    if (result == _playersCurrentlyFishing.end())
    {
        fishEntry.firstCaughtFishTime = FishingClock::now();
        fishEntry.lastCaughtFishTime = FishingClock::now();
    }
    else
    {
        //! we're already in the map, get fish caught so far. We will increment it by one at the end of the function
        fishEntry.SetFishCaughtSoFar(result->second.GetTotalFishCaught());
        fishEntry.firstCaughtFishTime = result->second.firstCaughtFishTime;
        fishEntry.lastCaughtFishTime = FishingClock::now();
    }

    fishEntry.IncrementFishCaught();
    _playersCurrentlyFishing[guid] = fishEntry;
};

void WorldCache::ListCurrentFishers(ChatHandler* handler)
{
    if (!handler)
        return;

    if (_isFisherListLocked)
    {
        handler->PSendSysMessage("Fisher list is currently being modified, try again in a few seconds.");
        return;
    }

    handler->PSendSysMessage("=== Listing currently fishing players ===");
    handler->PSendSysMessage("There is currently %zu fishers, listing players that caught at least %u fishes.", _playersCurrentlyFishing.size(), MIN_FISH_CAUGHT_REQUIRED);

    for (auto const& i : _playersCurrentlyFishing)
    {
        auto fishCaught = i.second.GetTotalFishCaught();
        if (fishCaught >= MIN_FISH_CAUGHT_REQUIRED)
        {
            Player* fisher = ObjectAccessor::FindPlayer(i.first);
            if (fisher)
            {
                FishingTimeStamp now = FishingClock::now();
                uint64 timeCount = std::chrono::duration_cast<Seconds>(now - i.second.firstCaughtFishTime).count();
                std::string _timeString = secsToTimeString(timeCount);
                std::string _fisherString = fmt::format("|cffC93400 {} |rhas been fishing for {} and has caught {} fishes so far.", fisher->GetName(), _timeString, fishCaught);
                handler->PSendSysMessage(_fisherString.c_str());
            }
        }
    }
}

void WorldCache::UpdateFishingList()
{
    _isFisherListLocked = true;

    std::vector<uint64> eraser;
    FishingTimeStamp now = FishingClock::now();
    for (auto const& i : _playersCurrentlyFishing)
    {
        uint32 timeCount = std::chrono::duration_cast<Milliseconds>(now - i.second.lastCaughtFishTime).count();
        if (timeCount >= 2 * MINUTE * IN_MILLISECONDS)
            eraser.push_back(i.first);
    }

    for (auto && guid : eraser)
        _playersCurrentlyFishing.erase(guid);

    _isFisherListLocked = false;
}

void WorldCache::LoadBossRecordAllowedMaps()
{
    uint32 oldMSTime = getMSTime();
    _bossRecordsAllowedMaps.clear();

    std::string allowedMaps = sConfigMgr->GetStringDefault("CreatureBossRecords.AllowedMaps", "");
    if (!allowedMaps.empty())
    {
        Tokenizer toks(allowedMaps, ';');
        for (auto&& token : toks)
            _bossRecordsAllowedMaps.insert(atoi(token));
    }

    sLog->outString(">> Loaded disallowed boss record maps in %u ms", GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

bool WorldCache::CanAnnounceBossRecordForMap(uint32 mapId) const
{
    auto result = _bossRecordsAllowedMaps.find(mapId);
    return result != _bossRecordsAllowedMaps.end();
}
