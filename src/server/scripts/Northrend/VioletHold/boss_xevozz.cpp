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
#include "MotionMaster.h"
#include "Player.h"
#include "ScriptedCreature.h"
#include "SpellInfo.h"
#include "SpellScript.h"
#include "violet_hold.h"

static uint32 const EtherealSphereCount = 3;
static uint32 const EtherealSphereSummonSpells[EtherealSphereCount] = { 54102, 54137, 54138 };
static uint32 const EtherealSphereHeroicSummonSpells[EtherealSphereCount] = { 54102, 54137, 54138 };

enum XevozzNPCs
{
    NPC_ETHEREAL_SPHERE                         = 29271,
    NPC_ETHEREAL_SPHERE2                        = 32582,
    NPC_ETHEREAL_SUMMON_TARGET                  = 29276
};

enum XevozzSpells
{
    SPELL_ARCANE_BARRAGE_VOLLEY                 = 54202,
    SPELL_ARCANE_BUFFET                         = 54226,
    SPELL_SUMMON_TARGET_VISUAL                  = 54111,

    SPELL_ARCANE_POWER                          = 54160,
    H_SPELL_ARCANE_POWER                        = 59474,
    SPELL_MAGIC_PULL                            = 50770,
    SPELL_SUMMON_PLAYERS                        = 54164,
    SPELL_POWER_BALL_VISUAL                     = 54141,
    SPELL_POWER_BALL_DAMAGE_TRIGGER             = 54207
};

enum XevozzYells
{
    // Xevozz
    SAY_AGGRO,
    SAY_SLAY,
    SAY_DEATH,
    SAY_SPAWN,
    SAY_CHARGED,
    SAY_REPEAT_SUMMON,
    SAY_SUMMON_ENERGY,

    // Ethereal Sphere
    SAY_ETHEREAL_SPHERE_SUMMON                  = 0
};

enum XevozzActions
{
    ACTION_SUMMON                               = 1,
};

struct boss_xevozzAI : public BossAI
{
    boss_xevozzAI(Creature* creature) : BossAI(creature, DATA_XEVOZZ) { }

    void Reset() override
    {
        me->SetWalk(true);
        _Reset();
    }

    void SummonTarget(uint32 spellId)
    {
        auto posInfo = sSpellMgr->GetSpellTargetPosition(spellId, EFFECT_0);
        if (!posInfo)
            return;

        Position pos(posInfo->target_X, posInfo->target_Y, posInfo->target_Z, posInfo->target_Orientation);
        if (Creature* target = me->SummonCreature(NPC_ETHEREAL_SUMMON_TARGET, pos, TEMPSUMMON_TIMED_DESPAWN, 3000))
            target->CastSpell(target, SPELL_SUMMON_TARGET_VISUAL, true);
        DoCastSelf(spellId);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->SetWalk(false);
        _EnterCombat();
        Talk(SAY_AGGRO);
        scheduler.Schedule(8s, 10s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_ARCANE_BARRAGE_VOLLEY);
            task.Repeat(8s, 10s);
        });

        scheduler.Schedule(10s, 11s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 45.0f, true))
                DoCast(target, SPELL_ARCANE_BUFFET);
            task.Repeat(15s, 20s);
        });

        scheduler.Schedule(5s, [this](TaskContext task)
        {
            Talk(SAY_REPEAT_SUMMON);

            std::list<uint8> summonSpells = { 0, 1, 2 };

            uint8 spell = Trinity::Containers::SelectRandomContainerElement(summonSpells);
            SummonTarget(EtherealSphereSummonSpells[spell]);
            summonSpells.remove(spell);

            if (IsHeroic())
            {
                spell = Trinity::Containers::SelectRandomContainerElement(summonSpells);
                task.Schedule(2500ms, [this, spell](TaskContext /*task*/)
                {
                    SummonTarget(EtherealSphereHeroicSummonSpells[spell]);
                });
            }

            task.Schedule(33s, 35s, [this](TaskContext /*task*/)
            {
                summons.DoAction(ACTION_SUMMON);
            });

            task.Repeat(45s, 47s);
        });
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
        instance->SetData(DATA_HANDLE_CELLS, DATA_XEVOZZ);
    }

    void JustSummoned(Creature* summon) override
    {
        BossAI::JustSummoned(summon);
        if (summon->GetEntry() != NPC_ETHEREAL_SUMMON_TARGET)
            summon->GetMotionMaster()->MoveFollow(me, 0.0f, 0.0f);
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

    void SpellHit(Unit* /*who*/, SpellInfo const* spell) override
    {
        if (spell->Id == SPELL_ARCANE_POWER || spell->Id == H_SPELL_ARCANE_POWER)
            Talk(SAY_SUMMON_ENERGY);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }
};

struct npc_ethereal_sphereAI : public ScriptedAI
{
    npc_ethereal_sphereAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = creature->GetInstanceScript();
    }

    void Reset() override
    {
        _scheduler.CancelAll();
        ScheduledTasks();

        DoCastSelf(SPELL_POWER_BALL_VISUAL);
        DoCastSelf(SPELL_POWER_BALL_DAMAGE_TRIGGER);

        me->DespawnOrUnsummon(40s);
    }

    void DoAction(int32 action) override
    {
        if (action == ACTION_SUMMON)
        {
            Talk(SAY_ETHEREAL_SPHERE_SUMMON);
            DoCastSelf(SPELL_SUMMON_PLAYERS);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    void ScheduledTasks()
    {
        _scheduler.Schedule(1s, [this](TaskContext task)
        {
            if (Creature* xevozz = instance->GetCreature(DATA_XEVOZZ))
            {
                if (me->IsWithinDist(xevozz, 3.0f))
                {
                    DoCastAOE(SPELL_ARCANE_POWER);
                    me->DespawnOrUnsummon(8s);
                    return;
                }
            }

            task.Repeat();
        });
    }

    private:
        InstanceScript* instance;
        TaskScheduler _scheduler;
};

class spell_xevozz_summon_players_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_xevozz_summon_players_SpellScript);

    bool Validate(SpellInfo const* /*spellInfo*/) override
    {
        return ValidateSpellInfo({ SPELL_MAGIC_PULL });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetHitUnit(), SPELL_MAGIC_PULL, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_xevozz_summon_players_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_xevozz()
{
    new CreatureAILoader<boss_xevozzAI>("boss_xevozz");
    new CreatureAILoader<npc_ethereal_sphereAI>("npc_ethereal_sphere");
    new SpellScriptLoaderEx<spell_xevozz_summon_players_SpellScript>("spell_xevozz_summon_players");
}
