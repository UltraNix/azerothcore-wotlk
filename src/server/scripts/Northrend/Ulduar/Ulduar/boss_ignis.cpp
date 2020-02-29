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

enum IgnisTheFurnaceMasterSpells
{
    SPELL_FLAME_JETS_10                     = 62680,
    SPELL_FLAME_JETS_25                     = 63472,
    SPELL_SCORCH_10                         = 62546,
    SPELL_SCORCH_25                         = 63474,
    SPELL_ACTIVATE_CONSTRUCT                = 62488,
    SPELL_STRENGTH_OF_THE_CREATOR           = 64473,
    SPELL_SLAG_POT_10                       = 62717,
    SPELL_SLAG_POT_25                       = 63477,
    SPELL_BERSERK                           = 64238,
    SPELL_GRAB                              = 62707,
    SPELL_GRAB_TRIGGERED                    = 62708,
    SPELL_GRAB_CONTROL_2                    = 62711,
    SPELL_SCORCHED_GROUND_10                = 62548,
    SPELL_SCORCHED_GROUND_25                = 63476,
    SPELL_HEAT_AREA                         = 62343,
    SPELL_HEAT_BUFF                         = 65667,
    SPELL_MOLTEN                            = 62373,
    SPELL_BRITTLE_10                        = 62382,
    SPELL_BRITTLE_25                        = 67114,
    SPELL_SHATTER                           = 62383,
    BOSS_IGNIS                              = 33118,
    NPC_IRON_CONSTRUCT                      = 33121,
    NPC_SCORCHED_GROUND                     = 33123,
    NPC_WATER_TRIGGER                       = 22515
};

std::string const TEXT_AGGRO               = "Insolent whelps! Your blood will temper the weapons used to reclaim this world!";
std::string const TEXT_ACTIVATE_CONSTRUCT  = "Arise, soldiers of the Iron Crucible! The Makers' will be done!";
std::string const TEXT_SCORCH_1            = "Let the inferno consume you!";
std::string const TEXT_SCORCH_2            = "BURN! Burn in the makers fire!";
std::string const TEXT_SLAG_POT            = "I will burn away your impurities!";
std::string const TEXT_SLAY_1              = "More scraps for the scrapheap!";
std::string const TEXT_SLAY_2              = "Your bones will serve as kindling!";
std::string const TEXT_BERSERK             = "Let it be finished!";
std::string const TEXT_DEATH               = "I. Have. Failed.";
std::string const TEXT_FLAME_JETS          = "Ignis The Furnace Master begins to cast Flame Jets!";

enum IgnisTheFuranceMasterSounds
{
    SOUND_AGGRO                             = 15564,
    SOUND_ACTIVATE_CONSTRUCT                = 15565,
    SOUND_SLAG_POT                          = 15566,
    SOUND_SCORCH_1                          = 15567,
    SOUND_SCORCH_2                          = 15568,
    SOUND_SLAY_1                            = 15569,
    SOUND_SLAY_2                            = 15570,
    SOUND_BERSERK                           = 15571,
    SOUND_DEATH                             = 15572
};

enum IgnisTheFuranceMasterMisc
{
    ACHIEV_STOKIN_THE_FURNACE_EVENT         = 20951,
    DATA_IGNIS_THE_FURANCE_SHATTERED
};

enum IgnisTheFuranceMasterEvents
{
    EVENT_NONE                              = 0,
    EVENT_ACTIVATE_CONSTRUCT,
    EVENT_SPELL_SCORCH,
    EVENT_ENABLE_ROTATE,
    EVENT_SPELL_FLAME_JETS,
    EVENT_GRAB,
};

constexpr uint32 SPELL_FREEZE_IRON_CONSTRUCT{ 38757 };

struct npc_ulduar_iron_constructAI : public ScriptedAI
{
    npc_ulduar_iron_constructAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = me->GetInstanceScript();
        DoCastSelf(SPELL_FREEZE_IRON_CONSTRUCT, true);
    }

    void Reset() override
    {
        scheduler.CancelAll();

        me->SetReactState(REACT_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void JustReachedHome() override
    {
        DoCastSelf(SPELL_FREEZE_IRON_CONSTRUCT, true);
    }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_ACTIVATE_CONSTRUCT)
        {
            scheduler.Schedule(2s, [&](TaskContext /*func*/)
            {
                if (Creature* ignis = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_IGNIS)))
                {
                    if (ignis->IsAlive() && ignis->IsInCombat())
                    {
                        me->RemoveAura(SPELL_FREEZE_IRON_CONSTRUCT);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                        me->SetReactState(REACT_AGGRESSIVE);
                    }
                }
            });

            scheduler.Schedule(1s, [&](TaskContext func)
            {
                if (Aura* aura = me->GetAura(SPELL_MOLTEN))
                {
                    if (me->FindNearestCreature(NPC_WATER_TRIGGER, 18.0f, true))
                    {
                        me->RemoveAura(aura);
                        DoCastSelf(RAID_MODE(SPELL_BRITTLE_10, SPELL_BRITTLE_25), true);
                    }
                }

                func.Repeat(1500ms);
            });

            if (instance)
            {
                if (Creature* ignis = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_IGNIS)))
                {
                    ignis->CastSpell(ignis, SPELL_STRENGTH_OF_THE_CREATOR, true);
                    if (ignis->GetVictim())
                        AttackStart(ignis->GetVictim());
                    DoZoneInCombat();
                }
            }
        }
        else if (spell->Id == SPELL_HEAT_BUFF)
        {
            if (Aura* aura = me->GetAura(SPELL_HEAT_BUFF))
            {
                if (aura->GetStackAmount() >= 20)
                {
                    DoCastSelf(SPELL_MOLTEN, true);
                    DoResetThreat();
                }
            }
        }
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (damage >= RAID_MODE(3000U, 5000U) && me->GetAura(RAID_MODE(SPELL_BRITTLE_10, SPELL_BRITTLE_25)))
        {
            DoCastSelf(SPELL_SHATTER, true);
            Unit::Kill(attacker, me);

            if (instance)
            {
                if (Creature* ignis = ObjectAccessor::GetCreature(*me, instance->GetData64(TYPE_IGNIS)))
                    if (ignis->IsAIEnabled)
                        ignis->AI()->SetData(DATA_IGNIS_THE_FURANCE_SHATTERED, 0);
            }
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

        scheduler.Update(diff);

        DoMeleeAttackIfReady();
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }

private:
    InstanceScript* instance;
    TaskScheduler scheduler;
};

struct npc_scorched_groundAI : public ScriptedAI
{
    npc_scorched_groundAI(Creature* creature) : ScriptedAI(creature ) { }

    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void UpdateAI(uint32 /*diff*/) override { }
    void EnterEvadeMode() override { }
};

struct boss_ignisAI : public BossAI
{
    boss_ignisAI(Creature* creature) : BossAI(creature, TYPE_IGNIS) { }

    void Reset() override
    {
        _fightTimer = 0;
        _Reset();
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        _counter = 0;
        _shattered = false;
        _lastShatterMSTime = 0;
        me->RemoveAurasDueToSpell(SPELL_STRENGTH_OF_THE_CREATOR);
        instance->SetData(TYPE_IGNIS, NOT_STARTED);
        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_STOKIN_THE_FURNACE_EVENT);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        _fightTimer = getMSTime();

        std::list<Creature*> list;
        me->GetCreaturesWithEntryInRange(list, 300.0f, NPC_IRON_CONSTRUCT);

        for (Creature* creature : list)
        {
            if (!creature->IsAlive())
            {
                creature->Respawn();
                creature->UpdatePosition(creature->GetHomePosition(), true);
                creature->StopMovingOnCurrentPos();
            }

            if (creature->IsAIEnabled)
                creature->AI()->Reset();

            if (!creature->HasAura(SPELL_FREEZE_IRON_CONSTRUCT))
                creature->CastSpell(creature, SPELL_FREEZE_IRON_CONSTRUCT, true);
        }

        _shattered = false;
        _lastShatterMSTime = 0;

        events.Reset();
        events.ScheduleEvent(EVENT_ACTIVATE_CONSTRUCT, RAID_MODE(40s, 30s), 1);
        events.ScheduleEvent(EVENT_SPELL_SCORCH, 12s);
        events.ScheduleEvent(EVENT_SPELL_FLAME_JETS, 32s);
        events.ScheduleEvent(EVENT_GRAB, 25s);

        me->MonsterYell(TEXT_AGGRO, LANG_UNIVERSAL, 0);
        me->PlayDirectSound(SOUND_AGGRO);

        instance->SetData(TYPE_IGNIS, IN_PROGRESS);
        instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_STOKIN_THE_FURNACE_EVENT);
        instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_STOKIN_THE_FURNACE_EVENT);

        me->RemoveAurasDueToSpell(SPELL_STRENGTH_OF_THE_CREATOR);
    }

    void SetData(uint32 id, uint32 /*value*/) override
    {
        if (id == DATA_IGNIS_THE_FURANCE_SHATTERED)
        {
            if (_lastShatterMSTime)
                if (getMSTimeDiff(_lastShatterMSTime, World::GetGameTimeMS()) <= 5000)
                    _shattered = true;

            _lastShatterMSTime = World::GetGameTimeMS();
        }
    }

    uint32 GetData(uint32 id) const override
    {
        if (id == DATA_IGNIS_THE_FURANCE_SHATTERED)
            return (_shattered ? 1 : 0);
        return 0;
    }

    void KilledUnit(Unit* victim) override
    {
        if (victim->IsPlayer() && roll_chance_i(25))
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

    void JustDied(Unit* killer) override
    {
        me->MonsterYell(TEXT_DEATH, LANG_UNIVERSAL, 0);
        me->PlayDirectSound(SOUND_DEATH);

        if (Map* map = me->GetMap())
            CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry, Difficulty(map->GetDifficulty()), "", 15000, _fightTimer);

        instance->SetData(TYPE_IGNIS, DONE);

        CheckConstructs();
    }

    void CheckConstructs()
    {
        std::list<Creature*> constructs;
        GetCreatureListWithEntryInGrid(constructs, me, NPC_IRON_CONSTRUCT, 200.0f);

        for (Creature* creature : constructs)
            if (creature->IsAlive() && creature->IsInCombat())
                creature->DisappearAndDie();
    }

    void SpellHit(Unit* caster, const SpellInfo* spell) override
    {
        if (caster && spell->Id == SPELL_GRAB_CONTROL_2)
            DoCast(caster, RAID_MODE(SPELL_SLAG_POT_10, SPELL_SLAG_POT_25), true);
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
                    events.Repeat(30s);
                    //! post nerf values
                    //events.Repeat(RAID_MODE(40s, 30s));
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
                    DoCastVictim(RAID_MODE(SPELL_SCORCH_10, SPELL_SCORCH_25));
                    events.Repeat(20s);
                    events.RescheduleEvent(EVENT_ENABLE_ROTATE, 3s);
                    break;
                case EVENT_ENABLE_ROTATE:
                    me->SetControlled(false, UNIT_STATE_ROOT);
                    me->DisableRotate(false);
                    break;
                case EVENT_SPELL_FLAME_JETS:
                    me->MonsterTextEmote(TEXT_FLAME_JETS.c_str(), 0, true);

                    DoCastVictim(RAID_MODE(SPELL_FLAME_JETS_10, SPELL_FLAME_JETS_25));

                    events.Repeat(25s);
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

                    events.Repeat(me->GetMap()->Is25ManRaid() ? 9s : 24s); // +6000 below
                    events.DelayEvents(6s, 0);
                    break;
                }
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
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
    uint32 _fightTimer;
};

constexpr uint32 SPELL_IGNIS_SCORCH_TRIGGER_AURA{ 62546 };
class spell_ignis_scorch_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_ignis_scorch_AuraScript)

    void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (aurEff->GetTickNumber() == aurEff->GetTotalTicks())
            if (Unit* caster = GetCaster())
                if (Creature* summon = caster->SummonCreature(NPC_SCORCHED_GROUND, caster->GetPositionX() + 20.0f*cos(caster->GetOrientation()), caster->GetPositionY() + 20.0f*sin(caster->GetOrientation()), 361.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 45000))
                {
                    if (!summon->FindNearestCreature(NPC_WATER_TRIGGER, 25.0f, true)) // must be away from the water
                        summon->CastSpell(summon, (aurEff->GetId() == SPELL_IGNIS_SCORCH_TRIGGER_AURA ? SPELL_SCORCHED_GROUND_10 : SPELL_SCORCHED_GROUND_25), true);
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

constexpr uint32 SPELL_SLAG_POT_DAMAGE_4500{ 65722 };
constexpr uint32 SPELL_SLAG_POT_DAMAGE_6000{ 65723 };
constexpr uint32 SPELL_SCORCH_DAMAGE_2000{ 62549 };
constexpr uint32 SPELL_SCORCH_DAMAGE_3000{ 63475 };
constexpr uint32 SPELL_SLAG_POT_IMBUED_10{ 62836 };
constexpr uint32 SPELL_SLAG_POT_IMBUED_25{ 63536 };

class spell_ignis_slag_pot_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_ignis_slag_pot_AuraScript)

    void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (Unit* caster = GetCaster())
        {
            if (Unit* target = GetTarget())
            {
                caster->CastSpell(target, (GetId() == SPELL_SLAG_POT_10 ? SPELL_SLAG_POT_DAMAGE_4500 : SPELL_SLAG_POT_DAMAGE_6000), true);
                if (target->HasUnitState(UNIT_STATE_CASTING))
                    target->InterruptNonMeleeSpells(true);
            }
        }
    }

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
        {
            target->ApplySpellImmune(SPELL_SCORCH_DAMAGE_2000, IMMUNITY_ID, SPELL_SCORCH_DAMAGE_2000, true);
            target->ApplySpellImmune(SPELL_SCORCH_DAMAGE_3000, IMMUNITY_ID, SPELL_SCORCH_DAMAGE_3000, true);
        }
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* target = GetTarget())
        {
            target->ApplySpellImmune(SPELL_SCORCH_DAMAGE_2000, IMMUNITY_ID, SPELL_SCORCH_DAMAGE_2000, false);
            target->ApplySpellImmune(SPELL_SCORCH_DAMAGE_3000, IMMUNITY_ID, SPELL_SCORCH_DAMAGE_3000, false);
            if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
            {
                if (target->IsAlive())
                    target->CastSpell(target, (GetId() == SPELL_SLAG_POT_10 ? SPELL_SLAG_POT_IMBUED_10 : SPELL_SLAG_POT_IMBUED_25), true);
            }
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
            if (!target || target->GetTypeId() != TYPEID_UNIT || !target->IsAIEnabled)
                return false;

            return static_cast<bool>(target->ToCreature()->AI()->GetData(DATA_IGNIS_THE_FURANCE_SHATTERED));
        }
};

void AddSC_boss_ignis()
{
    new CreatureAILoader<boss_ignisAI>("boss_ignis");
    new CreatureAILoader<npc_ulduar_iron_constructAI>("npc_ulduar_iron_construct");
    new CreatureAILoader<npc_scorched_groundAI>("npc_scorched_ground");
    new AuraScriptLoaderEx<spell_ignis_scorch_AuraScript>("spell_ignis_scorch");
    new SpellScriptLoaderEx<spell_ignis_grab_initial_SpellScript>("spell_ignis_grab_initial");
    new AuraScriptLoaderEx<spell_ignis_slag_pot_AuraScript>("spell_ignis_slag_pot");
    new achievement_ignis_shattered();
}