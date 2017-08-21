#include "ScriptPCH.h"

class Gambling : public PlayerScript
{
public:
    Gambling(): PlayerScript("Gambling") {}

    void OnDuelRequest(Player* target, Player* challenger) override
    { 
        if (!sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
            return;

        if (challenger->GetZoneId() == 41 && challenger->GetPositionZ() > 4.0f && challenger->GetPositionZ() < 6.0f || target->GetZoneId() == 41 && target->GetPositionZ() > 4.0f && target->GetPositionZ() < 6.0f)
        {
            if (challenger->hasGoldDuelSetting50G())
            {
                challenger->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 50 gold!");
                target->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 50 gold! Akceptujesz?");
            }
            else if (challenger->hasGoldDuelSetting100G())
            {
                challenger->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 100 gold!");
                target->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 100 gold! Akceptujesz?");
            }
            else if (challenger->hasGoldDuelSetting200G())
            {
                challenger->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 200 gold!");
                target->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 200 gold! Akceptujesz?");
            }
            else if (challenger->hasGoldDuelSetting500G())
            {
                challenger->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 500 gold!");
                target->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 500 gold! Akceptujesz?");
            }
            else if (challenger->hasGoldDuelSetting1000G())
            {
                challenger->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 1000 gold!");
                target->GetSession()->SendNotification("|cffffffff[PvP] Duel bedzie sie toczyc o stawke 1000 gold! Akceptujesz?");
            }
        }
    }

    void OnDuelEnd(Player* winner, Player* loser, Player* initiator, DuelCompleteType type) override
    {
        if (!sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE))
            return;

        int32 gold_setting_1 = 50 * GOLD;
        int32 gold_setting_2 = 100 * GOLD;
        int32 gold_setting_3 = 200 * GOLD;
        int32 gold_setting_4 = 500 * GOLD;
        int32 gold_setting_5 = 1000 * GOLD;
        float TAX_RATE = 0.9f;

        if (type != DUEL_INTERRUPTED && winner->duel->startTime != 0)
        {
            if (winner->GetZoneId() == 41 && winner->GetPositionZ() > 4.0f && winner->GetPositionZ() < 6.0f
                || loser->GetZoneId() == 41 && loser->GetPositionZ() > 4.0f && loser->GetPositionZ() < 6.0f && type == DUEL_WON)
            {
                if (initiator->hasGoldDuelSetting50G())
                {
                    if (loser->HasEnoughMoney(gold_setting_1))
                    {
                        winner->ModifyMoney(gold_setting_1 * TAX_RATE);
                        winner->GetSession()->SendNotification("|cffffffff[PvP] Wygrales 50 gold! (-10% Podatek)");

                        loser->ModifyMoney(-gold_setting_1);
                        loser->GetSession()->SendNotification("|cffffffff[PvP] Przegrales 50 gold!");
                    }
                    else
                        GamblingFail(winner, loser);
                }
                else if (initiator->hasGoldDuelSetting100G())
                {
                    if (loser->HasEnoughMoney(gold_setting_2))
                    {
                        winner->ModifyMoney(gold_setting_2 * TAX_RATE);
                        winner->GetSession()->SendNotification("|cffffffff[PvP] Wygrales 100 gold (-10% Podatek)!");

                        loser->ModifyMoney(-gold_setting_2);
                        loser->GetSession()->SendNotification("|cffffffff[PvP] Przegrales 100 gold!");
                    }
                    else
                        GamblingFail(winner, loser);
                }
                else if (initiator->hasGoldDuelSetting200G())
                {
                    if (loser->HasEnoughMoney(gold_setting_3))
                    {
                        winner->ModifyMoney(gold_setting_3 * TAX_RATE);
                        winner->GetSession()->SendNotification("|cffffffff[PvP] Wygrales 200 gold! (-10% Podatek)");

                        loser->ModifyMoney(-gold_setting_3);
                        loser->GetSession()->SendNotification("|cffffffff[PvP] Przegrales 200 gold!");
                    }
                    else
                        GamblingFail(winner, loser);
                }
                else if (initiator->hasGoldDuelSetting500G())
                {
                    if (loser->HasEnoughMoney(gold_setting_4))
                    {
                        winner->ModifyMoney(gold_setting_4 * TAX_RATE);
                        winner->GetSession()->SendNotification("|cffffffff[PvP] Wygrales 500 gold! (-10% Podatek)");

                        loser->ModifyMoney(-gold_setting_4);
                        loser->GetSession()->SendNotification("|cffffffff[PvP] Przegrales 500 gold!");
                    }
                    else
                        GamblingFail(winner, loser);
                }
                else if (initiator->hasGoldDuelSetting1000G())
                {
                    if (loser->HasEnoughMoney(gold_setting_5))
                    {
                        winner->ModifyMoney(gold_setting_5 * TAX_RATE);
                        winner->GetSession()->SendNotification("|cffffffff[PvP] Wygrales 1000 gold! (-10% Podatek)");

                        loser->ModifyMoney(-gold_setting_5);
                        loser->GetSession()->SendNotification("|cffffffff[PvP] Przegrales 1000 gold!");
                    }
                    else
                        GamblingFail(winner, loser);
                }
            }
        }
    }

    void GamblingFail(Player* winner, Player* loser)
    {
        if (!winner || loser)
            return;

        winner->GetSession()->SendNotification("|cffffffff[PvP] Zaklad przerwany! Przeciwnik stracil swoj majatek w czasie trwania walki!");
        loser->GetSession()->SendNotification("|cffffffff[PvP] Zaklad przerwany! Straciles swoj majatek w czasie trwania walki!");
    }
};

/*######
## npc_gambler
######*/

enum GamblerEnums
{
    GAMBLER_HELLO_TEXT = 1000024,
    GAMBLER_INFO_TEXT  = 1000025
};

class npc_gambler : public CreatureScript
{
public:
    npc_gambler() : CreatureScript("npc_gambler") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (sWorld->getBoolConfig(CONFIG_GAMBLING_ENABLE) && !player->duel)
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 50 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 100 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 200 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 500 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Stawka: 1000 gold.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Resetuj stawke.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "O co chodzi z pojedynkami za gold?", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);

            player->SEND_GOSSIP_MENU(GAMBLER_HELLO_TEXT, creature->GetGUID());
        }
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();

        bool close = true;

        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->SetResetDuelSetting();
                player->SetDuelSetting50G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->SetResetDuelSetting();
                player->SetDuelSetting100G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 3:
                player->SetResetDuelSetting();
                player->SetDuelSetting200G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 4:
                player->SetResetDuelSetting();
                player->SetDuelSetting500G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 5:
                player->SetResetDuelSetting();
                player->SetDuelSetting1000G();
                break;
            case GOSSIP_ACTION_INFO_DEF + 6:
                player->SetResetDuelSetting();
                break;
            case GOSSIP_ACTION_INFO_DEF + 7:
                close = false;
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Dziekuje za wyjasnienie.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
                player->SEND_GOSSIP_MENU(GAMBLER_INFO_TEXT, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 8:
                player->CLOSE_GOSSIP_MENU();
                break;
        }

        if (close)
            player->CLOSE_GOSSIP_MENU();

        // Prevent cheating.
        if (player->duel)
            player->SetResetDuelSetting();

        return true;
    }
};

void AddSC_Gambling()
{
    new Gambling();
    new npc_gambler();
}