#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "forge_of_souls.h"
#include "Spell.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "World.h"

enum DevourerTexts
{
    SAY_FACE_AGGRO                  = 0,
    SAY_FACE_ANGER_SLAY,
    SAY_FACE_SORROW_SLAY,
    SAY_FACE_DESIRE_SLAY,
    SAY_FACE_DEATH,
    EMOTE_MIRRORED_SOUL,
    EMOTE_UNLEASH_SOUL,
    SAY_FACE_UNLEASH_SOUL,
    EMOTE_WAILING_SOUL,
    SAY_FACE_WAILING_SOUL
};

enum DevourerSpells
{
    SPELL_PHANTOM_BLAST             = 68982,
    SPELL_PHANTOM_BLAST_H           = 70322,
    SPELL_MIRRORED_SOUL             = 69051,
    SPELL_WELL_OF_SOULS             = 68820,
    SPELL_UNLEASHED_SOULS           = 68939,

    SPELL_WAILING_SOULS             = 68899,
    SPELL_WAILING_SOULS_TARGETING   = 68912,
    SPELL_WAILING_SOULS_DMG         = 68873,
};

enum DevourerEvents
{
    EVENT_PHANTOM_BLAST             = 1,
    EVENT_MIRRORED_SOUL,
    EVENT_WELL_OF_SOULS,
    EVENT_UNLEASHED_SOULS,
    EVENT_WAILING_SOULS,
    EVENT_KILL_TALK
};

enum DevourerDisplayIds
{
    DISPLAY_ANGER                   = 30148,
    DISPLAY_SORROW                  = 30149,
    DISPLAY_DESIRE                  = 30150
};

enum DevourerMisc
{
    NPC_CRUCIBLE_OF_SOULS           = 37094,
    QUEST_TEMPERING_THE_BLADE_A     = 24476,
    QUEST_TEMPERING_THE_BLADE_H     = 24560
};

struct boss_devourer_of_soulsAI : public BossAI
{
    boss_devourer_of_soulsAI(Creature* creature) : BossAI(creature, DATA_DEVOURER) {}

    void Reset() override
    {
        _Reset();
        me->DisableRotate(false);
        _threeFaced = true;
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == DATA_THREE_FACED)
            return _threeFaced;

        return 0;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        Talk(SAY_FACE_AGGRO);
        events.ScheduleEvent(EVENT_PHANTOM_BLAST, 5000);
        events.ScheduleEvent(EVENT_MIRRORED_SOUL, 9000);
        events.ScheduleEvent(EVENT_WELL_OF_SOULS, urand(6000, 8000));
        events.ScheduleEvent(EVENT_UNLEASHED_SOULS, urand(18000, 20000));
        events.ScheduleEvent(EVENT_WAILING_SOULS, urand(60000, 70000));

        // Suport for Quest Tempering the Blade
        Map::PlayerList const& players = me->GetMap()->GetPlayers();
        for (auto itr = players.begin(); itr != players.end(); ++itr)
        {
            Player* player = itr->GetSource();

            if (!player)
                return;

            if ((player->GetTeamId() == TEAM_ALLIANCE && player->GetQuestStatus(QUEST_TEMPERING_THE_BLADE_A) == QUEST_STATUS_INCOMPLETE) ||
                (player->GetTeamId() == TEAM_HORDE && player->GetQuestStatus(QUEST_TEMPERING_THE_BLADE_H) == QUEST_STATUS_INCOMPLETE))
            {
                if (!me->FindNearestCreature(NPC_CRUCIBLE_OF_SOULS, 100.0f))
                    me->SummonCreature(NPC_CRUCIBLE_OF_SOULS, 5672.29f, 2520.69f, 713.44f, 0.96f);
            }
        }
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        switch (spell->Id)
        {
            case SPELL_PHANTOM_BLAST_H:
                _threeFaced = false;
                break;
            case SPELL_WAILING_SOULS_TARGETING:
                me->SetOrientation(me->GetAngle(target));
                me->SetControlled(true, UNIT_STATE_ROOT);
                me->DisableRotate(true);
                me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                me->SetReactState(REACT_PASSIVE);
                me->GetMotionMaster()->Clear(false);
                me->GetMotionMaster()->MoveIdle();
                me->StopMovingOnCurrentPos();

                me->SetFacingToObject(target);
                me->SendMovementFlagUpdate();
                me->CastSpell(me, SPELL_WAILING_SOULS, false);
                break;
        }
    }

    bool CanAIAttack(const Unit* target) const override
    {
        return target->GetPositionZ() > 706.5f;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (auto spell = me->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
        {
            if (spell->m_spellInfo->Id == SPELL_MIRRORED_SOUL)
            {
                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_PHANTOM_BLAST:
                            DoCastVictim(SPELL_PHANTOM_BLAST);
                            events.Repeat(5000);
                            break;
                        case EVENT_WELL_OF_SOULS:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                                DoCast(target, SPELL_WELL_OF_SOULS);
                            events.Repeat(urand(25000, 30000));
                            events.DelayEventsToMax(4000, 0);
                            break;
                        default:
                            events.Repeat(1000);
                            break;
                    }
                }

                if (!me->GetCurrentSpell(CURRENT_GENERIC_SPELL))
                {
                    me->ClearUnitState(UNIT_STATE_CASTING);
                    DoMeleeAttackIfReady();
                    me->AddUnitState(UNIT_STATE_CASTING);
                }

                return;
            }
        }

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_PHANTOM_BLAST:
                    DoCastVictim(SPELL_PHANTOM_BLAST);
                    events.Repeat(5000);
                    break;
                case EVENT_MIRRORED_SOUL:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 90.0f, true))
                    {
                        DoCast(target, SPELL_MIRRORED_SOUL);
                        me->setAttackTimer(BASE_ATTACK, 1500);
                        Talk(EMOTE_MIRRORED_SOUL);
                    }

                    events.Repeat(urand(15000, 25000));
                    break;
                case EVENT_WELL_OF_SOULS:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_WELL_OF_SOULS);
                    events.Repeat(urand(25000, 30000));
                    events.DelayEventsToMax(4000, 0);
                    break;
                case EVENT_UNLEASHED_SOULS:
                    DoCastSelf(SPELL_UNLEASHED_SOULS);
                    Talk(SAY_FACE_UNLEASH_SOUL);
                    Talk(EMOTE_UNLEASH_SOUL);
                    events.Repeat(urand(30000, 40000));
                    events.DelayEventsToMax(5000, 0);
                    me->setAttackTimer(BASE_ATTACK, 5500);
                    break;
                case EVENT_WAILING_SOULS:
                    Talk(SAY_FACE_WAILING_SOUL);
                    Talk(EMOTE_WAILING_SOUL);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
                        me->CastCustomSpell(SPELL_WAILING_SOULS_TARGETING, SPELLVALUE_MAX_TARGETS, 1, target, false);
                    events.Repeat(80000);
                    events.DelayEventsToMax(20000, 0);
                    break;
                default:
                    break;
            }
        }

        if (!me->HasReactState(REACT_PASSIVE))
            DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_FACE_DEATH);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            int32 textId = 0;
            switch (me->GetDisplayId())
            {
                case DISPLAY_ANGER:
                    textId = SAY_FACE_ANGER_SLAY;
                    break;
                case DISPLAY_SORROW:
                    textId = SAY_FACE_SORROW_SLAY;
                    break;
                case DISPLAY_DESIRE:
                    textId = SAY_FACE_DESIRE_SLAY;
                    break;
                default:
                    break;
            }

            if (textId)
                Talk(textId);

            events.ScheduleEvent(EVENT_KILL_TALK, 6000);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() != NPC_CRUCIBLE_OF_SOULS)
            summons.Summon(summon);

        if (summon->GetEntry() == 36595)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
            {
                summon->AddThreat(target, 100000.0f);
                if (summon->IsAIEnabled)
                    summon->AI()->AttackStart(target);
            }
        }
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade();
    }

private:
    bool _threeFaced;
};

class spell_wailing_souls_periodic_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_wailing_souls_periodic_AuraScript)

    bool _left;

    bool Load() override
    {
        _left = RAND(true, false);
        return true;
    }

    void HandlePeriodicTick(AuraEffect const* aurEff)
    {
        PreventDefaultAction();
        if (Unit* target = GetTarget())
        {
            if (aurEff->GetTickNumber() < 30 && aurEff->GetTickNumber() > 1)
            {
                target->GetMotionMaster()->MoveRotate(500 * 60, _left ? ROTATE_DIRECTION_LEFT : ROTATE_DIRECTION_RIGHT);
                target->CastSpell(target, SPELL_WAILING_SOULS_DMG, true);
            }
            else if (aurEff->GetTickNumber() == 33)
            {
                target->SetControlled(false, UNIT_STATE_ROOT);
                target->DisableRotate(false);
                if (target->GetTypeId() == TYPEID_UNIT)
                    target->ToCreature()->SetReactState(REACT_AGGRESSIVE);
                if (target->GetVictim())
                {
                    target->SetTarget(target->GetVictim()->GetGUID());
                    target->GetMotionMaster()->MoveChase(target->GetVictim());
                }
            }
            else if (aurEff->GetTickNumber() >= 34)
                Remove(AURA_REMOVE_BY_EXPIRE);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_wailing_souls_periodic_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class achievement_three_faced : public AchievementCriteriaScript
{
public:
    achievement_three_faced() : AchievementCriteriaScript("achievement_three_faced") { }

    bool OnCheck(Player* /*player*/, Unit* target) override
    {
        if (!target)
            return false;

        if (Creature* devourer = target->ToCreature())
            if (devourer->IsAIEnabled)
                if (devourer->AI()->GetData(DATA_THREE_FACED))
                    return true;

        return false;
    }
};

void AddSC_boss_devourer_of_souls()
{
    new CreatureAILoader<boss_devourer_of_soulsAI>("boss_devourer_of_souls");
    new AuraScriptLoaderEx<spell_wailing_souls_periodic_AuraScript>("spell_wailing_souls_periodic");
    new achievement_three_faced();
}