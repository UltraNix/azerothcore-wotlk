/*
 * Copyright (C)
 * Copyright (C)
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "AddonMgr.h"
#include "DatabaseEnv.h"
#include "Log.h"
#include "Timer.h"

#include <unordered_map>

inline uint32_t fnv1a( const void* key, const uint32_t len )
{
    const char* data = ( char* )key;
    uint32_t hash = 0x811c9dc5;
    uint32_t prime = 0x1000193;

    for (uint32_t i = 0u; i < len; ++i)
    {
        uint8_t value = data[ i ];
        hash = hash ^ value;
        hash *= prime;
    }

    return hash;
}

namespace AddonMgr
{

// Anonymous namespace ensures file scope of all the stuff inside it, even
// if you add something more to this namespace somewhere else.
namespace
{
    // List of saved addons (in DB).
    typedef std::unordered_map< uint32_t, SavedAddon> SavedAddonsMap;

    SavedAddonsMap m_knownAddons;
}

void LoadFromDB()
{
    uint32 oldMSTime = getMSTime();

    QueryResult result = CharacterDatabase.Query("SELECT name, crc FROM addons");
    if (!result)
    {
        sLog->outString(">> Loaded 0 known addons. DB table `addons` is empty!");
        sLog->outString();
        return;
    }

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();

        std::string name = fields[0].GetString();
        uint32 crc = fields[1].GetUInt32();

        uint32_t hash = fnv1a(name.c_str(), name.size());
        m_knownAddons.insert({ hash, SavedAddon(std::move(name), crc) });

        ++count;
    }
    while (result->NextRow());

    sLog->outString(">> Loaded %u known addons in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void SaveAddon(AddonInfo const& addon)
{
    std::string name = addon.Name;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_ADDON);

    stmt->setString(0, name);
    stmt->setUInt32(1, addon.CRC);

    CharacterDatabase.Execute(stmt);

    uint32_t hash = fnv1a(name.c_str(), name.size());
    m_knownAddons.insert({ hash, SavedAddon(std::move(name), addon.CRC) });
}

SavedAddon const* GetAddonInfo(const std::string& name)
{
    uint32_t hash = fnv1a(name.c_str(), name.size());

    auto it = m_knownAddons.find(hash);
    if (it == m_knownAddons.end())
        return nullptr;

    return &(it->second);
}

} // Namespace
