#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "pit_of_saron.h"
#include "SpellScript.h"
#include "SpellAuras.h"
#include "Player.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "CreatureGroups.h"
#include "Chat.h"
#include "GameObjectAI.h"

enum GarfrostYells
{
    SAY_AGGRO                   = 14,
    SAY_SLAY_1                  = 15,
    SAY_DEATH                   = 17,
    SAY_FORGE_1                 = 18,
    SAY_FORGE_2                 = 19,

    SAY_BOULDER_HIT             = 16,
    EMOTE_DEEP_FREEZE           = 23
};

enum GarfrostMisc
{
    EQUIP_ID_SWORD              = 49345,
    EQUIP_ID_MACE               = 49344,
    GO_SARONITE_ROCK            = 196485,

    DATA_GO_TO_ELEVEN           = 1
};

enum GarfrostSpells
{
    SPELL_PERMAFROST            = 70326,
    SPELL_THROW_SARONITE        = 68788,
    SPELL_THUNDERING_STOMP      = 68771,

    SPELL_CHILLING_WAVE         = 68778,
    SPELL_DEEP_FREEZE           = 70381,

    SPELL_FORGE_BLADE           = 68774,
    SPELL_FORGE_MACE            = 68785,
    SPELL_SARONITE_TRIGGERED    = 68789
};

enum GarfrostEvents
{
    EVENT_THROW_SARONITE        = 1,
    EVENT_JUMP,
    EVENT_CHILLING_WAVE,
    EVENT_DEEP_FREEZE,
    EVENT_KILL_TALK,

    EVENT_DESPAWN
};

struct boss_garfrostAI : public BossAI
{
    boss_garfrostAI(Creature* creature) : BossAI(creature, DATA_GARFROST) { }

    void Reset() override
    {
        _Reset();
        me->RemoveAura(SPELL_PERMAFROST);
        SetEquipmentSlots(true);
        me->SetReactState(REACT_AGGRESSIVE);
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        _phase = 0;
        _goToEleven = true;
        _canSayWhenHit = true;
    }

    uint32 GetData(uint32 type) const override
    {
        if (type == DATA_GO_TO_ELEVEN)
            return static_cast<uint32>(_goToEleven);

        return 0;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        DoCastSelf(SPELL_PERMAFROST, true);
        _EnterCombat();
        Talk(SAY_AGGRO);
        events.RescheduleEvent(EVENT_THROW_SARONITE, 5.0s, 7.5s);
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*damageSchoolMask*/) override
    {
        if (_phase == 2)
            return;

        if (me->HealthBelowPctDamaged(100 - 33 * (_phase + 1), damage) && !me->HasUnitState(UNIT_STATE_ROOT))
        {
            ++_phase;
            events.CancelEvent(EVENT_CHILLING_WAVE);
            me->SetReactState(REACT_PASSIVE);
            me->SetTarget(0);
            me->SendMeleeAttackStop(me->GetVictim());
            events.DelayEvents(8s);
            DoCastSelf(SPELL_THUNDERING_STOMP);
            events.RescheduleEvent(EVENT_JUMP, 1.250s);
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type == EFFECT_MOTION_TYPE && id == 0)
        {
            me->SetControlled(true, UNIT_STATE_ROOT);
            me->RemoveAurasDueToSpell(IsHeroic() ? 70334 : SPELL_FORGE_BLADE);
            if (_phase == 1)
            {
                DoCastSelf(SPELL_FORGE_BLADE);
                Talk(SAY_FORGE_1);
            }
            else
            {
                DoCastSelf(SPELL_FORGE_MACE);
                Talk(SAY_FORGE_2);
            }
        }
    }

    void HandleWeaponChange(uint32 equipId)
    {
        events.RescheduleEvent(equipId == EQUIP_ID_SWORD ? EVENT_CHILLING_WAVE : EVENT_DEEP_FREEZE, 10s);
        SetEquipmentSlots(false, equipId);
        me->SetReactState(REACT_AGGRESSIVE);
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        if (Unit* victim = me->GetVictim())
        {
            AttackStart(victim);
            me->SetTarget(victim->GetGUID());
        }
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell) override
    {
        switch (spell->Id)
        {
            case SPELL_SARONITE_TRIGGERED:
            case 70851:
                if (_canSayWhenHit)
                {
                    _canSayWhenHit = false;
                    Talk(SAY_BOULDER_HIT);
                }
                break;
            case SPELL_FORGE_BLADE:
            case 70334:
                HandleWeaponChange(EQUIP_ID_SWORD);
                break;
            case SPELL_FORGE_MACE:
            case 70335:
                HandleWeaponChange(EQUIP_ID_MACE);
                break;
            case 70336:
                if (Aura* aura = target->GetAura(70336))
                    if (aura->GetStackAmount() >= 11)
                        _goToEleven = false;
                break;
            default:
                break;
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
        case EVENT_THROW_SARONITE:
            _canSayWhenHit = true;
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 140.0f, true))
            {
                WorldPacket data;
                ChatHandler::BuildChatPacket(data, CHAT_MSG_RAID_BOSS_EMOTE, LANG_UNIVERSAL, me, nullptr, "%s hurls a massive saronite boulder at you!");
                target->ToPlayer()->GetSession()->SendPacket(&data);
                DoCast(target, SPELL_THROW_SARONITE);
            }
            events.Repeat(12.5s, 20.0s);
            break;
        case EVENT_JUMP:
        {
            me->DisableRotate(true);
            Position pos = (_phase == 1 ? Position(722.5643f, -234.1615f, 527.182f, 2.16421f) : Position(639.257f, -210.1198f, 529.015f, 0.523599f));
            me->GetMotionMaster()->MoveJump(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), 25.0f, 15.0f, 0);
            break;
        }
        case EVENT_CHILLING_WAVE:
            DoCastVictim(SPELL_CHILLING_WAVE);
            events.Repeat(35s);
            break;
        case EVENT_DEEP_FREEZE:
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0.0f, true))
            {
                Talk(EMOTE_DEEP_FREEZE, target);
                DoCast(target, SPELL_DEEP_FREEZE);
            }
            events.Repeat(35s);
            break;
        default:
            break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
    }

    void KilledUnit(Unit* who) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(SAY_SLAY_1);
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    void EnterEvadeMode() override
    {
        me->SetControlled(false, UNIT_STATE_ROOT);
        me->DisableRotate(false);
        _DespawnAtEvade();
        std::list<Creature*> addList;
        me->GetCreatureListWithEntryInGrid(addList, 36907, 250.0f);
        for (auto creature : addList)
        {
            if (!creature->IsAlive())
                creature->Respawn();
            _DespawnAtEvade(30, creature);
        }
        std::list<GameObject*> boulderList;
        me->GetGameObjectListWithEntryInGrid(boulderList, GO_SARONITE_ROCK, 250.0f);
        for (auto boulder : boulderList)
            boulder->AddObjectToRemoveList();
    }

    private:
        uint8 _phase;
        bool _canSayWhenHit;
        bool _goToEleven;
};

class go_saronite_rock : public GameObjectScript
{
    public:
        go_saronite_rock() : GameObjectScript("go_saronite_rock") {}

        struct go_saronite_rockAI : public GameObjectAI
        {
            go_saronite_rockAI(GameObject* go) : GameObjectAI(go)
            {
                _events.RescheduleEvent(EVENT_DESPAWN, 60s);
            }

            void UpdateAI(uint32 diff) override
            {
                if (_events.Empty())
                    return;

                _events.Update(diff);

                if (_events.ExecuteEvent() == EVENT_DESPAWN)
                    go->AddObjectToRemoveList();
            }

        private:
            EventMap _events;
        };

        GameObjectAI* GetAI(GameObject* go) const override
        {
            return new go_saronite_rockAI(go);
        }
};


class spell_garfrost_permafrost_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_garfrost_permafrost_SpellScript)

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        std::list<WorldObject*> targetList;
        for (auto target : targets)
            if (target->IsWithinLOSInMap(GetCaster()) || target->GetDistance(GetCaster()) < 4.0f)
                targetList.push_back(target);

        targets = targetList;
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_garfrost_permafrost_SpellScript::FilterTargets, EFFECT_ALL, TARGET_UNIT_DEST_AREA_ENEMY);
    }
};

class achievement_garfrost_doesnt_go_to_eleven : public AchievementCriteriaScript
{
    public:
        achievement_garfrost_doesnt_go_to_eleven() : AchievementCriteriaScript("achievement_garfrost_doesnt_go_to_eleven") { }

        bool OnCheck(Player* /*source*/, Unit* target) override
        {
            if (target && target->ToUnit() && target->ToUnit()->IsAIEnabled && target->GetMap()->IsHeroic())
                return target->GetAI()->GetData(DATA_GO_TO_ELEVEN);
            return false;
        }
};

void AddSC_boss_garfrost()
{
    new CreatureAILoader<boss_garfrostAI>("boss_garfrost");
    new go_saronite_rock();
    new SpellScriptLoaderEx<spell_garfrost_permafrost_SpellScript>("spell_garfrost_permafrost");
    new achievement_garfrost_doesnt_go_to_eleven();
}