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

std::vector<std::string> chinaTags =
{
    "€",
    "usd",
    " eur ",
    " usd!",
    " eur!",
    " usd.",
    " eur.",
    " wvvw",
    "angrathar.com",
    "angrathardotcom"
    "buy gold",
    "gold stock",
    "free gold",
    "cheap gold",
    "sell gold",
    "real money"
};

void LookForGoldMessage(Player* player, std::string& msg, uint32 lang)
{
    if (!sWorld->getBoolConfig(CONFIG_CHINA_TOWN) || lang == LANG_ADDON)
        return;

    bool found = false;
    // transform to lowercase (for simpler checking)
    std::string lower = msg; 
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    for (uint8 i = 0; i < chinaTags.size(); ++i)
        if (lower.find(chinaTags[i]) != std::string::npos)
            found = true;

    if (found && !player->IsGoldSeller())
    {
        player->SetGoldSeller(true);
        player->UpdateChinaTownTimer(time(nullptr), true);

        sWorld->SendGMText(LANG_POSSIBLE_GOLD_SELLER, player->GetName().c_str(), msg.c_str());
        sLog->outChinaTown("Player: %s (Account: %u) has send a message: %s", player->GetName().c_str(), player->GetSession()->GetAccountId(), msg.c_str());
    }
}