/*
* Copyright (C) 2015-2015 Theatre of Dreams
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

#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "Spell.h"
#include "old_scarlet_monastery.h"
#include "Unit.h"

enum Say
{
    SAY_BOSS_0 = 0, // What is that smell!? eww!
    SAY_BOSS_1 = 1, // uh.. strangers.. I''m Mazin Soulstealer, are you here to fight me?
    SAY_BOSS_2 = 2, // Fine, we will fight but first let me show you my collection... my collection of souls
    SAY_BOSS_3 = 3, // My powers allow me to steal part of someone soul without killing him, they''re not the real deal, but strong enough to kill you!
    SAY_BOSS_4 = 4, // Go''el also known as Thrall. Warchief of the Orcish Horde!
    SAY_BOSS_5 = 5, // Dark Ranger, Mistress Sylvanas!
    SAY_BOSS_6 = 6, // Founder of the Cult of the Damned, Kel''Thuzad!
    SAY_BOSS_7 = 7, // The end is near!
    SAY_BOSS_8 = 8, // Killing is not so easy as the innocent believe $n || There will be killing till the score is paid $n || Killing makes me feel good $n
    SAY_BOSS_9 = 9, // The death of the soul is more painful than that of the body. Javier.. Matar! MATARLOS A TODOS! \\ Javier.. kill them! KILL THEM ALL!
};

enum Spells
{
    SPELL_EVIL_TP = 61456,
    SPELL_ROOM_DUMMY = 2766,
    SPELL_ROOM_STUN = 44432, // cube stun
    SPELL_DEATH_SHOCK = 65725,
    SPELL_KNEEL = 39656,

    // Thrall
    SPELL_GROUND_SHAKER = 63157,
    SPELL_CHAIN_LIGHTNING = 64759,
    SPELL_LIGHTNING_SHIELD = 20545,
    SPELL_LAVA_BURST = 67330,
    SPELL_BLOODLUST = 23951,
    SPELL_AOE_AVOIDANCE = 68595,

    // Sylvanas
    SPELL_AUTO_SHOT = 38295,
    SPELL_FREEZING_TRAP = 43447,
    SPELL_DISARM_SILENCE = 51897,
    SPELL_FADE = 20672,
    SPELL_THROW_SPEAR = 61873,

    // Elementals
    SPELL_CHARGE = 19196,
    SPELL_LIGHTNING = 37681,
    SPELL_TORN_EARTH = 61897,
    SPELL_FIRE_FLY = 38267,

    // Void Zone
    SPELL_ZONE_VISUAL = 64384,
    SPELL_VOID_BLAST = 27812,

    // KelThuzad
    SPELL_FROST_BOLT = 28478,
    SPELL_FROST_VOLLEY = 69273,

    // KelThuzad Adds
    SPELL_BLADESTORM = 67541,

    // Orbs
    SPELL_EXPLOSION = 29324,

    // Soulstealer
    SPELL_PLAGUE_BARREL = 59460,
    SPELL_FIRE_BARRAGE = 30282,
    SPELL_MAGIC_DEBUFF = 38742,
    SPELL_FEL_FIREBALL = 40633,
    SPELL_IMMUNITY_SOULSTEALER = 74458,
    SPELL_DARK_WINGS = 30000,
    SPELL_BERSERK = 68378,
};

enum Events
{
    // Intro events
    EVENT_INTRO_1 = 1,
    EVENT_INTRO_2 = 2,
    EVENT_INTRO_3 = 3,
    EVENT_INTRO_4 = 4,
    EVENT_INTRO_5 = 5,
    EVENT_INTRO_6 = 6,
    EVENT_INTRO_7 = 7,
    EVENT_INTRO_8 = 8,
    EVENT_INTRO_9 = 9,
    EVENT_INTRO_10 = 10,
    EVENT_INTRO_11 = 11,
    EVENT_INTRO_12 = 12,
    EVENT_INTRO_13 = 13,
    // end of Intro Events
    EVENT_P1_1 = 14, // activate thrall
    // Thrall events
    EVENT_CB_SHAKER = 15,
    EVENT_CB_CHAIN = 16,
    EVENT_CB_SHIELD = 17,
    EVENT_CB_LBURST = 18,
    EVENT_CB_BLOODLUST = 19,
    EVENT_SOULSTEALER_BERSERK = 20,
    EVENT_ACTIVATE_SUMMONS = 21,
    // elemental events
    EVENT_AIR_ELE_SPELLS = 22,
    EVENT_FIRE_ELE_SPELLS = 23,
    EVENT_EARTH_ELE_SPELLS = 24,
    // sylvanas events
    EVENT_THROW_SPEAR = 25,
    EVENT_SYLV_KNOCKBACK = 26,
    EVENT_SYLV_FREEZING_TRAP = 27, // do poprawy,widac jak player kladzie trap
    EVENT_SYLV_DISARM_SILENCE = 28,
    EVENT_SYLV_FADE = 29,
    EVENT_SOULSTEALER_DEATH = 30,
    EVENT_SPAWN_RAGING_SKELETON = 31,
    EVENT_KELTHUZAD_FRST_VOLLEY = 32,

    // Raging Skeleton
    EVENT_SKEL_BLADE_STORM = 33,

    // Soulstealer
    EVENT_SOULSTEALER_ROOM = 34,
    EVENT_SOULSTEALER_BARREL = 35,
    EVENT_SOULSTEALER_MGC_DBF = 36,
    EVENT_SOULSTEALER_FEL_FIRE = 37,
    EVENT_SOULSTEALER_BARRAGE = 38,
    EVENT_SOULSTEALER_VOIDZONE = 39,
    EVENT_SOULSTEALER_WINGS = 40,
    EVENT_SOULSTEALER_TELEPORT = 41,

    // Sylvanas misc events, ustawiam jakis delay miedzy atakami,bo jak sie zrobi niewidzialna to zabije clotha na strzala za nim tank bedzie mogl zareagowac
    EVENT_START_ATTACKING = 42,
};

enum bossActions
{
    ACTION_ENTER_FIGHT = 1,
    ACTION_THRALL_DEATH = 2,
    ACTION_SYLVANAS_DEATH = 3,
    ACTION_KELTHUZAD_DEATH = 4,
};

enum Misc
{
    ONESHOT_LAUGH = 11,
};

const float RANGE_COMBAT_RANGE = 8.0f;

Position const soulPositions[3] =
{
    { 208.95f, -83.61f, 18.67f, 3.12f },
    { 192.27f, -59.37f, 18.67f, 4.73f },
    { 167.77f, -75.39f, 18.67f, 6.27f }
};

Position enterFightPos[3] =
{
    { 197.27f, -83.66f, 18.02f, 3.16f },
    { 192.70f, -71.30f, 18.02f, 4.77f },
    { 181.05f, -75.71f, 18.02f, 0.06f }
};

Position spawnElementals[4] =
{
    { 188.89f, -72.05f, 18.02f, 4.73f },
    { 197.37f, -79.64f, 18.02f, 3.17f },
    { 188.85f, -88.67f, 18.02f, 1.62f },
    { 180.29f, -79.04f, 18.02f, 6.24f }
};

Position arrowPos[9] =
{
    { 174.12f, -69.59f, 36.55f },
    { 173.98f, -78.86f, 36.55f },
    { 173.77f, -92.83f, 36.55f },
    { 181.55f, -92.88f, 33.89f },
    { 192.30f, -92.83f, 33.89f },
    { 201.69f, -81.82f, 33.31f },
    { 200.12f, -67.99f, 33.31f },
    { 190.95f, -67.08f, 32.13f },
    { 179.12f, -67.23f, 31.47f }
};

Position teleMiddlePos[3] =
{
    { 184.00f, -79.47f, 18.02f, 4.72f },
    { 192.69f, -79.67f, 18.02f, 4.76f },
    { 188.75f, -84.58f, 18.02f, 4.75f }
};

Position posIntro1 = { 184.18f, -84.50f, 18.02f };
Position walkFirstSoul = { 199.40f, -84.03f, 18.02f, 0.16f };
Position walkSecondSoul = { 192.69f, -68.43f, 18.02f, 1.64f };
Position walkThirdSoul = { 176.10f, -75.26f, 18.02f, 3.31f };
Position posStartFight = { 184.04f, -92.07f, 18.02f, 1.65f };

Position const teleportPos = { 182.13f, -132.50f, 18.02f };
Position spawnDeathOrb = { 188.44f, -74.82f, 18.02f };
Position arcanePos = { 189.22f, -78.83f, 24.09f };

class demonWingSelector
{
    public:
        demonWingSelector() { }

        bool operator()(Unit* target) const
        {
            return target->GetTypeId() == TYPEID_PLAYER && !target->HasAura(SPELL_ROOM_DUMMY);
        }
};

class boss_mazin_soulstealer : public CreatureScript
{
    public:
        boss_mazin_soulstealer() : CreatureScript("boss_mazin_soulstealer") { }

        struct boss_mazin_soulstealerAI : public BossAI
        {
            boss_mazin_soulstealerAI(Creature* creature) : BossAI(creature, DATA_MAZIN_SOULSTEALER), summons(me)
            {
                instance = creature->GetInstanceScript();
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
                intro = false;
                orient = 0;
                deathCount = 0;
                canMelee = true;
            }

            void Reset() override
            {
                _Reset();
                events.SetPhase(PHASE_NONE);
                if (intro)
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
            }

            void MoveInLineOfSight(Unit* who) override
            {
                if (who->ToPlayer() && who->ToPlayer()->IsGameMaster())
                    return;

                if (intro)
                    return;

                if (who->IsWithinDist(me, 5.0f))
                {
                    orient = who->GetOrientation();
                    intro = true;
                    me->SetWalk(true);
                    me->HandleEmoteCommand(ONESHOT_LAUGH);
                    events.ScheduleEvent(EVENT_INTRO_2, 1000);
                    events.SetPhase(PHASE_INTRO);
                }
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (events.IsInPhase(PHASE_ONE))
                    damage = damage * 0.1f;
                else if
                    (events.IsInPhase(PHASE_TWO))
                    damage = damage * 0.3f;
                else if
                    (events.IsInPhase(PHASE_THREE))
                    damage = damage * 0.5f;

                if (me->HealthBelowPctDamaged(40, damage) && events.IsInPhase(PHASE_FOUR))
                {
                    events.SetPhase(PHASE_FIVE);
                    events.ScheduleEvent(EVENT_SOULSTEALER_VOIDZONE, 6000, 1);
                    events.CancelEvent(EVENT_SOULSTEALER_ROOM);
                    events.CancelEvent(EVENT_SOULSTEALER_BARREL);
                }

                if (me->HealthBelowPctDamaged(1, damage) && events.IsInPhase(PHASE_FIVE))
                {
                    events.SetPhase(PHASE_SIX);
                    damage = 0;
                    canMelee = false;
                    Talk(SAY_BOSS_9);
                    events.ScheduleEvent(EVENT_SOULSTEALER_DEATH, 1);
                    me->SetReactState(REACT_PASSIVE);
                    DoStopAttack();
                }
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
            }

            void KilledUnit(Unit* victim) override
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    if (urand(0, 3))
                        Talk(SAY_BOSS_8, victim);
            }

            void SummonedCreatureDies(Creature* summon, Unit* killer) override
            {
                switch (summon->GetEntry())
                {
                    case NPC_SOUL_THRALL:
                        if (Creature* sylvanas = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_SOUL_SYLVANAS)))
                            sylvanas->AI()->DoAction(ACTION_ENTER_FIGHT);

                        events.SetPhase(PHASE_TWO);
                        events.ScheduleEvent(EVENT_SOULSTEALER_MGC_DBF, 4000, 1);
                        events.ScheduleEvent(EVENT_SOULSTEALER_FEL_FIRE, 4100, 1); // triggered
                        break;
                    case NPC_SOUL_SYLVANAS:
                        events.SetPhase(PHASE_THREE);
                        if (Creature* kelthuzad = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_SOUL_KELTHUZAD)))
                            kelthuzad->AI()->DoAction(ACTION_ENTER_FIGHT);

                        events.ScheduleEvent(EVENT_SOULSTEALER_BARREL, 5000, 1);
                        break;
                    case NPC_SOUL_KELTHUZAD:
                        events.SetPhase(PHASE_FOUR);

                        events.ScheduleEvent(EVENT_SOULSTEALER_ROOM, 15000, 1);
                        events.ScheduleEvent(EVENT_SOULSTEALER_WINGS, 6000, 1);
                        break;
                    default:
                        break;
                }
            }

            void JustReachedHome() override
            {
                _JustReachedHome();
                Reset();
                summons.DespawnAll();
                if (Map* map = me->GetMap())
                {
                    Map::PlayerList const& players = map->GetPlayers();
                    for (auto const& i : players)
                    {
                        if (Player* player = i.GetSource())
                        {
                            //! player has an aura which means he is stuck in death orb room
                            //! lets remove stun auras, visual auras and teleport him outside the room
                            if (player->HasAura(SPELL_ROOM_DUMMY))
                            {
                                player->CastSpell(player, SPELL_EVIL_TP);
                                player->RemoveAurasDueToSpell(SPELL_ROOM_DUMMY);
                                player->RemoveAurasDueToSpell(SPELL_ROOM_STUN);
                                player->ToPlayer()->TeleportTo(44, spawnDeathOrb.GetPositionX(), spawnDeathOrb.GetPositionY(), spawnDeathOrb.GetPositionZ(), player->GetOrientation());
                            }
                        }
                    }
                }
            }

            void EnterCombat(Unit* target) override
            {
                events.SetPhase(PHASE_ONE);
                me->SetReactState(REACT_AGGRESSIVE);

                _EnterCombat();
                if (Creature* thrall = me->SummonCreature(NPC_SOUL_THRALL, soulPositions[0], TEMPSUMMON_MANUAL_DESPAWN))
                    thrall->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                if (Creature* sylvanas = me->SummonCreature(NPC_SOUL_SYLVANAS, soulPositions[1], TEMPSUMMON_MANUAL_DESPAWN))
                    sylvanas->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                if (Creature* kelthuzad = me->SummonCreature(NPC_SOUL_KELTHUZAD, soulPositions[2], TEMPSUMMON_MANUAL_DESPAWN))
                    kelthuzad->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);

                events.ScheduleEvent(EVENT_P1_1, 3000);
                // schedule spells
                events.ScheduleEvent(EVENT_SOULSTEALER_BARRAGE, 8000, 1);
                events.ScheduleEvent(EVENT_SOULSTEALER_BERSERK, 720000);
            }

            void JustDied(Unit* killer) override
            {
                _JustDied();
                summons.DespawnAll();
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                switch (id)
                {
                    case 1:
                        events.ScheduleEvent(EVENT_INTRO_5, 1500);
                        break;
                    case 2:
                        events.ScheduleEvent(EVENT_INTRO_8, 1500);
                        break;
                    case 3:
                        events.ScheduleEvent(EVENT_INTRO_10, 1500);
                        break;
                    case 4:
                    {
                        me->SetFacingTo(1.65f);
                        me->SetWalk(false);
                        me->SetReactState(REACT_DEFENSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                        Position pos = me->GetPosition();
                        pos.SetOrientation(1.65f);
                        me->SetHomePosition(pos);
                        break;
                    }
                    default:
                        break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (events.GetPhaseMask() != PHASE_INTRO && !UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                if (!CheckInRoom() && !me->IsInEvadeMode())
                    EnterEvadeMode();

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        // ####### INTRO #########
                        case EVENT_INTRO_2:
                            Talk(SAY_BOSS_0);

                            events.ScheduleEvent(EVENT_INTRO_3, 6000);
                            break;
                        case EVENT_INTRO_3:
                            Talk(SAY_BOSS_1);
                            me->SetFacingTo(orient);

                            events.ScheduleEvent(EVENT_INTRO_4, 6000);
                            break;
                        case EVENT_INTRO_4:
                            Talk(SAY_BOSS_2);
                            me->GetMotionMaster()->MovePoint(1, walkFirstSoul);
                            break;
                        case EVENT_INTRO_5:
                            Talk(SAY_BOSS_3);

                            events.ScheduleEvent(EVENT_INTRO_6, 4000);
                            break;
                        case EVENT_INTRO_6:
                            Talk(SAY_BOSS_4);
                            if (Creature* thrall = me->SummonCreature(NPC_SOUL_THRALL, soulPositions[0], TEMPSUMMON_MANUAL_DESPAWN))
                                thrall->DespawnOrUnsummon(8000);

                            me->HandleEmoteCommand(25); // ONESHOT_POINT

                            events.ScheduleEvent(EVENT_INTRO_7, 2500);
                            break;
                        case EVENT_INTRO_7:
                            me->GetMotionMaster()->MovePoint(2, walkSecondSoul);
                            break;
                        case EVENT_INTRO_8:
                            Talk(SAY_BOSS_5);
                            if (Creature* sylvanas = me->SummonCreature(NPC_SOUL_SYLVANAS, soulPositions[1], TEMPSUMMON_MANUAL_DESPAWN))
                                sylvanas->DespawnOrUnsummon(8000);

                            me->HandleEmoteCommand(25); // ONESHOT_POINT

                            events.ScheduleEvent(EVENT_INTRO_9, 2500);
                            break;
                        case EVENT_INTRO_9:
                            me->GetMotionMaster()->MovePoint(3, walkThirdSoul);
                            break;
                        case EVENT_INTRO_10:
                            Talk(SAY_BOSS_6);
                            if (Creature* kel = me->SummonCreature(NPC_SOUL_KELTHUZAD, soulPositions[2], TEMPSUMMON_MANUAL_DESPAWN))
                                kel->DespawnOrUnsummon(6000);

                            me->HandleEmoteCommand(25); // ONESHOT_POINT
                            events.ScheduleEvent(EVENT_INTRO_11, 3000);
                            break;
                        case EVENT_INTRO_11:
                            me->GetMotionMaster()->MovePoint(4, posStartFight);
                            // ######## END OF INTRO ##########
                            break;
                        case EVENT_P1_1:
                            if (Creature* thrall = ObjectAccessor::GetCreature(*me, instance->GetData64(NPC_SOUL_THRALL)))
                                thrall->AI()->DoAction(ACTION_ENTER_FIGHT);
                            break;
                        case EVENT_SOULSTEALER_BARRAGE:
                            me->CastCustomSpell(SPELL_FIRE_BARRAGE, SPELLVALUE_BASE_POINT0, urand(2000, 3000), (Unit*)NULL, TRIGGERED_FULL_MASK);

                            if (events.IsInPhase(PHASE_ONE))
                                events.ScheduleEvent(EVENT_SOULSTEALER_BARRAGE, urand(8000, 12000), 1);
                            else if (events.IsInPhase(PHASE_TWO))
                                events.ScheduleEvent(EVENT_SOULSTEALER_BARRAGE, urand(8000, 10000), 1);
                            else if (events.IsInPhase(PHASE_THREE))
                                events.ScheduleEvent(EVENT_SOULSTEALER_BARRAGE, urand(6000, 7500), 1);
                            else if (events.IsInPhase(PHASE_FOUR))
                                events.ScheduleEvent(EVENT_SOULSTEALER_BARRAGE, urand(5000, 6000), 1);
                            else if (events.IsInPhase(PHASE_FIVE))
                                events.ScheduleEvent(EVENT_SOULSTEALER_BARRAGE, urand(4000, 5000), 1);
                            break;
                        case EVENT_SOULSTEALER_MGC_DBF:
                            DoCast(SPELL_MAGIC_DEBUFF);

                            events.ScheduleEvent(EVENT_SOULSTEALER_MGC_DBF, 30000, 1);
                            break;
                        case EVENT_SOULSTEALER_FEL_FIRE:
                            if (Unit* target = me->GetVictim())
                                me->CastCustomSpell(SPELL_FEL_FIREBALL, SPELLVALUE_BASE_POINT0, urand(15000, 18000), target, TRIGGERED_FULL_MASK);

                            events.ScheduleEvent(EVENT_SOULSTEALER_FEL_FIRE, 32200, 1);
                            break;
                        case EVENT_SOULSTEALER_BARREL:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, demonWingSelector()))
                                me->CastCustomSpell(SPELL_PLAGUE_BARREL, SPELLVALUE_BASE_POINT1, urand(1500, 3000), target, TRIGGERED_FULL_MASK);

                            events.ScheduleEvent(EVENT_SOULSTEALER_BARREL, 25000, 1);
                            break;
                        case EVENT_SOULSTEALER_VOIDZONE:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                                if (Creature* voidZone = me->SummonCreature(NPC_VOID_ZONE, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ() + 0.3f, 0.0f))
                                    voidZone->AI()->IsSummonedBy(me);

                            events.ScheduleEvent(EVENT_SOULSTEALER_VOIDZONE, 15000, 1);
                            break;
                        case EVENT_SOULSTEALER_ROOM:
                            if (Creature* orb = me->SummonCreature(NPC_DEATH_ORB, spawnDeathOrb))
                                orb->AI()->IsSummonedBy(me);

                            events.ScheduleEvent(EVENT_SOULSTEALER_ROOM, 30000, 1);
                            break;
                        case EVENT_SOULSTEALER_WINGS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, demonWingSelector()))
                            {
                                Position pos = teleMiddlePos[urand(0, 2)];
                                target->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation());
                                me->AddAura(SPELL_DARK_WINGS, target);
                            }

                            events.ScheduleEvent(EVENT_SOULSTEALER_WINGS, 30000, 1);
                            break;
                        case EVENT_SOULSTEALER_BERSERK:
                            Talk(SAY_BOSS_7);
                            DoCast(SPELL_BERSERK);
                            break;
                        case EVENT_SOULSTEALER_DEATH:
                            events.CancelEventGroup(1);
                            SetCombatMovement(false);
                            canMelee = false;
                            DoCast(me, SPELL_KNEEL, true);
                            if (deathCount < 4)
                            {
                                ++deathCount;
                                DoCast(SPELL_DEATH_SHOCK);
                                events.ScheduleEvent(EVENT_SOULSTEALER_DEATH, 1500);
                            }
                            else if (Unit* victim = me->SelectVictim())
                                victim->DealDamage(victim, me, me->GetHealth());
                            break;
                        default:
                            break;
                    }
                }
                if (canMelee)
                    DoMeleeAttackIfReady();
            }

            bool CanAIAttack(Unit const* who) const override
            {
                return who->GetPositionY() > -106.0f;
            }

        private:
            InstanceScript* instance;
            SummonList summons;
            bool intro;
            float orient;
            uint32 deathCount;
            bool canMelee;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<boss_mazin_soulstealerAI>(creature);
        }
};

class npc_thrall_OLDSM : public CreatureScript
{
    public:
        npc_thrall_OLDSM() : CreatureScript("npc_thrall_OLDSM") { }

        struct npc_thrall_OLDSMAI : public ScriptedAI
        {
            npc_thrall_OLDSMAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void Reset() override
            {
                events.Reset();
                spawnedFirstElementals = false;
                spawnedSecondElementals = false;
                spawnedThirdElementals = false;
            }

            void DoAction(int32 param) override
            {
                if (param == ACTION_ENTER_FIGHT)
                    me->GetMotionMaster()->MovePoint(1, enterFightPos[0]);
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == 1)
                {
                    DoZoneInCombat();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                }
            }

            void JustDied(Unit* /*killer*/) override
            {
                summons.DespawnAll();
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (me->HealthBelowPctDamaged(80, damage) && !spawnedFirstElementals)
                {
                    spawnedFirstElementals = true;
                    for (uint8 i = 0; i < 4; ++i)
                        if (Creature* elemental = me->SummonCreature(NPC_AIR_ELEMENTAL_MAZIN, spawnElementals[i], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                            elemental->AddAura(SPELL_AOE_AVOIDANCE, elemental);
                }

                if (me->HealthBelowPctDamaged(50, damage) && !spawnedSecondElementals)
                {
                    spawnedSecondElementals = true;
                    for (uint8 i = 0; i < 4; ++i)
                        if (Creature* elemental = me->SummonCreature(NPC_EARTH_ELEMENTAL_MAZIN, spawnElementals[i], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                            elemental->AddAura(SPELL_AOE_AVOIDANCE, elemental);
                }

                if (me->HealthBelowPctDamaged(20, damage) && !spawnedThirdElementals)
                {
                    spawnedThirdElementals = true;
                    for (uint8 i = 0; i < 4; ++i)
                        if (Creature* elemental = me->SummonCreature(NPC_FIRE_ELEMENTAL_MAZIN, spawnElementals[i], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                            elemental->AddAura(SPELL_AOE_AVOIDANCE, elemental);
                }
            }

            void EnterCombat(Unit* target) override
            {
                events.ScheduleEvent(EVENT_CB_SHAKER, 7000);
                events.ScheduleEvent(EVENT_CB_CHAIN, 1000);
                events.ScheduleEvent(EVENT_CB_LBURST, 4500);
                events.ScheduleEvent(EVENT_CB_SHIELD, 100);
                events.ScheduleEvent(EVENT_CB_BLOODLUST, 30000);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_CB_SHAKER:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            DoCast(target, SPELL_GROUND_SHAKER);

                        events.ScheduleEvent(EVENT_CB_SHAKER, 26000);
                        break;
                    case EVENT_CB_CHAIN:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            DoCast(target, SPELL_CHAIN_LIGHTNING);

                        events.ScheduleEvent(EVENT_CB_CHAIN, urand(10000, 14000));
                        break;
                    case EVENT_CB_LBURST:
                        me->CastCustomSpell(SPELL_LAVA_BURST, SPELLVALUE_BASE_POINT0, urand(10000, 15000), me->GetVictim(), TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_CB_LBURST, urand(11500, 14000));
                        break;
                    case EVENT_CB_SHIELD:
                        me->CastCustomSpell(SPELL_LIGHTNING_SHIELD, SPELLVALUE_BASE_POINT0, urand(3500, 4500), me, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_CB_SHIELD, 8000);
                        break;
                    case EVENT_CB_BLOODLUST:
                        me->AddAura(SPELL_BLOODLUST, me);
                        events.ScheduleEvent(EVENT_CB_BLOODLUST, 30000);
                        break;
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
            SummonList summons;
            bool spawnedFirstElementals;
            bool spawnedSecondElementals;
            bool spawnedThirdElementals;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_thrall_OLDSMAI>(creature);
        }
};

class npc_elementals_generic : public CreatureScript
{
    public:
        npc_elementals_generic() : CreatureScript("npc_elementals_generic") { }

        struct npc_elementals_genericAI : public ScriptedAI
        {
            npc_elementals_genericAI(Creature* creature) : ScriptedAI(creature)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void IsSummonedBy(Unit* summoner) override
            {
                me->SetControlled(true, UNIT_STATE_STUNNED);
                DoCast(SPELL_EVIL_TP);
                events.ScheduleEvent(EVENT_ACTIVATE_SUMMONS, 2000);
                DoZoneInCombat();
                me->setFaction(summoner->getFaction());
            }

            void EnterCombat(Unit* target) override
            {
                switch (me->GetEntry())
                {
                case NPC_AIR_ELEMENTAL_MAZIN:
                    events.ScheduleEvent(EVENT_AIR_ELE_SPELLS, urand(4000, 8000));
                    break;
                case NPC_FIRE_ELEMENTAL_MAZIN:
                    events.ScheduleEvent(EVENT_FIRE_ELE_SPELLS, urand(4000, 8000));
                    break;
                case NPC_EARTH_ELEMENTAL_MAZIN:
                    events.ScheduleEvent(EVENT_EARTH_ELE_SPELLS, urand(4000, 8000));
                    break;
                default:
                    break;
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_ACTIVATE_SUMMONS:
                        me->SetControlled(false, UNIT_STATE_STUNNED);
                        break;
                    case EVENT_AIR_ELE_SPELLS:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            me->CastCustomSpell(SPELL_LIGHTNING, SPELLVALUE_BASE_POINT0, urand(2000, 3000), target, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_AIR_ELE_SPELLS, urand(8000, 16000));
                        break;
                    case EVENT_FIRE_ELE_SPELLS:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            me->CastCustomSpell(SPELL_FIRE_FLY, SPELLVALUE_BASE_POINT0, urand(2000, 3000), target, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_FIRE_ELE_SPELLS, urand(8000, 16000));
                        break;
                    case EVENT_EARTH_ELE_SPELLS:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            me->CastCustomSpell(SPELL_TORN_EARTH, SPELLVALUE_BASE_POINT0, urand(1000, 1500), target, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_EARTH_ELE_SPELLS, urand(8000, 16000));
                        break;
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_elementals_genericAI>(creature);
        }
};

class npc_sylvanas_OLDSM : public CreatureScript
{
    public:
        npc_sylvanas_OLDSM() : CreatureScript("npc_sylvanas_OLDSM") { }

        struct npc_sylvanas_OLDSMAI : public ScriptedAI
        {
            npc_sylvanas_OLDSMAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);

                for (uint8 i = 0; i < 9; ++i)
                    arrowTriggerGUIDs[i] = 0;
            }

            void Reset() override
            {
                events.Reset();
                attackEnabled = true;
            }

            void DoAction(int32 param) override
            {
                switch (param)
                {
                case ACTION_ENTER_FIGHT:
                    me->GetMotionMaster()->MovePoint(1, enterFightPos[1]);

                    for (uint8 i = 0; i < 9; ++i)
                        if (Creature* arrowTrigger = me->SummonCreature(NPC_ARROW_TRIGGER, arrowPos[i]))
                        {
                            arrowTrigger->setFaction(me->getFaction());
                            arrowTrigger->SetReactState(REACT_PASSIVE);
                            arrowTriggerGUIDs[i] = arrowTrigger->GetGUID();
                        }

                    events.ScheduleEvent(EVENT_SYLV_FREEZING_TRAP, 20000);
                    events.ScheduleEvent(EVENT_THROW_SPEAR, 6000);
                    events.ScheduleEvent(EVENT_SYLV_KNOCKBACK, 5000);
                    events.ScheduleEvent(EVENT_SYLV_DISARM_SILENCE, 11000);
                    events.ScheduleEvent(EVENT_SYLV_FADE, 22000);
                    break;
                default:
                    break;
                }
            }

            void AttackStart(Unit* target) override
            {
                if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC))
                    return;

                AttackStartCaster(target, RANGE_COMBAT_RANGE);
            }

            void EnterCombat(Unit* target) override
            {
                if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC))
                    return;
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
            }

            void JustDied(Unit* /*killer*/) override
            {
                summons.DespawnAll();
            }

            void EnterEvadeMode() override
            {
                summons.DespawnAll();
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (id == 1)
                {
                    DoZoneInCombat();
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_THROW_SPEAR:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                        {
                            if (Creature* arrowTrigger = ObjectAccessor::GetCreature(*me, arrowTriggerGUIDs[urand(0, 8)]))
                            {
                                arrowTrigger->SetFacingTo(arrowTrigger->GetAngle(target->GetPositionX(), target->GetPositionY()));
                                arrowTrigger->CastCustomSpell(SPELL_THROW_SPEAR, SPELLVALUE_BASE_POINT0, urand(20, 25), target, TRIGGERED_FULL_MASK);
                            }
                        }
                        events.ScheduleEvent(EVENT_THROW_SPEAR, 8000);
                        break;
                    case EVENT_SYLV_KNOCKBACK:
                        if (Unit* target = me->GetVictim())
                            if (target->IsWithinDist(me, 4.0f))
                                target->KnockbackFrom(me->GetPositionX(), me->GetPositionY() + 4.0f, 60.0f, 8.0f);

                        events.ScheduleEvent(EVENT_SYLV_KNOCKBACK, 6000);
                        break;
                    case EVENT_SYLV_FREEZING_TRAP:
                        for (uint8 i = 0; i < 2; ++i)
                        {
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                                target->CastSpell(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), SPELL_FREEZING_TRAP, true);
                        }
                        events.ScheduleEvent(EVENT_SYLV_FREEZING_TRAP, 30000);
                        break;
                    case EVENT_SYLV_DISARM_SILENCE:
                        DoCast(SPELL_DISARM_SILENCE);
                        events.ScheduleEvent(EVENT_SYLV_DISARM_SILENCE, urand(25000, 29000));
                        break;
                    case EVENT_SYLV_FADE:
                        DoResetThreat();
                        attackEnabled = false;
                        DoCast(SPELL_FADE);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            if (target->GetPositionZ() > 18.40f)
                                events.ScheduleEvent(EVENT_SYLV_FADE, 1);
                            else
                            {
                                events.ScheduleEvent(EVENT_START_ATTACKING, 6500);
                                me->NearTeleportTo(target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, false);
                            }

                        events.ScheduleEvent(EVENT_SYLV_FADE, 30000);
                        break;
                    case EVENT_START_ATTACKING:
                        attackEnabled = true;
                        break;
                    default:
                        break;
                    }
                }
                if (attackEnabled)
                    DoSpellAttackIfReady(SPELL_AUTO_SHOT);
            }

        private:
            uint64 arrowTriggerGUIDs[9];
            EventMap events;
            SummonList summons;
            bool attackEnabled;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_sylvanas_OLDSMAI>(creature);
        }
};

class npc_kel_thuzad_OLDSM : public CreatureScript
{
    public:
        npc_kel_thuzad_OLDSM() : CreatureScript("npc_kel_thuzad_OLDSM") { }

        struct npc_kel_thuzad_OLDSMAI : public ScriptedAI
        {
            npc_kel_thuzad_OLDSMAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                me->SetReactState(REACT_PASSIVE);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void DoAction(int32 param) override
            {
                if (param == ACTION_ENTER_FIGHT)
                {
                    me->GetMotionMaster()->MovePoint(1, enterFightPos[2]);
                }
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
            }

            void EnterEvadeMode() override
            {
                summons.DespawnAll();
            }

            void JustDied(Unit* /*killer*/) override
            {
                summons.DespawnAll();
            }

            void Reset() override
            {
                events.Reset();
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == 1)
                {
                    DoZoneInCombat();
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    events.ScheduleEvent(EVENT_SPAWN_RAGING_SKELETON, 8000);
                    events.ScheduleEvent(EVENT_KELTHUZAD_FRST_VOLLEY, 11000);
                }
            }

            bool DoSpellAttackIfReady(uint32 spell, Unit* target, uint32 min, uint32 max)
            {
                if (me->HasUnitState(UNIT_STATE_CASTING) || !me->isAttackReady())
                    return true;

                if (SpellInfo const* spellInfo = sSpellMgr->GetSpellInfo(spell))
                {
                    Unit* victim = me->GetVictim();
                    if (target)
                        victim = target;

                    if (me->IsWithinCombatRange(victim, spellInfo->GetMaxRange(false)))
                    {
                        me->CastCustomSpell(spell, SPELLVALUE_BASE_POINT0, urand(min, max), victim, TRIGGERED_NONE);
                        me->resetAttackTimer();
                        return true;
                    }
                }

                return false;
            }

            void AttackStart(Unit* target) override
            {
                AttackStartCaster(target, RANGE_COMBAT_RANGE);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 Id = events.ExecuteEvent())
                {
                    switch (Id)
                    {
                    case EVENT_SPAWN_RAGING_SKELETON:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                            if (Creature* skeleton = me->SummonCreature(NPC_RAGING_SKELETON, target->GetPositionX() + 3.0f, target->GetPositionY() + 3.0f, target->GetPositionZ(), 0.0f))
                                skeleton->SetInCombatWith(target, false);

                        events.ScheduleEvent(EVENT_SPAWN_RAGING_SKELETON, 35000);
                        break;
                    case EVENT_KELTHUZAD_FRST_VOLLEY:
                        DoCastAOE(SPELL_FROST_VOLLEY, true);
                        events.ScheduleEvent(EVENT_KELTHUZAD_FRST_VOLLEY, urand(15000, 30000));
                        break;
                    default:
                        break;
                    }
                }
                DoSpellAttackIfReady(SPELL_FROST_BOLT, me->GetVictim(), 8000, 13000);
            }

        private:
            EventMap events;
            SummonList summons;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_kel_thuzad_OLDSMAI>(creature);
        }
};

class npc_raging_skeleton_OLDSM : public CreatureScript
{
    public:
        npc_raging_skeleton_OLDSM() : CreatureScript("npc_raging_skeleton_OLDSM") { }

        struct npc_raging_skeleton_OLDSMAI : public ScriptedAI
        {
            npc_raging_skeleton_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void Reset() override
            {
                events.Reset();
                DoZoneInCombat();
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_SKEL_BLADE_STORM, 1);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                damage = 0;
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_SKEL_BLADE_STORM:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.0f, true))
                        {
                            DoCast(SPELL_BLADESTORM);
                            Position pos;
                            target->GetPosition(&pos);
                            me->GetMotionMaster()->MovePoint(1, pos);
                        }
                        events.ScheduleEvent(EVENT_SKEL_BLADE_STORM, 5900);
                        break;
                    default:
                        break;
                    }
                }
            }

        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_raging_skeleton_OLDSMAI>(creature);
        }
};

// Soulstealer void zone
class npc_void_zone_OLDSM : public CreatureScript
{
    public:
        npc_void_zone_OLDSM() : CreatureScript("npc_void_zone_OLDSM") { }

        struct npc_void_zone_OLDSMAI : public ScriptedAI
        {
            npc_void_zone_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);

                SetCombatMovement(false);
                creature->AddAura(SPELL_ZONE_VISUAL, creature);
                events.ScheduleEvent(1, 4000);
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case 1:
                        me->CastCustomSpell(SPELL_VOID_BLAST, SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X) * 1000, (Unit*)NULL, TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(1, 2500);
                        break;
                    default:
                        break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_void_zone_OLDSMAI>(creature);
        }
};

class npc_purple_lightning_orb_OLDSM : public CreatureScript
{
    public:
        npc_purple_lightning_orb_OLDSM() : CreatureScript("npc_purple_lightning_orb_OLDSM") { }

        struct npc_purple_lightning_orb_OLDSMAI : public ScriptedAI
        {
            npc_purple_lightning_orb_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);

                events.ScheduleEvent(1, 1000); // event move
                events.ScheduleEvent(2, 1500); // explosion event
                me->AddUnitState(UNIT_STATE_IGNORE_PATHFINDING);
                me->SetWalk(true);
                me->SetSpeed(MOVE_WALK, 0.6f);
                me->SetReactState(REACT_PASSIVE);
            }

            void MovementInform(uint32 type, uint32 id)
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == 1)
                    me->DespawnOrUnsummon(2000);
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                damage = 0;
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                while (uint32 Id = events.ExecuteEvent())
                {
                    switch (Id)
                    {
                    case 1:
                        float x, y, z;
                        me->GetClosePoint(x, y, z, me->GetObjectSize() / 3, 7.0f);
                        me->GetMotionMaster()->MovePoint(1, x, y, z);
                        break;
                    case 2:
                        DoCast(SPELL_EXPLOSION);

                        events.ScheduleEvent(2, 1000);
                        break;
                    default:
                        break;
                    }
                }
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_purple_lightning_orb_OLDSMAI>(creature);
        }
};

class npc_death_orb_OLDSM : CreatureScript
{
    public:
        npc_death_orb_OLDSM() : CreatureScript("npc_death_orb_OLDSM") { }

        struct npc_death_orb_OLDSMAI : public ScriptedAI
        {
            npc_death_orb_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                events.ScheduleEvent(1, 1000);
                events.ScheduleEvent(2, 1200);
                me->SetReactState(REACT_PASSIVE);
                me->SetCanFly(true);
                me->SetDisableGravity(true);
                me->SetWalk(true);
                me->SetSpeed(MOVE_WALK, 0.2f);
                playerGUID = 0;
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
                me->ApplySpellImmune(0, IMMUNITY_ID, 49560, true);
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (type != POINT_MOTION_TYPE)
                    return;

                if (id == 1)
                {
                    if (Unit* targetPlayer = ObjectAccessor::FindPlayer(playerGUID))
                    {
                        me->DespawnOrUnsummon(2000);
                        me->Kill(me, targetPlayer);
                    }
                }
            }

            void JustDied(Unit* /*killer*/) override
            {
                if (Unit* targetPlayer = ObjectAccessor::FindPlayer(playerGUID))
                {
                    targetPlayer->CastSpell(targetPlayer, SPELL_EVIL_TP);
                    targetPlayer->RemoveAurasDueToSpell(SPELL_ROOM_DUMMY);
                    targetPlayer->RemoveAurasDueToSpell(SPELL_ROOM_STUN);
                    targetPlayer->ToPlayer()->TeleportTo(44, spawnDeathOrb.GetPositionX(), spawnDeathOrb.GetPositionY(), spawnDeathOrb.GetPositionZ(), targetPlayer->GetOrientation());
                    me->DespawnOrUnsummon(2000);
                }
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case 1:
                        DoZoneInCombat();
                        me->GetMotionMaster()->MovePoint(1, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 10.0f);
                        break;
                    case 2:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true, -SPELL_DARK_WINGS))
                        {
                            playerGUID = target->GetGUID();
                            target->AddAura(SPELL_ROOM_DUMMY, target);
                            target->AddAura(SPELL_ROOM_STUN, target);
                            target->CastSpell(target, SPELL_EVIL_TP);
                            target->ToPlayer()->TeleportTo(44, teleportPos.GetPositionX(), teleportPos.GetPositionY(), teleportPos.GetPositionZ(), target->GetOrientation());
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        private:
            EventMap events;
            uint64 playerGUID;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_death_orb_OLDSMAI>(creature);
        }
};

class spell_demon_wings_OLDSM : public SpellScriptLoader
{
    public:
        spell_demon_wings_OLDSM() : SpellScriptLoader("spell_demon_wings_OLDSM") { }

        class spell_demon_wings_OLDSM_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_demon_wings_OLDSM_AuraScript);

            void OnRemove(AuraEffect const* /*AuraEff*/, AuraEffectHandleModes /*AuraEff*/)
            {
                if (Unit* target = GetTarget())
                {
                    float angle[3];
                    float pi = (-M_PI / 2);
                    //! find proper position angles
                    for (uint8 i = 0; i < 3; ++i, pi += (M_PI / 2))
                        angle[i] = target->GetAngle(target->GetPositionX(), target->GetPositionY()) - pi;

                    pi = (-M_PI / 2);
                    float spawnOrientation[3];
                    //! find 3 orientation values and set orbs facing to that value
                    for (auto i = 0; i < 3; ++i, pi += (M_PI / 2))
                        spawnOrientation[i] = target->GetOrientation() - pi;

                    for (uint8 i = 0; i < 3; ++i)
                    {
                        Position spawnPos;
                        target->GetNearPosition(spawnPos, 5.0f, angle[i]);
                        if (Creature* orb = target->SummonCreature(NPC_PURPLE_LIGHT_ORB, spawnPos))
                            orb->SetOrientation(spawnOrientation[i]);
                    }
                }
            }

            void Register() override
            {
                OnEffectRemove += AuraEffectRemoveFn(spell_demon_wings_OLDSM_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new spell_demon_wings_OLDSM_AuraScript();
        }
};

class spell_fireball_barrage_OLDSM : public SpellScriptLoader
{
    public:
        spell_fireball_barrage_OLDSM() : SpellScriptLoader("spell_fireball_barrage_OLDSM") { }

        class spell_fireball_barrage_OLDSM_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_fireball_barrage_OLDSM_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if(Trinity::UnitAuraCheck(true, SPELL_PLAGUE_BARREL));
                unitList.remove_if(Trinity::UnitAuraCheck(true, SPELL_ROOM_DUMMY));
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_fireball_barrage_OLDSM_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_fireball_barrage_OLDSM_SpellScript();
        }
};

void AddSC_boss_mazin_soulstealer()
{
    new boss_mazin_soulstealer();
    new npc_thrall_OLDSM();
    new npc_elementals_generic();
    new npc_sylvanas_OLDSM();
    new npc_void_zone_OLDSM();
    new npc_kel_thuzad_OLDSM();
    new npc_raging_skeleton_OLDSM();
    new npc_purple_lightning_orb_OLDSM();
    new npc_death_orb_OLDSM();

    new spell_demon_wings_OLDSM();
    new spell_fireball_barrage_OLDSM();
}