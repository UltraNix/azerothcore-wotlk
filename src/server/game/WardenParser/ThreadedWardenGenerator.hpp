#pragma once

#include "Threading/SyncQueue.hpp"
#include "WorldCache.h"

#include <future>
#include <chrono>
#include <vector>
#include <string>
#include <cstdio>

//static const std::string WardenUniqueIdentifierCharset = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
//static const std::string WardenAlphaCharset = "abcdefghijklmnaoqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY";
//static const std::string WardenNumericCharset = "1234567890";

using WardenTimeStamp = std::chrono::time_point<std::chrono::steady_clock>;
using WardenClock = std::chrono::steady_clock;

struct WardenRequest
{
private:
    std::string _luaCode = "UNKNOWN";
    size_t _luaCodeSize = 0;
    std::string _checkPrefix = "UNKNOWN";
    std::string _checkBody = "UNKNOWN";
    std::string _description = "UNKNOWN";
    std::string _falsePositiveChance = "INVALID";
    WardenLuaCheckType _type = MAX_WARDEN_LUA_TYPES;

    WardenTimeStamp _timeStamp;
    uint32 _checkId = 0;

    /** player data **/
    std::string _playerName = "UNKNOWN";
    uint32 _playerGUIDLow = 0;

    //! when check was sent
    Position _position = { 0.f, 0.f, 0.f, 0.f };

public:
    void SetPrefix(std::string val) { _checkPrefix = std::move(val); }
    void SetBody(std::string val) { _checkBody = std::move(val); }
    void SetDescription(std::string val) { _description = std::move(val); }
    void SetLuaCode(std::string val) { _luaCode = std::move(val); }
    void SetLuaCodeSize(size_t size) { _luaCodeSize = size; }
    void SetTimeStamp() { _timeStamp = WardenClock::now(); }
    void SetCheckId(uint32 val) { _checkId = val; }
    void SetType(WardenLuaCheckType type) { _type = type; }
    void SetPosition(Position pos) { _position = std::move(pos); }
    void SetGUIDLow(uint32 guid) { _playerGUIDLow = guid; }
    void SetPlayerName(std::string name) { _playerName = std::move(name); }
    void SetFalsePositiveChance(std::string val) { _falsePositiveChance = std::move(val); }

    std::string const& GetLuaCode() const { return _luaCode; }
    size_t GetLuaCodeSize() const { return _luaCodeSize; }
    std::string const& GetPrefix() const { return _checkPrefix; }
    //! String used in SendAddonMessage that indicates clean client
    std::string const& GetBody() const { return _checkBody; }
    std::string const& GetDescription() const { return _description; }
    WardenTimeStamp GetTimeStamp() const { return _timeStamp; }
    uint32 GetCheckId() const { return _checkId; }
    WardenLuaCheckType const& GetType() { return _type; }
    Position const& GetPosition() const { return _position; }
    std::string const& GetPlayerName() const { return _playerName; }
    uint32 const GetGUIDLow() const { return _playerGUIDLow; }
    std::string const& GetFalsePositiveChance() { return _falsePositiveChance; }
};

struct RequestData
{
    uint32 _checkId;
    std::string _playerName;
    uint32 _playerGUIDLow;
    Position _playerPosition;
    std::string _addonMessageFunctionPrefix;
};

using LuaFuture = std::future< WardenRequest >;
using LuaPromise = std::promise< WardenRequest >;

struct AsyncLuaCodeResult
{
    AsyncLuaCodeResult() = default;

    AsyncLuaCodeResult(LuaFuture && future);
    AsyncLuaCodeResult(AsyncLuaCodeResult && rhs);

    AsyncLuaCodeResult& operator=(AsyncLuaCodeResult && rhs);

    bool            IsValid() const;
    bool            IsReady() const;

    void            Invalidate();

    WardenRequest   GetPreparedWardenRequest();

protected:
    LuaFuture      m_future;
};

using LuaRequest = std::pair<RequestData, LuaPromise>;

using LuaGeneratorPool = std::vector< std::thread >;
using LuaRequestQueue = Threading::SyncQueue< LuaRequest >;

class ThreadedWardenGenerator
{
public:
    ThreadedWardenGenerator();

    void                Initialize(size_t threadsCount);
    void                Shutdown();

    AsyncLuaCodeResult  RequestLuaCode(RequestData data);

protected:
    void                PrepareLuaCode(LuaRequest& request);

    std::atomic_bool    m_shutdown;
    std::atomic_bool    m_initialized;

    LuaRequestQueue    m_queue;
    LuaGeneratorPool   m_pool;

    void ReplaceAll(std::string& source, const std::string& from, const std::string& to);
};

ThreadedWardenGenerator & GetLuaGenerator();

