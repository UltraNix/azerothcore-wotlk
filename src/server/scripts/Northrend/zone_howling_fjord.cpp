/*
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

/* ScriptData
SDName: Sholazar_Basin
SD%Complete: 100
SDComment: Quest support: 11253, 11241.
SDCategory: howling_fjord
EndScriptData */

/* ContentData
npc_plaguehound_tracker
npc_apothecary_hanes
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "PassiveAI.h"
#include "Player.h"
#include "SpellInfo.h"

// Ours
class npc_attracted_reef_bull : public CreatureScript
{
public:
    npc_attracted_reef_bull() : CreatureScript("npc_attracted_reef_bull") { }

    struct npc_attracted_reef_bullAI : public NullCreatureAI
    {
        npc_attracted_reef_bullAI(Creature* creature) : NullCreatureAI(creature)
        {
            me->SetDisableGravity(true);
            if (me->IsSummon())
                if (Unit* owner = me->ToTempSummon()->GetSummoner())
                    me->GetMotionMaster()->MovePoint(0, *owner);
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (Creature* cow = me->FindNearestCreature(24797, 5.0f, true))
            {
                me->CastSpell(me, 44460, true);
                me->DespawnOrUnsummon(10000);
                cow->CastSpell(cow, 44460, true);
                cow->DespawnOrUnsummon(10000);
                if (me->IsSummon())
                    if (Unit* owner = me->ToTempSummon()->GetSummoner())
                        owner->CastSpell(owner, 44463, true);
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spellInfo)
        {
            if (caster && spellInfo->Id == 44454)
                me->GetMotionMaster()->MovePoint(0, *caster);
        }
    };

    CreatureAI *GetAI(Creature* creature) const
    {
        return new npc_attracted_reef_bullAI(creature);
    }
};

class npc_your_inner_turmoil : public CreatureScript
{
public:
    npc_your_inner_turmoil() : CreatureScript("npc_your_inner_turmoil") { }

    struct npc_your_inner_turmoilAI : public ScriptedAI
    {
        npc_your_inner_turmoilAI(Creature* creature) : ScriptedAI(creature) {}

        uint32 timer;
        short phase;

        void Reset()
        {
            timer = 0;
            phase = 0;
        }

        void UpdateAI(uint32 diff)
        {
            if (timer >= 6000 && phase < 4)
            {
                phase++;
                setphase(phase);
                timer = 0;
            }

            timer += diff;

            DoMeleeAttackIfReady();
        }

        void setphase(short phase)
        {
            Unit* summoner = me->ToTempSummon() ? me->ToTempSummon()->GetSummoner() : NULL;
            if (!summoner || summoner->GetTypeId() != TYPEID_PLAYER)
                return;

            switch (phase)
            {
                case 1:
                    me->MonsterWhisper("You think that you can get rid of me through meditation?", summoner->ToPlayer());
                    return;
                case 2:
                    me->MonsterWhisper("Fool! I will destroy you and finally become that which has been building inside of you all these years!", summoner->ToPlayer());
                    return;
                case 3:
                    me->MonsterWhisper("You cannot defeat me. I'm an inseparable part of you!", summoner->ToPlayer());
                    return;
                case 4:
                    me->MonsterWhisper("NOOOOOOOoooooooooo!", summoner->ToPlayer());
                    me->SetLevel(summoner->getLevel());
                    me->setFaction(14);
                    if (me->GetExactDist(summoner) < 50.0f)
                    {
                        me->UpdatePosition(summoner->GetPositionX(), summoner->GetPositionY(), summoner->GetPositionZ(), 0.0f, true);
                        summoner->CastSpell(me, 50218, true); // clone caster
                        AttackStart(summoner);
                    }
            }
        }
    };

    CreatureAI *GetAI(Creature* creature) const
    {
        return new npc_your_inner_turmoilAI(creature);
    }
};


// Theirs
/*######
## npc_apothecary_hanes
######*/
enum Entries
{
    NPC_APOTHECARY_HANES         = 23784,
    FACTION_ESCORTEE_A           = 774,
    FACTION_ESCORTEE_H           = 775,
    NPC_HANES_FIRE_TRIGGER       = 23968,
    QUEST_TRAIL_OF_FIRE          = 11241,
    SPELL_COSMETIC_LOW_POLY_FIRE = 56274,
    SPELL_HEALING_POTION         = 17534
};

class npc_apothecary_hanes : public CreatureScript
{
public:
    npc_apothecary_hanes() : CreatureScript("npc_apothecary_hanes") { }

    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest)
    {
        if (quest->GetQuestId() == QUEST_TRAIL_OF_FIRE)
        {
            creature->setFaction(player->GetTeamId() == TEAM_ALLIANCE ? FACTION_ESCORTEE_A : FACTION_ESCORTEE_H);
            CAST_AI(npc_escortAI, (creature->AI()))->Start(true, false, player->GetGUID());
        }
        return true;
    }

    struct npc_Apothecary_HanesAI : public npc_escortAI
    {
        npc_Apothecary_HanesAI(Creature* creature) : npc_escortAI(creature){ }
        uint32 PotTimer;

        void Reset()
        {
            SetDespawnAtFar(false);
            PotTimer = 10000; //10 sec cooldown on potion
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Player* player = GetPlayerForEscort())
                player->FailQuest(QUEST_TRAIL_OF_FIRE);
        }

        void UpdateEscortAI(uint32 diff)
        {
            if (HealthBelowPct(75))
            {
                if (PotTimer <= diff)
                {
                    DoCast(me, SPELL_HEALING_POTION, true);
                    PotTimer = 10000;
                } else PotTimer -= diff;
            }
            if (GetAttack() && UpdateVictim())
                DoMeleeAttackIfReady();
        }

        void WaypointReached(uint32 waypointId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 1:
                    me->SetReactState(REACT_AGGRESSIVE);
                    SetRun(true);
                    break;
                case 23:
                    player->GroupEventHappens(QUEST_TRAIL_OF_FIRE, me);
                    me->DespawnOrUnsummon();
                    break;
                case 5:
                    if (Unit* Trigger = me->FindNearestCreature(NPC_HANES_FIRE_TRIGGER, 10.0f))
                        Trigger->CastSpell(Trigger, SPELL_COSMETIC_LOW_POLY_FIRE, false);
                    SetRun(false);
                    break;
                case 6:
                    if (Unit* Trigger = me->FindNearestCreature(NPC_HANES_FIRE_TRIGGER, 10.0f))
                        Trigger->CastSpell(Trigger, SPELL_COSMETIC_LOW_POLY_FIRE, false);
                    SetRun(true);
                    break;
                case 8:
                    if (Unit* Trigger = me->FindNearestCreature(NPC_HANES_FIRE_TRIGGER, 10.0f))
                        Trigger->CastSpell(Trigger, SPELL_COSMETIC_LOW_POLY_FIRE, false);
                    SetRun(false);
                    break;
                case 9:
                    if (Unit* Trigger = me->FindNearestCreature(NPC_HANES_FIRE_TRIGGER, 10.0f))
                        Trigger->CastSpell(Trigger, SPELL_COSMETIC_LOW_POLY_FIRE, false);
                    break;
                case 10:
                    SetRun(true);
                    break;
                case 13:
                    SetRun(false);
                    break;
                case 14:
                    if (Unit* Trigger = me->FindNearestCreature(NPC_HANES_FIRE_TRIGGER, 10.0f))
                        Trigger->CastSpell(Trigger, SPELL_COSMETIC_LOW_POLY_FIRE, false);
                    SetRun(true);
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_Apothecary_HanesAI(creature);
    }
};

/*######
## npc_plaguehound_tracker
######*/

enum Plaguehound
{
    QUEST_SNIFF_OUT_ENEMY        = 11253
};

class npc_plaguehound_tracker : public CreatureScript
{
public:
    npc_plaguehound_tracker() : CreatureScript("npc_plaguehound_tracker") { }

    struct npc_plaguehound_trackerAI : public npc_escortAI
    {
        npc_plaguehound_trackerAI(Creature* creature) : npc_escortAI(creature) { }

        void Reset()
        {
            uint64 summonerGUID = 0;

            if (me->IsSummon())
                if (Unit* summoner = me->ToTempSummon()->GetSummoner())
                    if (summoner->GetTypeId() == TYPEID_PLAYER)
                        summonerGUID = summoner->GetGUID();

            if (!summonerGUID)
                return;

            me->SetWalk(true);
            Start(false, false, summonerGUID);
        }

        void WaypointReached(uint32 waypointId)
        {
            if (waypointId != 26)
                return;

            me->DespawnOrUnsummon();
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_plaguehound_trackerAI(creature);
    }
};

/*######
## npc_razael_and_lyana
######*/

#define GOSSIP_RAZAEL_REPORT "High Executor Anselm wants a report on the situation."
#define GOSSIP_LYANA_REPORT "High Executor Anselm requests your report."

enum Razael
{
    QUEST_REPORTS_FROM_THE_FIELD = 11221,
    NPC_RAZAEL = 23998,
    NPC_LYANA = 23778,
    GOSSIP_TEXTID_RAZAEL1 = 11562,
    GOSSIP_TEXTID_RAZAEL2 = 11564,
    GOSSIP_TEXTID_LYANA1 = 11586,
    GOSSIP_TEXTID_LYANA2 = 11588
};

class npc_razael_and_lyana : public CreatureScript
{
public:
    npc_razael_and_lyana() : CreatureScript("npc_razael_and_lyana") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        if (creature->IsQuestGiver())
            player->PrepareQuestMenu(creature->GetGUID());

        if (player->GetQuestStatus(QUEST_REPORTS_FROM_THE_FIELD) == QUEST_STATUS_INCOMPLETE)
            switch (creature->GetEntry())
            {
                case NPC_RAZAEL:
                    if (!player->GetReqKillOrCastCurrentCount(QUEST_REPORTS_FROM_THE_FIELD, NPC_RAZAEL))
                    {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_RAZAEL_REPORT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                        player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RAZAEL1, creature->GetGUID());
                        return true;
                    }
                break;
                case NPC_LYANA:
                    if (!player->GetReqKillOrCastCurrentCount(QUEST_REPORTS_FROM_THE_FIELD, NPC_LYANA))
                    {
                        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LYANA_REPORT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
                        player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LYANA1, creature->GetGUID());
                        return true;
                    }
                break;
            }
        player->SEND_GOSSIP_MENU(player->GetGossipTextId(creature), creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
    {
        player->PlayerTalkClass->ClearMenus();
        switch (action)
        {
            case GOSSIP_ACTION_INFO_DEF + 1:
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_RAZAEL2, creature->GetGUID());
                player->TalkedToCreature(NPC_RAZAEL, creature->GetGUID());
                break;
            case GOSSIP_ACTION_INFO_DEF + 2:
                player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_LYANA2, creature->GetGUID());
                player->TalkedToCreature(NPC_LYANA, creature->GetGUID());
                break;
        }
        return true;
    }
};

enum ValgardeEvent
{
    NPC_DRAGONFLAYER_INVADER            = 24051,

    // Dragonflayer Invader
    SPELL_INTERCEPT                     = 58747,
    SPELL_THROW_DRAGONFLAYER_HARPOON    = 42870,

    SAY_AGGRO                           = 0,

    // Dragonflayer Worg
    SPELL_INFECTED_BITE                 = 7367,

    // Valgarde Defender
    SPELL_REVENGE                       = 12170,

    SAY_FIGHT                           = 0
};

class ValgardeEventRespawn : public BasicEvent
{
    public:
        explicit ValgardeEventRespawn(Creature& owner) : _owner(owner) { }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            _owner.Respawn();
            return true;
        }

    private:
        Creature& _owner;
};

struct npc_valgarde_eventAI : public ScriptedAI
{
    npc_valgarde_eventAI(Creature* creature) : ScriptedAI(creature)
    {
        if (me->isDead())
            me->Respawn();
    }

    void Reset() override
    {
        _scheduler.CancelAll();
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->m_Events.AddEvent(new ValgardeEventRespawn(*me), me->m_Events.CalculateTime(10000));
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff,
            std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    protected:
        TaskScheduler _scheduler;
};

struct npc_valgarde_event_attackerAI : public npc_valgarde_eventAI
{
    npc_valgarde_event_attackerAI(Creature* creature) : npc_valgarde_eventAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->SetHomePosition(me->GetPosition());
        if (me->GetEntry() == NPC_DRAGONFLAYER_INVADER)
        {
            if (roll_chance_i(10))
                Talk(SAY_AGGRO);
            _scheduler.Schedule(0s, 1s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_INTERCEPT);
                task.Repeat(15s, 20s);
            });
            _scheduler.Schedule(6s, 10s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_THROW_DRAGONFLAYER_HARPOON);
                task.Repeat(15s, 20s);
            });
        }
        else
        {
            _scheduler.Schedule(2s, 5s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_INFECTED_BITE);
                task.Repeat(6s, 10s);
            });
        }
    }
};

struct npc_valgarde_event_defenderAI : public npc_valgarde_eventAI
{
    npc_valgarde_event_defenderAI(Creature* creature) : npc_valgarde_eventAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(2s, 5s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_REVENGE);
            task.Repeat(5s, 8s);
        });
        if (GuidCheck(me->GetDBTableGUIDLow()))
        {
            _scheduler.Schedule(2s, 5s, [this](TaskContext task)
            {
                if (roll_chance_i(5))
                    Talk(SAY_FIGHT);
                task.Repeat(30s, 1min);
            });
        }
    }

    bool GuidCheck(uint32 dbGUID)
    {
        for (auto guid : { 113665, 113644, 113664, 113663, 112719, 112720 })
            if (dbGUID == guid)
                return true;

        return false;
    }

    void JustDied(Unit* killer) override
    {
        if (GuidCheck(me->GetDBTableGUIDLow()))
            npc_valgarde_eventAI::JustDied(killer);
    }
};

enum Lebronski
{
    NPC_CONSTRUCT      = 24823,

    LEBRONSKI_PATH     = 867730,

    SPELL_QUEST_CREDIT = 44569,
    SPELL_BLUFF        = 44562,

    AURA_VEHICLE       = 46598,

    QUEST_IRON_RUNE    = 11491,

    SAY_SPOTTED        = 1,
    SAY_OUTRO          = 2,

    PHASE_NONE         = 0,
    PHASE_SPOTTED      = 1,

    EVENT_RESET        = 1,
    EVENT_SAY_OUTRO    = 2,
    EVENT_SPOTTED      = 3
};

struct npc_lebronskiAI : public ScriptedAI
{
    npc_lebronskiAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        events.Reset();
        _phase = PHASE_NONE;
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->GetMotionMaster()->MovePath(LEBRONSKI_PATH, true);
    }

    void MoveInLineOfSight(Unit* who)
    {
        if (me->GetDistance(who) > 5.0f)
            return;
        if (!who->IsPlayer() || !who->HasAura(AURA_VEHICLE))
            return;
        if (who->ToPlayer()->GetQuestStatus(QUEST_IRON_RUNE) != QUEST_STATUS_INCOMPLETE)
            return;

        if (_phase == PHASE_NONE)
        {
            _phase = PHASE_SPOTTED;
            me->GetMotionMaster()->Clear();
            me->SetFacingToObject(who);
            me->SetControlled(true, UNIT_STATE_ROOT);
            events.ScheduleEvent(EVENT_SPOTTED, 2s);
            events.ScheduleEvent(EVENT_RESET, 30s);
        }
    }

    void SpellHit(Unit* caster, const SpellInfo* spellInfo)
    {
        if (_phase != PHASE_SPOTTED)
            return;

        if (caster && spellInfo->Id == SPELL_BLUFF)
        {
            caster->CastSpell(caster, SPELL_QUEST_CREDIT, true);
            events.ScheduleEvent(EVENT_SAY_OUTRO, 2s);
        }
    }

    void UpdateAI(uint32 diff)
    {
        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_RESET:
                    Reset();
                    break;
                case EVENT_SAY_OUTRO:
                    Talk(SAY_OUTRO);
                    events.ScheduleEvent(EVENT_RESET, 5s);
                    break;
                case EVENT_SPOTTED:
                    Talk(SAY_SPOTTED);
                    break;
            }
        }
    }

private:
    EventMap events;
    uint8 _phase;
};

void AddSC_howling_fjord()
{
    // Ours
    new npc_attracted_reef_bull();
    new npc_your_inner_turmoil();

    // Theirs
    new npc_apothecary_hanes();
    new npc_plaguehound_tracker();
    new npc_razael_and_lyana();
    new CreatureAILoader<npc_valgarde_event_attackerAI>("npc_valgarde_event_attacker");
    new CreatureAILoader<npc_valgarde_event_defenderAI>("npc_valgarde_event_defender");
    new CreatureAILoader<npc_lebronskiAI>("npc_lebronski");
 }
