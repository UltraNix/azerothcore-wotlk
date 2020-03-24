

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