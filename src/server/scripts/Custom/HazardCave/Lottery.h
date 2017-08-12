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

#include "ScriptPCH.h"
#include "Config.h"
#include "Language.h"
#include "Player.h"
#include "Language.h"
#include "Chat.h"
#include "GameEventMgr.h"
#include "World.h"
#include "AccountMgr.h"
#include <algorithm>

enum LotteryType 
{
    GOLD_LOTTERY          = 0,
    SUNWELL_COINS_LOTTERY = 1
};

#define LOTTERY_ENABLE        true
#define LOTTERY_MINLVL        69
#define LOTTERY_BETCOST       100 * 10000 // 10 Gold
#define LOTTERY_COINS_BETCOST 50
#define LOTTERY_SC_BETCOST    10
#define LOTTERY_MAXNUMBER     30          // 1 - 30
#define LOTTERY_FIELDS        4	          // how many numbers? (e.g. '5 10 22 3 25')
#define LOTTERY_BETCOUNT      5

class Lottery 
{
    public:
        static bool randomItemWithPercent(Player* player, uint32 itemId, float winChance);
        static bool AddNumbers(const char * code, Player * player, Creature * pCreature, LotteryType type);
        static bool contains(uint32 *arrayWithNumbers, uint32 size, uint32 value);
        static bool equals(uint32* arrayFirst, uint32* arraySecond);
        static void modifyLotteryPoints(Player *player, int32 amount);
        static bool hasLotteryPoints(Player *player, uint32 amount);
        static void modifySunwellPoints(Player *player, int32 amount);
        static void modifySunwellPoints(std::string name, int32 amount);
        static bool hasSunwellPoints(Player *player, uint32 amount);
        static void findWinners(Creature * pCreature, LotteryType type);
        static void showNumbers(Creature * pCreature, Player * player, LotteryType type);
};

struct sWinner
{
    uint32 guid;
    uint32 points;

    std::string name;
    std::string bets;
};