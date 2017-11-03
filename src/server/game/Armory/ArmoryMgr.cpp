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

#include "ArmoryMgr.h"
#include "Map.h"

ArmoryMgr::ArmoryMgr() { }
ArmoryMgr::~ArmoryMgr() { }

void ArmoryMgr::InsertArmoryStats(Player* player, uint32 guid, uint32 guild, uint32 bossEntry, uint32 mapId, uint32 difficulityMap, uint32 playersCount, time_t time, time_t eventTime)
{
    if (!player)
        return;

    time_t encounterProgress = time - encounterStart;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_BAZAR_AUCTION);
    stmt->setUInt32(0, NULL);
    stmt->setUInt32(1, player->GetGUIDLow());
    stmt->setUInt32(2, guild);
    stmt->setUInt32(3, bossEntry);
    stmt->setUInt32(4, mapId);
    stmt->setUInt32(5, difficulityMap);
    stmt->setUInt32(6, playersCount);
    stmt->setUInt32(7, encounterProgress);
    stmt->setUInt32(8, eventTime);
    CharacterDatabase.Execute(stmt);
}

void ArmoryMgr::PrepareEncounterData(Map* map, EncounterCreditType type, uint32 creditEntry)
{
    if (!map->IsRaid() || !map->GetEntry())
        return;

    InstanceMap* map = map->ToInstanceMap();
    if (!map)
        return;

    Map::PlayerList const& pl = map->GetPlayers();
    for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
        if (Player* p = itr->GetSource())
            //InsertArmoryStats(p, p->GetGUIDLow(), p->GetGuildId(), creditEntry, map->GetId(), uint32(map->GetDifficulty());
}