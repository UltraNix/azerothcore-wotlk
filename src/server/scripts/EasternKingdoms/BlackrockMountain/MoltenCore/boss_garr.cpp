#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Spells
{
    // Garr
    SPELL_ANTIMAGIC_PULSE           = 19492,
    SPELL_MAGMA_SHACKLES            = 19496,
    SPELL_ENRAGE                    = 19516,
    SPELL_THRASH                    = 8876,
    SPELL_SEPARATION_ANXIETY_EFFECT = 23492,

    // Adds
    SPELL_ERUPTION                  = 19497,
    SPELL_IMMOLATE                  = 15733,
};

enum Events
{
    // Garr
    EVENT_ANTIMAGIC_PULSE           = 1,
    EVENT_MAGMA_SHACKLES,

    // Adds
    EVENT_CHECK_RANGE               = 1
};

struct boss_garrAI : public BossAI
{
    boss_garrAI(Creature* creature) : BossAI(creature, BOSS_GARR) { }

    void EnterCombat(Unit* /*victim*/) override
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_ANTIMAGIC_PULSE, 25000);
        events.ScheduleEvent(EVENT_MAGMA_SHACKLES, 15000);
    }

    void EnterEvadeMode() override
    {
        std::list<Creature*> addList;
        me->GetCreatureListWithEntryInGrid(addList, 12099, 100.0f);
        if (!addList.empty())
        {
            for (auto itr : addList)
            {
                if (!itr->IsAlive())
                    itr->Respawn();
                if (itr->IsAIEnabled)
                    itr->AI()->EnterEvadeMode();
            }
        }
        CreatureAI::EnterEvadeMode();
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_ANTIMAGIC_PULSE:
                DoCast(me, SPELL_ANTIMAGIC_PULSE);
                events.ScheduleEvent(EVENT_ANTIMAGIC_PULSE, urand(10000, 15000));
                break;
            case EVENT_MAGMA_SHACKLES:
                DoCast(me, SPELL_MAGMA_SHACKLES);
                events.ScheduleEvent(EVENT_MAGMA_SHACKLES, urand(8000, 12000));
                break;
            default:
                break;
        }
    }
};

struct npc_fireswornAI : public ScriptedAI
{
    npc_fireswornAI(Creature* creature) : ScriptedAI(creature), instance(me->GetInstanceScript()) { }

    void Reset() 
    {
        DoCast(me, SPELL_THRASH, true);
        DoCast(me, SPELL_IMMOLATE, true);
    }

    void EnterCombat(Unit* victim) override
    {
        CreatureAI::EnterCombat(victim);
        _events.ScheduleEvent(EVENT_CHECK_RANGE, 5000);
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (me->HealthBelowPctDamaged(10, damage))
        {
            if (Creature* garr = instance->GetCreature(BOSS_GARR))
                garr->AddAura(SPELL_ENRAGE, garr);
            damage = me->GetHealth() - 1;
            DoCastAOE(SPELL_ERUPTION);
            me->DespawnOrUnsummon();
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_CHECK_RANGE)
        {
            if (Creature* garr = instance->GetCreature(BOSS_GARR))
                if (!garr->IsInRange(me, 0.0f, 50.0f) && garr->IsAlive())
                    DoCast(me, SPELL_SEPARATION_ANXIETY_EFFECT, true);
            _events.Repeat(5000);
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
    InstanceScript* instance;
};

void AddSC_boss_garr()
{
    new CreatureAILoader<boss_garrAI>("boss_garr");
    new CreatureAILoader<npc_fireswornAI>("npc_firesworn");
}
