#include "ThreadedWardenGenerator.hpp"
#include "WorldCache.h"
#include "WorldSession.h"
#include "Util.h"
#include "Profiler.h"

#include <cctype> // for std::isdigit
#include "fmt/format.h"

void ThreadedWardenGenerator::Initialize(size_t threadsCount)
{
    m_pool.reserve(threadsCount);

    for (size_t idx = 0u; idx < threadsCount; ++idx)
    {
        m_pool.push_back(std::thread([this]
        {
            while (!m_queue.is_closed())
            {
                auto request = m_queue.pop();
                if ( !request )
                    continue;

                PrepareLuaCode(*request);
            }
        }));
    }
}

void ThreadedWardenGenerator::Shutdown()
{
    m_queue.close();

    for ( auto & thread : m_pool )
    {
        if ( thread.joinable() )
            thread.join();
    }
}

AsyncLuaCodeResult ThreadedWardenGenerator::RequestLuaCode(RequestData data)
{
    LuaPromise promise;

    AsyncLuaCodeResult result(promise.get_future());
    m_queue.push({ std::move(data), std::move(promise) });

    return result;
}

void ThreadedWardenGenerator::PrepareLuaCode(LuaRequest& request)
{
    PROFILE_SCOPE( "PrepareLuaCode" );

    WardenLuaCheck const* check = sWorldCache.GetWardenCheckFor(request.first._checkId);

    if (!check)
    {
        request.second.set_value({ });
        return;
    }

    WardenLuaCheckType const& checkType = check->_checkType;

    std::string _messagePrefix;
    std::string _successBody;
    std::string _failureBody;
    std::string _luaCode = check->_luaCode;
    std::string _messageReceiver = "";

    //! 1. name of a function that handles sending addon message
    //! 2. addon message prefix
    //! 3. addon message body
    //! 4. some checks insert data into _G (lua Global Tables)
    std::string addonSuccessMessage = "{}('{}','{}','WHISPER','{}')";
    std::string addonFailureMessage = "{}('{}','{}','WHISPER','{}')";
    std::string SendAddonMessageFunction = "if ({} == nil)then {}=SendAddonMessage end";
    std::string globalTablesString = "_G[\"{}\"]";
    std::string SendGlobalTablesData = "{}('{}',{},'WHISPER','{}')";

    //! Generate a name that includes a number in it
    //! ChatHandler checks whether a name in addon msg has a digit, if so it will return silently
    //! otherwise client would receive a warning that player doesnt exist
    std::string const WardenUniqueIdentifierCharset = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    std::string const WardenAlphaCharset = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY";
    std::string const WardenNumericCharset = "1234567890";

    _messageReceiver = GenerateRandomIdentifier(2, WardenAlphaCharset);
    _messageReceiver += GenerateRandomIdentifier(1, WardenNumericCharset);

    switch (checkType)
    {
        case WARDEN_LUA_RETRIEVE_DATA_FROM_GT:
            _messagePrefix = GenerateRandomIdentifier(WARDEN_TRAP_DEBUGSTACK_PREFIX_SIZE, WardenUniqueIdentifierCharset);
            break;
        case WARDEN_LUA_TRAP:
            _messagePrefix = GenerateRandomIdentifier(WARDEN_TRAP_PREFIX_SIZE, WardenUniqueIdentifierCharset);
            _successBody = GenerateRandomIdentifier(WARDEN_TRAP_BODY_SIZE, WardenUniqueIdentifierCharset);
            _failureBody = GenerateRandomIdentifier(WARDEN_TRAP_BODY_SIZE - 1, WardenUniqueIdentifierCharset);
            break;
        default:
        {
            _messagePrefix = GenerateRandomIdentifier(WARDEN_PREFIX_SIZE, WardenUniqueIdentifierCharset);
            _successBody = GenerateRandomIdentifier(WARDEN_BODY_SIZE, WardenUniqueIdentifierCharset);
            _failureBody = GenerateRandomIdentifier(WARDEN_BODY_SIZE - 1, WardenUniqueIdentifierCharset);
            break;
        }
    }

    //! generate different ending for _failureBody
    //! just in case GenerateRandomIdentifier returned same message twice
    auto randomCharacter = [](std::string message) -> char
    {
        return message[urand(0, message.size() - 1)];
    };

    bool _lastSignIsDigit = false;
    if (_failureBody.size() > size_t(0))
        _lastSignIsDigit = std::isdigit(_failureBody[_failureBody.size() - 1]);
    _failureBody += randomCharacter(_lastSignIsDigit ? WardenAlphaCharset : WardenNumericCharset);

    std::string finalAddonSuccessMessage = fmt::format(addonFailureMessage, request.first._addonMessageFunctionPrefix.c_str(), _messagePrefix.c_str(), _successBody.c_str(), _messageReceiver.c_str());
    std::string finalAddonFailureMessage = fmt::format(addonFailureMessage, request.first._addonMessageFunctionPrefix.c_str(), _messagePrefix.c_str(), _failureBody.c_str(), _messageReceiver.c_str());
    std::string finalAddonMessageFunction = fmt::format(SendAddonMessageFunction, request.first._addonMessageFunctionPrefix.c_str(), request.first._addonMessageFunctionPrefix.c_str());
    std::string globalTablesIndexAccess = fmt::format(globalTablesString, request.first._globalTablesAccessIndex);
    std::string finalSendGlobalTablesData = fmt::format(SendGlobalTablesData, request.first._addonMessageFunctionPrefix, _messagePrefix, globalTablesIndexAccess, _messageReceiver);

    ReplaceAll(_luaCode, "@addonSuccess", finalAddonSuccessMessage);
    ReplaceAll(_luaCode, "@addonFailure", finalAddonFailureMessage);
    if (checkType == WARDEN_LUA_TRAP_DEBUGSTACK || checkType == WARDEN_LUA_RETRIEVE_DATA_FROM_GT)
    {
        ReplaceAll(_luaCode, "@GlobalTablesEntry", globalTablesIndexAccess);
        ReplaceAll(_luaCode, "@AddonMsgGt", finalSendGlobalTablesData);
    }

    //! creates custom function that handles sending addon message to the server
    //! this has to be re-send each time, because it is lost when UI is reloaded
    //! or player leaves and enter the world (instances and so on)
    ReplaceAll(_luaCode, "@CreateSendAddonMessage", finalAddonMessageFunction);

    //! Fills the struct with request data
    //! this is used by _LuaResult in WorldSession
    WardenRequest w_request{ };
    w_request.SetCheckId(request.first._checkId);
    w_request.SetBody(_successBody);
    w_request.SetPrefix(_messagePrefix);
    w_request.SetDescription(check->_description);
    w_request.SetFalsePositiveChance(check->_falsePositiveProbability);
    w_request.SetPlayerName(request.first._playerName);
    w_request.SetGUIDLow(request.first._playerGUIDLow);
    w_request.SetPosition(request.first._playerPosition);
    w_request.SetType(checkType);
    w_request.SetLuaCode(_luaCode);
    w_request.SetLuaCodeSize(_luaCode.size());
    w_request.SetTimeStamp();

    request.second.set_value(std::move(w_request));
}

AsyncLuaCodeResult& AsyncLuaCodeResult::operator=(AsyncLuaCodeResult && rhs)
{
    m_future = std::move(rhs.m_future);
    return *this;
}

AsyncLuaCodeResult::AsyncLuaCodeResult(AsyncLuaCodeResult && rhs)
    : m_future(std::move(rhs.m_future)) { }

AsyncLuaCodeResult::AsyncLuaCodeResult(LuaFuture && future)
    : m_future(std::move(future)) { }

bool AsyncLuaCodeResult::IsValid() const
{
    return m_future.valid();
}

bool AsyncLuaCodeResult::IsReady() const
{
    return IsValid() && m_future.wait_for(std::chrono::nanoseconds(0)) == std::future_status::ready;
}

void AsyncLuaCodeResult::Invalidate()
{
    if (!IsValid())
        return;

    //! we create new future, so we don't need to wait for old one on .get() call
    LuaPromise promise;
    m_future = promise.get_future();

    promise.set_value({ });
    m_future.get();
}

WardenRequest AsyncLuaCodeResult::GetPreparedWardenRequest()
{
    return std::move(m_future.get());
}

void ThreadedWardenGenerator::ReplaceAll(std::string& source, std::string const& from, std::string const& to)
{
    std::string newString;
    newString.reserve(source.length());

    std::string::size_type lastPos = 0;
    std::string::size_type findPos;

    while (std::string::npos != (findPos = source.find(from, lastPos)))
    {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }

    newString += source.substr(lastPos);

    source.swap(newString);
}

ThreadedWardenGenerator & GetLuaGenerator()
{
    static ThreadedWardenGenerator s_generator;
    return s_generator;
}
