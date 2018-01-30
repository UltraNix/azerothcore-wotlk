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

#ifndef SC_SUNWELL_CHEAT_H
#define SC_SUNWELL_CHEAT_H

#include "Common.h"
#include "SharedDefines.h"
#include "Language.h"
#include "Player.h"
#include "Chat.h"

enum SunwellCheck
{
    CHECK_DOS_OPCODE = 0,
    CHECK_CAST_ABUSE = 1,
    MAX_CHECK_TYPES
};

enum SunwellAction
{
    SUN_ACTION_LOG  = 0,
    SUN_ACTION_KICK = 1,
    SUN_ACTION_BAN  = 2
};

class SunwellCheat
{
    public:
        SunwellCheat();
        ~SunwellCheat();

        static SunwellCheat* instance();

        //////////////////
        // Cleanup
        void cleanupReports(Player* player);
        //////////////////
        // opCounter
        void buildOpcodeReport(Player* player, uint16 opCode);
        //////////////////
        // goldAbuse
        void buildCastReport(Player* player, uint32 spellId);


    private:
        void buildCheatReport(uint32 amount, SunwellCheck type) { cheaterReports[type] = amount; }
        void clearCheatReport(SunwellCheck type) { cheaterReports[type] = 0; }
        void setCheatTimer(uint32 time, SunwellCheck type) { cheaterTimer[type] = time; }
        time_t getCheatTimer(SunwellCheck type) { return cheaterTimer[type]; }
        uint32 getCheaterRepors(SunwellCheck type) { return cheaterReports[type]; }

        uint32 cheaterReports[MAX_CHECK_TYPES];
        time_t cheaterTimer[MAX_CHECK_TYPES];
        typedef std::map<uint32, SunwellCheat> CheatersMap;
        CheatersMap cheaterPlayers;
};

#define sSunwellCheatMgr SunwellCheat::instance()

#endif