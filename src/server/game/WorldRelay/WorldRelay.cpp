#include "WorldRelaySocket.hpp"
#include "WorldRelay.hpp"
#include "Log.h"
#include "World.h"
#include "DatabaseEnv.h"

#include "fmt/format.h"

#include <iomanip>
#include <ctime>

using json = nlohmann::json;

WorldRelay::WorldRelay() : m_shutdown(false) { }

void WorldRelay::LoadRelayAddresses()
{
    sLog->outString(">> Loading relay addresses...");

    uint32 oldMSTime = getMSTime();

    auto* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_RELAY_ADDRESSES);
    auto result = WorldDatabase.Query(stmt);

    if (!result)
    {
        sLog->outString(">> Loaded 0 world relay addresses. Table is empty!");
        sLog->outString();
        return;
    }

    uint32 count = 0;
    do
    {
        Field* field = result->Fetch();
        uint32 type = field[0].GetUInt32();
        std::string address = field[1].GetString();
        m_addressStore[(WorldRelayType)type] = std::move(address);
        ++count;

    } while (result->NextRow());

    sLog->outString(">> Loaded world relay addresses (count: %u) in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void WorldRelay::LoadJsonStrings()
{
    sLog->outString(">> Loading json strings ...");

    uint32 oldMSTime = getMSTime();

    auto* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_JSON_STRINGS);
    auto result = WorldDatabase.Query(stmt);

    if (!result)
    {
        sLog->outString(">> Loaded 0 json strings. Table is empty!");
        sLog->outString();
        return;
    }

    uint32 count = 0;
    do
    {
        Field* field = result->Fetch();
        uint32 type = field[0].GetUInt32();
        std::string jsonString = field[1].GetString();
        m_jsonStore[(WorldRelayType)type] = std::move(jsonString);
        ++count;

    } while (result->NextRow());

    sLog->outString(">> Loaded json strings (count: %u) in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void WorldRelay::InitializeRelay(size_t threadsCount)
{
    m_pool.reserve(threadsCount);

    for (size_t idx = 0u; idx < threadsCount; ++idx)
    {
        m_pool.push_back(std::thread([this]
        {
            HttpPosterSocket soc("priv.wherego.pl");
            while (!m_shutdown)
            {
                auto request = m_queue.pop();
                RelayMessage(request, soc);
            }
        }));
    }

    sLog->outString(">> Relay initialized.");
}

void WorldRelay::Add(RelayRequest request)
{
    if (!sWorld->getBoolConfig(CONFIG_ENABLE_WEBHOOK_RELAY))
        return;

    m_queue.push(std::move(request));
}

void WorldRelay::RelayMessage(RelayRequest& request, HttpPosterSocket& soc)
{
    if (request.first >= WORLD_RELAY_MAX_TYPE)
        return;

    switch (request.first)
    {
        case TYPE_TICKETS_NEW:
            BuildRelayBodyTicketNew(request, soc);
            break;
        case TYPE_TICKETS_CLOSED:
            BuildRelayBodyTicketClosed(request, soc);
            break;
        case TYPE_LUA_CHECK_FAILURE_TIMEOUT:
        case TYPE_LUA_CHECK_FAILURE:
        case TYPE_LUA_TRAP_FAILURE:
            BuildRelayCheatDetected(request, soc);
            break;
        case TYPE_WARDEN_CHECK_FAILURE:
            BuildRelayWardenCheatDetected(request, soc);
            break;
        case TYPE_LUA_FAILURES_INFORM:
            BuildRelayWorldstartup(request, soc);
            break;
    }
}

void WorldRelay::BuildRelayBodyTicketNew(RelayRequest request, HttpPosterSocket& soc)
{
    auto result = m_jsonStore.find(request.first);
    if (result == m_jsonStore.end())
        return;

    json json;
    std::string _unformattedString = result->second;

    /** Argument order:
        name, name, color, level, race, class, guid, account name, zone name, area name, message, ticketId, playername
    **/
    std::string ticketMsg = escape_string(request.second.message);
    std::string jsonString = fmt::format(_unformattedString,
        sWorld->GetRealmName(),
        request.second.playerName,
        request.second.playerName,
        "#E79C2F",
        request.second.playerLevel,
        request.second.playerRace,
        request.second.playerClass,
        request.second.playerGUID,
        request.second.accountId,
        request.second.playerZone,
        request.second.playerArea,
        ticketMsg,
        sWorld->GetRealmName(),
        request.second.ticketId,
        request.second.playerName);

    json = json::parse(jsonString);
    soc.post(std::move(json.dump()), std::move(GetAddressForRelayType(request.first)));
}

void WorldRelay::BuildRelayBodyTicketClosed(RelayRequest request, HttpPosterSocket& soc)
{
    auto result = m_jsonStore.find(request.first);
    if (result == m_jsonStore.end())
        return;

    json json;
    std::string _unformattedString = result->second;
    std::string jsonString = fmt::format(_unformattedString,
        request.second.ticketId,
        sWorld->GetRealmName(),
        request.second.playerName,
        request.second.ticketClosedBy,
        request.second.playerName);
    json = json::parse(jsonString);

    soc.post(std::move(json.dump()), std::move(GetAddressForRelayType(request.first)));
}

void WorldRelay::BuildRelayCheatDetected(RelayRequest request, HttpPosterSocket& soc)
{
    auto result = m_jsonStore.find(request.first);
    if (result == m_jsonStore.end())
        return;

    json json;
    std::string _unformattedFailureMessage = "{} \\nRealmName: {} \\nWARDEN check failed for (Player name: {}) (Account Id: {}){} Possible cheater!"
        "\\nFalse positive chance: {} {} "
        "\\n ``` \\nData: \\nCheckId: {} \\nCheck description: {}"
        "\\n \\nPlayer name: {} \\nPlayer GUID: {} \\nPosition when check was send: {}\\n\\n\\nAdditional message:\\n{}\\n``` \\n---";

    std::time_t time = std::time(nullptr);
    char readableTime[100];
    bool success = std::strftime(readableTime, sizeof(readableTime), "%A %c", std::localtime(&time));

    std::string _unformattedJsonString = result->second;
    std::string _secondMessage = escape_string(request.second._additionalMessage);

    std::string failureMessage = fmt::format(_unformattedFailureMessage,
        success ? readableTime : "INVALID",
        sWorld->GetRealmName(),
        request.second.playerName,
        request.second.accountId,
        request.second.message.empty() ? "." : request.second.message,
        request.second.falsePositiveChance.size() == size_t(3) ? ":white_check_mark:" : ":exclamation:",
        request.second.falsePositiveChance,
        request.second.checkId,
        request.second._cheatDescription,
        request.second.playerName,
        request.second.playerGUID,
        request.second.playerPosition.ToString(),
        _secondMessage);

    std::string jsonString = fmt::format(_unformattedJsonString,
        failureMessage,
        "Warden");

    json = json::parse(jsonString);
    soc.post(std::move(json.dump()), std::move(GetAddressForRelayType(request.first)));
}

void WorldRelay::BuildRelayWardenCheatDetected(RelayRequest request, HttpPosterSocket& soc)
{
    auto result = m_jsonStore.find(request.first);
    if (result == m_jsonStore.end())
        return;

    //std::string unformattedString = result->second;
    std::string message = "RealmName: {} \\nWARDEN check failed (Check id: {}) for (Account Id: {}). Possible cheater, kicking session - monitor this account!";
    std::string textMessage = fmt::format(message,
        sWorld->GetRealmName(),
        request.second.checkId,
        request.second.accountId);

    std::string jsonString = fmt::format(result->second,
        textMessage,
        "Warden");

    json json = json::parse(jsonString);
    soc.post(std::move(json.dump()), std::move(GetAddressForRelayType(request.first)));
}

void WorldRelay::BuildRelayWorldstartup(RelayRequest request, HttpPosterSocket& soc)
{
    auto result = m_jsonStore.find(request.first);
    if (result == m_jsonStore.end())
        return;

    json json;
    std::string _unformattedString = result->second;
    std::string jsonString = fmt::format(_unformattedString, request.second.message, "World Informer");

    json = json::parse(jsonString);
    soc.post(std::move(json.dump()), std::move(GetAddressForRelayType(request.first)));
}

std::string const WorldRelay::GetAddressForRelayType(WorldRelayType type) const
{
    auto search = m_addressStore.find(type);
    if (search != m_addressStore.end())
        return search->second;

    return { };
}

WorldRelay & GetRelay()
{
    static WorldRelay instance;
    return instance;
}

