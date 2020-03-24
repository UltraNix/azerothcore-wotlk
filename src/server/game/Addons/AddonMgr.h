
#ifndef _ADDONMGR_H
#define _ADDONMGR_H

#include "Define.h"
#include <string>

#include <vector>

struct SavedAddon
{
    SavedAddon(std::string const& name, uint32 crc) : Name(name)
    {
        CRC = crc;
    }

    std::string Name;
    uint32 CRC;
};

struct BannedAddon
{
    uint32 Id;
    uint8 NameMD5[16];
    uint8 VersionMD5[16];
    uint32 Timestamp;
};

#define STANDARD_ADDON_CRC 0x4C1C776D

namespace AddonMgr
{
    void LoadFromDB();
    void SaveAddon(std::string const& name, uint32 publicKeyCrc);
    SavedAddon const* GetAddonInfo(const std::string& name);

    typedef std::vector<BannedAddon> BannedAddonList;
    BannedAddonList const* GetBannedAddons();
}

#endif

