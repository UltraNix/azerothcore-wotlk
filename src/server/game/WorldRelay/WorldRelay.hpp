#pragma once

#include "json.hpp"
#include "Threading/SyncQueue.hpp"

#include <vector>

class HttpPosterSocket;

enum WorldRelayType
{
    TYPE_TICKETS_NEW = 1,
    TYPE_TICKETS_CLOSED,
    TYPE_LUA_CHECK_FAILURE,
    TYPE_LUA_TRAP_FAILURE,
    TYPE_LUA_FAILURES_INFORM,
    TYPE_LUA_CHECK_FAILURE_TIMEOUT,

    WORLD_RELAY_MAX_TYPE
};

struct RelayData
{
    /** account related **/
    uint32 accountId;

    /** Player related **/
    uint32 playerClass;
    uint32 playerRace;
    uint32 playerLevel;
    std::string playerZone;
    std::string playerArea;
    uint32 playerGUID;
    std::string playerName;
    Position playerPosition;

    /** Generic **/
    std::string message;
    std::string falsePositiveChance;

    /** Ticket related **/
    std::string ticketClosedBy;
    uint32 ticketId;

    /** Cheat related **/
    uint32 checkId;
    std::string _cheatDescription;

};

using RelayRequest = std::pair<WorldRelayType, RelayData>;
using RelayGeneratorPool = std::vector< std::thread >;
using RelayRequestQueue = Threading::SyncQueue<RelayRequest>;
using json = nlohmann::json;
using RelayAddressStore = std::unordered_map<WorldRelayType, std::string>;
using JsonStringStore = std::unordered_map<WorldRelayType, std::string>;

class WorldRelay
{
public:
    WorldRelay();

    void                InitializeRelay(size_t threadsCount);
    void                LoadRelayAddresses();
    void                LoadJsonStrings();
    void                Shutdown();

    void                Add(RelayRequest /*request*/);

private:
    void                RelayMessage(RelayRequest& /*request*/, HttpPosterSocket& soc);

    //! prepare json message for types
    void                BuildRelayBodyTicketNew(RelayRequest /*request*/, HttpPosterSocket& soc);
    void                BuildRelayBodyTicketClosed(RelayRequest /*request*/, HttpPosterSocket& soc);
    void                BuildRelayCheatDetected(RelayRequest /*request*/, HttpPosterSocket& soc);
    void                BuildRelayWorldstartup(RelayRequest /*request*/, HttpPosterSocket& soc);

    std::string const   GetAddressForRelayType(WorldRelayType /*type*/) const;

    std::atomic_bool    m_shutdown;
    std::atomic_bool    m_initialized;

    RelayRequestQueue   m_queue;
    RelayGeneratorPool  m_pool;
    RelayAddressStore   m_addressStore;
    JsonStringStore     m_jsonStore;

    std::string EscapeForJson(std::string const &/*string*/);
};

WorldRelay & GetRelay();
