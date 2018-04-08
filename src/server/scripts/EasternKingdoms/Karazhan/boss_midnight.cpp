/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "karazhan.h"
#include "MotionMaster.h"
#include "ObjectAccessor.h"
#include "ScriptedCreature.h"
#include "SpellInfo.h"

enum AttumenTexts
{
    SAY_KILL,
    SAY_RANDOM,
    SAY_DISARMED,
    SAY_MIDNIGHT_KILL,
    SAY_APPEAR,
    SAY_MOUNT,

    SAY_DEATH                       = 3,

    // Midnight
    EMOTE_CALL_ATTUMEN              = 0,
    EMOTE_MOUNT_UP
};

enum AttumenSpells
{
    // Attumen
    SPELL_SHADOWCLEAVE              = 29832,
    SPELL_INTANGIBLE_PRESENCE       = 29833,
    SPELL_SPAWN_SMOKE               = 10389,
    SPELL_CHARGE                    = 29847,

    // Midnight
    SPELL_KNOCKDOWN                 = 29711,
    SPELL_SUMMON_ATTUMEN            = 29714,
    SPELL_MOUNT                     = 29770,
    SPELL_SUMMON_ATTUMEN_MOUNTED    = 29799
};

enum AttumenPhases
{
    PHASE_NONE,
    PHASE_ATTUMEN_ENGAGES,
    PHASE_MOUNTED
};

struct boss_attumenAI : public BossAI
{
    boss_attumenAI(Creature* creature) : BossAI(creature, BOSS_ATTUMEN) { }

    void Reset() override
    {
        _Reset();
        _midnightGUID = 0;
        _phase = PHASE_NONE;
    }

    void EnterEvadeMode() override
    {
        if (Creature* midnight = ObjectAccessor::GetCreature(*me, _midnightGUID))
            BossAI::_DespawnAtEvade(10, midnight);

        me->DespawnOrUnsummon();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        scheduler.Schedule(15s, 25s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_SHADOWCLEAVE);
            task.Repeat();
        });

        scheduler.Schedule(25s, 45s, [this](TaskContext task)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                DoCast(target, SPELL_INTANGIBLE_PRESENCE);

            task.Repeat();
        });

        scheduler.Schedule(30s, 60s, [this](TaskContext task)
        {
            Talk(SAY_RANDOM);
            task.Repeat();
        });
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        // Attumen does not die until he mounts Midnight, let health fall to 1 and prevent further damage.
        if (damage >= me->GetHealth() && _phase != PHASE_MOUNTED)
            damage = me->GetHealth() - 1;

        if (_phase == PHASE_ATTUMEN_ENGAGES && me->HealthBelowPctDamaged(25, damage))
        {
            _phase = PHASE_NONE;

            if (Creature* midnight = ObjectAccessor::GetCreature(*me, _midnightGUID))
                midnight->AI()->DoCastAOE(SPELL_MOUNT, true);
        }
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_KILL);
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_ATTUMEN_MOUNTED)
            if (Creature* midnight = ObjectAccessor::GetCreature(*me, _midnightGUID))
            {
                summon->SetHealth(std::max(midnight->GetHealth(), me->GetHealth()));
                summon->AI()->DoZoneInCombat();
                summon->AI()->SetGUID(_midnightGUID, NPC_MIDNIGHT);
            }

        BossAI::JustSummoned(summon);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        if (summoner->GetEntry() == NPC_MIDNIGHT)
            _phase = PHASE_ATTUMEN_ENGAGES;

        if (summoner->GetEntry() == NPC_ATTUMEN_UNMOUNTED)
        {
            _phase = PHASE_MOUNTED;
            DoCastSelf(SPELL_SPAWN_SMOKE);

            scheduler.Schedule(10s, 25s, [this](TaskContext task)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [this](Unit* tar) { return tar->IsPlayer() && tar->IsInRange(me, 8.0f, 25.0f); }))
                    DoCast(target, SPELL_CHARGE);

                task.Repeat();
            });

            scheduler.Schedule(25s, 35s, [this](TaskContext task)
            {
                DoCastVictim(SPELL_KNOCKDOWN);
                task.Repeat();
            });
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        if (Unit* midnight = ObjectAccessor::GetUnit(*me, _midnightGUID))
            midnight->Kill(midnight, midnight, false);

        _JustDied();
    }

    void SetGUID(uint64 guid, int32 id) override
    {
        if (id == NPC_MIDNIGHT)
            _midnightGUID = guid;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && _phase != PHASE_NONE)
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }

    void SpellHit(Unit* /*source*/, SpellInfo const* spell) override
    {
        if (spell->Mechanic == MECHANIC_DISARM)
            Talk(SAY_DISARMED);

        if (spell->Id == SPELL_MOUNT)
        {
            if (Creature* midnight = ObjectAccessor::GetCreature(*me, _midnightGUID))
            {
                _phase = PHASE_NONE;
                scheduler.CancelAll();

                midnight->AttackStop();
                midnight->RemoveAllAttackers();
                midnight->SetAggressive();
                midnight->GetMotionMaster()->MoveFollow(me, 2.0f, 0.0f);
                midnight->AI()->Talk(EMOTE_MOUNT_UP);

                me->AttackStop();
                me->RemoveAllAttackers();
                me->SetPassive();
                me->GetMotionMaster()->MoveFollow(midnight, 2.0f, 0.0f);
                Talk(SAY_MOUNT);

                scheduler.Schedule(1s, [this](TaskContext task)
                {
                    if (Creature* midnight = ObjectAccessor::GetCreature(*me, _midnightGUID))
                    {
                        if (me->IsWithinDist2d(midnight, 5.0f))
                        {
                            DoCastSelf(SPELL_SUMMON_ATTUMEN_MOUNTED);
                            me->SetVisible(false);
                            me->GetMotionMaster()->Clear();
                            midnight->SetVisible(false);
                        }
                        else
                        {
                            midnight->GetMotionMaster()->MoveFollow(me, 2.0f, 0.0f);
                            me->GetMotionMaster()->MoveFollow(midnight, 2.0f, 0.0f);
                            task.Repeat();
                        }
                    }
                });
            }
        }
    }

    private:
        uint64 _midnightGUID;
        uint8 _phase;
};

struct boss_midnightAI : public BossAI
{
    boss_midnightAI(Creature* creature) : BossAI(creature, BOSS_ATTUMEN) { }

    void Reset() override
    {
        _Reset();
        _phase = PHASE_NONE;
        me->SetVisible(true);
        me->SetDefensive();
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        // Midnight never dies, let health fall to 1 and prevent further damage.
        if (damage >= me->GetHealth())
            damage = me->GetHealth() - 1;

        if (_phase == PHASE_NONE && me->HealthBelowPctDamaged(95, damage))
        {
            _phase = PHASE_ATTUMEN_ENGAGES;
            Talk(EMOTE_CALL_ATTUMEN);
            DoCastAOE(SPELL_SUMMON_ATTUMEN);
        }
        else if (_phase == PHASE_ATTUMEN_ENGAGES && me->HealthBelowPctDamaged(25, damage))
        {
            _phase = PHASE_MOUNTED;
            DoCastAOE(SPELL_MOUNT, true);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_ATTUMEN_UNMOUNTED)
        {
            _attumenGUID = summon->GetGUID();
            summon->AI()->SetGUID(me->GetGUID(), NPC_MIDNIGHT);
            summon->AI()->AttackStart(me->GetVictim());
            summon->AI()->Talk(SAY_APPEAR);
        }

        BossAI::JustSummoned(summon);
    }

    void EnterCombat(Unit* attacker) override
    {
        BossAI::EnterCombat(attacker);

        scheduler.Schedule(15s, 25s, [this](TaskContext task)
        {
            DoCastVictim(SPELL_KNOCKDOWN);
            task.Repeat();
        });
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade(10);
    }

    void KilledUnit(Unit* victim) override
    {
        if (!victim->IsPlayer())
            return;

        if (_phase == PHASE_ATTUMEN_ENGAGES)
        {
            if (Unit* unit = ObjectAccessor::GetUnit(*me, _attumenGUID))
                Talk(SAY_MIDNIGHT_KILL, unit);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() || _phase == PHASE_MOUNTED)
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }

    private:
        uint64 _attumenGUID;
        uint8 _phase;
};

void AddSC_boss_attumen()
{
    new CreatureAILoader<boss_attumenAI>("boss_attumen");
    new CreatureAILoader<boss_midnightAI>("boss_midnight");
}
