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

            switch (message.size())
            {
                case WARDEN_PING_PONG_MESSAGE_SIZE:
                    SplitAddonMessage(message, _prefix, _body, position, WARDEN_PREFIX_SIZE);
                    break;
                case WARDEN_TRAP_MESSAGE_SIZE:
                    SplitAddonMessage(message, _prefix, _body, position, WARDEN_TRAP_PREFIX_SIZE);
                    IsTrapMessage = true;
                    break;
                default:
                    //! return alltogether, doesnt match our structures
                    return;
            }

            WardenRequest* request = IsTrapMessage ?
                session->GetLuaTrapRequest(_prefix) : session->GetLuaRequest(_prefix);

            if (!request)
            {
                sLog->outStaticDebug("ThreadedWardenParser::ParseMessage: Lack of lua request for key %s", _prefix);
                return;
            }

            bool checkPassed = false;
            if (!IsTrapMessage)
            {
                if (_prefix == request->GetPrefix())
                    checkPassed = _body == request->GetBody();
            }
            //! Trap checks send only one addon message, only in case of cheating
            //! if we hit it then client is cheating
            else if (_prefix == request->GetPrefix() && _body == request->GetBody())
                checkPassed = false;

            if (!checkPassed)
            {
                if (sLog->IsOutDebug())
                {
                    if (IsTrapMessage)
                        sLog->outStaticDebug("Client trap triggered, CheckId(%u), AccountId (%u), Received prefix (%s), Received body (%s)", request->GetCheckId(),
                            session->GetAccountId(), _prefix.c_str(), _body.c_str());
                    else
                        sLog->outStaticDebug("CheckId(%u) failed for account(%u). Received body is (%s) but correct answer should be (%s)!",
                            request->GetCheckId(), session->GetAccountId(), _body.c_str(), request->GetBody().c_str());
                }

                if (sWorldCache.CanRelayLuaResult(request->GetCheckId()))
                {
                    RelayData data;
                    data.accountId = session->GetAccountId();
                    data.playerGUID = request->GetGUIDLow();
                    data.playerName = request->GetPlayerName();
                    data.playerPosition = request->GetPosition();
                    data.checkId = request->GetCheckId();
                    data._cheatDescription = request->GetDescription();
                    data.falsePositiveChance = request->GetFalsePositiveChance();

                    session->HandleCheckFailure(request->GetCheckId(), false);
                    GetRelay().Add(std::make_pair((IsTrapMessage ? TYPE_LUA_TRAP_FAILURE : TYPE_LUA_CHECK_FAILURE), data));
                }
            }

            //! Erase request, client answered. We do not need to keep track of it anymore
            if (!IsTrapMessage)
                session->ClearPongRequest(_prefix);
        }
    }

    void ThreadedWardenParser::SplitAddonMessage(std::string& message, std::string& prefix, std::string& body, uint32 tabPosition, uint32 prefixSize)
    {
        //! everything past /t sign is addon message body
        body = message.substr(tabPosition + 1);
        //! Whats left is our prefix, size is based on entire message size
        //! because size of message is static, check WARDEN_PREFIX_SIZE in WorldSession.h
        //! and then we check if it matches with anything we've sent in the past
        message.resize(prefixSize);
        prefix = message;
    }

    ThreadedWardenParser & GetWardenParser()
    {
        static ThreadedWardenParser _parser;
        return _parser;
    }
}
