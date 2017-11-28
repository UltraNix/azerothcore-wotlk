/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "trial_of_the_champion.h"
#include "Player.h"

#define GOSSIP_START_EVENT1a "I am ready."
#define GOSSIP_START_EVENT1b "I am ready. However I'd like to skip the pageantry."
#define GOSSIP_START_EVENT2     "I'm ready for the next challenge."
#define GOSSIP_START_EVENT3  "I'm ready."

enum Spectators
{
    NPC_SPECTATOR_HORDE         = 34883,
    NPC_SPECTATOR_ALLIANCE      = 34887,
    NPC_SPECTATOR_HUMAN         = 34900,
    NPC_SPECTATOR_ORC           = 34901,
    NPC_SPECTATOR_TROLL         = 34902,
    NPC_SPECTATOR_TAUREN        = 34903,
    NPC_SPECTATOR_BELF          = 34904,
    NPC_SPECTATOR_UNDEAD        = 34905,
    NPC_SPECTATOR_DWARF         = 34906,
    NPC_SPECTATOR_DRAENEI       = 34908,
    NPC_SPECTATOR_NELF          = 34909,
    NPC_SPECTATOR_GNOME         = 34910,

    NPC_SPECTATOR_ANIM_HUMAN    = 34870,
    NPC_SPECTATOR_ANIM_ORC      = 34859,
    NPC_SPECTATOR_ANIM_DWARF    = 34856,
    NPC_SPECTATOR_ANIM_NELF     = 34871,
    NPC_SPECTATOR_ANIM_UNDEAD   = 34860,
    NPC_SPECTATOR_ANIM_TAUREN   = 34858,
    NPC_SPECTATOR_ANIM_GNOME    = 34869,
    NPC_SPECTATOR_ANIM_TROLL    = 34857,
    NPC_SPECTATOR_ANIM_BELF     = 34861,
    NPC_SPECTATOR_ANIM_DRAENEI  = 34868,

    NPC_NEUTRAL_DWARF           = 34974,
    NPC_NEUTRAL_DRAENEI         = 34975,
    NPC_NEUTRAL_HUMAN           = 34970,
    NPC_NEUTRAL_ORC             = 34977,
    NPC_NEUTRAL_BELF            = 34966,
    NPC_NEUTRAL_TAUREN          = 34979
};

struct SpectatorsInfo
{
    uint32 spectatorForEmote, spectatorForAnim;
};

SpectatorsInfo const SpectatorData[12] =
{
    { 0, 0 },
    { NPC_SPECTATOR_HUMAN, NPC_SPECTATOR_ANIM_HUMAN },
    { NPC_SPECTATOR_ORC, NPC_SPECTATOR_ANIM_ORC },
    { NPC_SPECTATOR_DWARF, NPC_SPECTATOR_ANIM_DWARF},
    { NPC_SPECTATOR_NELF, NPC_SPECTATOR_ANIM_NELF },
    { NPC_SPECTATOR_UNDEAD,  NPC_SPECTATOR_ANIM_UNDEAD },
    { NPC_SPECTATOR_TAUREN, NPC_SPECTATOR_ANIM_TAUREN },
    { NPC_SPECTATOR_GNOME, NPC_SPECTATOR_ANIM_GNOME },
    { NPC_SPECTATOR_TROLL, NPC_SPECTATOR_ANIM_TROLL },
    { 0, 0},
    { NPC_SPECTATOR_BELF, NPC_SPECTATOR_ANIM_BELF },
    { NPC_SPECTATOR_DRAENEI, NPC_SPECTATOR_ANIM_DRAENEI }
};

enum Announcer
{
    EVENT_RANDOM_EMOTE      = 1,
    EVENT_RANDOM_ANIMS,
    EVENT_RANDOM_ANIMS_TRIGGER,

    EMOTE_CHEER             = 0
};

class npc_announcer_toc5 : public CreatureScript
{
public:
    npc_announcer_toc5() : CreatureScript("npc_announcer_toc5") {}

    bool HasAllSeenEvent(Player* player)
    {
        if (!player)
            return false;

        if (player->IsGameMaster())
            return true;

        bool seen = true;
        Map::PlayerList const& players = player->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (Player const *plr = itr->GetSource())
            {
                if (!plr->GetMap()->IsHeroic())
                {
                    if (!plr->HasAchieved(3778) /* Normal ToC (horde) */ && !plr->HasAchieved(4296) /* Normal ToC (alliance) */)
                        seen = false;
                }
                else
                {
                    if (!plr->HasAchieved(4298) /* Heroic ToC (alliance) */ && !plr->HasAchieved(4297) /* Heroic ToC (horde) */)
                        seen = false;
                }
            }
        }
        return seen;
    }

    bool AllMountedCheck(Creature* creature, InstanceScript* instance)
    {
        bool check = false;
        if (instance->GetData(DATA_INSTANCE_PROGRESS) == INSTANCE_PROGRESS_INITIAL)
        {
            uint32 count = 0;
            Map::PlayerList const &players = creature->GetMap()->GetPlayers();

            if (!players.isEmpty())
            {
                for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                {
                    if (Player* player = itr->GetSource())
                    {
                        if (player->IsGameMaster())
		                {
		                    ++count;
		                    continue;
		                }
									
                        if (Unit* veh = player->GetVehicleBase())
                        {
                            if (veh->GetEntry() == VEHICLE_ARGENT_WARHORSE || veh->GetEntry() == VEHICLE_ARGENT_BATTLEWORG)
                                ++count;
                        }
                    }
                }

                if (count == players.getSize())
                    check = true;
            }
        }

        return check;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if( !pCreature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) )
            return true;

        InstanceScript* pInstance = pCreature->GetInstanceScript();
        if( !pInstance )
            return true;

        bool check = AllMountedCheck(pCreature, pInstance);

        uint32 gossipTextId = 0;
        switch( pInstance->GetData(DATA_INSTANCE_PROGRESS) )
        {
            case INSTANCE_PROGRESS_INITIAL:
                if (check)
                {
                    gossipTextId = 14688;
                    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT1a, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1338);
                    if (HasAllSeenEvent(pPlayer))
                        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT1b, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1341);
                }
                else
                    gossipTextId = (pInstance->GetData(DATA_TEAMID_IN_INSTANCE) == TEAM_ALLIANCE ? 14757 : 15043);
                break;
            case INSTANCE_PROGRESS_CHAMPIONS_DEAD:
                gossipTextId = 14737;
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1339);
                break;
            case INSTANCE_PROGRESS_ARGENT_CHALLENGE_DIED:
                gossipTextId = 14738;
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1340);
                break;
            default:
                return true;
        }

        pPlayer->SEND_GOSSIP_MENU(gossipTextId, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        if( !pCreature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) )
            return true;

        InstanceScript* pInstance = pCreature->GetInstanceScript();
        if( !pInstance )
            return true;

        if( uiAction == GOSSIP_ACTION_INFO_DEF+1338 || uiAction == GOSSIP_ACTION_INFO_DEF+1341 || uiAction == GOSSIP_ACTION_INFO_DEF+1339 || uiAction == GOSSIP_ACTION_INFO_DEF+1340 )
        {
            pInstance->SetData(DATA_ANNOUNCER_GOSSIP_SELECT, (uiAction == GOSSIP_ACTION_INFO_DEF+1341 ? 1 : 0));
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }

        pPlayer->CLOSE_GOSSIP_MENU();
        return true;
    }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_announcer_toc5AI(pCreature);
    }

    struct npc_announcer_toc5AI : public CreatureAI
    {
        npc_announcer_toc5AI(Creature *pCreature) : CreatureAI(pCreature) {}

        void Reset()
        {
            if(!_events.GetNextEventTime(EVENT_RANDOM_EMOTE))
                _events.ScheduleEvent(EVENT_RANDOM_EMOTE, 30000);

            if (!_events.GetNextEventTime(EVENT_RANDOM_ANIMS))
                _events.ScheduleEvent(EVENT_RANDOM_ANIMS, 5000);

            spectators.clear();
            GetSpectators(spectators, TEAM_ALLIANCE);
            GetSpectators(spectators, TEAM_HORDE);
            GetSpectators(spectators, TEAM_NEUTRAL);

            count = 0;
            InstanceScript* pInstance = me->GetInstanceScript();
            if( !pInstance )
                return;
            if( pInstance->GetData(DATA_TEAMID_IN_INSTANCE) == TEAM_ALLIANCE )
                me->UpdateEntry(NPC_ARELAS);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE); // removed during black knight scene
        }

        void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask)
        {
            if (damage >= me->GetHealth()) // for bk scene so strangulate doesn't kill him
                damage = me->GetHealth()-1;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != EFFECT_MOTION_TYPE)
                return;
            InstanceScript* pInstance = me->GetInstanceScript();
            if( !pInstance )
                return;
            if (pInstance->GetData(DATA_INSTANCE_PROGRESS) < INSTANCE_PROGRESS_ARGENT_CHALLENGE_DIED)
                return;

            Unit::Kill(me, me); // for bk scene, die after knockback
        }

        void GetSpectators(std::list<Creature*>& list, uint32 team)
        {
            if (team == TEAM_HORDE)
            {
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_BELF, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_UNDEAD, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_ORC, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_TAUREN, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_TROLL, 250.0f);
            }
            else if (team == TEAM_ALLIANCE)
            {
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_DWARF, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_DRAENEI, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_GNOME, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_HUMAN, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_SPECTATOR_ANIM_NELF, 250.0f);
            }
            else if (team == TEAM_NEUTRAL)
            {
                me->GetCreatureListWithEntryInGrid(list, NPC_NEUTRAL_DWARF, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_NEUTRAL_DRAENEI, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_NEUTRAL_HUMAN, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_NEUTRAL_ORC, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_NEUTRAL_BELF, 250.0f);
                me->GetCreatureListWithEntryInGrid(list, NPC_NEUTRAL_TAUREN, 250.0f);
            }
        }

        void UpdateAI(uint32 diff) 
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_RANDOM_ANIMS:
                    {
                        _events.ScheduleEvent(EVENT_RANDOM_ANIMS_TRIGGER, 0);
                        _events.Repeat(urand(9000, 10000));
                        break;
                    }
                    case EVENT_RANDOM_ANIMS_TRIGGER:
                        if (!spectators.empty())
                            for (auto itr : spectators)
                                if (roll_chance_i(70))
                                    itr->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);

                        if (++count <= 3)
                            _events.Repeat(urand(500, 1000));
                        else
                            count = 0;
                        break;
                    case EVENT_RANDOM_EMOTE:
                        if (!me->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) && !me->isMoving() && !me->HasAura(66804))
                        {
                            _events.Repeat(120000);
                            InstanceScript* instance = me->GetInstanceScript();

                            if (!instance)
                                return;

                            // Every 2 minutes a random player is being cheered by his/her race's spectators
                            // cheer should only occur during fights
                            Map::PlayerList const &pList = me->GetMap()->GetPlayers();
                            // Player list is always in the same order so we must randomize it
                            if (!pList.isEmpty())
                            {
                                uint32 rand = urand(0, pList.getSize() - 1);
                                for (Map::PlayerList::const_iterator itr = pList.begin(); itr != pList.end(); ++itr)
                                {
                                    if (rand == 0)
                                    {
                                        Player* plr = itr->GetSource();
                                        if (plr && !plr->IsGameMaster() && plr->IsAlive())
                                        {
                                            uint32 id = instance->GetData(DATA_TEAMID_IN_INSTANCE);

                                            // 50% chance for race cheering at you or faction cheering at you
                                            uint32 spectatorEntry = RAND(SpectatorData[plr->getRace()].spectatorForEmote, uint32(id == TEAM_ALLIANCE ? NPC_SPECTATOR_ALLIANCE : NPC_SPECTATOR_HORDE));

                                            if (Creature* spectator = me->FindNearestCreature(spectatorEntry, 250.0f))
                                                if (spectator->IsAIEnabled)
                                                    spectator->AI()->Talk(EMOTE_CHEER, plr);

                                            std::list<Creature*> spectators;
                                            if (spectatorEntry == NPC_SPECTATOR_HORDE || spectatorEntry == NPC_SPECTATOR_ALLIANCE)
                                            {
                                                GetSpectators(spectators, id);
                                                Trinity::Containers::RandomResize(spectators, urand(6, 10));
                                            }
                                            else
                                            {
                                                me->GetCreatureListWithEntryInGrid(spectators, SpectatorData[plr->getRace()].spectatorForAnim, 250.0f);
                                                Trinity::Containers::RandomResize(spectators, urand(2, 5));
                                            }

                                            if (!spectators.empty())
                                                for (auto itr : spectators)
                                                    itr->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);

                                            break;
                                        }
                                        else
                                            continue;
                                    }
                                    else
                                        --rand;
                                }
                            }
                        }
                        else
                            _events.Repeat(40000);
                        break;
                    default:
                        break;               
                }
            }
        }

    private:
        std::list<Creature*> spectators;
        uint32 count;
        EventMap _events;
    };
};

void AddSC_trial_of_the_champion()
{
    new npc_announcer_toc5();
}
