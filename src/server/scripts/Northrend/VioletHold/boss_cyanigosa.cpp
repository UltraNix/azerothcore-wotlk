/*
 * Copyright (C) 2008-2018 TrinityCore <https://www.trinitycore.org/>
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
#include "InstanceScript.h"
#include "SpellScript.h"
#include "ScriptedCreature.h"
#include "violet_hold.h"

enum CyanigosaSpells
{
    SPELL_SUMMON_PLAYER                         = 21150,
    SPELL_ARCANE_VACUUM                         = 58694,
    SPELL_BLIZZARD                              = 58693,
    SPELL_MANA_DESTRUCTION                      = 59374,
    SPELL_TAIL_SWEEP                            = 58690,
    SPELL_UNCONTROLLABLE_ENERGY                 = 58688,
    SPELL_TRANSFORM                             = 58668
};

enum CyanigosaYells
{
    SAY_AGGRO,
    SAY_SLAY,
    SAY_DEATH,
    SAY_SPAWN,
    SAY_DISRUPTION,
    SAY_BREATH_ATTACK,
    SAY_SPECIAL_ATTACK
};

struct boss_cyanigosaAI : public BossAI
{
    boss_cyanigosaAI(Creature* creature) : BossAI(creature, DATA_CYANIGOSA) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        scheduler.Schedule(10s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_ARCANE_VACUUM);
            task.Repeat();
        });

        scheduler.Schedule(15s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                DoCast(target, SPELL_BLIZZARD);
            task.Repeat();
        });

        scheduler.Schedule(20s, [this](TaskContext task)
        {
            DoCastAOE(SPELL_TAIL_SWEEP);
            task.Repeat();
        });

        scheduler.Schedule(25s, [this](TaskContext task)
        {
            DoCastAOE(SPELL_UNCONTROLLABLE_ENERGY);
            task.Repeat();
        });

        if (IsHeroic())
        {
            scheduler.Schedule(30s, [this](TaskContext task)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_MANA_DESTRUCTION);
                task.Repeat();
            });
        }
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_SLAY);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }
};

class achievement_defenseless : public AchievementCriteriaScript
{
    public:
        achievement_defenseless() : AchievementCriteriaScript("achievement_defenseless") { }

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (!target)
                return false;

            InstanceScript* instance = target->GetInstanceScript();
            if (!instance)
                return false;

            return instance->GetData(DATA_DEFENSELESS) != 0;
        }
};

class spell_cyanigosa_arcane_vacuum_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_cyanigosa_arcane_vacuum_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_SUMMON_PLAYER });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetHitUnit(), SPELL_SUMMON_PLAYER, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_cyanigosa_arcane_vacuum_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_cyanigosa()
{
    new CreatureAILoader<boss_cyanigosaAI>("boss_cyanigosa");
    new achievement_defenseless();
    new SpellScriptLoaderEx<spell_cyanigosa_arcane_vacuum_SpellScript>("spell_cyanigosa_arcane_vacuum");
}
