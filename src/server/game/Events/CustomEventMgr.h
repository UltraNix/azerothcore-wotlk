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

#ifndef TRINITY_CUSTOM_GAMEEVENT_MGR_H
#define TRINITY_CUSTOM_GAMEEVENT_MGR_H

#include "Common.h"
#include "SharedDefines.h"
#include "Define.h"
#include <ace/Singleton.h>
#include "SpellAuras.h"
#include "Chat.h"
#include "Item.h"

enum CustomEvents
{
    CUSTOM_EVENT_KRUUL = 0,
    CUSTOM_EVENT_FLUSH = 1,
    CUSTOM_EVENT_PVP = 2,
    CUSTOM_EVENT_HUNGER_GAMES = 3
};

enum HungerGamesState
{
    HUNGER_GAMES_NOT_STARTED = 0,
    HUNGER_GAMES_PREPARATION = 1,
    HUNGER_GAMES_STARTED = 2,
};

enum HungerGamesEvents {
    HUNGER_GAMES_EVENT_TELE = 0,
    HUNGER_GAMES_EVENT_REV = 1,
    HUNGER_GAMES_EVENT_FR = 2,
    HUNGER_GAMES_EVENT_UNFR = 3,
    HUNGER_GAMES_EVENT_DEBUFF = 4,
    HUNGER_GAMES_EVENT_TELE_HORDE = 5,
    HUNGER_GAMES_EVENT_TELE_DALA = 6,
};

Position const hungerGamesHordePos[15] =
{
    { -109.67f, 958.103f, 339.49f, 4.98f },
    { -99.04f, 910.49f, 339.33f, 5.65f },
    { -30.91f, 890.37f, 339.39f, 0.26f },
    { 24.97f, 918.73f, 339.39f, 0.51f },
    { 31.97f, 993.f, 339.39f, 6.12f },
    { 7.44f, 1066.85f, 358.51f, 5.08f },
    { 78.08f, 1125.20f, 367.18f, 5.54f },
    { 39.72f, 1176.f, 367.34f, 5.58f },
    { 127.f, 1109.13f, 337.35f, 5.64f },
    { 165.08f, 1086.30f, 344.4f, 4.19f },
    { 142.09f, 1032.94f, 296.47f, 4.88f },
    { 186.72f, 1016.24f, 300.11f, 2.74f },
    { 147.32f, 1002.6f, 295.45f, 3.39f },
    { 117.83f, 951.89f, 295.19f, 1.3f },
    { 124.84f, 951.23f, 295.17f, 2.72f }

};
typedef std::unordered_set<uint64> KruulGuidSet;

class CustomEventMgr
{
    CustomEventMgr() {}
    ~CustomEventMgr() {}

    ///////////////////////
    // Highlord Kruul
    //////////////////////
    uint32 KruulSpawnLoc = 0;
    bool KruulState = false;
    ///////////////////////
    // Arena Autoflush
    ///////////////////////
    bool FlushStatus = false;
    ///////////////////////
    // Arena PvP Event 
    ///////////////////////
    bool ArenaEventStatus = false;
    ///////////////////////
    // Hunger Games Event
    ///////////////////////
    std::vector<uint64> hungerGamesPlayers;
    std::vector<uint64> hungerGamesGMs;
    HungerGamesState hungerGamesState;
    uint32 hungerGamesUpdateTimer;
    HungerGamesEvents hungerGamesEvent;
    int8 hungerGamesTimedAnnSec;

    KruulGuidSet KruulList;

    public:
        static CustomEventMgr* instance();

        void InitCustomEventMgr();
        void Update(uint32, uint8);

        ///////////////////////
        // Highlord Kruul
        ///////////////////////
        int32 GetKruulDay() const;
        int32 GetKruulHour() const;
        int32 GetKruulMinute() const;
        uint32 GetKruulSpawnLoc() const;
        void   SetKruulSpawnLoc(uint32 location) { KruulSpawnLoc = location; }
        std::string GetKruulAnnouncePL() const;
        std::string GetKruulAnnounceEN() const;
        bool   GetKruulEventState() const;
        void   SetKruulEventState(bool started) { KruulState = started; }
        void   KruulListInsert(uint64 guid);
        bool   KruulListCheck(uint64 guid) const;

        ///////////////////////
        // Arena Autoflush
        ///////////////////////
        int32 GetFlushDay() const;
        int32 GetFlushHour() const;
        int32 GetFlushMinute() const;
        bool   GetFlushStatus() const;
        void   SetFlushStatus(bool flushed) { FlushStatus = flushed; }

        ///////////////////////
        // Arena PvP Event 
        ///////////////////////
        int32 GetArenaEventDay() const;
        int32 GetArenaEventHour() const;
        int32 GetArenaEventMinute() const;
        std::string GetEventPvPAnnouncesPL() const;
        std::string GetEventPvPAnnouncesEN() const;
        bool GetArenaEventStatus() const;
        void SetArenaEventStatus(bool started) { ArenaEventStatus = started; }

        ///////////////////////
        // Hunger Games Event
        ///////////////////////
        void addPlayerToHungerGames(uint64 guid);
        void addGmToHungerGames(uint64 guid);
        bool isGmInHungerGames(uint64 guid) const;
        void removeGmFromHungerGames(uint64 guid);
        void removePlayerFromHungerGames(uint64 guid);
        bool isPlayerInHungerGames(uint64 guid) const;
        void teleportHungerGamesPlayersToAzshara();
        void reviveHungerGamesPlayers();
        void freezeHungerGamesPlayers(bool freeze);
        HungerGamesState getHungerGamesState() const { return hungerGamesState; }
        size_t getHungerGamesPlayersCount() const { return hungerGamesPlayers.size(); }
        void resetHungerGamesState() { hungerGamesState = HUNGER_GAMES_NOT_STARTED; }
        bool isHungerGamesFull() const { return hungerGamesPlayers.size() >= sWorld->getIntConfig(CONFIG_HUNGER_GAMES_LIMIT); }
        void applyHungerGamesDebuff(bool apply);
        void sendAnnounceToHungerGamesPlayers(std::string msg, bool log = false);
        void startHungerGamesEvent(HungerGamesEvents e);
        void executeHungerGamesEvent();
        bool isHungerGamesEventInProgress() const { return hungerGamesTimedAnnSec != -1; }
        void teleportHungerGamesPlayersToHordeBase();
        void setPoiToHungerGamesPlayers(uint8 loc);
        void printHungerGamesPlayers(Player *p);
        void printHungerGamesGms(Player *p);
        void printHungerGamesStealthedPlayers(Player *p);
        void teleportWinnerToDalaran();
};

#define sCustomEventMgr CustomEventMgr::instance()

#endif