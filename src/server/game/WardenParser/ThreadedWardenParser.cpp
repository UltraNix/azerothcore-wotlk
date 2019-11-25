#include "ThreadedWardenParser.hpp"

#include "Player.h"
#include "WorldSession.h"
#include "WorldRelay/WorldRelay.hpp"

namespace WardenParserWin
{
    ThreadedWardenParser::ThreadedWardenParser() : m_shutdown(false) { }

    void ThreadedWardenParser::Initialize(size_t threadsCount)
    {
        m_pool.reserve(threadsCount);

        for (size_t idx = 0u; idx < threadsCount; ++idx)
        {
            m_pool.push_back(std::thread([this]
            {
                while (!m_shutdown)
                {
                    auto request = m_queue.pop();
                    ParseMessage(std::move(request));
                }
            }));
        }

        sLog->outString(">> Warden parser initialized.");
    }

    void ThreadedWardenParser::Shutdown()
    {
        m_shutdown = true;
    }

    void ThreadedWardenParser::AddMessage(Requestee who, std::string message)
    {
        m_queue.push({ who, std::move(message) });
    }

    void ThreadedWardenParser::ParseMessage(ParseRequest request)
    {
        Player* player = ObjectAccessor::FindPlayerInOrOutOfWorld(request.first.characterGUID);
        WorldSession* session = player ? player->GetSession() : nullptr;

        if (session)
        {
            std::string message = request.second;

            uint32 position = message.find("\t");
            if (position == std::string::npos)
            {
                sLog->outStaticDebug("ThreadedWardenParser::HandlePingPongMessage %s failed to find vertical tab in addon message", message.c_str());
                return;
            }

            std::string _prefix{ };
            std::string _body{ };
            bool IsTrapMessage = false;
            bool IsDebugStackMessage = false;

            //! addon message is sent as one string seperated by tab (/t)
            //! seperate prefix from message body
            SplitAddonMessage(message, _prefix, _body, position, 5);
            switch (_prefix.size())
            {
                //case WARDEN_PREFIX_SIZE:
                //    break;
                case WARDEN_TRAP_DEBUGSTACK_PREFIX_SIZE:
                    IsDebugStackMessage = true;
                    break;
                case WARDEN_TRAP_PREFIX_SIZE:
                    IsTrapMessage = true;
                    break;
                default:
                    break;
            }

            WardenRequestStore _store;
            _store.clear();
            //! Get by copy, different contexts might modify or erase while we operate on it
            if (IsTrapMessage || IsDebugStackMessage)
                _store = session->GetLuaTrapRequests();
            else
                _store = session->GetLuaRequests();

            auto luaRequest = _store.find(_prefix);
            if (luaRequest == _store.end())
            {
                sLog->outDebug(LOG_FILTER_WARDEN, "ThreadedWardenParser::ParseMessage: Lack of lua request for key %s", _prefix);
                return;
            }

            bool checkPassed = false;
            if (IsDebugStackMessage)
            {
                checkPassed = ParseDebugStackMessage(_body);
            }
            else if (IsTrapMessage)
            {
                if (_prefix == luaRequest->second.GetPrefix() && _body == luaRequest->second.GetBody())
                    checkPassed = false;
            }
            else
            {
                if (_prefix == luaRequest->second.GetPrefix())
                    checkPassed = _body == luaRequest->second.GetBody();
            }

            if (!checkPassed)
            {
                if (sLog->IsOutDebug())
                {
                    if (IsTrapMessage)
                        sLog->outStaticDebug("Client trap triggered, CheckId(%u), AccountId (%u), Received prefix (%s), Received body (%s)", luaRequest->second.GetCheckId(),
                            session->GetAccountId(), _prefix.c_str(), _body.c_str());
                    else
                        sLog->outStaticDebug("CheckId(%u) failed for account(%u). Received body is (%s) but correct answer should be (%s)!",
                            luaRequest->second.GetCheckId(), session->GetAccountId(), _body.c_str(), luaRequest->second.GetBody().c_str());
                }

                session->HandleCheckFailure(luaRequest->second.GetCheckId(), false);
                if (sWorldCache.CanRelayLuaResult(luaRequest->second.GetCheckId()))
                {
                    RelayData data;
                    data.accountId = session->GetAccountId();
                    data.playerGUID = luaRequest->second.GetGUIDLow();
                    data.playerName = luaRequest->second.GetPlayerName();
                    data.playerPosition = luaRequest->second.GetPosition();
                    data.checkId = luaRequest->second.GetCheckId();
                    data._cheatDescription = luaRequest->second.GetDescription();
                    data.falsePositiveChance = luaRequest->second.GetFalsePositiveChance();
                    data._additionalMessage = std::move(_body);

                    GetRelay().Add(std::make_pair(((IsTrapMessage || IsDebugStackMessage) ? TYPE_LUA_TRAP_FAILURE : TYPE_LUA_CHECK_FAILURE), data));
                }
            }

            //! Erase request, client answered. We do not need to keep track of it anymore
            if (!IsTrapMessage && !IsDebugStackMessage)
                session->ClearPongRequest(std::move(_prefix));
        }
    }

    void ThreadedWardenParser::SplitAddonMessage(std::string& message, std::string& prefix, std::string& body, uint32 tabPosition, uint32 prefixSize)
    {
        //! everything past /t sign is addon message body
        body = message.substr(tabPosition + 1);
        //! Whats left is our prefix, size is based on entire message size
        //! because size of message is static, check WARDEN_PREFIX_SIZE in WorldSession.h
        //! and then we check if it matches with anything we've sent in the past
        message.resize(tabPosition);
        prefix = message;
    }

    //! True means everything went okay, client didnt cheat
    bool ThreadedWardenParser::ParseDebugStackMessage(std::string message)
    {
        if (message.empty())
            return false;

        bool const foundSecureString = message.find("Secure") != std::string::npos;
        bool const foundEnterPressedString = message.find("OnEnterPressed") != std::string::npos;

        return foundSecureString || foundEnterPressedString;
    }

    ThreadedWardenParser & GetWardenParser()
    {
        static ThreadedWardenParser _parser;
        return _parser;
    }
}
