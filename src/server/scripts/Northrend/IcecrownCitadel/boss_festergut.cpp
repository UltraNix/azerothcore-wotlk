#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellAuras.h"
#include "icecrown_citadel.h"
#include "SpellAuraEffects.h"
#include "Player.h"

enum FestergutTexts
{
    SAY_STINKY_DEAD,
    SAY_AGGRO,
    EMOTE_GAS_SPORE,
    EMOTE_WARN_GAS_SPORE,
    SAY_PUNGENT_BLIGHT,
    EMOTE_WARN_PUNGENT_BLIGHT,
    EMOTE_PUNGENT_BLIGHT,
    SAY_KILL,
    SAY_BERSERK,
    SAY_DEATH
};

enum FestergutSpells
{
    // Festergut
    SPELL_INHALE_BLIGHT         = 69165,
    SPELL_PUNGENT_BLIGHT        = 69195,
    SPELL_GASTRIC_BLOAT         = 72214,
    SPELL_GASTRIC_EXPLOSION     = 72227,
    SPELL_GAS_SPORE             = 69278,
    SPELL_VILE_GAS              = 69240,
    SPELL_INOCULATED            = 69291,
    SPELL_MALLABLE_GOO_H        = 72296,

    // Stinky
    SPELL_MORTAL_WOUND          = 71127,
    SPELL_DECIMATE              = 71123,
    SPELL_PLAGUE_STENCH         = 71805,
};

uint32 const gaseousBlight[3]        = {69157, 69162, 69164};
uint32 const gaseousBlightVisual[3]  = {69126, 69152, 69154};

#define DATA_INOCULATED_STACK 69291

enum FestergutEvents
{
    // Festergut
    EVENT_BERSERK               = 1,
    EVENT_INHALE_BLIGHT,
    EVENT_VILE_GAS,
    EVENT_GAS_SPORE,
    EVENT_GASTRIC_BLOAT,
    EVENT_FESTERGUT_GOO,

    // Stinky
    EVENT_DECIMATE,
    EVENT_MORTAL_WOUND,
};

struct boss_festergutAI : public BossAI
{
    boss_festergutAI(Creature* creature) : BossAI(creature, DATA_FESTERGUT)
    {
        _gasDummyGUID = 0;
    }

    void Reset() override
    {
        _maxInoculatedStack = 0;
        _inhaleCounter = 0;
        _Reset();
        events.Reset();
        if (Creature* gasDummy = me->FindNearestCreature(NPC_GAS_DUMMY, 100.0f, true))
        {
            _gasDummyGUID = gasDummy->GetGUID();
            for (uint32 i : gaseousBlightVisual)
                gasDummy->RemoveAurasDueToSpell(i);
        }
    }

    auto GetPutricide() const
    {
        return ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE));
    }

    void EnterCombat(Unit* attacker) override
    {
        if (!instance->CheckRequiredBosses(DATA_FESTERGUT, attacker->ToPlayer()))
        {
            EnterEvadeMode();
            instance->DoCastSpellOnPlayers(LIGHT_S_HAMMER_TELEPORT);
            return;
        }

        events.ScheduleEvent(EVENT_BERSERK, 5min);
        events.ScheduleEvent(EVENT_INHALE_BLIGHT, 25s, 30s);
        events.ScheduleEvent(EVENT_GAS_SPORE, 20s, 25s);
        events.ScheduleEvent(EVENT_VILE_GAS, 30s, 40s, 1);
        events.ScheduleEvent(EVENT_GASTRIC_BLOAT, 14s);
        if (IsHeroic())
            events.ScheduleEvent(EVENT_FESTERGUT_GOO, 15s, 20s);

        me->setActive(true);
        Talk(SAY_AGGRO);
        DoZoneInCombat();

        if (Creature* gasDummy = me->FindNearestCreature(NPC_GAS_DUMMY, 100.0f, true))
            _gasDummyGUID = gasDummy->GetGUID();
        if (Creature* professor = GetPutricide())
            professor->AI()->DoAction(ACTION_FESTERGUT_COMBAT);
    }

    void JustDied(Unit* /*killer*/) override
    {
        for (uint32 spellId : { sSpellMgr->GetSpellIdForDifficulty(SPELL_INOCULATED, me), sSpellMgr->GetSpellIdForDifficulty(SPELL_GASTRIC_BLOAT, me) })
            instance->DoRemoveAurasDueToSpellOnPlayers(spellId);
        _JustDied();
        Talk(SAY_DEATH);
        if (Creature* professor = GetPutricide())
            professor->AI()->DoAction(ACTION_FESTERGUT_DEATH);

        RemoveBlight();
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
        instance->SetBossState(DATA_FESTERGUT, FAIL);
    }

    void EnterEvadeMode() override
    {
        for (uint32 spellId : { sSpellMgr->GetSpellIdForDifficulty(SPELL_INOCULATED, me), sSpellMgr->GetSpellIdForDifficulty(SPELL_GASTRIC_BLOAT, me) })
            instance->DoRemoveAurasDueToSpellOnPlayers(spellId);
        ScriptedAI::EnterEvadeMode();
        if (Creature* professor = GetPutricide())
            professor->AI()->EnterEvadeMode();
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_KILL);
    }

    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
    {
        if (spell->Id == sSpellMgr->GetSpellIdForDifficulty(SPELL_PUNGENT_BLIGHT, me))
            target->RemoveAurasDueToSpell(sSpellMgr->GetSpellIdForDifficulty(SPELL_INOCULATED, me));
        else if (Player* p = target->ToPlayer())
        {
            // Gaseous Blight damage
            if ((spell->Id == 69159 || spell->Id == 70136 || spell->Id == 69161 || spell->Id == 70139 || spell->Id == 69163 || spell->Id == 70469) && p->GetQuestStatus(QUEST_RESIDUE_RENDEZVOUS_10) == QUEST_STATUS_INCOMPLETE ||
                (spell->Id == 70135 || spell->Id == 70138 || spell->Id == 70468 || spell->Id == 70137 || spell->Id == 70140 || spell->Id == 70470) && p->GetQuestStatus(QUEST_RESIDUE_RENDEZVOUS_25) == QUEST_STATUS_INCOMPLETE)
                p->CastSpell(p, SPELL_ORANGE_BLIGHT_RESIDUE, true);
        }
    }

    void RemoveBlight() const
    {
        if (Creature* gasDummy = ObjectAccessor::GetCreature(*me, _gasDummyGUID))
            for (uint8 i = 0; i < 3; ++i)
            {
                me->RemoveAurasDueToSpell(gaseousBlight[i]);
                gasDummy->RemoveAurasDueToSpell(gaseousBlightVisual[i]);
            }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() || !CheckInRoom())
            return;

        events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_BERSERK:
                    DoCastSelf(SPELL_BERSERK2, true);
                    Talk(SAY_BERSERK);
                    break;
                case EVENT_INHALE_BLIGHT:
                    RemoveBlight();
                    if (_inhaleCounter == 3)
                    {
                        Talk(EMOTE_WARN_PUNGENT_BLIGHT);
                        Talk(SAY_PUNGENT_BLIGHT);
                        DoCastSelf(SPELL_PUNGENT_BLIGHT);
                        _inhaleCounter = 0;
                        events.RescheduleEvent(EVENT_GAS_SPORE, 20s, 25s);
                    }
                    else
                    {
                        DoCastSelf(SPELL_INHALE_BLIGHT);
                        // just cast and dont bother with target, conditions will handle it
                        ++_inhaleCounter;
                        if (_inhaleCounter < 3)
                            me->CastSpell(me, gaseousBlight[_inhaleCounter], true, nullptr, nullptr, me->GetGUID());
                    }

                    events.Repeat(34s);
                    break;
                case EVENT_GAS_SPORE:
                    Talk(EMOTE_WARN_GAS_SPORE);
                    Talk(EMOTE_GAS_SPORE);
                    me->CastCustomSpell(SPELL_GAS_SPORE, SPELLVALUE_MAX_TARGETS, RAID_MODE<int32>(2, 3, 2, 3), me);
                    events.Repeat(40s, 45s);
                    events.DelayEventsToMax(20000, 1); // delay EVENT_VILE_GAS
                    break;
                case EVENT_VILE_GAS:
                {
                    std::list<Unit*> ranged, melee;
                    uint32 minTargets = RAID_MODE<uint32>(3, 8, 3, 8);
                    SelectTargetList(ranged, 25, SELECT_TARGET_RANDOM, -5.0f, true);
                    SelectTargetList(melee, 25, SELECT_TARGET_RANDOM, 5.0f, true);
                    while (ranged.size() < minTargets)
                    {
                        if (melee.empty())
                            break;

                        Unit* target = Trinity::Containers::SelectRandomContainerElement(melee);
                        ranged.push_back(target);
                        melee.remove(target);
                    }

                    if (!ranged.empty())
                    {
                        Trinity::Containers::RandomResize(ranged, RAID_MODE<uint32>(1, 3, 1, 3));
                        for (auto &itr : ranged)
                            DoCast(itr, SPELL_VILE_GAS);
                    }
                    events.ScheduleEvent(EVENT_VILE_GAS, 28s, 35s, 1);
                    break;
                }
                case EVENT_GASTRIC_BLOAT:
                    DoCastSelf(SPELL_GASTRIC_BLOAT, true);
                    break;
                case EVENT_FESTERGUT_GOO:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, NonTankTargetSelector(me)))
                        if (Creature* professor = GetPutricide())
                            professor->CastSpell(target, SPELL_MALLABLE_GOO_H, true);
                    events.Repeat(15s, 20s);
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type == DATA_INOCULATED_STACK && data > _maxInoculatedStack)
            _maxInoculatedStack = data;
    }

    uint32 GetData(uint32 type) const override
    {
        if (type == DATA_INOCULATED_STACK)
            return _maxInoculatedStack;

        return 0;
    }

    private:
        uint64 _gasDummyGUID;
        uint32 _maxInoculatedStack;
        uint32 _inhaleCounter;
};

class spell_festergut_pungent_blight_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_festergut_pungent_blight_SpellScript);

    bool Load() override
    {
        return GetCaster()->IsCreature();
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        Unit* caster = GetCaster();
        if (caster->GetTypeId() != TYPEID_UNIT)
            return;

        // Get Inhaled Blight id for our difficulty
        uint32 blightId = sSpellMgr->GetSpellIdForDifficulty(uint32(GetEffectValue()), caster);

        // ...and remove it
        caster->RemoveAurasDueToSpell(blightId);
        caster->ToCreature()->AI()->Talk(EMOTE_PUNGENT_BLIGHT);

        if (InstanceScript* inst = caster->GetInstanceScript())
            if (Creature* professor = ObjectAccessor::GetCreature(*caster, inst->GetData64(DATA_PROFESSOR_PUTRICIDE)))
                professor->AI()->DoAction(ACTION_FESTERGUT_GAS);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_festergut_pungent_blight_SpellScript::HandleScript, EFFECT_1, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_festergut_blighted_spores_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_festergut_blighted_spores_AuraScript);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_INOCULATED });
    }

    void ExtraEffect(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
    {
        if (Aura* a = aurEff->GetBase())
            if (a->GetDuration() > a->GetMaxDuration() - 1000) // this does not stack for different casters and previous is removed by new DoT, prevent it from giving inoculation in such case
                return;
        uint32 inoculatedId = sSpellMgr->GetSpellIdForDifficulty(SPELL_INOCULATED, GetTarget());
        uint8 inoculatedStack = 1;
        if (Aura* a = GetTarget()->GetAura(inoculatedId))
        {
            inoculatedStack += a->GetStackAmount();
            if (a->GetDuration() > a->GetMaxDuration() - 10000) // player may gain only one stack at a time, no matter how many spores explode near him
                return;
        }
        GetTarget()->CastSpell(GetTarget(), SPELL_INOCULATED, true);
        if (InstanceScript* instance = GetTarget()->GetInstanceScript())
            if (Creature* festergut = ObjectAccessor::GetCreature(*GetTarget(), instance->GetData64(DATA_FESTERGUT)))
                festergut->AI()->SetData(DATA_INOCULATED_STACK, inoculatedStack);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_festergut_blighted_spores_AuraScript::ExtraEffect, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_festergut_gastric_bloat_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_festergut_gastric_bloat_SpellScript);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_GASTRIC_EXPLOSION });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        Aura const* aura = GetHitUnit()->GetAura(GetSpellInfo()->Id);
        if (!(aura && aura->GetStackAmount() == 10))
            return;

        GetHitUnit()->RemoveAurasDueToSpell(GetSpellInfo()->Id);
        GetHitUnit()->CastSpell(GetHitUnit(), SPELL_GASTRIC_EXPLOSION, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_festergut_gastric_bloat_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class achievement_flu_shot_shortage : public AchievementCriteriaScript
{
    public:
        achievement_flu_shot_shortage() : AchievementCriteriaScript("achievement_flu_shot_shortage") { }

        bool OnCheck(Player* /*source*/, Unit* target) override
        {
            if (target && target->IsCreature() && target->IsAIEnabled)
                return target->ToCreature()->AI()->GetData(DATA_INOCULATED_STACK) < 3;

            return false;
        }
};

struct npc_stinky_iccAI : public ScriptedAI
{
    npc_stinky_iccAI(Creature* creature) : ScriptedAI(creature) {}

    void Reset() override
    {
        _events.Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        me->setActive(true);
        DoCastSelf(SPELL_PLAGUE_STENCH, true);
        _events.ScheduleEvent(EVENT_DECIMATE, 20s, 25s);
        _events.ScheduleEvent(EVENT_MORTAL_WOUND, 1500ms, 2500ms);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_DECIMATE:
                    DoCastSelf(SPELL_DECIMATE);
                    _events.Repeat(20s, 25s);
                    break;
                case EVENT_MORTAL_WOUND:
                    DoCastVictim(SPELL_MORTAL_WOUND);
                    _events.Repeat(1500ms, 2500ms);
                    break;
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (InstanceScript* _instance = me->GetInstanceScript())
            if (Creature* festergut = ObjectAccessor::GetCreature(*me, _instance->GetData64(DATA_FESTERGUT)))
                if (festergut->IsAlive())
                    festergut->AI()->Talk(SAY_STINKY_DEAD);
    }

    private:
        EventMap _events;
};

void AddSC_boss_festergut()
{
    new CreatureAILoader<boss_festergutAI>("boss_festergut");
    new SpellScriptLoaderEx<spell_festergut_pungent_blight_SpellScript>("spell_festergut_pungent_blight");
    new AuraScriptLoaderEx<spell_festergut_blighted_spores_AuraScript>("spell_festergut_blighted_spores");
    new SpellScriptLoaderEx<spell_festergut_gastric_bloat_SpellScript>("spell_festergut_gastric_bloat");
    new achievement_flu_shot_shortage();

    new CreatureAILoader<npc_stinky_iccAI>("npc_stinky_icc");
}
