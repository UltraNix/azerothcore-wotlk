#pragma once

#include "json.hpp"
#include "Threading/SyncQueue.hpp"

#include <vector>
#include <thread>

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
    std::string _additionalMessage;
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

    /*!
        @brief calculates the extra space to escape a JSON string
        @param[in] s  the string to escape
        @return the number of characters required to escape string @a s
        @complexity Linear in the length of string @a s.
    */
    std::size_t extra_space(const std::string& s) noexcept
    {
        std::size_t result = 0;

        for (const auto& c : s)
        {
            switch (c)
            {
                case '"':
                case '\\':
                case '\b':
                case '\f':
                case '\n':
                case '\r':
                case '\t':
                {
                    // from c (1 byte) to \x (2 bytes)
                    result += 1;
                    break;
                }

                default:
                {
                    if (c >= 0x00 and c <= 0x1f)
                    {
                        // from c (1 byte) to \uxxxx (6 bytes)
                        result += 5;
                    }
                    break;
                }
            }
        }

        return result;
    }

    /*!
        @brief escape a string
        Escape a string by replacing certain special characters by a sequence of an
        escape character (backslash) and another character and other control
        characters by a sequence of "\u" followed by a four-digit hex
        representation.
        @param[in] s  the string to escape
        @return  the escaped string
        @complexity Linear in the length of string @a s.
    */
    std::string escape_string(const std::string& s) noexcept
    {
        const auto space = extra_space(s);
        if (space == 0)
        {
            return s;
        }

        // create a result string of necessary size
        std::string result(s.size() + space, '\\');
        std::size_t pos = 0;

        for (const auto& c : s)
        {
            switch (c)
            {
                // quotation mark (0x22)
                case '"':
                {
                    result[pos + 1] = '"';
                    pos += 2;
                    break;
                }

                // reverse solidus (0x5c)
                case '\\':
                {
                    // nothing to change
                    pos += 2;
                    break;
                }

                // backspace (0x08)
                case '\b':
                {
                    result[pos + 1] = 'b';
                    pos += 2;
                    break;
                }

                // formfeed (0x0c)
                case '\f':
                {
                    result[pos + 1] = 'f';
                    pos += 2;
                    break;
                }

                // newline (0x0a)
                case '\n':
                {
                    result[pos + 1] = 'n';
                    pos += 2;
                    break;
                }

                // carriage return (0x0d)
                case '\r':
                {
                    result[pos + 1] = 'r';
                    pos += 2;
                    break;
                }

                // horizontal tab (0x09)
                case '\t':
                {
                    result[pos + 1] = 't';
                    pos += 2;
                    break;
                }

                default:
                {
                    if (c >= 0x00 and c <= 0x1f)
                    {
                        // print character c as \uxxxx
                        sprintf(&result[pos + 1], "u%04x", int(c));
                        pos += 6;
                        // overwrite trailing null character
                        result[pos] = '\\';
                    }
                    else
                    {
                        // all other characters are added as-is
                        result[pos++] = c;
                    }
                    break;
                }
            }
        }

        return result;
    }
};

WorldRelay & GetRelay();
