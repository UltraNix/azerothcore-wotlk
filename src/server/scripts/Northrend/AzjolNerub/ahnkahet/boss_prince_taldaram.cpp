#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ahnkahet.h"
#include "SpellInfo.h"

enum TaldaramSpells
{
    SPELL_BLOODTHIRST               = 55968, // Trigger Spell + add aura
    SPELL_CONJURE_FLAME_SPHERE      = 55931,
    SPELL_FLAME_SPHERE_SUMMON_1     = 55895, // 1x 30106
    SPELL_FLAME_SPHERE_SUMMON_2     = 59511, // 1x 31686
    SPELL_FLAME_SPHERE_SUMMON_3     = 59512, // 1x 31687
    SPELL_FLAME_SPHERE_SPAWN_EFFECT = 55891,
    SPELL_FLAME_SPHERE_VISUAL       = 55928,
    SPELL_FLAME_SPHERE_PERIODIC     = 55926,
    SPELL_FLAME_SPHERE_DEATH_EFFECT = 55947,
    SPELL_EMBRACE_OF_THE_VAMPYR     = 55959,
    SPELL_VANISH                    = 55964,
    SPELL_SHADOWSTEP_SELECTOR       = 55965,
    SPELL_SHADOWSTEP                = 55966,

    SPELL_BEAM_VISUAL               = 60342,
    SPELL_HOVER_FALL                = 60425

};
enum TaldaramMisc
{
    ACTION_FREE                     = 1,
    DATA_EMBRACE_TARGET             = 1,

    ACTION_SPHERE                   = 2,

    DATA_EMBRACE_DMG                = 20000,
    DATA_EMBRACE_DMG_H              = 40000,

    NPC_FLAME_SPHERE_1              = 30106,
    NPC_FLAME_SPHERE_2              = 31686,
    NPC_FLAME_SPHERE_3              = 31687
};

#define DATA_SPHERE_DISTANCE                30.0f
#define DATA_SPHERE_ANGLE_OFFSET            float(M_PI) / 2
#define DATA_GROUND_POSITION_Z              11.30809f

enum TaldaramEvents
{
    EVENT_CONJURE_FLAME_SPHERES     = 1,
    EVENT_BLOODTHIRST,
    EVENT_VANISH,
    EVENT_START_FEEDING,
    EVENT_DONE_FEEDING,

    // Flame Sphere
    EVENT_START_MOVE,
    EVENT_DESPAWN
};

enum TaldaramYells
{
    SAY_1,
    SAY_WARNING,
    SAY_AGGRO,
    SAY_SLAY,
    SAY_DEATH,
    SAY_FEED,
    SAY_VANISH
};

struct boss_taldaramAI : public BossAI
{
    boss_taldaramAI(Creature* creature) : BossAI(creature, BOSS_TALDARAM) { }

    void Reset() override
    {
        _flameSphereTargetGUID = 0;
        _embraceTargetGUID = 0;
        _embraceTakenDamage = 0;
        _Reset();
        if (instance->GetData(DATA_SPHERE_EVENT_1) == DONE && instance->GetData(DATA_SPHERE_EVENT_2) == DONE)
            DoAction(ACTION_FREE);
        else
            DoCastSelf(SPELL_BEAM_VISUAL);
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_FREE)
        {
            me->RemoveAllAuras();
            me->SetUnitMovementFlags(MOVEMENTFLAG_WALKING);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);
            me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), DATA_GROUND_POSITION_Z, me->GetOrientation(), true);
            me->SetHomePosition(me->GetPositionX(), me->GetPositionY(), DATA_GROUND_POSITION_Z, me->GetOrientation());
            instance->HandleGameObject(instance->GetGameObject(DATA_TALDARAM_SHIELD)->GetGUID(), true);
        }
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        Talk(SAY_AGGRO);
        _EnterCombat();
        events.ScheduleEvent(EVENT_BLOODTHIRST, 10s);
        events.ScheduleEvent(EVENT_VANISH, 25s, 35s);
        events.ScheduleEvent(EVENT_CONJURE_FLAME_SPHERES, 5s);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);

        switch (summon->GetEntry())
        {
            case NPC_FLAME_SPHERE_1:
            case NPC_FLAME_SPHERE_2:
            case NPC_FLAME_SPHERE_3:
                if (summon->IsAIEnabled)
                    summon->AI()->SetGUID(_flameSphereTargetGUID);
                break;
            default:
                return;
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damageType*/, SpellSchoolMask /*mask*/) override
    {
        Unit* embraceTarget = GetEmbraceTarget();

        if (embraceTarget && embraceTarget->IsAlive())
        {
            _embraceTakenDamage += damage;
            if (_embraceTakenDamage > DUNGEON_MODE<uint32>(DATA_EMBRACE_DMG, DATA_EMBRACE_DMG_H))
            {
                _embraceTargetGUID = 0;
                _embraceTakenDamage = 0;
                me->CastStop();
            }
        }
    }

    void SpellHitTarget(Unit*, const SpellInfo* spellInfo) override
    {
        if (spellInfo->Id == SPELL_CONJURE_FLAME_SPHERE)
            summons.DoAction(ACTION_SPHERE);
    }

    Unit* GetEmbraceTarget() const
    {
        if (_embraceTargetGUID)
            return ObjectAccessor::GetUnit(*me, _embraceTargetGUID);

        return nullptr;
    }

    void UpdateAI(uint32 diff) override
    {
        if (me->HasAura(SPELL_VANISH))
        {
            if (me->getThreatManager().isThreatListEmpty())
            {
                EnterEvadeMode();
                return;
            }
        }
        else
        {
            if (!UpdateVictim())
                return;
        }

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_BLOODTHIRST:
                    DoCastSelf(SPELL_BLOODTHIRST);
                    events.Repeat(10s);
                    break;
                case EVENT_CONJURE_FLAME_SPHERES:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                    {
                        _flameSphereTargetGUID = target->GetGUID();
                        DoCastSelf(SPELL_FLAME_SPHERE_SUMMON_1, true);
                        if (IsHeroic())
                        {
                            DoCastSelf(SPELL_FLAME_SPHERE_SUMMON_2, true);
                            DoCastSelf(SPELL_FLAME_SPHERE_SUMMON_3, true);
                        }

                        DoCast(target, SPELL_CONJURE_FLAME_SPHERE);
                    }
                    events.Repeat(15s);
                    break;
                case EVENT_VANISH:
                    if (instance->instance->GetPlayersCountExceptGMs() > 1)
                    {
                        if (Unit* embraceTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                            _embraceTargetGUID = embraceTarget->GetGUID();
                        Talk(SAY_VANISH);
                        DoCastSelf(SPELL_VANISH);
                        events.DelayEvents(0.5s);
                        events.ScheduleEvent(EVENT_START_FEEDING, 2s);
                    }
                    events.Repeat(25s, 35s);
                    break;
                case EVENT_START_FEEDING:
                    me->RemoveAurasDueToSpell(SPELL_VANISH);
                    if (Unit* embraceTarget = GetEmbraceTarget())
                    {
                        DoCast(embraceTarget, SPELL_SHADOWSTEP);
                        DoCast(embraceTarget, SPELL_EMBRACE_OF_THE_VAMPYR);
                        Talk(SAY_FEED);
                        events.ScheduleEvent(EVENT_DONE_FEEDING, 20s);
                    }
                    break;
                case EVENT_DONE_FEEDING:
                    _embraceTargetGUID = 0;
                    break;
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
        _DespawnAtEvade();
    }

    private:
        uint64 _flameSphereTargetGUID;
        uint64 _embraceTargetGUID;
        uint32 _embraceTakenDamage;
        uint32 _initialCheckTimer;
};

struct npc_taldaram_flamesphereAI : public ScriptedAI
{
    npc_taldaram_flamesphereAI(Creature* creature) : ScriptedAI(creature) 
    { 
        _flameSphereTargetGUID = 0;
    }

    uint32 uiDespawnTimer;

    void SetGUID(uint64 guid, int32 /*id*/) override
    {
        _flameSphereTargetGUID = guid;
    }

    void DoAction(int32 param) override
    {
        if (param == ACTION_SPHERE)
        {
            float angleOffset = 0.0f;
            float distOffset = DATA_SPHERE_DISTANCE;

            switch (me->GetEntry())
            {
                case NPC_FLAME_SPHERE_1:
                    break;
                case NPC_FLAME_SPHERE_2:
                    angleOffset = DATA_SPHERE_ANGLE_OFFSET;
                    break;
                case NPC_FLAME_SPHERE_3:
                    angleOffset = -DATA_SPHERE_ANGLE_OFFSET;
                    break;
                default:
                    return;
            }

            Unit* sphereTarget = ObjectAccessor::GetUnit(*me, _flameSphereTargetGUID);
            if (!sphereTarget)
                return;

            float angle = me->GetAngle(sphereTarget) + angleOffset;
            float x = me->GetPositionX() + distOffset * std::cos(angle);
            float y = me->GetPositionY() + distOffset * std::sin(angle);

            me->SetSpeed(MOVE_RUN, 0.65f);
            me->GetMotionMaster()->MovePoint(0, x, y, me->GetPositionZ());
            DoCastSelf(SPELL_FLAME_SPHERE_PERIODIC);
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (id == 0)
            me->Kill(me, me);
    }

    void Reset() override
    {
        me->SetReactState(REACT_PASSIVE);
        DoCastSelf(SPELL_FLAME_SPHERE_SPAWN_EFFECT, true);
        DoCastSelf(SPELL_FLAME_SPHERE_VISUAL, true);
        uiDespawnTimer = 13000;
    }

    void EnterCombat(Unit* /*who*/) override {}
    void MoveInLineOfSight(Unit* /*who*/) override {}

    void JustDied(Unit* /*who*/) override
    {
        DoCastSelf(SPELL_FLAME_SPHERE_DEATH_EFFECT, true);
    }

    void UpdateAI(uint32 diff) override
    {
        if (uiDespawnTimer <= diff)
            me->Kill(me, me);
        else
            uiDespawnTimer -= diff;
    }

    private:
        uint64 _flameSphereTargetGUID;
};

// 55895, 59511, 59512 - Flame Sphere Summon
class spell_prince_taldaram_flame_sphere_summon_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_prince_taldaram_flame_sphere_summon_SpellScript);

    void SetDest(SpellDestination& dest)
    {
        dest.RelocateOffset({ 0.0f, 0.0f, 5.5f, 0.0f });
    }

    void Register() override
    {
        OnDestinationTargetSelect += SpellDestinationTargetSelectFn(spell_prince_taldaram_flame_sphere_summon_SpellScript::SetDest, EFFECT_0, TARGET_DEST_CASTER);
    }
};

class go_prince_taldaram_sphere : public GameObjectScript
{
    public:
        go_prince_taldaram_sphere() : GameObjectScript("go_prince_taldaram_sphere") { }

        bool OnGossipHello(Player* /*player*/, GameObject* go)
        {
            InstanceScript* instance = go->GetInstanceScript();
            if (!instance)
                return false;

            Creature* taldaram = instance->GetCreature(BOSS_TALDARAM);
            if (taldaram && taldaram->IsAIEnabled && taldaram->IsAlive())
            {
                go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);
                go->SetGoState(GO_STATE_ACTIVE);
                taldaram->AI()->Talk(SAY_1);
                uint32 eventId = (go->GetEntry() == GO_TALDARAM_SPHERE_1) ? DATA_SPHERE_EVENT_1 : DATA_SPHERE_EVENT_2;

                if (instance->GetData(eventId) == NOT_STARTED)
                    instance->SetData(eventId, DONE);

                if (instance->GetData(DATA_SPHERE_EVENT_1) == DONE && instance->GetData(DATA_SPHERE_EVENT_2) == DONE)
                {
                    taldaram->AI()->DoAction(ACTION_FREE);
                    taldaram->AI()->Talk(SAY_WARNING);
                }
            }

            return true;
        }
};

void AddSC_boss_taldaram()
{
    new CreatureAILoader<boss_taldaramAI>("boss_taldaram");
    new CreatureAILoader<npc_taldaram_flamesphereAI>("npc_taldaram_flamesphere");
    new SpellScriptLoaderEx<spell_prince_taldaram_flame_sphere_summon_SpellScript>("spell_prince_taldaram_flame_sphere_summon");
    new go_prince_taldaram_sphere();
}
