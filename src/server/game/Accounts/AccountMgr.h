

#ifndef _ACCMGR_H
#define _ACCMGR_H

#include "Define.h"
#include <string>

enum AccountOpResult
{
    AOR_OK,
    AOR_NAME_TOO_LONG,
    AOR_PASS_TOO_LONG,
    AOR_NAME_ALREDY_EXIST,
    AOR_NAME_NOT_EXIST,
    AOR_DB_INTERNAL_ERROR
};

#define MAX_ACCOUNT_STR 20

namespace AccountMgr
{
    bool CheckPassword(uint32 accountId, std::string password);
    bool CheckCountry(uint32 accountId, std::string country, std::string exceptCountry);

    uint32 GetId(std::string const& username);
    uint32 GetSecurity(uint32 accountId);
    uint32 GetSecurity(uint32 accountId, int32 realmId);

    bool GetName(uint32 accountId, std::string& name);
    std::string const GetName(uint32 accountId);
    uint32 GetCharactersCount(uint32 accountId);
    std::string CalculateShaPassHash(std::string const& name, std::string const& password);

    bool normalizeString(std::string& utf8String);
    bool IsPlayerAccount(uint32 gmlevel);
    bool IsModeratorAccount(uint32 gmlevel); // Sitowsky
    bool IsGMAccount(uint32 gmlevel);
    bool IsAdminAccount(uint32 gmlevel);
    bool IsConsoleAccount(uint32 gmlevel);
    std::string GetLastIp(uint32 acc_id);

};

#endif
