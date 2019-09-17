/*
 * Copyright (C) 2008-2018 Hellground <http://hellground.net/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "sethekk_halls.h"

enum Says
{
    SAY_SUMMON_BROOD    = 0,
    SAY_SPELL_BOMB      = 1,
    SAY_INTRO_1         = 2,
    SAY_INTRO_2         = 3
};

enum Spells
{
    SPELL_SHADOWFORM            = 40973,
    SPELL_PARALYZING_SCREECH    = 40184,
    SPELL_SPELL_BOMB            = 40303,
    SPELL_CYCLONE_OF_FEATHERS   = 40321,
    SPELL_BANISH_SELF           = 42354,
    SPELL_FLESH_RIP             = 40199,
    SPELL_DIVE                  = 40279,

    SPELL_PROTECTION_OF_THE_HAWK    = 40237,
    SPELL_SPITE_OF_THE_EAGLE        = 40240,
    SPELL_SPEED_OF_THE_FALCON       = 40241,
    SPELL_FREEZE                    = 36575,
    SPELL_SHADOWFORM_2              = 39946,
    SPELL_SCREECH                   = 31273,
};

enum Events
{
    EVENT_PARALYZING_SCREECH        = 1,
    EVENT_SPELL_BOMB                = 2,
    EVENT_CYCLONE_OF_FEATHERS       = 3,
    EVENT_SUMMON                    = 4,
    EVENT_INTRO_BEGIN               = 5,
    EVENT_INTRO_STEP                = 6,
    EVENT_INTRO_END                 = 7,
    EVENT_SPIRIT_ACTIVE             = 8,
    EVENT_SPIRIT_REMOVE_FREEZE      = 9,
    EVENT_ACTIVATE_BROOD            = 10,
    EVENT_SCREECH                   = 11,
    EVENT_FLESH_RIP                 = 12,
    EVENT_DIVE                      = 13
};

Position const broodSummonPosition[7] =
{
    { -110.888f, 273.285f, 51.2342f, 0.65809f },
    { -118.116f, 300.301f, 51.2342f, 6.15589f },
    { -68.1980f, 319.389f, 50.0232f, 4.57725f },
    { -59.0446f, 316.367f, 46.9062f, 3.95287f },
    { -51.0529f, 289.847f, 51.1133f, 3.30099f },
    { -61.4086f, 266.650f, 48.6213f, 2.49988f },
    { -91.0337f, 257.492f, 43.4755f, 1.95010f }
};

uint32 const AnzuSpirits[3] = { NPC_HAWK_SPIRIT, NPC_EAGLE_SPIRIT, NPC_FALCON_SPIRIT };

Position const PosAnzuSpirit[3] =
{
    { -96.5290f,  303.6788f, 26.4831f, 5.1741f },
    { -100.1466f, 276.8206f, 24.1406f, 0.6503f },
    { -70.7110f,  290.0608f, 26.4994f, 3.2177f }
};

struct boss_anzuAI : public BossAI
{
    boss_anzuAI(Creature* creature) : BossAI(creature, BOSS_ANZU), _introDone(false) { }

    void Reset() override
    {
        BossAI::Reset();
        _banishStages.fill(false);
        if (!_introDone)
        {
            me->SetPassive();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NON_ATTACKABLE);
            DoCastSelf(SPELL_SHADOWFORM);
            events.ScheduleEvent(EVENT_INTRO_BEGIN, 1s);
        }
    }

    bool CanAIAttack(const Unit* who) const override
    {
        switch (who->GetEntry())
        {
        case NPC_HAWK_SPIRIT:
        case NPC_EAGLE_SPIRIT:
        case NPC_FALCON_SPIRIT:
            return false;
        }
        return true;
    }

    void EnterCombat(Unit* who) override
    {
        BossAI::EnterCombat(who);

        for (uint8 i = 0; i < 3; ++i)
            me->SummonCreature(AnzuSpirits[i], PosAnzuSpirit[i], TEMPSUMMON_MANUAL_DESPAWN, 0);

        if (_introDone)
            ScheduleCombatEvents();
    }

    void AttackStart(Unit* who) override
    {
        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
            return;

        BossAI::AttackStart(who);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*damageSchoolMask*/) override
    {
        if (me->HealthBelowPctDamaged(66, damage) && !_banishStages.at(0))
        {
            _banishStages.at(0) = true;
            Talk(SAY_SUMMON_BROOD);
            events.ScheduleEvent(EVENT_SUMMON, 3s);
        }

        if (me->HealthBelowPctDamaged(33, damage) && !_banishStages.at(1))
        {
            _banishStages.at(1) = true;
            Talk(SAY_SUMMON_BROOD);
            events.ScheduleEvent(EVENT_SUMMON, 3s);
        }
    }

    void ScheduleCombatEvents()
    {
        events.Reset();
        events.ScheduleEvent(EVENT_PARALYZING_SCREECH, 14s);
        events.ScheduleEvent(EVENT_CYCLONE_OF_FEATHERS, 5s);
        events.ScheduleEvent(EVENT_SPELL_BOMB, 10s);
        events.ScheduleEvent(EVENT_FLESH_RIP, 10s, 15s);
        events.ScheduleEvent(EVENT_DIVE, 6s, 16s);
    }

    void UpdateAI(const uint32 diff) override
    {
        if (!UpdateVictim() && _introDone)
            return;

        events.Update(diff);

        if (me->IsCasting())
            return;

        while (auto eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_INTRO_BEGIN:
                Talk(SAY_INTRO_1);
                events.ScheduleEvent(EVENT_INTRO_STEP, 6s);
                break;
            case EVENT_INTRO_STEP:
                Talk(SAY_INTRO_2);
                events.ScheduleEvent(EVENT_INTRO_END, 2s);
                break;
            case EVENT_INTRO_END:
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NON_ATTACKABLE);
                me->RemoveAurasDueToSpell(SPELL_SHADOWFORM);
                me->SetAggressive();
                if (Unit * target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                    AttackStart(target);

                DoZoneInCombat(me, 50.0f);
                _introDone = true;
                events.Reset();
                ScheduleCombatEvents();
                break;
            case EVENT_FLESH_RIP:
            {
                DoCastSelf(SPELL_FLESH_RIP);
                events.Repeat(10s, 14s);
                break;
            }
            case EVENT_PARALYZING_SCREECH:
                DoCastSelf(SPELL_PARALYZING_SCREECH);
                events.Repeat(26s);
                break;
            case EVENT_CYCLONE_OF_FEATHERS:
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.f, true))
                    me->CastSpell(target, SPELL_CYCLONE_OF_FEATHERS);
                events.Repeat(21s);
                break;
            case EVENT_SUMMON:
            {
                events.CancelEvent(EVENT_FLESH_RIP);
                events.CancelEvent(EVENT_DIVE);
                events.ScheduleEvent(EVENT_FLESH_RIP, 55s);
                events.ScheduleEvent(EVENT_DIVE, 60s, 80s);
                Position const CenterPos = { -87.5742f, 287.856f, 26.4832f, 0.08f };
                for (uint8 i = 0; i < 7; i++)
                {
                    if (Creature * brood = me->SummonCreature(NPC_BROOD_OF_ANZU, broodSummonPosition[i], TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 46000))
                    {
                        brood->SetPassive();
                        brood->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                        Movement::PointsArray path;
                        FillSpiralPath(CenterPos, frand(15.f, 20.f), path, roll_chance_i(50) ? true : false, 10);
                        brood->SetHover(true);
                        brood->SetDisableGravity(true);
                        brood->SetCanFly(true);
                        brood->GetMotionMaster()->MoveSplinePath(&path);
                    }
                }

                DoCastSelf(SPELL_BANISH_SELF, true);
                break;
            }
            case EVENT_SPELL_BOMB:
            {
                if (Unit * target = SelectTarget(SELECT_TARGET_RANDOM, 0, [](WorldObject* object)
                {
                    return object->ToPlayer() && object->ToPlayer()->getPowerType() == POWER_MANA;
                }))
                {
                    me->CastSpell(target, SPELL_SPELL_BOMB, true);
                    Talk(SAY_SPELL_BOMB);
                }
                break;
            }
            case EVENT_DIVE:
            {
                if (Unit * target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 45.f, true))
                    me->CastSpell(target, SPELL_DIVE);
                events.Repeat(30s, 40s);
                break;
            }
            default:
                break;
            }
        }

        if (!me->HasAura(SPELL_BANISH_SELF))
            DoMeleeAttackIfReady();
    }

    void FillSpiralPath(Position const& centerPos, float radius, Movement::PointsArray& path, bool clockwise, uint32 numOfCircles)
    {
        float step = clockwise ? -M_PI / 8.0f : M_PI / 8.0f;
        float angle = centerPos.GetAngle(me->GetPositionX(), me->GetPositionY());
        float radiusStep = radius / float(16 * (numOfCircles * 1.3f));
        float z = centerPos.GetPositionZ() + frand(10.f, 25.f);

        for (uint32 i = 0; i < numOfCircles; ++i)
        {

            for (uint32 j = 0; j < 16; angle += step, ++j)
            {
                G3D::Vector3 point;
                point.x = centerPos.GetPositionX() + radius * cosf(angle);
                point.y = centerPos.GetPositionY() + radius * sinf(angle);
                point.z = z;
                radius -= radiusStep;
                path.push_back(point);
            }
        }

        for (uint32 i = 0; i < numOfCircles * 3 * 16; ++i, angle += step)
        {
            G3D::Vector3 point;
            point.x = centerPos.GetPositionX() + radius * cosf(angle);
            point.y = centerPos.GetPositionY() + radius * sinf(angle);
            point.z = z;
            path.push_back(point);
        }
    }

private:
    std::array<bool, 2> _banishStages;
    bool _introDone;
};

struct npc_brood_of_anzu_AI : public ScriptedAI
{
    npc_brood_of_anzu_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        events.Reset();
        events.ScheduleEvent(EVENT_ACTIVATE_BROOD, 2s, 7s);
    }

    void UpdateAI(const uint32 diff) override
    {
        if (events.Empty())
            return;

        events.Update(diff);

        while (auto eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_ACTIVATE_BROOD:
            {
                events.ScheduleEvent(EVENT_SCREECH, 2s, 8s);
                me->SetAggressive();
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                DoZoneInCombat(me, 50.f);
                if (Unit * target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                    AttackStart(target);
                break;
            }
            case EVENT_SCREECH:
            {
                DoCastAOE(SPELL_SCREECH, true);
                events.Repeat(10s, 15s);
                break;
            }
            }
        }

        DoMeleeAttackIfReady();
    }
private:
    EventMap events;
};

struct npc_anzu_spiritAI : public ScriptedAI
{
    npc_anzu_spiritAI(Creature* creature) : ScriptedAI(creature)
    {
        Initialize();
        me->SetReactState(REACT_PASSIVE);
        me->setFaction(35);
    }

    void SpellHit(Unit* caster, const SpellInfo* spell) override
    {
        if (spell && spell->SpellFamilyName == SPELLFAMILY_DRUID && spell->SpellFamilyFlags == flag96(0x1000000050, 0x0, 0x0))
        {
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_AURA_DURATION, spell->GetDuration());
            if (spellId == SPELL_SPITE_OF_THE_EAGLE)
                me->CastCustomSpell(spellId, val);
            else
                me->CastCustomSpell(spellId, val, caster);

            me->RemoveAurasDueToSpell(SPELL_SHADOWFORM_2);
            events.ScheduleEvent(EVENT_SPIRIT_ACTIVE, 3.5s);
        }
    }

    void Initialize()
    {
        switch (me->GetEntry())
        {
        case NPC_EAGLE_SPIRIT:
            spellId = SPELL_SPITE_OF_THE_EAGLE;
            break;
        case NPC_HAWK_SPIRIT:
            spellId = SPELL_PROTECTION_OF_THE_HAWK;
            break;
        case NPC_FALCON_SPIRIT:
            spellId = SPELL_SPEED_OF_THE_FALCON;
            break;
        default:
            spellId = 0;
            break;
        }
    }

    void Reset() override
    {
        events.Reset();
        Initialize();
        DoCast(me, SPELL_SHADOWFORM_2);
    }

    void UpdateAI(const uint32 diff) override
    {
        if (events.Empty())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SPIRIT_ACTIVE:
                DoCast(me, SPELL_SHADOWFORM_2);
                DoCastSelf(SPELL_FREEZE);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                events.ScheduleEvent(EVENT_SPIRIT_REMOVE_FREEZE, 15s);
                break;
            case EVENT_SPIRIT_REMOVE_FREEZE:
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->RemoveAurasDueToSpell(SPELL_FREEZE);
                break;
            default:
                break;
            }
        }
    }

private:
    EventMap events;
    uint32 spellId;
};

class spell_summon_raven_god_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_summon_raven_god_SpellScript);

    void HandleHit()
    {
        if (GetCaster())
            if (InstanceScript * instance = GetCaster()->GetInstanceScript())
                instance->SetData(DATA_ANZU_STARTEVENT, DATA_ANZU_STARTEVENT);
    }

    void Register() override
    {
        AfterCast += SpellCastFn(spell_summon_raven_god_SpellScript::HandleHit);
    }
};

void AddSC_boss_anzu()
{
    new CreatureAILoader<boss_anzuAI>("boss_anzu");
    new CreatureAILoader<npc_brood_of_anzu_AI>("npc_brood_of_anzu");
    new CreatureAILoader<npc_anzu_spiritAI>("npc_anzu_spirit");
    new SpellScriptLoaderEx<spell_summon_raven_god_SpellScript>("spell_summon_raven_lord");
}
