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
## npc_fel_guard_hound
######*/

enum FelGuard
{
    SPELL_SUMMON_POO            = 37688,
    NPC_DERANGED_HELBOAR        = 16863
};

class npc_fel_guard_hound : public CreatureScript
{
public:
    npc_fel_guard_hound() : CreatureScript("npc_fel_guard_hound") { }

    struct npc_fel_guard_houndAI : public ScriptedAI
    {
        npc_fel_guard_houndAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset()
        {
            checkTimer = 5000; //check for creature every 5 sec
            helboarGUID = 0;
        }

        void MovementInform(uint32 type, uint32 id)
        {
            if (type != POINT_MOTION_TYPE || id != 1)
                return;

            if (Creature* helboar = ObjectAccessor::GetCreature(*me, helboarGUID))
            {
                helboar->RemoveCorpse();
                DoCast(SPELL_SUMMON_POO);

                if (Player* owner = me->GetCharmerOrOwnerPlayerOrPlayerItself())
                    me->GetMotionMaster()->MoveFollow(owner, 0.0f, 0.0f);
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (checkTimer <= diff)
            {
                if (Creature* helboar = me->FindNearestCreature(NPC_DERANGED_HELBOAR, 10.0f, false))
                {
                    if (helboar->GetGUID() != helboarGUID && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE && !me->FindCurrentSpellBySpellId(SPELL_SUMMON_POO))
                    {
                        helboarGUID = helboar->GetGUID();
                        me->GetMotionMaster()->MovePoint(1, helboar->GetPositionX(), helboar->GetPositionY(), helboar->GetPositionZ());
                    }
                }
                checkTimer = 5000;
            }
            else checkTimer -= diff;

            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }

    private:
        uint32 checkTimer;
        uint64 helboarGUID;
    };

    CreatureAI* GetAI(Creature* creature) const
    {
        return new npc_fel_guard_houndAI(creature);
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
            _events.ScheduleEvent(EVENT_COL_12, 25000);
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
    new npc_fel_guard_hound();
    new CreatureAILoader<npc_colonel_julesAI>("npc_colonel_jules");
    new CreatureAILoader<npc_abyssal_shelfAI>("npc_abyssal_shelf");
}
