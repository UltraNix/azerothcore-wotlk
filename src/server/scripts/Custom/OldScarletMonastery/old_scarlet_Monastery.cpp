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
                        me->CastCustomSpell(SPELL_SHOCKWAVE, SPELLVALUE_BASE_POINT1, urand(12000, 18000), me->GetVictim(), TRIGGERED_FULL_MASK);

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
                            me->CastCustomSpell(SPELL_LIGHT_CONSUMPTION, SPELLVALUE_BASE_POINT0, urand(4000, 6000), target, TRIGGERED_NONE);
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
                            int32 bp0 = urand(300, 400);
                            int32 bp1 = urand(200, 300);
                            me->CastCustomSpell(target, SPELL_FLAME_STRIKE, &bp0, &bp1, NULL, true);
                        }
                        events.ScheduleEvent(EVENT_FLAME_STRIKE, urand(18000, 22000), 1);
                        break;
                    case EVENT_FEL_FIREBALL:
                        me->CastCustomSpell(SPELL_FEL_FIREBALL, SPELLVALUE_BASE_POINT0, urand(16000, 20000), me->GetVictim(), TRIGGERED_NONE);

                        events.ScheduleEvent(EVENT_FEL_FIREBALL, 8000, 1);
                        break;
                    case EVENT_EMBER_SHOWER:
                        if (emberCounter <= 10)
                        {
                            ++emberCounter;
                            me->CastCustomSpell(SPELL_EMBER_SHOWER, SPELLVALUE_BASE_POINT0, urand(1000, 1300), (Unit*)NULL, TRIGGERED_FULL_MASK);
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
                            me->CastCustomSpell(SPELL_SHADOW_RAY, SPELLVALUE_BASE_POINT1, 3000, target, TRIGGERED_NONE);

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

class npc_devaleth : public CreatureScript
{
    public:
        npc_devaleth() : CreatureScript("npc_devaleth") { }

        struct npc_devalethAI : public BossAI
        {
            npc_devalethAI(Creature* creature) : BossAI(creature, DATA_DEVALETH) { }

            void Reset() override
            {
                _Reset();
            }

            void EnterCombat(Unit* target) override
            {
                _EnterCombat();
                events.ScheduleEvent(EVENT_MORTAL_STRIKE, 6000);
                events.ScheduleEvent(EVENT_CLEAVE, 8000);
                events.ScheduleEvent(EVENT_WITHERING_ROAR, 10000);
                events.ScheduleEvent(EVENT_FEARSOME_ROAR, 20000);
                events.ScheduleEvent(EVENT_DEAFENING_ROAR, 30000);
                events.ScheduleEvent(EVENT_TERRIFYING_ROAR, 40000);
                events.ScheduleEvent(EVENT_SUMMON_EAGLES, 35000);
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
                        DoCastVictim(SPELL_MORTAL_STRIKE, true);
                        events.ScheduleEvent(EVENT_MORTAL_STRIKE, 10000);
                        break;
                    case EVENT_CLEAVE:
                        DoCastVictim(SPELL_CLEAVE, true);
                        events.ScheduleEvent(EVENT_CLEAVE, urand(7000, 12000));
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
                    default:
                        break;
                    }
                }
                DoMeleeAttackIfReady();
            }
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
                        events.ScheduleEvent(EVENT_FEATHER_BURST, urand(6000, 17500));
                        break;
                    case EVENT_RESET_THREAT:
                        DoResetThreat();
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                            me->AddThreat(target, 200000.0f);
                        events.ScheduleEvent(EVENT_RESET_THREAT, urand(3000, 9000));
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
    new npc_risen_eagle();
    new npc_risen_construct();
}