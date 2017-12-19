/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "Vehicle.h"
#include "SpellAuras.h"
#include "SpellAuraEffects.h"
#include "Player.h"

#define SPELL_FLAME_JETS_10                62680
#define SPELL_FLAME_JETS_25                63472
#define SPELL_SCORCH_10                    62546
#define SPELL_SCORCH_25                    63474
#define SPELL_ACTIVATE_CONSTRUCT           62488
#define SPELL_STRENGTH_OF_THE_CREATOR      64473
#define SPELL_SLAG_POT_10                  62717
#define SPELL_SLAG_POT_25                  63477
#define SPELL_BERSERK                      64238
#define SPELL_GRAB                         62707
#define SPELL_GRAB_TRIGGERED               62708
#define SPELL_GRAB_CONTROL_2               62711
#define SPELL_SCORCHED_GROUND_10           62548
#define SPELL_SCORCHED_GROUND_25           63476
#define SPELL_HEAT_AREA                    62343
#define SPELL_HEAT_BUFF                    65667
#define SPELL_MOLTEN                       62373
#define SPELL_BRITTLE_10                   62382
#define SPELL_BRITTLE_25                   67114
#define SPELL_SHATTER                      62383
#define BOSS_IGNIS                         33118
#define NPC_IRON_CONSTRUCT                 33121
#define NPC_SCORCHED_GROUND                33123
#define NPC_WATER_TRIGGER                  22515

#define S_FLAME_JETS                       RAID_MODE(SPELL_FLAME_JETS_10, SPELL_FLAME_JETS_25)
#define S_SCORCH                           RAID_MODE(SPELL_SCORCH_10, SPELL_SCORCH_25)
#define S_SLAG_POT                         RAID_MODE(SPELL_SLAG_POT_10, SPELL_SLAG_POT_25)
#define S_SCORCHED_GROUND                  RAID_MODE(SPELL_SCORCHED_GROUND_10, SPELL_SCORCHED_GROUND_25)
#define S_BRITTLE                          RAID_MODE(SPELL_BRITTLE_10, SPELL_BRITTLE_25)

#define TEXT_AGGRO                        "Insolent whelps! Your blood will temper the weapons used to reclaim this world!"
#define TEXT_ACTIVATE_CONSTRUCT           "Arise, soldiers of the Iron Crucible! The Makers' will be done!"
#define TEXT_SCORCH_1                     "Let the inferno consume you!"
#define TEXT_SCORCH_2                     "BURN! Burn in the makers fire!"
#define TEXT_SLAG_POT                     "I will burn away your impurities!"
#define TEXT_SLAY_1                       "More scraps for the scrapheap!"
#define TEXT_SLAY_2                       "Your bones will serve as kindling!"
#define TEXT_BERSERK                      "Let it be finished!"
#define TEXT_DEATH                        "I. Have. Failed."
#define TEXT_FLAME_JETS                   "Ignis The Furnace Master begins to cast Flame Jets!"

#define SOUND_AGGRO                        15564
#define SOUND_ACTIVATE_CONSTRUCT           15565
#define SOUND_SLAG_POT                     15566
#define SOUND_SCORCH_1                     15567
#define SOUND_SCORCH_2                     15568
#define SOUND_SLAY_1                       15569
#define SOUND_SLAY_2                       15570
#define SOUND_BERSERK                      15571
#define SOUND_DEATH                        15572

#define ACHIEV_STOKIN_THE_FURNACE_EVENT 20951

enum eEvents
{
    EVENT_NONE = 0,
    EVENT_ACTIVATE_CONSTRUCT,
    EVENT_SPELL_SCORCH,
    EVENT_ENABLE_ROTATE,
    EVENT_SPELL_FLAME_JETS,
    EVENT_GRAB,
};

struct npc_ulduar_iron_constructAI : public ScriptedAI
{
    npc_ulduar_iron_constructAI(Creature* creature) : ScriptedAI(creature)
    { 
        instance = me->GetInstanceScript();
        DoCastSelf(38757, true);
    }

    void Reset() override
    {
        _timer = 1000;
        me->SetReactState(REACT_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void JustReachedHome() override
    {
        DoCastSelf(38757, true);
    }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_ACTIVATE_CONSTRUCT)
        {
            me->RemoveAura(38757);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_AGGRESSIVE);

            if(instance)
                if (Creature* ignis = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_IGNIS)))
                {
                    ignis->CastSpell(ignis, SPELL_STRENGTH_OF_THE_CREATOR, true);
                    if (ignis->GetVictim())
                        AttackStart(ignis->GetVictim());
                    DoZoneInCombat();
                }
        }
        else if (spell->Id == SPELL_HEAT_BUFF)
        {
            if (Aura* aura = me->GetAura(SPELL_HEAT_BUFF))
                if (aura->GetStackAmount() >= RAID_MODE(10, 20))
                {
                    if (RAID_MODE(1,0) && aura->GetStackAmount() > 10) // prevent going over 10 on 10man version
                        aura->ModStackAmount(-1);

                    DoCastSelf(SPELL_MOLTEN, true);
                    me->getThreatManager().resetAllAggro();
                }
        }
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (damage >= RAID_MODE(3000U, 5000U) && me->GetAura(S_BRITTLE))
        {
            DoCastSelf(SPELL_SHATTER, true);
            Unit::Kill(attacker, me);

            if (instance)
                if (Creature* ignis = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_IGNIS)))
                    if (ignis->IsAIEnabled)
                        ignis->AI()->SetData(1337, 0);
        }
    }

    void JustDied(Unit* killer) override
    {
        if (instance)
            if (Creature* ignis = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_IGNIS)))
                ignis->RemoveAuraFromStack(SPELL_STRENGTH_OF_THE_CREATOR);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (_timer <= diff)
        {
            _timer = 1000;
            if (Aura* aura = me->GetAura(SPELL_MOLTEN))
                if (me->FindNearestCreature(NPC_WATER_TRIGGER, 18.0f, true))
                {
                    me->RemoveAura(aura);
                    DoCastSelf(S_BRITTLE, true);
                }
        }
        else
            _timer -= diff;

        DoMeleeAttackIfReady();
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

private:
    InstanceScript* instance;
    uint32 _timer;
};

struct boss_ignisAI : public BossAI
{
    boss_ignisAI(Creature* creature) : BossAI(creature, TYPE_IGNIS) {}

    void Reset() override
    {
        _Reset();
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        _counter = 0;
        _shattered = false;
        _lastShatterMSTime = 0;
            
        instance->SetData(TYPE_IGNIS, NOT_STARTED);
        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_STOKIN_THE_FURNACE_EVENT);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();

        std::list<Creature*> list;
        me->GetCreaturesWithEntryInRange(list, 300.0f, NPC_IRON_CONSTRUCT);
        if (!list.empty())
        {
            for (auto itr : list)
            {
                if (!itr->IsAlive())
                {
                    itr->Respawn();
                    itr->UpdatePosition(itr->GetHomePosition(), true);
                    itr->StopMovingOnCurrentPos();
                }

                if (itr->IsAIEnabled)
                    itr->AI()->Reset();

                if (!itr->HasAura(38757))
                    itr->CastSpell(itr, 38757, true);
            }
        }

        _shattered = false;
        _lastShatterMSTime = 0;

        events.Reset();
        events.ScheduleEvent(EVENT_ACTIVATE_CONSTRUCT, RAID_MODE(40000,30000));
        events.ScheduleEvent(EVENT_SPELL_SCORCH, 10000);
        events.ScheduleEvent(EVENT_SPELL_FLAME_JETS, 32000);
        events.ScheduleEvent(EVENT_GRAB, 25000);

        me->MonsterYell(TEXT_AGGRO, LANG_UNIVERSAL, 0);
        me->PlayDirectSound(SOUND_AGGRO);

        instance->SetData(TYPE_IGNIS, IN_PROGRESS);
        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_STOKIN_THE_FURNACE_EVENT);
        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_STOKIN_THE_FURNACE_EVENT);
    }

    void SetData(uint32 id, uint32 /*value*/) override
    {
        if (id == 1337)
        {
            if (_lastShatterMSTime)
                if (getMSTimeDiff(_lastShatterMSTime, World::GetGameTimeMS()) <= 5000)
                    _shattered = true;

            _lastShatterMSTime = World::GetGameTimeMS();
        }
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == 1337)
            return (_shattered ? 1 : 0);
        return 0;
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer())
        {
            if (urand(0, 1))
            {
                me->MonsterYell(TEXT_SLAY_1, LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SLAY_1);
            }
            else
            {
                me->MonsterYell(TEXT_SLAY_2, LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SLAY_2);
            }
        }
    }

    void JustDied(Unit* /*victim*/) override
    {
        me->MonsterYell(TEXT_DEATH, LANG_UNIVERSAL, 0);
        me->PlayDirectSound(SOUND_DEATH);

        instance->SetData(TYPE_IGNIS, DONE);

        CheckConstructs();
    }

    void CheckConstructs()
    {
        std::list<Creature*> constructs;
        GetCreatureListWithEntryInGrid(constructs, me, NPC_IRON_CONSTRUCT, 200.0f);
        if (!constructs.empty())
            for (auto itr : constructs)
                if (itr->IsAlive() && itr->IsInCombat())
                    itr->DisappearAndDie();
    }

    void SpellHit(Unit* caster, const SpellInfo* spell) override
    {
        if (caster && spell->Id == SPELL_GRAB_CONTROL_2)
            DoCast(caster, S_SLAG_POT, true);
    }

    void MoveInLineOfSight(Unit* who) override {}

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        if (me->GetPositionX() < 490.0f || me->GetPositionX() > 690.0f || me->GetPositionY() < 130.0f || me->GetPositionY() > 410.0f)
        {
            EnterEvadeMode();
            return;
        }

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ACTIVATE_CONSTRUCT:
                    me->CastCustomSpell(SPELL_ACTIVATE_CONSTRUCT, SPELLVALUE_MAX_TARGETS, 1, (Unit*)nullptr, false);
                    if (++_counter >= 20)
                    {
                        me->MonsterYell(TEXT_BERSERK, LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_BERSERK);
                        DoCastSelf(SPELL_BERSERK, true);
                        break;
                    }
                    events.Repeat(RAID_MODE(40000, 30000));
                    break;
                case EVENT_SPELL_SCORCH:
                    if (urand(0, 1))
                    {
                        me->MonsterYell(TEXT_SCORCH_1, LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_SCORCH_1);
                    }
                    else
                    {
                        me->MonsterYell(TEXT_SCORCH_2, LANG_UNIVERSAL, 0);
                        me->PlayDirectSound(SOUND_SCORCH_2);
                    }
                    me->SetControlled(true, UNIT_STATE_ROOT);
                    me->DisableRotate(true);
                    me->SendMovementFlagUpdate();
                    DoCastVictim(S_SCORCH);
                    events.Repeat(20000);
                    events.RescheduleEvent(EVENT_ENABLE_ROTATE, 3001);
                    break;
                case EVENT_ENABLE_ROTATE:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    me->DisableRotate(false);
                    break;
                case EVENT_SPELL_FLAME_JETS:
                    me->MonsterTextEmote(TEXT_FLAME_JETS, 0, true);

                    if (me->GetMap()->Is25ManRaid() && me->GetVictim())
                    {
                        int32 dmg = urand(8483, 11198);
                        me->CastCustomSpell(me->GetVictim(), S_FLAME_JETS, &dmg, nullptr, nullptr, false);
                    }
                    else
                        DoCastVictim(S_FLAME_JETS);

                    events.Repeat(25000);
                    break;
                case EVENT_GRAB:
                {
                    std::list<Creature*> icl;
                    me->GetCreaturesWithEntryInRange(icl, 300.0f, NPC_IRON_CONSTRUCT);

                    std::vector<uint64> playerGUIDs;
                    Map::PlayerList const& pl = me->GetMap()->GetPlayers();
                    Player* temp = nullptr;

                    for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
                    {
                        temp = itr->GetSource();

                        if (!temp->IsAlive() || temp->GetExactDist2d(me) > 90.0f)
                            continue;
                        if (me->GetVictim() && temp->GetGUID() == me->GetVictim()->GetGUID())
                            continue;
                        bool found = false;
                        for (std::list<Creature*>::iterator itr = icl.begin(); itr != icl.end(); ++itr)
                            if ((*itr)->GetVictim() && (*itr)->GetVictim()->GetGUID() == temp->GetGUID())
                            {
                                found = true;
                                break;
                            }

                        if (!found)
                            playerGUIDs.push_back(temp->GetGUID());
                    }

                    if (!playerGUIDs.empty())
                    {
                        if (Player* target = ObjectAccessor::GetPlayer(*me, Trinity::Containers::SelectRandomContainerElement(playerGUIDs)))
                        {
                            me->MonsterYell(TEXT_SLAG_POT, LANG_UNIVERSAL, 0);
                            me->PlayDirectSound(SOUND_SLAG_POT);
                            DoCast(target, SPELL_GRAB, false);
                        }
                    }

                    events.Repeat(me->GetMap()->Is25ManRaid() ? 9000 : 24000); // +6000 below
                    events.DelayEvents(6000);
                }
                break;
                default:
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void EnterEvadeMode() override
    {
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        _DespawnAtEvade();
        instance->SetData(TYPE_IGNIS, FAIL);
    }

private:
    uint8 _counter;
    bool _shattered;
    uint32 _lastShatterMSTime;
};

class spell_ignis_scorch_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_ignis_scorch_AuraScript)

    void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (aurEff->GetTickNumber() == aurEff->GetTotalTicks())
            if (Unit* caster = GetCaster())
                if (Creature* summon = caster->SummonCreature(NPC_SCORCHED_GROUND, caster->GetPositionX() + 20.0f*cos(caster->GetOrientation()), caster->GetPositionY() + 20.0f*sin(caster->GetOrientation()), 361.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 30000))
                {
                    if (!summon->FindNearestCreature(NPC_WATER_TRIGGER, 25.0f, true)) // must be away from the water
                        summon->CastSpell(summon, (aurEff->GetId() == 62546 ? SPELL_SCORCHED_GROUND_10 : SPELL_SCORCHED_GROUND_25), true);
                }
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_ignis_scorch_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_ignis_grab_initial_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_ignis_grab_initial_SpellScript);

    void HandleScript(SpellEffIndex effIndex)
    {
        if (Unit* target = GetHitUnit())
            target->CastSpell(target, SPELL_GRAB_TRIGGERED, true);
    }

    void Register()
    {
        OnEffectHitTarget += SpellEffectFn(spell_ignis_grab_initial_SpellScript::HandleScript, EFFECT_2, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_ignis_slag_pot_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_ignis_slag_pot_AuraScript)

    void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (Unit* caster = GetCaster())
            if (Unit* target = GetTarget())
            {
                caster->CastSpell(target, (GetId() == 62717 ? 65722 : 65723), true);
                if (target->HasUnitState(UNIT_STATE_CASTING))
                    target->InterruptNonMeleeSpells(true);
            }
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
        {
            target->ApplySpellImmune(GetId(), IMMUNITY_ID, 62549, true);
            target->ApplySpellImmune(GetId(), IMMUNITY_ID, 63475, true);
        }
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
        {
            target->ApplySpellImmune(GetId(), IMMUNITY_ID, 62549, false);
            target->ApplySpellImmune(GetId(), IMMUNITY_ID, 63475, false);
            if (target->IsAlive())
                target->CastSpell(target, (GetId() == 62717 ? 62836 : 63536), true);
        }
    }

    void Register()
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_ignis_slag_pot_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
        OnEffectApply += AuraEffectApplyFn(spell_ignis_slag_pot_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
        AfterEffectRemove += AuraEffectRemoveFn(spell_ignis_slag_pot_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY, AURA_EFFECT_HANDLE_REAL);
    }
};

class achievement_ignis_shattered : public AchievementCriteriaScript
{
    public:
        achievement_ignis_shattered() : AchievementCriteriaScript("achievement_ignis_shattered") {}

        bool OnCheck(Player* /*player*/, Unit* target)
        {
            if (!target || target->GetTypeId() != TYPEID_UNIT)
                return false;
            
            if (!target->IsAIEnabled)
                return false;

            return (target->ToCreature()->AI()->GetData(1337) ? true : false);
        }
};

void AddSC_boss_ignis()
{
    new CreatureAILoader<boss_ignisAI>("boss_ignis");
    new CreatureAILoader<npc_ulduar_iron_constructAI>("npc_ulduar_iron_construct");
    new AuraScriptLoaderEx<spell_ignis_scorch_AuraScript>("spell_ignis_scorch");
    new SpellScriptLoaderEx<spell_ignis_grab_initial_SpellScript>("spell_ignis_grab_initial");
    new AuraScriptLoaderEx<spell_ignis_slag_pot_AuraScript>("spell_ignis_slag_pot");
    new achievement_ignis_shattered();
}