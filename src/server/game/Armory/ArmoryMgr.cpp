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

ArmoryMgr* ArmoryMgr::instance()
{				
    static ArmoryMgr instance;
    return &instance;		
}

void ArmoryMgr::InsertArmoryStats(Player* player, uint32 guid, uint32 guildId, uint32 creatureEntry, uint32 mapId, uint32 difficulity, uint32 groupCount, uint32 fightTime)
{
    if (!player)
        return;

    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement(CHAR_INS_ARMORY_STATS);
    stmt->setUInt32(0, guid);
    stmt->setUInt32(1, guildId);
    stmt->setUInt32(2, creatureEntry);
    stmt->setUInt32(3, mapId);
    stmt->setUInt32(4, difficulity);
    stmt->setUInt32(5, groupCount);
    stmt->setUInt32(6, GetMSTimeDiffToNow(fightTime));
    stmt->setUInt32(7, time(NULL));
    CharacterDatabase.Execute(stmt);
}

void ArmoryMgr::PrepareEncounterData(Map* map, Creature* creature, uint32 fightTime)
{
    if (!sWorld->getBoolConfig(CONFIG_ARMORY_STATS))
        return;

    if (!map || !creature)
        return;

    InstanceMap* playersMap = map->ToInstanceMap();
    if (!playersMap)
        return;

    Map::PlayerList const& pl = playersMap->GetPlayers();
    for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
        if (Player* p = itr->GetSource())
            InsertArmoryStats(p, p->GetGUIDLow(), p->GetGuildId(), creature->GetEntry(), playersMap->GetId(), uint32(playersMap->GetDifficulty()), playersMap->GetPlayersCountExceptGMs(), creature->GetBossFightTime());
}