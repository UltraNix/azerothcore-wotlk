#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "gundrak.h"
#include "SpellScript.h"

enum DrakkariColossusSays
{
    SAY_SURGE,
    EMOTE_ALTAR
};

enum DrakkariColossusSpells
{
    SPELL_MOJO_PUDDLE                       = 55627,
    SPELL_MOJO_WAVE                         = 55626,
    SPELL_FREEZE_ANIM                       = 52656,
    SPELL_MIGHTY_BLOW                       = 54719,

    SPELL_ELEMENTAL_SPAWN_EFFECT            = 54888,
    SPELL_EMERGE                            = 54850,
    SPELL_EMERGE_SUMMON                     = 54851,
    SPELL_MOJO_VOLLEY                       = 54849,

    SPELL_SURGE_VISUAL                      = 54827,
    SPELL_SURGE                             = 54801,
    SPELL_SURGE_DAMAGE                      = 54819,

    SPELL_FACE_ME                           = 54991,
    SPELL_MERGE                             = 54878
};

enum DrakkariColossusEvents
{
    EVENT_COLOSSUS_MIGHTY_BLOW              = 1,
    EVENT_COLOSSUS_START_FIGHT,

    EVENT_ELEMENTAL_SURGE,
    EVENT_ELEMENTAL_VOLLEY,

    EVENT_INFORM,
    EVENT_MOJO_MOJO_WAVE,
    EVENT_MOJO_MOJO_PUDDLE
};

enum DrakkariColossusMisc
{
    NPC_LIVING_MOJO                         = 29830,
    NPC_DRAKKARI_ELEMENTAL                  = 29573,

    ACTION_INFORM                           = 2,

    POINT_MERGE                             = 1,

    DATA_EMERGE_COUNT                       = 1
};

static const std::vector<Position> MojoSpawnPositions =
{
    { 1663.1f, 743.6f, 143.1f },
    { 1669.97f, 753.7f, 143.1f },
    { 1680.7f, 750.7f, 143.1f },
    { 1680.7f, 737.1f, 143.1f },
    { 1670.4f, 733.5f, 143.1f }
};

class RestoreFight : public BasicEvent
{
    public:
        RestoreFight(Creature* owner) : _owner(owner) { }

        bool Execute(uint64 /*execTime*/, uint32 /*diff*/)
        {
            _owner->SetReactState(REACT_AGGRESSIVE);
            if (_owner->IsAIEnabled)
                _owner->AI()->DoZoneInCombat(nullptr, 250.0f);
            return true;
        }

    private:
        Creature* _owner;
};

struct boss_drakkari_colossusAI : public BossAI
{
    boss_drakkari_colossusAI(Creature* creature) : BossAI(creature, BOSS_DRAKKARI_COLOSSUS)
    {
        if (me->IsAlive())
        {
            _mojoGUIDs.reserve(MojoSpawnPositions.size());
            DoCastSelf(SPELL_FREEZE_ANIM, true);
            SummonLivingMojo();
        }
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_INFORM)
        {
            me->SetInCombatWithZone();
            for (uint64 const guid : _mojoGUIDs)
                if (Creature* mojo = instance->instance->GetCreature(guid))
                {
                    mojo->SetPassive();
                    mojo->GetMotionMaster()->MoveCharge(1672.96f, 743.488f, 143.338f, 7.0f, POINT_MERGE);
                    mojo->DespawnOrUnsummon(1.2s);
                }
            events.ScheduleEvent(EVENT_COLOSSUS_START_FIGHT, 3.5s);
        }
    }

    void SummonLivingMojo()
    {
        for (auto const& pos : MojoSpawnPositions)
            if (Creature* summon = me->SummonCreature(NPC_LIVING_MOJO, pos))
            {
                summon->SetFacingToObject(me);
                _mojoGUIDs.emplace_back(summon->GetGUID());
            }
    }

    void Reset() override
    {
        _emergeCount = 0;
        _Reset();
        SetImmune(true);
    }

    void JustReachedHome() override
    {
        _JustReachedHome();
        if (me->IsAlive())
        {
            DoCastSelf(SPELL_FREEZE_ANIM, true);
            SummonLivingMojo();
        }
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_COLOSSUS_MIGHTY_BLOW, 10s);
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_DRAKKARI_ELEMENTAL)
        {
            summon->SetRegeneratingHealth(false);
            summon->SetReactState(REACT_PASSIVE);
            summon->m_Events.AddEvent(new RestoreFight(summon), summon->m_Events.CalculateTime(3000));
            if (_emergeCount == 2)
            {
                summon->SetHealth(summon->GetMaxHealth()/2);
                summon->LowerPlayerDamageReq(summon->GetMaxHealth()/2);
                summon->AI()->DoAction(ACTION_INFORM);
            }
        }

        summons.Summon(summon);
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == DATA_EMERGE_COUNT)
            return _emergeCount;

        return 0;
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        summons.Despawn(summon);
        if (summon->GetEntry() == NPC_DRAKKARI_ELEMENTAL)
            Unit::Kill(me, me);
    }

    void SetImmune(bool apply) const
    {
        //me->SetAttackable(!apply);
        me->SetSelectable(!apply);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        summons.Despawn(summon);
        if (summon->GetEntry() == NPC_DRAKKARI_ELEMENTAL)
        {
            SetImmune(false);
            me->RemoveAurasDueToSpell(SPELL_FREEZE_ANIM);
            if (Unit* victim = me->GetVictim())
                me->GetMotionMaster()->MoveChase(victim);
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        if (me->HealthBelowPctDamaged(50 - _emergeCount * 30, damage))
        {
            ++_emergeCount;
            DoCastSelf(SPELL_EMERGE);
            DoCastSelf(SPELL_EMERGE_SUMMON, true);
            me->GetMotionMaster()->Clear();
            SetImmune(true);
        }

        if (damage >= me->GetHealth())
            damage = me->GetHealth() - 1;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_COLOSSUS_START_FIGHT:
                    me->RemoveAurasDueToSpell(SPELL_FREEZE_ANIM);
                    SetImmune(false);
                    break;
                case EVENT_COLOSSUS_MIGHTY_BLOW:
                    DoCastVictim(SPELL_MIGHTY_BLOW);
                    events.Repeat(10s);
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
        uint8 _emergeCount;
        std::vector<uint64> _mojoGUIDs;
};

struct boss_drakkari_elementalAI : public ScriptedAI
{
    boss_drakkari_elementalAI(Creature* creature) : ScriptedAI(creature)
    {
        _events.ScheduleEvent(EVENT_ELEMENTAL_SURGE, 7s);
        _events.ScheduleEvent(EVENT_ELEMENTAL_VOLLEY, 0s);
    }

    void Reset() override
    {
        _despawn = false;
        DoCastSelf(SPELL_ELEMENTAL_SPAWN_EFFECT);
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(EMOTE_ALTAR);
    }

    void EnterCombat(Unit* /*attacker*/) override { }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        if (!_despawn && me->HealthBelowPctDamaged(50, damage))
            if (InstanceScript* instance = me->GetInstanceScript())
                if (Creature* colossus = instance->GetCreature(BOSS_DRAKKARI_COLOSSUS))
                    if (colossus->IsAIEnabled && colossus->AI()->GetData(DATA_EMERGE_COUNT) < 2)
                    {
                        _despawn = true;
                        DoCastSelf(SPELL_FACE_ME, true);
                        DoCastSelf(SPELL_SURGE_VISUAL, true);
                        DoCastSelf(SPELL_MERGE);
                        me->DespawnOrUnsummon(2s);
                        _events.Reset();
                    }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting() || me->HasUnitState(UNIT_STATE_CHARGING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ELEMENTAL_SURGE:
                    Talk(SAY_SURGE);
                    DoCastSelf(SPELL_SURGE_VISUAL, true);
                    DoCastVictim(SPELL_SURGE);
                    _events.Repeat(15s);
                    break;
                case EVENT_ELEMENTAL_VOLLEY:
                    DoCastSelf(SPELL_MOJO_VOLLEY, true);
                    break;
                default:
                    break;
            }

            if (me->IsCasting() || me->HasUnitState(UNIT_STATE_CHARGING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    private:
        EventMap _events;
        bool _despawn;
};

struct npc_living_mojoAI : public ScriptedAI
{
    npc_living_mojoAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
        _events.ScheduleEvent(EVENT_MOJO_MOJO_PUDDLE, 13s);
        _events.ScheduleEvent(EVENT_MOJO_MOJO_WAVE, 15s);
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (me->ToTempSummon())
            return;

        ScriptedAI::MoveInLineOfSight(who);
    }

    void AttackStart(Unit* who) override
    {
        if (me->ToTempSummon())
        {
            if (who->IsPlayer() || IS_PLAYER_GUID(who->GetOwnerGUID()))
                _events.ScheduleEvent(EVENT_INFORM, 1s);
            return;
        }

        ScriptedAI::AttackStart(who);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !me->ToTempSummon())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_INFORM:
                    if (Creature* summoner = me->ToTempSummon()->GetSummonerCreatureBase())
                        summoner->AI()->DoAction(ACTION_INFORM);
                    break;
                case EVENT_MOJO_MOJO_PUDDLE:
                    DoCastSelf(SPELL_MOJO_PUDDLE);
                    _events.Repeat(13s);
                    break;
                case EVENT_MOJO_MOJO_WAVE:
                    DoCastVictim(SPELL_MOJO_WAVE);
                    _events.Repeat(15s);
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
        EventMap _events;
};

class spell_drakkari_colossus_emerge_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_drakkari_colossus_emerge_SpellScript);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), SPELL_FREEZE_ANIM, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_drakkari_colossus_emerge_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_drakkari_colossus_surge_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_drakkari_colossus_surge_SpellScript);

    void HandleDummy(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_SURGE_DAMAGE, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_drakkari_colossus_surge_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

class spell_drakkari_colossus_face_me_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_drakkari_colossus_face_me_SpellScript);

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
        {
            GetCaster()->SetInFront(target);
            GetCaster()->SetFacingTo(GetCaster()->GetAngle(target));
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_drakkari_colossus_face_me_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

void AddSC_boss_drakkari_colossus()
{
    new CreatureAILoader<boss_drakkari_colossusAI>("boss_drakkari_colossus");
    new CreatureAILoader<boss_drakkari_elementalAI>("boss_drakkari_elemental");
    new CreatureAILoader<npc_living_mojoAI>("npc_living_mojo");
    new SpellScriptLoaderEx<spell_drakkari_colossus_emerge_SpellScript>("spell_drakkari_colossus_emerge");
    new SpellScriptLoaderEx<spell_drakkari_colossus_surge_SpellScript>("spell_drakkari_colossus_surge");
    new SpellScriptLoaderEx<spell_drakkari_colossus_face_me_SpellScript>("spell_drakkari_colossus_face_me");
}
