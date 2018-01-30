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

#include "CustomEventMgr.h"
#include "World.h"
#include "ObjectMgr.h"
#include "Player.h"
#include "BattlegroundMgr.h"
#include "ArenaTeamMgr.h"
#include "Language.h"
#include "Group.h"

CustomEventMgr* CustomEventMgr::instance()
{
    static CustomEventMgr instance;
    return &instance;
}

void CustomEventMgr::InitCustomEventMgr()
{
    SetKruulSpawnLoc(urand(0, 8));
    KruulList.clear();

    switch (GetKruulSpawnLoc())
    {
        case 0:
            sLog->outMisc("Kruul Event - Rolled Locations: Stonetalon Mountains, Redridge Mountains");
            break;
        case 1:
            sLog->outMisc("Kruul Event - Rolled Locations: Thousand Needles, Badlands");
            break;
        case 2:
            sLog->outMisc("Kruul Event - Rolled Locations: Winterspring, Wetlands");
            break;
        case 3:
            sLog->outMisc("Kruul Event - Rolled Locations: Desolace, Lochmodan");
            break;
        case 4:
            sLog->outMisc("Kruul Event - Rolled Locations: Stonetalon Mountains, Lochmodan");
            break;
        case 5:
            sLog->outMisc("Kruul Event - Rolled Locations: Thousand Needles, Wetlands");
            break;
        case 6:
            sLog->outMisc("Kruul Event - Rolled Locations: Winterspring, Redridge Mountains");
            break;
        case 7:
            sLog->outMisc("Kruul Event - Rolled Locations: Desolace, Badlands");
            break;
        case 8:
            sLog->outMisc("Kruul Event - Rolled Locations: Durotar, Elwynn Forest");
            break;
    }
    hungerGamesState = HUNGER_GAMES_NOT_STARTED;
    hungerGamesUpdateTimer = 1000;
    hungerGamesTimedAnnSec = -1;
}
void CustomEventMgr::Update(uint32 diff, uint8 eventUpdate)
{
    time_t now = time(nullptr);
    tm* aTm = localtime(&now);

    switch (eventUpdate)
    {
        ///////////////////////
        // Highlord Kruul
        ///////////////////////
        case CUSTOM_EVENT_KRUUL:
        {
            if (sWorld->getBoolConfig(CONFIG_KRUUL_EVENT))
            {
                if (aTm->tm_wday == GetKruulDay() && aTm->tm_hour == GetKruulHour() && aTm->tm_min == GetKruulMinute() && !GetKruulEventState())
                {
                    SetKruulEventState(true);
                    sWorld->SendWorldText(LANG_AUTO_BROADCAST, GetKruulAnnouncePL().c_str());
                    sWorld->SendWorldText(LANG_AUTO_BROADCAST, GetKruulAnnounceEN().c_str());
                }

                if (aTm->tm_wday != GetKruulDay() && GetKruulEventState())
                {
                    SetKruulEventState(false);
                    KruulList.clear();
                }
            }

        } 
        break;
        ///////////////////////
        // Arena Autoflush
        ///////////////////////
        case CUSTOM_EVENT_FLUSH:
        {
            if (sWorld->getBoolConfig(CONFIG_ARENA_AUTO_FLUSH_ENABLE))
            {
                if (aTm->tm_wday == GetFlushDay() && aTm->tm_hour == GetFlushHour() && aTm->tm_min == GetFlushMinute() && !GetFlushStatus())
                {
                    SetFlushStatus(true);
                    sArenaTeamMgr->DistributeArenaPoints();
                }

                if (aTm->tm_wday != GetFlushDay() && GetFlushStatus())
                    SetFlushStatus(false);
            }
        }
        break;
        ///////////////////////
        // Arena PvP Event 
        ///////////////////////
        case CUSTOM_EVENT_PVP:
        {
            if (sWorld->getBoolConfig(CONFIG_ARENA_REWARD_ENABLE))
            {
                if (aTm->tm_wday == GetArenaEventDay() && aTm->tm_hour == GetArenaEventHour() && aTm->tm_min == GetArenaEventMinute() && !GetArenaEventStatus())
                {
                    SetArenaEventStatus(true);
                    sWorld->SendWorldText(LANG_AUTO_BROADCAST, GetEventPvPAnnouncesPL().c_str());
                    sWorld->SendWorldText(LANG_AUTO_BROADCAST, GetEventPvPAnnouncesEN().c_str());
                }

                if (aTm->tm_wday != GetArenaEventDay() && GetArenaEventStatus())
                    SetArenaEventStatus(false);
            }
        }
        break;
        ///////////////////////
        // Hunger Games Event
        ///////////////////////
        case CUSTOM_EVENT_HUNGER_GAMES:
        {
            if (!sWorld->getBoolConfig(CONFIG_HUNGER_GAMES_ENABLE)) 
                break;

            if (hungerGamesTimedAnnSec == -1) 
                break;
            if (diff >= hungerGamesUpdateTimer) 
            {
                hungerGamesUpdateTimer = 1000;

                if (hungerGamesTimedAnnSec == 0) 
                {
                    executeHungerGamesEvent();
                    --hungerGamesTimedAnnSec;
                    break;
                }
                std::string msg;
                switch (hungerGamesEvent) 
                {
                    case HUNGER_GAMES_EVENT_TELE:
                        msg = "You will be teleported to Azshara Crater in ";
                        break;
                    case HUNGER_GAMES_EVENT_REV:
                        msg = "You will be revived in ";
                        break;
                    case HUNGER_GAMES_EVENT_FR:
                        msg = "You will be freezed in ";
                        break;
                    case HUNGER_GAMES_EVENT_UNFR:
                        msg = "You will be unfreezed in ";
                        break;
                    case HUNGER_GAMES_EVENT_DEBUFF:
                        msg = "You will be debuffed in ";
                        break;
                    case HUNGER_GAMES_EVENT_TELE_HORDE:
                        msg = "You will be teleported to Horde base in ";
                        break;
                    case HUNGER_GAMES_EVENT_TELE_DALA:
                        msg = "You will be teleported to Dalaran in ";
                        break;
                }
                msg += std::to_string(hungerGamesTimedAnnSec) + " second" + ((hungerGamesTimedAnnSec != 1) ? "s!" : "!");
                --hungerGamesTimedAnnSec;
                sendAnnounceToHungerGamesPlayers(msg);

            }
            else hungerGamesUpdateTimer -= diff;
        }
        break;
    }
}


///////////////////////
// Highlord Kruul
///////////////////////

int32 CustomEventMgr::GetKruulDay() const { return uint32(sWorld->getIntConfig(CONFIG_KRUUL_EVENT_DAY)); }
int32 CustomEventMgr::GetKruulHour() const { return uint32(sWorld->getIntConfig(CONFIG_KRUUL_EVENT_HOUR)); }
int32 CustomEventMgr::GetKruulMinute() const { return uint32(sWorld->getIntConfig(CONFIG_KRUUL_EVENT_MINUTE)); }
uint32 CustomEventMgr::GetKruulSpawnLoc() const { return KruulSpawnLoc; }
std::string CustomEventMgr::GetKruulAnnouncePL() const { return "Highlord Kruul stapa po Azeroth. Czy znajda sie smialkowie ktorzy stawia mu czola?"; }
std::string CustomEventMgr::GetKruulAnnounceEN() const { return "Highlord Kruul has appeared in Azeroth. Will you choose to face him?"; }
bool CustomEventMgr::GetKruulEventState() const { return KruulState; }
void CustomEventMgr::KruulListInsert(uint64 guid) { KruulList.insert(guid); }
bool CustomEventMgr::KruulListCheck(uint64 guid) const { return KruulList.count(guid) != 0; }

///////////////////////
// Arena Autoflush
///////////////////////

int32 CustomEventMgr::GetFlushDay() const { return uint32(sWorld->getIntConfig(CONFIG_ARENA_AUTO_FLUSH_ENABLE_DAY)); }
int32 CustomEventMgr::GetFlushHour() const { return uint32(sWorld->getIntConfig(CONFIG_ARENA_AUTO_FLUSH_ENABLE_HOUR)); }
int32 CustomEventMgr::GetFlushMinute() const { return uint32(sWorld->getIntConfig(CONFIG_ARENA_AUTO_FLUSH_ENABLE_MINUTE)); }
bool CustomEventMgr::GetFlushStatus() const { return FlushStatus; }

///////////////////////
// Arena PvP Event 
///////////////////////

int32 CustomEventMgr::GetArenaEventDay() const {  return uint32(sWorld->getIntConfig(CONFIG_ARENA_EVENT_DAY)); }
int32 CustomEventMgr::GetArenaEventHour() const { return uint32(sWorld->getIntConfig(CONFIG_ARENA_EVENT_HOUR)); }
int32 CustomEventMgr::GetArenaEventMinute() const { return uint32(sWorld->getIntConfig(CONFIG_ARENA_EVENT_MINUTE)); }
std::string CustomEventMgr::GetEventPvPAnnouncesPL() const { return  "Event PvP wlasnie wystartowal! Do wygrania sa miedzy innymi epickie companiony oraz Swift Nether Drake - mount 310%"; }
std::string CustomEventMgr::GetEventPvPAnnouncesEN() const { return  "Event PvP has just launched! Play 2v2 or 3v3 and win fantastic rewards like epic companions or Swift Nether Drake - mount 310%."; }
bool CustomEventMgr::GetArenaEventStatus() const { return ArenaEventStatus; }

///////////////////////
// Hunger Games Event
///////////////////////

void CustomEventMgr::addPlayerToHungerGames(uint64 guid)
{
    if (isHungerGamesFull()) return;
    if (!isPlayerInHungerGames(guid)) hungerGamesPlayers.push_back(guid);
}

void CustomEventMgr::addGmToHungerGames(uint64 guid)
{
    if (!isGmInHungerGames(guid)) hungerGamesGMs.push_back(guid);
}

bool CustomEventMgr::isGmInHungerGames(uint64 guid) const
{
    return std::find(hungerGamesGMs.begin(), hungerGamesGMs.end(), guid) != hungerGamesGMs.end();
}

void CustomEventMgr::removeGmFromHungerGames(uint64 guid)
{
    auto itr = std::find(hungerGamesGMs.begin(), hungerGamesGMs.end(), guid);
    if (itr != hungerGamesGMs.end())
        hungerGamesGMs.erase(itr);
}

void CustomEventMgr::removePlayerFromHungerGames(uint64 guid)
{
    auto itr = std::find(hungerGamesPlayers.begin(), hungerGamesPlayers.end(), guid);
    if (itr != hungerGamesPlayers.end())
        hungerGamesPlayers.erase(itr);
    if (hungerGamesPlayers.size() == 1)
    {
        if (Player *winner = ObjectAccessor::FindPlayer(hungerGamesPlayers[0]))
        {
            std::string msg = "Hunger Games has ended. The winner is " + winner->GetName() + ". Congratulations!";
            sendAnnounceToHungerGamesPlayers(msg, true);
            startHungerGamesEvent(HUNGER_GAMES_EVENT_TELE_DALA);
        }
    }
}

bool CustomEventMgr::isPlayerInHungerGames(uint64 guid) const
{
    return std::find(hungerGamesPlayers.begin(), hungerGamesPlayers.end(), guid) != hungerGamesPlayers.end();
}

void CustomEventMgr::teleportHungerGamesPlayersToAzshara()
{
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(8326);
    for (auto &guid : hungerGamesPlayers) {
        if (Player *p = ObjectAccessor::FindPlayer(guid)) {
            if (Group *group = p->GetGroup()) group->RemoveMember(p->GetGUID());
            if (p->GetTeamId() == TEAM_ALLIANCE)
                p->TeleportTo(37, 1038.33f, 293.55f, 335.30f, 3.39f);
            else
                p->TeleportTo(37, 26.89f, 904.84f, 339.39f, 5.34f);
            if (spellInfo)
                Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, p, p);
            p->RemoveArenaAuras();
            p->SetHealth(p->GetMaxHealth());
            if (p->getPowerType() == POWER_MANA)
                p->SetPower(POWER_MANA, p->GetMaxPower(POWER_MANA));
            p->RemoveArenaSpellCooldowns();
        }
    }
    hungerGamesState = HUNGER_GAMES_PREPARATION;
}

void CustomEventMgr::reviveHungerGamesPlayers()
{
    for (auto &guid : hungerGamesPlayers) {
        if (Player *p = ObjectAccessor::FindPlayer(guid)) {
            p->RemoveAurasDueToSpell(8326);
        }
    }
    hungerGamesState = HUNGER_GAMES_STARTED;
}

void CustomEventMgr::freezeHungerGamesPlayers(bool freeze)
{
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(9454);
    for (auto &guid : hungerGamesPlayers) {
        if (Player *p = ObjectAccessor::FindPlayer(guid)) {
            if (freeze)
            {
                p->RemoveArenaAuras();
                if (spellInfo)
                    Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, p, p);

            }
            else
                p->RemoveAurasDueToSpell(9454);
        }
    }
}

void CustomEventMgr::applyHungerGamesDebuff(bool apply)
{
    SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(46392);
    for (auto &guid : hungerGamesPlayers) {
        if (Player *p = ObjectAccessor::FindPlayer(guid)) {
            if (apply)
            {
                if (spellInfo)
                    Aura::TryRefreshStackOrCreate(spellInfo, MAX_EFFECT_MASK, p, p);
            }
            else
                p->RemoveAurasDueToSpell(46392);
        }
    }
}

void CustomEventMgr::sendAnnounceToHungerGamesPlayers(std::string msg, bool log)
{
    WorldPacket data;
    ChatHandler::BuildChatPacket(data, CHAT_MSG_RAID_WARNING, Language::LANG_UNIVERSAL, NULL, NULL, msg);
    for (auto &guid : hungerGamesPlayers) {
        if (Player *p = ObjectAccessor::FindPlayer(guid))
            p->GetSession()->SendPacket(&data);
    }
    for (auto &guid : hungerGamesGMs) {
        if (Player *p = ObjectAccessor::FindPlayer(guid))
            p->GetSession()->SendPacket(&data);
    }
    if (log)
        sLog->outRewards(msg.c_str());
}

void CustomEventMgr::startHungerGamesEvent(HungerGamesEvents h)
{
    if (h == HUNGER_GAMES_EVENT_TELE)
        hungerGamesState = HUNGER_GAMES_PREPARATION;

    if (isHungerGamesEventInProgress()) 
        return;
    hungerGamesTimedAnnSec = 5;
    hungerGamesEvent = h;
    hungerGamesUpdateTimer = (h == HUNGER_GAMES_EVENT_TELE_DALA) ? 3000 : 0;
}

void CustomEventMgr::executeHungerGamesEvent()
{
    switch (hungerGamesEvent)
    {
        case HUNGER_GAMES_EVENT_TELE:
            teleportHungerGamesPlayersToAzshara();
            break;
        case HUNGER_GAMES_EVENT_REV:
            reviveHungerGamesPlayers();
            break;
        case HUNGER_GAMES_EVENT_FR:
            freezeHungerGamesPlayers(true);
            break;
        case HUNGER_GAMES_EVENT_UNFR:
            freezeHungerGamesPlayers(false);
            break;
        case HUNGER_GAMES_EVENT_DEBUFF:
            applyHungerGamesDebuff(true);
            break;
        case HUNGER_GAMES_EVENT_TELE_HORDE:
            teleportHungerGamesPlayersToHordeBase();
            break;
        case HUNGER_GAMES_EVENT_TELE_DALA:
            teleportWinnerToDalaran();
            break;
    }
}

void CustomEventMgr::teleportHungerGamesPlayersToHordeBase()
{
    uint8 posIndex = 0;
    for (auto &guid : hungerGamesPlayers)
    {
        if (Player *p = ObjectAccessor::FindPlayer(guid))
        {
            p->SetHealth(p->GetMaxHealth());
            if (p->getPowerType() == POWER_MANA)
                p->SetPower(POWER_MANA, p->GetMaxPower(POWER_MANA));

            p->TeleportTo(37, hungerGamesHordePos[posIndex].m_positionX, hungerGamesHordePos[posIndex].m_positionY, hungerGamesHordePos[posIndex].m_positionZ, hungerGamesHordePos[posIndex].m_orientation);
            posIndex = (posIndex + 1) % 15;
        }

    }
}

void CustomEventMgr::setPoiToHungerGamesPlayers(uint8 loc)
{
    if (loc >= 3) 
        return;

    for (auto &guid : hungerGamesPlayers)
    {
        if (Player *p = ObjectAccessor::FindPlayer(guid))
            p->PlayerTalkClass->SendPointOfInterest(2000 + loc);
    }

    for (auto &guid : hungerGamesGMs)
    {
        if (Player *p = ObjectAccessor::FindPlayer(guid))
            if (p->GetMapId() == 37)
                p->PlayerTalkClass->SendPointOfInterest(2000 + loc);
    }
}

void CustomEventMgr::printHungerGamesPlayers(Player * p)
{
    if (!p || !p->IsInWorld() || !p->GetSession()) 
        return;

    ChatHandler ch(p->GetSession());
    uint32 index = 1;

    for (auto &guid : hungerGamesPlayers)
    {
        if (Player *pp = ObjectAccessor::FindPlayer(guid))
            ch.PSendSysMessage("%d. %s", index++, pp->GetName().c_str());
    }
}

void CustomEventMgr::printHungerGamesGms(Player * p)
{
    if (!p || !p->IsInWorld() || !p->GetSession()) 
        return;

    ChatHandler ch(p->GetSession());
    ch.PSendSysMessage("Lista GMow monitorujacych event:");
    uint32 index = 1;

    for (auto &guid : hungerGamesGMs) 
    {
        if (Player *pp = ObjectAccessor::FindPlayer(guid))
            ch.PSendSysMessage("%d. %s", index++, pp->GetName().c_str());
    }
}

void CustomEventMgr::printHungerGamesStealthedPlayers(Player * p)
{
    if (!p || !p->IsInWorld() || !p->GetSession())
        return;
    ChatHandler ch(p->GetSession());
    ch.PSendSysMessage("Lista graczy ukrywajacych sie w stealth:");
    uint32 index = 1;

    for (auto &guid : hungerGamesPlayers)
    {
        if (Player *pp = ObjectAccessor::FindPlayer(guid)) 
        {
            if (pp->HasAuraType(SPELL_AURA_MOD_STEALTH))
                ch.PSendSysMessage("%d. %s", index++, pp->GetName().c_str());
        }
    }
}

void CustomEventMgr::teleportWinnerToDalaran()
{
    // This method should be executed only when there is only one player left in hunger games (winner)
    if (hungerGamesPlayers.size() != 1) 
        return;

    if (Player *p = ObjectAccessor::FindPlayer(hungerGamesPlayers[0]))
        p->TeleportTo(571, 5804.15f, 624.77f, 647.76f, 1.64f);
}