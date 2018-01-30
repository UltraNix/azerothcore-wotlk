#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"

enum EdwinSays
{
    SAY_AGGRO,
    SAY_66PCT,
    SAY_SUMMON_1,
    SAY_SUMMON_2,
    SAY_SLAY,
    SAY_DEATH
};

enum EdwinSpells
{
    SPELL_VANCLEEF_ALLIES   = 5200,
    SPELL_DUAL_WIELD        = 674
};

struct boss_edwin_vancleefAI : public BossAI
{
    boss_edwin_vancleefAI(Creature* creature) : BossAI(creature, BOSS_EDWIN_VANCLEEF) { }

    void Reset() override
    {
        _said66 = false;
        _summonPhase = 0;
        _Reset();
        DoCastSelf(SPELL_DUAL_WIELD);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        _JustDied();
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_SLAY);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*damageSchoolMask*/) override
    {
        if (!_said66 && me->HealthBelowPctDamaged(66, damage))
        {
            _said66 = true;
            Talk(SAY_66PCT);
        }

        if ((_summonPhase == 0 && me->HealthBelowPctDamaged(50, damage)) || (_summonPhase == 1 && me->HealthBelowPctDamaged(25, damage)))
        {
            DoCastAOE(SPELL_VANCLEEF_ALLIES);
            Talk(_summonPhase == 0 ? SAY_SUMMON_1 : SAY_SUMMON_2);
            ++_summonPhase;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

    private:
        bool _said66;
        uint8 _summonPhase;
};

void AddSC_boss_edwin_vancleef()
{
    new CreatureAILoader<boss_edwin_vancleefAI>("boss_edwin_vancleef");
}