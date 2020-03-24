#include "shadowfang_keep.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"

enum NandosSpells
{
    SPELL_BLEAK_WORG        = 7487,
    SPELL_SLAVERING_WORG    = 7488,
    SPELL_LUPINE_HORROR     = 7489
};

struct boss_wolf_master_nandosAI : public BossAI
{
    boss_wolf_master_nandosAI(Creature* creature) : BossAI(creature, BOSS_NANDOS) { }

    void Reset() override
    {
        _Reset();
        _offset = 0;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        int32 hpPct = std::max(0, 75 - (_offset * 25));
        if (hpPct && me->HealthBelowPctDamaged(hpPct, damage))
        {
            DoCastSelf(SPELL_BLEAK_WORG + _offset);
            ++_offset;
        }
    }

    private:
        int32 _offset;
};

void AddSC_boss_wolf_master_nandos()
{
    new CreatureAILoader<boss_wolf_master_nandosAI>("boss_wolf_master_nandos");
}
