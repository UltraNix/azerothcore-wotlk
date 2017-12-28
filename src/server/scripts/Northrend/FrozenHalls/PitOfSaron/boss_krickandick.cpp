#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "pit_of_saron.h"
#include "Vehicle.h"
#include "SpellScript.h"
#include "PassiveAI.h"
#include "SpellAuraEffects.h"
#include "Player.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Chat.h"

enum KIYells
{
    SAY_AGGRO                       = 24,
    SAY_SLAY_1,
    SAY_SLAY_2,
    SAY_ORDER_STOP,
    SAY_ORDER_BLOW,
    SAY_TARGET_1,
    SAY_TARGET_2,
    SAY_TARGET_3,
    EMOTE_KRICK_MINES,
    EMOTE_ICK_POISON
};

enum KISpells
{
    SPELL_TOXIC_WASTE               = 69024,
    SPELL_MIGHTY_KICK               = 69021,
    SPELL_SHADOW_BOLT               = 69028,

    SPELL_PURSUIT                   = 68987,

    SPELL_POISON_NOVA               = 68989,

    SPELL_EXPLOSIVE_BARRAGE_KRICK   = 69012,
    SPELL_EXPLOSIVE_BARRAGE_ICK     = 69263,
    SPELL_EXPLOSIVE_BARRAGE_SUMMON  = 69015,
    SPELL_EXPLODING_ORB_VISUAL      = 69017,
    SPELL_AUTO_GROW                 = 69020,
    SPELL_HASTY_GROW                = 44851,
    SPELL_EXPLOSIVE_BARRAGE_DAMAGE  = 69019,

    SPELL_STRANGULATE               = 69413,
    SPELL_NECROMANTIC_POWER         = 69753
};

enum KIEvents
{
    EVENT_TOXIC_WASTE               = 1,
    EVENT_MIGHTY_KICK,
    EVENT_SHADOW_BOLT,
    EVENT_SPECIAL,
    EVENT_PURSUIT,
    EVENT_POISON_NOVA,
    EVENT_EXPLOSIVE_BARRAGE,
    EVENT_SET_REACT_AGGRESSIVE,
    EVENT_KILL_TALK,

    EVENT_KRICK_OUTRO_1,
    EVENT_KRICK_OUTRO_2,
    EVENT_KRICK_OUTRO_3,
    EVENT_KRICK_OUTRO_4,
    EVENT_KRICK_OUTRO_5,
    EVENT_KRICK_OUTRO_6,
    EVENT_KRICK_OUTRO_7,
    EVENT_KRICK_OUTRO_8,
    EVENT_KRICK_OUTRO_9,
    EVENT_KRICK_OUTRO_10,
    EVENT_KRICK_OUTRO_11,
    EVENT_KRICK_OUTRO_12
};

struct boss_ickAI : public BossAI
{
    boss_ickAI(Creature* creature) : BossAI(creature, DATA_ICK) { }

    void Reset() override
    {
        _Reset();
        if (Creature* krick = GetKrick())
            if (!krick->GetVehicleBase())
                krick->EnterVehicle(me, 0);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    bool CanAIAttack(const Unit* who) const override
    {
        return instance && instance->GetData(DATA_INSTANCE_PROGRESS) >= INSTANCE_PROGRESS_FINISHED_INTRO;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        if (Creature* krick = GetKrick())
            if (krick->IsAIEnabled)
                krick->AI()->Talk(SAY_AGGRO);

        _EnterCombat();
        events.RescheduleEvent(EVENT_TOXIC_WASTE, 5s);
        events.RescheduleEvent(EVENT_MIGHTY_KICK, 20s);
        events.RescheduleEvent(EVENT_SHADOW_BOLT, 10s);
        events.RescheduleEvent(EVENT_SPECIAL, 30s, 35s);
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        if (!target || !spell)
            return;

        if (spell->Id == SPELL_PURSUIT && target->GetTypeId() == TYPEID_PLAYER)
        {
            WorldPacket data;
            ChatHandler::BuildChatPacket(data, CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, me, nullptr, "%s is chasing you!");
            target->ToPlayer()->GetSession()->SendPacket(&data);
            AttackStart(target);
            me->SetReactState(REACT_PASSIVE);
            events.RescheduleEvent(EVENT_SET_REACT_AGGRESSIVE, 12s);
        }
    }

    Creature* GetKrick() const
    {
        return instance->GetCreature(DATA_KRICK);
    }

    void DamageTaken(Unit* /*doneBy*/, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        if (damage >= me->GetHealth())
            if (Creature* krick = GetKrick())
            {
                krick->InterruptNonMeleeSpells(true);
                krick->RemoveAllAuras();
                Position myPos(*me), exitPos;
                float ang = me->GetOrientation() + 3 * M_PI / 2;
                float dist = 3.0f;
                exitPos.Relocate(myPos.GetPositionX() + dist*cos(ang), myPos.GetPositionY() + dist*sin(ang), 515.0f, M_PI);
                exitPos.m_positionZ = me->GetMap()->GetHeight(exitPos.GetPositionX(), exitPos.GetPositionY(), exitPos.GetPositionZ());

                if (exitPos.GetPositionZ() < 505.0f || exitPos.GetPositionZ() > 512.0f || !me->IsWithinLOS(exitPos.GetPositionX(), exitPos.GetPositionY(), exitPos.GetPositionZ()))
                    exitPos.Relocate(myPos);

                krick->_ExitVehicle(&exitPos);
                if (krick->IsAIEnabled)
                    krick->AI()->DoAction(1);
            }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_TOXIC_WASTE:
                if (Creature* krick = GetKrick())
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                        krick->CastSpell(target, SPELL_TOXIC_WASTE);
                events.Repeat(7s, 10s);
                break;
            case EVENT_MIGHTY_KICK:
                DoCastVictim(SPELL_MIGHTY_KICK);
                events.Repeat(25s);
                break;
            case EVENT_SHADOW_BOLT:
                if (Creature* krick = GetKrick())
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 35.0f, true))
                        krick->CastSpell(target, SPELL_SHADOW_BOLT);
                events.Repeat(15s);
                break;
            case EVENT_SET_REACT_AGGRESSIVE:
                me->SetReactState(REACT_AGGRESSIVE);
                break;
            case EVENT_SPECIAL:
                events.ScheduleEvent(RAND(EVENT_EXPLOSIVE_BARRAGE, EVENT_POISON_NOVA, EVENT_PURSUIT), 1s);
                events.Repeat(23s, 28s);
                break;
            case EVENT_PURSUIT:
                if (Creature* krick = GetKrick())
                    if (krick->IsAIEnabled)
                        krick->AI()->Talk(RAND(SAY_TARGET_1, SAY_TARGET_2, SAY_TARGET_3));
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 70.0f, true))
                    DoCast(target, SPELL_PURSUIT);
                break;
            case EVENT_POISON_NOVA:
                if (Creature* krick = GetKrick())
                {
                    if (krick->IsAIEnabled)
                        krick->AI()->Talk(SAY_ORDER_BLOW);
                    Talk(EMOTE_ICK_POISON);
                }
                DoCastSelf(SPELL_POISON_NOVA);
                break;
            case EVENT_EXPLOSIVE_BARRAGE:
                if (Creature* krick = GetKrick())
                {
                    if (krick->IsAIEnabled)
                    {
                        krick->AI()->Talk(SAY_ORDER_STOP);
                        krick->AI()->Talk(EMOTE_KRICK_MINES);
                    }
                    krick->InterruptNonMeleeSpells(false);
                    me->InterruptNonMeleeSpells(false);
                    krick->CastSpell(krick, SPELL_EXPLOSIVE_BARRAGE_KRICK);
                    DoCastSelf(SPELL_EXPLOSIVE_BARRAGE_ICK);
                }
                events.DelayEvents(20s);
                break;
        default:
            break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        me->RemoveAllAuras();
    }

    void EnterEvadeMode() override
    {
        _DespawnAtEvade();
        if (Creature* krick = GetKrick())
            _DespawnAtEvade(30, krick);
    }

    void KilledUnit(Unit* who) override
    {
        // if during pursuit ick kills his target, set to aggressive again
        if (who && me->GetVictim() && who->GetGUID() == me->GetVictim()->GetGUID())
            if (me->GetReactState() == REACT_PASSIVE)
                me->SetReactState(REACT_AGGRESSIVE);

        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            if (Creature* krick = GetKrick())
                if (krick->IsAIEnabled)
                    krick->AI()->Talk(RAND(SAY_SLAY_1, SAY_SLAY_2));
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void JustSummoned(Creature* /*summon*/) override { }
};

struct boss_krickAI : public NullCreatureAI
{
    boss_krickAI(Creature* creature) : NullCreatureAI(creature)
    {
        _instance = creature->GetInstanceScript();
    }

    void DoAction(int32 actionId) override
    {
        if (actionId != 1)
            return;

        me->setActive(true);
        _events.RescheduleEvent(EVENT_KRICK_OUTRO_1, 0s);
    }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        if (!_instance)
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_KRICK_OUTRO_1:
                    _instance->SetData(DATA_INSTANCE_PROGRESS, INSTANCE_PROGRESS_FINISHED_KRICK_SCENE);

                    if (Creature* leader = _instance->GetCreature(DATA_LEADER_FIRST_GUID))
                    {
                        leader->GetMotionMaster()->Clear();
                        leader->UpdatePosition(SBSLeaderStartPos, true);
                        leader->StopMovingOnCurrentPos();
                        if (leader->IsAIEnabled)
                            leader->AI()->Reset();
                    }
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_2, 3s);
                    break;
                case EVENT_KRICK_OUTRO_2:
                    Talk(SAY_OUTRO_KRICK_1);
                    if (Creature* leader = _instance->GetCreature(DATA_LEADER_FIRST_GUID))
                    {
                        float angle = me->GetAngle(leader);
                        me->SetFacingTo(angle);
                        float x = me->GetPositionX() + cos(angle)*7.0f;
                        float y = me->GetPositionY() + sin(angle)*7.0f;
                        leader->GetMotionMaster()->MovePoint(0, x, y, me->GetPositionZ());
                    }

                    for (auto itr : { DATA_GUARD_1_GUID, DATA_GUARD_2_GUID })
                        if (Creature* guard = _instance->GetCreature(itr))
                            guard->DespawnOrUnsummon();
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_3, 7s);
                    break;
                case EVENT_KRICK_OUTRO_3:
                    if (Creature* creature = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                    {
                        creature->setActive(true);
                        creature->UpdatePosition(SBSTyrannusStartPos, true);
                        creature->SetHomePosition(SBSTyrannusStartPos);
                    }
                    if (Creature* leader = _instance->GetCreature(DATA_LEADER_FIRST_GUID))
                        if (leader->IsAIEnabled)
                            leader->AI()->Talk(leader->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_KRICK_1 : SAY_SYLVANAS_KRICK_1);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_4, 6.5s);
                    break;
                case EVENT_KRICK_OUTRO_4:
                    Talk(SAY_OUTRO_KRICK_2);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_5, 17s);
                    break;
                case EVENT_KRICK_OUTRO_5:
                    if (Creature* creature = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                        creature->GetMotionMaster()->MovePath(PATH_BEGIN_VALUE + 10, false);
                    if (Creature* leader = _instance->GetCreature(DATA_LEADER_FIRST_GUID))
                        if (leader->IsAIEnabled)
                            leader->AI()->Talk(leader->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_KRICK_2 : SAY_SYLVANAS_KRICK_2);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_6, 6.5s);
                    break;
                case EVENT_KRICK_OUTRO_6:
                    Talk(SAY_OUTRO_KRICK_3);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_7, 6.5s);
                    break;
                case EVENT_KRICK_OUTRO_7:
                    if (Creature* creature = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                    {
                        creature->SetFacingToObject(me);
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SAY_TYRANNUS_KRICK_1);
                    }
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_8, 4s);
                    break;
                case EVENT_KRICK_OUTRO_8:
                    DoCastSelf(SPELL_STRANGULATE, true);
                    me->SendMeleeAttackStop(me->GetVictim());
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    me->SendMovementFlagUpdate();
                    me->GetMotionMaster()->MoveTakeoff(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 9.0f, 0.5f * 7.0f);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_9, 2s);
                    break;
                case EVENT_KRICK_OUTRO_9:
                    Talk(SAY_OUTRO_KRICK_4);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_10, 1.5s);
                    break;
                case EVENT_KRICK_OUTRO_10:
                    if (Creature* creature = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                        creature->CastSpell(creature, SPELL_NECROMANTIC_POWER, false);

                    me->SetReactState(REACT_PASSIVE);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNK_29 | UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC);
                    me->SetFlag(UNIT_FIELD_FLAGS_2, UNIT_FLAG2_FEIGN_DEATH);
                    me->SetFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_DEAD);
                    me->AddUnitState(UNIT_STATE_DIED);

                    DoCastSelf(SPELL_KRICK_KILL_CREDIT, true);

                    me->RemoveAllAuras();
                    me->GetMotionMaster()->MoveFall(0, true);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_11, 5s);
                    break;
                case EVENT_KRICK_OUTRO_11:
                    if (Creature* creature = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                        if (creature->IsAIEnabled)
                            creature->AI()->Talk(SAY_TYRANNUS_KRICK_2);
                    _events.RescheduleEvent(EVENT_KRICK_OUTRO_12, 9s);
                    break;
                case EVENT_KRICK_OUTRO_12:
                    if (Creature* creature = _instance->GetCreature(DATA_TYRANNUS_EVENT_GUID))
                        creature->GetMotionMaster()->MovePoint(1, 809.39f, 74.69f, 541.54f);
                    if (Creature* leader = _instance->GetCreature(DATA_LEADER_FIRST_GUID))
                    {
                        if (leader->IsAIEnabled)
                            leader->AI()->Talk(leader->GetEntry() == NPC_JAINA_PART1 ? SAY_JAINA_KRICK_3 : SAY_SYLVANAS_KRICK_3);
                        leader->GetMotionMaster()->MovePath(PATH_BEGIN_VALUE + 11, false);
                    }
                    me->setActive(false);
                    Unit::Kill(me, me);
                    break;
                default:
                    break;
            }
        }
    }

    private:
        InstanceScript* _instance;
        EventMap _events;
};

class spell_krick_explosive_barrage_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_krick_explosive_barrage_AuraScript)

    void HandlePeriodicTick(AuraEffect const* /*aurEff*/)
    {
        // @todo remove this playerlist garbage
        PreventDefaultAction();
        if (Unit* caster = GetCaster())
            if (caster->GetTypeId() == TYPEID_UNIT)
            {
                auto const &players = caster->GetMap()->GetPlayers();
                for (auto itr = players.begin(); itr != players.end(); ++itr)
                    if (Player* player = itr->GetSource())
                        if (player->IsWithinDist(caster, 100.0f) && !player->IsGameMaster())
                            caster->CastSpell(player, SPELL_EXPLOSIVE_BARRAGE_SUMMON, true);
            }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_krick_explosive_barrage_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_exploding_orb_auto_grow_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_exploding_orb_auto_grow_AuraScript)

    void HandlePeriodicTick(AuraEffect const* aurEff)
    {
        if (aurEff->GetTickNumber() >= 16)
            if (Unit* target = GetTarget())
            {
                PreventDefaultAction();
                target->CastSpell(target, SPELL_EXPLOSIVE_BARRAGE_DAMAGE, false);
                target->RemoveAurasDueToSpell(SPELL_HASTY_GROW);
                target->RemoveAurasDueToSpell(SPELL_AUTO_GROW);
                target->RemoveAurasDueToSpell(SPELL_EXPLODING_ORB_VISUAL);
                if (target->GetTypeId() == TYPEID_UNIT)
                    target->ToCreature()->DespawnOrUnsummon(2s);
            }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_exploding_orb_auto_grow_AuraScript::HandlePeriodicTick, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

void AddSC_boss_ick()
{
    new CreatureAILoader<boss_ickAI>("boss_ick");
    new CreatureAILoader<boss_krickAI>("boss_krick");

    new AuraScriptLoaderEx<spell_krick_explosive_barrage_AuraScript>("spell_krick_explosive_barrage");
    new AuraScriptLoaderEx<spell_exploding_orb_auto_grow_AuraScript>("spell_exploding_orb_auto_grow");
}