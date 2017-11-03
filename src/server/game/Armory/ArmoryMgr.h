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

#ifndef SC_ARMGR_H
#define SC_ARMGR_H

#include "Common.h"
#include "SharedDefines.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"
#include "AccountMgr.h"

class ArmoryMgr
{
    ArmoryMgr();
    ~ArmoryMgr();

    time_t encounterStart;

    public:
        static ArmoryMgr* instance()
        {
            static ArmoryMgr* instance = new ArmoryMgr();
            return instance;
        }
        
        void PrepareEncounterData(Map* map, EncounterCreditType type, uint32 creditEntry);
        void InsertArmoryStats(Player* player, uint32 guid, uint32 guild, uint32 bossEntry, uint32 mapId, uint32 difficulityMap, uint32 playersCount, time_t time, time_t eventTime);
        void SetEnounterStartTime(time_t startTime) { encounterStart = startTime; }
};

#define sArmoryMgr ArmoryMgr::instance()

#endif