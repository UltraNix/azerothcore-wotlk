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

/* ScriptData
SDName: Hellfire_Peninsula
SD%Complete: 100
SDComment: Quest support: 9375, 9410, 9418, 10129, 10146, 10162, 10163, 10340, 10346, 10347, 10382 (Special flight paths) "Needs update"
SDCategory: Hellfire Peninsula
EndScriptData */

/* ContentData
npc_aeranas
npc_ancestral_wolf
npc_wounded_blood_elf
npc_fel_guard_hound
EndContentData */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ScriptedEscortAI.h"
#include "Player.h"
#include "WorldSession.h"
#include <SpellScript.h>

// Ours

class spell_q10935_the_exorcism_of_colonel_jules : public SpellScriptLoader
{
    public:
        spell_q10935_the_exorcism_of_colonel_jules() : SpellScriptLoader("spell_q10935_the_exorcism_of_colonel_jules") { }

        class spell_q10935_the_exorcism_of_colonel_jules_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_q10935_the_exorcism_of_colonel_jules_SpellScript);

            void HandleDummy(SpellEffIndex effIndex)
            {
                PreventHitDefaultEffect(effIndex);
                Creature* target = GetHitCreature();
                if (!target)
                    return;

                if (GetCaster()->IsHostileTo(target))
                    GetCaster()->CastSpell(target, 39323 /*SPELL_HOLY_FIRE*/, true);
                else
                    GetCaster()->CastSpell(target, 39322 /*SPELL_HEAL_BARADA*/, true);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_q10935_the_exorcism_of_colonel_jules_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_q10935_the_exorcism_of_colonel_jules_SpellScript();
        }
};


// Theirs
/*######
## npc_aeranas
######*/

enum Aeranas
{
    SAY_SUMMON                  = 0,
    SAY_FREE                    = 1,
    FACTION_HOSTILE             = 16,
    FACTION_FRIENDLY            = 35,
    SPELL_ENVELOPING_WINDS      = 15535,
    SPELL_SHOCK                 = 12553
};

class npc_aeranas : public CreatureScript
{
public:
    npc_aeranas() : CreatureScript("npc_aeranas") { }

    struct npc_aeranasAI : public ScriptedAI
    {
        npc_aeranasAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            faction_Timer = 8000;
            envelopingWinds_Timer = 9000;
            shock_Timer = 5000;

            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->setFaction(FACTION_FRIENDLY);

            Talk(SAY_SUMMON);
        }

        void UpdateAI(uint32 diff)
        {
            if (faction_Timer)
            {
                if (faction_Timer <= diff)
                {
                    me->setFaction(FACTION_HOSTILE);
                    faction_Timer = 0;
                } else faction_Timer -= diff;
            }

            if (!UpdateVictim())
                return;

            if (HealthBelowPct(30))
            {
                me->setFaction(FACTION_FRIENDLY);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                me->RemoveAllAuras();
                me->DeleteThreatList();
                me->CombatStop(true);
                Talk(SAY_FREE);
                return;
            }

            if (shock_Timer <= diff)
            {
                DoCastVictim(SPELL_SHOCK);
                shock_Timer = 10000;
            } else shock_Timer -= diff;

            if (envelopingWinds_Timer <= diff)
            {
                DoCastVictim(SPELL_ENVELOPING_WINDS);
                envelopingWinds_Timer = 25000;
            } else envelopingWinds_Timer -= diff;

            DoMeleeAttackIfReady();
        }

    private:
        uint32 faction_Timer;
        uint32 envelopingWinds_Timer;
        uint32 shock_Timer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aeranasAI(creature);
    }
};

/*######
## npc_ancestral_wolf
######*/

enum AncestralWolf
{
    EMOTE_WOLF_LIFT_HEAD        = 0,
    EMOTE_WOLF_HOWL             = 1,
    SAY_WOLF_WELCOME            = 2,
    SPELL_ANCESTRAL_WOLF_BUFF   = 29981,
    NPC_RYGA                    = 17123
};

class npc_ancestral_wolf : public CreatureScript
{
public:
    npc_ancestral_wolf() : CreatureScript("npc_ancestral_wolf") { }

    struct npc_ancestral_wolfAI : public npc_escortAI
    {
        npc_ancestral_wolfAI(Creature* creature) : npc_escortAI(creature)
        {
            if (creature->GetOwner() && creature->GetOwner()->GetTypeId() == TYPEID_PLAYER)
                Start(false, true, creature->GetOwner()->GetGUID());
        }

        void Reset()
        {
            ryga = NULL;
            me->CastSpell(me, SPELL_ANCESTRAL_WOLF_BUFF, false);
            me->SetReactState(REACT_PASSIVE);
        }

        void MoveInLineOfSight(Unit* who)

        {
            if (!ryga && who->GetEntry() == NPC_RYGA && me->IsWithinDistInMap(who, 15.0f))
                if (Creature* temp = who->ToCreature())
                    ryga = temp;

            npc_escortAI::MoveInLineOfSight(who);
        }

        void WaypointReached(uint32 waypointId)
        {
            me->CastSpell(me, SPELL_ANCESTRAL_WOLF_BUFF, false);
            switch (waypointId)
            {
                case 0:
                    Talk(EMOTE_WOLF_LIFT_HEAD);
                    break;
                case 2:
                    Talk(EMOTE_WOLF_HOWL);
                    break;
                case 50:
                    if (ryga && ryga->IsAlive() && !ryga->IsInCombat())
                        ryga->AI()->Talk(SAY_WOLF_WELCOME);
                    break;
            }
        }

    private:
        Creature* ryga;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_ancestral_wolfAI(creature);
    }
};

/*######
## npc_wounded_blood_elf
######*/

enum WoundedBloodElf
{
    SAY_ELF_START               = 0,
    SAY_ELF_SUMMON1             = 1,
    SAY_ELF_RESTING             = 2,
    SAY_ELF_SUMMON2             = 3,
    SAY_ELF_COMPLETE            = 4,
    SAY_ELF_AGGRO               = 5,
    QUEST_ROAD_TO_FALCON_WATCH  = 9375,
    NPC_HAALESHI_WINDWALKER     = 16966,
    NPC_HAALESHI_TALONGUARD     = 16967,
    FACTION_FALCON_WATCH_QUEST  = 775
};

class npc_wounded_blood_elf : public CreatureScript
{
public:
    npc_wounded_blood_elf() : CreatureScript("npc_wounded_blood_elf") { }

    struct npc_wounded_blood_elfAI : public npc_escortAI
    {
        npc_wounded_blood_elfAI(Creature* creature) : npc_escortAI(creature) { }

        void Reset() { }

        void EnterCombat(Unit* /*who*/)
        {
            if (HasEscortState(STATE_ESCORT_ESCORTING))
                Talk(SAY_ELF_AGGRO);
        }

        void JustSummoned(Creature* summoned)
        {
            summoned->AI()->AttackStart(me);
        }

        void sQuestAccept(Player* player, Quest const* quest)
        {
            if (quest->GetQuestId() == QUEST_ROAD_TO_FALCON_WATCH)
            {
                me->setFaction(FACTION_FALCON_WATCH_QUEST);
                npc_escortAI::Start(true, false, player->GetGUID());
            }
        }

        void WaypointReached(uint32 waypointId)
        {
            Player* player = GetPlayerForEscort();
            if (!player)
                return;

            switch (waypointId)
            {
                case 0:
                    Talk(SAY_ELF_START, player);
                    break;
                case 9:
                    Talk(SAY_ELF_SUMMON1, player);
                    // Spawn two Haal'eshi Talonguard
                    DoSpawnCreature(NPC_HAALESHI_TALONGUARD, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    DoSpawnCreature(NPC_HAALESHI_TALONGUARD, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    break;
                case 13:
                    Talk(SAY_ELF_RESTING, player);
                    break;
                case 14:
                    Talk(SAY_ELF_SUMMON2, player);
                    // Spawn two Haal'eshi Windwalker
                    DoSpawnCreature(NPC_HAALESHI_WINDWALKER, -15, -15, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    DoSpawnCreature(NPC_HAALESHI_WINDWALKER, -17, -17, 0, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    break;
                case 27:
                    Talk(SAY_ELF_COMPLETE, player);
                    // Award quest credit
                    player->GroupEventHappens(QUEST_ROAD_TO_FALCON_WATCH, me);
                    break;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_wounded_blood_elfAI(creature);
    }
};

/*######
## npc_deranged_helboar
######*/

enum ShizzWork
{
    SPELL_BURNING_SPOKES            = 33908,
    SPELL_ENRAGE                    = 8599,
    SPELL_SUMMON_POODAD             = 37688,

    NPC_FEL_GUARD_HOUND             = 21847,

    QUEST_SHIZZ_WORK                = 10629,

    EVENT_STOP_EATING               = 1,
    EVENT_SUMMON_GOB
};

struct npc_fel_guard_houndAI : public ScriptedAI
{
    npc_fel_guard_houndAI(Creature* creature) : ScriptedAI(creature), _helboarGUID(0) { }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
        {
            if (Creature* helboar = ObjectAccessor::GetCreature(*me, _helboarGUID))
                me->SetFacingToObject(helboar);
            me->SetUInt32Value(UNIT_NPC_EMOTESTATE, EMOTE_STATE_ATTACK_UNARMED);
            _events.ScheduleEvent(EVENT_STOP_EATING, 3s);
        }
    }

    void SetGUID(uint64 guid, int32 id) override
    {
        if (id == 1)
            _helboarGUID = guid;
    }

    void UpdateAI(uint32 diff) override
    {
        if (_events.Empty())
            return;

        _events.Update(diff);

        switch (_events.ExecuteEvent())
        {
            case EVENT_STOP_EATING:
                me->SetUInt32Value(UNIT_NPC_EMOTESTATE, 0);
                if (Unit* owner = me->GetOwner())
                    me->GetMotionMaster()->MoveFollow(owner, owner->GetObjectSize(), owner->GetFollowAngle());
                _events.ScheduleEvent(EVENT_SUMMON_GOB, 2s);
                break;
            case EVENT_SUMMON_GOB:
                DoCastSelf(SPELL_SUMMON_POODAD, true);
                _helboarGUID = 0;
                break;
            default:
                break;
        }
    }

    private:
        EventMap _events;
        uint64 _helboarGUID;
};

struct npc_deranged_helboarAI : public ScriptedAI
{
    npc_deranged_helboarAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _enraged = false;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        if (!_enraged && me->HealthBelowPctDamaged(30, damage))
        {
            _enraged = true;
            DoCastSelf(SPELL_ENRAGE, true);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        // spell 37689 should be used to inform hound about helboar
        // right now it can't be done, we don't have any way to ensure that hound belongs to loot recipient
        if (Player* player = me->GetLootRecipient())
            if (player->GetQuestStatus(QUEST_SHIZZ_WORK) == QUEST_STATUS_INCOMPLETE)
            {
                std::list<Creature*> minions;
                player->GetAllMinionsByEntry(minions, NPC_FEL_GUARD_HOUND);
                if (Creature* hound = minions.front())
                    if (hound->IsInWorld())
                    {
                        if (hound->IsAIEnabled)
                            hound->AI()->SetGUID(me->GetGUID(), 1);
                        hound->SetWalk(true);
                        Position pos;
                        me->GetNearPosition(pos, hound->GetObjectSize() + 1.5f, hound->GetRelativeAngle(me));
                        hound->GetMotionMaster()->MovePoint(1, pos, true, false);
                    }
            }
    }

    private:
        bool _enraged;
};


class npc_foreman_razelcraz : public CreatureScript
{
    public:
        npc_foreman_razelcraz() : CreatureScript("npc_foreman_razelcraz") { }

        bool OnQuestReward(Player* player, Creature* /*creature*/, Quest const* quest, uint32 /*opt*/)
        {
            if (quest->GetQuestId() == QUEST_SHIZZ_WORK)
            {
                std::list<Creature*> minions;
                player->GetAllMinionsByEntry(minions, NPC_FEL_GUARD_HOUND);
                if (Creature* hound = minions.front())
                    if (hound->IsInWorld())
                        hound->DespawnOrUnsummon();
            }

            return false;
        }
};

/*######
## npc_fel_cannon_mki
######*/

enum FelCannonMki
{
    SPELL_FEL_CANNON_BLAST = 36238
};

class npc_fel_cannon_mki : public CreatureScript
{
public:
    npc_fel_cannon_mki() : CreatureScript("npc_fel_cannon_mki") { }

    struct npc_fel_cannon_mkiAI : public ScriptedAI
    {
        npc_fel_cannon_mkiAI(Creature* creature) : ScriptedAI(creature)
        {
            SetCombatMovement(false);
        }

        void Reset()
        {
            CastTimer = 2000;
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (CastTimer <= diff)
            {
                DoCast(me->GetVictim(), SPELL_FEL_CANNON_BLAST);
                CastTimer = 2000 + urand(0, 2000);
            }
            else CastTimer -= diff;
        }

    private:
        uint32 CastTimer;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fel_cannon_mkiAI(creature);
    }
};

enum Agonis
{
    EVENT_AGONIS_CORRUPTION        = 1,
    EVENT_AGONIS_SELECT_TARGET     = 2,

    SPELL_AGONIS_CORRUPTION        = 21068,
};

class npc_aggonis : public CreatureScript
{
public:
    npc_aggonis() : CreatureScript("npc_aggonis") { }

    struct npc_aggonisAI : public ScriptedAI
    {
        npc_aggonisAI(Creature* creature) : ScriptedAI(creature) {}

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_AGONIS_CORRUPTION, urand(5000, 8000));
            events.ScheduleEvent(EVENT_AGONIS_SELECT_TARGET, 3000);
        }

        void JustRespawned() { Reset(); }

        void AttackStart(Unit* who)
        {
            if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE))
                return;

            ScriptedAI::AttackStart(who);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim() && !me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE))
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.ExecuteEvent())
            {
                case EVENT_AGONIS_CORRUPTION:
                    DoCast(me->GetVictim(), SPELL_AGONIS_CORRUPTION);
                    events.RepeatEvent(urand(15000, 20000));
                    break;
                case EVENT_AGONIS_SELECT_TARGET:
                    me->MonsterSay("Fools!  You seek to abjure my father\'s presence?  Death awaits you, mortals!", 0, me->GetVictim());
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);

                    if (Unit *pTarget = me->SelectNearestTarget(40))
                    {
                        me->GetMotionMaster()->MoveChase(pTarget);
                        AttackStart(pTarget);
                    }
                    events.PopEvent();
                    break;
            }

            DoMeleeAttackIfReady();
        }

        private:
            EventMap events;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_aggonisAI(creature);
    }
};

enum colonelSpells
{
    SPELL_COL_FEIGN_DEATH           = 39283,
    SPELL_JULES_THREATENS           = 39284,
    SPELL_JULES_UPRIGHT             = 39294,
    SPELL_JULES_VOMIT               = 39295,
    SPELL_JULES_PRONE               = 39283
};

enum colonelEvents
{
    EVENT_COL_BEGIN                 = 1,
    EVENT_COL_1                     = 2,
    EVENT_COL_2                     = 3,
    EVENT_COL_3                     = 4,
    EVENT_COL_4                     = 5,
    EVENT_COL_5                     = 6,
    EVENT_COL_6                     = 7,
    EVENT_COL_7                     = 8,
    EVENT_COL_8                     = 9,
    EVENT_COL_9                     = 10,
    EVENT_COL_10                    = 11,
    EVENT_COL_11                    = 12,
    EVENT_COL_12                    = 13,
    EVENT_COL_13                    = 14,
    EVENT_SPAWN_COL_ADDS            = 15
};

enum colonelMisc
{
    SAY_COL_1                       = 0,
    SAY_COL_2                       = 1,

    NPC_FLYING_SKULL                = 22507,
    QUEST_EXORCISM_OF_COLONEL       = 10935
};

Position const colonelSummonPosition = { -710.0f, 2754.28f, 104.3f, 4.7f };

struct npc_colonel_julesAI : public npc_escortAI
{
    npc_colonel_julesAI(Creature* creature) : npc_escortAI(creature), summons(me) { }

    void sGossipHello(Player* player) override
    {
        if (player->GetQuestStatus(QUEST_EXORCISM_OF_COLONEL) == QUEST_STATUS_INCOMPLETE)
        {
            player->KilledMonsterCredit(me->GetEntry(), me->GetGUID());
        }
    }

    void Reset() override
    {
        _eventInProgress = false;
        me->SetUInt32Value(UNIT_NPC_FLAGS, 0); // override all flags
        me->SetReactState(REACT_PASSIVE);
        DoCastSelf(SPELL_COL_FEIGN_DEATH);
        me->SetCanFly(false);
        _events.Reset();
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type == 1 && data == 1 && !_eventInProgress)
        {
            _eventInProgress = true;
            _events.ScheduleEvent(EVENT_COL_BEGIN, 14000);
            Talk(SAY_COL_1);
        }
    }

    void JustSummoned(Creature* creature) override
    {
        summons.Summon(creature);
    }

    void WaypointReached(uint32 waypointId) override
    {
        if (waypointId == 44)
        {
            me->SetCanFly(false);
            me->RemoveAllAuras();
            me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            DoCastSelf(SPELL_COL_FEIGN_DEATH);
            _events.ScheduleEvent(EVENT_COL_12, 35000);
            _events.CancelEvent(EVENT_SPAWN_COL_ADDS);
            summons.DespawnAll();
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_eventInProgress)
            return;

        npc_escortAI::UpdateAI(diff);

        _events.Update(diff);

        while (auto eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_COL_BEGIN:
                    me->SetCanFly(true);
                    Talk(SAY_COL_2);
                    _events.ScheduleEvent(EVENT_COL_1, 9000);
                    break;
                case EVENT_COL_1:
                    me->RemoveAurasDueToSpell(SPELL_COL_FEIGN_DEATH);
                    DoCastSelf(SPELL_JULES_UPRIGHT);
                    Start(true, false, 0, nullptr);
                    SetDespawnAtEnd(false);
                    _events.ScheduleEvent(EVENT_SPAWN_COL_ADDS, 3000);
                    _events.ScheduleEvent(EVENT_COL_2, 4000);
                    break;
                case EVENT_SPAWN_COL_ADDS:
                    me->SummonCreature(NPC_FLYING_SKULL, colonelSummonPosition, TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 60000);
                    _events.Repeat(urand(5000, 8000));
                    break;
                case EVENT_COL_2:
                    DoCastSelf(SPELL_JULES_THREATENS, true);
                    DoCastSelf(SPELL_JULES_UPRIGHT);
                    _events.ScheduleEvent(EVENT_COL_3, 9000);
                    break;
                case EVENT_COL_3:
                    Talk(SAY_COL_2);
                    _events.ScheduleEvent(EVENT_COL_4, 25000);
                    break;
                case EVENT_COL_4:
                    Talk(SAY_COL_2);
                    _events.ScheduleEvent(EVENT_COL_5, 30000);
                    break;
                case EVENT_COL_5:
                    _events.ScheduleEvent(EVENT_COL_6, 4000);
                    break;
                case EVENT_COL_6:
                    DoCastSelf(SPELL_JULES_UPRIGHT, true);
                    _events.ScheduleEvent(EVENT_COL_7, 3500);
                    break;
                case EVENT_COL_7:
                    DoCastSelf(SPELL_JULES_VOMIT, true);
                    _events.ScheduleEvent(EVENT_COL_8, 8500);
                    break;
                case EVENT_COL_8:
                    Talk(SAY_COL_2);
                    _events.ScheduleEvent(EVENT_COL_9, 18000);
                    break;
                case EVENT_COL_9:
                    Talk(SAY_COL_2);
                    _events.ScheduleEvent(EVENT_COL_10, 18000);
                    break;
                case EVENT_COL_10:
                    Talk(SAY_COL_2);
                    _events.ScheduleEvent(EVENT_COL_11, 18000);
                    break;
                case EVENT_COL_11:
                    Talk(SAY_COL_2);
                    break;
                case EVENT_COL_12:
                    Reset();
                    break;
            }
        }

    }
private:
    bool _eventInProgress;
    EventMap _events;
    SummonList summons;
};

class AbyssalShelfRespawn : public BasicEvent
{
    public:
        explicit AbyssalShelfRespawn(Creature& owner) : _owner(owner) { }

        bool Execute(uint64 /*currTime*/, uint32 /*diff*/)
        {
            _owner.Respawn();
            return true;
        }

    private:
        Creature& _owner;
};

struct npc_abyssal_shelfAI : public ScriptedAI
{
    npc_abyssal_shelfAI(Creature* creature) : ScriptedAI(creature) { }

    void JustDied(Unit* /*killer*/) override
    {
        me->m_Events.AddEvent(new AbyssalShelfRespawn(*me), me->m_Events.CalculateTime(20000));
    }
};

#define GOSSIP_ITEM_ATTUNE    "Yes, Scryer. You may possess me."

enum DemoniacScryer
{
    GOSSIP_TEXTID_PROTECT           = 10659,
    GOSSIP_TEXTID_ATTUNED           = 10643,

    QUEST_DEMONIAC                  = 10838,
    NPC_HELLFIRE_WARDLING           = 22259,
    NPC_ORC_HA                      = 22273,
    NPC_BUTTRESS                    = 22267,
    NPC_BUTTRESS_SPAWNER            = 22260,

    SPELL_SUMMONED                  = 7741,
    SPELL_DEMONIAC_VISITATION       = 38708,
    SPELL_BUTTRESS_APPERANCE        = 38719,
    SPELL_SUCKER_CHANNEL            = 38721,
    SPELL_SUCKER_DESPAWN_MOB        = 38691,
    SPELL_SUCKER_SPAWN_MOB          = 38679,
    SPELL_SUCKER_SPAWN_BOSS         = 38709,
    SPELL_SUCKER_SPAWN_BUTRESS_N    = 38675,
    SPELL_SUCKER_SPAWN_BUTRESS_S    = 38676,
    SPELL_SUCKER_SPAWN_BUTRESS_E    = 38677,
    SPELL_SUCKER_SPAWN_BUTRESS_W    = 38678,
    SPELL_SUCKER_SPAWN_SPAWNER      = 38681,
    SPELL_SPAWNER_VISUAL_EFFECT     = 38727,
    SPELL_SUCKER_APPEARANCE         = 38690,
    SPELL_MOB_DESPAWN_VISUAL        = 38891,

    EVENT_SUMMON_IMP                = 1,
    EVENT_SUMMON_ORC,
    EVENT_SUMMON_BUTTRESS,
    EVENT_START_ATTACK,
    EVENT_DESPAWN
};

static const std::vector<uint32> ButressSpells = { SPELL_SUCKER_SPAWN_BUTRESS_N, SPELL_SUCKER_SPAWN_BUTRESS_S, SPELL_SUCKER_SPAWN_BUTRESS_E, SPELL_SUCKER_SPAWN_BUTRESS_W, SPELL_SUCKER_SPAWN_SPAWNER };

struct npc_demoniac_scryerAI : public ScriptedAI
{
    npc_demoniac_scryerAI(Creature* creature) : ScriptedAI(creature), _summons(creature)
    {
        _summons.DespawnAll();
        _events.Reset();
        _events.ScheduleEvent(EVENT_SUMMON_IMP, 15s);
        _events.ScheduleEvent(EVENT_SUMMON_ORC, 2min + 15s);
        _events.ScheduleEvent(EVENT_SUMMON_BUTTRESS, 45s);
        _buttressCount = 0;
        _completed = false;
        me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        DoCastSelf(SPELL_SUCKER_APPEARANCE, true);
        me->SetRegeneratingHealth(false);
    }

    void AttackStart(Unit* /*enemy*/) override { }
    void EnterEvadeMode() override
    {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
    }

    void JustSummoned(Creature* summon) override
    {
        switch (summon->GetEntry())
        {
            case NPC_HELLFIRE_WARDLING:
            case NPC_ORC_HA:
                summon->SetPassive();
                summon->CastSpell(summon, SPELL_SUMMONED, false);
                _events.RescheduleEvent(EVENT_START_ATTACK, 2s);
                break;
            case NPC_BUTTRESS:
                summon->SetFacingToObject(me);
                summon->CastSpell(summon, SPELL_BUTTRESS_APPERANCE, false);
                summon->CastSpell(me, SPELL_SUCKER_CHANNEL, false);
                break;
            case NPC_BUTTRESS_SPAWNER:
                summon->CastSpell(summon, SPELL_SPAWNER_VISUAL_EFFECT, true);
                break;
            default:
                break;
        }

        _summons.Summon(summon);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _summons.DespawnAll();
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        _summons.Despawn(summon);
        summon->DespawnOrUnsummon();
    }

    void sGossipHello(Player* player) override
    {
        if (_completed)
        {
            if (player->GetQuestStatus(QUEST_DEMONIAC) == QUEST_STATUS_INCOMPLETE)
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_ATTUNE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_ATTUNED, me->GetGUID());
            return;
        }

        player->SEND_GOSSIP_MENU(GOSSIP_TEXTID_PROTECT, me->GetGUID());
        return;
    }

    void sGossipSelect(Player* player, uint32 /*sender*/, uint32 /*action*/) override
    {
        player->CLOSE_GOSSIP_MENU();
        DoCast(player, SPELL_DEMONIAC_VISITATION);
        _events.RescheduleEvent(EVENT_DESPAWN, 2.5min);
    }

    void UpdateAI(uint32 const diff) override
    {
        UpdateVictim();
        if (_events.Empty())
            return;

        _events.Update(diff);

        switch (_events.ExecuteEvent())
        {
            case EVENT_SUMMON_IMP:
                DoCastAOE(SPELL_SUCKER_SPAWN_MOB);
                _events.Repeat(15s);
                break;
            case EVENT_SUMMON_ORC:
                DoCastAOE(SPELL_SUCKER_SPAWN_BOSS);
                break;
            case EVENT_SUMMON_BUTTRESS:
                if (_buttressCount < ButressSpells.size())
                {
                    DoCastSelf(ButressSpells[_buttressCount]);
                    ++_buttressCount;
                }

                if (_buttressCount == 5)
                {
                    _completed = true;
                    _events.Reset();
                    _events.ScheduleEvent(EVENT_DESPAWN, 2min);
                    break;
                }

                _events.Repeat(45s);
                break;
            case EVENT_START_ATTACK:
                _summons.Broadcast([this](Creature* summon)
                {
                    if (summon->GetEntry() == NPC_HELLFIRE_WARDLING || summon->GetEntry() == NPC_ORC_HA && summon->GetReactState() == REACT_PASSIVE)
                    {
                        summon->SetAggressive();
                        if (summon->IsAIEnabled)
                            summon->AI()->AttackStart(me);
                    }
                });
                break;
            case EVENT_DESPAWN:
                _summons.DespawnAll();
                me->DespawnOrUnsummon();
                break;
            default:
                break;
        }
    }

    private:
        EventMap _events;
        uint32 _buttressCount;
        bool _completed;
        SummonList _summons;
};

// 38708 - Demonaic Visitation
class spell_demonaic_visitation_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_demonaic_visitation_AuraScript);

    void OnAuraRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE && GetCaster() && GetCaster()->IsInMap(GetTarget()) && GetTarget()->IsPlayer())
            GetCaster()->MonsterWhisper("Thank you for allowing me to visit, $N. You have a very colorful soul, but it's a little brighter than I prefer... or I might have stayed longer!", GetTarget()->ToPlayer());
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_demonaic_visitation_AuraScript::OnAuraRemove, EFFECT_1, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_hellfire_peninsula()
{
    // Ours
    new spell_q10935_the_exorcism_of_colonel_jules();
    new npc_fel_cannon_mki();
    new npc_aggonis();

    // Theirs
    new npc_aeranas();
    new npc_ancestral_wolf();
    new npc_wounded_blood_elf();
    new CreatureAILoader<npc_fel_guard_houndAI>("npc_fel_guard_hound");
    new CreatureAILoader<npc_deranged_helboarAI>("npc_deranged_helboar");
    new npc_foreman_razelcraz();
    new CreatureAILoader<npc_colonel_julesAI>("npc_colonel_jules");
    new CreatureAILoader<npc_abyssal_shelfAI>("npc_abyssal_shelf");
    new CreatureAILoader<npc_demoniac_scryerAI>("npc_demoniac_scryer");
    new AuraScriptLoaderEx<spell_demonaic_visitation_AuraScript>("spell_demonaic_visitation");
}
