#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "molten_core.h"

enum Texts
{
    EMOTE_LOWHP             = 0,
};

enum Spells
{
    // Golemagg
    SPELL_MAGMA_SPLASH      = 13879,
    SPELL_PYROBLAST         = 20228,
    SPELL_EARTHQUAKE        = 19798,
    SPELL_ENRAGE            = 19953,
    SPELL_GOLEMAGG_TRUST    = 20553,
    SPELL_DOUBLE_ATTACK     = 18943,

    // Core Rager
    SPELL_THRASH            = 12787,
    SPELL_MANGLE            = 19820
};

enum Events
{
    // Golemagg
    EVENT_PYROBLAST         = 1,
    EVENT_EARTHQUAKE,

    // Core Rager
    EVENT_MANGLE            = 1,
    EVENT_TRUST
};

struct boss_golemaggAI : public BossAI
{
    boss_golemaggAI(Creature* creature) : BossAI(creature, BOSS_GOLEMAGG_THE_INCINERATOR) { }

    void Reset()
    {
        _Reset();
        DoCast(me, SPELL_MAGMA_SPLASH, true);
    }

    void EnterCombat(Unit* /*victim*/)
    {
        _EnterCombat();
        me->CallForHelp(15.0f);
        events.ScheduleEvent(EVENT_PYROBLAST, 7000);
    }

    void EnterEvadeMode() override
    {
        std::list<Creature*> addList;
        me->GetCreatureListWithEntryInGrid(addList, 11672, 100.0f);
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

    void JustDied(Unit* /*killer*/) override
    {
        std::list<Creature*> addList;
        me->GetCreatureListWithEntryInGrid(addList, 11672, 100.0f);
        if (!addList.empty())
            for (auto itr : addList)
                itr->DespawnOrUnsummon();
        _JustDied();
    }

    void DamageTaken(Unit*, uint32& /*damage*/, DamageEffectType, SpellSchoolMask)
    {
        if (!HealthBelowPct(10) || me->HasAura(SPELL_ENRAGE))
            return;

        DoCast(me, SPELL_ENRAGE, true);
        events.ScheduleEvent(EVENT_EARTHQUAKE, 3000);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_PYROBLAST:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                    DoCast(target, SPELL_PYROBLAST);
                events.ScheduleEvent(EVENT_PYROBLAST, 7000);
                break;
            case EVENT_EARTHQUAKE:
                DoCastVictim(SPELL_EARTHQUAKE);
                events.ScheduleEvent(EVENT_EARTHQUAKE, 3000);
                break;
            default:
                break;
        }
    }
};

struct npc_core_ragerAI : public ScriptedAI
{
    npc_core_ragerAI(Creature* creature) : ScriptedAI(creature) { }

    void EnterCombat(Unit* victim)
    {
        CreatureAI::EnterCombat(victim);
        _events.ScheduleEvent(EVENT_TRUST, 2000);
    }

    void DamageTaken(Unit*, uint32& /*damage*/, DamageEffectType, SpellSchoolMask)
    {
        if (HealthAbovePct(50))
            return;

        Talk(EMOTE_LOWHP);
        me->SetFullHealth();
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_MANGLE:
                    DoCastVictim(SPELL_MANGLE);
                    _events.Repeat(10000);
                    break;
                case EVENT_TRUST:
                    if (Creature* hound = me->FindNearestCreature(11672, 30.0f, true))
                        me->AddAura(SPELL_GOLEMAGG_TRUST, me);
                    _events.Repeat(2000);
                    break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

private:
    EventMap _events;
};

void AddSC_boss_golemagg()
{
    new CreatureAILoader<boss_golemaggAI>("boss_golemagg");
    new CreatureAILoader<npc_core_ragerAI>("npc_core_rager");
}
