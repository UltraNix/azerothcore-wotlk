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

enum CustomEvents
{
    CUSTOM_EVENT_KRUUL = 0,
    CUSTOM_EVENT_FLUSH = 1,
    CUSTOM_EVENT_PVP   = 2
};

class CustomEventMgr
{
    CustomEventMgr();
    ~CustomEventMgr();

    public:
        static CustomEventMgr* instance()
        {
            static CustomEventMgr* instance = new CustomEventMgr();
            return instance;
        }

        void InitCustomEventMgr();
        void Update(uint32, uint8);

        ///////////////////////
        // Highlord Kruul
        ///////////////////////
        uint32 GetKruulDay() const;
        uint32 GetKruulHour() const;
        uint32 GetKruulMinute() const;
        uint32 GetKruulSpawnLoc() const;
        void   SetKruulSpawnLoc(uint32 location) { KruulSpawnLoc = location; }
        std::string GetKruulAnnouncePL() const;
        std::string GetKruulAnnounceEN() const;
        bool   GetKruulSpawn() const;
        void   SetKruulSpawn(bool spawn) { KruulSpawn = spawn; }
        bool   GetKruulScriptSpawn() const;
        void   SetKruulScriptSpawn(bool spawn) { KruulScriptSpawn = spawn; }


        ///////////////////////
        // Arena Autoflush
        ///////////////////////
        uint32 GetFlushDay() const;
        uint32 GetFlushHour() const;
        uint32 GetFlushMinute() const;
        bool   GetFlushStatus() const;
        void   SetFlushStatus(bool flushed) { FlushStatus = flushed; }
        ///////////////////////
        // Arena PvP Event 
        ///////////////////////
        uint32 GetArenaEventDay() const;
        uint32 GetArenaEventHour() const;
        uint32 GetArenaEventMinute() const;
        std::string GetEventPvPAnnouncePL() const;
        std::string GetEventPvPAnnounceEN() const;
        bool GetArenaEventStatus() const;
        void SetArenaEventStatus(bool started) { ArenaEventStatus = started; }
    private:
        ///////////////////////
        // Highlord Kruul
        //////////////////////
        uint32 KruulSpawnLoc = 0;
        bool KruulSpawn = false;
        bool KruulScriptSpawn = false;
        ///////////////////////
        // Arena Autoflush
        ///////////////////////
        bool FlushStatus = false;
        ///////////////////////
        // Arena PvP Event 
        ///////////////////////
        bool ArenaEventStatus = false;     
};

#define sCustomEventMgr CustomEventMgr::instance()

#endif