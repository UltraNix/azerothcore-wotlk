#include "GlobalPlayerStore.h"

#include "Accounts/AccountMgr.h"
#include "Database/DatabaseEnv.h"
#include "Entities/Object/ObjectDefines.h"
#include "Packets/WorldPacket.h"
#include "Server/Protocol/Opcodes.h"
#include "World/World.h"

GlobalPlayerStore &GlobalPlayerStore::GetInstance()
{
    static GlobalPlayerStore instance;

    return instance;
}

void GlobalPlayerStore::Load()
{
    auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ALL_CHARACTERS_DATA_FOR_CACHE);
    auto result = CharacterDatabase.Query(stmt);
    if (!result)
    {
        sLog->outString();
        sLog->outErrorDb(">>  Loaded 0 Players data!");
        return;
    }

    uint32 count = 0;

    // query to load number of mails by receiver
    std::map<uint32, uint16> _mailCountMap;
    stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_ALL_MAIL_COUNTS_FOR_CACHE);
    auto mailCountResult = CharacterDatabase.Query(stmt);
    if (mailCountResult)
    {
        do
        {
            Field* fields = mailCountResult->Fetch();
            _mailCountMap[fields[0].GetUInt32()] = uint16(fields[1].GetUInt64());
        }
        while (mailCountResult->NextRow());
    }

    do
    {
        Field* fields = result->Fetch();
        uint32 guidLow = fields[0].GetUInt32();
        uint32 accountId = fields[1].GetUInt32();

        // count mails
        uint16 mailCount = 0;
        std::map<uint32, uint16>::const_iterator itr = _mailCountMap.find(guidLow);
        if (itr != _mailCountMap.end())
            mailCount = itr->second;

        Add(
            guidLow,                        /*guid*/
            accountId,                      /*accountId*/
            fields[2].GetString(),          /*name*/
            fields[3].GetUInt8(),           /*gender*/
            fields[4].GetUInt8(),           /*race*/
            fields[5].GetUInt8(),           /*class*/
            fields[6].GetUInt8(),           /*level*/
            mailCount,                      /*mail count*/
            0,                              /*guild id*/
            AccountMgr::GetName(accountId)  /*account name*/);

        ++count;
    }
    while (result->NextRow());

    sLog->outString(">>  Loaded %u Players data!", count);
}

uint32 GlobalPlayerStore::GetGUID(std::string const &name)
{
    SharedLock lock(_mutex);

    auto itr = _globalPlayerNameMap.find(name);
    if (itr == _globalPlayerNameMap.end())
        return 0;

    return itr->second;
}

GlobalPlayerData const *GlobalPlayerStore::GetData(uint32 guid)
{
    SharedLock lock(_mutex);

    auto itr = _globalPlayerDataMap.find(guid);
    if (itr == _globalPlayerDataMap.end())
        return nullptr;

    return &itr->second;
}

void GlobalPlayerStore::UpdateFromDB(uint32 guid)
{
    auto stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_CHARACTER_DATA_FOR_CACHE);

    stmt->setUInt32(0, guid);

    auto result = CharacterDatabase.Query(stmt);

    if (result)
    {
        uint16 mailCount = 0;
        stmt = CharacterDatabase.GetPreparedStatement(CHAR_SEL_MAIL_COUNT_BY_RECEIVER);
        stmt->setUInt32(0, guid);
        auto mailCountResult = CharacterDatabase.Query(stmt);
        if (mailCountResult)
        {
            Field* fields = mailCountResult->Fetch();
            mailCount = uint16(fields[0].GetUInt64());
        }

        Field* fields = result->Fetch();
        uint32 guidLow = fields[0].GetUInt32();
        uint32 accountId = fields[1].GetUInt32();

        SetData(
            guidLow,                        /*guid*/
            accountId,                      /*accountId*/
            fields[2].GetString(),          /*name*/
            fields[3].GetUInt8(),           /*gender*/
            fields[4].GetUInt8(),           /*race*/
            fields[5].GetUInt8(),           /*class*/
            fields[6].GetUInt8(),           /*level*/
            mailCount,                      /*mail count*/
            0,                              /*guild id*/
            AccountMgr::GetName(accountId)  /*account name*/);
    }
    else
    {
        DeletePlayerData(guid);
    }
}

void GlobalPlayerStore::Add(uint32 guid, uint32 accountId, std::string const &name, uint8 gender, uint8 race, uint8 playerClass, uint8 level, uint16 mailCount, uint32 guildId,
                            std::string const &accName)
{
    GlobalPlayerData data;

    data.guidLow = guid;
    data.accountId = accountId;
    data.name = name;
    data.accountName = accName;
    data.level = level;
    data.race = race;
    data.playerClass = playerClass;
    data.gender = gender;
    data.mailCount = mailCount;
    data.guildId = guildId;
    data.groupId = 0;
    data.arenaTeamId[0] = 0;
    data.arenaTeamId[1] = 0;
    data.arenaTeamId[2] = 0;

    UniqueLock lock(_mutex);

    _globalPlayerDataMap[guid] = data;
    _globalPlayerNameMap[name] = guid;
}

void GlobalPlayerStore::SetData(uint32 guid, uint32 accountId, std::string const &name, uint8 gender, uint8 race, uint8 playerClass, uint8 level, uint16 mailCount, uint32 guildId,
                                std::string const &accName)
{
    UniqueLock lock(_mutex);

    GlobalPlayerData& data = _globalPlayerDataMap[guid];

    data.guidLow = guid;
    data.accountId = accountId;
    data.name = name;
    data.accountName = accName;
    data.level = level;
    data.race = race;
    data.playerClass = playerClass;
    data.gender = gender;
    data.mailCount = mailCount;
    data.guildId = guildId;
    data.groupId = 0;

    _globalPlayerDataMap[guid] = data;
    _globalPlayerNameMap[name] = guid;
}

void GlobalPlayerStore::UpdateData(uint32 guid, uint8 mask, std::string const &name, uint8 level, uint8 gender, uint8 race, uint8 playerClass)
{
    UniqueLock lock(_mutex);

    auto itr = _globalPlayerDataMap.find(guid);
    if (itr == _globalPlayerDataMap.end())
        return;

    if (mask & PLAYER_UPDATE_DATA_LEVEL)
        itr->second.level = level;

    if (mask & PLAYER_UPDATE_DATA_RACE)
        itr->second.race = race;

    if (mask & PLAYER_UPDATE_DATA_CLASS)
        itr->second.playerClass = playerClass;

    if (mask & PLAYER_UPDATE_DATA_GENDER)
        itr->second.gender = gender;

    if (mask & PLAYER_UPDATE_DATA_NAME)
        itr->second.name = name;

    WorldPacket data(SMSG_INVALIDATE_PLAYER, 8);
    data << MAKE_NEW_GUID(guid, 0, HIGHGUID_PLAYER);
    sWorld->SendGlobalMessage(&data);
}

void GlobalPlayerStore::UpdateMails(uint32 guid, int16 count, bool add)
{
    UniqueLock lock(_mutex);
    auto data = _globalPlayerDataMap.find(guid);
    if (data == _globalPlayerDataMap.end())
        return;

    if (add)
    {
        auto mailCount = (int16)data->second.mailCount;
        if (count < 0 && abs(count) > mailCount)
            count = -mailCount;
        data->second.mailCount = uint16(mailCount + count); // addition or subtraction
    }
    else
        data->second.mailCount = count;
}

void GlobalPlayerStore::UpdateGuild(uint32 guid, uint32 guildId)
{
    UniqueLock lock(_mutex);
    auto data = _globalPlayerDataMap.find(guid);
    if (data == _globalPlayerDataMap.end())
        return;
    data->second.groupId = guildId;
}

void GlobalPlayerStore::UpdateGroup(uint32 guid, uint32 groupId)
{
    UniqueLock lock(_mutex);
    auto data = _globalPlayerDataMap.find(guid);
    if (data == _globalPlayerDataMap.end())
        return;
    data->second.groupId = groupId;
}

void GlobalPlayerStore::UpdateArenaTeam(uint32 guid, uint8 slot, uint32 arenaTeamId)
{
    UniqueLock lock(_mutex);
    auto data = _globalPlayerDataMap.find(guid);
    if (data == _globalPlayerDataMap.end())
        return;
    data->second.arenaTeamId[slot] = arenaTeamId;
}

void GlobalPlayerStore::UpdateNameData(uint32 guid, std::string const &oldName, std::string const &newName)
{
    UniqueLock lock(_mutex);
    _globalPlayerNameMap.erase(oldName);
    _globalPlayerNameMap[newName] = guid;
}

void GlobalPlayerStore::UpdateAccountId(uint32 guid, uint32 accountId)
{
    UniqueLock lock(_mutex);
    auto itr = _globalPlayerDataMap.find(guid);
    if (itr == _globalPlayerDataMap.end())
        return;

    itr->second.accountId = accountId;

    WorldPacket data(SMSG_INVALIDATE_PLAYER, 8);
    data << MAKE_NEW_GUID(guid, 0, HIGHGUID_PLAYER);
    sWorld->SendGlobalMessage(&data);
}

void GlobalPlayerStore::DeletePlayerData(uint32 guid)
{
    std::string name;
    {
        SharedLock lock(_mutex);
        auto data = _globalPlayerDataMap.find(guid);
        if (data != _globalPlayerDataMap.end())
            name = data->second.name;
    }

    DeletePlayerData(guid, name);
}

void GlobalPlayerStore::DeletePlayerData(uint32 guid, std::string const &name)
{
    UniqueLock lock(_mutex);
    _globalPlayerDataMap.erase(guid);

    if (!name.empty())
        _globalPlayerNameMap.erase(name);
}

uint32 GlobalPlayerStore::GetAccountId(uint32 guid)
{
    SharedLock lock(_mutex);

    auto data = _globalPlayerDataMap.find(guid);
    if (data != _globalPlayerDataMap.end())
        return data->second.accountId;

    return 0;
}
