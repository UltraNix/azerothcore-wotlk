#include "ThreadedWardenParser.hpp"

#include "WorldSession.h"
#include "World.h"
#include "Profiler.h"

namespace WardenParserWin
{
    void ThreadedWardenParser::Initialize(size_t threadsCount)
    {
        m_pool.reserve(threadsCount);

        for (size_t idx = 0u; idx < threadsCount; ++idx)
        {
            m_pool.emplace_back([this]
            {
                while (!m_queue.is_closed())
                {
                    auto request = m_queue.pop();
                    if (!request)
                        continue;

                    ParseMessage( std::move( *request ));
                }
            });
        }

        sLog->outString(">> Warden parser initialized.");
    }

    void ThreadedWardenParser::Shutdown()
    {
        m_queue.close();

        for ( auto & thread : m_pool )
        {
            if ( thread.joinable() )
                thread.join();
        }
    }

    void ThreadedWardenParser::AddMessage(Requestee who, std::string message)
    {
        m_queue.push({ std::move(who), std::move(message) });
    }

    void ThreadedWardenParser::ParseMessage(ParseRequest request)
    {
        PROFILE_SCOPE( "ParseMessage" );

        Requestee const& requestee = request.first;
        std::string& message = request.second;

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

        WardenRequestStore const& requestStore = IsTrapMessage || IsDebugStackMessage ? requestee.GetTrapRequestStore() : requestee.GetRequestStore();
        auto luaRequest = requestStore.find(_prefix);
        if (luaRequest == requestStore.end())
        {
            sLog->outDebug(LOG_FILTER_WARDEN, "ThreadedWardenParser::ParseMessage: Lack of lua request for key %s", _prefix.c_str());
            return;
        }

        bool checkPassed = false;
        if (IsDebugStackMessage)
            checkPassed = ParseDebugStackMessage(_body);
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

        WardenLuaResult result;
        result.SetCheckType(IsDebugStackMessage || IsTrapMessage);
        result.SetCheckPassed(checkPassed);
        result.SetCheckId(luaRequest->second.GetCheckId());
        result.SetCheckPrefix(_prefix);
        result.SetCharacterGUID(requestee.GetCharacterGUID());

        if (!checkPassed)
        {
            result.SetPosition(luaRequest->second.GetPosition());
            result.SetAdditionalMessage(_body);
            result.SetLuaDescription(luaRequest->second.GetDescription());
            result.SetLuaFalsePositiveChance(luaRequest->second.GetFalsePositiveChance());
        }

        std::lock_guard<std::mutex> const lock(resultsLock);
        _parseResultStore[requestee.GetCharacterGUID()].emplace_back(result);
    }

    void ThreadedWardenParser::GrabAllReports(World* world)
    {
        std::lock_guard<std::mutex> const lock(resultsLock);
        if (_parseResultStore.empty())
            return;

        for (auto&& iter : _parseResultStore)
            world->HandleLuaResult(iter.first, std::move(iter.second));
        _parseResultStore.clear();
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
        bool const foundEnchantrixAddon = message.find("Enchantrix") != std::string::npos;
        bool const foundSpotterAddon = message.find("Spotter") != std::string::npos;

        return foundSecureString || foundEnterPressedString;
    }

    ThreadedWardenParser & GetWardenParser()
    {
        static ThreadedWardenParser _parser;
        return _parser;
    }
}
