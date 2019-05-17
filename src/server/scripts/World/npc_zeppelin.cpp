#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "TransportMgr.h"
#include "Transport.h"
#include "Log.h"

enum ZeppelinTransport
{
    //from transports and gameobject_template table
    ZEPPELIN_THE_THUNDERCALLER_ENTRY                = 164871,
    ZEPPELIN_THE_PURPLE_PRINCESS_ENTRY              = 176495,
    ZEPPELIN_THE_IRON_EAGLE_ENTRY                   = 175080
};

enum ZeppelinMaster
{
    //from npc_text table
    WELCOME_TEXT_ID                                 = 2644,

    ARRIVED_AT_GROMGOL_TEXT_ID                      = 11167,
    ARRIVED_AT_ORGRIMMAR_TEXT_ID                    = 11169,
    ARRIVED_AT_UNDERCITY_TEXT_ID                    = 11173,

    DEPARTED_FROM_GROMGOL_TEXT_ID                   = 11172,
    DEPARTED_FROM_ORGRIMMAR_TEXT_ID                 = 11174,
    DEPARTED_FROM_UNDERCITY_TEXT_ID                 = 11175
};

enum ZeppelinTheThunderCaller
{
    //from loaded keyframes of this transport
    OG_UC_ORGRIMMAR_STOP_KEYFRAME_INDEX             = 3, // first stop
    OG_UC_UNDERCITY_STOP_KEYFRAME_INDEX             = 15 // second stop
};

enum ZeppelinThePurplePrincess
{
    //from loaded keyframes of this transport
    UC_STV_STRANGLETHORN_VALE_STOP_KEYFRAME_INDEX   = 2, // first stop
    UC_STV_UNDERCITY_STOP_KEYFRAME_INDEX            = 16 // second stop
};

enum ZeppelinTheIronEagle
{
    //from loaded keyframes of this transport
    OG_STV_STRANGLETHORN_VALE_STOP_KEYFRAME_INDEX   = 2, // first stop
    OG_STV_ORGRIMMAR_STOP_KEYFRAME_INDEX            = 11 // second stop
};

const std::string GOSSIP_HELLO_ZEPPELIN_MASTER{ "Where is the zeppelin now?" };

class ZeppelinLocationHelper
{
public:
    ZeppelinLocationHelper(uint32 transportEntry, uint32 firstStop, uint32 secondStop) :
        m_transport(sTransportMgr->GetContinentTransport(transportEntry)),
        m_firstStop(m_transport->ToMotionTransport()->GetKeyFrames()[firstStop]),
        m_secondStop(m_transport->ToMotionTransport()->GetKeyFrames()[secondStop]) { }

    bool IsZeppelinArrivedAtFirstStop() { return IsZeppelinArrived(m_firstStop); }

    bool IsZeppelinArrivedAtSecondStop() { return IsZeppelinArrived(m_secondStop); }

    bool IsZeppelinDepartedFromFirstStop()
    {
        uint32 timer = GetTimer();
        return timer > m_firstStop.DepartureTime + 10 * IN_MILLISECONDS && timer < m_secondStop.ArriveTime;
    }

    bool IsZeppelinDepartedFromSecondStop()
    {
        uint32 timer = GetTimer();
        return timer < m_firstStop.ArriveTime || timer > m_secondStop.DepartureTime + 10 * IN_MILLISECONDS;
    }

private:
    const uint32 GetTimer() const
    {
        return m_transport->GetPathProgress() % m_transport->ToMotionTransport()->GetPeriod();
    }

    const bool IsZeppelinArrived(KeyFrame const& zeppelinStopKeyFrame) const
    {
        uint32 timer = GetTimer();
        return timer >= zeppelinStopKeyFrame.ArriveTime &&
            timer <= zeppelinStopKeyFrame.DepartureTime + 10 * IN_MILLISECONDS;
    }

    Transport const* m_transport;
    KeyFrame const& m_firstStop;
    KeyFrame const& m_secondStop;
};

class npc_zapettaAI : public ScriptedAI
{
public:
    npc_zapettaAI(Creature* creature) : ScriptedAI(creature),
        m_zeppelinLocationHelper(ZEPPELIN_THE_THUNDERCALLER_ENTRY, OG_UC_ORGRIMMAR_STOP_KEYFRAME_INDEX, OG_UC_UNDERCITY_STOP_KEYFRAME_INDEX) { }

    void sGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (!m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ZEPPELIN_MASTER.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        SendGossipMenuFor(player, WELCOME_TEXT_ID, me->GetGUID());
    }

    void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 /*gossipListId*/) override
    {
        player->PlayerTalkClass->ClearMenus();

        if (m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            SendGossipMenuFor(player, ARRIVED_AT_ORGRIMMAR_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromFirstStop())
            SendGossipMenuFor(player, DEPARTED_FROM_ORGRIMMAR_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            SendGossipMenuFor(player, ARRIVED_AT_UNDERCITY_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromSecondStop())
            SendGossipMenuFor(player, DEPARTED_FROM_UNDERCITY_TEXT_ID, me->GetGUID());
    }

private:
    ZeppelinLocationHelper m_zeppelinLocationHelper;
};

struct npc_frezzaAI : public ScriptedAI
{
public:
    npc_frezzaAI(Creature* creature) : ScriptedAI(creature),
        m_zeppelinLocationHelper(
            ZEPPELIN_THE_THUNDERCALLER_ENTRY,
            OG_UC_ORGRIMMAR_STOP_KEYFRAME_INDEX,
            OG_UC_UNDERCITY_STOP_KEYFRAME_INDEX) { }

    void sGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (!m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ZEPPELIN_MASTER.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        SendGossipMenuFor(player, WELCOME_TEXT_ID, me->GetGUID());
    }

    void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 /*gossipListId*/) override
    {
        ClearGossipMenuFor(player);

        if (m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            SendGossipMenuFor(player, ARRIVED_AT_ORGRIMMAR_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromFirstStop())
            SendGossipMenuFor(player, DEPARTED_FROM_ORGRIMMAR_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            SendGossipMenuFor(player, ARRIVED_AT_UNDERCITY_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromSecondStop())
            SendGossipMenuFor(player, DEPARTED_FROM_UNDERCITY_TEXT_ID, me->GetGUID());
    }

private:
    ZeppelinLocationHelper m_zeppelinLocationHelper;
};

struct npc_squibby_overspeckAI : public ScriptedAI
{
public:
    npc_squibby_overspeckAI(Creature* creature) : ScriptedAI(creature),
        m_zeppelinLocationHelper(
            ZEPPELIN_THE_PURPLE_PRINCESS_ENTRY,
            UC_STV_STRANGLETHORN_VALE_STOP_KEYFRAME_INDEX,
            UC_STV_UNDERCITY_STOP_KEYFRAME_INDEX) { }

    void sGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (!m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            AddGossipItemFor(player,
                GOSSIP_ICON_CHAT,
                GOSSIP_HELLO_ZEPPELIN_MASTER.c_str(),
                GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        SendGossipMenuFor(player, WELCOME_TEXT_ID, me->GetGUID());
    }

    void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 /*gossipListId*/) override
    {
        ClearGossipMenuFor(player);

        if (m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            SendGossipMenuFor(player, ARRIVED_AT_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromFirstStop())
            SendGossipMenuFor(player, DEPARTED_FROM_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            SendGossipMenuFor(player, ARRIVED_AT_UNDERCITY_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromSecondStop())
            SendGossipMenuFor(player, DEPARTED_FROM_UNDERCITY_TEXT_ID, me->GetGUID());
    }

private:
    ZeppelinLocationHelper m_zeppelinLocationHelper;
};

struct npc_hin_denburgAI : public ScriptedAI
{
public:
    npc_hin_denburgAI(Creature* creature) : ScriptedAI(creature),
        m_zeppelinLocationHelper(
            ZEPPELIN_THE_PURPLE_PRINCESS_ENTRY,
            UC_STV_STRANGLETHORN_VALE_STOP_KEYFRAME_INDEX, // first stop
            UC_STV_UNDERCITY_STOP_KEYFRAME_INDEX) { }      // second stop

    void sGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (!m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ZEPPELIN_MASTER.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        SendGossipMenuFor(player, WELCOME_TEXT_ID, me->GetGUID());
    }

    void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 /*gossipListId*/) override
    {
        ClearGossipMenuFor(player);

        if (m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            SendGossipMenuFor(player, ARRIVED_AT_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromFirstStop())
            SendGossipMenuFor(player, DEPARTED_FROM_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            SendGossipMenuFor(player, ARRIVED_AT_UNDERCITY_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromSecondStop())
            SendGossipMenuFor(player, DEPARTED_FROM_UNDERCITY_TEXT_ID, me->GetGUID());
    }

private:
    ZeppelinLocationHelper m_zeppelinLocationHelper;
};

struct npc_nezrazAI : public ScriptedAI
{
public:
    npc_nezrazAI(Creature* creature) : ScriptedAI(creature),
        m_zeppelinLocationHelper(
            ZEPPELIN_THE_IRON_EAGLE_ENTRY,
            OG_STV_STRANGLETHORN_VALE_STOP_KEYFRAME_INDEX, // first stop
            OG_STV_ORGRIMMAR_STOP_KEYFRAME_INDEX) { }      // second stop

    void sGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (!m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ZEPPELIN_MASTER.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        SendGossipMenuFor(player, WELCOME_TEXT_ID, me->GetGUID());
    }

    void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 /*gossipListId*/) override
    {
        ClearGossipMenuFor(player);

        if (m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            SendGossipMenuFor(player, ARRIVED_AT_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromFirstStop())
            SendGossipMenuFor(player, DEPARTED_FROM_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            SendGossipMenuFor(player, ARRIVED_AT_ORGRIMMAR_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromSecondStop())
            SendGossipMenuFor(player, DEPARTED_FROM_ORGRIMMAR_TEXT_ID, me->GetGUID());
    }

private:
    ZeppelinLocationHelper m_zeppelinLocationHelper;
};

struct npc_snurk_bucksquickAI : public ScriptedAI
{
public:
    npc_snurk_bucksquickAI(Creature* creature) : ScriptedAI(creature),
        m_zeppelinLocationHelper(
            ZEPPELIN_THE_IRON_EAGLE_ENTRY,
            OG_STV_STRANGLETHORN_VALE_STOP_KEYFRAME_INDEX, // first stop
            OG_STV_ORGRIMMAR_STOP_KEYFRAME_INDEX) { }      // second stop

    void sGossipHello(Player* player) override
    {
        ClearGossipMenuFor(player);

        if (!m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, GOSSIP_HELLO_ZEPPELIN_MASTER.c_str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

        SendGossipMenuFor(player, WELCOME_TEXT_ID, me->GetGUID());
    }

    void sGossipSelect(Player* player, uint32 /*menuId*/, uint32 /*gossipListId*/) override
    {
        ClearGossipMenuFor(player);

        if (m_zeppelinLocationHelper.IsZeppelinArrivedAtFirstStop())
            SendGossipMenuFor(player, ARRIVED_AT_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromFirstStop())
            SendGossipMenuFor(player, DEPARTED_FROM_GROMGOL_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinArrivedAtSecondStop())
            SendGossipMenuFor(player, ARRIVED_AT_ORGRIMMAR_TEXT_ID, me->GetGUID());

        else if (m_zeppelinLocationHelper.IsZeppelinDepartedFromSecondStop())
            SendGossipMenuFor(player, DEPARTED_FROM_ORGRIMMAR_TEXT_ID, me->GetGUID());
    }

private:
    ZeppelinLocationHelper m_zeppelinLocationHelper;
};

void AddSC_npc_zeppelin_scripts()
{
    new CreatureAILoader<npc_zapettaAI>("npc_zapetta");
    new CreatureAILoader<npc_frezzaAI>("npc_frezza");
    new CreatureAILoader<npc_squibby_overspeckAI>("npc_squibby_overspeck");
    new CreatureAILoader<npc_hin_denburgAI>("npc_hin_denburg");
    new CreatureAILoader<npc_nezrazAI>("npc_nezraz");
    new CreatureAILoader<npc_snurk_bucksquickAI>("npc_snurk_bucksquick");
};
