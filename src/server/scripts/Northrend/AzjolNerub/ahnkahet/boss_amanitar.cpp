#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ahnkahet.h"

enum AmanitarSpells
{
    // Amanitar
    SPELL_BASH                              = 57094,
    SPELL_ENTANGLING_ROOTS                  = 57095,
    SPELL_MINI                              = 57055,
    SPELL_VENOM_BOLT_VOLLEY                 = 57088,
    SPELL_REMOVE_MUSHROOM_POWER             = 57283,
    // Mushrooms
    SPELL_POTENT_FUNGUS                     = 56648,
    SPELL_POISONOUS_MUSHROOM_POISON_CLOUD   = 57061,
    SPELL_POISONOUS_MUSHROOM_VISUAL_AURA    = 56741,
    SPELL_POWER_MUSHROOM_VISUAL_AURA        = 56740,
    SPELL_PUTRID_MUSHROOM                   = 31690,
    SPELL_GROW                              = 54244,
    SPELL_SHRINK                            = 31691
};

enum AmanitarEvents
{
    // Amanitar
    EVENT_ROOTS                             = 1,
    EVENT_BASH,
    EVENT_VOLLEY,
    EVENT_SPAWN,
    EVENT_RESPAWN,
    EVENT_MINI,

    // Mushrooms
    EVENT_GROW                              = 1,
    EVENT_SHRINK
};

Position const MushroomPositions[32] =
{
    { 373.4807f, -856.5301f, -74.30518f, 0.2094395f },
    { 358.4792f, -879.3193f, -75.9463f,  5.166174f },
    { 356.5531f, -846.3022f, -72.1796f,  3.193953f },
    { 332.369f,  -846.081f,  -74.30516f, 4.834562f },
    { 360.2234f, -862.055f,  -75.22755f, 1.658063f },
    { 351.7189f, -890.9619f, -76.54617f, 1.064651f },
    { 345.8126f, -869.1772f, -77.17728f, 1.361357f },
    { 367.5179f, -884.0129f, -77.32881f, 4.276057f },
    { 370.6044f, -868.4305f, -74.19881f, 0.8901179f },
    { 381.3156f, -873.2377f, -74.82656f, 1.099557f },
    { 371.5869f, -873.8141f, -74.72424f, 1.082104f },
    { 340.4079f, -891.6375f, -74.99128f, 1.134464f },
    { 368.21f,   -851.5953f, -73.99741f, 4.694936f },
    { 328.7047f, -853.9812f, -75.51253f, 0.5759587f },
    { 366.4145f, -876.39f,   -75.52739f, 5.253441f },
    { 380.1362f, -861.4344f, -73.45917f, 3.787364f },
    { 373.3007f, -888.8057f, -79.03593f, 5.602507f },
    { 348.3599f, -848.0839f, -73.54117f, 1.745329f },
    { 352.5586f, -882.6624f, -75.68202f, 3.822271f },
    { 357.8967f, -871.179f,  -75.77553f, 2.443461f },
    { 360.1034f, -842.3351f, -71.08852f, 4.34587f },
    { 348.1334f, -861.5244f, -74.61307f, 2.565634f },
    { 401.4896f, -866.7059f, -73.22395f, 0.8901179f },
    { 360.1683f, -889.1515f, -76.74798f, 3.612832f },
    { 350.1828f, -907.7313f, -74.94678f, 5.044002f },
    { 340.6278f, -856.5973f, -74.23862f, 4.415683f },
    { 366.4849f, -859.7621f, -74.82679f, 1.500983f },
    { 359.1482f, -853.3346f, -74.47543f, 5.654867f },
    { 374.9992f, -879.0921f, -75.56115f, 1.867502f },
    { 339.5252f, -850.4612f, -74.45442f, 4.764749f },
    { 337.0534f, -864.002f,  -75.72749f, 4.642576f },
    { 398.2797f, -851.8694f, -68.84419f, 0.5759587f }
};

struct boss_amanitarAI : public BossAI
{
    boss_amanitarAI(Creature* creature) : BossAI(creature, BOSS_AMANITAR) { }

    void Reset() override
    {
        _Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _EnterCombat();
        events.ScheduleEvent(EVENT_ROOTS, 5s, 9s);
        events.ScheduleEvent(EVENT_BASH, 10s, 14s);
        events.ScheduleEvent(EVENT_VOLLEY, 15s, 20s);
        events.ScheduleEvent(EVENT_SPAWN, 50ms);
        events.ScheduleEvent(EVENT_RESPAWN, 40s, 60s);
        events.ScheduleEvent(EVENT_MINI, 12s, 18s);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        BossAI::SummonedCreatureDies(summon, killer);
    }

    void SummonedCreatureDespawn(Creature* summon) override
    {
        _mushroomsDeque.push_back(summon->GetPosition());
        BossAI::SummonedCreatureDespawn(summon);
    }

    void SpawnMushroom(Position const pos) const
    {
        me->SummonCreature(roll_chance_i(40) ? NPC_HEALTHY_MUSHROOM : NPC_POISONOUS_MUSHROOM, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 4000);
    }

    void JustDied(Unit* /*killer*/) override
    {
        DoCastSelf(SPELL_REMOVE_MUSHROOM_POWER, true);
        _JustDied();
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_ROOTS:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true, -SPELL_ENTANGLING_ROOTS))
                    DoCast(target, SPELL_ENTANGLING_ROOTS);
                events.Repeat(10s, 15s);
                break;
            case EVENT_BASH:
                DoCastVictim(SPELL_BASH);
                events.Repeat(7s, 12s);
                break;
            case EVENT_VOLLEY:
                DoCastSelf(SPELL_VENOM_BOLT_VOLLEY);
                events.Repeat(18s, 22s);
                break;
            case EVENT_SPAWN:
                for (auto pos : MushroomPositions)
                    SpawnMushroom(pos);
                break;
            case EVENT_RESPAWN:
                while (!_mushroomsDeque.empty())
                {
                    SpawnMushroom(_mushroomsDeque.front());
                    _mushroomsDeque.pop_front();
                }
                events.ScheduleEvent(EVENT_MINI, 3s, 10s);
                events.Repeat(40s, 60s);
                break;
            case EVENT_MINI:
                DoCastSelf(SPELL_MINI);
                break;
            default:
                break;
        }
    }

    private:
        std::deque<Position> _mushroomsDeque;
};

struct npc_amanitar_mushroomsAI : public ScriptedAI
{
    npc_amanitar_mushroomsAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetAttackable(false);
        _events.Reset();
        me->SetReactState(REACT_PASSIVE);
        SetCombatMovement(false);
        DoCastSelf(SPELL_PUTRID_MUSHROOM);
        _events.ScheduleEvent(EVENT_GROW, 800ms);
    }

    void EnterEvadeMode() override { }

    void UpdateAI(uint32 diff) override
    {
        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_GROW:
                    DoCastSelf(SPELL_GROW);
                    me->SetAttackable(true);
                    break;
                case EVENT_SHRINK:
                    DoCastSelf(SPELL_SHRINK);
                    me->DespawnOrUnsummon(4s);
                    break;
                default:
                    break;
            }
        }
    }

    protected:
        EventMap _events;
};

struct npc_amanitar_healthy_mushroomAI : public npc_amanitar_mushroomsAI
{
    npc_amanitar_healthy_mushroomAI(Creature* creature) : npc_amanitar_mushroomsAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_POWER_MUSHROOM_VISUAL_AURA);
        npc_amanitar_mushroomsAI::Reset();
    }

    // healthy
    void JustDied(Unit* killer) override
    {
        if (!killer)
            return;

        if (!killer->HasAura(SPELL_MINI))
            DoCastSelf(SPELL_POTENT_FUNGUS, true);
        else
            killer->RemoveAurasDueToSpell(SPELL_MINI);
    }
};

struct npc_amanitar_poisonous_mushroomAI : public npc_amanitar_mushroomsAI
{
    npc_amanitar_poisonous_mushroomAI(Creature* creature) : npc_amanitar_mushroomsAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_POISONOUS_MUSHROOM_VISUAL_AURA);
        _active = false;
        npc_amanitar_mushroomsAI::Reset();
    }

    void UpdateAI(uint32 diff) override
    {
        npc_amanitar_mushroomsAI::UpdateAI(diff);

        if (_active)
            return;

        if (Player* target = SelectTargetFromPlayerList(2.0f))
        {
            _active = true;

            target->RemoveAurasDueToSpell(SPELL_POTENT_FUNGUS);
            DoCastSelf(SPELL_POISONOUS_MUSHROOM_POISON_CLOUD, true);

            me->SetAttackable(false);
            _events.ScheduleEvent(EVENT_SHRINK, 1s);
        }
    }

    private:
        bool _active;
};

class spell_amanitar_remove_mushroom_power_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_amanitar_remove_mushroom_power_SpellScript);

    void HandleDummyEffect(SpellEffIndex /*eff*/)
    {
        if (Unit* target = GetHitUnit())
        {
            target->RemoveAurasDueToSpell(SPELL_POTENT_FUNGUS);
            target->RemoveAurasDueToSpell(SPELL_MINI);
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_amanitar_remove_mushroom_power_SpellScript::HandleDummyEffect, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};


void AddSC_boss_amanitar()
{
    new CreatureAILoader<boss_amanitarAI>("boss_amanitar");
    new CreatureAILoader<npc_amanitar_healthy_mushroomAI>("npc_amanitar_healthy_mushroom");
    new CreatureAILoader<npc_amanitar_poisonous_mushroomAI>("npc_amanitar_poisonous_mushroom");
    new SpellScriptLoaderEx<spell_amanitar_remove_mushroom_power_SpellScript>("spell_amanitar_remove_mushroom_power");
}
