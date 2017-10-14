#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "utgarde_keep.h"

enum IngvarDisplayIds
{
    DISPLAYID_DEFAULT       = 21953,
    DISPLAYID_UNDEAD        = 26351,
};

enum IngvarNPCs
{
    NPC_INGVAR_UNDEAD        = 23980,
    NPC_ANNHYLDE             = 24068,
    NPC_THROW                = 23997
};

enum IngvarYells
{
    //Yells Ingvar
    YELL_AGGRO_1                                = 0,
    YELL_KILL_1,
    YELL_DEAD_1,

    YELL_AGGRO_2,
    YELL_KILL_2,
    YELL_DEAD_2,

    EMOTE_ROAR,

    YELL_ANHYLDE_1                              = 0,
    YELL_ANHYLDE_2                              = 1,
};

enum IngvarSpells
{
    SPELL_SUMMON_VALKYR                         = 42912,
    SPELL_RESURRECTION_BEAM                     = 42857,
    SPELL_RESURRECTION_BALL                     = 42862,
    SPELL_RESURRECTION_HEAL                     = 42704,
    SPELL_INGVAR_TRANSFORM                      = 42796,

    SPELL_STAGGERING_ROAR                       = 42708,
    SPELL_CLEAVE                                = 42724,
    SPELL_SMASH                                 = 42669,
    SPELL_ENRAGE                                = 42705,

    SPELL_DREADFUL_ROAR                         = 42729,
    SPELL_WOE_STRIKE                            = 42730,
    SPELL_DARK_SMASH                            = 42723,
    SPELL_SHADOW_AXE                            = 42749
};

enum IngvarEvents
{
    EVENT_START_RESURRECTION                    = 1,
    EVENT_YELL_DEAD_1,
    EVENT_VALKYR_MOVE,
    EVENT_ANNHYLDE_YELL,
    EVENT_VALKYR_BEAM,
    EVENT_RESURRECTION_BALL,
    EVENT_RESURRECTION_HEAL,
    EVENT_MORPH_TO_UNDEAD,
    EVENT_START_PHASE_2,

    EVENT_UNROOT,
    EVENT_SPELL_ROAR,
    EVENT_SPELL_CLEAVE_OR_WOE_STRIKE,
    EVENT_SPELL_SMASH,
    EVENT_SPELL_ENRAGE_OR_SHADOW_AXE,
    EVENT_AXE_RETURN,
    EVENT_AXE_PICKUP,
};

struct boss_ingvar_the_plundererAI : BossAI
{
    explicit boss_ingvar_the_plundererAI(Creature* creature) : BossAI(creature, DATA_INGVAR), _valkyrGUID(0), _throwGUID(0), _said(false) {}

    bool IsInFirstPhase() const
    {
        return me->GetDisplayId() == DISPLAYID_DEFAULT;
    }

    bool HasWeaponEquipped() const
    {
        return me->GetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_ID) != 0;
    }

    void Reset() override
    {
        _Reset();
        _said = false;
        _valkyrGUID = 0;
        _throwGUID = 0;
        me->SetDisplayId(DISPLAYID_DEFAULT);
        me->LoadEquipment(1);
        FeignDeath(false);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetAttackable(true);
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        instance->SetData(DATA_INGVAR, NOT_STARTED);
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (IsInFirstPhase() && !_said && damage >= me->GetHealth())
        {
            _said = true;
            damage = 0;
            me->InterruptNonMeleeSpells(true);
            me->RemoveAllAuras();
            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetAttackable(false);
            me->SetControlled(false, UNIT_STATE_ROOT);
            me->DisableRotate(false);
            me->StopMoving();
            FeignDeath(true);
            events.Reset();
            events.RescheduleEvent(EVENT_START_RESURRECTION, 1000);
            events.RescheduleEvent(EVENT_YELL_DEAD_1, 0);
        }
    }

    void EnterCombat(Unit* /*who*/) override
    {
        events.Reset();
        // schedule Phase 1 abilities
        events.RescheduleEvent(EVENT_SPELL_ROAR, 15000);
        events.RescheduleEvent(EVENT_SPELL_CLEAVE_OR_WOE_STRIKE, 2000);
        events.RescheduleEvent(EVENT_SPELL_SMASH, 5000);
        events.RescheduleEvent(EVENT_SPELL_ENRAGE_OR_SHADOW_AXE, 10000);

        Talk(YELL_AGGRO_1);
        me->LowerPlayerDamageReq(me->GetMaxHealth());

        instance->SetData(DATA_INGVAR, IN_PROGRESS);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (summon->GetEntry() == NPC_ANNHYLDE)
        {
            _valkyrGUID = summon->GetGUID();
            summon->SetCanFly(true);
            summon->SetDisableGravity(true);
            summon->SetHover(true);
            summon->m_positionZ += 35.0f;
            summon->SetFacingTo(summon->GetOrientation());
        }
        else if (summon->GetEntry() == NPC_THROW)
        {
            _throwGUID = summon->GetGUID();
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70.0f, true))
                summon->GetMotionMaster()->MovePoint(0, *target);
        }
    }

    void KilledUnit(Unit* who) override
    {
        if (who->IsPlayer())
            Talk(IsInFirstPhase() ? YELL_KILL_1 : YELL_KILL_2);
    }

    void FeignDeath(bool apply)
    {
        if (apply)
        {
            me->SetStandState(UNIT_STAND_STATE_DEAD);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29);
            me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
        }
        else
        {
            me->SetStandState(UNIT_STAND_STATE_STAND);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29);
            me->RemoveFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
            me->RemoveFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        events.Reset();
        summons.DespawnAll();
        Talk(YELL_DEAD_2);
        instance->DoUpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE, NPC_INGVAR_UNDEAD, 1); // undead entry needed for achievements
        instance->SetData(DATA_INGVAR, DONE);
    }

    void EnterEvadeMode() override
    {
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        _DespawnAtEvade();
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_YELL_DEAD_1:
                Talk(YELL_DEAD_1);
                break;
            case EVENT_START_RESURRECTION:
                me->CastSpell(me, SPELL_SUMMON_VALKYR, true);
                if (Creature* valkyr = ObjectAccessor::GetCreature(*me, _valkyrGUID))
                {
                    valkyr->SetAttackable(false);
                    valkyr->SetVisible(false);
                }
                events.RescheduleEvent(EVENT_VALKYR_BEAM, 7000);
                events.RescheduleEvent(EVENT_VALKYR_MOVE, 1);
                events.RescheduleEvent(EVENT_ANNHYLDE_YELL, 3000);
                break;
            case EVENT_VALKYR_MOVE:
                if (Creature* valkyr = ObjectAccessor::GetCreature(*me, _valkyrGUID))
                    valkyr->GetMotionMaster()->MovePoint(1, valkyr->GetPositionX(), valkyr->GetPositionY(), valkyr->GetPositionZ() - 15.0f);
                break;
            case EVENT_ANNHYLDE_YELL:
                if (Creature* valkyr = ObjectAccessor::GetCreature(*me, _valkyrGUID))
                {
                    valkyr->SetVisible(true);
                    if (valkyr->IsAIEnabled)
                        valkyr->AI()->Talk(YELL_ANHYLDE_2);
                }
                break;
            case EVENT_VALKYR_BEAM:
                me->RemoveAura(SPELL_SUMMON_VALKYR);
                if (Creature* valkyr = ObjectAccessor::GetCreature(*me, _valkyrGUID))
                    valkyr->CastSpell(me, SPELL_RESURRECTION_BEAM, false);
                events.RescheduleEvent(EVENT_RESURRECTION_BALL, 4000);
                break;
            case EVENT_RESURRECTION_BALL:
                DoCastSelf(SPELL_RESURRECTION_BALL, true);
                events.RescheduleEvent(EVENT_RESURRECTION_HEAL, 4000);
                break;
            case EVENT_RESURRECTION_HEAL:
                me->RemoveAura(SPELL_RESURRECTION_BALL);
                DoCastSelf(SPELL_RESURRECTION_HEAL, true);
                FeignDeath(false);
                events.RescheduleEvent(EVENT_MORPH_TO_UNDEAD, 3000);
                break;
            case EVENT_MORPH_TO_UNDEAD:
                DoCastSelf(SPELL_INGVAR_TRANSFORM, true);
                events.RescheduleEvent(EVENT_START_PHASE_2, 1000);
                break;
            case EVENT_START_PHASE_2:
                if (Creature* valkyr = ObjectAccessor::GetCreature(*me, _valkyrGUID))
                {
                    valkyr->DespawnOrUnsummon();
                    summons.DespawnAll();
                }
                me->SetAttackable(true);
                me->SetReactState(REACT_AGGRESSIVE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                AttackStart(me->GetVictim());
                Talk(YELL_AGGRO_2);

                // schedule Phase 2 abilities
                events.RescheduleEvent(EVENT_SPELL_ROAR, 15000);
                events.RescheduleEvent(EVENT_SPELL_CLEAVE_OR_WOE_STRIKE, 2000);
                events.RescheduleEvent(EVENT_SPELL_SMASH, 5000);
                events.RescheduleEvent(EVENT_SPELL_ENRAGE_OR_SHADOW_AXE, 10000);
                break;

                // ABILITIES HERE:
            case EVENT_UNROOT:
                me->SetControlled(false, UNIT_STATE_ROOT);
                me->DisableRotate(false);
                break;
            case EVENT_SPELL_ROAR:
                Talk(EMOTE_ROAR);

                me->_AddCreatureSpellCooldown(SPELL_STAGGERING_ROAR, 0);
                me->_AddCreatureSpellCooldown(SPELL_DREADFUL_ROAR, 0);

                DoCastAOE(IsInFirstPhase() ? SPELL_STAGGERING_ROAR : SPELL_DREADFUL_ROAR);
                events.Repeat(urand(15000, 20000));
                break;
            case EVENT_SPELL_CLEAVE_OR_WOE_STRIKE:
                if (!HasWeaponEquipped())
                {
                    events.Repeat(3000);
                    break;
                }
                DoCastVictim(IsInFirstPhase() ? SPELL_CLEAVE : SPELL_WOE_STRIKE);
                events.Repeat(urand(3000, 7000));
                break;
            case EVENT_SPELL_SMASH:
                if (!HasWeaponEquipped())
                {
                    events.Repeat(3000);
                    break;
                }
                me->SetControlled(true, UNIT_STATE_ROOT);
                me->DisableRotate(true);
                me->SendMovementFlagUpdate();
                if (uint32 spellId = IsInFirstPhase() ? SPELL_SMASH : SPELL_DARK_SMASH)
                {
                    DoCastAOE(spellId);
                    events.Repeat(urand(9000, 11000));
                    if (auto sInfo = sSpellMgr->GetSpellInfo(spellId))
                        events.RescheduleEvent(EVENT_UNROOT, sInfo->CastTimeEntry->CastTime + 500);
                }
                break;
            case EVENT_SPELL_ENRAGE_OR_SHADOW_AXE:
                if (IsInFirstPhase())
                {
                    DoCastSelf(SPELL_ENRAGE);
                    events.Repeat(10000);
                }
                else
                {
                    DoCastAOE(SPELL_SHADOW_AXE, true);
                    SetEquipmentSlots(false, EQUIP_UNEQUIP, EQUIP_NO_CHANGE, EQUIP_NO_CHANGE);
                    events.Repeat(35000);
                    events.RescheduleEvent(EVENT_AXE_RETURN, 10000);
                }
                break;
            case EVENT_AXE_RETURN:
                if (Creature* axe = ObjectAccessor::GetCreature(*me, _throwGUID))
                    axe->GetMotionMaster()->MoveCharge(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 0.5f);
                events.RescheduleEvent(EVENT_AXE_PICKUP, 1500);
                break;
            case EVENT_AXE_PICKUP:
                if (Creature* c = ObjectAccessor::GetCreature(*me, _throwGUID))
                {
                    c->DestroyForNearbyPlayers();
                    c->DespawnOrUnsummon();
                    summons.DespawnAll();
                }
                _throwGUID = 0;
                SetEquipmentSlots(true);
                break;
            default:
                break;
        }
    }

    private:
        uint64 _valkyrGUID;
        uint64 _throwGUID;
        bool _said;
};

void AddSC_boss_ingvar_the_plunderer()
{
    new CreatureAILoader<boss_ingvar_the_plundererAI>("boss_ingvar_the_plunderer");
}
