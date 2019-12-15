#pragma once

#include <vector>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <string>

#include "Threading/SyncQueue.hpp"
#include "Common.h"
#include "Object.h"

enum WardenLuaCheckType : uint32
{
    WARDEN_LUA_PONG = 1,
    WARDEN_LUA_TRAP,
    //! clean client will always answer
    //! unlocked client will not answer
    WARDEN_LUA_PONG_2,
    //! send before everything else
    WARDEN_LUA_FRAME_CREATION,
    WARDEN_LUA_ADDON_SENDER_CREATION,
    //! WRobot specific check, this will hook into protected functions
    //! and then move data to clients global table and we will extract that data later
    //! with additional check
    WARDEN_LUA_TRAP_DEBUGSTACK,
    //! this check grabs data that we store in global tables and then returns data to us
    WARDEN_LUA_RETRIEVE_DATA_FROM_GT,

    MAX_WARDEN_LUA_TYPES
};

using WardenTimeStamp = std::chrono::time_point<std::chrono::steady_clock>;
using WardenClock = std::chrono::steady_clock;

constexpr uint32 WARDEN_PREFIX_DEBUGSTACK_SIZE{ 4 };
constexpr uint32 WARDEN_PREFIX_SIZE{ 5 };
constexpr uint32 WARDEN_BODY_SIZE{ 5 };

constexpr uint32 WARDEN_TRAP_PREFIX_SIZE{ 7 };
constexpr uint32 WARDEN_TRAP_BODY_SIZE{ 7 };

constexpr uint32 WARDEN_TRAP_GLOBALTABLES_PREFIX_SIZE{ 6 };

//! addonmessage string is composed of prefix + /t + body
constexpr uint32 WARDEN_PING_PONG_MESSAGE_SIZE{ WARDEN_PREFIX_SIZE + WARDEN_BODY_SIZE + 1 };
constexpr uint32 WARDEN_TRAP_MESSAGE_SIZE{ WARDEN_TRAP_PREFIX_SIZE + WARDEN_TRAP_BODY_SIZE + 1 };

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
    std::string const& GetFalsePositiveChance() const { return _falsePositiveChance; }
};
using LuaFuture = std::future< WardenRequest >;
using WardenRequestStore = std::unordered_map<std::string/*prefix*/, WardenRequest>;

struct RequestData
{
    uint32 _checkId;
    std::string _playerName;
    uint32 _playerGUIDLow;
    Position _playerPosition;
    std::string _addonMessageFunctionPrefix;
    std::string _globalTablesAccessIndex;
};

struct AsyncLuaCodeResult
{
    AsyncLuaCodeResult() = default;

    AsyncLuaCodeResult(LuaFuture&& future);
    AsyncLuaCodeResult(AsyncLuaCodeResult&& rhs);

    AsyncLuaCodeResult& operator=(AsyncLuaCodeResult&& rhs);

    bool            IsValid() const;
    bool            IsReady() const;

    void            Invalidate();

    WardenRequest   GetPreparedWardenRequest();

protected:
    LuaFuture      m_future;
};

struct WardenLuaCheck
{
    uint32 _checkId = 0;
    std::string _luaCode = "";
    WardenLuaCheckType _checkType = MAX_WARDEN_LUA_TYPES;
    std::string _description = "";
    std::string _falsePositiveProbability = "";
};

struct WardenLuaResult
{
private:
    uint64 characterGUID = 0;
    bool _IsTrapOrDebugCheck = false;
    bool passed = true;
    uint32 checkId = 0;
    Position position = { 0.f, 0.f, 0.f, 0.f };
    std::string luaDescription = "None";
    std::string luaFalsePositive = "High";
    std::string additionalMessageFromCheck = "None";
    std::string checkPrefix = "";

public:
    void SetCharacterGUID(uint64 val) { characterGUID = val; }
    uint64 const GetCharacterGUID() const { return characterGUID; }
    void SetCheckType(bool val /*true means its trap check*/) { _IsTrapOrDebugCheck = val; }
    bool IsTrapOrDebugCheck() const { return _IsTrapOrDebugCheck; }
    void SetCheckPassed(bool val) { passed = val; }
    bool CheckPassed() const { return passed; }
    void SetCheckId(uint32 val) { checkId = val; }
    uint32 GetCheckId() const { return checkId; }
    void SetPosition(Position const pos) { position = std::move(position); }
    Position const& GetPosition() const { return position; }
    std::string const& GetLuaDescription() const { return luaDescription; }
    std::string const& GetLuaFalsePositiveChance() const { return luaFalsePositive; }
    std::string const& GetAdditionalMessage() const { return additionalMessageFromCheck; }
    void SetLuaDescription(std::string val) { luaDescription = std::move(val); }
    void SetLuaFalsePositiveChance(std::string val) { luaFalsePositive = std::move(val); }
    void SetAdditionalMessage(std::string val) { additionalMessageFromCheck = std::move(val); }
    void SetCheckPrefix(std::string val) { checkPrefix = std::move(val); }
    std::string const& GetCheckPrefix() { return checkPrefix; }
};

struct Requestee
{
private:
    uint64 characterGUID;
    WardenRequestStore _requestStore;
    WardenRequestStore _requestTrapStore;
    WardenRequestStore _requestDebugStackStore;
public:
    void SetCharacterGUID(uint32 val) { characterGUID = val; }
    uint64 const GetCharacterGUID() const { return characterGUID; }
    void CopyLuaRequestStore(WardenRequestStore store) { _requestStore = store; }
    void CopyLuaTrapRequestStore(WardenRequestStore store) { _requestTrapStore = store; }
    void CopyLuaDebugstackStore(WardenRequestStore store) { _requestDebugStackStore = store; }
    WardenRequestStore const& GetRequestStore() const { return _requestStore; }
    WardenRequestStore const& GetTrapRequestStore() const { return _requestTrapStore; }
    WardenRequestStore const& GetDebugstackRequestStore() const { return _requestDebugStackStore; }
};

using WardenLuaStore = std::unordered_map<uint32 /*checkId*/, WardenLuaCheck /*struct*/>;
using LuaPromise = std::promise< WardenRequest >;
using LuaRequest = std::pair<RequestData, LuaPromise>;
using LuaGeneratorPool = std::vector< std::thread >;
using LuaRequestQueue = Threading::SyncQueue< LuaRequest >;
using ParseRequest = std::pair<Requestee, std::string >;
using ParseGeneratorPool = std::vector< std::thread >;
using ParseRequestQueue = Threading::SyncQueue< ParseRequest >;
