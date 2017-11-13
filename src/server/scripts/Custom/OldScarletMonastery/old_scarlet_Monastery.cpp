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

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "old_scarlet_monastery.h"
#include "Unit.h"
#include "SpellScript.h"
#include "Spell.h"

#include <utility>
#include <array>

enum Spells
{
    // Risen Dark Stalker
    SPELL_STEALTH = 1787,
    SPELL_EVISCERATE = 71933,
    SPELL_SPRINT = 2983,
    SPELL_VANISH_VISUAL = 24222,
    SPELL_VANISH = 20672,
    SPELL_KIDNEY_SHOT = 72335,
    SPELL_BLIND = 34654,
    SPELL_DEADLY_POISON = 63756,
    SPELL_SHADOWSTEP = 45273,

    // Tank
    SPELL_SHIELD_WALL = 41196,
    SPELL_INTERVENE = 41198,
    SPELL_PROTECTION = 38916,
    SPELL_THROW_SHIELD = 73076,
    SPELL_AOE_REFLECT = 20619,
    SPELL_SHOCKWAVE = 75418,
    SPELL_ICY_TORRENT = 51584,
    SPELL_DEVESTATE = 69902,

    // Caster
    SPELL_FLAME_STRIKE = 35895,
    SPELL_FEL_FIREBALL = 40633,
    SPELL_FEL_EXPLOSION = 44314,
    SPELL_EMBER_SHOWER = 61147,
    SPELL_SHADOW_RAY = 51496,

    // Healer
    SPELL_GREATER_HEAL = 71131,
    SPELL_POWER_SHIELD = 46193,
    SPELL_DISPEL_MAGIC = 16908,
    SPELL_RENEW = 66177,
    SPELL_BLAZING_LIGHT = 67291,
    SPELL_LIGHT_CONSUMPTION = 57377,

    // Devaleth
    SPELL_MORTAL_STRIKE = 67542,
    SPELL_CLEAVE = 74524,
    SPELL_DEAFENING_ROAR = 64189,
    SPELL_FEARSOME_ROAR = 59422,
    SPELL_WITHERING_ROAR = 59267,
    SPELL_TERRIFYING_ROAR = 40221,

    SPELL_FEATHER_BURST = 39068,

    SPELL_REPETENCE     = 66008,

    // Risen Construct
    SPELL_EXPLODO_ROCKETS = 4342,
    SPELL_INCENDIARY_ROCKET = 66541,
    SPELL_CHAIN_LIGHTNING = 62131,
    SPELL_EARTH_QUAKE = 32686,
    SPELL_CRUSH_ARMOR = 33661,
};

enum Events
{
    // Rogue
    EVENT_STALKER_VANISH_VISUAL = 1,
    EVENT_STALKER_VANISH = 2,
    EVENT_STALKER_KIDNEY = 3,
    EVENT_STALKER_EVISCERATE = 4,

    // Tank
    EVENT_SHIELD_WALL = 5,
    EVENT_INTERVENE = 6,
    EVENT_THROW_SHIELD = 7,
    EVENT_AOE_REFLECT = 8,
    EVENT_SHOCKWAVE = 9,
    EVENT_ICY_TORRENT = 10,
    EVENT_DEVESTATE = 11,
    EVENT_CANCLE_PROTECTION = 12,

    // Healer
    EVENT_GREATER_HEAL = 13,
    EVENT_POWER_SHIELD = 14,
    EVENT_DISPEL_MAGIC = 15,
    EVENT_RENEW = 16,
    EVENT_BLAZING_LIGHT = 17,
    EVENT_LIGHT_CONSUMPTION = 18,

    // Caster
    EVENT_FLAME_STRIKE = 19,
    EVENT_FEL_FIREBALL = 20,
    EVENT_FEL_EXPLOSION = 21,
    EVENT_EMBER_SHOWER = 22,
    EVENT_CANCEL_EMBER_SHOWER = 23,
    EVENT_SPELL_SHADOWRAY = 24,

    // Devaleth
    EVENT_MORTAL_STRIKE = 25,
    EVENT_CLEAVE = 26,
    EVENT_DEAFENING_ROAR = 27,
    EVENT_FEARSOME_ROAR = 28,
    EVENT_WITHERING_ROAR = 29,
    EVENT_TERRIFYING_ROAR = 30,
    EVENT_FEATHER_BURST = 31,
    EVENT_SUMMON_EAGLES = 32,
    EVENT_RESET_THREAT = 33,

    EVENT_EXPLODO_ROCKETS = 34,
    EVENT_INCENDIARY_ROCKET = 35,
    EVENT_CHAIN_LIGHTNING = 36,
    EVENT_EARTH_QUAKE = 37,
    EVENT_CRUSH_ARMOR = 38,
    EVENT_REPETENCE     = 39
};

class npc_dark_risen_stalker : public CreatureScript
{
    public:
        npc_dark_risen_stalker() : CreatureScript("npc_dark_risen_stalker") { }

        struct npc_dark_risen_stalkerAI : public ScriptedAI
        {
            npc_dark_risen_stalkerAI(Creature* creature) : ScriptedAI(creature)
            {
            }

            void Reset() override
            {
                DoCast(me, SPELL_STEALTH, true);
                if (!me->HasAura(SPELL_DEADLY_POISON))
                    DoCast(me, SPELL_DEADLY_POISON, true);
                me->SetReactState(REACT_AGGRESSIVE);
                _events.Reset();
            }

            void EnterCombat(Unit* victim) override
            {
                DoCastVictim(SPELL_SHADOWSTEP, true);
                _events.ScheduleEvent(EVENT_STALKER_EVISCERATE, 1000);
                DoCast(SPELL_SPRINT);
                _events.ScheduleEvent(EVENT_STALKER_KIDNEY, 4000);
                _events.ScheduleEvent(EVENT_STALKER_VANISH_VISUAL, 8000);
            }

            void MoveInLineOfSight(Unit* who) override
            {
                if (who->IsWithinDist(me, 10.0f, true))
                    ScriptedAI::MoveInLineOfSight(who);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                _events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_STALKER_EVISCERATE:
                        if (Unit* victim = me->GetVictim())
                        {
                            if (me->IsWithinMeleeRange(victim))
                            {
                                me->CastCustomSpell(SPELL_EVISCERATE, SPELLVALUE_BASE_POINT0, 25000, victim, TRIGGERED_FULL_MASK);
                                me->CastCustomSpell(SPELL_EVISCERATE, SPELLVALUE_BASE_POINT0, 25000, victim, TRIGGERED_FULL_MASK);
                            }
                            else _events.ScheduleEvent(EVENT_STALKER_EVISCERATE, 1000);
                        }
                        break;
                    case EVENT_STALKER_VANISH_VISUAL:
                        DoCast(me, SPELL_VANISH_VISUAL, true);
                        _events.ScheduleEvent(EVENT_STALKER_VANISH, 500);
                        break;
                    case EVENT_STALKER_VANISH:
                        DoCast(me, SPELL_VANISH, true);
                        _events.ScheduleEvent(EVENT_STALKER_VANISH_VISUAL, 13000);
                        DoResetThreat();
                        break;
                    case EVENT_STALKER_KIDNEY:
                        DoCastVictim(SPELL_KIDNEY_SHOT, true);
                        _events.ScheduleEvent(EVENT_STALKER_KIDNEY, 12000);
                        break;
                    default:
                        break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (damage >= 10000)
                    DoCast(attacker, SPELL_BLIND, true);
            }

        private:
            EventMap _events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_dark_risen_stalkerAI>(creature);
        }
};

class npc_trash_tank_OLDSM : public CreatureScript
{
    public:
        npc_trash_tank_OLDSM() : CreatureScript("npc_trash_tank_OLDSM") { }

        struct npc_trash_tank_OLDSMAI : public ScriptedAI
        {
            npc_trash_tank_OLDSMAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                events.Reset();
                didWall = false;
                me->SetControlled(false, UNIT_STATE_ROOT);
            }

            void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
            {
                if (me->HealthBelowPctDamaged(50, damage) && !didWall)
                {
                    didWall = true;
                    events.ScheduleEvent(EVENT_SHIELD_WALL, 1);
                }
            }

            void MoveInLineOfSight(Unit* who) override
            {
                if (who->IsWithinDist(me, 10.0f, true))
                    ScriptedAI::MoveInLineOfSight(who);
            }

            void EnterCombat(Unit* target) override
            {
                events.ScheduleEvent(EVENT_THROW_SHIELD, 6000);
                events.ScheduleEvent(EVENT_AOE_REFLECT, 3000);
                events.ScheduleEvent(EVENT_SHOCKWAVE, 20000);
                events.ScheduleEvent(EVENT_ICY_TORRENT, 1000);
                events.ScheduleEvent(EVENT_DEVESTATE, 3500);
            }

            void MovementInform(uint32 type, uint32 id) override
            {
                if (id == 10000)
                {
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    me->SetFacingTo(me->GetAngle(me->GetVictim()->GetPositionX(), me->GetVictim()->GetPositionY()));
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
                    case EVENT_SHIELD_WALL:
                        DoCast(SPELL_SHIELD_WALL);
                        break;
                    case EVENT_CANCLE_PROTECTION:
                        me->SetControlled(false, UNIT_STATE_ROOT);
                        break;
                    case EVENT_THROW_SHIELD:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            me->CastCustomSpell(SPELL_THROW_SHIELD, SPELLVALUE_BASE_POINT0, urand(5000, 6000), target, TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_THROW_SHIELD, 8000);
                        break;
                    case EVENT_AOE_REFLECT:
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_MAX_TARGETS, 2);
                        me->CastCustomSpell(SPELL_AOE_REFLECT, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_AOE_REFLECT, 30000);
                        break;
                    }
                    case EVENT_SHOCKWAVE:
                        me->CastCustomSpell(SPELL_SHOCKWAVE, SPELLVALUE_BASE_POINT1, urand(12000, 15000), me->GetVictim(), TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_SHOCKWAVE, urand(13000, 20000));
                        break;
                    case EVENT_ICY_TORRENT:
                        me->CastCustomSpell(SPELL_ICY_TORRENT, SPELLVALUE_BASE_POINT0, urand(6000, 10000), me->GetVictim(), TRIGGERED_FULL_MASK);

                        events.ScheduleEvent(EVENT_ICY_TORRENT, 15000);
                        break;
                    case EVENT_DEVESTATE:
                        DoCast(SPELL_DEVESTATE);

                        events.ScheduleEvent(EVENT_DEVESTATE, urand(5000, 10000));
                        break;
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }

        private:
            EventMap events;
            bool didWall;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_trash_tank_OLDSMAI>(creature);
        }
};

class npc_trash_healer_OLDSM : public CreatureScript
{
    public:
        npc_trash_healer_OLDSM() : CreatureScript("npc_trash_healer_OLDSM") { }

        struct npc_trash_healer_OLDSMAI : public ScriptedAI
        {
            npc_trash_healer_OLDSMAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                events.Reset();
                me->RemoveAurasDueToSpell(SPELL_PROTECTION);
            }

            void MoveInLineOfSight(Unit* who) override
            {
                if (who->IsWithinDist(me, 10.0f, true))
                    ScriptedAI::MoveInLineOfSight(who);
            }

            void EnterCombat(Unit* target) override
            {
                events.ScheduleEvent(EVENT_GREATER_HEAL, 9000);
                events.ScheduleEvent(EVENT_POWER_SHIELD, 8000);
                events.ScheduleEvent(EVENT_DISPEL_MAGIC, 4000);
                events.ScheduleEvent(EVENT_RENEW, 6000);
                events.ScheduleEvent(EVENT_BLAZING_LIGHT, 12000);
                events.ScheduleEvent(EVENT_LIGHT_CONSUMPTION, urand(5000, 15000));
            }

            void AttackStart(Unit* target) override
            {
                AttackStartCaster(target, 8.0f);
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
                    case EVENT_GREATER_HEAL:
                        if (Unit* target = DoSelectLowestHpFriendly(100.0f))
                            me->CastCustomSpell(SPELL_GREATER_HEAL, SPELLVALUE_BASE_POINT0, urand(30000, 40000), target, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_GREATER_HEAL, 6000);
                        break;
                    case EVENT_POWER_SHIELD:
                        if (Unit* target = DoSelectLowestHpFriendly(100.0f))
                            me->CastCustomSpell(SPELL_POWER_SHIELD, SPELLVALUE_BASE_POINT0, urand(40000, 50000), target, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_POWER_SHIELD, urand(11000, 13000));
                        break;
                    case EVENT_DISPEL_MAGIC:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            DoCast(target, SPELL_DISPEL_MAGIC);

                        events.ScheduleEvent(EVENT_DISPEL_MAGIC, urand(4500, 8000));
                        break;
                    case EVENT_RENEW:
                        if (Unit* target = DoSelectLowestHpFriendly(100.0f))
                            me->CastCustomSpell(SPELL_RENEW, SPELLVALUE_BASE_POINT0, urand(16000, 20000), target, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_RENEW, 15000);
                        break;
                    case EVENT_BLAZING_LIGHT:
                        me->CastCustomSpell(SPELL_BLAZING_LIGHT, SPELLVALUE_BASE_POINT0, urand(4000, 6000), (Unit*)NULL, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_BLAZING_LIGHT, 8000);
                        break;
                    case EVENT_LIGHT_CONSUMPTION:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            me->CastCustomSpell(SPELL_LIGHT_CONSUMPTION, SPELLVALUE_BASE_POINT0, urand(3000, 5000), target, TRIGGERED_NONE);
                        events.ScheduleEvent(EVENT_LIGHT_CONSUMPTION, 15000);
                        break;
                    default:
                        break;
                    }
                }
                // No melee
            }
        private:
            EventMap events;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_trash_healer_OLDSMAI>(creature);
        }
};

class npc_trash_caster_OLDSM : public CreatureScript
{
    public:
        npc_trash_caster_OLDSM() : CreatureScript("npc_trash_caster_OLDSM") { }

        struct npc_trash_caster_OLDSMAI : public ScriptedAI
        {
            npc_trash_caster_OLDSMAI(Creature* creature) : ScriptedAI(creature) { }

            void Reset() override
            {
                events.Reset();
                emberCounter = 0;
                eventsDelayed = false;
            }

            void MoveInLineOfSight(Unit* who) override
            {
                if (who->IsWithinDist(me, 10.0f, true))
                    ScriptedAI::MoveInLineOfSight(who);
            }

            void EnterCombat(Unit* target) override
            {
                events.ScheduleEvent(EVENT_FLAME_STRIKE, 3000, 1);
                events.ScheduleEvent(EVENT_FEL_FIREBALL, 1500, 1);
                events.ScheduleEvent(EVENT_EMBER_SHOWER, urand(6000, 20000), 1);
                events.ScheduleEvent(EVENT_SPELL_SHADOWRAY, 14000, 1);
            }

            void AttackStart(Unit* target) override
            {
                AttackStartCaster(target, 8.0f);
            }

            void UpdateAI(uint32 diff) override
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STATE_CASTING) || me->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                    case EVENT_FLAME_STRIKE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_BOTTOMAGGRO))
                        {
                            int32 bp0 = urand(150, 250);
                            int32 bp1 = urand(100, 150);
                            me->CastCustomSpell(target, SPELL_FLAME_STRIKE, &bp0, &bp1, NULL, true);
                        }
                        events.ScheduleEvent(EVENT_FLAME_STRIKE, urand(18000, 22000), 1);
                        break;
                    case EVENT_FEL_FIREBALL:
                        me->CastCustomSpell(SPELL_FEL_FIREBALL, SPELLVALUE_BASE_POINT0, urand(13000, 17000), me->GetVictim(), TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_FEL_FIREBALL, 8000, 1);
                        break;
                    case EVENT_EMBER_SHOWER:
                        if (emberCounter <= 10)
                        {
                            ++emberCounter;
                            me->CastCustomSpell(SPELL_EMBER_SHOWER, SPELLVALUE_BASE_POINT0, urand(500, 800), (Unit*)NULL, TRIGGERED_FULL_MASK);
                            events.ScheduleEvent(EVENT_EMBER_SHOWER, 500);
                            if (!eventsDelayed)
                            {
                                eventsDelayed = true;
                                events.DelayEvents(10500, 1);
                            }
                        }
                        else
                        {
                            events.ScheduleEvent(EVENT_EMBER_SHOWER, 25000);
                            emberCounter = 0;
                            eventsDelayed = false;
                        }
                        break;
                    case EVENT_SPELL_SHADOWRAY:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                            me->CastCustomSpell(SPELL_SHADOW_RAY, SPELLVALUE_BASE_POINT1, 2000, target, TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_SPELL_SHADOWRAY, 45000, 1);
                        break;
                    default:
                        break;
                    }
                }
                // No melee
            }
        private:
            EventMap events;
            uint32 emberCounter;
            bool eventsDelayed;
        };

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetOldScarletMonasteryAI<npc_trash_caster_OLDSMAI>(creature);
        }
};

class spell_aoe_reflect_OLDSM : public SpellScriptLoader
{
    public:
        spell_aoe_reflect_OLDSM() : SpellScriptLoader("spell_aoe_reflect_OLDSM") { }

        class spell_aoe_reflect_OLDSM_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_aoe_reflect_OLDSM_SpellScript);

            void FilterTargets(std::list<WorldObject*>& unitList)
            {
                unitList.remove_if([&](WorldObject* object)
                {
                    return object->GetTypeId() == TYPEID_PLAYER || object->ToUnit()->HasAura(GetSpellInfo()->Id);
                });
            }

            void Register() override
            {
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_aoe_reflect_OLDSM_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
            }
        };

        SpellScript* GetSpellScript() const override
        {
            return new spell_aoe_reflect_OLDSM_SpellScript();
        }
};
/*#################################
SIMON SAYS - OLD SCARLET MONASTERY
##################################*/
//
//struct SimonSays
//{
//    std::string const talk;
//    uint32 emoteId;
//};
//
//std::vector<SimonSays> const vProperSimon
//{
//    { "Let the rhythm flow through your bones, dance to win the frozen scones!", 34 },
//    { "Cry for your husbands, cry for your wives! When you lose - nobody survives!", 65 },
//    { "The world will fall beneath the blight, cower, your scum, before our might!", 28 },
//    { "For our cries the world was deaf - now greet your friend, the eternal death!", 48 },
//    { "I have given you a chance, you ungrateful brat! Why won't you thank me for that?!", 97 },
//    { "There is a great power for you to embrace! Now laugh, laugh in the death's face!", 60 },
//    { "The hate and rage make me sick... Put your lips on my cheek!", 58 },
//    { "Poison is in your mouth, fools! Spit it out or become mindless tools!", 89 },
//    { "Doesn't it tire you, all that death? Lay on the ground to catch some breath.", 61 },
//    { "You can die in any minute now... Or in this very second if you don't bow!", 17 },
//    { "When she is here to take out your breath... What do we say to her, what do we say to death?", 66 }
//};
//
//std::vector<std::string> const vScamSimon =
//{
//    "Move your body with the rhythm, dance like you never did before!",
//    "Cry for your husbands, cry for your wives! When you lose it - nobody lives!",
//    "The world will fall beneath the blight, cower, you scum, before our power!",
//    "For our cries the world was blind - now greet your friend, the eternal death!",
//    "I have given you a chance, you ungrateful scum! Why won't you thank me for that?!",
//    "There is a great power for you to get! Now laugh, laugh in the death's face!",
//    "The hate and rage make me sick... Now kiss me, on my lips!",
//    "Poison is in your mouth, idiots! Spit it out or become mindless tools!",
//    "Doesn't it tire you, all that bloodshed? Lay on the ground to catch some breath.",
//    "You can die in any minute... Or in this very second if you don't bow!",
//    "When she is here to take out your life... What do we say to her, what do we say to death?"
//};
//
//std::array<Position const, 10> playerPositions =
//{
//    {
//        { 250.539734f, -38.383926f, 31.493990f, 2.292578f },
//        { 252.019638f, -37.069260f, 31.493746f, 2.398607f },
//        { 253.439621f, -35.212593f, 31.493746f, 2.536052f },
//        { 254.467316f, -32.894466f, 31.493746f, 2.818795f },
//        { 254.818634f, -30.777582f, 31.493746f, 3.074050f },
//        { 254.523270f, -29.145168f, 31.493746f, 3.297888f },
//        { 254.097214f, -27.133762f, 31.493746f, 3.415698f },
//        { 252.861954f, -25.401718f, 31.493000f, 3.798187f },
//        { 251.194778f, -23.733984f, 31.493000f, 4.002391f },
//        { 248.934662f, -22.435266f, 31.493000f, 4.269422f }
//    }
//};
//
//std::string const failureQuote = "The death has come to strangle your necks! Beg for mercy or you might be next!"; // id 8
//std::string const eventBeginQuote = "Come here, children - don't you worry! Sit down now and hear my story!";
//
//std::string const eventStartingRhyme_1 = "The dead arrived, cold and still. I was living then in Tarren Mill.";
//std::string const eventStartingRhyme_2 = "My family dead, laying on the floor, when the prince opened the door.";
//std::string const eventStartingRhyme_3 = "He saw me crying - and afraid I was, for I have taken a terrible loss.";
//std::string const eventStartingRhyme_4 = "My heart he pierced and left for dead, everything was stained in the bloody red.";
//std::string const eventStartingRhyme_5 = "I have arisen, cold and still. Unliving in the dead Tarren Mill.";
//std::string const eventStartingRhyme_6 = "Death is the answer, so who's to blame? You will play my special game!";
//
//enum simonSaysEvents
//{
//    //! rp stuff
//    EVENT_BEGIN_EVENT               = 1,
//    EVENT_TALK_1                    = 2,
//    EVENT_TALK_2                    = 3,
//    EVENT_TALK_3                    = 4,
//    EVENT_TALK_4                    = 5,
//    EVENT_TALK_5                    = 6,
//    EVENT_TALK_6                    = 7,
//
//    //! like in simon says game, if there is prepend 'simon says' and someone properly answers
//    //! then he succeeded else if there wasnt simon says and he did answer then he lost
//    //! if he didnt say anything then he succeeded
//    //! first we have to decide if we use a talk from 'simon says' list or not
//    EVENT_ROLL                     = 8,
//    EVENT_WAIT_FOR_RESPONSE        = 9,
//    EVENT_WAIT_FOR_BEG_RESPONSOE   = 10
//};
//
//enum simonSaysMisc
//{
//    EMOTE_BEG_ID                 = 8
//};
//
//class npc_devaleth : public CreatureScript
//{
//public:
//    npc_devaleth() : CreatureScript("npc_devaleth") { }
//
//    struct npc_devalethAI : public BossAI
//    {
//        npc_devalethAI(Creature* creature) : BossAI(creature, DATA_DEVALETH) { }
//
//        void Reset() override
//        {
//            _Reset();
//            me->SetHealth(me->GetMaxHealth());
//            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
//            properVectorIndex = 0;
//            scamVectorIndex = 0;
//            simonSays = false;
//            eventStarted = false;
//            waitingForEmote = false;
//            waitingForBeg = false;
//            eventParticipants.clear();
//            playerRespondedVector.clear();
//            simonGUID = 0;
//            arthurGUID = 0;
//            me->SetRegeneratingHealth(false);
//        }
//
//        void AttackStart(Unit* /*who*/) override { }
//        void EnterCombat(Unit* /*who*/) override { }
//
//        void MoveInLineOfSight(Unit* who) override
//        {
//            if (who->GetTypeId() != TYPEID_PLAYER)
//                return;
//
//            if (!who->IsWithinDist(me, 3.0f))
//                return;
//
//            if (who->ToPlayer()->IsGameMaster())
//                return;
//
//            if (eventStarted)
//                return;
//
//            if (Map* map = me->GetMap())
//            {
//                Map::PlayerList const& players = map->GetPlayers();
//                if (players.getSize() >= 7)
//                {
//                    eventStarted = true;
//                    events.ScheduleEvent(EVENT_BEGIN_EVENT, 1000);
//                    auto j = 0;
//                    for (auto const& i : players)
//                    {
//                        if (Player* player = i.GetSource())
//                        {
//                            if (player->IsGameMaster())
//                                continue;
//
//                            eventParticipants.push_back(player->GetGUID());
//                            if (player->GetMapId() == me->GetMapId())
//                                player->NearTeleportTo(playerPositions.at(j).GetPositionX(), playerPositions.at(j).GetPositionY(),
//                                    playerPositions.at(j).GetPositionZ(), playerPositions.at(j).GetOrientation());
//
//                            ++j;
//                        }
//                    }
//                }
//            }
//        }
//
//        void ReceiveEmote(Player* player, uint32 emoteId) override
//        {
//            if (!waitingForEmote && !waitingForBeg)
//                return;
//
//            if (IsInRespondedVector(player->GetGUID()))
//                return;
//
//            if (waitingForEmote)
//            {
//                if (simonSays && emoteId == vProperSimon.at(properVectorIndex).emoteId)
//                    playerRespondedVector.push_back(player->GetGUID());
//                else if (!simonSays)
//                    playerRespondedVector.push_back(player->GetGUID());
//            }
//            else if (waitingForBeg && emoteId == EMOTE_BEG_ID)
//                playerRespondedVector.push_back(player->GetGUID());
//        }
//
//        bool IsInRespondedVector(uint64 guid)
//        {
//            return std::find(playerRespondedVector.begin(), playerRespondedVector.end(), guid) != playerRespondedVector.end();
//        }
//
//        void RemoveFromParticipantsVector(uint64 guid)
//        {
//            eventParticipants.erase(std::remove(eventParticipants.begin(), eventParticipants.end(), guid), eventParticipants.end());
//        }
//
//        void UpdateAI(uint32 diff) override
//        {
//            if (!eventStarted)
//                return;
//
//            events.Update(diff);
//
//            while (uint32 eventId = events.ExecuteEvent())
//            {
//                switch (eventId)
//                {
//                    case EVENT_BEGIN_EVENT:
//                    {
//                        _EnterCombat();
//                        DoZoneInCombat();
//                        Creature* simon = me->SummonCreature(NPC_SIMON, me->GetPosition());
//                        Creature* arthur = me->SummonCreature(NPC_ARTHUR, me->GetPosition());
//                        if (!simon || !arthur)
//                        {
//                            sLog->outError("[Old scarlet monastery]: Either simon or arthur returns null, something went wrong. Shutting down event and despawning.");
//                            _DespawnAtEvade(30, me);
//                            return;
//                        }
//                        simon->SetReactState(REACT_PASSIVE);
//                        simon->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
//                        arthur->SetReactState(REACT_PASSIVE);
//                        arthur->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PC);
//                        arthurGUID = arthur->GetGUID();
//                        simonGUID = simon->GetGUID();
//
//                        me->MonsterSay(eventBeginQuote.c_str(), 0, nullptr);
//                        events.ScheduleEvent(EVENT_TALK_1, 5000);
//                        break;
//                    }
//                    case EVENT_TALK_1:
//                    {
//                        me->MonsterSay(eventStartingRhyme_1.c_str(), 0, nullptr);
//                        events.ScheduleEvent(EVENT_TALK_2, 5000);
//                        break;
//                    }
//                    case EVENT_TALK_2:
//                    {
//                        me->MonsterSay(eventStartingRhyme_2.c_str(), 0, nullptr);
//                        events.ScheduleEvent(EVENT_TALK_3, 5000);
//                        break;
//                    }
//                    case EVENT_TALK_3:
//                    {
//                        me->MonsterSay(eventStartingRhyme_3.c_str(), 0, nullptr);
//                        events.ScheduleEvent(EVENT_TALK_4, 5000);
//                        break;
//                    }
//                    case EVENT_TALK_4:
//                    {
//                        me->MonsterSay(eventStartingRhyme_4.c_str(), 0, nullptr);
//                        events.ScheduleEvent(EVENT_TALK_5, 5000);
//                        break;
//                    }
//                    case EVENT_TALK_5:
//                    {
//                        me->MonsterSay(eventStartingRhyme_5.c_str(), 0, nullptr);
//                        events.ScheduleEvent(EVENT_TALK_6, 5000);
//                        break;
//                    }
//                    case EVENT_TALK_6:
//                    {
//                        me->MonsterSay(eventStartingRhyme_6.c_str(), 0, nullptr);
//                        events.ScheduleEvent(EVENT_ROLL, 8000);
//                        break;
//                    }
//                    case EVENT_ROLL:
//                    {
//                        simonSays = roll_chance_i(50) ? true : false;
//                        //! if simonSays returns true then we prepend "simon says" and players have to
//                        //! answer creature question with an emote
//                        if (simonSays)
//                            properVectorIndex = urand(0, vProperSimon.size() - 1);
//                        else
//                            scamVectorIndex = urand(0, vScamSimon.size() - 1);
//
//                        //! Wheter we will scam players or play properly is now decided
//                        //! also vector positions are also decided
//                        //! Do the talk and enable gathering responoses
//                        if (simonSays)
//                        {
//                            if (Creature* simon = ObjectAccessor::GetCreature(*me, simonGUID))
//                                simon->MonsterSay(vProperSimon.at(properVectorIndex).talk.c_str(), 0, nullptr);
//                        }
//                        else
//                        {
//                            if (Creature* arthur = ObjectAccessor::GetCreature(*me, arthurGUID))
//                                arthur->MonsterSay(vScamSimon.at(scamVectorIndex).c_str(), 0, nullptr);
//                        }
//
//                        waitingForEmote = true;
//                        events.ScheduleEvent(EVENT_WAIT_FOR_RESPONSE, 8000);
//                        break;
//                    }
//                    case EVENT_WAIT_FOR_RESPONSE:
//                    {
//                        //! Wait time is over, disable gathering responoses
//                        waitingForEmote = false;
//                        //! proper round
//                        if (simonSays)
//                        {
//                            for (auto const& guid : eventParticipants)
//                            {
//                                //! its proper round, player has responoded and responded correctly - he is safe
//                                if (IsInRespondedVector(guid))
//                                {
//                                    if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
//                                        player->SetStandState(UNIT_STAND_STATE_STAND);
//                                    continue;
//                                }
//
//                                //! he is not in responoded vector, could be that he responoded but with wrong emote or didnt respond at all
//                                if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
//                                    me->Kill(me, player, true);
//
//                                RemoveFromParticipantsVector(guid);
//                                waitingForBeg = true;
//                            }
//                        }
//                        else // scam round
//                        {
//                            for (auto const& guid : eventParticipants)
//                            {
//                                //! player has responded to creature during scam round
//                                //! he has failed the event
//                                if (IsInRespondedVector(guid))
//                                {
//                                    if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
//                                        me->Kill(me, player, true);
//
//                                    RemoveFromParticipantsVector(guid);
//                                    waitingForBeg = true;
//                                }
//                            }
//                        }
//
//                        //! check if anyone is left in the event, else no point going further
//                        //! we will check that multiple times
//                        if (eventParticipants.empty())
//                        {
//                            _DespawnAtEvade(30, me);
//                            return;
//                        }
//
//                        //! deal damage to boss now
//                        //! yeah we've got to iterate instead of calculating based on vector count
//                        //! because we need all the players to be eligable for loot
//                        for (auto const& guid : eventParticipants)
//                        {
//                            if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
//                                player->DealDamage(player, me, me->GetMaxHealth() * 0.01f);
//                        }
//
//                        if (waitingForBeg)
//                        {
//                            me->MonsterSay(failureQuote.c_str(), 0, nullptr);
//                            events.ScheduleEvent(EVENT_WAIT_FOR_BEG_RESPONSOE, 5000);
//                        }
//                        else
//                            events.ScheduleEvent(EVENT_ROLL, 1500);
//
//                        playerRespondedVector.clear();
//                        break;
//                    }
//                    case EVENT_WAIT_FOR_BEG_RESPONSOE:
//                    {
//                        for (auto const& guid : eventParticipants)
//                        {
//                            //! if he is in vector, he begged for his life and he is fine, skip
//                            if (IsInRespondedVector(guid))
//                            {
//                                if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
//                                    player->SetStandState(UNIT_STAND_STATE_STAND);
//                                continue;
//                            }
//
//                            //! he is not in responoded vector, could be that he responoded but with wrong emote or didnt respond at all
//                            if (Player* player = ObjectAccessor::GetPlayer(*me, guid))
//                                me->Kill(me, player, true);
//
//                            RemoveFromParticipantsVector(guid);
//                        }
//
//                        playerRespondedVector.clear();
//
//                        if (eventParticipants.empty())
//                        {
//                            _DespawnAtEvade(30, me);
//                            return;
//                        }
//
//                        waitingForBeg = false;
//                        events.ScheduleEvent(EVENT_ROLL, 1500);
//                        break;
//                    }
//                }
//            }
//        }
//
//        void JustDied(Unit* killer) override
//        {
//            events.Reset();
//            eventStarted = false;
//            instance->SetData(DATA_DEVALETH_DEATH, 1);
//            BossAI::JustDied(killer);
//        }
//
//    private:
//        std::vector<uint64> eventParticipants;
//        std::vector<uint64> playerRespondedVector;
//        uint32 properVectorIndex;
//        uint32 scamVectorIndex;
//        uint64 simonGUID;
//        uint64 arthurGUID;
//        //! false = do not prepend anything else prepend 'simon says'
//        bool simonSays;
//        bool eventStarted;
//        bool waitingForEmote;
//        bool waitingForBeg;
//    };
//
//    CreatureAI* GetAI(Creature* creature) const override
//    {
//        return GetOldScarletMonasteryAI<npc_devalethAI>(creature);
//    }
//};

class npc_devaleth : public CreatureScript
{
public:
    npc_devaleth() : CreatureScript("npc_devaleth") { }

    struct npc_devalethAI : public BossAI
    {
        npc_devalethAI(Creature* creature) : BossAI(creature, DATA_DEVALETH)
        {
            instance = me->GetInstanceScript();
        }

        void Reset() override
        {
            _Reset();
        }

        void EnterCombat(Unit* target) override
        {
            events.ScheduleEvent(EVENT_MORTAL_STRIKE, 6000);
            events.ScheduleEvent(EVENT_CLEAVE, 8000);
            events.ScheduleEvent(EVENT_WITHERING_ROAR, 10000);
            events.ScheduleEvent(EVENT_FEARSOME_ROAR, 20000);
            events.ScheduleEvent(EVENT_DEAFENING_ROAR, 30000);
            events.ScheduleEvent(EVENT_TERRIFYING_ROAR, 40000);
            events.ScheduleEvent(EVENT_SUMMON_EAGLES, 35000);
            events.ScheduleEvent(EVENT_REPETENCE, 15000);
            Talk(1);
        }

        void MoveInLineOfSight(Unit* who) override { }

        void JustDied(Unit* killer) override
        {
            instance->SetData(DATA_DEVALETH_DEATH, 1);
            BossAI::JustDied(killer);
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
                    case EVENT_MORTAL_STRIKE:
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, 150);
                        val.AddSpellMod(SPELLVALUE_BASE_POINT1, -100);
                        me->CastCustomSpell(SPELL_MORTAL_STRIKE, val, me->GetVictim(), TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_MORTAL_STRIKE, 10000);
                        break;
                    }
                    case EVENT_CLEAVE:
                        me->CastCustomSpell(SPELL_CLEAVE, SPELLVALUE_BASE_POINT0, 100, me->GetVictim(), TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_CLEAVE, 10000);
                        break;
                    case EVENT_WITHERING_ROAR:
                        me->CastCustomSpell(SPELL_WITHERING_ROAR, SPELLVALUE_BASE_POINT1, -1000, me, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_WITHERING_ROAR, 40000);
                        break;
                    case EVENT_FEARSOME_ROAR:
                    {
                        int32 bp0 = -12000, bp1 = -50;
                        me->CastCustomSpell(me->GetVictim(), SPELL_FEARSOME_ROAR, &bp0, &bp1, nullptr, true);
                        events.ScheduleEvent(EVENT_FEARSOME_ROAR, 40000);
                        break;
                    }
                    case EVENT_DEAFENING_ROAR:
                        DoCast(me, SPELL_DEAFENING_ROAR, true);
                        events.ScheduleEvent(EVENT_DEAFENING_ROAR, 40000);
                        break;
                    case EVENT_TERRIFYING_ROAR:
                        DoCast(me, SPELL_TERRIFYING_ROAR, true);
                        events.ScheduleEvent(EVENT_TERRIFYING_ROAR, 40000);
                        break;
                    case EVENT_SUMMON_EAGLES:
                    {
                        Position pos = *me;
                        Talk(0);
                        for (int i = -1; i < 2; ++i)
                        {
                            me->GetNearPosition(pos, 3.0f, -M_PI / 3.0f * i);
                            if (Creature* eagle = me->SummonCreature(NPC_RISEN_EAGLE, pos, TEMPSUMMON_TIMED_DESPAWN, 30000))
                                eagle->SetInCombatWithZone();
                        }

                        events.ScheduleEvent(EVENT_SUMMON_EAGLES, 40000);
                        break;
                    }
                    case EVENT_REPETENCE:
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, 20.f, true))
                            DoCast(target, SPELL_REPETENCE, true);

                        events.ScheduleEvent(EVENT_REPETENCE, 10000);
                        break;
                    }
                    default:
                        break;
                }
            }
            DoMeleeAttackIfReady();
        }

    private:
        InstanceScript* instance;
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetOldScarletMonasteryAI<npc_devalethAI>(creature);
    }
};

class npc_risen_eagle : public CreatureScript
{
public:
    npc_risen_eagle() : CreatureScript("npc_risen_eagle") { }

    struct npc_risen_eagleAI : public ScriptedAI
    {
        npc_risen_eagleAI(Creature* creature) : ScriptedAI(creature) { }

        void Reset() override
        {
            events.Reset();
        }

        void EnterCombat(Unit* target) override
        {
            events.ScheduleEvent(EVENT_FEATHER_BURST, urand(2000, 4000));
            events.ScheduleEvent(EVENT_RESET_THREAT, urand(4000, 5000));
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
                    case EVENT_FEATHER_BURST:
                        me->CastCustomSpell(SPELL_FEATHER_BURST, SPELLVALUE_BASE_POINT0, 300, me->GetVictim(), TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_FEATHER_BURST, urand(6000, 7500));
                        break;
                    case EVENT_RESET_THREAT:
                        DoResetThreat();
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            me->AddThreat(target, 200000.0f);
                        events.ScheduleEvent(EVENT_RESET_THREAT, urand(3000, 5000));
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
        return GetOldScarletMonasteryAI<npc_risen_eagleAI>(creature);
    }
};

class npc_risen_construct : public CreatureScript
{
    public:
        npc_risen_construct() : CreatureScript("npc_risen_construct") { }

        struct npc_risen_constructAI : public ScriptedAI
        {
            npc_risen_constructAI(Creature* creature) : ScriptedAI(creature)
            {
                //SetImmuneToPushPullEffects(true);
            }

            void Reset() override
            {
                events.Reset();
            }

            void EnterCombat(Unit* target) override
            {
                events.ScheduleEvent(EVENT_CRUSH_ARMOR, 5000);
                events.ScheduleEvent(EVENT_INCENDIARY_ROCKET, 10000);
                events.ScheduleEvent(EVENT_EARTH_QUAKE, 20000);
                events.ScheduleEvent(EVENT_EXPLODO_ROCKETS, 7000);
                events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 15000);
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
                    case EVENT_CRUSH_ARMOR:
                        DoCastVictim(SPELL_CRUSH_ARMOR);
                        events.ScheduleEvent(EVENT_CRUSH_ARMOR, 5000);
                        break;
                    case EVENT_INCENDIARY_ROCKET:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, -10.0f, true))
                            DoCast(target, SPELL_INCENDIARY_ROCKET, true);
                        events.ScheduleEvent(EVENT_INCENDIARY_ROCKET, 20000);
                        break;
                    case EVENT_EARTH_QUAKE:
                        me->CastCustomSpell(SPELL_EARTH_QUAKE, SPELLVALUE_BASE_POINT0, 3000, me, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_EARTH_QUAKE, 30000);
                        break;
                    case EVENT_CHAIN_LIGHTNING:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me, true)))
                            DoCast(target, SPELL_CHAIN_LIGHTNING, true);
                        events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 15000);
                        break;
                    case EVENT_EXPLODO_ROCKETS:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me, true)))
                            me->CastCustomSpell(SPELL_EXPLODO_ROCKETS, SPELLVALUE_BASE_POINT0, 8000, target, TRIGGERED_FULL_MASK);
                        events.ScheduleEvent(EVENT_EXPLODO_ROCKETS, 8000);
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
            return GetOldScarletMonasteryAI<npc_risen_constructAI>(creature);
        }
};

void AddSC_old_scarlet_monastery()
{
    new npc_dark_risen_stalker();
    new npc_trash_tank_OLDSM();
    new npc_trash_healer_OLDSM();
    new npc_trash_caster_OLDSM();
    new spell_aoe_reflect_OLDSM();
    new npc_devaleth();
    new npc_risen_construct();
    new npc_risen_eagle();
}