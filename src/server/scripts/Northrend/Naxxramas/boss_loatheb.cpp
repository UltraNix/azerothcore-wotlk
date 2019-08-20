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
    SPELL_FUNGAL_CREEP                 = 29232,
    SPELL_BERSERK                      = 26662
};

enum Events
{
    EVENT_SPELL_NECROTIC_AURA          = 1,
    EVENT_SPELL_DEATHBLOOM,
    EVENT_SPELL_INEVITABLE_DOOM,
    EVENT_SPELL_BERSERK,
    EVENT_SPELL_SPORE,
    EVENT_AURA_REMOVED,
    EVENT_AURA_FADING
};

enum Texts
{
    SAY_NECROTIC_AURA_APPLIED,
    SAY_NECROTIC_AURA_REMOVED,
    SAY_NECROTIC_AURA_FADING
};

struct boss_loathebAI : public BossAI
{
    boss_loathebAI(Creature* creature) : BossAI(creature, EVENT_LOATHEB) {}

    void Reset() override
    {
        _fightTimer = 0;
        _Reset();
        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_FUNGAL_CREEP);
        instance->SetData(EVENT_LOATHEB, NOT_STARTED);
        if (GameObject* go = me->GetMap()->GetGameObject(instance->GetData64(DATA_LOATHEB_GATE)))
            go->SetGoState(GO_STATE_ACTIVE);
    }

    void JustSummoned(Creature* summon) override
    {
        BossAI::JustSummoned(summon);
        summon->SetInCombatWithZone();
    }

    void SummonedCreatureDies(Creature* who, Unit* killer) override
    {
        BossAI::SummonedCreatureDies(who, killer);
        instance->SetData(DATA_SPORE_KILLED, 0);
    }

    void KilledUnit(Unit* who)
    {
        if (who->IsPlayer())
            instance->SetData(DATA_IMMORTAL_FAIL, 0);
    }

    void EnterCombat(Unit* /*who*/)
    {
        me->SetHealth(me->GetMaxHealth());
        _fightTimer = getMSTime();
        _EnterCombat();
        instance->SetData(EVENT_LOATHEB, IN_PROGRESS);
        if (GameObject* go = me->GetMap()->GetGameObject(instance->GetData64(DATA_LOATHEB_GATE)))
            go->SetGoState(GO_STATE_READY);

        events.ScheduleEvent(EVENT_SPELL_NECROTIC_AURA, 12000);
        events.ScheduleEvent(EVENT_SPELL_DEATHBLOOM, 5000);
        events.ScheduleEvent(EVENT_SPELL_SPORE, 18000);

        events.ScheduleEvent(EVENT_SPELL_INEVITABLE_DOOM, sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS) ? RAID_MODE(120000, 20000) : 120000);
        events.ScheduleEvent(EVENT_SPELL_BERSERK, sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS) ? RAID_MODE(720000, 480000) : 720000);
    }

    void JustDied(Unit* killer) override
    {
        _JustDied();
        instance->SetData(EVENT_LOATHEB, DONE);

        if (Map* map = me->GetMap())
            CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry, map->GetDifficulty(), "", 15000, _fightTimer);
    }

    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return me->GetDistance(me->GetHomePosition()) > 50.0f;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (auto eventId = events.ExecuteEvent())
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
                    DoCastSelf(SPELL_NECROTIC_AURA, true);
                    events.Repeat(20000);
                    break;
                case EVENT_SPELL_DEATHBLOOM:
                    DoCastSelf(RAID_MODE(SPELL_DEATHBLOOM_10, SPELL_DEATHBLOOM_25));
                    events.Repeat(sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS) ? (me->GetMap()->Is25ManRaid() ? 20000 : 30000) : 30000);
                    break;
                case EVENT_SPELL_SPORE:
                    DoCastSelf(SPELL_SUMMON_SPORE, true);
                    events.Repeat(RAID_MODE(36000, 15000));
                    break;
                case EVENT_SPELL_INEVITABLE_DOOM:
                    DoCastSelf(RAID_MODE(SPELL_INEVITABLE_DOOM_10, SPELL_INEVITABLE_DOOM_25));
                    if (sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS))
                        me->GetMap()->Is25ManRaid() ? events.RepeatEvent(20000) : events.RepeatEvent(events.GetTimer() < 5 * MINUTE * IN_MILLISECONDS ? 30000 : 15000);
                    else
                        events.Repeat(events.GetTimer() < 5 * MINUTE*IN_MILLISECONDS ? 30000 : 15000);
                    break;
                case EVENT_SPELL_BERSERK:
                    DoCastSelf(SPELL_BERSERK, true);
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
        }

        DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea();
    }
private:
    uint32 _fightTimer;
};

// 29232 - Fungal Creep
class spell_loatheb_fungal_creep_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_loatheb_fungal_creep_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.sort(Trinity::ObjectDistanceOrderPred(GetCaster()));
        targets.resize(5);
        _targets = targets;
    }

    // use the same target for second and third effect
    void FilterTargetsSubsequent(std::list<WorldObject*>& targets)
    {
        if (_targets.empty())
            return;

        targets.clear();
        targets = _targets;
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_loatheb_fungal_creep_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_loatheb_fungal_creep_SpellScript::FilterTargetsSubsequent, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_loatheb_fungal_creep_SpellScript::FilterTargetsSubsequent, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
    }

    std::list<WorldObject*> _targets;
};

void AddSC_boss_loatheb()
{
    new CreatureAILoader<boss_loathebAI>("boss_loatheb");
    new SpellScriptLoaderEx<spell_loatheb_fungal_creep_SpellScript>("spell_loatheb_fungal_creep");
}
