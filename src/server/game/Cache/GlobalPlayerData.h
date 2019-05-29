#ifndef SUNWELLCORE_GLOBALPLAYERDATA_H
#define SUNWELLCORE_GLOBALPLAYERDATA_H

enum GlobalPlayerUpdateMask
{
    PLAYER_UPDATE_DATA_LEVEL            = 0x01,
    PLAYER_UPDATE_DATA_RACE             = 0x02,
    PLAYER_UPDATE_DATA_CLASS            = 0x04,
    PLAYER_UPDATE_DATA_GENDER           = 0x08,
    PLAYER_UPDATE_DATA_NAME             = 0x10
};
struct GlobalPlayerData
{
    uint32 guidLow = 0;
    uint32 accountId = 0;
    std::string accountName;
    std::string name;
    uint8 race = 0;
    uint8 playerClass = 0;
    uint8 gender = 0;
    uint8 level = 0;
    uint16 mailCount = 0;
    uint32 guildId = 0;
    uint32 groupId = 0;
    uint32 arenaTeamId[3] = {0, 0, 0};
};

#endif //SUNWELLCORE_GLOBALPLAYERDATA_H
