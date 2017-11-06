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

CustomEventMgr::CustomEventMgr() {}
CustomEventMgr::~CustomEventMgr() {}

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
}
void CustomEventMgr::Update(uint32 diff, uint8 eventUpdate)
{
    time_t now = time(NULL);
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
                    sWorld->SendWorldText(LANG_AUTO_BROADCAST, GetEventPvPAnnouncePL().c_str());
                    sWorld->SendWorldText(LANG_AUTO_BROADCAST, GetEventPvPAnnounceEN().c_str());
                }

                if (aTm->tm_wday != GetArenaEventDay() && GetArenaEventStatus())
                    SetArenaEventStatus(false);
            }
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
std::string CustomEventMgr::GetEventPvPAnnouncePL() const { return  "Event PvP wlasnie wystartowal! Do wygrania sa miedzy innymi epickie companiony oraz Swift Nether Drake - mount 310%"; }
std::string CustomEventMgr::GetEventPvPAnnounceEN() const { return  "Event PvP has just launched! Play 2v2 or 3v3 and win fantastic rewards like epic companions or Swift Nether Drake - mount 310%."; }
bool CustomEventMgr::GetArenaEventStatus() const { return ArenaEventStatus; }