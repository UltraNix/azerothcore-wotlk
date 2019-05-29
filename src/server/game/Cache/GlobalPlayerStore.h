#ifndef SUNWELLCORE_GLOBALPLAYERSTORE_H
#define SUNWELLCORE_GLOBALPLAYERSTORE_H

#include <map>
#include <string>
#include <shared_mutex>

#include "Define.h"
#include "GlobalPlayerData.h"

typedef std::shared_lock<std::shared_mutex> SharedLock;
typedef std::unique_lock<std::shared_mutex> UniqueLock;

class GlobalPlayerStore
{
public:
    static GlobalPlayerStore& GetInstance();

    void Load();
    uint32 GetGUID(std::string const& name);
    GlobalPlayerData const* GetData(uint32 guid);
    void Add(uint32 guid, uint32 accountId, std::string const& name, uint8 gender, uint8 race, uint8 playerClass, uint8 level, uint16 mailCount, uint32 guildId, std::string const& accName);
    void SetData(uint32 guid, uint32 accountId, std::string const& name, uint8 gender, uint8 race, uint8 playerClass, uint8 level, uint16 mailCount, uint32 guildId, std::string const& accName);
    void UpdateData(uint32 guid, uint8 mask, std::string const& name, uint8 level = 0, uint8 gender = 0, uint8 race = 0, uint8 playerClass = 0);
    void UpdateFromDB(uint32 guid);
    void UpdateMails(uint32 guid, int16 count, bool add = true);
    void UpdateGuild(uint32 guid, uint32 guildId);
    void UpdateGroup(uint32 guid, uint32 groupId);
    void UpdateArenaTeam(uint32 guid, uint8 slot, uint32 arenaTeamId);
    void UpdateNameData(uint32 guidLow, std::string const& oldName, std::string const& newName);
    void UpdateAccountId(uint32 guid, uint32 accountId);
    void DeletePlayerData(uint32 guid, std::string const& name);
    void DeletePlayerData(uint32 guid);
    uint32 GetAccountId(uint32 guid);

private:
    GlobalPlayerStore() = default;

    std::shared_mutex _mutex;
    std::map<uint32, GlobalPlayerData> _globalPlayerDataMap;
    std::map<std::string, uint32> _globalPlayerNameMap;

protected:
    GlobalPlayerStore(GlobalPlayerStore const&)             = delete;
    GlobalPlayerStore(GlobalPlayerStore &&)                 = delete;
    GlobalPlayerStore& operator=(GlobalPlayerStore const&)  = delete;
    GlobalPlayerStore& operator=(GlobalPlayerStore &&)      = delete;
};

#define sGlobalPlayerStore GlobalPlayerStore::GetInstance()

#endif //SUNWELLCORE_GLOBALPLAYERSTORE_H
