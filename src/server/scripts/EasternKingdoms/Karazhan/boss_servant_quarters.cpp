/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "karazhan.h"


enum ServantQuartersSpells
{
    SPELL_SNEAK                 = 22766, // added in creature_template_addon
    SPELL_ACIDIC_FANG           = 29901,
    SPELL_HYAKISS_WEB           = 29896,

    SPELL_DIVE                  = 29903,
    SPELL_SONIC_BURST           = 29904,
    SPELL_WING_BUFFET           = 29905,
    SPELL_FEAR                  = 29321,

    SPELL_RAVAGE                = 29906
};

enum ServantQuertersEvents
{
    EVENT_ACIDIC_FANG           = 1,
    EVENT_HYAKISS_WEB,

    EVENT_DIVE                  = 10,
    EVENT_SONIC_BURST,
    EVENT_WING_BUFFET,
    EVENT_FEAR,

    EVENT_RAVAGE                = 20,
};

enum ServantQuartersMisc
{
    SAY_ENTER
};

struct boss_servant_quartersAI : public BossAI
{
    boss_servant_quartersAI(Creature* creature) : BossAI(creature, BOSS_SERVANT_QUARTERS) { }

    void Reset() override
    {
        _Reset();
        if (instance->GetData(DATA_SELECTED_RARE) != me->GetEntry())
        {
            me->DespawnOrUnsummon(1ms);
            return;
        }

        SetBossAttackable(static_cast<bool>(instance->GetData(DATA_SERVANT_QUARTERS_AGGRO)));
    }

    void SetBossAttackable(bool apply)
    {
        if (apply)
        {
            me->SetVisible(true);
            me->SetAggressive();
            me->RestoreFaction();
        }
        else
        {
            me->SetVisible(false);
            me->SetPassive();
            me->setFaction(35);
        }
    }

    void DoAction(int32 /*actionId*/) override
    {
        if (!me->IsVisible())
        {
            Talk(SAY_ENTER);
            SetBossAttackable(true);
        }
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        if (me->GetEntry() == NPC_HYAKISS_THE_LURKER)
        {
            events.ScheduleEvent(EVENT_ACIDIC_FANG, 5s);
            events.ScheduleEvent(EVENT_HYAKISS_WEB, 9s);
        }
        else if (me->GetEntry() == NPC_SHADIKITH_THE_GLIDER)
        {
            events.ScheduleEvent(EVENT_SONIC_BURST, 4s);
            events.ScheduleEvent(EVENT_WING_BUFFET, 7s);
            events.ScheduleEvent(EVENT_DIVE, 10s);
        }
        else
            events.ScheduleEvent(EVENT_RAVAGE, 3s);
    }

    void MovementInform(uint32 type, uint32 point) override
    {
        if (type == POINT_MOTION_TYPE && point == EVENT_CHARGE)
            events.ScheduleEvent(EVENT_FEAR, 0s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_ACIDIC_FANG:
                DoCastVictim(SPELL_ACIDIC_FANG);
                events.Repeat(12s, 18s);
                break;
            case EVENT_HYAKISS_WEB:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f))
                    DoCast(target, SPELL_HYAKISS_WEB);
                events.Repeat(15s);
                break;
            case EVENT_SONIC_BURST:
                DoCastSelf(SPELL_SONIC_BURST);
                events.Repeat(12s, 18s);
                break;
            case EVENT_WING_BUFFET:
                DoCastSelf(SPELL_WING_BUFFET);
                events.Repeat(12s, 18s);
                break;
            case EVENT_DIVE:
                if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 40.0f, true))
                    DoCast(target, SPELL_DIVE);
                events.Repeat(20s);
                break;
            case EVENT_FEAR:
                DoCastVictim(SPELL_FEAR);
                break;
            case EVENT_RAVAGE:
                DoCastVictim(SPELL_RAVAGE);
                events.Repeat(10.5s);
                break;
            default:
                break;
        }
    }
};

void AddSC_boss_servant_quarters()
{
    new CreatureAILoader<boss_servant_quartersAI>("boss_servant_quarters");
}
