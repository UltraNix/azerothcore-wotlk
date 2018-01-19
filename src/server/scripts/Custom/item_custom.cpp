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

/* ScriptData
SDName: item_custom
SD%Complete: 100
SDComment: Items for a range of different items. See content below (in script)
SDCategory: NPCs
EndScriptData
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "Spell.h"
#include "Player.h"

/*#####
# item_mysterious_time_pack
# Not used right now.

class item_mysterious_time_pack : public ItemScript
{
public:
    item_mysterious_time_pack() : ItemScript("item_mysterious_time_pack") { }

    bool OnExpire(Player* player, ItemTemplate const* /*pItemProto)
    {
        ItemPosCountVec dest;
        uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, 82000, 1); // Mysterious Time Pack
        if (msg == EQUIP_ERR_OK)
            player->StoreNewItem(dest, 82000, true, Item::GenerateItemRandomPropertyId(82000));

        return true;
    }
};

#####*/

void AddSC_item_custom()
{
    // new item_mysterious_time_pack();
}