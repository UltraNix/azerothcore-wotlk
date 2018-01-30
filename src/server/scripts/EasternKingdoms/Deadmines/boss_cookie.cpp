#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "deadmines.h"

enum CookieSpells
{
    SPELL_ACID_SPLASH       = 6306,
    SPELL_COOKIES_COOKING   = 5174
};

struct boss_cookieAI : public BossAI
{
    boss_cookieAI(Creature* creature) : BossAI(creature, BOSS_COOKIE) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        scheduler.Schedule(1s, 7s, [this](TaskContext task) 
        {
            DoCastSelf(SPELL_ACID_SPLASH);
            task.Repeat(20s, 25s);
        });
        scheduler.Schedule(10s, 12s, [this](TaskContext task) 
        {
            if (HealthBelowPct(100))
                DoCastSelf(SPELL_COOKIES_COOKING);
            task.Repeat(15s, 25s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff,
            std::bind(&BossAI::DoMeleeAttackIfReady, this));
    }
};

void AddSC_boss_cookie()
{
    new CreatureAILoader<boss_cookieAI>("boss_cookie");
}