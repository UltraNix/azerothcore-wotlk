/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "naxxramas.h"
#include "SpellScript.h"

enum Spells
{
    SPELL_NECROTIC_AURA                = 55593,
    SPELL_SUMMON_SPORE                 = 29234,
    SPELL_DEATHBLOOM_10                = 29865,
    SPELL_DEATHBLOOM_25                = 55053,
    SPELL_INEVITABLE_DOOM_10           = 29204,
    SPELL_INEVITABLE_DOOM_25           = 55052,
    SPELL_BERSERK                      = 26662
};

enum Events
{
    EVENT_SPELL_NECROTIC_AURA          = 1,
    EVENT_SPELL_DEATHBLOOM,
    EVENT_SPELL_INEVITABLE_DOOM,
    EVENT_SPELL_BERSERK,
    EVENT_AURA_REMOVED,
    EVENT_AURA_FADING
};

enum Texts
{
    SAY_NECROTIC_AURA_APPLIED,
    SAY_NECROTIC_AURA_REMOVED,
    SAY_NECROTIC_AURA_FADING
};

struct boss_loathebAI : public ScriptedAI
{
    boss_loathebAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = me->GetInstanceScript();
    }

    InstanceScript* pInstance;
    EventMap events;

    void Reset()
    {
        events.Reset();

        if (pInstance)
        {
            pInstance->SetData(EVENT_LOATHEB, NOT_STARTED);
            if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetData64(DATA_LOATHEB_GATE)))
                go->SetGoState(GO_STATE_ACTIVE);
        }
    }

    void JustSummoned(Creature* cr) { cr->SetInCombatWithZone(); }

    void SummonedCreatureDies(Creature* cr, Unit*)
    {
        if (pInstance)
            pInstance->SetData(DATA_SPORE_KILLED, 0);
    }

    void KilledUnit(Unit* who)
    {
        if (who->GetTypeId() == TYPEID_PLAYER && pInstance)
            pInstance->SetData(DATA_IMMORTAL_FAIL, 0);
    }

    void EnterCombat(Unit *who)
    {
        if (pInstance)
        {
            pInstance->SetData(EVENT_LOATHEB, IN_PROGRESS);
            if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetData64(DATA_LOATHEB_GATE)))
                go->SetGoState(GO_STATE_READY);
        }

        me->SetInCombatWithZone();
        events.ScheduleEvent(EVENT_SPELL_NECROTIC_AURA, 0);
        events.ScheduleEvent(EVENT_SPELL_DEATHBLOOM, 25000);
        events.ScheduleEvent(EVENT_SPELL_INEVITABLE_DOOM, 120000);
        events.ScheduleEvent(EVENT_SPELL_BERSERK, 720000);
    }

    void JustDied(Unit* Killer)
    {
        if (pInstance)
            pInstance->SetData(EVENT_LOATHEB, DONE);
    }

    void UpdateAI(uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);
        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_SPELL_NECROTIC_AURA:
                    Talk(SAY_NECROTIC_AURA_APPLIED);
                    if (int32 duration = sSpellMgr->GetSpellInfo(SPELL_NECROTIC_AURA)->GetDuration())
                    {
                        events.ScheduleEvent(EVENT_AURA_FADING, duration - 4000);
                        events.ScheduleEvent(EVENT_AURA_REMOVED, duration);
                    }
                    me->CastSpell(me, SPELL_NECROTIC_AURA, true);
                    events.Repeat(20000);
                    break;
                case EVENT_SPELL_DEATHBLOOM:
                    me->CastSpell(me, SPELL_SUMMON_SPORE, true);
                    me->CastSpell(me, RAID_MODE(SPELL_DEATHBLOOM_10, SPELL_DEATHBLOOM_25), false);
                    events.Repeat(30000);
                    break;
                case EVENT_SPELL_INEVITABLE_DOOM:
                    me->CastSpell(me, RAID_MODE(SPELL_INEVITABLE_DOOM_10, SPELL_INEVITABLE_DOOM_25), false);
                    events.Repeat(events.GetTimer() < 5 * MINUTE*IN_MILLISECONDS ? 30000 : 15000);
                    break;
                case EVENT_SPELL_BERSERK:
                    me->CastSpell(me, SPELL_BERSERK, true);
                    break;
                case EVENT_AURA_FADING:
                    Talk(SAY_NECROTIC_AURA_FADING);
                    break;
                case EVENT_AURA_REMOVED:
                    Talk(SAY_NECROTIC_AURA_REMOVED);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }
};

void AddSC_boss_loatheb()
{
    new CreatureAILoader<boss_loathebAI>("boss_loatheb");
}
