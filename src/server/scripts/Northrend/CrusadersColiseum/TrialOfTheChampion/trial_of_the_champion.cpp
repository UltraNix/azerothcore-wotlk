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
    NPC_SPECTATOR_ANIM_DRAENEI  = 34868
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

    EMOTE_CHEER             = 0
};

class npc_announcer_toc5 : public CreatureScript
{
public:
    npc_announcer_toc5() : CreatureScript("npc_announcer_toc5") {}

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        if( !pCreature->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP) )
            return true;

        InstanceScript* pInstance = pCreature->GetInstanceScript();
        if( !pInstance )
            return true;

        uint32 gossipTextId = 0;
        switch( pInstance->GetData(DATA_INSTANCE_PROGRESS) )
        {
            case INSTANCE_PROGRESS_INITIAL:
                gossipTextId = 14688;
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT1a, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1338);
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT1b, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1341);
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
            list.clear();
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
        }

        void UpdateAI(uint32 diff) 
        {
            _events.Update(diff);

            while (uint32 eventId = _events.ExecuteEvent())
            {
                switch (eventId)
                {
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
                                                Trinity::Containers::RandomResizeList(spectators, urand(6, 10));
                                            }
                                            else
                                            {
                                                me->GetCreatureListWithEntryInGrid(spectators, SpectatorData[plr->getRace()].spectatorForAnim, 250.0f);
                                                Trinity::Containers::RandomResizeList(spectators, urand(2, 5));
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
        EventMap _events;
    };
};

void AddSC_trial_of_the_champion()
{
    new npc_announcer_toc5();
}
