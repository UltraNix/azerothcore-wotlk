#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "trial_of_the_crusader.h"
#include "SpellScript.h"
#include "PassiveAI.h"
#include "SpellAuras.h"
#include "Player.h"

enum Yells
{
    SAY_AGGRO,
    SAY_LIGHT,
    SAY_NIGHT,
    EMOTE_VORTEX,
    EMOTE_TWINK_PACT,
    SAY_TWINK_PACT,
    SAY_KILL_PLAYER_1,
    SAY_BERSERK,
    SAY_DEATH,
    SAY_KILL_PLAYER_2
};

enum Equipment
{
    EQUIP_MAIN_1 = 49303,
    EQUIP_OFFHAND_1 = 47146,
    EQUIP_RANGED_1 = 47267,
    EQUIP_MAIN_2 = 45990,
    EQUIP_OFFHAND_2 = 47470,
    EQUIP_RANGED_2 = 47267,
};

enum ValkyrNPCs
{
    NPC_DARK_ESSENCE = 34567,
    NPC_LIGHT_ESSENCE = 34568,
    NPC_CONCENTRATED_DARK = 34628,
    NPC_CONCENTRATED_LIGHT = 34630,
};

enum ValkyrSpells
{
    SPELL_LIGHT_ESSENCE = 65686,
    SPELL_LIGHT_ESSENCE_2 = 65811,
    SPELL_DARK_ESSENCE = 65684,
    SPELL_DARK_ESSENCE_2 = 65827,

    SPELL_UNLEASHED_DARK = 65808,
    SPELL_UNLEASHED_LIGHT = 65795,
    SPELL_POWERING_UP = 67590,
    SPELL_EMPOWERED_DARK = 65724,
    SPELL_EMPOWERED_LIGHT = 65748,
    SPELL_SURGE_OF_SPEED = 65828,

    SPELL_LIGHT_TWIN_SPIKE = 66075,
    SPELL_LIGHT_SURGE = 65766,
    SPELL_LIGHT_SHIELD = 65858,
    SPELL_LIGHT_TWIN_PACT = 65876,
    SPELL_LIGHT_VORTEX = 66046,
    SPELL_LIGHT_TOUCH = 67297,

    SPELL_DARK_TWIN_SPIKE = 66069,
    SPELL_DARK_SURGE = 65768,
    SPELL_DARK_SHIELD = 65874,
    SPELL_DARK_TWIN_PACT = 65875,
    SPELL_DARK_VORTEX = 66058,
    SPELL_DARK_TOUCH = 67282,

    SPELL_TWIN_POWER = 65916,
    SPELL_BERSERK = 64238,

    SPELL_VALKYR_HITTING_YA = 66073,
    SPELL_VALKYR_HITTING_YA_PROC = 66072
};

enum ValkyrEvents
{
    EVENT_BERSERK = 1,
    EVENT_SUMMON_BALLS_1,
    EVENT_SUMMON_BALLS_2,
    EVENT_SUMMON_BALLS_3,
    EVENT_SPELL_SPIKE,
    EVENT_SPELL_TOUCH,
    EVENT_SPECIAL,
    EVENT_REMOVE_DUAL_WIELD,
};

struct boss_twin_valkyrAI : public ScriptedAI
{
    boss_twin_valkyrAI(Creature* creature) : ScriptedAI(creature), summons(me)
    {
        instance = creature->GetInstanceScript();
        me->SetReactState(REACT_PASSIVE);
        me->SetModifierValue(UNIT_MOD_DAMAGE_OFFHAND, TOTAL_PCT, 1.0f);
        me->UpdateDamagePhysical(OFF_ATTACK);
        _lastSynchroHP = (int32)me->GetMaxHealth();
        _specialMask = 0;
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_HASTE_SPELLS, true);

        _events.Reset();
        if (me->GetEntry() == NPC_LIGHTBANE)
        {
            if (instance)
                instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, 21853);

            // special events here
            _events.RescheduleEvent(EVENT_BERSERK, IsHeroic() ? 360000 : 600000);
            _events.RescheduleEvent(EVENT_SUMMON_BALLS_1, urand(10000, 15000));
            _events.RescheduleEvent(EVENT_SPECIAL, 45000);
        }
        _events.RescheduleEvent(EVENT_SPELL_SPIKE, urand(5000, 8000));

        if (IsHeroic())
            _events.RescheduleEvent(EVENT_SPELL_TOUCH, urand(10000, 25000), 1);

        me->SetDisableGravity(true);
        me->SetHover(true);
        me->SetCanFly(true);
        DoCastSelf(SPELL_VALKYR_HITTING_YA);
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

    void DoAction(int32 action) override
    {
        switch (action)
        {
        case -1:
            summons.DespawnAll();
            if (instance && me->GetEntry() == NPC_LIGHTBANE)
            {
                uint32 essenceId1 = 0, empoweredId1 = 0, touchId1 = 0, essenceId2 = 0, empoweredId2 = 0, touchId2 = 0;
                switch (me->GetMap()->GetDifficulty())
                {
                case 0:
                    essenceId1 = 65684;
                    empoweredId1 = 65724;
                    touchId1 = 65950;
                    essenceId2 = 65686;
                    empoweredId2 = 65748;
                    touchId2 = 66001;
                    break;
                case 1:
                    essenceId1 = 67176;
                    empoweredId1 = 67213;
                    touchId1 = 67296;
                    essenceId2 = 67222;
                    empoweredId2 = 67216;
                    touchId2 = 67281;
                    break;
                case 2:
                    essenceId1 = 67177;
                    empoweredId1 = 67214;
                    touchId1 = 67297;
                    essenceId2 = 67223;
                    empoweredId2 = 67217;
                    touchId2 = 67282;
                    break;
                case 3:
                    essenceId1 = 67178;
                    empoweredId1 = 67215;
                    touchId1 = 67298;
                    essenceId2 = 67224;
                    empoweredId2 = 67218;
                    touchId2 = 67283;
                    break;
                }
                instance->DoRemoveAurasDueToSpellOnPlayers(essenceId1);
                instance->DoRemoveAurasDueToSpellOnPlayers(empoweredId1);
                instance->DoRemoveAurasDueToSpellOnPlayers(touchId1);
                instance->DoRemoveAurasDueToSpellOnPlayers(essenceId2);
                instance->DoRemoveAurasDueToSpellOnPlayers(empoweredId2);
                instance->DoRemoveAurasDueToSpellOnPlayers(touchId2);
            }
            break;
        case -3:
            me->SetCanDualWield(true);
            DoCastSelf(SPELL_TWIN_POWER, true);
            _events.RescheduleEvent(EVENT_REMOVE_DUAL_WIELD, 15000);
            break;
        }
    }

    Creature* GetSister() const
    {
        return ObjectAccessor::GetCreature(*me, instance->GetData64(me->GetEntry() == NPC_DARKBANE ? NPC_LIGHTBANE : NPC_DARKBANE));
    }

    void EnterCombat(Unit* /*who*/) override
    {
        me->setActive(true);
        me->LowerPlayerDamageReq(me->GetMaxHealth());
        DoZoneInCombat();
        if (Creature* twin = GetSister())
            if (!twin->IsInCombat())
                if (Unit* target = twin->SelectNearestTarget(200.0f))
                    twin->AI()->AttackStart(target);

        Talk(SAY_AGGRO);
        DoCastSelf(me->GetEntry() == NPC_LIGHTBANE ? SPELL_LIGHT_SURGE : SPELL_DARK_SURGE, true);

        if (instance && me->GetEntry() == NPC_LIGHTBANE)
            instance->DoStartTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, 21853);
    }

    void JustReachedHome() override
    {
        me->setActive(false);
    }

    void UpdateSharedHealth()
    {
        // lightbane synchronizes
        if (me->GetEntry() == NPC_LIGHTBANE)
            if (Creature* twin = GetSister())
                if (twin->IsAlive() && me->IsAlive())
                {
                    int32 d = CAST_AI(boss_twin_valkyrAI, twin->AI())->_lastSynchroHP - (int32)twin->GetHealth();
                    int32 newhealth = (int32)me->GetHealth() - d;
                    if (newhealth <= 0)
                        newhealth = 1;
                    me->SetHealth((uint32)newhealth);
                    twin->SetHealth(me->GetHealth());
                    CAST_AI(boss_twin_valkyrAI, twin->AI())->_lastSynchroHP = (int32)twin->GetHealth();
                }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        UpdateSharedHealth();
        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.GetEvent())
        {
            switch (eventId)
            {
            case EVENT_BERSERK:
                DoCastSelf(SPELL_BERSERK, true);
                Talk(SAY_BERSERK);
                if (Creature* twin = GetSister())
                {
                    twin->CastSpell(twin, SPELL_BERSERK, true);
                    if (twin->IsAIEnabled)
                        twin->AI()->Talk(SAY_BERSERK);
                }
                _events.PopEvent();
                break;
            case EVENT_SUMMON_BALLS_1:
            case EVENT_SUMMON_BALLS_2:
            case EVENT_SUMMON_BALLS_3:
            {
                uint8 eventId = _events.GetEvent();
                uint8 count = 0;
                if (IsHeroic())
                    count = eventId == EVENT_SUMMON_BALLS_3 ? 45 : 10;
                else
                    count = eventId == EVENT_SUMMON_BALLS_3 ? 30 : 6;
                for (uint8 i = 0; i<count; ++i)
                {
                    float angle = Position::RandomOrientation();
                    if (Creature* ball = me->SummonCreature((i % 2) ? NPC_CONCENTRATED_DARK : NPC_CONCENTRATED_LIGHT, Locs[LOC_CENTER].GetPositionX() + cos(angle)*47.0f, Locs[LOC_CENTER].GetPositionY() + sin(angle)*47.0f, Locs[LOC_CENTER].GetPositionZ() + 1.5f, 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1500))
                        boss_twin_valkyrAI::JustSummoned(ball);
                }
                _events.PopEvent();
                switch (eventId)
                {
                case EVENT_SUMMON_BALLS_1:
                    _events.RescheduleEvent(EVENT_SUMMON_BALLS_2, 8000);
                    break;
                case EVENT_SUMMON_BALLS_2:
                    _events.RescheduleEvent(EVENT_SUMMON_BALLS_3, 8000);
                    break;
                case EVENT_SUMMON_BALLS_3:
                    _events.RescheduleEvent(EVENT_SUMMON_BALLS_1, 15000);
                    break;
                }
            }
            break;
            case EVENT_SPELL_SPIKE:
                me->CastSpell(me->GetVictim(), me->GetEntry() == NPC_LIGHTBANE ? SPELL_LIGHT_TWIN_SPIKE : SPELL_DARK_TWIN_SPIKE, false);
                _events.RepeatEvent(urand(7000, 10000));
                break;
            case EVENT_SPELL_TOUCH:
            {
                DoCastAOE(me->GetEntry() == NPC_LIGHTBANE ? SPELL_LIGHT_TOUCH : SPELL_DARK_TOUCH);
                _events.RepeatEvent(45000);
                break;
            }
            case EVENT_SPECIAL:
            {
                uint8 s;
                do s = urand(0, 3); while (_specialMask & (1 << s) && (_specialMask & 0xF) != 0xF);
                _specialMask |= (1 << s);
                switch (s)
                {
                case 0: // light vortex
                    DoCastAOE(SPELL_LIGHT_VORTEX);
                    Talk(EMOTE_VORTEX);
                    Talk(SAY_LIGHT);
                    if (Creature* twin = GetSister())
                        twin->AI()->Talk(SAY_LIGHT);
                    break;
                case 1: // dark vortex
                    if (Creature* twin = GetSister())
                    {
                        twin->CastSpell((Unit*)nullptr, SPELL_DARK_VORTEX, false);
                        if (twin->IsAIEnabled)
                        {
                            twin->AI()->Talk(EMOTE_VORTEX);
                            twin->AI()->Talk(SAY_NIGHT);
                        }
                        Talk(SAY_NIGHT);
                    }
                    break;
                case 2: // light pact
                    Talk(EMOTE_TWINK_PACT);
                    Talk(SAY_TWINK_PACT);
                    if (Creature* twin = GetSister())
                    {
                        if (twin->IsAIEnabled)
                        {
                            twin->AI()->Talk(SAY_TWINK_PACT);
                            twin->AI()->DoAction(-3);
                        }
                    }
                    DoCastSelf(SPELL_LIGHT_SHIELD, true);
                    DoCastSelf(SPELL_LIGHT_TWIN_PACT);
                    break;
                case 3: // dark pact
                    if (Creature* twin = GetSister())
                    {
                        twin->AI()->Talk(EMOTE_TWINK_PACT);
                        twin->AI()->Talk(SAY_TWINK_PACT);
                        Talk(SAY_TWINK_PACT);
                        twin->CastSpell(twin, SPELL_DARK_SHIELD, true);
                        twin->CastSpell(twin, SPELL_DARK_TWIN_PACT, false);
                        DoAction(-3);
                    }
                    break;
                }
                if ((_specialMask & 0xF) == 0xF)
                    _specialMask = 0;
                _events.RepeatEvent(45000);
                _events.DelayEventsToMax(15000, 1); // no touch of light/darkness during special abilities!
            }
            break;
            case EVENT_REMOVE_DUAL_WIELD:
                me->SetCanDualWield(false);
                _events.PopEvent();
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void RemovePoweringUp()
    {
        instance->DoRemoveAurasDueToSpellOnPlayers(67590);
        instance->DoRemoveAurasDueToSpellOnPlayers(67602);
        instance->DoRemoveAurasDueToSpellOnPlayers(67603);
        instance->DoRemoveAurasDueToSpellOnPlayers(67604);
    }

    void JustDied(Unit* /*killer*/) override
    {
        RemovePoweringUp();
        DoAction(-1);
        Talk(SAY_DEATH);
        if (instance)
        {
            instance->SetData(TYPE_VALKYR, DONE);
            instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_POWERING_UP);
        }
        if (Creature* twin = GetSister())
            if (twin->IsAlive())
            {
                twin->SetHealth(1);
                Unit::Kill(twin, twin);
            }
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        summons.Despawn(summon);
    }

    void KilledUnit(Unit* who) override
    {
        if (who->GetTypeId() == TYPEID_PLAYER)
        {
            int32 id = urand(0, 1) ? SAY_KILL_PLAYER_1 : SAY_KILL_PLAYER_2;
            Talk(id);
            if (Creature* twin = GetSister())
                if (twin->IsAIEnabled)
                    twin->AI()->Talk(id);
        }
    }

    void EnterEvadeMode()
    {
        RemovePoweringUp();
        if (instance)
            instance->SetData(TYPE_FAILED, 0);
    }

private:
    InstanceScript* instance;
    SummonList summons;
    EventMap _events;
    int32 _lastSynchroHP;
    uint8 _specialMask;
};

struct boss_eydisAI : public boss_twin_valkyrAI
{
    boss_eydisAI(Creature* creature) : boss_twin_valkyrAI(creature)
    {
        me->SetFlag(UNIT_FIELD_AURASTATE, 1 << (19 - 1));
        SetEquipmentSlots(false, EQUIP_MAIN_2, EQUIP_OFFHAND_2, EQUIP_RANGED_2);
        if (Creature* c = me->SummonCreature(NPC_DARK_ESSENCE, Locs[LOC_DARKESS_1]))
            boss_twin_valkyrAI::JustSummoned(c);
        if (Creature* c = me->SummonCreature(NPC_DARK_ESSENCE, Locs[LOC_DARKESS_2]))
            boss_twin_valkyrAI::JustSummoned(c);
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

    void JustSummoned(Creature* /*summon*/) override {}
};

struct boss_fjolaAI : public boss_twin_valkyrAI
{
    boss_fjolaAI(Creature* creature) : boss_twin_valkyrAI(creature)
    {
        me->SetFlag(UNIT_FIELD_AURASTATE, 1 << (22 - 1));
        SetEquipmentSlots(false, EQUIP_MAIN_1, EQUIP_OFFHAND_1, EQUIP_RANGED_1);
        if (Creature* c = me->SummonCreature(NPC_LIGHT_ESSENCE, Locs[LOC_LIGHTESS_1]))
            boss_twin_valkyrAI::JustSummoned(c);
        if (Creature* c = me->SummonCreature(NPC_LIGHT_ESSENCE, Locs[LOC_LIGHTESS_2]))
            boss_twin_valkyrAI::JustSummoned(c);
    }

    void JustSummoned(Creature* /*summon*/) {}
};

class npc_essence_of_twin : public CreatureScript
{
public:
    npc_essence_of_twin() : CreatureScript("npc_essence_of_twin") { }

    bool OnGossipHello(Player* player, Creature* creature)
    {
        switch (creature->GetEntry())
        {
        case NPC_LIGHT_ESSENCE:
        {
            uint32 essenceId = 0;
            uint32 effect2Id = 0;
            uint32 empoweredId = 0;
            uint32 touchId1 = 0;
            uint32 touchId2 = 0;
            switch (creature->GetMap()->GetDifficulty())
            {
            case 0:
                essenceId = 65684;
                empoweredId = 65724;
                touchId1 = 65950;
                touchId2 = 66001;
                effect2Id = 65827;
                break;
            case 1:
                essenceId = 67176;
                empoweredId = 67213;
                touchId1 = 67296;
                touchId2 = 67281;
                effect2Id = 67179;
                break;
            case 2:
                essenceId = 67177;
                empoweredId = 67214;
                touchId1 = 67297;
                touchId2 = 67282;
                effect2Id = 67180;
                break;
            case 3:
                essenceId = 67178;
                empoweredId = 67215;
                touchId1 = 67298;
                touchId2 = 67283;
                effect2Id = 67181;
                break;
            }
            player->RemoveAura(essenceId);
            player->RemoveAura(effect2Id);
            player->RemoveAura(touchId1);
            player->CastSpell(player, SPELL_LIGHT_ESSENCE, true);
        }
        break;
        case NPC_DARK_ESSENCE:
        {
            uint32 essenceId = 0;
            uint32 effect2Id = 0;
            uint32 empoweredId = 0;
            uint32 touchId1 = 0;
            uint32 touchId2 = 0;
            switch (creature->GetMap()->GetDifficulty())
            {
            case 0:
                essenceId = 65686;
                empoweredId = 65748;
                touchId1 = 65950;
                touchId2 = 66001;
                effect2Id = 65811;
                break;
            case 1:
                essenceId = 67222;
                empoweredId = 67216;
                touchId1 = 67296;
                touchId2 = 67281;
                effect2Id = 67511;
                break;
            case 2:
                essenceId = 67223;
                empoweredId = 67217;
                touchId1 = 67297;
                touchId2 = 67282;
                effect2Id = 67512;
                break;
            case 3:
                essenceId = 67224;
                empoweredId = 67218;
                touchId1 = 67298;
                touchId2 = 67283;
                effect2Id = 67513;
                break;
            }
            player->RemoveAura(essenceId);
            player->RemoveAura(effect2Id);
            player->RemoveAura(touchId2);
            player->CastSpell(player, SPELL_DARK_ESSENCE, true);
        }
        break;
        default:
            break;
        }
        player->CLOSE_GOSSIP_MENU();
        return true;
    }
};

struct npc_concentrated_ballAI : public ScriptedAI
{
    npc_concentrated_ballAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        _despawning = false;
        me->SetSpeed(MOVE_RUN, 0.5f, true);
    }

    void DoAction(int32 param) override
    {
        if (param == 1)
            _despawning = true;
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE || id != 0)
            return;

        if (urand(0, 2))
            me->DespawnOrUnsummon(0);
    }

    void MoveToNextPoint()
    {
        float angle = Position::RandomOrientation();
        me->GetMotionMaster()->MovePoint(0, Locs[LOC_CENTER].GetPositionX() + cos(angle)*47.0f, Locs[LOC_CENTER].GetPositionY() + sin(angle)*47.0f, me->GetPositionZ());
    }

    void UpdateAI(uint32 diff) override
    {
        if (_despawning)
            return;

        if (Player* target = SelectTargetFromPlayerList(2.75f))
        {
            _despawning = true;
            me->GetMotionMaster()->MoveIdle();
            DoCastAOE(me->GetEntry() == NPC_CONCENTRATED_LIGHT ? SPELL_UNLEASHED_LIGHT : SPELL_UNLEASHED_DARK);
            me->SetDisplayId(11686);
            me->DespawnOrUnsummon(1500);
        }

        if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
            MoveToNextPoint();
    }

private:
    bool _despawning;
};

class spell_valkyr_essence_auraAuraScript : public AuraScript
{
    PrepareAuraScript(spell_valkyr_essence_auraAuraScript);

    void HandleAfterEffectAbsorb(AuraEffect * /*aurEff*/, DamageInfo & /*dmgInfo*/, uint32 & absorbAmount)
    {
        uint16 divisionAmount = 2300;

        if (auto caster = GetCaster())
        {
            if (auto map = caster->GetMap())
            {
                if (map->Is25ManRaid() && !map->IsHeroic())
                    divisionAmount = 1200;
                else if (!map->Is25ManRaid() && map->IsHeroic())
                    divisionAmount = 1500;
                else if (!map->Is25ManRaid() && !map->IsHeroic())
                    divisionAmount = 1200;
            }
        }

        uint16 count = absorbAmount / divisionAmount;
        if (!count || !GetOwner())
            return;

        if (const SpellInfo* se = GetAura()->GetSpellInfo())
            if (Unit* owner = GetOwner()->ToUnit())
            {
                uint32 auraId = 0;
                uint32 empoweredId = 0;
                switch (se->Id)
                {
                    case 65686:
                        auraId = 67590;
                        empoweredId = 65748;
                        break;
                    case 65684:
                        auraId = 67590;
                        empoweredId = 65724;
                        break;
                    case 67222:
                        auraId = 67602;
                        empoweredId = 65748;
                        break;
                    case 67176:
                        auraId = 67602;
                        empoweredId = 65724;
                        break;
                    case 67223:
                        auraId = 67603;
                        empoweredId = 65748;
                        break;
                    case 67177:
                        auraId = 67603;
                        empoweredId = 65724;
                        break;
                    case 67224:
                        auraId = 67604;
                        empoweredId = 65748;
                        break;
                    case 67178:
                        auraId = 67604;
                        empoweredId = 65724;
                        break;
                }
                if (!owner->HasAura(auraId))
                {
                    owner->CastSpell(owner, SPELL_POWERING_UP, true);
                    if (--count == 0)
                        return;
                }
                if (Aura* aur = owner->GetAura(auraId))
                {
                    if (aur->GetStackAmount() + count < 100)
                    {
                        aur->ModStackAmount(count);

                        if (roll_chance_i(30)) // 30% chance to gain extra speed for collecting
                            owner->CastSpell(owner, SPELL_SURGE_OF_SPEED, true);
                    }
                    else
                    {
                        owner->CastSpell(owner, empoweredId, true);
                        aur->Remove();
                    }
                }
            }
    }

    void Register() override
    {
        AfterEffectAbsorb += AuraEffectAbsorbFn(spell_valkyr_essence_auraAuraScript::HandleAfterEffectAbsorb, EFFECT_0);
    }
};

enum spellValkyrTouchHelpers
{
    SPELL_LIGHT_ESSENCE_HELPER_10MAN = 67223,
    SPELL_LIGHT_ESSENCE_HELPER_25MAN = 67224,

    SPELL_DARK_ESSENCE_HELPER_10MAN = 67177,
    SPELL_DARK_ESSENCE_HELPER_25MAN = 67178
};

class spell_valkyr_touch_light_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_valkyr_touch_light_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* target)
        {
            return target->ToPlayer()->HasAura(target->GetMap()->Is25ManRaid() ? SPELL_LIGHT_ESSENCE_HELPER_25MAN : SPELL_LIGHT_ESSENCE_HELPER_10MAN) ||
                target->ToPlayer()->HasAura(SPELL_VALKYR_HITTING_YA_PROC);
        });

        Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 2 : 1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_valkyr_touch_light_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_valkyr_touch_light_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

class spell_valkyr_touch_dark_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_valkyr_touch_dark_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([](WorldObject* target)
        {
            return target->ToPlayer()->HasAura(target->GetMap()->Is25ManRaid() ? SPELL_DARK_ESSENCE_HELPER_25MAN : SPELL_DARK_ESSENCE_HELPER_10MAN) ||
                target->ToPlayer()->HasAura(SPELL_VALKYR_HITTING_YA_PROC);
        });

        Trinity::Containers::RandomResizeList(targets, GetCaster()->GetMap()->Is25ManRaid() ? 2 : 1);
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_valkyr_touch_dark_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENEMY);
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_valkyr_touch_dark_SpellScript::FilterTargets, EFFECT_2, TARGET_UNIT_SRC_AREA_ENEMY);
    }
};

void AddSC_boss_twin_valkyr()
{
    new CreatureAILoader<boss_eydisAI>("boss_eydis");
    new CreatureAILoader<boss_fjolaAI>("boss_fjola");
    new npc_essence_of_twin();
    new CreatureAILoader<npc_concentrated_ballAI>("npc_concentrated_ball");
    new AuraScriptLoaderEx<spell_valkyr_essence_auraAuraScript>("spell_valkyr_essence");
    new SpellScriptLoaderEx<spell_valkyr_touch_light_SpellScript>("spell_valkyr_touch_light");
    new SpellScriptLoaderEx<spell_valkyr_touch_dark_SpellScript>("spell_valkyr_touch_dark");
}
