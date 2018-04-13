#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellAuras.h"
#include "GridNotifiers.h"
#include "icecrown_citadel.h"

enum RotfaceTexts
{
    SAY_PRECIOUS_DIES,
    SAY_AGGRO,
    EMOTE_SLIME_SPRAY,
    SAY_SLIME_SPRAY,
    SAY_UNSTABLE_EXPLOSION                  = 5,
    SAY_KILL,
    SAY_BERSERK,
    SAY_DEATH,
    EMOTE_MUTATED_INFECTION,

    EMOTE_UNSTABLE_2                        = 0,
    EMOTE_UNSTABLE_3,
    EMOTE_UNSTABLE_4,
    EMOTE_UNSTABLE_EXPLOSION,

    SAY_ROTFACE_OOZE_FLOOD                  = 2, // professor

    EMOTE_PRECIOUS_ZOMBIES                  = 0,
};

enum Spells
{
    // Rotface
    SPELL_SLIME_SPRAY                       = 69508,    // every 20 seconds
    SPELL_SUMMON_SPRAY_STALKER              = 70882,
    SPELL_MUTATED_INFECTION                 = 69674,    // hastens every 1:30
    SPELL_VILE_GAS_TRIGGER_SUMMON           = 72287,

    // Ooze Flood
    SPELL_OOZE_FLOOD_VISUAL                 = 69785,
    SPELL_OOZE_FLOOD_PERIODIC               = 69788,

    // Oozes
    SPELL_LITTLE_OOZE_COMBINE               = 69537,    // combine 2 Small Oozes
    SPELL_LARGE_OOZE_COMBINE                = 69552,    // combine 2 Large Oozes
    SPELL_LARGE_OOZE_BUFF_COMBINE           = 69611,    // combine Large and Small Ooze
    SPELL_OOZE_MERGE                        = 69889,    // 2 Small Oozes summon a Large Ooze
    SPELL_WEAK_RADIATING_OOZE               = 69750,    // passive damage aura - small
    SPELL_RADIATING_OOZE                    = 69760,    // passive damage aura - large
    SPELL_UNSTABLE_OOZE                     = 69558,    // damage boost and counter for explosion
    SPELL_GREEN_ABOMINATION_HITTIN__YA_PROC = 70001,    // prevents getting hit by infection
    SPELL_UNSTABLE_OOZE_EXPLOSION           = 69839,
    SPELL_STICKY_OOZE                       = 69774,
    SPELL_UNSTABLE_OOZE_EXPLOSION_TRIGGER   = 69832,
    SPELL_VERTEX_COLOR_PINK                 = 53213,
    SPELL_VERTEX_COLOR_BRIGHT_RED           = 69844,
    SPELL_VERTEX_COLOR_DARK_RED             = 44773,

    // Precious
    SPELL_MORTAL_WOUND                      = 71127,
    SPELL_DECIMATE                          = 71123,
    SPELL_AWAKEN_PLAGUED_ZOMBIES            = 71159,

    // Professor Putricide
    SPELL_VILE_GAS_H                        = 72272,
    SPELL_VILE_GAS_TRIGGER                  = 72285
};

enum Events
{
    EVENT_NONE,
    // Rotface
    EVENT_UNROOT,
    EVENT_SLIME_SPRAY,
    EVENT_HASTEN_INFECTIONS,
    EVENT_MUTATED_INFECTION,
    EVENT_ROTFACE_OOZE_FLOOD,
    EVENT_ROTFACE_VILE_GAS,

    EVENT_STICKY_OOZE,

    // Precious
    EVENT_DECIMATE,
    EVENT_MORTAL_WOUND,
    EVENT_SUMMON_ZOMBIES,
};

uint32 const oozeFloodSpells[4] = {69782, 69796, 69798, 69801};
uint32 getOozeFloodSpellIndex(uint32 id)
{
    switch (id)
    {
        case 69782: return 0;
        case 69796: return 1;
        case 69798: return 2;
        case 69801: return 3;
    }
    return 0;
}

struct RotfaceHeightCheck
{
    RotfaceHeightCheck() {}

    bool operator()(Creature* stalker) const
    {
        return stalker->GetPositionZ() < 365.0f;
    }
};

class StartMovementEventRotface : public BasicEvent
{
    public:
        StartMovementEventRotface(Creature* owner) : _owner(owner) {}

        bool Execute(uint64 /*time*/, uint32 /*diff*/)
        {
            _owner->SetAggressive();
            if (!_owner->getThreatManager().isThreatListEmpty())
                if (Unit* target = _owner->SelectVictim())
                    _owner->AI()->AttackStart(target);
            if (!_owner->GetVictim())
                if (Unit* target = _owner->AI()->SelectTarget(SELECT_TARGET_NEAREST, 0))
                    _owner->AI()->AttackStart(target);
            _owner->AI()->DoZoneInCombat();
            return true;
        }

    private:
        Creature* _owner;
};

struct boss_rotfaceAI : public BossAI
{
    boss_rotfaceAI(Creature* creature) : BossAI(creature, DATA_ROTFACE) { }

    void Reset() override
    {
        _infectionCooldown = 14000;
        memset(&_oozeFloodDummyGUIDs, 0, sizeof(_oozeFloodDummyGUIDs));
        _oozeFloodStage = 0;
        _Reset();
        events.Reset();
    }

    void EnterCombat(Unit* attacker) override
    {
        if (!instance->CheckRequiredBosses(DATA_ROTFACE, attacker->ToPlayer()))
        {
            EnterEvadeMode();
            instance->DoCastSpellOnPlayers(LIGHT_S_HAMMER_TELEPORT);
            return;
        }

        // schedule events
        events.Reset();
        events.ScheduleEvent(EVENT_SLIME_SPRAY, 20s);
        events.ScheduleEvent(EVENT_HASTEN_INFECTIONS, 90s);
        events.ScheduleEvent(EVENT_MUTATED_INFECTION, 14s);
        events.ScheduleEvent(EVENT_ROTFACE_OOZE_FLOOD, 8s);
        if (IsHeroic())
            events.ScheduleEvent(EVENT_ROTFACE_VILE_GAS, 15s, 20s);

        DoCastSelf(SPELL_GREEN_ABOMINATION_HITTIN__YA_PROC, true);
        me->setActive(true);
        Talk(SAY_AGGRO);
        DoZoneInCombat();

        if (Creature* professor = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
            professor->AI()->DoAction(ACTION_ROTFACE_COMBAT);

        instance->SetData(DATA_OOZE_DANCE_ACHIEVEMENT, uint32(true)); // reset

                                                                        // randomize ooze flood
        _oozeFloodStage = urand(0, 3);
        std::list<Creature*> list;
        GetCreatureListWithEntryInGrid(list, me, NPC_PUDDLE_STALKER, 60.0f);
        list.remove_if(RotfaceHeightCheck()); // remove from the list all on the ground
        for (auto &itr : list)
        {
            uint32 index = me->GetHomePosition().GetAngle(itr) / (M_PI / 2.0f);
            if (index > 3) index = 3;
            if (_oozeFloodDummyGUIDs[index][0])
                _oozeFloodDummyGUIDs[index][1] = itr->GetGUID();
            else
                _oozeFloodDummyGUIDs[index][0] = itr->GetGUID();
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        instance->DoRemoveAurasDueToSpellOnPlayers(sSpellMgr->GetSpellIdForDifficulty(SPELL_MUTATED_INFECTION, me));
        _JustDied();
        Talk(SAY_DEATH);
        if (Creature* professor = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
            professor->AI()->DoAction(ACTION_ROTFACE_DEATH);
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
        instance->SetBossState(DATA_ROTFACE, FAIL);
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_VILE_GAS_STALKER)
            if (Creature* professor = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
                professor->CastSpell(summon, SPELL_VILE_GAS_H, true);

        if (me->IsAlive() && me->IsInCombat() && !me->IsInEvadeMode())
            summons.Summon(summon);
        else
            summon->DespawnOrUnsummon(1);
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
            Talk(SAY_KILL);
    }

    void EnterEvadeMode() override
    {
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        ScriptedAI::EnterEvadeMode();
        if (Creature* professor = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
            professor->AI()->EnterEvadeMode();
    }

    void SpellHitTarget(Unit* target, SpellInfo const* spell) override
    {
        switch (spell->Id)
        {
            case SPELL_SLIME_SPRAY:
                Talk(SAY_SLIME_SPRAY);
                break;
            case 69507: // Slime Spray damage
            case 71213:
            case 73189:
            case 73190:
                if (Player* p = target->ToPlayer())
                    if (p->GetQuestStatus(QUEST_RESIDUE_RENDEZVOUS_10) == QUEST_STATUS_INCOMPLETE || p->GetQuestStatus(QUEST_RESIDUE_RENDEZVOUS_25) == QUEST_STATUS_INCOMPLETE)
                        p->CastSpell(p, SPELL_GREEN_BLIGHT_RESIDUE, true);
                break;
            case 69782:
            case 69796:
            case 69798:
            case 69801:
                {
                    uint32 index = getOozeFloodSpellIndex(spell->Id);
                    if (target->GetGUID() == _oozeFloodDummyGUIDs[index][0] || target->GetGUID() == _oozeFloodDummyGUIDs[index][1])
                        target->CastSpell((Unit*)nullptr, spell->Effects[0].CalcValue(), false);
                }
                break;
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
                case EVENT_UNROOT:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    me->DisableRotate(false);
                    break;
                case EVENT_SLIME_SPRAY:
                    me->CastCustomSpell(SPELL_SUMMON_SPRAY_STALKER, SPELLVALUE_MAX_TARGETS, 1, me, true);
                    if (Creature* stalker = me->FindNearestCreature(37986, 100.0f))
                    {
                        Talk(EMOTE_SLIME_SPRAY);
                        me->SetOrientation(me->GetAngle(stalker));
                        me->SetControlled(true, UNIT_STATE_ROOT);
                        me->DisableRotate(true);
                        me->SetFacingTo(me->GetAngle(stalker));
                        me->SendMovementFlagUpdate();
                        DoCastAOE(SPELL_SLIME_SPRAY);
                    }
                    events.DelayEvents(1ms);
                    events.Repeat(20s);
                    events.ScheduleEvent(EVENT_UNROOT, 0s);
                    break;
                case EVENT_HASTEN_INFECTIONS:
                    _infectionCooldown = std::max<uint32>(_infectionCooldown - 2000, 8000);
                    events.Repeat(90s);
                    break;
                case EVENT_MUTATED_INFECTION:
                    me->CastCustomSpell(SPELL_MUTATED_INFECTION, SPELLVALUE_MAX_TARGETS, 1, me, false);
                    events.Repeat(_infectionCooldown);
                    break;
                case EVENT_ROTFACE_OOZE_FLOOD:
                    if (Creature* professor = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_PROFESSOR_PUTRICIDE)))
                    {
                        professor->AI()->Talk(SAY_ROTFACE_OOZE_FLOOD);
                        DoCastAOE(oozeFloodSpells[_oozeFloodStage], true);
                        if (++_oozeFloodStage == 4)
                            _oozeFloodStage = 0;
                    }
                    events.Repeat(25s);
                    break;
                case EVENT_ROTFACE_VILE_GAS:
                    DoCastAOE(SPELL_VILE_GAS_TRIGGER);
                    events.Repeat(30s, 35s);
                    break;
                break;
                default:
                    break;
            }

            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    private:
        uint32 _infectionCooldown;
        uint64 _oozeFloodDummyGUIDs[4][2];
        uint8 _oozeFloodStage;
};

struct npc_little_oozeAI : public ScriptedAI
{
    npc_little_oozeAI(Creature* creature) : ScriptedAI(creature), _instance(creature->GetInstanceScript())
    {
        _firstUpdate = true;
        if (Creature* rotface = ObjectAccessor::GetCreature(*me, _instance->GetData64(DATA_ROTFACE)))
            rotface->AI()->JustSummoned(me);
    }

    void IsSummonedBy(Unit* summoner) override
    {
        if (!summoner)
            return;

        me->AddThreat(summoner, 500000.0f);
        AttackStart(summoner);
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (Creature* rotface = ObjectAccessor::GetCreature(*me, _instance->GetData64(DATA_ROTFACE)))
            rotface->AI()->SummonedCreatureDespawn(me);
        me->DespawnOrUnsummon(0);
    }

    void UpdateAI(uint32 diff) override
    {
        if (_firstUpdate)
        {
            _firstUpdate = false;
            DoCastSelf(SPELL_LITTLE_OOZE_COMBINE, true);
            DoCastSelf(SPELL_WEAK_RADIATING_OOZE, true);
            _events.Reset();
            _events.ScheduleEvent(EVENT_STICKY_OOZE, 5s);
            DoResetThreat();
            me->SetInCombatWithZone();
            if (TempSummon* ts = me->ToTempSummon())
                if (Unit* summoner = ts->GetSummoner())
                {
                    me->AddThreat(summoner, 500000.0f);
                    AttackStart(summoner);
                }
        }

        if (!UpdateVictim())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_STICKY_OOZE:
                    DoCastVictim(SPELL_STICKY_OOZE);
                    _events.Repeat(15s);
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void EnterEvadeMode() override
    {
        me->SetInCombatWithZone();
    }

    private:
        bool _firstUpdate;
        EventMap _events;
        InstanceScript* _instance;
};

struct npc_big_oozeAI : public ScriptedAI
{
    npc_big_oozeAI(Creature* creature) : ScriptedAI(creature), _instance(creature->GetInstanceScript())
    {
        _firstUpdate = true;
        if (Creature* rotface = ObjectAccessor::GetCreature(*me, _instance->GetData64(DATA_ROTFACE)))
            rotface->AI()->JustSummoned(me);
    }

    void IsSummonedBy(Unit* /*summoner*/) override
    {
        me->SetPassive();
        me->m_Events.AddEvent(new StartMovementEventRotface(me), me->m_Events.CalculateTime(2000));
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (Creature* rotface = ObjectAccessor::GetCreature(*me, _instance->GetData64(DATA_ROTFACE)))
            rotface->AI()->SummonedCreatureDespawn(me);
        me->DespawnOrUnsummon();
    }

    void DoAction(int32 action) override
    {
        if (action == EVENT_STICKY_OOZE)
            _events.CancelEvent(EVENT_STICKY_OOZE);
    }

    void UpdateAI(uint32 diff) override
    {
        if (_firstUpdate)
        {
            _firstUpdate = false;
            DoCastSelf(SPELL_LARGE_OOZE_COMBINE, true);
            DoCastSelf(SPELL_LARGE_OOZE_BUFF_COMBINE, true);
            DoCastSelf(SPELL_RADIATING_OOZE, true);
            DoCastSelf(SPELL_UNSTABLE_OOZE, true);
            DoCastSelf(SPELL_GREEN_ABOMINATION_HITTIN__YA_PROC, true);
            _events.Reset();
            _events.ScheduleEvent(EVENT_STICKY_OOZE, 5s);
        }

        if (!UpdateVictim())
            return;

        _events.Update(diff);

        switch (_events.ExecuteEvent())
        {
            case EVENT_STICKY_OOZE:
                DoCastVictim(SPELL_STICKY_OOZE);
                _events.Repeat(15s);
                break;
            default:
                break;
        }

        if (me->IsVisible())
            DoMeleeAttackIfReady();
    }

    void EnterEvadeMode() override
    {
        me->SetInCombatWithZone();
    }

    private:
        bool _firstUpdate;
        EventMap _events;
        InstanceScript* _instance;
};

class spell_rotface_mutated_infection_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_rotface_mutated_infection_SpellScript);

    bool Load() override
    {
        _target = nullptr;
        return true;
    }

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        // remove targets with this aura already
        // tank is not on this list
        targets.remove_if(Trinity::UnitAuraCheck(true, GetSpellInfo()->Id));
        targets.remove(GetCaster()->GetVictim());
        if (targets.empty())
            return;

        WorldObject* target = Trinity::Containers::SelectRandomContainerElement(targets);
        targets.clear();
        targets.push_back(target);
        _target = target;
    }

    void ReplaceTargets(std::list<WorldObject*>& targets)
    {
        targets.clear();
        if (_target)
            targets.push_back(_target);
    }

    void NotifyTargets()
    {
        if (Creature* caster = GetCaster()->ToCreature())
            if (Unit* target = GetHitUnit())
                if (caster->IsAIEnabled)
                    caster->AI()->Talk(EMOTE_MUTATED_INFECTION, target);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rotface_mutated_infection_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rotface_mutated_infection_SpellScript::ReplaceTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rotface_mutated_infection_SpellScript::ReplaceTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
        AfterHit += SpellHitFn(spell_rotface_mutated_infection_SpellScript::NotifyTargets);
    }

    WorldObject* _target;
};

class spell_rotface_mutated_infection_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_rotface_mutated_infection_AuraScript);

    void ExtraRemoveEffect(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        GetTarget()->CastSpell(GetTarget(), GetSpellInfo()->Effects[2].CalcValue(), true);
    }

    void Register() override
    {
        AfterEffectRemove += AuraEffectRemoveFn(spell_rotface_mutated_infection_AuraScript::ExtraRemoveEffect, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_rotface_little_ooze_combine_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_rotface_little_ooze_combine_SpellScript);

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        // little targetting little
        if (!GetHitCreature() || !GetHitCreature()->IsAlive())
            return;

        GetCaster()->RemoveAurasDueToSpell(SPELL_LITTLE_OOZE_COMBINE);
        GetHitCreature()->RemoveAurasDueToSpell(SPELL_LITTLE_OOZE_COMBINE);
        GetHitCreature()->CastSpell(GetCaster(), SPELL_OOZE_MERGE, true);
        GetHitCreature()->DespawnOrUnsummon();
        if (GetCaster()->ToCreature())
            GetCaster()->ToCreature()->DespawnOrUnsummon();
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rotface_little_ooze_combine_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};


void HandleBigOozeStacks(Creature* ooze, uint8 stackAmount)
{
    if (!ooze->IsAIEnabled)
        return;

    switch (stackAmount)
    {
        case 2:
            ooze->AI()->Talk(EMOTE_UNSTABLE_2, ooze);
            ooze->CastSpell(ooze, SPELL_VERTEX_COLOR_PINK, true);
            break;
        case 3:
            ooze->AI()->Talk(EMOTE_UNSTABLE_3, ooze);
            ooze->CastSpell(ooze, SPELL_VERTEX_COLOR_BRIGHT_RED, true);
            break;
        case 4:
            ooze->AI()->Talk(EMOTE_UNSTABLE_4, ooze);
            ooze->CastSpell(ooze, SPELL_VERTEX_COLOR_DARK_RED, true);
            break;
        case 5:
        {
            ooze->RemoveAurasDueToSpell(SPELL_LARGE_OOZE_BUFF_COMBINE);
            ooze->RemoveAurasDueToSpell(SPELL_LARGE_OOZE_COMBINE);
            if (InstanceScript* instance = ooze->GetInstanceScript())
                if (Creature* rotface = ObjectAccessor::GetCreature(*ooze, instance->GetData64(DATA_ROTFACE)))
                    if (rotface->IsAlive() && rotface->IsAIEnabled)
                    {
                        ooze->ToCreature()->AI()->Talk(EMOTE_UNSTABLE_EXPLOSION);
                        rotface->AI()->Talk(SAY_UNSTABLE_EXPLOSION);
                    }

            ooze->AI()->DoAction(EVENT_STICKY_OOZE);
            ooze->CastSpell(ooze, SPELL_UNSTABLE_OOZE_EXPLOSION, false, nullptr, nullptr, ooze->GetGUID());
            if (InstanceScript* instance = ooze->GetInstanceScript())
                instance->SetData(DATA_OOZE_DANCE_ACHIEVEMENT, uint32(false));
            break;
        }
        default:
            break;
    }
}

class spell_rotface_large_ooze_combine_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_rotface_large_ooze_combine_SpellScript);

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        // large targetting large
        if (!GetHitCreature() || !GetHitCreature()->IsAlive())
            return;

        Creature* caster = GetCaster()->ToCreature();
        if (!caster)
            return;

        uint8 casterStack = 1;
        uint8 targetStack = 1;
        Aura* casterAura = caster->GetAura(SPELL_UNSTABLE_OOZE);
        if (casterAura)
            casterStack = casterAura->GetStackAmount();
        Aura* targetAura = GetHitCreature()->GetAura(SPELL_UNSTABLE_OOZE);
        if (targetAura)
            targetStack = targetAura->GetStackAmount();
        uint8 newStack = casterStack+targetStack;
        if (newStack > 5)
            newStack = 5;
        if (casterAura)
            casterAura->SetStackAmount(newStack);
        else
        {
            caster->CastSpell(caster, SPELL_UNSTABLE_OOZE, true);
            if (Aura* aur = caster->GetAura(SPELL_UNSTABLE_OOZE))
                aur->SetStackAmount(newStack);
        }

        HandleBigOozeStacks(caster, newStack);

        GetHitCreature()->RemoveAurasDueToSpell(SPELL_LARGE_OOZE_BUFF_COMBINE);
        GetHitCreature()->RemoveAurasDueToSpell(SPELL_LARGE_OOZE_COMBINE);
        GetHitCreature()->DespawnOrUnsummon();
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rotface_large_ooze_combine_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_rotface_large_ooze_buff_combine_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_rotface_large_ooze_buff_combine_SpellScript);

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        // large targetting little
        if (!(GetHitCreature() && GetHitCreature()->IsAlive()))
            return;

        Creature* caster = GetCaster()->ToCreature();
        if (Aura* unstable = GetCaster()->GetAura(SPELL_UNSTABLE_OOZE))
        {
            uint8 newStack = uint8(unstable->GetStackAmount()+1);
            unstable->SetStackAmount(newStack);
            HandleBigOozeStacks(caster, newStack);
        }

        GetHitCreature()->RemoveAurasDueToSpell(SPELL_LITTLE_OOZE_COMBINE);
        GetHitCreature()->DespawnOrUnsummon();
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rotface_large_ooze_buff_combine_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_rotface_unstable_ooze_explosion_init_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_rotface_unstable_ooze_explosion_init_SpellScript);

    bool Validate(SpellInfo const* /*spell*/) override
    {
        return ValidateSpellInfo({ SPELL_UNSTABLE_OOZE_EXPLOSION_TRIGGER });
    }

    void HandleCast(SpellEffIndex effIndex)
    {
        PreventHitEffect(effIndex);
        if (!GetHitUnit())
            return;

        float x, y, z;
        GetHitUnit()->GetPosition(x, y, z);
        if (Creature* dummy = GetCaster()->SummonCreature(NPC_UNSTABLE_EXPLOSION_STALKER, x, y, z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 60000))
            GetCaster()->CastSpell(dummy, SPELL_UNSTABLE_OOZE_EXPLOSION_TRIGGER, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_rotface_unstable_ooze_explosion_init_SpellScript::HandleCast, EFFECT_0, SPELL_EFFECT_FORCE_CAST);
    }
};

class spell_rotface_unstable_ooze_explosion_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_rotface_unstable_ooze_explosion_SpellScript);

    void CheckTarget(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(EFFECT_0);
        if (!GetExplTargetDest())
            return;

        uint32 triggered_spell_id = GetSpellInfo()->Effects[effIndex].TriggerSpell;

        float x, y, z;
        GetExplTargetDest()->GetPosition(x, y, z);
        // let Rotface handle the cast - caster dies before this executes
        if (InstanceScript* script = GetCaster()->GetInstanceScript())
            if (Creature* rotface = script->instance->GetCreature(script->GetData64(DATA_ROTFACE)))
                rotface->CastSpell(x, y, z, triggered_spell_id, true); // caster not available on clientside, no log in such case
    }

    void Register() override
    {
        OnEffectHit += SpellEffectFn(spell_rotface_unstable_ooze_explosion_SpellScript::CheckTarget, EFFECT_0, SPELL_EFFECT_TRIGGER_MISSILE);
    }
};

class spell_rotface_unstable_ooze_explosion_suicide_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_rotface_unstable_ooze_explosion_suicide_AuraScript);

    void DespawnSelf(AuraEffect const* /*aurEff*/)
    {
        PreventDefaultAction();
        Unit* target = GetTarget();
        if (!target->IsCreature())
            return;

        target->SetVisible(false);
        target->RemoveAllAuras();
        target->ToCreature()->DespawnOrUnsummon(60000);
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_rotface_unstable_ooze_explosion_suicide_AuraScript::DespawnSelf, EFFECT_2, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_rotface_vile_gas_trigger_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_rotface_vile_gas_trigger_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.sort(Trinity::ObjectDistanceOrderPred(GetCaster()));
        if (targets.empty())
            return;

        std::list<WorldObject*> ranged, melee;
        auto itr = targets.begin();
        while (itr != targets.end() && (*itr)->GetDistance(GetCaster()) < 5.0f)
        {
            melee.push_back((*itr)->ToUnit());
            ++itr;
        }

        while (itr != targets.end())
        {
            ranged.push_back((*itr)->ToUnit());
            ++itr;
        }

        uint32 minTargets = GetCaster()->GetMap()->Is25ManRaid() ? 8 : 3;
        while (ranged.size() < minTargets)
        {
            if (melee.empty())
                break;

            WorldObject* target = Trinity::Containers::SelectRandomContainerElement(melee);
            ranged.push_back(target);
            melee.remove(target);
        }

        if (!ranged.empty())
            Trinity::Containers::RandomResize(ranged, GetCaster()->GetMap()->Is25ManRaid() ? 3 : 1);

        targets.swap(ranged);
    }

    void HandleDummy(SpellEffIndex effIndex)
    {
        PreventHitDefaultEffect(effIndex);
        GetCaster()->CastSpell(GetHitUnit(), SPELL_VILE_GAS_TRIGGER_SUMMON);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_rotface_vile_gas_trigger_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_rotface_vile_gas_trigger_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

struct npc_precious_iccAI : public ScriptedAI
{
    npc_precious_iccAI(Creature* creature) : ScriptedAI(creature), _summons(me)
    {
        _instance = creature->GetInstanceScript();
    }

    void Reset() override
    {
        _scheduler.CancelAll();
        _summons.DespawnAll();
    }

    void JustSummoned(Creature* summon) override
    {
        summon->SetPassive();
        summon->SetSpeed(MOVE_RUN, 0.7f);
        _summons.Summon(summon);
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _scheduler.Schedule(20s, 25s, [this](TaskContext task)
        {
            DoCastSelf(SPELL_DECIMATE);
            task.Repeat();
        });
        _scheduler.Schedule(1500ms, 2500ms, [this](TaskContext task)
        {
            DoCastVictim(SPELL_MORTAL_WOUND);
            task.Repeat();
        });
        _scheduler.Schedule(25s, 30s, [this](TaskContext task)
        {
            Talk(EMOTE_PRECIOUS_ZOMBIES);
            for (uint32 i = 0; i < 11; ++i)
                DoCastAOE(SPELL_AWAKEN_PLAGUED_ZOMBIES, true);
            _scheduler.Schedule(2s, [this](TaskContext /*task*/) {
                for (auto guid : _summons)
                    if (Creature* summon = _instance->instance->GetCreature(guid))
                    {
                        if (summon->HasReactState(REACT_PASSIVE))
                        {
                            summon->SetReactState(REACT_AGGRESSIVE);
                            DoZoneInCombat(summon);
                        }
                    }

            });
            task.Repeat(20s, 22s);
        });
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _summons.Despawn(summon);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _summons.DespawnAll();
        if (Creature* rotface = ObjectAccessor::GetCreature(*me, _instance->GetGuidData(DATA_ROTFACE)))
            if (rotface->IsAlive() && rotface->IsAIEnabled)
                rotface->AI()->Talk(SAY_PRECIOUS_DIES);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _scheduler.Update(diff,
            std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    private:
        TaskScheduler _scheduler;
        SummonList _summons;
        InstanceScript* _instance;
};

void AddSC_boss_rotface()
{
    new CreatureAILoader<boss_rotfaceAI>("boss_rotface");
    new CreatureAILoader<npc_little_oozeAI>("npc_little_ooze");
    new CreatureAILoader<npc_big_oozeAI>("npc_big_ooze");
    new SpellAuraScriptLoaderEx<spell_rotface_mutated_infection_SpellScript, spell_rotface_mutated_infection_AuraScript>("spell_rotface_mutated_infection");
    new SpellScriptLoaderEx<spell_rotface_little_ooze_combine_SpellScript>("spell_rotface_little_ooze_combine");
    new SpellScriptLoaderEx<spell_rotface_large_ooze_combine_SpellScript>("spell_rotface_large_ooze_combine");
    new SpellScriptLoaderEx<spell_rotface_large_ooze_buff_combine_SpellScript>("spell_rotface_large_ooze_buff_combine");;
    new SpellScriptLoaderEx<spell_rotface_unstable_ooze_explosion_init_SpellScript>("spell_rotface_unstable_ooze_explosion_init");
    new SpellScriptLoaderEx<spell_rotface_unstable_ooze_explosion_SpellScript>("spell_rotface_unstable_ooze_explosion");
    new AuraScriptLoaderEx<spell_rotface_unstable_ooze_explosion_suicide_AuraScript>("spell_rotface_unstable_ooze_explosion_suicide");
    new SpellScriptLoaderEx<spell_rotface_vile_gas_trigger_SpellScript>("spell_rotface_vile_gas_trigger");

    new CreatureAILoader<npc_precious_iccAI>("npc_precious_icc");
}
