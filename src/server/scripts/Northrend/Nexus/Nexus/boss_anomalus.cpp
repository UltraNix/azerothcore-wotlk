/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "nexus.h"
#include "Player.h"
#include "World.h"

enum Spells
{
    SPELL_SPARK                             = 47751,
    SPELL_RIFT_SHIELD                       = 47748,
    SPELL_CHARGE_RIFTS                      = 47747,
    SPELL_CREATE_RIFT                       = 47743,
    SPELL_ARCANE_ATTRACTION                 = 57063,
    SPELL_CLOSE_RIFTS                       = 47745
};

enum Yells
{
    SAY_AGGRO,
    SAY_DEATH,
    SAY_RIFT,
    EMOTE_RIFT,
    EMOTE_SHIELD
};

enum Events
{
    EVENT_ANOMALUS_SPARK                    = 1,
    EVENT_ANOMALUS_HEALTH,
    EVENT_ANOMALUS_ARCANE_ATTRACTION
};

class ChargeRifts : public BasicEvent
{
    public:
        explicit ChargeRifts(Creature* caster) : _caster(caster) {}

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/) override
        {
            if (_caster->IsAIEnabled)
                _caster->AI()->Talk(EMOTE_SHIELD);
            _caster->CastSpell(_caster, SPELL_CHARGE_RIFTS, true);
            return true;
        }

    private:
        Creature* _caster;
};

struct boss_anomalusAI : BossAI
{
    explicit boss_anomalusAI(Creature* creature) : BossAI(creature, DATA_ANOMALUS_EVENT), _achievement(false), _riftCount(0), _preNerf(sWorld->PatchNotes(PATCH_MIN, PATCH_332))
    {
        boundaryHandler.SetBoundary(new CircleBoundary(me->GetHomePosition(), 60.0f));
    }

    void Reset() override
    {
        _Reset();
        _achievement = true;
        _riftCount = 0;
        DoCastSelf(SPELL_CLOSE_RIFTS, true);
    }

    uint32 GetData(uint32 data) const override
    {
        if (data == me->GetEntry())
            return _achievement;
        return 0;
    }

    void SetData(uint32 type, uint32) override
    {
        if (_preNerf)
            events.ScheduleEvent(EVENT_ANOMALUS_HEALTH, 1000);

        if (type == me->GetEntry())
        {
            me->RemoveAura(SPELL_RIFT_SHIELD);
            me->InterruptNonMeleeSpells(false);
            _achievement = false;
        }
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Talk(SAY_AGGRO);
        _EnterCombat();

        events.SetTimer(45000);
        events.ScheduleEvent(EVENT_ANOMALUS_SPARK, 5000);
        events.ScheduleEvent(EVENT_ANOMALUS_HEALTH, 1000);
        if (IsHeroic())
            events.ScheduleEvent(EVENT_ANOMALUS_ARCANE_ATTRACTION, 8000);
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_DEATH);
        _JustDied();
        DoCastSelf(SPELL_CLOSE_RIFTS, true);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch(eventId)
        {
            case EVENT_ANOMALUS_HEALTH:
            {
                bool healthCheck;

                if (_preNerf)
                {
                    healthCheck = (me->HealthBelowPct(75) && _riftCount == 0) ||
                        (me->HealthBelowPct(50) && _riftCount == 1) ||
                        (me->HealthBelowPct(25) && _riftCount == 2);
                }
                else
                    healthCheck = (me->HealthBelowPct(50) && _riftCount == 0);

                if (healthCheck)
                {
                    _riftCount++;
                    Talk(SAY_RIFT);
                    Talk(EMOTE_RIFT);

                    DoCastSelf(SPELL_CREATE_RIFT);
                    DoCastSelf(SPELL_RIFT_SHIELD, true);
                    me->m_Events.AddEvent(new ChargeRifts(me), me->m_Events.CalculateTime(1000));
                    events.DelayEvents(46000);
                    break;
                }
                events.Repeat(1000);
            }
            break;
            case EVENT_ANOMALUS_SPARK:
                DoCastVictim(SPELL_SPARK);
                events.Repeat(5000);
                break;
            case EVENT_ANOMALUS_ARCANE_ATTRACTION:
                if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_ARCANE_ATTRACTION);
                events.Repeat(15000);
                break;
            default:
                break;
        }
    }

private:
    bool _achievement;
    uint8 _riftCount;
    bool _preNerf;
};

class achievement_chaos_theory : public AchievementCriteriaScript
{
    public:
        achievement_chaos_theory() : AchievementCriteriaScript("achievement_chaos_theory") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            if (!target)
                return false;

            if (!target->IsAIEnabled)
                return false;

            return target->GetAI()->GetData(target->GetEntry());
        }
};

void AddSC_boss_anomalus()
{
    new CreatureAILoader<boss_anomalusAI>("boss_anomalus");
    new achievement_chaos_theory();
}
