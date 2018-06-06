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

#include "SunwellCheat.h"

SunwellCheatData::SunwellCheatData()
{
    for ( uint8 i = 0; i < MAX_CHECK_TYPES; ++i )
    {
        m_cheaterReports[ i ] = 0;
        m_cheaterTimer[ i ] = 0;
    }
}

void SunwellCheatData::buildCheatReport( uint32 amount, SunwellCheck type )
{
    m_cheaterReports[ type ] = amount;
}

void SunwellCheatData::clearCheatReport( SunwellCheck type )
{
    m_cheaterReports[ type ] = 0;
}

void SunwellCheatData::setCheatTimer( uint32 time, SunwellCheck type )
{
    m_cheaterTimer[ type ] = time;
}

time_t SunwellCheatData::getCheatTimer( SunwellCheck type )
{
    return m_cheaterTimer[ type ];
}

uint32 SunwellCheatData::getCheaterRepors( SunwellCheck type )
{
    return m_cheaterReports[ type ];
}

SunwellCheat* SunwellCheat::instance()
{
    static SunwellCheat instance;
    return &instance;
}

//////////////////
// Cleanup
//////////////////
void SunwellCheat::cleanupReports(Player* player)
{
    if (!sWorld->getBoolConfig(CONFIG_SUNWELL_CHEAT) || !player || !player->IsInWorld())
        return;

    time_t actualTime = sWorld->GetGameTime();
    uint32 nextTick   = sWorld->getIntConfig(CONFIG_SUNWELL_CHEAT_CLEAN_TIMER) * MINUTE;

    auto it = m_cheaterPlayers.find( player->GetGUIDLow() );
    if ( it == m_cheaterPlayers.end() )
        return;

    SunwellCheatData & cheatData = it->second;
    for (uint8 i = 0; i < MAX_CHECK_TYPES; ++i)
    {
        if ( actualTime > cheatData.getCheatTimer( SunwellCheck( i ) ) )
        {
            cheatData.setCheatTimer( actualTime + nextTick, SunwellCheck( i ) );
            cheatData.clearCheatReport( SunwellCheck( i ) );
        }
    }
}

//////////////////
// opCounter
//////////////////
void SunwellCheat::buildOpcodeReport(Player* player, uint16 opCode)
{
    if (!sWorld->getBoolConfig(CONFIG_SUNWELL_CHEAT) || !player || !opCode)
        return;
    
    SunwellCheatData & cheatData = m_cheaterPlayers[ player->GetGUIDLow() ];

    uint32 opCounter  = cheatData.getCheaterRepors(CHECK_DOS_OPCODE);
    uint32 opLimit    = sWorld->getIntConfig(CONFIG_SUNWELL_CHEAT_OPCODE_LIMIT);

    // Push another report.
    cheatData.buildCheatReport(++opCounter, CHECK_DOS_OPCODE);

    if (opCounter >= opLimit)
    {
        uint32 action = sWorld->getIntConfig(CONFIG_SUNWELL_CHEAT_OPCODE_ACTION);

        switch (action)
        {
            case SUN_ACTION_LOG:
                sLog->outCheat("[SunwellCheat] Player %s (GUID: %u) (Account ID: %u) has been reported due to possible DOS flooding! opCode: %u count: %u",
                    player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), opCode, opCounter);
                break;
            case SUN_ACTION_KICK:
                sLog->outCheat("[SunwellCheat] Player %s (GUID: %u) (Account ID: %u) has been kicked due to possible DOS flooding! opCode: %u count: %u",
                    player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), opCode, opCounter);
                player->GetSession()->KickPlayer();
                break;
            case SUN_ACTION_BAN:
            {
                BanMode bm = (BanMode)action;

                uint32 duration = sWorld->getIntConfig(CONFIG_SUNWELL_CHEAT_DURATION);
                std::string nameOrIp = "";

                switch (bm)
                {
                    case BAN_CHARACTER: // not supported, ban account
                    case BAN_ACCOUNT: (void)AccountMgr::GetName(player->GetSession()->GetAccountId(), nameOrIp); break;
                    case BAN_IP: nameOrIp = player->GetSession()->GetRemoteAddress(); break;
                }

                sWorld->BanAccount(bm, nameOrIp, duration, "DOS (Packet Flooding or Spoofing)", "[SunwellCheat]");
                sLog->outCheat("[SunwellCheat] Player %s (GUID: %u) (Account ID: %u) has been banned for %u minutes due to possible DOS flooding! opCode: %u count: %u",
                    player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), duration / MINUTE, opCode, opCounter);

                player->GetSession()->KickPlayer();
            }
            default:
                break;
        }

        if (!sWorld->getBoolConfig(CONFIG_SUNWELL_CHEAT_NOTIFY))
            return;

        sWorld->SendGMText(LANG_SUNWELLCHEAT_DOS, player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), opCode, opCounter);
    }
}

//////////////////
// goldAbuse
//////////////////
void SunwellCheat::buildCastReport(Player* player, uint32 spellId)
{
    if (!sWorld->getBoolConfig(CONFIG_SUNWELL_CHEAT) || !player || !spellId)
        return;

    SunwellCheatData & cheatData = m_cheaterPlayers[ player->GetGUIDLow() ];

    uint32 castCounter = cheatData.getCheaterRepors(CHECK_CAST_ABUSE);
    uint32 castLimit   = sWorld->getIntConfig(CONFIG_SUNWELL_CHEAT_CAST_LIMIT);

    // Push another report.
    cheatData.buildCheatReport(++castCounter, CHECK_CAST_ABUSE);

    if (castCounter >= castLimit)
    {
        uint32 action = sWorld->getIntConfig(CONFIG_SUNWELL_CHEAT_CAST_ACTION);

        switch (action)
        {
            case SUN_ACTION_LOG:
                sLog->outCheat("[SunwellCheat] Player %s (GUID: %u) (Account ID: %u) has been reported due to casted spell: %u over: %u times! Possible gold cheater!",
                    player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), spellId, castCounter);
                break;
            case SUN_ACTION_KICK:
                sLog->outCheat("[SunwellCheat] Player %s (GUID: %u) (Account ID: %u) has been kicked due to casted spell: %u over: %u times! Possible gold cheater!",
                    player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), spellId, castCounter);
                player->GetSession()->KickPlayer();
                break;
            case SUN_ACTION_BAN:
            {
                BanMode bm = (BanMode)action;

                uint32 duration = sWorld->getIntConfig(CONFIG_SUNWELL_CHEAT_DURATION);
                std::string nameOrIp = "";

                switch (bm)
                {
                    case BAN_CHARACTER: // not supported, ban account
                    case BAN_ACCOUNT: (void)AccountMgr::GetName(player->GetSession()->GetAccountId(), nameOrIp); break;
                    case BAN_IP: nameOrIp = player->GetSession()->GetRemoteAddress(); break;
                }

                sWorld->BanAccount(bm, nameOrIp, duration, "DOS (Packet Flooding or Spoofing)", "[SunwellCheat]");
                sLog->outCheat("[SunwellCheat] Player %s (GUID: %u) (Account ID: %u) has been banned for %u due to casted spell: %u over: %u times! Possible gold cheater!",
                    player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), duration / MINUTE, spellId, castCounter);

                player->GetSession()->KickPlayer();
            }
            default:
                break;
        }

        if (!sWorld->getBoolConfig(CONFIG_SUNWELL_CHEAT_NOTIFY))
            return;

        sWorld->SendGMText(LANG_SUNWELLCHEAT_GOLD, player->GetName().c_str(), player->GetGUID(), player->GetSession()->GetAccountId(), spellId, castCounter);
    }
}
