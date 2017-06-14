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
#include "ScriptedGossip.h"
#include "SpellScript.h"
#include "Spell.h"
#include "old_scarlet_monastery.h"
#include "MoveSpline.h"
#include "MoveSplineInit.h"
#include "GameObjectAI.h"

uint32 const DessembraePathSize = 4;

G3D::Vector3 const DessembraePath[DessembraePathSize] =
{
    { 432.13f, -113.14f, 32.07f },
    { 432.53f, -88.53f, 30.82f },
    { 406.94f, -86.64f, 30.82f },
    { 374.41f, -78.97f, 30.82f }
};

Position const HomePosition = { 374.0134f, -102.901f, 33.052f, 1.5708f };
Position const ChannelerSpawnPosition = { 374.246033f, -149.857071f, 29.533041f, 6.27011f };
Position const gateAndPhoenixPosition = { 374.38f, -57.88f, 30.83f, 1.47f };
Position const ArcanePhaseCenter = { 374.031555f, -66.279106f, 30.830984f, 0.002510f };
Position const ShadowSpawnPositions[6] =
{
    { 386.678864f, -144.984161f, 29.533041f, 3.419118f },
    { 386.242432f, -154.668839f, 29.533041f, 2.782943f },
    { 379.116913f, -161.566269f, 29.533041f, 1.844392f },
    { 369.234711f, -161.756683f, 29.533041f, 1.191726f },
    { 362.439392f, -154.759796f, 29.533041f, 0.531991f },
    { 361.880646f, -145.021133f, 29.533041f, 6.041561f }
};

Position protectorsAndWellsPositions[25] =
{
    { 393.35f, -47.35f, 30.82f, 3.10f },
    { 379.90f, -30.65f, 30.82f, 4.49f },
    { 368.03f, -31.41f, 30.82f, 5.02f },
    { 374.01f, -50.97f, 30.82f, 5.25f },
    { 355.36f, -48.45f, 30.82f, 4.95f },
    { 355.54f, -64.73f, 30.82f, 5.12f },
    { 368.69f, -70.52f, 30.82f, 5.92f },
    { 376.27f, -79.69f, 30.82f, 5.51f },
    { 395.15f, -70.28f, 30.82f, 1.50f },
    { 385.96f, -64.83f, 30.82f, 2.50f },
    { 376.81f, -53.63f, 30.82f, 2.11f },
    { 387.38f, -46.95f, 30.82f, 0.67f },
    { 362.97f, -45.84f, 30.82f, 3.32f },
    { 361.52f, -66.52f, 30.82f, 4.02f },
    { 392.42f, -71.79f, 30.82f, 5.93f },
    { 395.60f, -62.21f, 30.82f, 1.71f },
    { 395.26f, -48.97f, 30.82f, 1.71f },
    { 394.64f, -30.44f, 30.82f, 1.63f },
    { 379.93f, -72.00f, 30.82f, 5.01f },
    { 369.09f, -87.39f, 31.40f, 3.45f },
    { 378.64f, -85.73f, 31.12f, 1.61f },
    { 386.53f, -87.10f, 31.68f, 1.91f },
    { 353.55f, -76.29f, 30.82f, 1.55f },
    { 353.93f, -64.92f, 30.82f, 1.53f },
    { 354.55f, -48.22f, 30.82f, 1.53f },
};

Position ChannelTriggerPositions[5] =
{
    { 383.05f, -143.25f, 29.53f, 0.0f },
    { 368.33f, -140.55f, 29.53f, 0.0f },
    { 363.51f, -153.37f, 29.53f, 0.0f },
    { 376.67f, -160.68f, 29.53f, 0.0f },
    { 384.70f, -145.30f, 29.53f, 0.0f },
};

enum Says
{
    SAY_START_MOVE = 0, // I warned you to leave me alone dammit!
    SAY_START_EVENT = 1, // Be hole, be dust, be dream, be wind. Be night, be dark, be wish, be mind. Now slip, now slide, now move unseen. Above, beneath, betwixt, between. Every spell is a journey you know?
    SAY_PHYSICAL_BALL = 2, // This is essence of physical mastery.
    SAY_FROST_BALL = 3, // This one is essence of frost magic.
    SAY_FIRE_BALL = 4, // Essence of fire magic. Can you feel the burning sensation?
    SAY_ARCANE_BALL = 5, // And last but not least, essence of arcane magic.
    SAY_EVENT_END = 6, // Ahh.. im whole again!
    SAY_TELEPORT_PLAYERS = 7, // I won't play your game mortals, you will play my instead! $n $n $n || dorobic targety;p
    SAY_FAILED = 8, // Looks like your friends lost.
    SAY_ORBS = 9, // Tonitrus meum iram fulgur meum fortitudinem. Adduce meo nubes nigrae quasi noctem.
    SAY_WEREWOLF = 10, // Aoooowwwwww!
    SAY_PHEONIX = 11, // Which came first, the phoenix or the flame?
    SAY_ARCANE = 12, // I walked this land when the Dragon Aspects were but children. I have commanded armies a hundred thousand strong. I have spread the fire of my wrath across entire continents, and sat alone upon tall thrones.Do you grasp the meaning of this ?
    SAY_FROST = 13, // Nothing burns like the cold.
    SAY_KILL = 14, // Is it wrong to kill something that wants to kill you? || Many have tried to kill me. Another one falls.
    SAY_BLISTERING = 15, // Defair le coo reah melth plea, et to belth thoo coupe snow Melthere nada greth planetarie, reah melth plea. Defair le coo et to belth thoo coupe snow.
    SAY_LOOKING_TARGET = 16, // Dessembrae is looking for target..
    SAY_CHASE_TARGET = 17, // Dessembrae is chasing $N
    SAY_GAIN_SPEED = 18  // Dessembrae is gaining speed!
};

enum Spells
{
    SPELL_ARCANE_BALL = 69017,
    SPELL_FIRE_BALL = 71706,
    SPELL_FROST_BALL = 46235,
    SPELL_TRANSFORM_VISUAL = 52866,
    SPELL_HOWLING_SCREECH = 32651,
    SPELL_CHANNEL_TEST = 65113,
    SPELL_NORMAL_PHASE_SHIELD = 74621,
    SPELL_BURNING_RAGE = 38771,
    SPELL_BEAM = 46624,
    SPELL_ARCANE_EXPLOSION = 29973,
    SPELL_BLUE_SHIELD = 45848, // protector banka
    SPELL_STEAM_VISUAL = 36151,
    SPELL_KNEEL = 39656,
    SPELL_SHELL_SHIELD = 26064, // zmienic value
    SPELL_MOONFIRE_VISUAL = 36704,
    SPELL_WORGENS_CALL = 53095,
    SPELL_BEHEMOTH_CHARGE = 41272,
    SPELL_PHEONIX_VISUAL = 64724,
    SPELL_BLAST_WAVE = 17145,
    SPELL_FLAME_PATCH = 64561,
    SPELL_ARCANE_VOLLEY = 59382,
    SPELL_SURGE = 44019,
    SPELL_ARCANE_ORB = 34172,
    SPELL_PLASMA_BALL = 63689,
    SPELL_FROZEN_ORB_AURA = 72081,
    SPELL_FROST_BREATH = 37993,
    SPELL_ROCK_SHELL = 33810,
    SPELL_ICICLE = 69424,
    SPELL_FROSTBOMB = 51103,
    SPELL_FROST_BREATH_STRAFE = 49343,
    SPELL_BLISTERING_COLD = 70123,
    SPELL_MATRIX = 65210,
    SPELL_DEBUF_NATURE_TEST = 3023, // testowa aura ktora po 6 sec triggeruje liquid breath, breath ma skrypt tylko dla tej mapy ktory naklada absorb na osobe ktora trafi
    SPELL_COLUMN_OF_FROST = 72019, // zmiana fazy
    SPELL_NATURE_EXPLOSION = 64650,
    SPELL_BOMB_OBJECT = 64600,
    SPELL_SPAWN_VISUAL = 24240, // red lightning
    SPELL_SPOTLIGHT = 34126,
    SPELL_POST_ROOM_ABSORB = 36815,
};

enum DisplayIds
{
    DISPLAY_PHYSICAL_BALL = 25144,
    DISPLAY_DESSEMBRAE_ORIGINAL = 23477,
    DISPLAY_DESSEM_WEREWOLF = 26791,
    DISPLAY_DESSEM_PHEONIX = 23574,
    DISPLAY_DESSEM_ICE_VOID = 24699
};

enum Events
{
    EVENT_START_EVENT = 1,
    EVENT_PHYSICAL_BALL = 2,
    EVENT_FROST_BALL = 3,
    EVENT_FIRE_BALL = 4,
    EVENT_ARCANE_BALL = 5,
    EVENT_START_BALLS = 6,
    EVENT_STOP_BALLS = 7,
    EVENT_START_FIGHT = 8,
    EVENT_TELEPORT_PLAYERS = 9,
    EVENT_CHECK_ROOM = 10,
    EVENT_TELEPORT_BACK = 11,
    EVENT_CAST_ARCANE_EXPLOSION = 12,
    EVENT_SPAWN_PROTECTOR = 13,
    EVENT_NORMAL_PHASE = 14,
    EVENT_TRANSFORM_WEREWOLF = 15,
    EVENT_TRANSFORM_2 = 16,
    EVENT_SPAWN_DEFENSE_BUFF = 17, // werewolf
    EVENT_BEHEMOTH_CHARGE = 18,
    EVENT_WORGENS_CALL = 19,
    EVENT_TRANSFORM_PHEONIX = 20,
    EVENT_TRANSFORM_PHEONIX_2 = 21,
    EVENT_FIND_CHASE_TARGET = 22,
    EVENT_START_CHASING_PHASE = 23,
    EVENT_SPAWN_PHEONIXES = 24,
    EVENT_SPAWN_FLAME_PATCHES = 25,
    EVENT_INCREASE_SPEED = 26,
    EVENT_REDUCE_SPEED = 27,
    EVENT_SUMMON_ARCANE_ORBS = 28,
    EVENT_SUMMON_ARCANE_ORBS_EXT = 29,
    EVENT_ARCANE_EXPLOSION_P4 = 30,
    EVENT_SUMMON_FORCE_FIELD = 31,
    EVENT_CANCEL_SUMMON_ORBS = 32,
    EVENT_ARCANE_ORB_CAST = 33,
    EVENT_PLASMA_BALL = 34,
    EVENT_TRANSFORM_ICE_VOID = 35,
    EVENT_FROSTBOMB = 36,
    EVENT_COLD_STARE = 37,
    EVENT_FROST_BREATH_PLAYERS = 38,
    EVENT_ICE_BURST = 39,
    EVENT_FROST_BREATH_STRAFE = 40,
    EVENT_REMOVE_FROST_BREATH_S = 41,
    EVENT_ICICLE = 42,

    // shadow of the past
    EVENT_HOWLING_SCREECH = 1,
    EVENT_START_ATTACKING = 2,

    // arcane channeler
    EVENT_SUMMON_SHADOW = 1,
    EVENT_CHECK_CHANNEL = 2,
    EVENT_CHANGE_ROTATION = 3,
};

enum Misc
{
    DATA_BALL_MOVE = 0,
    DATA_ROOM_CLEARED = 1,
    DATA_PHASE_INFO = 2,
    GO_FORCE_FIELD = 184719,
};

enum dessembraePhases
{
    PHASE_INTRO_D = 1,
    PHASE_NORMAL = 2,
    PHASE_PHYSICAL = 3,
    PHASE_FIRE = 4,
    PHASE_ARCANE = 5,
    PHASE_FROST = 6
};

enum SpecSpells
{
    // Priest
    SPELL_SHADOWFORM = 15473, // shadow
    // Druid
    SPELL_MOONKIN_FORM = 24858, // balance
    SPELL_CAT_FORM = 768,   // feral
    // Shaman
    SPELL_ELEMENTAL_MASTERY = 16166, // elemental
    SPELL_DUAL_WIELD = 30798, // enh
    // Paladin
    SPELL_THE_ART_OF_WAR = 53488, // retri
    // Warrior
    SPELL_TITANS_GRIP = 49152, // fury
    SPELL_ENDLESS_RAGE = 29623, // arms
    // Death Knight
    SPELL_BLOOD_PRESENCE = 48266  // Unholy / Frost / Blood
};

class DamageDealerSelector
{
public:
    DamageDealerSelector() { }

    bool operator()(WorldObject* object) const
    {
        if (Unit* unit = object->ToUnit())
        {
            if (unit->GetTypeId() != TYPEID_PLAYER)
                return false;

            switch (unit->getClass())
            {
            case CLASS_MAGE:
            case CLASS_WARLOCK:
            case CLASS_ROGUE:
            case CLASS_HUNTER:
                return true;
            case CLASS_PRIEST:
                return unit->HasAura(SPELL_SHADOWFORM);
            case CLASS_DRUID:
                return unit->HasAura(SPELL_MOONKIN_FORM) || unit->HasAura(SPELL_CAT_FORM);
            case CLASS_SHAMAN:
                return unit->HasAura(SPELL_ELEMENTAL_MASTERY) || unit->HasAura(SPELL_DUAL_WIELD);
            case CLASS_PALADIN:
                return unit->HasAura(SPELL_THE_ART_OF_WAR);
            case CLASS_WARRIOR:
                return unit->HasAura(SPELL_TITANS_GRIP) || unit->HasAura(SPELL_ENDLESS_RAGE);
            case CLASS_DEATH_KNIGHT:
                return unit->HasAura(SPELL_BLOOD_PRESENCE);
            default:
                return false;
            }
        }
        return false;
    }
};

class worgensCallSelector
{
public:
    worgensCallSelector() { }

    bool operator()(Unit* target) const
    {
        return target->GetTypeId() == TYPEID_PLAYER && !target->HasAura(SPELL_WORGENS_CALL);
    }
};

class boss_dessembrae : public CreatureScript
{
    public:
        boss_dessembrae() : CreatureScript("boss_dessembrae") { }

        struct boss_dessembraeAI : public BossAI
        {
            boss_dessembraeAI(Creature* creature) : BossAI(creature, DATA_DESSEMBRAE)
            {
                instance = me->GetInstanceScript();
                //SetImmuneToPushPullEffects(true);
            }

            void Reset() override
            {
                _Reset();
                if (GameObject* gate = ObjectAccessor::GetGameObject(*me, gateGUID))
                    gate->Delete();
                if (GameObject* forceField = ObjectAccessor::GetGameObject(*me, forceFieldGUID))
                    forceField->Delete();
                events.SetPhase(PHASE_NORMAL);
                angle = 0.0f;
                summonedBalls = 0;
                me->RestoreDisplayId();
                talkDone = false;
                memset(playersInRoomGUIDs, 0, sizeof(playersInRoomGUIDs));
                //memset(playerNames, 0, sizeof(playerNames));
                channelerGUID = 0;
                //me->SetInhabitType(INHABIT_GROUND);
                me->SetReactState(REACT_AGGRESSIVE);
                me->SetObjectScale(1.0f);
                gateGUID = 0;
                forceFieldGUID = 0;
                orbAngle = 0.0f;
                plasmaCount = 0;
                me->SetMeleeDamageSchool(SPELL_SCHOOL_NORMAL);
                me->RemoveAurasDueToSpell(SPELL_FROZEN_ORB_AURA);
                me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, 200);
                me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, 300);
                me->UpdateDamagePhysical(BASE_ATTACK);
                me->setAttackTimer(BASE_ATTACK, 2000);
                me->SetSpeed(MOVE_RUN, 1.3f);
                if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAurasDueToSpell(SPELL_NORMAL_PHASE_SHIELD);
                me->RemoveAurasDueToSpell(SPELL_MATRIX);
                me->SetFullHealth();
                roomFailed = false;
                me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, false);
                me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, false);
            }

            void sGossipHello(Player* player) override
            {
                if (!talkDone)
                    player->SEND_GOSSIP_MENU(player->GetGossipTextId(me), me->GetGUID());
            }

            void sGossipSelect(Player* player, uint32 /*sender*/, uint32 action) override
            {
                if (!talkDone && action == 0 && instance->CheckRequiredBosses(DATA_DESSEMBRAE))
                {
                    talkDone = true;
                    Movement::PointsArray path(DessembraePath, DessembraePath + DessembraePathSize);

                    Movement::MoveSplineInit init(me);
                    init.MovebyPath(path, 0);
                    init.SetWalk(true);
                    init.SetSmooth();
                    init.Launch();

                    events.SetPhase(PHASE_INTRO_D);
                    player->PlayerTalkClass->ClearMenus();
                    player->CLOSE_GOSSIP_MENU();
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    Talk(SAY_START_MOVE);
                    events.ScheduleEvent(EVENT_START_EVENT, 34000);
                }
            }

            bool CanAIAttack(const Unit* target) const override
            {
                return target->GetPositionY() > -130.0f;
            }

            void SpellHitTarget(Unit* target, SpellInfo const* spellInfo) override
            {
                if (spellInfo->Id == SPELL_BLISTERING_COLD)
                    me->RemoveAurasDueToSpell(SPELL_MATRIX);
            }

            void EnterCombat(Unit* victim) override
            {
                _EnterCombat();
                DoZoneInCombat();
                DoCast(SPELL_NORMAL_PHASE_SHIELD);
                events.ScheduleEvent(EVENT_NORMAL_PHASE, 100);
                events.SetPhase(PHASE_NORMAL);
                events.ScheduleEvent(EVENT_TELEPORT_PLAYERS, 5000, 0, PHASE_NORMAL);
                events.ScheduleEvent(EVENT_CAST_ARCANE_EXPLOSION, 3000, 0, PHASE_NORMAL);
            }

            void SetData(uint32 type, uint32 data) override
            {
                if (type == DATA_ROOM_CLEARED)
                {
                    events.CancelEvent(EVENT_CHECK_ROOM);
                    events.ScheduleEvent(EVENT_TELEPORT_BACK, 3000);
                }
            }

            uint32 GetData(uint32 type) const override
            {
                if (type == DATA_PHASE_INFO)
                    return uint32(events.GetPhaseMask() & (1 << (PHASE_ARCANE - 1)));
                return 0;
            }

            void KilledUnit(Unit* victim) override
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    if (urand(0, 3))
                        Talk(SAY_KILL);
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (me->HealthBelowPctDamaged(80, damage) && events.IsInPhase(PHASE_NORMAL))
                {
                    if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    Talk(SAY_WEREWOLF);
                    me->RemoveAurasDueToSpell(SPELL_NORMAL_PHASE_SHIELD);
                    summons.DespawnEntry(NPC_PROTECTOR);
                    summons.DespawnEntry(NPC_ARCANE_CHANNELER);
                    summons.DespawnEntry(NPC_SHADOW_OF_THE_PAST);
                    events.SetPhase(PHASE_PHYSICAL);
                    events.CancelEvent(EVENT_TELEPORT_PLAYERS);
                    events.CancelEvent(EVENT_SPAWN_PROTECTOR);
                    events.CancelEvent(EVENT_CAST_ARCANE_EXPLOSION);
                    me->CastStop();
                    DoResetThreat();
                    events.ScheduleEvent(EVENT_TELEPORT_BACK, 1000);
                    events.ScheduleEvent(EVENT_TRANSFORM_WEREWOLF, 500);
                }

                if (me->HealthBelowPctDamaged(60, damage) && events.IsInPhase(PHASE_PHYSICAL))
                {
                    Talk(SAY_PHEONIX);
                    events.SetPhase(PHASE_FIRE);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, 200);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, 300);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    me->setAttackTimer(BASE_ATTACK, 2000);
                    me->SetCanDualWield(false);
                    events.CancelEvent(EVENT_SPAWN_DEFENSE_BUFF);
                    events.CancelEvent(EVENT_BEHEMOTH_CHARGE);
                    events.CancelEvent(EVENT_WORGENS_CALL);
                    me->SetReactState(REACT_PASSIVE);
                    DoStopAttack();
                    events.ScheduleEvent(EVENT_TRANSFORM_PHEONIX, 1000, 0, PHASE_FIRE);
                    events.ScheduleEvent(EVENT_SPAWN_PHEONIXES, 8000, 0, PHASE_FIRE);
                    me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, true);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, true);
                    if (GameObject* gate = me->SummonGameObject(GO_ORB_GATE, HomePosition.GetPositionX(), HomePosition.GetPositionY(), HomePosition.GetPositionZ(), HomePosition.GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, 0))
                        gateGUID = gate->GetGUID();
                }

                if (me->HealthBelowPctDamaged(40, damage) && events.IsInPhase(PHASE_FIRE))
                {
                    Talk(SAY_ARCANE);
                    summons.DespawnEntry(NPC_FLAME_TRIGGER);
                    summons.DespawnEntry(NPC_LITTLE_PHEONIX);
                    events.SetPhase(PHASE_ARCANE);
                    me->RestoreDisplayId();
                    me->SetObjectScale(1.0f);
                    me->SetMeleeDamageSchool(SPELL_SCHOOL_NORMAL);
                    me->SetSpeed(MOVE_RUN, 1.3f);
                    DoZoneInCombat();
                    AttackStart(me->SelectVictim());
                    events.ScheduleEvent(EVENT_ARCANE_EXPLOSION_P4, 20000, 0, PHASE_ARCANE);
                    events.ScheduleEvent(EVENT_ARCANE_ORB_CAST, 15000, 0, PHASE_ARCANE);
                    events.ScheduleEvent(EVENT_PLASMA_BALL, 7000, 0, PHASE_ARCANE);
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_TAUNT, false);
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_ATTACK_ME, false);
                    if (GameObject* gate = ObjectAccessor::GetGameObject(*me, gateGUID))
                    {
                        gate->Delete();
                        gateGUID = 0;
                    }
                }

                if (me->HealthBelowPctDamaged(20, damage) && events.IsInPhase(PHASE_ARCANE))
                {
                    Talk(SAY_FROST);
                    events.SetPhase(PHASE_FROST);
                    summons.DespawnEntry(NPC_ARCANE_ORB);
                    events.ScheduleEvent(EVENT_TRANSFORM_ICE_VOID, 3000);
                    me->CastStop();
                    me->SetReactState(REACT_PASSIVE);
                    me->StopMoving();
                    DoStopAttack();
                    if (GameObject* forceField = ObjectAccessor::GetGameObject(*me, forceFieldGUID))
                    {
                        forceFieldGUID = 0;
                        forceField->Delete();
                    }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim() && !events.IsInPhase(PHASE_INTRO_D))
                    return;

                //_DoAggroPulse(diff);
                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING) && !(me->GetCurrentSpell(CURRENT_GENERIC_SPELL) && (me->GetCurrentSpell(CURRENT_GENERIC_SPELL)->m_spellInfo->Id == SPELL_ARCANE_EXPLOSION)))
                    return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_START_EVENT:
                        me->SetFacingTo(1.61f);
                        Talk(SAY_START_EVENT);
                        events.ScheduleEvent(EVENT_PHYSICAL_BALL, 8000);
                        break;
                    case EVENT_PHYSICAL_BALL:
                        Talk(SAY_PHYSICAL_BALL);
                        angle = 0.0f;
                        summonedBalls = 0;
                        SummonBall(NPC_PHYSICAL_BALL);
                        events.ScheduleEvent(EVENT_FROST_BALL, 6000);
                        break;
                    case EVENT_FROST_BALL:
                        Talk(SAY_FROST_BALL);
                        SummonBall(NPC_FROST_BALL);
                        events.ScheduleEvent(EVENT_FIRE_BALL, 6000);
                        break;
                    case EVENT_FIRE_BALL:
                        Talk(SAY_FIRE_BALL);
                        SummonBall(NPC_FIRE_BALL);
                        events.ScheduleEvent(EVENT_ARCANE_BALL, 6000);
                        break;
                    case EVENT_ARCANE_BALL:
                        Talk(SAY_ARCANE_BALL);
                        SummonBall(NPC_ARCANE_BALL);
                        events.ScheduleEvent(EVENT_START_BALLS, 4000);
                        break;
                    case EVENT_START_BALLS:
                        BallsMove();
                        events.ScheduleEvent(EVENT_STOP_BALLS, 16000);
                        break;
                    case EVENT_STOP_BALLS:
                        DoCast(SPELL_TRANSFORM_VISUAL);
                        me->SetDisplayId(DISPLAY_DESSEMBRAE_ORIGINAL);
                        me->SetNativeDisplayId(DISPLAY_DESSEMBRAE_ORIGINAL);
                        me->setFaction(16);
                        me->SetHomePosition(HomePosition);
                        Talk(SAY_EVENT_END);
                        summons.DespawnAll();
                        events.ScheduleEvent(EVENT_START_FIGHT, 4000);
                        break;
                    case EVENT_NORMAL_PHASE:
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_PASSIVE);
                        DoStopAttack();
                        me->StopMoving();
                        break;
                    case EVENT_TELEPORT_PLAYERS:
                    {
                        std::list<Unit*> players;
                        SelectTargetList(players, DamageDealerSelector(), 3, SELECT_TARGET_RANDOM);
                        if (players.empty())
                            break;

                        if (Creature* channeler = me->SummonCreature(NPC_ARCANE_CHANNELER, ChannelerSpawnPosition, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 70000))
                        {
                            channelerGUID = channeler->GetGUID();
                            float angle = 0.0f;
                            uint8 i = 0;
                            for (std::list<Unit*>::iterator itr = players.begin(); itr != players.end() && i < 3; ++itr, ++i)
                            {
                                Unit* target = *itr;
                                playersInRoomGUIDs[i] = target->GetGUID();
                                float x, y, z;
                                channeler->GetNearPoint2D(x, y, 5.0f, angle);
                                z = channeler->GetPositionZ() + 0.5f;
                                target->NearTeleportTo(x, y, z, angle);
                                angle += M_PI * 2.0f / 3.0f;
                            }
                        }
                        roomFailed = false;
                        events.ScheduleEvent(EVENT_CHECK_ROOM, 60000);
                        events.ScheduleEvent(EVENT_TELEPORT_PLAYERS, 90000, 0, PHASE_NORMAL);
                        break;
                    }
                    case EVENT_TELEPORT_BACK:
                    {
                        float angle = 0.0f;
                        if (roomFailed)
                            me->AddAura(SPELL_BURNING_RAGE, me);
                        //memset(playerNames, 0, sizeof(playerNames));
                        for (int i = 0; i < 3; ++i)
                        {
                            if (Player* player = ObjectAccessor::GetPlayer(*me, playersInRoomGUIDs[i]))
                            {
                                if (!player->IsAlive())
                                    continue;
                                playersInRoomGUIDs[i] = 0;
                                float x, y, z;
                                me->GetNearPoint2D(x, y, 5.0f, angle);
                                z = me->GetPositionZ() + 0.5f;
                                player->DealDamage(player, me, me->GetMaxHealth() * 0.035f);
                                player->NearTeleportTo(x, y, z, angle);
                                angle += M_PI * 2.0f / 3.0f;
                                player->CastCustomSpell(SPELL_POST_ROOM_ABSORB, SPELLVALUE_BASE_POINT0, 500000, player, true);
                            }
                        }
                        break;
                    }
                    case EVENT_CHECK_ROOM:
                    {
                        if (Creature* channeler = ObjectAccessor::GetCreature(*me, channelerGUID))
                        {
                            if (channeler->IsAlive())
                            {
                                roomFailed = true;
                                channeler->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                channeler->RemoveAllAurasExceptType(SPELL_AURA_PERIODIC_TRIGGER_SPELL);
                                Talk(SAY_FAILED);
                                channeler->DespawnOrUnsummon(5000);
                            }
                        }
                        events.ScheduleEvent(EVENT_TELEPORT_BACK, 1000);
                        break;
                    }
                    case EVENT_CAST_ARCANE_EXPLOSION:
                    {
                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X) * 50000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT0, me->HasAura(SPELL_BURNING_RAGE) ? 3 * 500000 : 500000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT1, 0);
                        me->CastCustomSpell(SPELL_ARCANE_EXPLOSION, values, (Unit*)nullptr, TRIGGERED_NONE);
                        events.ScheduleEvent(EVENT_SPAWN_PROTECTOR, 500, 0, PHASE_NORMAL);
                        events.ScheduleEvent(EVENT_CAST_ARCANE_EXPLOSION, 13000, 0, PHASE_NORMAL);
                        break;
                    }
                    case EVENT_SPAWN_PROTECTOR:
                        shufflePositions();
                        me->SummonCreature(NPC_PROTECTOR, protectorsAndWellsPositions[1]);
                        break;
                    case EVENT_TRANSFORM_WEREWOLF:
                        me->AddAura(SPELL_KNEEL, me);
                        me->SetControlled(true, UNIT_STATE_ROOT);
                        events.ScheduleEvent(EVENT_SPAWN_DEFENSE_BUFF, 1000, 0, PHASE_PHYSICAL);
                        events.ScheduleEvent(EVENT_TRANSFORM_2, 6000);
                        break;
                    case EVENT_TRANSFORM_2:
                        me->SetDisplayId(DISPLAY_DESSEM_WEREWOLF);
                        DoCast(SPELL_TRANSFORM_VISUAL);
                        me->RemoveAurasDueToSpell(SPELL_KNEEL);
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        me->AddAura(SPELL_STEAM_VISUAL, me);
                        AttackStart(me->GetVictim());
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->SetCanDualWield(true);

                        me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, 1000);
                        me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, 1400);
                        me->SetBaseWeaponDamage(OFF_ATTACK, MINDAMAGE, 400);
                        me->SetBaseWeaponDamage(OFF_ATTACK, MAXDAMAGE, 600);
                        me->UpdateDamagePhysical(BASE_ATTACK);
                        me->UpdateDamagePhysical(OFF_ATTACK);
                        me->setAttackTimer(BASE_ATTACK, 1500);
                        me->setAttackTimer(OFF_ATTACK, 1500);

                        events.ScheduleEvent(EVENT_BEHEMOTH_CHARGE, 6000, 0, PHASE_PHYSICAL);
                        events.ScheduleEvent(EVENT_WORGENS_CALL, 10000, 0, PHASE_PHYSICAL);
                        break;
                    case EVENT_SPAWN_DEFENSE_BUFF:
                        // Spawnowanie GO, ktore po kliknieciu daje buff na redukcje dmg. Skrypt nizej
                        shufflePositions();
                        if (GameObject* energyWell = me->SummonGameObject(GO_ENERGY_WELL, protectorsAndWellsPositions[1].GetPositionX(), protectorsAndWellsPositions[1].GetPositionY(), protectorsAndWellsPositions[1].GetPositionZ(), protectorsAndWellsPositions[1].GetOrientation(), 0, 0, 0, 0, 0))
                            // Inaczej nie da sie kliknac
                            me->RemoveGameObject(energyWell, false);

                        events.ScheduleEvent(EVENT_SPAWN_DEFENSE_BUFF, 11000, 0, PHASE_PHYSICAL);
                        break;
                    case EVENT_BEHEMOTH_CHARGE:
                        // charge w gracza ktory zadaje 80% hp
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1))
                            me->CastCustomSpell(SPELL_BEHEMOTH_CHARGE, SPELLVALUE_BASE_POINT1, target->GetMaxHealth() * 0.80f, target, TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_BEHEMOTH_CHARGE, 8000, 0, PHASE_PHYSICAL);
                        break;
                    case EVENT_WORGENS_CALL:
                        // zamienia gracza w wilka, gracz moze wtedy bic tylko melee atakami
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, worgensCallSelector()))
                            target->CastSpell(target, SPELL_WORGENS_CALL);

                        events.ScheduleEvent(EVENT_WORGENS_CALL, 40000, 0, PHASE_PHYSICAL);
                        break;
                    case EVENT_TRANSFORM_PHEONIX:
                        me->AddAura(SPELL_PHEONIX_VISUAL, me);
                        events.ScheduleEvent(EVENT_TRANSFORM_PHEONIX_2, 3000, 0, PHASE_FIRE);
                        break;
                    case EVENT_TRANSFORM_PHEONIX_2:
                    {
                        me->RemoveAurasDueToSpell(SPELL_PHEONIX_VISUAL);
                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X) * 50000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT0, 1500);
                        me->CastCustomSpell(SPELL_BLAST_WAVE, values, (Unit*)NULL, TRIGGERED_NONE);
                        me->SetDisplayId(DISPLAY_DESSEM_PHEONIX);
                        me->SetObjectScale(4.0f); // display pheonixa jest bardzo maly dlatego zwiekszam, na nastepnej fazie trzeba zmniejszyc
                        me->SetMeleeDamageSchool(SPELL_SCHOOL_FIRE);
                        events.ScheduleEvent(EVENT_FIND_CHASE_TARGET, 1000, 0, PHASE_FIRE);
                        events.ScheduleEvent(EVENT_SPAWN_FLAME_PATCHES, 5000, 0, PHASE_FIRE);
                        break;
                    }
                    case EVENT_FIND_CHASE_TARGET:
                        DoResetThreat();
                        DoStopAttack();
                        me->SetReactState(REACT_PASSIVE);
                        me->SetSpeed(MOVE_RUN, 0.5f); // pamietac zeby na nastepnej fazie zmienic speed na normalny
                        me->SetControlled(true, UNIT_STATE_ROOT);
                        Talk(SAY_LOOKING_TARGET);
                        events.ScheduleEvent(EVENT_START_CHASING_PHASE, 3000, 0, PHASE_FIRE);
                        break;
                    case EVENT_START_CHASING_PHASE:
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        {
                            me->AddThreat(target, 9999999.0f);
                            Talk(SAY_CHASE_TARGET, target);
                            AttackStart(target);
                            me->SetReactState(REACT_AGGRESSIVE);
                        }
                        events.ScheduleEvent(EVENT_FIND_CHASE_TARGET, 15000, 0, PHASE_FIRE);
                        events.ScheduleEvent(EVENT_INCREASE_SPEED, 7000, 0, PHASE_FIRE);
                        break;
                    case EVENT_SPAWN_PHEONIXES:
                        me->SummonCreature(NPC_LITTLE_PHEONIX, HomePosition);

                        events.ScheduleEvent(EVENT_SPAWN_PHEONIXES, 7000, 0, PHASE_FIRE);
                        break;
                    case EVENT_SPAWN_FLAME_PATCHES:
                        if (Creature* flamePatch = me->SummonCreature(NPC_FLAME_TRIGGER, *me))
                        {
                            flamePatch->SetReactState(REACT_PASSIVE);
                            flamePatch->AddAura(SPELL_FLAME_PATCH, flamePatch);
                        }
                        events.ScheduleEvent(EVENT_SPAWN_FLAME_PATCHES, 2000, 0, PHASE_FIRE);
                        break;
                    case EVENT_INCREASE_SPEED:
                        Talk(SAY_GAIN_SPEED);
                        me->SetSpeed(MOVE_RUN, 1.00f);
                        events.ScheduleEvent(EVENT_REDUCE_SPEED, 3500, 0, PHASE_FIRE);
                        break;
                    case EVENT_REDUCE_SPEED:
                        me->SetSpeed(MOVE_RUN, 0.5f);
                        break;
                    case EVENT_ARCANE_EXPLOSION_P4:
                    {
                        me->SetReactState(REACT_PASSIVE);
                        DoStopAttack();
                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X) * 50000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT0, 500000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT1, 0);
                        me->CastCustomSpell(SPELL_ARCANE_EXPLOSION, values, (Unit*)nullptr, TRIGGERED_NONE);
                        me->SummonCreature(NPC_FORCE_FIELD_DUMMY, ArcanePhaseCenter, TEMPSUMMON_TIMED_DESPAWN, 10000);
                        events.CancelEvent(EVENT_PLASMA_BALL);
                        events.CancelEvent(EVENT_ARCANE_ORB_CAST);
                        events.ScheduleEvent(EVENT_SUMMON_FORCE_FIELD, 9000, 0, PHASE_ARCANE);
                        events.ScheduleEvent(EVENT_SUMMON_ARCANE_ORBS, 12000, 0, PHASE_ARCANE);
                        break;
                    }
                    case EVENT_SUMMON_FORCE_FIELD:
                    {
                        if (GameObject* forceField = me->SummonGameObject(GO_FORCE_FIELD, ArcanePhaseCenter.m_positionX, ArcanePhaseCenter.m_positionY, ArcanePhaseCenter.m_positionZ, 0, 0, 0, 0, 0, 0))
                            forceFieldGUID = forceField->GetGUID();
                        break;
                    }
                    case EVENT_SUMMON_ARCANE_ORBS:
                        Talk(SAY_ORBS);
                        DoStopAttack();
                        me->SetReactState(REACT_PASSIVE);
                        me->NearTeleportTo(ArcanePhaseCenter.m_positionX, ArcanePhaseCenter.m_positionY, ArcanePhaseCenter.m_positionZ, 0.0f);
                        orbAngle = 0.0f;
                        events.ScheduleEvent(EVENT_SUMMON_ARCANE_ORBS_EXT, 1000, 0, PHASE_ARCANE);
                        events.ScheduleEvent(EVENT_CANCEL_SUMMON_ORBS, 30000, 0, PHASE_ARCANE);
                        break;
                    case EVENT_SUMMON_ARCANE_ORBS_EXT:
                        SummonOrbsWave(4);
                        events.ScheduleEvent(EVENT_SUMMON_ARCANE_ORBS_EXT, 200, 0, PHASE_ARCANE);
                        break;
                    case EVENT_CANCEL_SUMMON_ORBS:
                        if (GameObject* forceField = ObjectAccessor::GetGameObject(*me, forceFieldGUID))
                        {
                            forceFieldGUID = 0;
                            forceField->Delete();
                        }
                        me->SetReactState(REACT_AGGRESSIVE);
                        DoZoneInCombat();
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                            AttackStart(target);
                        events.CancelEvent(EVENT_SUMMON_ARCANE_ORBS_EXT);
                        events.ScheduleEvent(EVENT_ARCANE_ORB_CAST, 12000, 0, PHASE_ARCANE);
                        events.ScheduleEvent(EVENT_ARCANE_EXPLOSION_P4, 60000, 0, PHASE_ARCANE);
                        events.ScheduleEvent(EVENT_PLASMA_BALL, 7000);
                        break;
                    case EVENT_ARCANE_ORB_CAST:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, -10.0f, true))
                            DoCast(target, SPELL_ARCANE_ORB, true);
                        else DoCast(me->GetVictim(), SPELL_ARCANE_ORB, true);
                        events.ScheduleEvent(EVENT_ARCANE_ORB_CAST, 8000, 0, PHASE_ARCANE);
                        break;
                    case EVENT_PLASMA_BALL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO, 1, 0.0f, true))
                            me->CastCustomSpell(SPELL_PLASMA_BALL, SPELLVALUE_BASE_POINT0, 40000, target);
                        events.ScheduleEvent(EVENT_PLASMA_BALL, ++plasmaCount >= 3 ? 12000 : 1000, 0, PHASE_ARCANE);
                        if (plasmaCount >= 3)
                            plasmaCount = 0;
                        break;
                    case EVENT_TRANSFORM_ICE_VOID:
                        me->SetDisplayId(DISPLAY_DESSEM_ICE_VOID);
                        DoCast(SPELL_TRANSFORM_VISUAL);
                        DoCast(SPELL_COLUMN_OF_FROST);
                        me->SetReactState(REACT_AGGRESSIVE);
                        AttackStart(me->GetVictim());
                        DoCast(SPELL_FROZEN_ORB_AURA);
                        events.ScheduleEvent(EVENT_FROSTBOMB, 10000, 0, PHASE_FROST);
                        events.ScheduleEvent(EVENT_COLD_STARE, 5000, 0, PHASE_FROST);
                        events.ScheduleEvent(EVENT_ICICLE, 15000, 0, PHASE_FROST);
                        events.ScheduleEvent(EVENT_FROST_BREATH_PLAYERS, 30000, 0, PHASE_FROST);
                        events.ScheduleEvent(EVENT_FROST_BREATH_STRAFE, 40000, 0, PHASE_FROST);
                        break;
                    case EVENT_FROSTBOMB:
                    {
                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_BASE_POINT0, 10000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT1, 3000);
                        values.AddSpellMod(SPELLVALUE_BASE_POINT2, -50);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, -10.0f, true))
                            me->CastCustomSpell(SPELL_FROSTBOMB, values, target, TRIGGERED_NONE);
                        else me->CastCustomSpell(SPELL_FROSTBOMB, values, me->GetVictim(), TRIGGERED_NONE);
                        events.ScheduleEvent(EVENT_FROSTBOMB, 25000, 0, PHASE_FROST);
                        break;
                    }
                    case EVENT_ICICLE:
                    {
                        UnitList targets;
                        SelectTargetList(targets, NonTankTargetSelector(me, true), 3, SELECT_TARGET_RANDOM);
                        if (!targets.empty())
                        {
                            for (std::list<Unit*>::iterator itr = targets.begin(); itr != targets.end(); ++itr)
                            {
                                Unit* target = *itr;
                                if (target)
                                    target->CastSpell(target, SPELL_ICICLE, TRIGGERED_FULL_MASK, (Item*)0, (const AuraEffect*)0, me->GetGUID());
                            }
                        }
                        events.ScheduleEvent(EVENT_ICICLE, 15000, 0, PHASE_FROST);
                        break;
                    }
                    case EVENT_FROST_BREATH_STRAFE:
                        me->SetReactState(REACT_PASSIVE);
                        DoStopAttack();
                        me->StopMoving();
                        events.DelayEvents(8000); // delay all events, only frost phase events remains in the EventMap
                        DoCast(me, SPELL_FROST_BREATH_STRAFE, true);
                        events.ScheduleEvent(EVENT_FROST_BREATH_STRAFE, 40000, 0, PHASE_FROST);
                        events.ScheduleEvent(EVENT_REMOVE_FROST_BREATH_S, 8000, 0, PHASE_FROST);
                        break;
                    case EVENT_REMOVE_FROST_BREATH_S:
                        me->RemoveAurasDueToSpell(SPELL_FROST_BREATH_STRAFE);
                        me->SetReactState(REACT_AGGRESSIVE);
                        AttackStart(me->GetVictim());
                        DoZoneInCombat();
                        break;
                    case EVENT_FROST_BREATH_PLAYERS:
                    {
                        events.DelayEvents(13500);
                        std::list<HostileReference*> const& threatList = me->getThreatManager().getThreatList();
                        for (std::list<HostileReference*>::const_iterator itr = threatList.begin(); itr != threatList.end(); ++itr)
                        {
                            if (Unit* target = (*itr)->getTarget())
                                if (target->GetTypeId() == TYPEID_PLAYER)
                                    target->AddAura(SPELL_DEBUF_NATURE_TEST, target);
                        }
                        me->CastCustomSpell(SPELL_MATRIX, SPELLVALUE_BASE_POINT1, -100, me, TRIGGERED_FULL_MASK);

                        CustomSpellValues values;
                        values.AddSpellMod(SPELLVALUE_BASE_POINT0, 100000);
                        values.AddSpellMod(SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X) * 50000);
                        me->CastCustomSpell(SPELL_BLISTERING_COLD, values, (Unit*)nullptr, TRIGGERED_NONE);
                        Talk(SAY_BLISTERING);

                        events.ScheduleEvent(EVENT_FROST_BREATH_PLAYERS, 40000);
                        break;
                    }
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }

            void SummonBall(uint32 entry)
            {

                float x = me->GetPositionX() + 3.0f * cosf(angle);
                float y = me->GetPositionY() + 3.0f * sinf(angle);
                float z = me->GetPositionZ();

                angle += M_PI / 2;
                if (Creature* ball = me->SummonCreature(entry, x, y, z))
                    ballsGUIDs[summonedBalls++] = ball->GetGUID();

            }

            void BallsMove()
            {
                for (uint8 i = 0; i < summonedBalls; ++i)
                    if (Creature* ball = ObjectAccessor::GetCreature(*me, ballsGUIDs[i]))
                    {
                        ball->AI()->SetData(DATA_BALL_MOVE, 0);
                    }
            }

            void shufflePositions()
            {
                std::random_shuffle(std::begin(protectorsAndWellsPositions), std::end(protectorsAndWellsPositions));
            }

            void SummonOrbsWave(uint32 numAdds)
            {
                float radius = 13.0f;
                float step = 2.0f * M_PI / float(numAdds);
                float z = me->GetPositionZ();
                float moveAngle = orbAngle;

                for (uint32 i = 0; i < numAdds; moveAngle += step, ++i)
                {
                    float x = me->GetPositionX() + radius * cosf(moveAngle);
                    float y = me->GetPositionY() + radius * sinf(moveAngle);
                    if (Creature* orb = me->SummonCreature(NPC_ARCANE_ORB, *me))
                    {
                        orb->SetReactState(REACT_PASSIVE);
                        orb->GetMotionMaster()->MovePoint(1, x, y, z, false);
                    }
                }
                orbAngle += 0.1412f;
                if (orbAngle >= 2 * M_PI)
                    orbAngle -= 2 * M_PI;
            }

        private:
            InstanceScript* instance;
            float angle;
            uint32 summonedBalls;
            uint64 ballsGUIDs[4];
            bool talkDone;
            uint64 playersInRoomGUIDs[3];
            uint64 channelerGUID;
            uint64 gateGUID;
            uint64 forceFieldGUID;
            float orbAngle;
            uint8 plasmaCount;
            bool roomFailed;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<boss_dessembraeAI>(creature);
        }
};

class npc_dessembraes_ball : public CreatureScript
{
    public:
        npc_dessembraes_ball() : CreatureScript("npc_dessembraes_ball") { }

        struct npc_dessembraes_ballAI : public ScriptedAI
        {
            npc_dessembraes_ballAI(Creature* creature) : ScriptedAI(creature)
            {
                //SetImmuneToPushPullEffects(true);
            }

            void Reset() override
            {
                dessebraeGUID = 0;
            }

            void UpdateAI(uint32 diff) override
            {
            }

            void IsSummonedBy(Unit* summoner) override
            {
                dessebraeGUID = summoner->GetGUID();
            }

            void SetData(uint32 type, uint32 id) override
            {
                if (type == DATA_BALL_MOVE)
                {
                    if (Creature* dessembrae = ObjectAccessor::GetCreature(*me, dessebraeGUID))
                    {
                        Movement::MoveSplineInit init(me);
                        FillSpiralPath(*dessembrae, 10.0f, dessembrae->GetPositionZ() + 10.0f, dessembrae->GetPositionZ(), init.Path(), true, 10);
                        init.SetFly();
                        init.SetSmooth();
                        init.Launch();
                    }
                }
            }

            void FillSpiralPath(Position const& centerPos, float radius, float startZ, float endZ, Movement::PointsArray& path, bool clockwise, uint32 numOfCircles)
            {
                float step = clockwise ? -M_PI / 8.0f : M_PI / 8.0f;
                float angle = centerPos.GetAngle(me->GetPositionX(), me->GetPositionY());
                float radiusStep = radius / float(16 * (numOfCircles * 1.3f));
                float zStep = fabs(startZ - endZ) / float(16 * numOfCircles);

                for (uint32 i = 0; i < numOfCircles; ++i)
                {
                    for (uint32 j = 0; j < 16; angle += step, ++j)
                    {
                        G3D::Vector3 point;
                        point.x = centerPos.GetPositionX() + radius * cosf(angle);
                        point.y = centerPos.GetPositionY() + radius * sinf(angle);
                        point.z = startZ;
                        radius -= radiusStep;
                        startZ -= zStep;
                        path.push_back(point);
                    }
                }

                for (uint32 i = 0; i < numOfCircles * 3 * 16; ++i, angle += step)
                {
                    G3D::Vector3 point;
                    point.x = centerPos.GetPositionX() + radius * cosf(angle);
                    point.y = centerPos.GetPositionY() + radius * sinf(angle);
                    point.z = startZ;
                    path.push_back(point);
                }
            }

        private:
            uint64 dessebraeGUID;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_dessembraes_ballAI>(creature);
        }
};

class npc_arcane_channeler : public CreatureScript
{
    public:
        npc_arcane_channeler() : CreatureScript("npc_arcane_channeler") { }

        struct npc_arcane_channelerAI : public ScriptedAI
        {
            npc_arcane_channelerAI(Creature* creature) : ScriptedAI(creature), summons(me)
            {
                //SetImmuneToPushPullEffects(true);
            }

            void Reset() override
            {
                count = 0;
                events.Reset();
                summons.DespawnAll();
                DoStopAttack();
                me->SetReactState(REACT_PASSIVE);
                events.ScheduleEvent(EVENT_SUMMON_SHADOW, 8000);
                events.ScheduleEvent(EVENT_CHECK_CHANNEL, 1000);
                me->ClearUnitState(UNIT_STATE_CANNOT_TURN);
            }

            void IsSummonedBy(Unit* summoner) override
            {
                if (summoner)
                    summonerGUID = summoner->GetGUID();
                if (Creature* channel = me->SummonCreature(NPC_CHANNELER_TARGET, 383.05f, -143.25f, 29.53f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
                {
                    channelTriggerGUID = channel->GetGUID();
                    me->SetFacingToObject(channel);
                }
            }

            void JustDied(Unit* killer) override
            {
                if (Creature* dessembrae = ObjectAccessor::GetCreature(*me, summonerGUID))
                    dessembrae->AI()->SetData(DATA_ROOM_CLEARED, 0);
                me->SetCorpseDelay(5);
                summons.DespawnAll();
                if (Creature* trigger = ObjectAccessor::GetCreature(*me, channelTriggerGUID))
                    trigger->DespawnOrUnsummon();
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
            }

            void SummonedCreatureDies(Creature* summon, Unit* killer) override
            {
                summons.Despawn(summon);
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_SUMMON_SHADOW:
                        me->SummonCreature(NPC_SHADOW_OF_THE_PAST, ShadowSpawnPositions[urand(0, 5)], TEMPSUMMON_TIMED_DESPAWN, 30000);
                        events.ScheduleEvent(EVENT_SUMMON_SHADOW, 12000);
                        break;
                    case EVENT_CHECK_CHANNEL:
                        if (Creature* channeler = ObjectAccessor::GetCreature(*me, channelTriggerGUID))
                        {
                            me->SetFacingTo(me->GetAngle(channeler->GetPositionX(), channeler->GetPositionY()));
                            if (++count >= 10)
                                if (!me->HasUnitState(UNIT_STATE_CASTING))
                                    DoCast(channeler, SPELL_CHANNEL_TEST);
                        }
                        events.ScheduleEvent(EVENT_CHECK_CHANNEL, 200);
                        break;
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            uint32 count;
            EventMap events;
            uint64 summonerGUID;
            SummonList summons;
            uint64 channelTriggerGUID;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_arcane_channelerAI>(creature);
        }
};

class npc_channel_trigger_OLDSM : public CreatureScript
{
    public:
        npc_channel_trigger_OLDSM() : CreatureScript("npc_channel_trigger_OLDSM") { }

        struct npc_channel_trigger_OLDSMAI : public ScriptedAI
        {
            npc_channel_trigger_OLDSMAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                me->SetReactState(REACT_PASSIVE);
            }

            void IsSummonedBy(Unit* summoner) override
            {
                timer = 2000;
            }

            void EnterEvadeMode() override { }

            void MovePath(bool clockwise)
            {
                Movement::MoveSplineInit init(me);
                FillCirclePath(ChannelerSpawnPosition, 6.0f, ChannelerSpawnPosition.m_positionZ, init.Path(), clockwise);
                init.SetWalk(false);
                init.SetSmooth();
                init.SetCyclic();
                init.Launch();
            }

            void FillCirclePath(Position const& centerPos, float radius, float z, Movement::PointsArray& path, bool clockwise)
            {
                float step = clockwise ? -M_PI / 4.0f : M_PI / 4.0f;
                float angle = centerPos.GetAngle(me->GetPositionX(), me->GetPositionY());

                for (uint8 i = 0; i < 8; angle += step, ++i)
                {
                    G3D::Vector3 point;
                    point.x = centerPos.GetPositionX() + radius * cosf(angle);
                    point.y = centerPos.GetPositionY() + radius * sinf(angle);
                    point.z = z;
                    path.push_back(point);
                }
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                damage = 0;
            }

            void UpdateAI(uint32 diff) override
            {
                if (timer >= diff)
                    timer -= diff;
                else
                {
                    me->StopMoving();
                    me->GetMotionMaster()->Clear();
                    MovePath(urand(0, 1));
                    timer = urand(2000, 5000);
                }
            }

        private:
            uint32 timer;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_channel_trigger_OLDSMAI>(creature);
        }
};

class npc_protector_OLDSM : public CreatureScript
{
    public:
        npc_protector_OLDSM() : CreatureScript("npc_protector_OLDSM") { }

        struct npc_protector_OLDSMAI : public ScriptedAI
        {
            npc_protector_OLDSMAI(Creature* creature) : ScriptedAI(creature), summons(me) { }

            void Reset() override
            {
                events.Reset();
                me->setFaction(35);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                playerList.clear();
                didProtect = false;
                countHellos = 0;
                DoCast(SPELL_SPOTLIGHT);
                me->SetObjectScale(0.3f);
                events.ScheduleEvent(1/*EVENT_DESPAWN_SELF_AND_ADDS*/, 12000);
                SpawnBombs(5, 10);
            }

            void JustSummoned(Creature* summon) override
            {
                summons.Summon(summon);
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                if (events.ExecuteEvent() == 1/*EVENT_DESPAWN_SELF_AND_ADDS*/)
                {
                    summons.DespawnAll();
                    me->DespawnOrUnsummon();
                }
            }

            void SpawnBombs(uint32 firstBatch, uint32 secondBatch)
            {
                Position fromPosition;
                me->GetPosition(&fromPosition);
                float z = me->GetPositionZ();

                float radius = 8.0f;
                float angle = 0.0f;
                float calcAngle = 2 * M_PI / firstBatch;

                float radius2 = 14.0f;
                float angle2 = M_PI / 1.5f;
                float calcAngle2 = 2 * M_PI / secondBatch;

                // inner ring
                for (uint8 i = 0; i < firstBatch; angle += calcAngle, ++i)
                {
                    float x = fromPosition.GetPositionX() + radius * cosf(angle);
                    float y = fromPosition.GetPositionY() + radius * sinf(angle);
                    me->SummonCreature(NPC_PROTECTOR_BOMBS, x, y, z);
                }

                // outter ring
                for (uint8 j = 0; j < secondBatch; angle2 += calcAngle2, ++j)
                {
                    float x = fromPosition.GetPositionX() + radius2 * cosf(angle2);
                    float y = fromPosition.GetPositionY() + radius2 * sinf(angle2);
                    me->SummonCreature(NPC_PROTECTOR_BOMBS, x, y, z);
                }
            }

            void sGossipHello(Player* player) override
            {
                if (!didProtect)
                {
                    if (playerList.find(player->GetGUID()) == playerList.end())
                    {
                        playerList.insert(player->GetGUID());
                        ++countHellos;
                        player->PlayerTalkClass->ClearMenus();
                        if (countHellos >= 5)
                        {
                            didProtect = true;
                            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                            CustomSpellValues values;
                            values.AddSpellMod(SPELLVALUE_BASE_POINT0, -98);
                            values.AddSpellMod(SPELLVALUE_BASE_POINT1, 0);
                            me->CastCustomSpell(SPELL_BLUE_SHIELD, values, (Unit*)NULL, TRIGGERED_FULL_MASK);
                        }
                    }
                    player->CLOSE_GOSSIP_MENU();
                }
            }
        private:
            bool didProtect;
            uint32 countHellos;
            std::set<uint64> playerList;
            SummonList summons;
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_protector_OLDSMAI>(creature);
        }
};

class npc_protector_bomb_OLDSM : public CreatureScript
{
    public:
        npc_protector_bomb_OLDSM() : CreatureScript("npc_protector_bomb_OLDSM") { }

        struct npc_protector_bomb_OLDSMAI : public ScriptedAI
        {
            npc_protector_bomb_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                SetCombatMovement(false);

                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
                explosionTimer = 10000;
                DoCast(SPELL_BOMB_OBJECT);
                exploded = false;
            }

            void AttackStart(Unit* target) override { }
            void EnterCombat(Unit* target) override { }
            void EnterEvadeMode() override { }

            void DamageTaken(Unit* who, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                damage = 0;
            }

            void MoveInLineOfSight(Unit* who) override
            {
                if (!exploded && me->IsWithinDistInMap(who, 0.6f) && who->ToPlayer())
                {
                    if (GameObject* bomb = me->GetGameObject(SPELL_BOMB_OBJECT))
                    {
                        exploded = true;
                        me->CastCustomSpell(SPELL_NATURE_EXPLOSION, SPELLVALUE_RADIUS_MOD, 5000, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                        bomb->SetGoState(GO_STATE_ACTIVE);
                        //bomb->RemoveFromOwner();
                        me->DespawnOrUnsummon(1500);
                    }
                }
            }

            void UpdateAI(uint32 diff) override
            {
                if (explosionTimer <= diff && !exploded)
                {
                    if (GameObject* bomb = me->GetGameObject(SPELL_BOMB_OBJECT))
                    {
                        exploded = true;
                        me->CastCustomSpell(SPELL_NATURE_EXPLOSION, SPELLVALUE_RADIUS_MOD, 3000, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                        bomb->SetGoState(GO_STATE_ACTIVE);
                        //bomb->RemoveFromOwner();
                        me->DespawnOrUnsummon(1500);
                    }
                }
                else explosionTimer -= diff;
            }
        private:
            uint32 explosionTimer;
            bool exploded;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_protector_bomb_OLDSMAI>(creature);
        }
};

class npc_shadow_of_the_past : public CreatureScript
{
    public:
        npc_shadow_of_the_past() : CreatureScript("npc_shadow_of_the_past") { }

        struct npc_shadow_of_the_pastAI : public ScriptedAI
        {
            npc_shadow_of_the_pastAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                events.Reset();
            }

            void IsSummonedBy(Unit* summoner) override
            {
                me->SetInCombatWithZone();
                me->SetControlled(true, UNIT_STATE_STUNNED);
                events.ScheduleEvent(EVENT_START_ATTACKING, 1500);
            }

            void EnterCombat(Unit* target) override
            {
                events.ScheduleEvent(EVENT_HOWLING_SCREECH, 3000);
                CreatureAI::EnterCombat(target);
            }

            bool CanAIAttack(const Unit* target) const override
            {
                return target->GetPositionY() < -130.0f;
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
                    case EVENT_START_ATTACKING:
                        me->SetControlled(false, UNIT_STATE_STUNNED);
                        break;
                    case EVENT_HOWLING_SCREECH:
                        me->CastCustomSpell(SPELL_HOWLING_SCREECH, SPELLVALUE_RADIUS_MOD, 5000, me, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_HOWLING_SCREECH, 5000);
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
            return GetOldScarletMonasteryAI<npc_shadow_of_the_pastAI>(creature);
        }
};

class npc_little_phoenix_OLDSM : public CreatureScript
{
    public:
        npc_little_phoenix_OLDSM() : CreatureScript("npc_little_phoenix_OLDSM") { }

        struct npc_little_phoenix_OLDSMAI : public ScriptedAI
        {
            npc_little_phoenix_OLDSMAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                events.ScheduleEvent(/*EVENT_FOLLOW_DESSEMBRAE*/1, 2000);
                me->SetSpeed(MOVE_RUN, 0.80f);
                DoStopAttack();
                exploded = false;
            }

            void IsSummonedBy(Unit* summoner) override
            {
                if (summoner)
                    dessembraeGUID = summoner->GetGUID();
            }

            void AttackStart(Unit* target) override { }
            void EnterCombat(Unit* target) override { }

            void MoveInLineOfSight(Unit* who) override
            {
                if (who->GetTypeId() == TYPEID_UNIT && who->GetEntry() == NPC_DESSEMBRAE && who->IsWithinDistInMap(me, 2.5f, false) && !exploded)
                {
                    CustomSpellValues values;
                    values.AddSpellMod(SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X) * 50000);
                    values.AddSpellMod(SPELLVALUE_BASE_POINT0, 1700);
                    me->CastCustomSpell(SPELL_BLAST_WAVE, values, (Unit*)NULL, TRIGGERED_FULL_MASK);
                    exploded = true;
                    me->SetReactState(REACT_PASSIVE);
                    me->GetMotionMaster()->Clear();
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    events.CancelEvent(1); // follow
                    me->DespawnOrUnsummon(1500);
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
                        if (Creature* dessem = ObjectAccessor::GetCreature(*me, dessembraeGUID))
                        {
                            me->GetMotionMaster()->MoveFollow(dessem, 0.0f, 0.0f);
                            events.ScheduleEvent(/*EVENT_FOLLOW_DESSEMBRAE*/1, 2000);
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        private:
            EventMap events;
            uint64 dessembraeGUID;
            bool exploded;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_little_phoenix_OLDSMAI>(creature);
        }
};

class npc_arcane_orb_OLDSM : public CreatureScript
{
    public:
        npc_arcane_orb_OLDSM() : CreatureScript("npc_arcane_orb_OLDSM") { }

        struct npc_arcane_orb_OLDSMAI : public ScriptedAI
        {
            npc_arcane_orb_OLDSMAI(Creature* creature) : ScriptedAI(creature)
            {
                invert = false;
                hitCounter = 0;
            }

            void SpellHitTarget(Unit* victim, const SpellInfo* spellInfo) override
            {
                if (victim->GetTypeId() == TYPEID_PLAYER)
                    if (spellInfo && spellInfo->Id == SPELL_SURGE)
                    {
                        me->CastCustomSpell(SPELL_ARCANE_VOLLEY, SPELLVALUE_BASE_POINT0, 15000, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                        hitCounter = 10;
                    }
            }

            void MovementInform(uint32 type, uint32 point) override
            {
                if (type == POINT_MOTION_TYPE && point == 1)
                    me->DespawnOrUnsummon();
            }

            void UpdateAI(uint32 diff) override
            {
                if (invert = !invert)
                {
                    if (hitCounter > 0)
                        --hitCounter;
                    else me->CastCustomSpell(SPELL_SURGE, SPELLVALUE_RADIUS_MOD, me->GetFloatValue(OBJECT_FIELD_SCALE_X)/*7*/, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                }
            }
        private:
            bool invert;
            int8 hitCounter;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_arcane_orb_OLDSMAI>(creature);
        }
};

class go_energy_well : public GameObjectScript
{
    public:
        go_energy_well() : GameObjectScript("go_energy_well") { }

        bool OnGossipHello(Player* player, GameObject *go)
        {
            if (player)
            {
                player->CastCustomSpell(SPELL_SHELL_SHIELD, SPELLVALUE_BASE_POINT0, -80, player, TRIGGERED_FULL_MASK);
                go->CastSpell(player, SPELL_MOONFIRE_VISUAL/*, true*/);
                go->Delete();
            }
            return false;
        }

        struct go_energy_wellAI : public GameObjectAI
        {
            go_energy_wellAI(GameObject* go) : GameObjectAI(go) { }

            void Reset() override
            {
                events.ScheduleEvent(1, 12000);
            }

            void UpdateAI(uint32 diff) override
            {
                events.Update(diff);

                if (events.ExecuteEvent() == 1)
                    go->Delete();
            }
        private:
            EventMap events;
        };

        GameObjectAI* GetAI(GameObject* go) const override
        {
            return GetOldScarletMonasteryAI<go_energy_wellAI>(go);
        }
};

class RoomPositionCheck
{
    public:
        bool operator()(WorldObject* object) const
        {
            if (object->GetPositionY() > -130.0f)
                return false;

            return true;
        }
};

class ForceFieldCheck
{
    public:
        ForceFieldCheck(Unit* caster) { }

        bool operator()(WorldObject* object) const
        {
            if (object->IsWithinDist2d(&ArcanePhaseCenter, 14.0f))
                return true;

            return false;
        }
};

class spell_arcane_explosion_OLDSM : public SpellScriptLoader
{
    public:
        spell_arcane_explosion_OLDSM() : SpellScriptLoader("spell_arcane_explosion_OLDSM") { }

        class spell_arcane_explosion_OLDSM_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_arcane_explosion_OLDSM_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                if (!GetCaster() || GetCaster()->GetMapId() != 44)
                    return;
                unitList.remove_if(RoomPositionCheck());
                if (GetCaster()->GetTypeId() == TYPEID_UNIT && !GetCaster()->IsWithinLOS(ArcanePhaseCenter.m_positionX, ArcanePhaseCenter.m_positionY, ArcanePhaseCenter.m_positionZ))
                    if (GetCaster()->ToCreature()->AI()->GetData(DATA_PHASE_INFO)) // PHASE_ARCANE
                        unitList.remove_if(ForceFieldCheck(GetCaster()));
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_arcane_explosion_OLDSM_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_arcane_explosion_OLDSM_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_arcane_explosion_OLDSM_SpellScript();
        }
};

class spell_arcane_orb_damage : public SpellScriptLoader
{
    public:
        spell_arcane_orb_damage() : SpellScriptLoader("spell_arcane_orb_damage") { }

        class spell_arcane_orb_damage_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_arcane_orb_damage_SpellScript);

            void CalculateDamage(SpellEffIndex effIndex)
            {
                if (GetHitUnit() && GetHitUnit()->GetMapId() == 44)
                    SetHitDamage(25000);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_arcane_orb_damage_SpellScript::CalculateDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_arcane_orb_damage_SpellScript();
        }
};

// aura ktora triggeruje frost breath ktory nalozy absorb
class aura_nature_debuff_test_OLDSM : public SpellScriptLoader
{
    public:
        aura_nature_debuff_test_OLDSM() : SpellScriptLoader("aura_nature_debuff_test_OLDSM") { }

        class aura_nature_debuff_test_OLDSM_AuraScript : public AuraScript
        {
            PrepareAuraScript(aura_nature_debuff_test_OLDSM_AuraScript);

            void OnRemove(AuraEffect const* /*AuraEff*/, AuraEffectHandleModes /*AuraEff*/)
            {
                if (Unit* target = GetTarget())
                    target->CastCustomSpell(SPELL_FROST_BREATH, SPELLVALUE_MAX_TARGETS, 1, (Unit*)nullptr, TRIGGERED_FULL_MASK);
            }

            void Register() override
            {
                OnEffectRemove += AuraEffectRemoveFn(aura_nature_debuff_test_OLDSM_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_RESISTANCE, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const override
        {
            return new aura_nature_debuff_test_OLDSM_AuraScript();
        }
};

class spell_frost_breath_OLDSM : public SpellScriptLoader
{
    public:
        spell_frost_breath_OLDSM() : SpellScriptLoader("spell_frost_breath_OLDSM") { }

        class spell_frost_breath_OLDSM_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_frost_breath_OLDSM_SpellScript);

            void OnEffectHit(SpellEffIndex effIndex)
            {
                if (Unit* target = GetHitUnit())
                    if (target->GetMapId() == 44)
                        target->CastCustomSpell(SPELL_ROCK_SHELL, SPELLVALUE_BASE_POINT0, 125000, target, TRIGGERED_FULL_MASK);
            }

            void Register() override
            {
                OnEffectHitTarget += SpellEffectFn(spell_frost_breath_OLDSM_SpellScript::OnEffectHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_frost_breath_OLDSM_SpellScript();
        }
};

void AddSC_boss_dessembrae()
{
    new boss_dessembrae();
    new npc_dessembraes_ball();
    new npc_arcane_channeler();
    new npc_shadow_of_the_past();
    new npc_channel_trigger_OLDSM();
    new npc_protector_OLDSM();
    new npc_little_phoenix_OLDSM();
    new npc_arcane_orb_OLDSM();
    new npc_protector_bomb_OLDSM();

    new go_energy_well();

    new spell_arcane_explosion_OLDSM();
    new spell_arcane_orb_damage();
    new aura_nature_debuff_test_OLDSM();
    new spell_frost_breath_OLDSM();
}
