#include "ScriptPCH.h"
#include "halls_of_reflection.h"

enum MarwynYells
{
    SAY_AGGRO = 60,
    SAY_SLAY_1,
    SAY_SLAY_2,
    SAY_DEATH,
    SAY_CORRUPTED_FLESH_1,
    SAY_CORRUPTED_FLESH_2
};

enum MarwynSpells
{
    SPELL_OBLITERATE = 72360,
    SPELL_WELL_OF_CORRUPTION = 72362,
    SPELL_CORRUPTED_FLESH = 72363,
    SPELL_SHARED_SUFFERING = 72368,
};

enum MarwynEvents
{
    EVENT_AGGRO = 1,
    EVENT_OBLITERATE,
    EVENT_WELL_OF_CORRUPTION,
    EVENT_CORRUPTED_FLESH,
    EVENT_SHARED_SUFFERING,
    EVENT_KILL_TALK
};

struct boss_marwynAI : public BossAI
{
    boss_marwynAI(Creature* creature) : BossAI(creature, DATA_MARWYN) { }

    void Reset() override
    {
        _Reset();
        me->SetAttackable(false);
        instance->SetData(DATA_MARWYN, NOT_STARTED);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        me->SetAttackable(true);
        events.ScheduleEvent(EVENT_OBLITERATE, 15s);
        events.ScheduleEvent(EVENT_WELL_OF_CORRUPTION, 13s);
        events.ScheduleEvent(EVENT_CORRUPTED_FLESH, 20s);
        events.ScheduleEvent(EVENT_SHARED_SUFFERING, 5s);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId != 1)
            return;

        Talk(SAY_AGGRO);
        _events.ScheduleEvent(EVENT_AGGRO, 8s);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_AGGRO)
            me->SetInCombatWithZone();

        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_OBLITERATE:
                if (me->IsWithinMeleeRange(me->GetVictim()))
                {
                    DoCastVictim(SPELL_OBLITERATE);
                    events.Repeat(15s);
                }
                else
                    events.Repeat(3s);
                break;
            case EVENT_WELL_OF_CORRUPTION:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                    DoCast(target, SPELL_WELL_OF_CORRUPTION);
                events.Repeat(13s);
                break;
            case EVENT_CORRUPTED_FLESH:
                Talk(RAND(SAY_CORRUPTED_FLESH_1, SAY_CORRUPTED_FLESH_2));
                DoCastAOE(SPELL_CORRUPTED_FLESH);
                events.Repeat(20s);
                break;
            case EVENT_SHARED_SUFFERING:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.0f, true))
                    DoCast(target, SPELL_SHARED_SUFFERING, true);
                events.Repeat(15s);
                break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        _JustDied();
        instance->SetData(DATA_MARWYN, DONE);
    }

    void KilledUnit(Unit* /*who*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(RAND(SAY_SLAY_1, SAY_SLAY_2));
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void EnterEvadeMode() override
    {
        ScriptedAI::EnterEvadeMode();
        if (_events.GetTimeUntilEvent(EVENT_AGGRO))
            Reset();
    }

    private:
        EventMap _events;
};

class spell_hor_shared_suffering_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_hor_shared_suffering_AuraScript)

    void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        // @todo remove playerlist
        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL) // dispelled
            if (Unit* caster = GetCaster())
                if (Map* map = caster->FindMap())
                    if (Aura* aura = aurEff->GetBase())
                    {
                        uint32 count = 0;
                        uint32 ticks = 0;
                        uint32 dmgPerTick = aura->GetSpellInfo()->Effects[0].BasePoints;
                        auto const& players = map->GetPlayers();
                        for (auto itr = players.begin(); itr != players.end(); ++itr)
                            if (Player* player = itr->GetSource())
                                if (player->IsAlive())
                                    ++count;
                        ticks = (aura->GetDuration() / int32(aura->GetSpellInfo()->Effects[0].Amplitude)) + 1;
                        int32 dmg = (ticks*dmgPerTick) / count;
                        caster->CastCustomSpell(GetTarget(), 72373, nullptr, &dmg, nullptr, true);
                    }
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_hor_shared_suffering_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

void AddSC_boss_marwyn()
{
    new CreatureAILoader<boss_marwynAI>("boss_marwyn");
    new AuraScriptLoaderEx<spell_hor_shared_suffering_AuraScript>("spell_hor_shared_suffering");
}