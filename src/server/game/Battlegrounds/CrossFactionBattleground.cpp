#include "Battleground.h"
#include "BattlegroundMgr.h"
#include "Player.h"
#include "Chat.h"
#include "BattlegroundQueue.h"
#include "Unit.h"
#include "CrossFactionBattleground.h"
#include <vector>
#include <utility>
#include "ReputationMgr.h"
#include <array>

/* ## Crossfaction Battlegrounds ##
##### Based on LilleCarl work #####
##################################*/

uint8 Unit::getRace( bool allowOverride ) const
{
    auto race = GetByteValue( UNIT_FIELD_BYTES_0, 0 );
    if ( IsPlayer() )
    {
        Player const* pPlayer = ToPlayer();
        if ( allowOverride && pPlayer->GetBattlegroundId() != 0 )
            return pPlayer->GetBgData()->bgRace;

        return allowOverride ? race : pPlayer->GetInitialRace();
    }

    return race;
}

uint32 Player::ConvertFactionForReputationReward( uint32 faction_id ) const
{
    if ( IsPlayingNative() )
        return faction_id;

    if ( m_team == TEAM_ALLIANCE )
    {
        switch ( faction_id )
        {
            //! weird case used in BattlegroundAV:202
            case TEAM_HORDE: return TEAM_ALLIANCE;

            //! Frostwolf -> Stormpike
            case 729: return 730;
            //! Warsong Outriders -> Silverwing Sentinels
            case 889: return 890;
            //! The Defilers -> The League of Arathor
            case 510: return 509;
        }
    }
    else
    {
        switch ( faction_id )
        {
            //! weird case used in BattlegroundAV:202
            case TEAM_ALLIANCE: return TEAM_HORDE;

            //! Stormpike -> Frostwolf
            case 730: return 729;
            //! Silverwing Sentinels -> Warsong Outriders
            case 890: return 889;
            //! The League of Arathor -> The Defilers
            case 509: return 510;
        }
    }

    return faction_id;
}

Language Player::ConvertLanguage( Language language ) const
{
    if ( IsPlayingNative() )
        return language;

    switch ( language )
    {
        case LANG_UNIVERSAL:
            return LANG_UNIVERSAL;
        case LANG_COMMON:
            return GetTeam() == TEAM_ALLIANCE ? LANG_UNIVERSAL : LANG_UNK_CROSSFACTION;
        case LANG_ORCISH:
            return GetTeam() == TEAM_HORDE ? LANG_UNIVERSAL : LANG_UNK_CROSSFACTION;
    }

    return LANG_UNK_CROSSFACTION;
}

bool Player::SendBattleGroundChat(uint32 msgtype, std::string const& message)
{
    // Select distance to broadcast to
    float distance = msgtype == CHAT_MSG_SAY ? sWorld->getFloatConfig(CONFIG_LISTEN_RANGE_SAY) : sWorld->getFloatConfig(CONFIG_LISTEN_RANGE_YELL);

    if (Battleground* pBattleGround = GetBattleground())
    {
        if (pBattleGround->isArena()) // only fake chat in BG's. CBFG should not interfere with arenas
            return false;

        for (Battleground::BattlegroundPlayerMap::const_iterator itr = pBattleGround->GetPlayers().begin(); itr != pBattleGround->GetPlayers().end(); ++itr)
        {
            if (Player* pPlayer = ObjectAccessor::FindPlayer(itr->first))
            {
                if (GetDistance2d(pPlayer->GetPositionX(), pPlayer->GetPositionY()) <= distance)
                {
                    WorldPacket data(SMSG_MESSAGECHAT, 200);

                    if (GetTeam() == pPlayer->GetTeam())
                        BuildPlayerChat(&data, msgtype, message, LANG_UNIVERSAL);
                    else if (msgtype != CHAT_MSG_EMOTE)
                        BuildPlayerChat(&data, msgtype, message, LANG_UNK_CROSSFACTION);

                    pPlayer->GetSession()->SendPacket(&data);
                }
            }
        }
        return true;
    }
    else
        return false;
}

void Player::MorphFit(bool value)
{
    if (!IsPlayingNative() && value)
    {
        if (GetTeam(CrossFactionTeam::Discard) == TEAM_HORDE)
        {
            m_bgData.bgRace = RACE_HUMAN;

            if (getGender() == GENDER_MALE)
            {
                SetDisplayId(19723);
                SetNativeDisplayId(19723);
            }
            else
            {
                SetDisplayId(19724);
                SetNativeDisplayId(19724);
            }
        }
        else
        {
            m_bgData.bgRace = RACE_BLOODELF;

            if (getGender() == GENDER_MALE)
            {
                SetDisplayId(20578);
                SetNativeDisplayId(20578);
            }
            else
            {
                SetDisplayId(20579);
                SetNativeDisplayId(20579);
            }
        }
    }
    else
    {
        InitDisplayIds();

        m_bgData.bgRace = value ? getRace( false ) : 0u;
    }

    RestoreDisplayId();

    //SetByteValue( UNIT_FIELD_BYTES_0, 0, getRace() );
    SetByteValue( PLAYER_BYTES_3, 3, uint8( GetTeam() == TEAM_ALLIANCE ? 1 : 0 ) );
}

void Player::FitPlayerInTeam(bool action, Battleground* pBattleGround)
{
    if (!pBattleGround)
        pBattleGround = GetBattleground();

    if ((!pBattleGround || pBattleGround->isArena()) && action)
        return;

    //! set custom race, displayId, nativeDisplayId
    MorphFit( action );

    //! override faction
    if ( !IsPlayingNative() && action )
    {
        setFactionForRace( getRace() );
    }
    else
    {
        setFactionForRace( getRace( false ) );
    }

    if ( pBattleGround )
    {
        static std::vector< std::pair< uint32, uint32 > > s_factions =
        {   //A H
            { 0, 0 },// BATTLEGROUND_TYPE_NONE = 0, // None
            { 730, 729 },// BATTLEGROUND_AV = 1, // Alterac Valley
            { 890, 889 },// BATTLEGROUND_WS = 2, // Warsong Gulch
            { 509, 510 },// BATTLEGROUND_AB = 3, // Arathi Basin
            { 0, 0 },// BATTLEGROUND_NA = 4, // Nagrand Arena
            { 0, 0 },// BATTLEGROUND_BE = 5, // Blade's Edge Arena
            { 0, 0 },// BATTLEGROUND_AA = 6, // All Arenas
            { 0, 0 },// BATTLEGROUND_EY = 7, // Eye of the Storm
            { 0, 0 },// BATTLEGROUND_RL = 8, // Ruins of Lordaernon
            { 0, 0 },// BATTLEGROUND_SA = 9, // Strand of the Ancients
            { 0, 0 },// BATTLEGROUND_DS = 10, // Dalaran Sewers
            { 0, 0 },// BATTLEGROUND_RV = 11, // Ring of Valor
            { 0, 0 },// BATTLEGROUND_IC = 30, // Isle of Conquest
            { 0, 0 },// BATTLEGROUND_RB = 32 // Random Battleground
        };

        auto & data = s_factions[ pBattleGround->GetBgTypeID() ];
        if ( data.first && data.second )
        {
            auto rank1 = GetReputationMgr().GetRank( data.first );
            auto rank2 = GetReputationMgr().GetRank( data.second );

            //! aply only when playing for other team, otherwise forget forced reaction
            bool apply = action && !IsPlayingNative();

            GetReputationMgr().ApplyForceReaction( data.first, rank2, apply );
            GetReputationMgr().ApplyForceReaction( data.second, rank1, apply );
            GetReputationMgr().SendForceReactions();
        }

        if ( action )
        {
            SendChatMessage( "%sYou are playing for the %s%s in this %s", MSG_COLOR_WHITE, GetTeam() == TEAM_ALLIANCE ? MSG_COLOR_DARKBLUE"alliance" : MSG_COLOR_RED"horde", MSG_COLOR_WHITE, pBattleGround->GetName() );
        }
    }

    //! restore GM faction
    if ( IsGameMaster() )
    {
        SetGameMaster( true );
    }

    if ( !action )
    {
        m_crossfactionState = CrossFactionPlayerState::UpdatePlayerData;
    }

    sWorld->UpdateGlobalPlayerData( GetGUID(), PLAYER_UPDATE_DATA_RACE, "", 0, 0, getRace() );
}

void Player::SetCrossfactionBgAllowed( bool enabled )
{
    if ( enabled )
    {
        m_ExtraFlags &= ~PLAYER_EXTRA_DISABLE_CFBG;
    }
    else
    {
        m_ExtraFlags |= PLAYER_EXTRA_DISABLE_CFBG;
    }
}

void InvalidatePlayerGUID( Player* source, uint64 guid )
{
    WorldPacket packet( SMSG_INVALIDATE_PLAYER, 8 );
    packet << guid;

    source->GetSession()->SendPacket( &packet );
};

void Player::RequestCleanDataForDirtyPlayers()
{
    for ( auto guid : m_dirtyPlayers )
    {
        InvalidatePlayerGUID( this, guid );
        GetSession()->SendNameQueryOpcode( guid, true );
    }

    InvalidatePlayerGUID( this, GetGUID() );
    GetSession()->SendNameQueryOpcode( GetGUID(), true );

    m_dirtyPlayers.clear();
}

void Player::RequestDirtyDataForPlayer( uint64 guid )
{
    InvalidatePlayerGUID( this, guid );

    if ( m_dirtyPlayers.insert( guid ).second )
    {
        GetSession()->SendNameQueryOpcode( guid, false );
    }
}

void Player::RequestDirtyDataForBgPlayers( const Battleground::BattlegroundPlayerMap & players )
{
    for ( auto && it : players )
    {
        uint64 guid = it.first;

        RequestDirtyDataForPlayer( guid );

        if ( Player* player = ObjectAccessor::FindPlayer( guid ) )
        {
            player->RequestDirtyDataForPlayer( GetGUID() );
        }
    }

    InvalidatePlayerGUID( this, GetGUID() );
    GetSession()->SendNameQueryOpcode( GetGUID(), false );
}

// This function will invite players in the least populated faction, which makes battleground queues much faster.
// This function will return true if cross faction battlegrounds are enabled, otherwise return false,
// which is useful in FillPlayersToBG. Because then we can interrupt the regular invitation if cross faction bg's are enabled.
bool BattlegroundQueue::FillXPlayersToBG(BattlegroundBracketId bracket_id, Battleground* bg, bool start, PvPDifficultyEntry const* bracketEntry )
{
    uint8 queuedPeople = 0;
    for (GroupQueueInfo* group : m_QueuedGroups[bracket_id][BG_QUEUE_MIXED])
    {
        if ( !group->IsInvitedToBGInstanceGUID )
        {
            queuedPeople += group->Players.size();
        }
    }

    if ( IsCrossfactionEnabledForBracket( bracketEntry ? bracketEntry : GetBattlegroundBracketById( bg->GetMapId(), bracket_id ) ) && (sBattlegroundMgr->isTesting() || queuedPeople >= bg->GetMinPlayersPerTeam() * 2 || !start))
    {
        int32 aliFree = start ? bg->GetMaxPlayersPerTeam() : bg->GetFreeSlotsForTeam(TEAM_ALLIANCE);
        int32 hordeFree = start ? bg->GetMaxPlayersPerTeam() : bg->GetFreeSlotsForTeam(TEAM_HORDE);
        // Empty selection pools. They will be refilled from queued groups.
        m_SelectionPools[TEAM_ALLIANCE].Init();
        m_SelectionPools[TEAM_HORDE].Init();
        int32 valiFree = aliFree;
        int32 vhordeFree = hordeFree;
        int32 diff = 0;

        // Add teams to their own factions as far as possible.
        if (start)
        {
            QueuedGroupMap m_PreGroupMap_a, m_PreGroupMap_h;
            int32 m_SmallestOfTeams = 0;
            int32 queuedAlliance = 0;
            int32 queuedHorde = 0;

            for ( GroupQueueInfo* group : m_QueuedGroups[ bracket_id ][ BG_QUEUE_MIXED ] )
            {
                if ( group->IsInvitedToBGInstanceGUID)
                    continue;

                bool alliance = group->oTeam == TEAM_ALLIANCE;

                if (alliance)
                {
                    m_PreGroupMap_a.insert(std::make_pair( group->Players.size(), group ));
                    queuedAlliance += group->Players.size();
                }
                else
                {
                    m_PreGroupMap_h.insert(std::make_pair( group->Players.size(), group ));
                    queuedHorde += group->Players.size();
                }
            }

            m_SmallestOfTeams = std::min(std::min(aliFree, queuedAlliance), std::min(hordeFree, queuedHorde));

            valiFree -= PreAddPlayers(m_PreGroupMap_a, m_SmallestOfTeams, aliFree);
            vhordeFree -= PreAddPlayers(m_PreGroupMap_h, m_SmallestOfTeams, hordeFree);
        }

        QueuedGroupMap m_QueuedGroupMap;
        for ( GroupQueueInfo* group : m_QueuedGroups[ bracket_id ][ BG_QUEUE_MIXED ] )
        {
            m_QueuedGroupMap.insert( std::make_pair( group->Players.size(), group ) );
        }

        for (QueuedGroupMap::reverse_iterator itr = m_QueuedGroupMap.rbegin(); itr != m_QueuedGroupMap.rend(); ++itr)
        {
            GroupsQueueType const& allypool = m_SelectionPools[TEAM_ALLIANCE].SelectedGroups;
            GroupsQueueType const& hordepool = m_SelectionPools[TEAM_HORDE].SelectedGroups;

            GroupQueueInfo* ginfo = itr->second;

            // If player already was invited via pre adding (add to own team first) or he was already invited to a bg, skip.

            if (ginfo->IsInvitedToBGInstanceGUID ||
                std::find(allypool.begin(), allypool.end(), ginfo) != allypool.end() ||
                std::find(hordepool.begin(), hordepool.end(), ginfo) != hordepool.end())/* ||
                (m_SelectionPools[TEAM_ALLIANCE].GetPlayerCount() >= bg->GetMinPlayersPerTeam() &&
                    m_SelectionPools[TEAM_HORDE].GetPlayerCount() >= bg->GetMinPlayersPerTeam()))*/
                continue;

            diff = abs(valiFree - vhordeFree);
            bool moreAli = valiFree < vhordeFree;

            if (diff > 0)
                ginfo->teamId = moreAli ? TEAM_HORDE : TEAM_ALLIANCE;

            if ( ginfo->teamId != ginfo->oTeam && !ginfo->IsCrossfactionAllowed )
                continue;

            bool alliance = ginfo->teamId == TEAM_ALLIANCE;

            if (m_SelectionPools[alliance ? TEAM_ALLIANCE : TEAM_HORDE].AddGroup(ginfo, alliance ? aliFree : hordeFree))
                alliance ? valiFree -= ginfo->Players.size() : vhordeFree -= ginfo->Players.size();
        }

        return true;
    }
    return false;
}

bool BattlegroundQueue::FillXPlayersToBGWithSpecific( Battleground* bg, const int32 aliFree, const int32 hordeFree, BattlegroundBracketId thisBracketId, BattlegroundQueue* specificQueue, BattlegroundBracketId specificBracketId )
{
    // clear selection pools
    m_SelectionPools[ TEAM_ALLIANCE ].Init();
    m_SelectionPools[ TEAM_HORDE ].Init();

    uint8 queuedPeople = 0;

    for ( auto bracketId : { thisBracketId, specificBracketId } )
    {
        for ( GroupQueueInfo* group : m_QueuedGroups[ bracketId ][ BG_QUEUE_MIXED ] )
        {
            if ( !group->IsInvitedToBGInstanceGUID )
            {
                queuedPeople += group->Players.size();
            }
        }
    }

    if ( IsCrossfactionEnabledForBracket( GetBattlegroundBracketById( bg->GetMapId(), specificBracketId ) ) && ( sBattlegroundMgr->isTesting() || queuedPeople >= bg->GetMinPlayersPerTeam() * 2 ) )
    {
        int32 valiFree = aliFree;
        int32 vhordeFree = hordeFree;
        int32 diff = 0;

        // Add teams to their own factions as far as possible.
        QueuedGroupMap m_PreGroupMap_a, m_PreGroupMap_h;
        int32 m_SmallestOfTeams = 0;
        int32 queuedAlliance = 0;
        int32 queuedHorde = 0;

        for ( auto bracketId : { thisBracketId, specificBracketId } )
        {
            for ( GroupQueueInfo* group : m_QueuedGroups[ bracketId ][ BG_QUEUE_MIXED ] )
            {
                if ( group->IsInvitedToBGInstanceGUID )
                    continue;

                bool alliance = group->oTeam == TEAM_ALLIANCE;

                if ( alliance )
                {
                    m_PreGroupMap_a.insert( std::make_pair( group->Players.size(), group ) );
                    queuedAlliance += group->Players.size();
                }
                else
                {
                    m_PreGroupMap_h.insert( std::make_pair( group->Players.size(), group ) );
                    queuedHorde += group->Players.size();
                }
            }
        }

        m_SmallestOfTeams = std::min( std::min( aliFree, queuedAlliance ), std::min( hordeFree, queuedHorde ) );

        valiFree -= PreAddPlayers( m_PreGroupMap_a, m_SmallestOfTeams, aliFree );
        vhordeFree -= PreAddPlayers( m_PreGroupMap_h, m_SmallestOfTeams, hordeFree );

        QueuedGroupMap m_QueuedGroupMap;
        for ( auto bracketId : { thisBracketId, specificBracketId } )
        {
            for ( GroupQueueInfo* group : m_QueuedGroups[ bracketId ][ BG_QUEUE_MIXED ] )
            {
                m_QueuedGroupMap.insert( std::make_pair( group->Players.size(), group ) );
            }
        }

        for ( QueuedGroupMap::reverse_iterator itr = m_QueuedGroupMap.rbegin(); itr != m_QueuedGroupMap.rend(); ++itr )
        {
            GroupsQueueType const& allypool = m_SelectionPools[ TEAM_ALLIANCE ].SelectedGroups;
            GroupsQueueType const& hordepool = m_SelectionPools[ TEAM_HORDE ].SelectedGroups;

            GroupQueueInfo* ginfo = itr->second;

            // If player already was invited via pre adding (add to own team first) or he was already invited to a bg, skip.

            if ( ginfo->IsInvitedToBGInstanceGUID ||
                 std::find( allypool.begin(), allypool.end(), ginfo ) != allypool.end() ||
                 std::find( hordepool.begin(), hordepool.end(), ginfo ) != hordepool.end() )/* ||
                                                                                            (m_SelectionPools[TEAM_ALLIANCE].GetPlayerCount() >= bg->GetMinPlayersPerTeam() &&
                                                                                            m_SelectionPools[TEAM_HORDE].GetPlayerCount() >= bg->GetMinPlayersPerTeam()))*/
                continue;

            diff = abs( valiFree - vhordeFree );
            bool moreAli = valiFree < vhordeFree;

            if ( diff > 0 )
                ginfo->teamId = moreAli ? TEAM_HORDE : TEAM_ALLIANCE;

            if ( ginfo->teamId != ginfo->oTeam && !ginfo->IsCrossfactionAllowed )
                continue;

            bool alliance = ginfo->teamId == TEAM_ALLIANCE;

            if ( m_SelectionPools[ alliance ? TEAM_ALLIANCE : TEAM_HORDE ].AddGroup( ginfo, alliance ? aliFree : hordeFree ) )
                alliance ? valiFree -= ginfo->Players.size() : vhordeFree -= ginfo->Players.size();
        }

        return true;
    }
    return false;
}

int32 BattlegroundQueue::PreAddPlayers(QueuedGroupMap m_PreGroupMap, int32 MaxAdd, uint32 MaxInTeam)
{
    int32 LeftToAdd = MaxAdd;
    uint32 Added = 0;

    for (QueuedGroupMap::reverse_iterator itr = m_PreGroupMap.rbegin(); itr != m_PreGroupMap.rend(); ++itr)
    {
        int32 PlayerSize = itr->first;
        bool alliance = itr->second->oTeam == TEAM_ALLIANCE;

        if (PlayerSize <= LeftToAdd && m_SelectionPools[alliance ? TEAM_ALLIANCE : TEAM_HORDE].AddGroup(itr->second, MaxInTeam))
            LeftToAdd -= PlayerSize, Added -= PlayerSize;
    }

    return LeftToAdd;
}

void Player::SendChatMessage(const char *format, ...)
{
    if (!IsInWorld())
        return;

    if (format)
    {
        va_list ap;
        char str[2048];
        va_start(ap, format);
        vsnprintf(str, 2048, format, ap);
        va_end(ap);

        ChatHandler(GetSession()).SendSysMessage(str);
    }
}
