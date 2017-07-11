/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "trial_of_the_champion.h"
#include "ScriptedEscortAI.h"
#include "SpellScript.h"

enum EadricSpells
{
    //Eadric
    SPELL_EADRIC_ACHIEVEMENT                = 68197,
    ACHIEV_FACEROLLER                       = 3803,
    SPELL_EADRIC_CREDIT                     = 68575,

    SPELL_RADIANCE                          = 66935,
    SPELL_VENGEANCE                         = 66865,
    SPELL_HAMMER_JUSTICE                    = 66863,
    SPELL_HAMMER_RIGHTEOUS                  = 66867,
    SPELL_HAMMER_RIGHTEOUS_DAMAGE           = 66903,
    SPELL_HAMMER_RIGHTEOUS_ACTION_BAR       = 66904,
    SPELL_HAMMER_RIGHTEOUS_THROW_BACK       = 66905,
};

enum EadricEvents
{
    EVENT_SPELL_RADIANCE                    = 1,
    EVENT_SPELL_HAMMER_RIGHTEOUS,
};

enum PaletressSpells
{
    SPELL_PALETRESS_CREDIT                  = 68574,

    SPELL_SMITE                             = 66536,
    SPELL_HOLY_FIRE                         = 66538,
    SPELL_RENEW                             = 66537,

    SPELL_HOLY_NOVA                         = 66546,
    SPELL_SHIELD                            = 66515,
    SPELL_CONFESS                           = 66680,
    SPELL_SUMMON_MEMORY                     = 66545,

    //Memory
    SPELL_OLD_WOUNDS                        = 66620,
    SPELL_SHADOWS_PAST                      = 66619,
    SPELL_WAKING_NIGHTMARE                  = 66552,
};

enum PaletressEvents
{
    EVENT_SPELL_SMITE                       = 1,
    EVENT_SPELL_HOLY_FIRE,
    EVENT_SPELL_RENEW,

    EVENT_MEMORY_SCALE,
    EVENT_MEMORY_START_ATTACK,
    EVENT_SPELL_OLD_WOUNDS,
    EVENT_SPELL_SHADOWS_PAST,
    EVENT_SPELL_WAKING_NIGHTMARE,
};

#define TEXT_RADIATE                    "Eadric the Pure begins to radiate light. Shield your eyes!"

struct boss_eadricAI : public BossAI
{
    boss_eadricAI(Creature* creature) : BossAI(creature, BOSS_ARGENT_CHALLENGE) {}

    void Reset() override
    {
        _Reset();
        me->SetReactState(REACT_PASSIVE);
        instance->SetData(BOSS_ARGENT_CHALLENGE, NOT_STARTED);
    }
        
    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
            me->SetFacingTo(3 * M_PI / 2);
    }

    void KilledUnit(Unit* who) override
    {
        if (who->IsPlayer())
            Talk(urand(0, 1) ? TEXT_EADRIC_SLAIN_1 : TEXT_EADRIC_SLAIN_2);
    }

    void EnterCombat(Unit* who) override
    {
        _EnterCombat();
        events.Reset();
        events.ScheduleEvent(EVENT_SPELL_RADIANCE, 16000);
        events.ScheduleEvent(EVENT_SPELL_HAMMER_RIGHTEOUS, 25000);
        Talk(TEXT_EADRIC_AGGRO);
        DoCastSelf(SPELL_VENGEANCE);
        instance->SetData(BOSS_ARGENT_CHALLENGE, IN_PROGRESS);
    }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_HAMMER_RIGHTEOUS_THROW_BACK && me->GetHealth() == 1) // hammer throw back damage (15k)
            DoCastSelf(SPELL_EADRIC_ACHIEVEMENT, true);
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask)
    {
        if (damage >= me->GetHealth())
        {
            damage = me->GetHealth() - 1;
            if (me->getFaction() != 35)
            {
                DoCastAOE(SPELL_EADRIC_CREDIT, true);
                me->GetMap()->UpdateEncounterState(ENCOUNTER_CREDIT_CAST_SPELL, SPELL_PALETRESS_CREDIT, me); // paletress' spell credits encounter, but shouldn't credit achievements
                me->setFaction(35);
                events.Reset();
                Talk(TEXT_EADRIC_DEATH);
                me->getThreatManager().clearReferences();
                me->SetRegeneratingHealth(false);
                _EnterEvadeMode();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                instance->SetData(BOSS_ARGENT_CHALLENGE, DONE);
            }
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SPELL_RADIANCE:
                DoCastAOE(SPELL_RADIANCE);
                me->MonsterTextEmote(TEXT_RADIATE, 0, true);
                events.Repeat(16000);
                break;
            case EVENT_SPELL_HAMMER_RIGHTEOUS:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 55.0f, true))
                {
                    char buffer[100];
                    sprintf(buffer, "Eadric the Pure targets %s with the Hammer of the Righteous!", target->GetName().c_str());
                    me->MonsterTextEmote(buffer, 0, true);
                    Talk(TEXT_EADRIC_HAMMER);
                    DoCast(target, SPELL_HAMMER_JUSTICE, true);
                    DoCast(target, SPELL_HAMMER_RIGHTEOUS);
                }
                events.Repeat(25000);
                break;
            default:
                break;
        }
    }
};

struct boss_paletressAI : public BossAI
{
    boss_paletressAI(Creature* creature) : BossAI(creature, BOSS_ARGENT_CHALLENGE) {}

    void Reset() override
    {
        _Reset();
        _summoned = false;
        if (_memoryGUID)
        {
            if (Creature* memory = ObjectAccessor::GetCreature(*me, _memoryGUID))
                memory->DespawnOrUnsummon();
            _memoryGUID = 0;
        }
        me->SetReactState(REACT_PASSIVE);
        instance->SetData(BOSS_ARGENT_CHALLENGE, NOT_STARTED);
    }
        
    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == POINT_MOTION_TYPE && id == 1)
            me->SetFacingTo(3 * M_PI / 2);
    }

    void KilledUnit(Unit* who) override
    {
        if (who->IsPlayer())
            Talk(urand(0, 1) ? TEXT_PALETRESS_SLAIN_1 : TEXT_PALETRESS_SLAIN_2);
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        events.Reset();
        events.ScheduleEvent(EVENT_SPELL_HOLY_FIRE, urand(9000,12000));
        events.ScheduleEvent(EVENT_SPELL_SMITE, urand(2000,3000));
        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
        Talk(TEXT_PALETRESS_AGGRO);
        instance->SetData(BOSS_ARGENT_CHALLENGE, IN_PROGRESS);
    }

    void DoAction(int32 param) override
    {
        if (param == 1)
        {
            _memoryGUID = 0;
            me->RemoveAura(SPELL_SHIELD);
            Talk(TEXT_PALETRESS_MEMORY_DEFEATED);
        }
        else if (param == -1)
        {
            if (_memoryGUID)
                if (Creature* memory = ObjectAccessor::GetCreature(*me, _memoryGUID))
                {
                    memory->DespawnOrUnsummon();
                    _memoryGUID = 0;
                }
        }
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        //if( me->HasAura(SPELL_SHIELD) )
        //    return;

        if (!_summoned && HealthBelowPct(25))
        {
            me->InterruptNonMeleeSpells(true);
            Talk(TEXT_PALETRESS_MEMORY_SUMMON);
            DoCastAOE(SPELL_HOLY_NOVA);
            DoCastSelf(SPELL_SHIELD);
            DoCastAOE(SPELL_SUMMON_MEMORY);
            SummonMemory();
            DoCastAOE(SPELL_CONFESS);
            events.ScheduleEvent(EVENT_SPELL_RENEW, urand(6000, 8000));
            _summoned = true;
        }

        if (damage >= me->GetHealth())
        {
            damage = me->GetHealth() - 1;

            if (me->getFaction() != 35)
            {
                DoCastAOE(SPELL_PALETRESS_CREDIT, true); // achievements
                me->setFaction(35);
                events.Reset();
                Talk(TEXT_PALETRESS_DEATH);
                me->getThreatManager().clearReferences();
                me->SetRegeneratingHealth(false);
                _EnterEvadeMode();
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                instance->SetData(BOSS_ARGENT_CHALLENGE, DONE);
                instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET, 68206);
            }
        }
    }

    void JustSummoned(Creature* summon) override
    {
        instance->SetData(DATA_MEMORY_ENTRY, summon->GetEntry());
        _memoryGUID = summon->GetGUID();
    }

    void SummonMemory()
    {
        std::vector<uint32> spells = { 66704,66705,66706,66707,66709,66710,66711,66712,66713,66714,66715,66708,66708,66691,66692,66694,66695,66696,66697,66698,66699,66700,66701,66702,66703,66543 };
        DoCastSelf(Trinity::Containers::SelectRandomContainerElement(spells), true);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SPELL_SMITE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    DoCast(target, SPELL_SMITE);
                events.Repeat(urand(3000, 4000));
                break;
            case EVENT_SPELL_HOLY_FIRE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                    DoCast(target, SPELL_HOLY_FIRE);
                events.Repeat(urand(9000, 12000));
                break;
            case EVENT_SPELL_RENEW:
                if (!_memoryGUID)
                    break;
                if (urand(0, 1))
                    DoCastSelf(SPELL_RENEW);
                else if (Creature* memory = ObjectAccessor::GetCreature(*me, _memoryGUID))
                    if (memory->IsAlive())
                        DoCast(memory, SPELL_RENEW);
                events.Repeat(urand(15000, 17000));
                break;
            default:
                break;
        }
    }

private:
    bool _summoned;
    uint64 _memoryGUID;
};

struct npc_memoryAI : public ScriptedAI
{
    npc_memoryAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = me->GetInstanceScript();
        _events.Reset();
        me->SetReactState(REACT_PASSIVE);
        me->SetObjectScale(0.01f);
        _events.ScheduleEvent(EVENT_MEMORY_SCALE, 500);
    }

    void Reset() override {}

    void JustDied(Unit* /*killer*/) override
    {
        me->DespawnOrUnsummon(20000);
        if (instance)
            if (Creature* paletress = ObjectAccessor::GetCreature(*me, instance->GetData64(DATA_PALETRESS)))
                if(paletress->IsAIEnabled)
                    paletress->AI()->DoAction(1);
    }

    void UpdateAI(uint32 diff) override
    {
        if (UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_MEMORY_SCALE:
                    me->SetObjectScale(1.0f);
                    _events.ScheduleEvent(EVENT_MEMORY_START_ATTACK, 5000);
                    break;
                case EVENT_MEMORY_START_ATTACK:
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    if (Unit* target = me->SelectNearestTarget(200.0f))
                    {
                        AttackStart(target);
                        DoZoneInCombat();
                    }
                    me->SetReactState(REACT_AGGRESSIVE);
                    _events.ScheduleEvent(EVENT_SPELL_OLD_WOUNDS, 8000);
                    _events.ScheduleEvent(EVENT_SPELL_SHADOWS_PAST, 4000);
                    _events.ScheduleEvent(EVENT_SPELL_WAKING_NIGHTMARE, urand(20000, 30000));
                    break;
                case EVENT_SPELL_OLD_WOUNDS:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 10.0f, true))
                        DoCast(target, SPELL_OLD_WOUNDS, true);
                    _events.Repeat(12000);
                    break;
                case EVENT_SPELL_SHADOWS_PAST:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        DoCast(target, SPELL_SHADOWS_PAST);
                    _events.Repeat(urand(15000, 20000));
                    break;
                case EVENT_SPELL_WAKING_NIGHTMARE:
                    DoCastSelf(SPELL_WAKING_NIGHTMARE);
                    _events.Repeat(35000);
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }

private:
    InstanceScript* instance;
    EventMap _events;
};

enum ArgentSoldierSpells
{
    // monk
    SPELL_FLURRY_OF_BLOWS                   = 67233,
    SPELL_PUMMEL                            = 67235,
    SPELL_DIVINE_SHIELD                     = 67251, 
    SPELL_FINAL_MEDITATION                  = 67255,

    // priestess
    SPELL_HOLY_SMITE_N                      = 36176,
    SPELL_HOLY_SMITE_H                      = 67289,
    SPELL_FOUNTAIN_OF_LIGHT                 = 67194,
    NPC_FOUNTAIN_OF_LIGHT                   = 35311,
    SPELL_SHADOW_WORD_PAIN_N                = 34941,
    SPELL_SHADOW_WORD_PAIN_H                = 34942,
    SPELL_MIND_CONTROL                      = 67229,

    // lightwielder
    SPELL_BLAZING_LIGHT                     = 67247,
    SPELL_CLEAVE                            = 15284,
    SPELL_UNBALANCING_STRIKE                = 67237,
};

#define SPELL_HOLY_SMITE                DUNGEON_MODE(SPELL_HOLY_SMITE_N, SPELL_HOLY_SMITE_H)
#define SPELL_SHADOW_WORD_PAIN            DUNGEON_MODE(SPELL_SHADOW_WORD_PAIN_N, SPELL_SHADOW_WORD_PAIN_H)

enum ArgentSoldierEvents
{
    EVENT_MONK_SPELL_FLURRY_OF_BLOWS        = 1,
    EVENT_MONK_SPELL_PUMMEL,
    EVENT_PRIESTESS_SPELL_HOLY_SMITE,
    EVENT_PRIESTESS_SPELL_SHADOW_WORD_PAIN,
    EVENT_PRIESTESS_SPELL_FOUNTAIN_OF_LIGHT,
    EVENT_PRIESTESS_SPELL_MIND_CONTROL,
    EVENT_LIGHTWIELDER_SPELL_BLAZING_LIGHT,
    EVENT_LIGHTWIELDER_SPELL_CLEAVE,
    EVENT_LIGHTWIELDER_SPELL_UNBALANCING_STRIKE,
};

struct npc_argent_soldierAI : public npc_escortAI
{
    npc_argent_soldierAI(Creature* creature) : npc_escortAI(creature)
    {
        instance = me->GetInstanceScript();
        me->SetReactState(REACT_PASSIVE);
        SetDespawnAtEnd(false);
        _wp = 0;
    }

    InstanceScript* instance;
    EventMap _events;
    uint8 _wp;
    bool _check;

    void Reset() override
    {
        _events.Reset();
        _check = false;
    }

    void WaypointReached(uint32 point) override
    {
        if (point == 1)
        {
            switch (_wp)
            {
                case 0:
                    me->SetFacingTo(5.4f);
                    break;
                case 1:
                    me->SetFacingTo(4.6f);
                    break;
                case 2:
                    me->SetFacingTo(4.0f);
                    break;
            }
        }
    }

    void SetData(uint32 type, uint32 /*uiData*/) override
    {
        AddWaypoint(0, me->GetPositionX(), 660.0f, 411.80f);
        switch (me->GetEntry())
        {
            case NPC_ARGENT_LIGHTWIELDER:
                switch (type)
                {
                    case 0:
                        AddWaypoint(1,716.321f,647.047f,411.93f);
                        break;
                    case 1:
                        AddWaypoint(1,742.44f,650.29f,411.79f);
                        break;
                    case 2:
                        AddWaypoint(1,772.6314f,651.7f,411.93f);
                        break;
                }
                break;
            case NPC_ARGENT_MONK:
                switch (type)
                {
                    case 0:
                        AddWaypoint(1, 717.86f, 649.0f, 411.923f);
                        break;
                    case 1:
                        AddWaypoint(1, 746.73f, 650.24f, 411.56f);
                        break;
                    case 2:
                        AddWaypoint(1, 775.567f, 648.26f, 411.93f);
                        break;
                }
                break;
            case NPC_PRIESTESS:
                switch (type)
                {
                    case 0:
                        AddWaypoint(1, 719.872f, 650.94f, 411.93f);
                        break;
                    case 1:
                        AddWaypoint(1, 750.72f, 650.20f, 411.77f);
                        break;
                    case 2:
                        AddWaypoint(1, 777.78f, 645.70f, 411.93f);
                        break;
                }
                break;
        }

        Start(false, true, 0);
        _wp = type;
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (_check && damage >= me->GetHealth())
        {
            _check = false;
            damage = me->GetHealth()-1;
            _events.DelayEvents(10000);
            DoCastSelf(SPELL_DIVINE_SHIELD, true);
            DoCastAOE(SPELL_FINAL_MEDITATION, true);
        }
    }

    void EnterCombat(Unit* /*who*/)
    {
        switch (me->GetEntry())
        {
            case NPC_ARGENT_MONK:
                _events.RescheduleEvent(EVENT_MONK_SPELL_FLURRY_OF_BLOWS, 5000);
                _events.RescheduleEvent(EVENT_MONK_SPELL_PUMMEL, 7000);
                if (IsHeroic())
                    _check = true;
                break;
            case NPC_PRIESTESS:
                _events.RescheduleEvent(EVENT_PRIESTESS_SPELL_HOLY_SMITE, urand(5000,8000));
                _events.RescheduleEvent(EVENT_PRIESTESS_SPELL_SHADOW_WORD_PAIN, urand(3000,6000));
                _events.RescheduleEvent(EVENT_PRIESTESS_SPELL_FOUNTAIN_OF_LIGHT, urand(8000,15000));
                if (IsHeroic())
                    _events.RescheduleEvent(EVENT_PRIESTESS_SPELL_MIND_CONTROL, 12000);
                break;
            case NPC_ARGENT_LIGHTWIELDER:
                _events.RescheduleEvent(EVENT_LIGHTWIELDER_SPELL_BLAZING_LIGHT, urand(12000,15000));
                _events.RescheduleEvent(EVENT_LIGHTWIELDER_SPELL_CLEAVE, urand(3000,5000));
                if (IsHeroic())
                    _events.RescheduleEvent(EVENT_LIGHTWIELDER_SPELL_UNBALANCING_STRIKE, urand(8000, 12000));
                break;
        }                
    }

    void UpdateAI(uint32 diff) override
    {
        npc_escortAI::UpdateAI(diff);

        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_MONK_SPELL_FLURRY_OF_BLOWS:
                    DoCastSelf(SPELL_FLURRY_OF_BLOWS);
                    _events.Repeat(urand(12000, 18000));
                    break;
                case EVENT_MONK_SPELL_PUMMEL:
                    DoCastVictim(SPELL_PUMMEL);
                    _events.Repeat(urand(8000, 11000));
                    break;

                case EVENT_PRIESTESS_SPELL_HOLY_SMITE:
                    DoCastVictim(SPELL_HOLY_SMITE);
                    _events.Repeat(urand(6000, 8000));
                    break;
                case EVENT_PRIESTESS_SPELL_SHADOW_WORD_PAIN:
                    DoCastVictim(SPELL_SHADOW_WORD_PAIN);
                    _events.Repeat(urand(12000, 15000));
                    break;
                case EVENT_PRIESTESS_SPELL_FOUNTAIN_OF_LIGHT:
                    DoCastAOE(SPELL_FOUNTAIN_OF_LIGHT);
                    _events.Repeat(urand(35000, 45000));
                    break;
                case EVENT_PRIESTESS_SPELL_MIND_CONTROL:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        DoCast(target, SPELL_MIND_CONTROL);
                    _events.Repeat(urand(22000, 30000));
                    break;
                case EVENT_LIGHTWIELDER_SPELL_BLAZING_LIGHT:
                    if (Unit* target = DoSelectLowestHpFriendly(40.0f))
                    {
                        if (!target)
                            target = me;

                        DoCast(target, SPELL_BLAZING_LIGHT);
                    }
                    _events.Repeat(urand(8000, 12000));
                break;
                case EVENT_LIGHTWIELDER_SPELL_CLEAVE:
                    DoCastVictim(SPELL_CLEAVE);
                    _events.Repeat(urand(6000, 8000));
                    break;
                case EVENT_LIGHTWIELDER_SPELL_UNBALANCING_STRIKE:
                    DoCastVictim(SPELL_UNBALANCING_STRIKE);
                    _events.Repeat(urand(12000, 15000));
                    break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        me->DespawnOrUnsummon(10000);
        if (instance)
            instance->SetData(DATA_ARGENT_SOLDIER_DEFEATED, 0);
    }
};

class spell_eadric_radiance_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_eadric_radiance_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        std::list<WorldObject*> tmplist;
        for (std::list<WorldObject*>::const_iterator itr = targets.begin(); itr != targets.end(); ++itr)
            if ((*itr)->ToUnit()->HasInArc(M_PI, GetCaster()))
                tmplist.push_back(*itr);

        targets.clear();
        targets = tmplist;
    }

    void Register()
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_eadric_radiance_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_eadric_radiance_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_toc5_light_rain_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_toc5_light_rain_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        for (std::list<WorldObject*>::iterator itr = targets.begin(); itr != targets.end(); )
        {
            if ((*itr)->IsUnit())
                if ((*itr)->ToCreature()->GetEntry() == NPC_FOUNTAIN_OF_LIGHT)
                {
                    targets.erase(itr);
                    itr = targets.begin();
                    continue;
                }
            ++itr;
        }
    }

    void Register()
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_toc5_light_rain_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
    }
};

class spell_reflective_shield_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_reflective_shield_AuraScript)

    void HandleAfterEffectAbsorb(AuraEffect * aurEff, DamageInfo & dmgInfo, uint32 & absorbAmount)
    {
        if (Unit* attacker = dmgInfo.GetAttacker())
            if (GetOwner() && attacker->GetGUID() != GetOwner()->GetGUID())
            {
                int32 damage = (int32)(absorbAmount*0.25f);
                GetOwner()->ToUnit()->CastCustomSpell(attacker, 33619, &damage, nullptr, nullptr, true);
            }
    }

    void Register()
    {
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_reflective_shield_AuraScript::HandleAfterEffectAbsorb, EFFECT_0);
    }
};

void AddSC_boss_argent_challenge()
{
    new CreatureAILoader<boss_eadricAI>("boss_eadric");
    new CreatureAILoader<boss_paletressAI>("boss_paletress");
    new CreatureAILoader<npc_memoryAI>("npc_memory");
    new CreatureAILoader<npc_argent_soldierAI>("npc_argent_soldier");
    new SpellScriptLoaderEx<spell_eadric_radiance_SpellScript>("spell_eadric_radiance");
    new SpellScriptLoaderEx<spell_toc5_light_rain_SpellScript>("spell_toc5_light_rain");
    new AuraScriptLoaderEx<spell_reflective_shield_AuraScript>("spell_reflective_shield");
}
