/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "karazhan.h"

enum OperaYells
{
    // Barnes
    SAY_BARNES_BEGIN,
    SAY_BARNES_WELCOME,
    SAY_BARNES_OZ_1,
    SAY_BARNES_OZ_2,
    SAY_BARNES_OZ_3,
    SAY_BARNES_HOOD_1,
    SAY_BARNES_HOOD_2,
    SAY_BARNES_HOOD_3,
    SAY_BARNES_ROMEO_JULIANNE_1,
    SAY_BARNES_ROMEO_JULIANNE_2,
    SAY_BARNES_ROMEO_JULIANNE_3,

    // Big Bad Wolf
    SAY_WOLF_AGGRO              = 0,
    SAY_WOLF_SLAY,
    SAY_WOLF_HOOD,

    // Julianne
    SAY_JULIANNE_AGGRO          = 0,
    SAY_JULIANNE_ENTER,
    SAY_JULIANNE_DEATH01,
    SAY_JULIANNE_DEATH02,
    SAY_JULIANNE_RESURRECT,
    SAY_JULIANNE_SLAY,

    // Romulo
    SAY_ROMULO_AGGRO            = 0,
    SAY_ROMULO_DEATH,
    SAY_ROMULO_ENTER,
    SAY_ROMULO_RESURRECT,
    SAY_ROMULO_SLAY,

    // Crone
    SAY_CRONE_AGGRO             = 0,
    SAY_CRONE_DEATH,
    SAY_CRONE_SLAY,

    // Dorothee
    SAY_DOROTHEE_DEATH          = 0,
    SAY_DOROTHEE_SUMMON,
    SAY_DOROTHEE_TITO_DEATH,
    SAY_DOROTHEE_AGGRO,

    // Roar
    SAY_ROAR_AGGRO              = 0,
    SAY_ROAR_DEATH,
    SAY_ROAR_SLAY,

    // Strawman
    SAY_STRAWMAN_AGGRO          = 0,
    SAY_STRAWMAN_DEATH,
    SAY_STRAWMAN_SLAY,

    // Tinhead
    SAY_TINHEAD_AGGRO           = 0,
    SAY_TINHEAD_DEATH,
    SAY_TINHEAD_SLAY,
    EMOTE_RUST,
};

enum OperaSpells
{
    // Barnes
    SPELL_TUXEDO_TRANSFORM      = 32616,
    SPELL_SPOTLIGHT             = 25824,

    // Big Bad Wolf
    SPELL_PICK_RED_RIDING_HOOD  = 30769,
    SPELL_RED_RIDING_HOOD       = 30768,
    SPELL_TERRIFYING_HOWL       = 30752,
    SPELL_WIDE_SWIPE            = 30761,

    // Julianne
    SPELL_BLINDING_PASSION      = 30890,
    SPELL_DEVOTION              = 30887,
    SPELL_ETERNAL_AFFECTION     = 30878,
    SPELL_POWERFUL_ATTRACTION   = 30889,
    SPELL_DRINK_POISON          = 30907,
    SPELL_UNDYING_LOVE          = 30951,

    // Romulo
    SPELL_BACKWARD_LUNGE        = 30815,
    SPELL_DARING                = 30841,
    SPELL_DEADLY_SWATHE         = 30817,
    SPELL_POISON_THRUST         = 30822,

    // Crone
    SPELL_CHAIN_LIGHTNING       = 32337,
    SPELL_CYCLONE_AURA          = 32334,
    SPELL_CYCLONE_VISUAL        = 32332,

    // Dorothee
    SPELL_FRIGHTENED_SCREAM     = 31013,
    SPELL_SUMMON_TITO           = 31014,
    SPELL_WATER_BOLT            = 31012,

    // Tito
    SPELL_ANNOYING_YIPPING      = 31015,

    // Roar
    SPELL_MANGLE                = 31041,
    SPELL_SHRED                 = 31042,
    SPELL_FRIGHTENED_ROAR       = 31013,

    // Strawman
    SPELL_BRAIN_BASH            = 31046,
    SPELL_BRAIN_WIPE            = 31069,
    SPELL_BURNING_STRAW         = 31075,

    // Tinhead
    SPELL_CLEAVE                = 31043,
    SPELL_RUST                  = 31086,
};

enum OperaEvents
{
    // Barnes
    EVENT_BARNES_BEGIN          = 1,
    EVENT_BARNES_OPEN_DOOR,
    EVENT_RED_RIDING_HOOD_1,
    EVENT_RED_RIDING_HOOD_2,
    EVENT_RED_RIDING_HOOD_3,
    EVENT_WIZARD_OF_OZ_1,
    EVENT_WIZARD_OF_OZ_2,
    EVENT_WIZARD_OF_OZ_3,
    EVENT_ROMULO_AND_JULIANNE_1,
    EVENT_ROMULO_AND_JULIANNE_2,
    EVENT_ROMULO_AND_JULIANNE_3,
    EVENT_RETURN,
    EVENT_CHECK_ENCOUNTER,
    EVENT_TALK_DOROTHEE,
    EVENT_AGGRO_DOROTHEE,
    EVENT_AGGRO_STRAWMAN,
    EVENT_AGGRO_TINHEAD,
    EVENT_AGGRO_ROAR,

    // Big Bad Wolf
    EVENT_RED_RIDING_HOOD_SPELL  = 1,
    EVENT_TERRYFING_HOWL,
    EVENT_WIDE_SWIPE,

    // Julianne
    EVENT_AGGRO                 = 1,
    EVENT_BLINDING_PASSION,
    EVENT_DEVOTION,
    EVENT_ETERNAL_AFFECTION,
    EVENT_POWERFUL_ATTRACTION,
    EVENT_DRINK_POISON,
    EVENT_SUMMON_ROMULO,

    // Romulo
    EVENT_BACKWARD_LUNGE        = 1,
    EVENT_DARING,
    EVENT_DEADLY_SWATCHE,
    EVENT_POISONED_THRUST,
    EVENT_RES_JULIANNE,

    // Crone
    EVENT_CHAIN_LIGHTNING       = 1,
    EVENT_CYCLONE,

    // Dorothee
    EVENT_FRIGHTENED_SCREAM     = 1,
    EVENT_SUMMON_TITO,
    EVENT_WATER_BOLT,

    // Tito
    EVENT_ANNOYING_YIPPING      = 1,

    // Roar
    EVENT_MANGLE                = 1,
    EVENT_SHRED,
    EVENT_FRIGHTENED_ROAR,

    // Strawman
    EVENT_BRAIN_BASH            = 1,
    EVENT_BRAIN_WIPE,

    // Tinhead
    EVENT_CLEAVE                = 1,
    EVENT_RUST,

    // Shared
    EVENT_KILL_TALK             = 255
};

enum OperaMisc
{
    // Barnes
    MENU_ID_BEGIN               = 7422,
    PATH_STAGE                  = 1358230,
    PATH_RETURN                 = 1358231,
    NPC_SPOTLIGHT               = 19525,
    ACTION_COMPLETED            = 0,
    ACTION_CLEANUP              = 1,
    ACTION_SCHEDULE_OZ          = 2,

    // Grandmother
    MENU_ID_SUMMON_WOLF         = 7443,
    NPC_BIG_BAD_WOLF            = 17521,
    NPC_GRANDMOTHER             = 17603,

    // RAJ
    ACTION_RESURRECT            = 1,
    GROUP_COMBAT                = 1,

    // Oz
    PHASE_NOT_SPAWNED           = 1,
    DATA_ADD_KILLED             = 1,
    DATA_TITO_DIED,
    NPC_CYCLONE                 = 18412
};

struct npc_barnesAI : public ScriptedAI
{
    npc_barnesAI(Creature* creature) : ScriptedAI(creature), _summons(me)
    {
        _instance = me->GetInstanceScript();
        _eventType = _instance->GetData(DATA_OPERA_PERFORMANCE);
    }

    void HandleDoor(uint32 goData, bool open)
    {
        if (auto go = _instance->GetGameObject(goData))
            go->SetGoState(open ? GO_STATE_ACTIVE : GO_STATE_READY);
    }

    void sGossipSelect(Player* player, uint32 menuId, uint32 /*gossipListId*/) override
    {
        if (menuId == MENU_ID_BEGIN)
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            _events.Reset();
            _events.ScheduleEvent(EVENT_BARNES_BEGIN, 1s);
        }
    }

    void DoAction(int32 actionId) override
    {
        switch (actionId)
        {
            case ACTION_COMPLETED:
                HandleDoor(DATA_GO_STAGEDOORLEFT, true);
                HandleDoor(DATA_GO_STAGEDOORRIGHT, true);
                me->DespawnOrUnsummon();
                break;
            case ACTION_CLEANUP:
                _summons.DespawnAll();
                me->UpdatePosition(me->GetHomePosition(), true);
                HandleDoor(DATA_GO_CURTAINS, false);
                HandleDoor(DATA_GO_STAGEDOORLEFT, true);
                break;
            case ACTION_SCHEDULE_OZ:
                _events.ScheduleEvent(EVENT_TALK_DOROTHEE, 3s);
                _events.ScheduleEvent(EVENT_AGGRO_DOROTHEE, 13s);
                _events.ScheduleEvent(EVENT_AGGRO_ROAR, 18s);
                _events.ScheduleEvent(EVENT_AGGRO_STRAWMAN, 27s);
                _events.ScheduleEvent(EVENT_AGGRO_TINHEAD, 36s);
                break;
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != WAYPOINT_MOTION_TYPE)
            return;

        if (!_instance)
            return;

        // @todo find out a better way to solve this mess
        bool nearDoor = false;
        if (auto leftDoor = _instance->GetGameObject(DATA_GO_STAGEDOORLEFT))
            if (me->GetDistance(*leftDoor) < 5.0f)
                nearDoor = true;

        if (id == 1 && !nearDoor)
        {
            me->SetFacingTo(4.578353f);
            Talk(SAY_BARNES_WELCOME);

            switch (_eventType)
            {
                case OPERA_EVENT_RED_RIDING_HOOD:
                    _events.ScheduleEvent(EVENT_RED_RIDING_HOOD_1, 7s);
                    _events.ScheduleEvent(EVENT_RED_RIDING_HOOD_2, 18s);
                    _events.ScheduleEvent(EVENT_RED_RIDING_HOOD_3, 31s);
                    break;
                case OPERA_EVENT_WIZARD_OF_OZ:
                    _events.ScheduleEvent(EVENT_WIZARD_OF_OZ_1, 6s);
                    _events.ScheduleEvent(EVENT_WIZARD_OF_OZ_2, 24s);
                    _events.ScheduleEvent(EVENT_WIZARD_OF_OZ_3, 34s);
                    break;
                case OPERA_EVENT_ROMULO_AND_JULIANNE:
                    _events.ScheduleEvent(EVENT_ROMULO_AND_JULIANNE_1, 6s);
                    _events.ScheduleEvent(EVENT_ROMULO_AND_JULIANNE_2, 14s);
                    _events.ScheduleEvent(EVENT_ROMULO_AND_JULIANNE_3, 29s);
                    break;
                default:
                    break;
            }

            if (Creature* spotlight = me->SummonCreature(NPC_SPOTLIGHT, *me, TEMPSUMMON_TIMED_DESPAWN, 45000))
            {
                spotlight->SetSelectable(false);
                spotlight->CastSpell(spotlight, SPELL_SPOTLIGHT, false);
            }

            _events.ScheduleEvent(EVENT_RETURN, 45s);
        }
        else if (id == 1 && nearDoor)
        {
            me->SetFacingTo(1.41372f);
            me->RemoveAurasDueToSpell(SPELL_TUXEDO_TRANSFORM);
            HandleDoor(DATA_GO_CURTAINS, true);
            HandleDoor(DATA_GO_STAGEDOORLEFT, false);
            _instance->SetBossState(BOSS_OPERA, IN_PROGRESS);
            me->SummonCreatureGroup(_eventType);
        }
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void HandleAttackStart(Creature* add)
    {
        add->SetAggressive();
        add->SetImmuneToPC(false);
        DoZoneInCombat(add);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_BARNES_BEGIN:
                    Talk(SAY_BARNES_BEGIN);
                    HandleDoor(DATA_GO_STAGEDOORLEFT, true);
                    _events.ScheduleEvent(EVENT_BARNES_OPEN_DOOR, 2s);
                    break;
                case EVENT_BARNES_OPEN_DOOR:
                    me->GetMotionMaster()->MovePath(PATH_STAGE, false);
                    DoCastSelf(SPELL_TUXEDO_TRANSFORM, true);
                    break;
                case EVENT_RED_RIDING_HOOD_1:
                    Talk(SAY_BARNES_HOOD_1);
                    break;
                case EVENT_RED_RIDING_HOOD_2:
                    Talk(SAY_BARNES_HOOD_2);
                    break;
                case EVENT_RED_RIDING_HOOD_3:
                    Talk(SAY_BARNES_HOOD_3);
                    break;
                case EVENT_WIZARD_OF_OZ_1:
                    Talk(SAY_BARNES_OZ_1);
                    break;
                case EVENT_WIZARD_OF_OZ_2:
                    Talk(SAY_BARNES_OZ_2);
                    break;
                case EVENT_WIZARD_OF_OZ_3:
                    Talk(SAY_BARNES_OZ_3);
                    break;
                case EVENT_ROMULO_AND_JULIANNE_1:
                    Talk(SAY_BARNES_ROMEO_JULIANNE_1);
                    break;
                case EVENT_ROMULO_AND_JULIANNE_2:
                    Talk(SAY_BARNES_ROMEO_JULIANNE_2);
                    break;
                case EVENT_ROMULO_AND_JULIANNE_3:
                    Talk(SAY_BARNES_ROMEO_JULIANNE_3);
                    break;
                case EVENT_RETURN:
                    me->GetMotionMaster()->MovePath(PATH_RETURN, false);
                    break;
                case EVENT_TALK_DOROTHEE:
                    if (Creature* dorothee = _instance->GetCreature(DATA_DOROTHEE))
                        if (dorothee->IsAIEnabled)
                            dorothee->AI()->Talk(SAY_DOROTHEE_AGGRO);
                    break;
                case EVENT_AGGRO_DOROTHEE:
                    if (Creature* dorothee = _instance->GetCreature(DATA_DOROTHEE))
                        HandleAttackStart(dorothee);
                    break;
                case EVENT_AGGRO_STRAWMAN:
                    if (Creature* strawman = _instance->GetCreature(DATA_STRAWMAN))
                        HandleAttackStart(strawman);
                    break;
                case EVENT_AGGRO_TINHEAD:
                    if (Creature* tinhead = _instance->GetCreature(DATA_TINHEAD))
                        HandleAttackStart(tinhead);
                    break;
                case EVENT_AGGRO_ROAR:
                    if (Creature* roar = _instance->GetCreature(DATA_ROAR))
                        HandleAttackStart(roar);
                    break;
                default:
                    break;
            }
        }
    }

    private:
        uint8 _eventType;
        InstanceScript* _instance;
        EventMap _events;
        SummonList _summons;
};

struct npc_grandmotherAI : public ScriptedAI
{
    npc_grandmotherAI(Creature* creature) : ScriptedAI(creature) { }

    void sGossipSelect(Player* player, uint32 menuId, uint32 /*gossipListId*/) override
    {
        if (menuId == MENU_ID_SUMMON_WOLF)
        {
            if (Creature* bigBadWolf = me->SummonCreature(NPC_BIG_BAD_WOLF, *me, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 7200000))
            {
                if (bigBadWolf->IsAIEnabled)
                    bigBadWolf->AI()->AttackStart(player);

                if (auto instance = me->GetInstanceScript())
                    if (auto barnes = instance->GetCreature(DATA_BARNES))
                        if (barnes->IsAIEnabled)
                            barnes->AI()->JustSummoned(bigBadWolf);
            }

            me->DespawnOrUnsummon();
        }
    }
};

struct boss_big_bad_wolfAI : public ScriptedAI
{
    boss_big_bad_wolfAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        _events.Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        Talk(SAY_WOLF_AGGRO);
        _events.ScheduleEvent(EVENT_RED_RIDING_HOOD_SPELL, 4s);
        _events.ScheduleEvent(EVENT_TERRYFING_HOWL, 25s, 35s);
        _events.ScheduleEvent(EVENT_WIDE_SWIPE, 5s);
    }

    void EnterEvadeMode() override
    {
        _instance->SetBossState(BOSS_OPERA, FAIL);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (_events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_WOLF_SLAY);
            _events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void JustDied(Unit* /*atacker*/) override
    {
        _instance->SetBossState(BOSS_OPERA, DONE);
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
                case EVENT_RED_RIDING_HOOD_SPELL:
                    Talk(SAY_WOLF_HOOD);
                    DoCastSelf(SPELL_PICK_RED_RIDING_HOOD);
                    _events.Repeat(40s);
                    break;
                case EVENT_TERRYFING_HOWL:
                    DoCastSelf(SPELL_TERRIFYING_HOWL);
                    _events.Repeat(25s, 30s);
                    break;
                case EVENT_WIDE_SWIPE:
                    DoCastAOE(SPELL_WIDE_SWIPE);
                    _events.Repeat(25s, 30s);
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
        InstanceScript* _instance;
        EventMap _events;
};

class spell_wolf_pick_red_riding_hood_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_wolf_pick_red_riding_hood_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        if (targets.empty())
            return;

        Trinity::Containers::RandomResize(targets, 1);
    }

    void HandleScriptEffect(SpellEffIndex /*effIndex*/)
    {
        if (Unit* target = GetHitUnit())
            GetCaster()->CastSpell(target, SPELL_RED_RIDING_HOOD, true);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_wolf_pick_red_riding_hood_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnEffectHitTarget += SpellEffectFn(spell_wolf_pick_red_riding_hood_SpellScript::HandleScriptEffect, EFFECT_0, SPELL_EFFECT_SCRIPT_EFFECT);
    }
};

class spell_wolf_red_riding_hood_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_wolf_red_riding_hood_AuraScript);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->getThreatManager().tauntApply(GetTarget());
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (Unit* caster = GetCaster())
            caster->getThreatManager().tauntFadeOut(GetTarget());
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_wolf_red_riding_hood_AuraScript::OnApply, EFFECT_0, SPELL_AURA_MOD_RESISTANCE_PCT, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_wolf_red_riding_hood_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_MOD_RESISTANCE_PCT, AURA_EFFECT_HANDLE_REAL);
    }
};

struct raj_eventAI : public ScriptedAI
{
    raj_eventAI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _phase = 0;
    }

    void SetFeignDeath(bool apply)
    {
        if (apply)
        {
            _events.CancelEventGroup(GROUP_COMBAT);
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->InterruptNonMeleeSpells(false);
            me->AttackStop();
            me->RemoveAllAuras();
            me->SetHealth(0);
            me->StopMovingOnCurrentPos();
            me->SetSelectable(false);
            me->SetPassive();
        }
        else
        {
            me->SetControlled(false, UNIT_STATE_ROOT);
            me->SetAggressive();
            me->SetFullHealth();
            me->SetSelectable(true);
            DoZoneInCombat();
        }

        me->SetStandState(apply ? UNIT_STAND_STATE_DEAD : UNIT_STAND_STATE_STAND);
    }

    virtual void ScheduleCombatEvents() = 0;

    void EnterCombat(Unit* /*attacker*/) override
    {
        ScheduleCombatEvents();
    }

    void EnterEvadeMode() override
    {
        me->DespawnOrUnsummon();
        _instance->SetBossState(BOSS_OPERA, FAIL);
    }

    Creature* GetPartner() const
    {
        return _instance->GetCreature(me->GetEntry() == NPC_ROMULO ? DATA_JULIANNE : DATA_ROMULO);
    }

    void FinishEncounter() const
    {
        if (Creature* partner = GetPartner())
            for (auto creature : { me, partner })
            {
                creature->SetHealth(1);
                creature->Kill(creature, creature, false);
                creature->SetSelectable(true);
            }

        if (Creature* julianne = _instance->GetCreature(DATA_JULIANNE))
            if (julianne->IsAIEnabled)
                julianne->AI()->Talk(SAY_JULIANNE_DEATH02);

        _instance->SetBossState(BOSS_OPERA, DONE);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && _phase != 0)
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            DoEvent(eventId);
            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    virtual void DoEvent(uint32 eventId) = 0;

    protected:
        InstanceScript* _instance;
        EventMap _events;
        uint8 _phase;
};

struct boss_julianneAI : public raj_eventAI
{
    boss_julianneAI(Creature* creature) : raj_eventAI(creature)
    {
        me->SetPassive();
        me->SetImmuneToAll(true);
        _events.ScheduleEvent(EVENT_AGGRO, 5s);
        _instance = me->GetInstanceScript();
    }

    void ScheduleCombatEvents() override
    {
        _events.ScheduleEvent(EVENT_BLINDING_PASSION, 1s, GROUP_COMBAT);
        _events.ScheduleEvent(EVENT_DEVOTION, 15s, GROUP_COMBAT);
        _events.ScheduleEvent(EVENT_ETERNAL_AFFECTION, 10s, GROUP_COMBAT);
        _events.ScheduleEvent(EVENT_POWERFUL_ATTRACTION, 5s, GROUP_COMBAT);
    }

    void EnterCombat(Unit* attacker) override
    {
        _phase = 1;
        Talk(SAY_JULIANNE_AGGRO);
        raj_eventAI::EnterCombat(attacker);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (_events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_JULIANNE_SLAY);
            _events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId != ACTION_RESURRECT)
            return;

        SetFeignDeath(false);
        Talk(SAY_JULIANNE_RESURRECT);
        if (Creature* romulo = GetPartner())
            DoCast(romulo, SPELL_UNDYING_LOVE);
        ScheduleCombatEvents();
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*schoolmask*/) override
    {
        if (damage > me->GetHealth())
        {
            damage = me->GetHealth() - 1;
            if (_phase == 1)
            {
                _events.CancelEventGroup(GROUP_COMBAT);
                me->InterruptNonMeleeSpells(false);
                _phase = 2;
                Talk(SAY_JULIANNE_DEATH01);
                DoCastSelf(SPELL_DRINK_POISON);
                _events.ScheduleEvent(EVENT_DRINK_POISON, 2s);
            }
            else if (_phase == 2 && GetPartner())
            {
                _phase = 3;
                SetFeignDeath(true);
                if (GetPartner()->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                    FinishEncounter();
            }
        }
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_AGGRO:
                me->SetAggressive();
                me->SetImmuneToAll(false);
                DoZoneInCombat();
                break;
            case EVENT_BLINDING_PASSION:
                DoCastVictim(SPELL_BLINDING_PASSION);
                _events.Repeat(8s, 14s);
                break;
            case EVENT_DEVOTION:
                DoCastSelf(SPELL_DEVOTION);
                _events.Repeat(15s, 45s);
                break;
            case EVENT_ETERNAL_AFFECTION:
                if (Creature* romulo = GetPartner())
                {
                    if (romulo->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                        DoCastSelf(SPELL_ETERNAL_AFFECTION);
                    else
                        DoCast(roll_chance_f(100.0f - me->GetHealthPct()) ? me : romulo, SPELL_ETERNAL_AFFECTION);
                }
                else
                    DoCastSelf(SPELL_ETERNAL_AFFECTION);
                _events.Repeat(45s, 60s);
                break;
            case EVENT_POWERFUL_ATTRACTION:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    DoCast(target, SPELL_POWERFUL_ATTRACTION);
                _events.Repeat(5s, 30s);
                break;
            case EVENT_DRINK_POISON:
                if (_phase == 2)
                {
                    SetFeignDeath(true);
                    _events.ScheduleEvent(EVENT_SUMMON_ROMULO, 3s);
                }
                break;
            case EVENT_SUMMON_ROMULO:
                if (Creature* romulo = me->SummonCreature(NPC_ROMULO, { -10900.0f, -1758.0f, me->GetPositionZ(), 0.0f }, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 7200000))
                    if (romulo->IsAIEnabled)
                        romulo->AI()->DoZoneInCombat();
                break;
            default:
                break;
        }
    }
};

struct boss_romuloAI : public raj_eventAI
{
    boss_romuloAI(Creature* creature) : raj_eventAI(creature) { }

    void ScheduleCombatEvents() override
    {
        _events.ScheduleEvent(EVENT_BACKWARD_LUNGE, 15s, GROUP_COMBAT);
        _events.ScheduleEvent(EVENT_DARING, 20s, GROUP_COMBAT);
        _events.ScheduleEvent(EVENT_DEADLY_SWATCHE, 25s, GROUP_COMBAT);
        _events.ScheduleEvent(EVENT_POISONED_THRUST, 10s, GROUP_COMBAT);
    }

    void EnterCombat(Unit* attacker) override
    {
        _phase = 1;
        Talk(SAY_ROMULO_AGGRO);
        raj_eventAI::EnterCombat(attacker);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (_events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_ROMULO_SLAY);
            _events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*schoolmask*/) override
    {
        if (damage > me->GetHealth())
        {
            damage = me->GetHealth() - 1;
            if (_phase == 1)
            {
                _phase = 2;
                Talk(SAY_ROMULO_DEATH);
                SetFeignDeath(true);
                _events.ScheduleEvent(EVENT_RES_JULIANNE, 4s);
            }
            else if (_phase == 2)
            {
                _phase = 3;
                SetFeignDeath(true);
                if (Creature* julianne = GetPartner())
                    if (julianne->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
                        FinishEncounter();
            }
        }
    }

    void SpellHit(Unit* /*who*/, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_UNDYING_LOVE)
        {
            ScheduleCombatEvents();
            SetFeignDeath(false);
        }
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_BACKWARD_LUNGE:
                DoCastAOE(SPELL_BACKWARD_LUNGE);
                _events.Repeat(15s, 30s);
                break;
            case EVENT_DARING:
                DoCastSelf(SPELL_DARING);
                _events.Repeat(20s, 40s);
                break;
            case EVENT_DEADLY_SWATCHE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    DoCast(target, SPELL_DEADLY_SWATHE);
                _events.Repeat(15s, 25s);
                break;
            case EVENT_POISONED_THRUST:
                DoCastVictim(SPELL_POISON_THRUST);
                _events.Repeat(10s, 20s);
                break;
            case EVENT_RES_JULIANNE:
                if (Creature* julianne = GetPartner())
                    if (julianne->IsAIEnabled)
                        julianne->AI()->DoAction(ACTION_RESURRECT);
                break;
            default:
                break;
        }
    }
};

struct npc_oz_eventAI : public ScriptedAI
{
    npc_oz_eventAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetImmuneToPC(true);
        me->SetPassive();
        _instance = me->GetInstanceScript();
    }

    void MoveInLineOfSight(Unit* /*who*/) override { }

    void JustDied(Unit* /*killer*/) override
    {
        if (Creature* crone = _instance->GetCreature(DATA_CRONE))
            if (crone->IsAIEnabled)
                crone->AI()->SetData(DATA_ADD_KILLED, 1);
    }

    void EnterEvadeMode() override
    {
        me->DespawnOrUnsummon();
        _instance->SetBossState(BOSS_OPERA, FAIL);
    }

    virtual void DoEvent(uint32 eventId) = 0;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            DoEvent(eventId);
            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    protected:
        EventMap _events;
        InstanceScript* _instance;
};

struct boss_croneAI : public npc_oz_eventAI
{
    boss_croneAI(Creature* creature) : npc_oz_eventAI(creature), _summons(me) { }

    void Reset() override
    {
        _addKillCount = 0;
        me->SetPassive();
        me->SetVisible(false);
        _events.Reset();
        if (auto barnes = _instance->GetCreature(DATA_BARNES))
            if (barnes->IsAIEnabled)
                barnes->AI()->DoAction(ACTION_SCHEDULE_OZ);
    }

    void SetData(uint32 type, uint32 /*data*/) override
    {
        if (type == DATA_ADD_KILLED)
        {
            if (++_addKillCount >= 4)
            {
                me->SetAggressive();
                me->SetVisible(true);
                me->SetImmuneToPC(false);
                DoZoneInCombat();
                Talk(SAY_CRONE_AGGRO);
                _events.ScheduleEvent(EVENT_CYCLONE, 30s);
                _events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 10s);
            }
        }
    }

    void JustSummoned(Creature* summon) override
    {
        _summons.Summon(summon);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (_events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_CRONE_SLAY);
            _events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        Talk(SAY_CRONE_DEATH);
        _instance->SetBossState(BOSS_OPERA, DONE);
        _summons.DespawnAll();
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CYCLONE:
            {
                Position pos;
                me->GetRandomNearPosition(pos, 15.0f);
                if (Creature* cyclone = me->SummonCreature(NPC_CYCLONE, pos, TEMPSUMMON_TIMED_DESPAWN, 15000))
                {
                    cyclone->CastSpell(cyclone, SPELL_CYCLONE_AURA);
                    cyclone->CastSpell(cyclone, SPELL_CYCLONE_VISUAL);
                }
                _events.Repeat(30s);
                break;
            }
            case EVENT_CHAIN_LIGHTNING:
                DoCastVictim(SPELL_CHAIN_LIGHTNING);
                _events.Repeat(15s);
                break;
            default:
                break;
        }
    }

    private:
        SummonList _summons;
        uint8 _addKillCount;
};

struct npc_dorotheeAI : public npc_oz_eventAI
{
    npc_dorotheeAI(Creature* creature) : npc_oz_eventAI(creature) { }

    void Reset() override
    {
        _titoDied = false;
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_FRIGHTENED_SCREAM, 15s);
        _events.ScheduleEvent(EVENT_SUMMON_TITO, 40s, 45s);
        _events.ScheduleEvent(EVENT_WATER_BOLT, 500ms);
    }

    void JustDied(Unit* killer) override
    {
        npc_oz_eventAI::JustDied(killer);
        Talk(SAY_DOROTHEE_DEATH);
    }

    void SetData(uint32 type, uint32 /*data*/) override
    {
        if (type == DATA_TITO_DIED)
            _titoDied = true;
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_FRIGHTENED_SCREAM:
                DoCastSelf(SPELL_FRIGHTENED_SCREAM);
                _events.Repeat(30s);
                break;
            case EVENT_SUMMON_TITO:
                Talk(SAY_DOROTHEE_SUMMON);
                DoCastSelf(SPELL_SUMMON_TITO);
                break;
            case EVENT_WATER_BOLT:
                DoCastVictim(SPELL_WATER_BOLT);
                _events.Repeat(_titoDied ? 1.5s : 5s);
                break;
            default:
                break;
        }
    }

    private:
        bool _titoDied;
};

struct npc_titoAI : public npc_oz_eventAI
{
    npc_titoAI(Creature* creature) : npc_oz_eventAI(creature)
    {
        me->SetImmuneToPC(false);
        me->SetAggressive();
    }

    void Reset() override
    {
        DoZoneInCombat();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.Reset();
        _events.ScheduleEvent(EVENT_ANNOYING_YIPPING, 10s);
    }

    void JustDied(Unit* /*attacker*/) override
    {
        if (Creature* dorothee = _instance->GetCreature(DATA_DOROTHEE))
            if (dorothee->IsAIEnabled)
            {
                dorothee->AI()->Talk(SAY_DOROTHEE_TITO_DEATH);
                dorothee->AI()->SetData(DATA_TITO_DIED, 1);
            }
    }

    void DoEvent(uint32 eventId) override
    {
        if (eventId == EVENT_ANNOYING_YIPPING)
        {
            DoCastVictim(SPELL_ANNOYING_YIPPING);
            _events.Repeat(10s);
        }
    }
};

struct npc_roarAI : public npc_oz_eventAI
{
    npc_roarAI(Creature* creature) : npc_oz_eventAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        Talk(SAY_ROAR_AGGRO);
        _events.ScheduleEvent(EVENT_MANGLE, 5s);
        _events.ScheduleEvent(EVENT_SHRED, 10s);
        _events.ScheduleEvent(EVENT_FRIGHTENED_ROAR, 15s);
    }

    void JustDied(Unit* killer) override
    {
        npc_oz_eventAI::JustDied(killer);
        Talk(SAY_ROAR_DEATH);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (_events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_ROAR_SLAY);
            _events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_MANGLE:
                DoCastVictim(SPELL_MANGLE);
                _events.Repeat(5s, 8s);
                break;
            case EVENT_SHRED:
                DoCastVictim(SPELL_SHRED);
                _events.Repeat(10s, 15s);
                break;
            case EVENT_FRIGHTENED_ROAR:
                DoCastSelf(SPELL_FRIGHTENED_ROAR);
                _events.Repeat(20s, 30s);
                break;
            default:
                break;
        }
    }
};

struct npc_strawmanAI : public npc_oz_eventAI
{
    npc_strawmanAI(Creature* creature) : npc_oz_eventAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        Talk(SAY_STRAWMAN_AGGRO);
        _events.ScheduleEvent(EVENT_BRAIN_BASH, 5s);
        _events.ScheduleEvent(EVENT_BRAIN_WIPE, 7s);
    }

    void JustDied(Unit* killer) override
    {
        npc_oz_eventAI::JustDied(killer);
        Talk(SAY_STRAWMAN_DEATH);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (_events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_STRAWMAN_SLAY);
            _events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType damageType, SpellSchoolMask schoolMask) override
    {
        if (damage && (damageType == DIRECT_DAMAGE || damageType == SPELL_DIRECT_DAMAGE) && schoolMask == SPELL_SCHOOL_MASK_FIRE)
            DoCastSelf(SPELL_BURNING_STRAW, true);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_BRAIN_BASH:
                DoCastVictim(SPELL_BRAIN_BASH);
                _events.Repeat(15s);
                break;
            case EVENT_BRAIN_WIPE:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [](Unit* tar) -> bool { return tar->getPowerType() == POWER_MANA; }))
                    DoCast(target, SPELL_BRAIN_WIPE);
                _events.Repeat(20s);
                break;
            default:
                break;
        }
    }
};

struct npc_tinheadAI : public npc_oz_eventAI
{
    npc_tinheadAI(Creature* creature) : npc_oz_eventAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        Talk(SAY_TINHEAD_AGGRO);
        _events.ScheduleEvent(EVENT_CLEAVE, 5s);
        _events.ScheduleEvent(EVENT_RUST, 30s);
    }

    void JustDied(Unit* killer) override
    {
        npc_oz_eventAI::JustDied(killer);
        Talk(SAY_TINHEAD_DEATH);
    }

    void KilledUnit(Unit* /*victim*/) override
    {
        if (_events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_TINHEAD_SLAY);
            _events.ScheduleEvent(EVENT_KILL_TALK, 5s);
        }
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CLEAVE:
                DoCastVictim(SPELL_CLEAVE);
                _events.Repeat(5s);
                break;
            case EVENT_RUST:
                if (Aura* aura = me->GetAura(SPELL_RUST, me->GetGUID()))
                    if (aura->GetStackAmount() == 8)
                    {
                        aura->RefreshDuration();
                        break;
                    }

                Talk(EMOTE_RUST);
                DoCastSelf(SPELL_RUST);
                _events.Repeat(6s);
                break;
            default:
                break;
        }
    }
};

void AddSC_bosses_opera()
{
    new CreatureAILoader<npc_barnesAI>("npc_barnes");

    // Red Riding Hood
    new CreatureAILoader<npc_grandmotherAI>("npc_grandmother");
    new CreatureAILoader<boss_big_bad_wolfAI>("boss_big_bad_wolf");
    new SpellScriptLoaderEx<spell_wolf_pick_red_riding_hood_SpellScript>("spell_wolf_pick_red_riding_hood");
    new AuraScriptLoaderEx<spell_wolf_red_riding_hood_AuraScript>("spell_wolf_red_riding_hood");

    // Romulo and Julianne
    new CreatureAILoader<boss_julianneAI>("boss_julianne");
    new CreatureAILoader<boss_romuloAI>("boss_romulo");

    // Wizard of Oz
    new CreatureAILoader<boss_croneAI>("boss_crone");
    new CreatureAILoader<npc_dorotheeAI>("npc_dorothee");
    new CreatureAILoader<npc_titoAI>("npc_tito");
    new CreatureAILoader<npc_roarAI>("npc_roar");
    new CreatureAILoader<npc_strawmanAI>("npc_strawman");
    new CreatureAILoader<npc_tinheadAI>("npc_tinhead");
}
