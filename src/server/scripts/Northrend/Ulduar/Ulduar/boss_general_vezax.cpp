/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "AccountMgr.h"
#include "PassiveAI.h"
#include "Player.h"
#include "WorldSession.h"

enum VezaxSpellData
{
    SPELL_VEZAX_BERSERK                         = 26662,

    SPELL_VEZAX_SHADOW_CRASH                    = 62660,
    SPELL_VEZAX_SHADOW_CRASH_DMG                = 62659,
    SPELL_VEZAX_SHADOW_CRASH_AREA_AURA          = 63277,
    SPELL_VEZAX_SHADOW_CRASH_AURA               = 65269,

    SPELL_SEARING_FLAMES                        = 62661,

    SPELL_SURGE_OF_DARKNESS                     = 62662,

    SPELL_MARK_OF_THE_FACELESS_AURA             = 63276,
    SPELL_MARK_OF_THE_FACELESS_EFFECT           = 63278,

    SPELL_AURA_OF_DESPAIR_1                     = 62692,
    SPELL_AURA_OF_DESPAIR_2                     = 64848,
    SPELL_CORRUPTED_RAGE                        = 68415,
    SPELL_CORRUPTED_WISDOM                      = 64646,
    SPELL_SHAMANISTIC_RAGE                      = 30823,
    SPELL_JUDGEMENTS_OF_THE_WISDOM_RANK_1       = 31876,

    SPELL_SUMMON_SARONITE_VAPORS                = 63081,
    NPC_SARONITE_VAPORS                         = 33488,
    SPELL_SARONITE_VAPORS_DMG                   = 63338,
    SPELL_SARONITE_VAPORS_ENERGIZE              = 63337,
    SPELL_SARONITE_VAPORS_AURA                  = 63323,
    SPELL_SARONITE_VAPORS_DUMMYAURA             = 63322,

    SPELL_SARONITE_ANIMUS_FORMATION_VISUAL      = 63319,
    SPELL_SUMMON_SARONITE_ANIMUS                = 63145,
    SPELL_SARONITE_BARRIER                      = 63364,
    SPELL_PROFOUND_DARKNESS                     = 63420,
    SPELL_ANIMUS_MODEL_ANIMATION                = 63359
};

enum VezaxNpcs
{
    // NPC_VEZAX                                   = 33271,
    NPC_VEZAX_BUNNY                                = 33500,
    NPC_SARONITE_ANIMUS                            = 33524
};

enum VezaxGOs
{
    // GO_VEZAX_DOOR                               = 194750
};

enum VezaxSounds
{
    SOUND_VEZAX_AGGRO                              = 15542,
    SOUND_VEZAX_SLAIN_1                            = 15543,
    SOUND_VEZAX_SLAIN_2                            = 15544,
    SOUND_VEZAX_SURGE                              = 15545,
    SOUND_VEZAX_DEATH                              = 15546,
    SOUND_VEZAX_BERSERK                            = 15547,
    SOUND_VEZAX_HARDMODE                           = 15548
};

enum VezaxEvents
{
    EVENT_SPELL_VEZAX_SHADOW_CRASH                = 1,
    EVENT_SPELL_SEARING_FLAMES,
    EVENT_SPELL_SURGE_OF_DARKNESS,
    EVENT_SPELL_MARK_OF_THE_FACELESS,
    EVENT_SPELL_SUMMON_SARONITE_VAPORS,
    EVENT_SARONITE_VAPORS_SWIRL,
    EVENT_SPELL_SUMMON_SARONITE_ANIMUS,
    EVENT_DESPAWN_SARONITE_VAPORS,
    EVENT_SPELL_PROFOUND_DARKNESS,
    EVENT_BERSERK,
    EVENT_RESTORE_TARGET
};

#define TEXT_VEZAX_AGGRO                            "Your destruction will herald a new age of suffering!"
#define TEXT_VEZAX_SLAIN_1                          "You thought to stand before the legions of death... and survive?"
#define TEXT_VEZAX_SLAIN_2                          "Defiance... a flaw of mortality."
#define TEXT_VEZAX_SURGE                            "The black blood of Yogg-Saron courses through me! I. AM. UNSTOPPABLE!"
#define TEXT_VEZAX_BERSERK                          "Your defeat was inevitable!"
#define TEXT_VEZAX_DEATH                            "Oh, what horrors await...."
#define TEXT_VEZAX_HARDMODE                         "Behold, now! Terror, absolute!"

struct boss_vezaxAI : public BossAI
{
    boss_vezaxAI(Creature* creature) : BossAI(creature, TYPE_VEZAX) { }

    void Reset() override
    {
        _animusDied = false;
        _fightTimer = 0;
        _vaporsCount = 0;
        _hardmodeAvailable = true;
        _berserk = false;
        _shadowdodger = true;
        me->SetLootMode(1);

        if (instance)
            instance->SetData(TYPE_VEZAX, NOT_STARTED);
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade();
        instance->SetData(TYPE_VEZAX, FAIL);
    }

    bool CanSeeAlways(WorldObject const* /*obj*/) override
    {
        //! can always see if is in combat, prevent issues with mages going invisible
        return me->IsInCombat();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _fightTimer = getMSTime();
        _EnterCombat();
        events.Reset();
        events.RescheduleEvent(EVENT_SPELL_VEZAX_SHADOW_CRASH, 13000);
        events.RescheduleEvent(EVENT_SPELL_SEARING_FLAMES, 10000, 1);
        events.RescheduleEvent(EVENT_SPELL_SURGE_OF_DARKNESS, 63000);
        events.RescheduleEvent(EVENT_SPELL_MARK_OF_THE_FACELESS, 20000);
        events.RescheduleEvent(EVENT_SPELL_SUMMON_SARONITE_VAPORS, 30000);
        events.RescheduleEvent(EVENT_BERSERK, 600000);

        me->MonsterYell(TEXT_VEZAX_AGGRO, LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(SOUND_VEZAX_AGGRO, nullptr);

        if (instance)
            instance->SetData(TYPE_VEZAX, IN_PROGRESS);

        DoCastSelf(SPELL_AURA_OF_DESPAIR_1, true);
    }

    void DoAction(int32 param) override
    {
        switch (param)
        {
            case 1:
                _hardmodeAvailable = false;
                break;
            case 2:
                me->RemoveAura(SPELL_SARONITE_BARRIER);
                me->SetLootMode(3);
                _animusDied = true;
                break;
        }
    }

    uint32 GetData(uint32 id) const override
    {
        switch (id)
        {
            case 1: return (me->GetLootMode() == 3 ? 1 : 0);
            case 2: return (_shadowdodger == true ? 1 : 0);
        }
        return 0;
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        if (target && spell && target->IsPlayer() && spell->Id == SPELL_VEZAX_SHADOW_CRASH_DMG)
            _shadowdodger = false;

        if (spell->Id == SPELL_SEARING_FLAMES && target && target->IsPlayer() && sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
        {
            events.CancelEvent(EVENT_SPELL_SEARING_FLAMES);
            events.ScheduleEvent(EVENT_SPELL_SEARING_FLAMES, 1s);
        }
    }

    void UpdateAI(uint32 diff) override
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
                case EVENT_BERSERK:
                    _berserk = true;
                    DoCastSelf(SPELL_VEZAX_BERSERK, true);
                    me->MonsterYell(TEXT_VEZAX_BERSERK, LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_VEZAX_BERSERK, 0);
                    break;
                case EVENT_SPELL_VEZAX_SHADOW_CRASH:
                {
                    events.Repeat(urand(8000, 15000));

                    std::vector<Player*> players;
                    Map::PlayerList const& pl = me->GetMap()->GetPlayers();
                    for (auto itr = pl.begin(); itr != pl.end(); ++itr)
                    {
                        auto temp = itr->GetSource();
                        if (!temp->IsGameMaster() && temp->IsAlive() && temp->GetDistance(me) > 15.0f)
                            players.push_back(temp);
                    }

                    if (!players.empty())
                    {
                        me->setAttackTimer(BASE_ATTACK, 2000);
                        auto target = Trinity::Containers::SelectRandomContainerElement(players);
                        me->SetTarget(target->GetGUID());
                        DoCast(target, SPELL_VEZAX_SHADOW_CRASH);
                        events.ScheduleEvent(EVENT_RESTORE_TARGET, 750);
                    }
                }
                break;
                case EVENT_RESTORE_TARGET:
                    if (me->GetVictim())
                        me->SetTarget(me->GetVictim()->GetGUID());
                    break;
                case EVENT_SPELL_SEARING_FLAMES:
                    if (!me->FindNearestCreature(NPC_SARONITE_ANIMUS, 250.0f))
                        DoCastAOE(SPELL_SEARING_FLAMES);
                    events.Repeat(me->GetMap()->Is25ManRaid() ? 8000 : 15000);
                    break;
                case EVENT_SPELL_SURGE_OF_DARKNESS:
                    me->MonsterYell(TEXT_VEZAX_SURGE, LANG_UNIVERSAL, nullptr);
                    me->PlayDirectSound(SOUND_VEZAX_SURGE, nullptr);
                    DoCastSelf(SPELL_SURGE_OF_DARKNESS);
                    events.Repeat(63000);
                    events.DelayEvents(10000, 1);
                    break;
                case EVENT_SPELL_MARK_OF_THE_FACELESS:
                {
                    std::vector<Player*> outside;
                    std::vector<Player*> inside;
                    Map::PlayerList const &pl = me->GetMap()->GetPlayers();
                    for (auto itr = pl.begin(); itr != pl.end(); ++itr)
                        if (auto tmp = itr->GetSource())
                            if (tmp->IsAlive() && !tmp->IsGameMaster())
                            {
                                if (tmp->GetDistance(me) > 15.0f)
                                    outside.push_back(tmp);
                                else
                                    inside.push_back(tmp);
                            }

                    Player* target = nullptr;
                    if (outside.size() >= uint8(me->GetMap()->Is25ManRaid() ? 9 : 4))
                        target = Trinity::Containers::SelectRandomContainerElement(outside);
                    else if (!inside.empty())
                        target = Trinity::Containers::SelectRandomContainerElement(inside);

                    if (target)
                        DoCast(target, SPELL_MARK_OF_THE_FACELESS_AURA);

                    events.Repeat(40000);
                }
                break;
                case EVENT_SPELL_SUMMON_SARONITE_VAPORS:
                {
                    _vaporsCount++;
                    DoCastSelf(SPELL_SUMMON_SARONITE_VAPORS);
                    me->MonsterTextEmote("A cloud of saronite vapors coalesces nearby!", nullptr, true);

                    if (_vaporsCount < 8 || !_hardmodeAvailable)
                        events.Repeat(30000);
                    else
                    {
                        for (auto itr = summons.begin(); itr != summons.end(); ++itr)
                            if (auto sv = ObjectAccessor::GetCreature(*me, *itr))
                            {
                                sv->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                                sv->GetMotionMaster()->MoveIdle();
                                sv->GetMotionMaster()->MoveCharge(1852.78f, 81.38f, 342.461f, 28.0f);
                            }

                        events.DelayEvents(12000, 0);
                        events.DelayEvents(12000, 1);
                        events.ScheduleEvent(EVENT_SARONITE_VAPORS_SWIRL, 6000);
                    }
                }
                break;
                case EVENT_SARONITE_VAPORS_SWIRL:
                    if (summons.size())
                    {
                        me->MonsterTextEmote("The saronite vapors mass and swirl violently, merging into a monstrous form!", 0, true);
                        if (auto sv = ObjectAccessor::GetCreature(*me, *(summons.begin())))
                            sv->CastSpell(sv, SPELL_SARONITE_ANIMUS_FORMATION_VISUAL, true);

                        events.ScheduleEvent(EVENT_SPELL_SUMMON_SARONITE_ANIMUS, 2000);
                        break;
                    }
                    break;
                case EVENT_SPELL_SUMMON_SARONITE_ANIMUS:
                    if (summons.size())
                    {
                        me->MonsterTextEmote("A saronite barrier appears around General Vezax!", 0, true);
                        me->MonsterYell(TEXT_VEZAX_HARDMODE, LANG_UNIVERSAL, nullptr);
                        me->PlayDirectSound(SOUND_VEZAX_HARDMODE, nullptr);

                        DoCastSelf(SPELL_SARONITE_BARRIER);
                        if (auto sv = ObjectAccessor::GetCreature(*me, *(summons.begin())))
                            sv->CastSpell(sv, SPELL_SUMMON_SARONITE_ANIMUS, true);

                        events.ScheduleEvent(EVENT_DESPAWN_SARONITE_VAPORS, 2500);
                        break;
                    }
                    break;
                case EVENT_DESPAWN_SARONITE_VAPORS:
                    summons.DespawnEntry(NPC_SARONITE_VAPORS);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* killer) override
    {
        _JustDied();
        if (instance)
            instance->SetData(TYPE_VEZAX, DONE);

        instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_PROFOUND_DARKNESS);

        me->MonsterYell(TEXT_VEZAX_DEATH, LANG_UNIVERSAL, nullptr);
        me->PlayDirectSound(SOUND_VEZAX_DEATH, nullptr);

        if (auto door = me->FindNearestGameObject(GO_VEZAX_DOOR, 500.0f))
            if (door->GetGoState() != GO_STATE_ACTIVE)
            {
                door->SetLootState(GO_READY);
                door->UseDoorOrButton(0, false);
            }

        if (Map* map = me->GetMap())
            CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry + _animusDied, Difficulty(map->GetDifficulty() + _animusDied * 2), "", 15000, _fightTimer);
    }

    void KilledUnit(Unit* who) override
    {
        if (who->IsPlayer())
        {
            if (roll_chance_i(50))
            {
                me->MonsterYell(TEXT_VEZAX_SLAIN_1, LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_VEZAX_SLAIN_1, 0);
            }
            else
            {
                me->MonsterYell(TEXT_VEZAX_SLAIN_2, LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_VEZAX_SLAIN_2, 0);
            }
        }
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        summons.Despawn(summon);
    }

private:
    uint8 _vaporsCount;
    uint32 _fightTimer;
    bool _hardmodeAvailable;
    bool _berserk;
    bool _shadowdodger;
    bool _animusDied;
};

struct npc_ulduar_saronite_vaporsAI : NullCreatureAI
{
    explicit npc_ulduar_saronite_vaporsAI(Creature* creature) : NullCreatureAI(creature)
    {
        instance = me->GetInstanceScript();
        me->GetMotionMaster()->MoveRandom(4.0f);
    }

    void JustDied(Unit* /*killer*/) override
    {
        DoCastSelf(SPELL_SARONITE_VAPORS_AURA, true);

        // killed saronite vapors, hard mode unavailable
        if (instance)
            if (auto vezax = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_VEZAX)))
                if (vezax->IsAIEnabled)
                    vezax->AI()->DoAction(1);
    }

private:
    InstanceScript* instance;
};

enum Animus
{
    EVENT_PROFOUND_DARKNESS = 1
};

struct npc_ulduar_saronite_animusAI : ScriptedAI
{
    explicit npc_ulduar_saronite_animusAI(Creature* creature) : ScriptedAI(creature), timer(0)
    {
        instance = me->GetInstanceScript();
        if (instance)
            if (auto vezax = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_VEZAX)))
                if (vezax->IsAIEnabled)
                    vezax->AI()->JustSummoned(me);
    }


    uint16 timer;

    void Reset() override
    {
        ScriptedAI::Reset();
        _events.Reset();
        _events.ScheduleEvent(EVENT_PROFOUND_DARKNESS, 2000);
        DoZoneInCombat(me, 300.0f);
        DoCastSelf(SPELL_ANIMUS_MODEL_ANIMATION, true);
    }

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(3000);

        if (instance)
            if (auto vezax = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_VEZAX)))
                if (vezax->IsAIEnabled)
                    vezax->AI()->DoAction(2);
    }

    void UpdateAI(uint32 diff) override
    {
        UpdateVictim();

        _events.Update(diff);

        if (_events.ExecuteEvent() == EVENT_PROFOUND_DARKNESS)
        {
            // boosted
            if (instance)
            {
                if (Is25ManRaid() && sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
                {
                    if (auto vezax = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_VEZAX)))
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, vezax->GetMaxHealth() * 0.005);
                        vezax->CastCustomSpell(22806, val, vezax, TRIGGERED_FULL_MASK);
                    }
                }
            }

            DoCastSelf(SPELL_PROFOUND_DARKNESS, true);
            if (Is25ManRaid() && sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF))
                _events.Repeat(1.2s);
            else
                _events.Repeat(2s);
        }

        DoMeleeAttackIfReady();
    }

private:
    InstanceScript* instance;
    EventMap _events;
};

class spell_aura_of_despair_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_aura_of_despair_AuraScript)

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetTarget())
            {
                if (!target->IsPlayer())
                    return;

                //! handled in internal functions
                //target->CastSpell(target, SPELL_AURA_OF_DESPAIR_2, true);
                if (target->HasSpell(SPELL_SHAMANISTIC_RAGE))
                    caster->CastSpell(target, SPELL_CORRUPTED_RAGE, true);
                else if (target->HasSpell(SPELL_JUDGEMENTS_OF_THE_WISDOM_RANK_1) || target->HasSpell(SPELL_JUDGEMENTS_OF_THE_WISDOM_RANK_1 + 1) || target->HasSpell(SPELL_JUDGEMENTS_OF_THE_WISDOM_RANK_1 + 2))
                    caster->CastSpell(target, SPELL_CORRUPTED_WISDOM, true);
            }
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto target = GetTarget())
        {
            target->RemoveAurasDueToSpell(SPELL_AURA_OF_DESPAIR_2);
            target->RemoveAurasDueToSpell(SPELL_CORRUPTED_RAGE);
            target->RemoveAurasDueToSpell(SPELL_CORRUPTED_WISDOM);
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_aura_of_despair_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PREVENT_REGENERATE_POWER, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_aura_of_despair_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PREVENT_REGENERATE_POWER, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_mark_of_the_faceless_periodic_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_mark_of_the_faceless_periodic_AuraScript)

    void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (auto caster = GetCaster())
            if (GetTarget()->GetMapId() == 603)
            {
                int32 dmg = 5000;
                caster->CastCustomSpell(GetTarget(), SPELL_MARK_OF_THE_FACELESS_EFFECT, 0, &dmg, 0, true);
            }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_mark_of_the_faceless_periodic_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_mark_of_the_faceless_drainhealth_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_mark_of_the_faceless_drainhealth_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove(GetExplTargetUnit());
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_mark_of_the_faceless_drainhealth_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class spell_saronite_vapors_dummy_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_saronite_vapors_dummy_AuraScript)

    void HandleAfterEffectApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (auto caster = GetCaster())
        {
            int32 damage = 100 * pow(2.0f, static_cast<float>(GetStackAmount()));
            caster->CastCustomSpell(GetTarget(), SPELL_SARONITE_VAPORS_DMG, &damage, NULL, NULL, true);
        }
    }

    void Register() override
    {
        AfterEffectApply += AuraEffectApplyFn(spell_saronite_vapors_dummy_AuraScript::HandleAfterEffectApply, EFFECT_0, SPELL_AURA_DUMMY, AURA_EFFECT_HANDLE_REAL_OR_REAPPLY_MASK);
    }
};

class spell_saronite_vapors_damage_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_saronite_vapors_damage_SpellScript);

    void HandleAfterHit()
    {
        if (auto caster = GetCaster())
            if (GetHitDamage() > 2)
            {
                int32 mana = GetHitDamage() / 2;
                if (auto target = GetHitUnit())
                    caster->CastCustomSpell(target, SPELL_SARONITE_VAPORS_ENERGIZE, &mana, nullptr, nullptr, true);
            }
    }

    void Register() override
    {
        AfterHit += SpellHitFn(spell_saronite_vapors_damage_SpellScript::HandleAfterHit);
    }
};

class achievement_smell_saronite : public AchievementCriteriaScript
{
    public:
        achievement_smell_saronite() : AchievementCriteriaScript("achievement_smell_saronite") {}

        bool OnCheck(Player* /*player*/, Unit* target) override
        {
            return target && target->GetEntry() == NPC_VEZAX && target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->AI()->GetData(1);
        }
};

class achievement_shadowdodger : public AchievementCriteriaScript
{
    public:
        achievement_shadowdodger() : AchievementCriteriaScript("achievement_shadowdodger") {}

        bool OnCheck(Player* player, Unit* target) override
        {
            return target && target->GetEntry() == NPC_VEZAX && target->GetTypeId() == TYPEID_UNIT && target->ToCreature()->AI()->GetData(2);
        }
};

class go_ulduar_pure_saronite_deposit : public GameObjectScript
{
    public:
        go_ulduar_pure_saronite_deposit() : GameObjectScript("go_ulduar_pure_saronite_deposit") { }

        bool OnGossipHello(Player* plr, GameObject* go) override
        {
            if (plr->IsGameMaster())
                return false;

            if (auto pInstance = go->GetInstanceScript())
                if (pInstance->GetData(TYPE_XT002) != DONE && pInstance->GetData(TYPE_MIMIRON) != DONE && pInstance->GetData(TYPE_THORIM) != DONE && pInstance->GetData(TYPE_FREYA) != DONE && pInstance->GetData(TYPE_HODIR) != DONE)
                {
                    std::string accountName;
                    AccountMgr::GetName(plr->GetSession()->GetAccountId(), accountName);
                    sWorld->BanAccount(BAN_ACCOUNT, accountName, "0s", "Tele hack", "Server");
                    return true;
                }

            return false;
        }
};

enum facelessHorrorMisc
{
    EVENT_FACELESS_SHADOWCRASH  = 1,

    SPELL_FACELESS_SHADOWCRASH  = 63722,
    SPELL_FACELESS_VOID_BARRIER = 63710,
    SPELL_FACELESS_SUMMON_VOID  = 63708,
    SPELL_FACELESS_VOID_WAVE    = 63703,
    SPELL_FACELESS_GRIP         = 64429,
    SPELL_FACELESS_GRIP_TRIGGER = 64431
};

struct npc_faceless_horror_ulduar_AI : public ScriptedAI
{
    npc_faceless_horror_ulduar_AI(Creature* creature) : ScriptedAI(creature), summons(me) { }

    void Reset() override
    {
        _barriers.fill(false);
        summons.DespawnAll();
        events.Reset();
        me->RemoveAllAuras();
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);

        if (summon->IsAIEnabled)
            summon->AI()->DoZoneInCombat(summon, 100.0f);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        summons.Despawn(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        me->RemoveAurasDueToSpell(SPELL_FACELESS_VOID_BARRIER);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        DoZoneInCombat(me, 100.0f);
        DoCastSelf(SPELL_FACELESS_VOID_WAVE);
        events.ScheduleEvent(EVENT_FACELESS_SHADOWCRASH, 5s);
        DoCastVictim(SPELL_FACELESS_GRIP);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (me->HealthBelowPctDamaged(75, damage) && !_barriers.at(0))
        {
            _barriers.at(0) = true;
            SummonVoidBeast();
        }
        else if (me->HealthBelowPctDamaged(50, damage) && !_barriers.at(1))
        {
            _barriers.at(1) = true;
            SummonVoidBeast();
        }
        else if (me->HealthBelowPctDamaged(25, damage) && !_barriers.at(2))
        {
            _barriers.at(2) = true;
            SummonVoidBeast();
        }
    }

    void SummonVoidBeast()
    {
        DoCastSelf(SPELL_FACELESS_VOID_BARRIER);
        DoCastAOE(SPELL_FACELESS_SUMMON_VOID);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (auto eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_FACELESS_SHADOWCRASH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 70.f, true))
                        DoCast(target, SPELL_FACELESS_SHADOWCRASH);
                    events.Repeat(11s);
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }
private:
    std::array<bool, 3> _barriers;
    EventMap events;
    SummonList summons;
};

class spell_faceless_death_grip_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_faceless_death_grip_SpellScript);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (GetHitUnit())
            GetHitUnit()->CastSpell(GetCaster(), SPELL_FACELESS_GRIP_TRIGGER, true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_faceless_death_grip_SpellScript::HandleHit, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_vezax()
{
    new CreatureAILoader<boss_vezaxAI>("boss_vezax");
    new CreatureAILoader<npc_ulduar_saronite_vaporsAI>("npc_ulduar_saronite_vapors");
    new CreatureAILoader<npc_ulduar_saronite_animusAI>("npc_ulduar_saronite_animus");

    new AuraScriptLoaderEx<spell_aura_of_despair_AuraScript>("spell_aura_of_despair");
    new AuraScriptLoaderEx<spell_mark_of_the_faceless_periodic_AuraScript>("spell_mark_of_the_faceless_periodic");
    new SpellScriptLoaderEx<spell_mark_of_the_faceless_drainhealth_SpellScript>("spell_mark_of_the_faceless_drainhealth");
    new AuraScriptLoaderEx<spell_saronite_vapors_dummy_AuraScript>("spell_saronite_vapors_dummy");
    new SpellScriptLoaderEx<spell_saronite_vapors_damage_SpellScript>("spell_saronite_vapors_damage");

    //! misc
    new SpellScriptLoaderEx<spell_faceless_death_grip_SpellScript>("spell_faceless_death_grip");
    new CreatureAILoader<npc_faceless_horror_ulduar_AI>("npc_faceless_horror_ulduar");

    new achievement_smell_saronite();
    new achievement_shadowdodger();

    new go_ulduar_pure_saronite_deposit();
}