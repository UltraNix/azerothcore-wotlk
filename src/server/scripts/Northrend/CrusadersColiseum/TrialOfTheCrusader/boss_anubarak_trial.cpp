#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "trial_of_the_crusader.h"
#include "SpellScript.h"
#include "PassiveAI.h"
#include "Player.h"
#include "SpellAuraEffects.h"

enum AnubTexts
{
    SAY_INTRO,
    SAY_AGGRO,
    EMOTE_SUBMERGE,
    EMOTE_BURROWER,
    SAY_EMERGE,
    SAY_LEECHING_SWARM,
    EMOTE_LEECHING_SWARM,
    SAY_KILL_PLAYER,
    SAY_DEATH,

    EMOTE_SPIKE = 0,
};

enum AnubNPCs
{
    NPC_FROST_SPHERE = 34606,
    NPC_BURROW = 34862,
    NPC_BURROWER = 34607,
    NPC_SCARAB = 34605,
    NPC_SPIKE = 34660,
};

const Position AnubLocs[] =
{
    // scarab's beginning pos
    { 722.65f, 135.41f, 142.16f, M_PI },

    // churning ground spawns
    { 694.886353f, 102.484665f, 142.119614f, 0 },
    { 731.987244f, 83.3824690f, 142.119614f, 0 },
    { 694.500671f, 185.363968f, 142.117905f, 0 },
    { 740.184509f, 193.443390f, 142.117584f, 0 },

    // sphere spawns
    { 786.6439f, 108.2498f, 155.6701f, 0 },
    { 806.8429f, 150.5902f, 155.6701f, 0 },
    { 759.1386f, 163.9654f, 155.6701f, 0 },
    { 744.3701f, 119.5211f, 155.6701f, 0 },
    { 710.0211f, 120.8152f, 155.6701f, 0 },
    { 706.6383f, 161.5266f, 155.6701f, 0 },
};

class HideNpcEvent : public BasicEvent
{
public:
    HideNpcEvent(Creature& owner) : _owner(owner) { }

    bool Execute(uint64 /*eventTime*/, uint32 /*updateTime*/)
    {
        _owner.SetVisible(false);
        return true;
    }

private:
    Creature& _owner;
};

enum AnubSpells
{
    // Anub'arak
    SPELL_SUBMERGE = 65981,
    SPELL_EMERGE = 65982,
    SPELL_BERSERK = 26662,

    SPELL_FREEZING_SLASH = 66012,
    SPELL_PENETRATING_COLD = 66013,
    SPELL_SUMMON_SCARAB = 66339,
    SPELL_SUMMON_BURROWER = 66332,
    SPELL_LEECHING_SWARM = 66118,

    // Anub'arak Pursue
    SPELL_MARK = 67574,
    SPELL_SUMMON_SPIKE = 66169,
    SPELL_SPIKE_SPEED1 = 65920,
    SPELL_SPIKE_TRAIL = 65921,
    SPELL_SPIKE_SPEED2 = 65922,
    SPELL_SPIKE_SPEED3 = 65923,
    SPELL_SPIKE_FAIL = 66181,
    SPELL_SPIKE_TELE = 66170,
    SPELL_IMPALE = 65919,

    // Scarab
    SPELL_DETERMINATION = 66092,
    SPELL_ACID_MANDIBLE = 65774,

    // Burrow
    SPELL_CHURNING_GROUND = 66969,

    // Frost Sphere
    SPELL_FROST_SPHERE = 67539,
    SPELL_PERMAFROST = 66193,
    SPELL_PERMAFROST_VISUAL = 65882,

    // Burrower
    SPELL_SPIDER_FRENZY = 66128,
    SPELL_EXPOSE_WEAKNESS = 67720,
    SPELL_SHADOW_STRIKE = 66134,
    SPELL_SUBMERGE_EFFECT = 53421,
    SPELL_EMERGE_EFFECT = 66947,
};

enum AnubEvents
{
    EVENT_RESPAWN_SPHERE = 1,
    EVENT_ENRAGE,
    EVENT_SPELL_FREEZING_SLASH,
    EVENT_SPELL_PENETRATING_COLD,
    EVENT_SUMMON_NERUBIAN,
    EVENT_SUBMERGE,
    EVENT_EMERGE,
    EVENT_EMERGE_2,
    EVENT_SPELL_SUMMON_SPIKE,
    EVENT_SPELL_SHADOW_STRIKE,
    EVENT_SUMMON_SCARAB,
    EVENT_SHADOW_STRIKE
};

#define SUBMERGE_INTERVAL 80000
#define EMERGE_INTERVAL 60000

struct boss_anubarak_trialAI : public BossAI
{
    boss_anubarak_trialAI(Creature* creature) : BossAI(creature, TYPE_ANUBARAK)
    {
        events.Reset();
        _intro = false;
        _phase3 = false;
        me->ApplySpellImmune(0, IMMUNITY_ID, RAID_MODE(66193, 67855, 67856, 67857), true);
        me->m_SightDistance = 90.0f; // for MoveInLineOfSight distance
    }

    void Reset() override
    {
        _Reset();
        me->SetStandState(UNIT_STAND_STATE_SUBMERGED);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        summons.DespawnAll();
        for (uint8 i = 0; i<10; ++i)
        {
            float angle = Position::RandomOrientation();
            float dist = frand(0.0f, 40.0f);
            if (Creature* c = me->SummonCreature(NPC_SCARAB, AnubLocs[0].GetPositionX() + cos(angle)*dist, AnubLocs[0].GetPositionY() + sin(angle)*dist, AnubLocs[0].GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 5000))
            {
                c->setFaction(31);
                c->GetMotionMaster()->MoveRandom(15.0f);
            }
        }
    }

    void DoAction(int32 param) override
    {
        switch (param)
        {
        case -1:
            summons.DespawnAll();
            break;
        }
    }

    void EnterCombat(Unit* /*who*/) override
    {
        _EnterCombat();
        events.Reset();
        events.RescheduleEvent(EVENT_ENRAGE, 600000);

        if (IsHeroic())
            events.RescheduleEvent(EVENT_SHADOW_STRIKE, 30000);

        events.RescheduleEvent(EVENT_SPELL_FREEZING_SLASH, urand(7000, 15000));
        events.RescheduleEvent(EVENT_SPELL_PENETRATING_COLD, urand(15000, 20000));
        events.RescheduleEvent(EVENT_SUMMON_NERUBIAN, urand(8000, 10000));
        events.RescheduleEvent(EVENT_SUBMERGE, SUBMERGE_INTERVAL);

        if (!IsHeroic())
            events.RescheduleEvent(EVENT_RESPAWN_SPHERE, 4000);

        for (std::list<uint64>::iterator itr = summons.begin(); itr != summons.end(); ++itr)
            if (Creature* c = instance->instance->GetCreature(*itr))
            {
                c->GetMotionMaster()->MoveIdle();
                c->StopMoving();
                c->CastSpell(c, SPELL_SUBMERGE, false);
                if (c->IsAIEnabled)
                    c->AI()->DoAction(1);
            }

        summons.clear();

        for (uint8 i = 0; i<4; ++i)
            if (Creature* c = me->SummonCreature(NPC_BURROW, AnubLocs[i + 1]))
                _burrowGUID[i] = c->GetGUID();
        for (uint8 i = 0; i<6; ++i)
            if (Creature* c = me->SummonCreature(NPC_FROST_SPHERE, AnubLocs[i + 5]))
                _sphereGUID[i] = c->GetGUID();

        Talk(SAY_AGGRO);
        instance->SetData(TYPE_ANUBARAK, IN_PROGRESS);
    }

    bool CanSeeAlways(WorldObject const* /*obj*/) override
    {
        //! If phase 3 is active meaning leeching swarm was activated
        //! lets set canSeeAlways to true so players do not drop auras with invisibility auras
        //! due to how visibility systems work on SunwellCore
        return _phase3;
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        if (!_phase3 && HealthBelowPct(30) && !me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE) && !me->HasAura(SPELL_SUBMERGE) && !me->HasAura(SPELL_EMERGE))
        {
            _phase3 = true;
            events.CancelEvent(EVENT_SUBMERGE);
            events.CancelEvent(EVENT_EMERGE);
            events.CancelEvent(EVENT_EMERGE_2);

            if (!IsHeroic())
                events.CancelEvent(EVENT_SUMMON_NERUBIAN);

            DoCastAOE(SPELL_LEECHING_SWARM);
            Talk(EMOTE_LEECHING_SWARM);
            Talk(SAY_LEECHING_SWARM);
            return;
        }

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SHADOW_STRIKE:
            {
                std::list<Creature*> addList;
                me->GetCreatureListWithEntryInGrid(addList, NPC_BURROWER, 500.0f);
                if (!addList.empty())
                    for (auto itr : addList)
                        if (auto target = SelectTarget(SELECT_TARGET_RANDOM, 0, 50.0f, true))
                            if (!itr->HasAura(SPELL_SUBMERGE))
                                itr->CastSpell(target, SPELL_SHADOW_STRIKE);
                events.Repeat(30000);
                break;
            }
            case EVENT_ENRAGE:
                DoCastSelf(SPELL_BERSERK, true);
                break;
            case EVENT_RESPAWN_SPHERE:
            {
                uint8 StartAt = urand(0, 5);
                uint8 i = StartAt;
                do
                {
                    if (Creature* c = ObjectAccessor::GetCreature(*me, _sphereGUID[i]))
                        if (!c->HasAura(SPELL_FROST_SPHERE))
                        {
                            if (Creature* c = me->SummonCreature(NPC_FROST_SPHERE, AnubLocs[i + 5]))
                                _sphereGUID[i] = c->GetGUID();
                            break;
                        }
                    i = (i + 1) % 6;
                } while (i != StartAt);
                events.Repeat(4000);
                break;
            }
            case EVENT_SPELL_FREEZING_SLASH:
                DoCastVictim(SPELL_FREEZING_SLASH);
                events.Repeat(urand(15000, 20000));
                break;
            case EVENT_SPELL_PENETRATING_COLD:
                me->CastCustomSpell(SPELL_PENETRATING_COLD, SPELLVALUE_MAX_TARGETS, RAID_MODE(2, 5, 2, 5));
                events.Repeat(20000);
                break;
            case EVENT_SUMMON_NERUBIAN:
                me->CastCustomSpell(SPELL_SUMMON_BURROWER, SPELLVALUE_MAX_TARGETS, RAID_MODE(1, 2, 2, 4));
                events.Repeat(45000);
                break;
            case EVENT_SUBMERGE:
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                bool berserk = me->HasAura(SPELL_BERSERK);
                me->RemoveAllAuras();
                if (berserk)
                    DoCastSelf(SPELL_BERSERK, true);
                Talk(EMOTE_SUBMERGE);
                Talk(EMOTE_BURROWER);
                DoCastSelf(SPELL_SUBMERGE);
                events.CancelEvent(EVENT_SUMMON_NERUBIAN);
                events.CancelEvent(EVENT_SPELL_FREEZING_SLASH);
                events.CancelEvent(EVENT_SPELL_PENETRATING_COLD);
                events.CancelEvent(EVENT_SHADOW_STRIKE);
                events.RescheduleEvent(EVENT_EMERGE, EMERGE_INTERVAL);
                events.RescheduleEvent(EVENT_SPELL_SUMMON_SPIKE, 2500);
                events.RescheduleEvent(EVENT_SUMMON_SCARAB, 3000);
                break;
            }
            case EVENT_SUMMON_SCARAB:
                if (Creature* c = ObjectAccessor::GetCreature(*me, _burrowGUID[urand(0, 3)]))
                    DoCast(c, SPELL_SUMMON_SCARAB, true);
                events.Repeat(4000);
                break;
            case EVENT_EMERGE:
                DoCastSelf(SPELL_SPIKE_TELE, true);
                summons.DespawnEntry(NPC_SPIKE);
                events.CancelEvent(EVENT_SUMMON_SCARAB);
                events.RescheduleEvent(EVENT_EMERGE_2, 2000);
                break;
            case EVENT_EMERGE_2:
                Talk(SAY_EMERGE);
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->setAttackTimer(BASE_ATTACK, 3000);
                me->RemoveAura(SPELL_SUBMERGE);
                DoCastSelf(SPELL_EMERGE);

                if (IsHeroic())
                    events.RescheduleEvent(EVENT_SHADOW_STRIKE, 30000);
                events.RescheduleEvent(EVENT_SUMMON_NERUBIAN, urand(8000, 10000));
                events.RescheduleEvent(EVENT_SPELL_FREEZING_SLASH, urand(7000, 15000));
                events.RescheduleEvent(EVENT_SPELL_PENETRATING_COLD, urand(15000, 20000));
                events.RescheduleEvent(EVENT_SUBMERGE, SUBMERGE_INTERVAL);
                break;
            case EVENT_SPELL_SUMMON_SPIKE:
                DoCastSelf(SPELL_SUMMON_SPIKE, true);
                break;
            default:
                break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        if (!me->HasUnitState(UNIT_STATE_CASTING))
            DoMeleeAttackIfReady();
    }

    void JustSummoned(Creature* summon) override
    {
        if (!summon)
            return;

        summons.Summon(summon);
    }

    void JustDied(Unit* /*pKiller*/)
    {
        _JustDied();
        Talk(SAY_DEATH);
        instance->SetData(TYPE_ANUBARAK, DONE);

        instance->DoRemoveAurasDueToSpellOnPlayers(RAID_MODE(66013, 67700, 68509, 68510));

        if (!instance)
            return;

        Player* plr = nullptr;
        if (!instance->instance->GetPlayers().isEmpty())
        {
            for (auto itr = instance->instance->GetPlayers().begin(); itr != instance->instance->GetPlayers().end(); ++itr)
            {
                if (!itr->GetSource()->IsGameMaster())
                {
                    plr = itr->GetSource();
                    break;
                }
            }
        }

        if (!plr)
            return;

        // remove loot for the other faction (items are invisible for players, done in conditions), so corpse can be skinned
        for (std::vector<LootItem>::iterator itr = me->loot.items.begin(); itr != me->loot.items.end(); ++itr)
            if (ItemTemplate const *iProto = sObjectMgr->GetItemTemplate((*itr).itemid))
                if (((iProto->Flags2 & ITEM_FLAGS_EXTRA_HORDE_ONLY) && plr->GetTeamId() != TEAM_HORDE) || ((iProto->Flags2 & ITEM_FLAGS_EXTRA_ALLIANCE_ONLY) && plr->GetTeamId() != TEAM_ALLIANCE))
                {
                    (*itr).count = 0;
                    (*itr).is_looted = true;
                    --me->loot.unlootedCount;
                }
    }

    void KilledUnit(Unit* who) override
    {
        if (who->GetTypeId() == TYPEID_PLAYER)
            Talk(SAY_KILL_PLAYER);
    }

    void EnterEvadeMode() override
    {
        events.Reset();
        summons.DespawnAll();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        instance->SetData(TYPE_FAILED, 1);
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (who->GetTypeId() != TYPEID_PLAYER || me->GetExactDistSq(who) > 6400.0f) // 80yd*80yd
            return;

        if (me->getStandState() != UNIT_STAND_STATE_STAND)
            me->SetStandState(UNIT_STAND_STATE_STAND);

        if (!_intro)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            if (!me->IsInCombat())
                Talk(SAY_INTRO);
            _intro = true;
        }
        ScriptedAI::MoveInLineOfSight(who);
    }

    bool CanAIAttack(const Unit* target) const override
    {
        return target->GetEntry() != NPC_FROST_SPHERE;
    }

private:
    bool _intro;
    bool _phase3;
    uint64 _sphereGUID[6];
    uint64 _burrowGUID[4];
};

struct npc_swarm_scarabAI : public ScriptedAI
{
    npc_swarm_scarabAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    int32 determinationTimer;
    int32 despawnTimer;

    void DoAction(int32 param) override
    {
        if (param == 1)
            despawnTimer = 2000;
    }

    void Reset() override
    {
        me->SetCorpseDelay(10 * 60);
        DoCastSelf(SPELL_ACID_MANDIBLE, true);
        determinationTimer = urand(10000, 50000);
        despawnTimer = 0;
        if (me->getFaction() == 16) // hostile - it's phase 2
            if (Unit* target = me->SelectNearestTarget(250.0f))
            {
                AttackStart(target);
                DoZoneInCombat();
                if (Unit* t = SelectTarget(SELECT_TARGET_RANDOM, 0, 250.0f, true))
                {
                    me->AddThreat(t, 20000.0f);
                    AttackStart(t);
                }
            }
    }

    void EnterCombat(Unit* /*who*/) override
    {
        Creature* anubarak = me->FindNearestCreature(34564, 250.0f);

        if (!anubarak)
            return;

        if (anubarak->IsInCombat())
            DoZoneInCombat();
        else
        {
            me->GetMotionMaster()->MoveIdle();
            me->StopMoving();
            DoCastSelf(SPELL_SUBMERGE);
            DoAction(1);
        }
    }

    void UpdateAI(uint32 diff)
    {
        if (despawnTimer)
        {
            if (despawnTimer <= (int32)diff)
            {
                despawnTimer = 0;
                me->DisappearAndDie();
            }
            else
                despawnTimer -= diff;

            return;
        }

        if (!UpdateVictim())
            return;

        if (determinationTimer <= (int32)diff)
        {
            DoCastSelf(SPELL_DETERMINATION);
            determinationTimer = urand(20000, 60000);
        }
        else
            determinationTimer -= diff;

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* killer) override
    {
        Creature* anubarak = me->FindNearestCreature(34564, 250.0f);

        if (!anubarak)
            return;

        if (anubarak->IsInCombat())
            DoCastSelf(RAID_MODE(SPELL_TRAITOR_KING_10, SPELL_TRAITOR_KING_25, SPELL_TRAITOR_KING_10, SPELL_TRAITOR_KING_25), true);
        me->m_Events.AddEvent(new HideNpcEvent(*me), me->m_Events.CalculateTime(5000));
    }

    bool CanAIAttack(const Unit* target) const override
    {
        return target->GetEntry() != NPC_FROST_SPHERE && !me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
    }
};

struct npc_frost_sphereAI : public NullCreatureAI
{
    npc_frost_sphereAI(Creature* creature) : NullCreatureAI(creature)
    {
        uint32 ID = 0;
        if (me->GetMap())
            switch (me->GetMap()->GetDifficulty())
            {
            case RAID_DIFFICULTY_10MAN_NORMAL: ID = 66118; break;
            case RAID_DIFFICULTY_25MAN_NORMAL: ID = 67630; break;
            case RAID_DIFFICULTY_10MAN_HEROIC: ID = 68646; break;
            case RAID_DIFFICULTY_25MAN_HEROIC: ID = 68647; break;
            }

        if (ID)
            me->ApplySpellImmune(0, IMMUNITY_ID, ID, true);

        std::vector<uint32> spells =
        {
            53195, // starfall rank 4
            53194, // starfall rank 3
            53191, // starfall rank 2
            50294, // starfall rank 1
            51429, // pestilence rank 5
            51428, // pestilence rank 4
            51427, // pestilence rank 3
            51426, // pestilence rank 2
            50842, // pestilence rank 1
            49271, // chain lightning rank 8 
            49270, // chain lightning rank 7
        };

        for (auto spellId : spells)
            me->ApplySpellImmune(0, IMMUNITY_ID, spellId, true);

        _permafrostTimer = 0;
        me->CastSpell(me, SPELL_FROST_SPHERE, true);
        me->GetMotionMaster()->MoveRandom(20.0f);
        me->SetCorpseDelay(15 * 60 * 1000);
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType det, SpellSchoolMask) override
    {
        if (det != DIRECT_DAMAGE && det != SPELL_DIRECT_DAMAGE)
        {
            damage = 0;
            return;
        }

        if (me->GetHealth() <= damage)
        {
            damage = 0;
            if (!me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE))
            {
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                me->GetMotionMaster()->MoveIdle();
                me->GetMotionMaster()->MoveCharge(me->GetPositionX(), me->GetPositionY(), 143.0f, 20.0f);
                _permafrostTimer = 1500;
            }
        }
    }

    void SpellHit(Unit* caster, const SpellInfo* spell) override
    {
        if (spell->Id == SPELL_SPIKE_FAIL)
        {
            me->RemoveAllAuras();
            me->DespawnOrUnsummon(1500);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (_permafrostTimer)
        {
            if (_permafrostTimer <= diff)
            {
                _permafrostTimer = 0;
                me->RemoveAurasDueToSpell(SPELL_FROST_SPHERE);
                me->SetDisplayId(11686);
                me->SetObjectScale(2.0f);
                me->UpdatePosition(me->GetPositionX(), me->GetPositionY(), 142.7f, me->GetOrientation(), false);
                me->SetFacingTo(me->GetOrientation());
                DoCastSelf(SPELL_PERMAFROST_VISUAL, true);
                DoCastSelf(SPELL_PERMAFROST, true);
                me->SetCanFly(false);
            }
            else
                _permafrostTimer -= diff;
        }
    }

private:
    uint32 _permafrostTimer;
};

struct npc_nerubian_burrowerAI : public ScriptedAI
{
    npc_nerubian_burrowerAI(Creature* creature) : ScriptedAI(creature)
    {
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SHACKLE, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_KNOCKOUT, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
        me->ApplySpellImmune(0, IMMUNITY_ID, 33786, true); // cyclone
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
        me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK_DEST, true);
        me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_DECREASE_SPEED, true);

        // I am summoned by another npc (SPELL_EFFECT_FORCE_CAST), inform Anub'arak
        if (InstanceScript* pInstance = me->GetInstanceScript())
            if (uint64 guid = pInstance->GetData64(TYPE_ANUBARAK))
                if (Creature* anub = pInstance->instance->GetCreature(guid))
                    CAST_AI(boss_anubarak_trialAI, anub->AI())->JustSummoned(me);
    }

    void Reset() override
    {
        me->SetCorpseDelay(10 * 60);
        DoCastSelf(SPELL_EXPOSE_WEAKNESS, true);
        DoCastSelf(SPELL_SPIDER_FRENZY, true);
        _events.Reset();
        _events.RescheduleEvent(EVENT_SUBMERGE, 30000);
        if (Unit* target = me->SelectNearestTarget(250.0f))
        {
            AttackStart(target);
            DoZoneInCombat();
        }
    }

    void SpellHitTarget(Unit* target, const SpellInfo* spell)
    {
        if (!target || !spell)
            return;

        if (spell->Id == SPELL_SHADOW_STRIKE)
        {
            float o = target->GetOrientation();
            if (o >= M_PI)
                o -= M_PI;
            else
                o += M_PI;

            me->NearTeleportTo(target->GetPositionX() + cos(o)*5.0f, target->GetPositionY() + sin(o)*5.0f, target->GetPositionZ() + 0.6f, target->GetOrientation());
            AttackStart(target);
            me->GetMotionMaster()->MoveChase(target);
            _events.DelayEvents(3000);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case EVENT_SUBMERGE:
                if (HealthBelowPct(80) && !me->HasAura(RAID_MODE(66193, 67855, 67856, 67857))) // not having permafrost - allow submerge
                {
                    me->GetMotionMaster()->MoveIdle();
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->RemoveAllAuras();
                    DoCastSelf(SPELL_EXPOSE_WEAKNESS, true);
                    DoCastSelf(SPELL_SPIDER_FRENZY, true);
                    DoCastSelf(SPELL_SUBMERGE);
                    _events.DelayEvents(15000);
                    _events.RescheduleEvent(EVENT_EMERGE, 15000);
                }
                else
                    _events.Repeat(3000);
                break;
            case EVENT_EMERGE:
                me->SetHealth(me->GetMaxHealth());
                me->GetMotionMaster()->MoveChase(me->GetVictim());
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                DoCastSelf(SPELL_EMERGE);
                me->RemoveAura(SPELL_SUBMERGE);
                _events.RescheduleEvent(EVENT_SUBMERGE, 30000);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* killer) override
    {
        me->m_Events.AddEvent(new HideNpcEvent(*me), me->m_Events.CalculateTime(5000));
    }

    bool CanAIAttack(const Unit* target) const override
    {
        return target->GetEntry() != NPC_FROST_SPHERE;
    }

private:
    EventMap _events;
};

struct npc_anubarak_spikeAI : public ScriptedAI
{
    npc_anubarak_spikeAI(Creature* creature) : ScriptedAI(creature)
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetCorpseDelay(0);
    }

    void DoAction(int32 param) override
    {
        if (param == -1)
        {
            if (Unit* target = ObjectAccessor::GetPlayer(*me, _targetGUID))
                target->RemoveAura(SPELL_MARK);
            _targetGUID = 0;
            me->RemoveAllAuras();
            me->GetMotionMaster()->MoveIdle();
            _events.Reset();
            _events.RescheduleEvent(3, 4000);
        }
    }

    void SelectNewTarget(bool next)
    {
        if (_targetGUID)
            if (Unit* target = ObjectAccessor::GetPlayer(*me, _targetGUID))
                target->RemoveAura(SPELL_MARK);
        _targetGUID = 0;
        if (!next)
        {
            _events.Reset();
            me->RemoveAllAuras();
        }
        DoZoneInCombat();
        DoResetThreat();
        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250.0f, true))
        {
            if (!next)
            {
                DoCastSelf(SPELL_SPIKE_SPEED1, true);
                DoCastSelf(SPELL_SPIKE_TRAIL, true);
                _events.RescheduleEvent(1, 7000);
            }
            _targetGUID = target->GetGUID();
            DoCast(target, SPELL_MARK, true);
            Talk(EMOTE_SPIKE, target);
            AttackStart(target);
            me->GetMotionMaster()->MoveChase(target);
        }
    }

    void Reset() override
    {
        SelectNewTarget(false);
    }

    bool IsValidTargetForSpike(Unit* target) const
    {
        std::vector<uint32> spellIds =
        {
            45438, // ice block
            642, // divine shield
            1856, // vanish
            5384, // feign death
            19752, // divine intervetion
        };

        for (auto spellId : spellIds)
            if (target->HasAura(spellId))
                return false;

        return true;
    }

    void UpdateAI(uint32 diff) override
    {
        if (_targetGUID)
        {
            Unit* target = ObjectAccessor::GetPlayer(*me, _targetGUID);
            if (!target || !target->HasAura(SPELL_MARK) || !IsValidTargetForSpike(target) || !me->IsValidAttackTarget(target) || me->GetMotionMaster()->GetCurrentMovementGeneratorType() != CHASE_MOTION_TYPE || !me->HasUnitState(UNIT_STATE_CHASE_MOVE))
            {
                SelectNewTarget(true);
                return;
            }
        }

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
            case 1:
                DoCastSelf(SPELL_SPIKE_SPEED2, true);
                _events.RescheduleEvent(2, 7000);
                break;
            case 2:
                DoCastSelf(SPELL_SPIKE_SPEED3, true);
                break;
            case 3:
                Reset();
                break;
            default:
                break;
            }
        }
    }

    void DamageTaken(Unit*, uint32& damage, DamageEffectType, SpellSchoolMask) override
    {
        damage = 0;
    }

private:
    EventMap _events;
    uint64 _targetGUID;
};

class spell_pursuing_spikesAuraScript : public AuraScript
{
    PrepareAuraScript(spell_pursuing_spikesAuraScript)

        void HandleEffectPeriodic(AuraEffect const * aurEff)
    {
        if (Unit* target = GetTarget())
        {
            if (Creature* c = target->FindNearestCreature(NPC_FROST_SPHERE, 8.0f, true))
            {
                target->UpdatePosition(*c, false);
                target->CastCustomSpell(SPELL_SPIKE_FAIL, SPELLVALUE_MAX_TARGETS, 1);
                if (target->GetTypeId() == TYPEID_UNIT)
                    target->ToCreature()->AI()->DoAction(-1);
                Remove();
                return;
            }
            target->CastSpell((Unit*)nullptr, SPELL_IMPALE, true);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_pursuing_spikesAuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

// 66118 Leeching Swarm
enum eLeechingSwarmSpells
{
    SPELL_LEECHING_SWARM_DMG = 66240,
    SPELL_LEECHING_SWARM_HEAL = 66125,
};

class spell_gen_leeching_swarm_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_gen_leeching_swarm_AuraScript)

        bool Validate(SpellInfo const* /*spellEntry*/) override
    {
        return ValidateSpellInfo({ SPELL_LEECHING_SWARM_DMG,SPELL_LEECHING_SWARM_HEAL });
    }

    void HandleEffectPeriodic(AuraEffect const* aurEff)
    {
        if (Unit* caster = GetCaster())
        {
            if (!sSpellMgr->GetSpellInfo(SPELL_LEECHING_SWARM_DMG))
                return;

            if (!GetTarget()->IsPlayer())
                return;

            int32 multiplier = 68;
            if (auto caster = GetCaster())
            {
                if (auto map = caster->GetMap())
                {
                    if (map->Is25ManRaid() && map->IsHeroic()) // 25 hc
                        multiplier = 250;
                    else if (map->Is25ManRaid() && !map->IsHeroic()) // 25 n
                        multiplier = 155;
                    else if (!map->Is25ManRaid() && map->IsHeroic()) // 10 hc
                        multiplier = 92;
                    else if (!map->Is25ManRaid() && !map->IsHeroic()) // 10 n
                        multiplier = 68;
                }
            }

            int32 lifeLeeched = GetTarget()->CountPctFromCurHealth(aurEff->GetAmount());
            if (lifeLeeched < 250)
                lifeLeeched = 250;

            // Damage
            caster->CastCustomSpell(GetTarget(), SPELL_LEECHING_SWARM_DMG, &lifeLeeched, 0, 0, true);

            // Heal
            uint32 resist = 0;
            uint32 absorb = 0;
            GetTarget()->CalcAbsorbResist(caster, GetTarget(), sSpellMgr->GetSpellInfo(SPELL_LEECHING_SWARM_DMG)->GetSchoolMask(), DIRECT_DAMAGE, lifeLeeched, &absorb, &resist, sSpellMgr->GetSpellInfo(SPELL_LEECHING_SWARM_DMG));
            if (Unit* target = GetTarget())
            {
                if (!target->IsImmunedToDamage(sSpellMgr->GetSpellInfo(SPELL_LEECHING_SWARM_DMG)))
                {
                    lifeLeeched -= resist;
                    int32 value = lifeLeeched * multiplier / 100.0f;
                    caster->CastCustomSpell(caster, SPELL_LEECHING_SWARM_HEAL, &value, 0, 0, true);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_gen_leeching_swarm_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
    }
};

class spell_anubarak_permafrost_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_anubarak_permafrost_SpellScript)

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if(Trinity::UnitAuraCheck(true, 1044)); // hand of freedom
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_anubarak_permafrost_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_DEST_AREA_ENTRY);
    }
};

void AddSC_boss_anubarak_trial()
{
    new CreatureAILoader<boss_anubarak_trialAI>("boss_anubarak_trial");
    new CreatureAILoader<npc_swarm_scarabAI>("npc_swarm_scarab");
    new CreatureAILoader<npc_frost_sphereAI>("npc_frost_sphere");
    new CreatureAILoader<npc_nerubian_burrowerAI>("npc_nerubian_burrower");
    new CreatureAILoader<npc_anubarak_spikeAI>("npc_anubarak_spike");
    new AuraScriptLoaderEx<spell_pursuing_spikesAuraScript>("spell_pursuing_spikes");
    new AuraScriptLoaderEx<spell_gen_leeching_swarm_AuraScript>("spell_gen_leeching_swarm");
    new SpellScriptLoaderEx<spell_anubarak_permafrost_SpellScript>("spell_anubarak_permafrost");
}