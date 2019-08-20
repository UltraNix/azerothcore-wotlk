#include "hellforge.hpp"

#include "MoveSplineInit.h"

enum BossFiveEvents
{
    EVENT_INTRO_STEP_ONE                    = 1,
    EVENT_INTRO_MOVE_TO_EDGE,
    EVENT_FINISH_INTRO,
    EVENT_SUMMON_BURNER,
    EVENT_SUMMON_FEARER,
    EVENT_SUMMON_BIG_ADD,
    EVENT_SUMMON_BATS,
    EVENT_SHADOW_WORD_DEATH,
    EVENT_SONIC_SCREECH,
    EVENT_BAT_PHASE,
    EVENT_MOVE_TO_SPLIT_START,
    EVENT_MOVE_TO_END_SPLIT,
    EVENT_MOVE_BACK_TO_EDGE,
    EVENT_BAT_SHADOW_BOLT,
    EVENT_END_BAT_PHASE,
    EVENT_SHADOW_BOLT,
    EVENT_BEGIN_LAST_PHASE_SCENE,
    EVENT_GRIP_WANDERER,
    EVENT_MOVE_WANDERER,
    EVENT_END_LAST_PHASE_SCENE
};

enum BossFiveSpells
{
    SPELL_BOSS_FIVE_SHADOW_PRISON           = 40647,
    SPELL_BOSS_FIVE_SHADOW_WORD             = 56920,
    SPELL_BOSS_FIVE_BLOODTHRIST             = 57792,
    SPELL_BOSS_FIVE_SONIC_SCREECH           = 64688,
    SPELL_BOSS_FIVE_PARALYZE                = 43437,
    SPELL_BOSS_FIVE_TRANSFORM_VIS           = 16052,
    SPELL_BOSS_FIVE_SWARMING_SHADOW         = 71264,
    SPELL_BOSS_FIVE_UNHOLY_FRENZY           = 69052,
    SPELL_BOSS_FIVE_SHADOW_BOLT             = 40185,
    SPELL_BOSS_FIVE_FOG_VISUAL              = 63096,
    SPELL_BOSS_FIVE_SARONITE_BARRIER        = 63364,
    SPELL_BOSS_FIVE_VALKYR_QUICKNESS        = 67318,
    SPELL_BOSS_FIVE_SOUL_FLAME              = 23272,
    SPELL_BOSS_FIVE_MANA_BURN_CHANNEL       = 24619,
    SPELL_BOSS_FIVE_FADE_OUT                = 5543,
    SPELL_BOSS_FIVE_WITHER                  = 22662,
    SPELL_BOSS_FIVE_HULK                    = 34159,
    SPELL_BOSS_FIVE_CLEAVE                  = 70361,
    SPELL_BOSS_FIVE_SHADOW_BOLT_BAT         = 30686,
    SPELL_BOSS_FIVE_SHADOWFORM_VISUAL       = 63359,
    SPELL_BOSS_FIVE_SHADOW_BREATH           = 59126,
    SPELL_BOSS_FIVE_ADD_HAMSTRING           = 31553,
    SPELL_BOSS_FIVE_VISUAL_LINK             = 72304,
};

enum BossFiveMisc
{
    POINT_MOVE_TO_WANDERER                  = 1,
    POINT_MOVE_TO_PLATFORM_EDGE,
    POINT_MOVE_OUTSIDE_PLATFORM,
    POINT_MOVE_TO_SPLIT,
    POINT_MOVE_TO_SPLIT_END,
    POINT_MOVE_BACK_TO_MIDDLE,
    POINT_MOVE_TO_KABOOM,
    DATA_FROSTY_WORGEN_KILLED,
    DISPLAY_ID_BOSS_FIVE_BAT                = 16053,
    GROUP_SWARMING_SHADOWS,
    GROUP_CANCELABLE
};

enum BossFiveCreatures
{
    NPC_BOSS_FIVE_BURNER                    = 250024,
    NPC_BOSS_FIVE_FEARER                    = 250025,
    NPC_BOSS_FIVE_BIG_ADD                   = 250026,
    NPC_BOSS_FIVE_BAT                       = 250027,
    NPC_BOSS_FIVE_SWARM_SPREADER            = 250028,
    NPC_BOSS_FIVE_FIERY_WORGEN              = 250029,
    NPC_BOSS_FIVE_WORGEN_MELEE_EXPLOSION    = 250030
};

enum BossFivePlatformFires
{
    GO_TO_PLATFORM_RIGHT                    = 0,
    GO_TO_PLATFORM_MIDDLE,
    GO_TO_PLATFORM_LEFT
};

enum BossFiveEventTypes
{
    BOSS_EVENT_TYPE_SUMMONS                 = 0x01,
    BOSS_EVENT_TYPE_SWD                     = 0x02,
    BOSS_EVENT_TYPE_SONIC_SCREECH           = 0x04,
    BOSS_EVENT_TYPE_BAT_PHASE               = 0x08,
};

enum BossFiveStatIDs
{
    BOSS_FIVE_STAT_ID_HEALTH                = 48,
    BOSS_FIVE_STAT_ID_MELEE_DAMAGE          = 49,
    BOSS_FIVE_STAT_ID_SHADOW_WORD           = 50,
    BOSS_FIVE_STAT_ID_SONIC_SCREECH         = 51,
    BOSS_FIVE_STAT_ID_SHADOW_BOLT           = 52,

    // add related stats
    BOSS_FIVE_ADD_BAT_HEALTH                = 53,
    BOSS_FIVE_ADD_BAT_SHADOW_BOLT           = 54,

    BOSS_FIVE_ADD_CRYSTAL_HEALTH            = 55,

    BOSS_FIVE_ADD_MINDMASTER_HEALTH         = 56,
    BOSS_FIVE_ADD_MINDMASTER_MANA           = 57,

    BOSS_FIVE_ADD_SLAUGHTER_HEALTH          = 58,
    BOSS_FIVE_ADD_SLAUGHTER_MELEE_DMG       = 59,

    BOSS_FIVE_ADD_WARLOCK_HEALTH            = 60,
    BOSS_FIVE_ADD_WARLOCK_MANA              = 61,

    BOSS_FIVE_ADD_MINDMASTER_WITHER_DAMAGE  = 62,
    BOSS_FIVE_ADD_WARLOCK_BURN_DAMAGE       = 63,

    BOSS_FIVE_ADD_SLAUGHTER_CLEAVE_DMG      = 64,
    BOSS_FIVE_ADD_SLAUGHTER_HAMSTRING_DMG   = 65,

    BOSS_FIVE_ADD_MINDMASTER_WITHER_DOT_DMG = 66,

    BOSS_FIVE_ADD_CASTER_MELEE_DAMAGE       = 67,
    BOSS_FIVE_ADD_WORGEN_HEALTH             = 78,
    BOSS_FIVE_ADD_WORGEN_MELEE_DMG          = 81,
    BOSS_FIVE_STAT_ID_SHADOW_BREATH         = 82,
    BOSS_FIVE_STAT_ID_FLAMES                = 83,
    BOSS_FIVE_STAT_ID_SHADOW_WORD_HEAL_RAT  = 84
};

Position const _wandererPosition{ 1025.720f, -228.156f, -61.860f, 3.90f };
Position const _platformEdgePosition{ 1037.869f, -266.781f, -61.789f, 5.441f };
Position const _batSpawnPosition{ 1083.411f, -287.672f, -58.01706f, 2.620f };
Position const _batLeftCorner{ 1031.193f, -305.195f, -56.38353f, 1.854f };
Position const _batRightCorner { 1076.448f, -257.247f, -57.91593f, 2.687f };
Position const _edgeOfPlatform{ 1058.910f, -287.596f, -58.16265f, 2.343f };
Position const _fieryWorgenSpawnPosition{ 1064.041f, -291.297f, -99.63377f, 2.389f };
Position const _fieryWorgenJumpPosition{ 1043.164f, -267.062f, -60.88081f, 2.355f };
constexpr uint16 MAX_AMOUNT_OF_BATS{ 2 };
constexpr uint32 ROOM_CORNERS_SIZE{ 4 };
const std::array<Position, ROOM_CORNERS_SIZE> _roomCorners
{
    {
        { 1012.332f, -198.454f, -61.78903f, 4.811f },
        { 969.3470f, -240.877f, -61.78918f, 6.176f },
        { 1012.308f, -287.577f, -61.78926f, 1.519f },
        { 1054.235f, -241.744f, -61.78926f, 3.047f }
    }
};

static const std::vector<Position> _splitPositions
{
    { 1065.839f, -259.900f, -56.23103f, 2.358f }, // right
    { 1046.421f, -276.695f, -56.23103f, 2.381f }, // middle
    { 1028.574f, -293.851f, -56.23103f, 2.319f }  // left
};

static const std::vector<Position> _splitEndPositions
{
    { 1006.126f, -199.004f, -57.63847f, 5.460f }, // right
    { 987.7640f, -215.670f, -57.21530f, 2.405f }, // middle
    { 972.0560f, -237.237f, -58.11316f, 2.397f }   // left
};

static const std::vector<Position> _swarmingOrbsPositions
{
    { 1054.552f, -241.736f, -57.06224f, 3.044f },
    { 1012.718f, -290.954f, -57.06224f, 1.645f },
    { 967.6260f, -241.021f, -57.06224f, 0.015f },
    { 1010.674f, -198.614f, -57.06224f, 4.755f }
};

struct boss_hellforge_five_AI : public BossAI
{
    boss_hellforge_five_AI(Creature* creature) : BossAI(creature, DATA_BOSS_FIVE)
    {
        _platformSplits = { GO_TO_PLATFORM_LEFT, GO_TO_PLATFORM_MIDDLE, GO_TO_PLATFORM_RIGHT };
        me->ApplySpellImmune(72635, IMMUNITY_ID, 72635, true); // swarming shadows
        _introDoneOnce = false;
    }

    void ScheduleCombatEvents(uint32 mask)
    {
        if (mask & BOSS_EVENT_TYPE_SUMMONS)
        {
            events.ScheduleEvent(EVENT_SUMMON_BURNER, 20s, 25s);
            events.ScheduleEvent(EVENT_SUMMON_FEARER, 20s, 25s);
            events.ScheduleEvent(EVENT_SUMMON_BIG_ADD, 40s, 45s);
            events.ScheduleEvent(EVENT_SUMMON_BATS, 30s, 35s);
        }

        if (mask & BOSS_EVENT_TYPE_SWD)
            events.ScheduleEvent(EVENT_SHADOW_WORD_DEATH, 15s, 25s);

        if (mask & BOSS_EVENT_TYPE_SONIC_SCREECH)
            events.ScheduleEvent(EVENT_SONIC_SCREECH, 45s);

        if (mask & BOSS_EVENT_TYPE_BAT_PHASE)
            events.ScheduleEvent(EVENT_BAT_PHASE, 90s);
    }

    void DelayNonBatEvents()
    {
        uint32 timeToScreech = events.GetTimeUntilEvent(EVENT_SONIC_SCREECH);
        events.RescheduleEvent(EVENT_SONIC_SCREECH, timeToScreech + 100000);
        uint32 timeToShadowWordDeath = events.GetTimeUntilEvent(EVENT_SHADOW_WORD_DEATH);
        events.RescheduleEvent(EVENT_SHADOW_WORD_DEATH, timeToShadowWordDeath + 100000);
    }

    void Reset() override
    {
        DoCastSelf(SPELL_BOSS_FIVE_SHADOWFORM_VISUAL);
        me->SetCanFly(false);
        me->SetDisableGravity(false);
        me->RestoreDisplayId();
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetAggressive();
        _introScene = false;
        _did30pct = false;
        _lastPhaseScene = false;
        _worgenGUID = 0;
        BossAI::Reset();
        scheduler.CancelAll();
        Trinity::Containers::RandomShuffle(_platformSplits);
        me->UpdateSpeed(MOVE_RUN);
        _fightTimer = 0;
        LoadBossStats();
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_FIVE_STAT_ID_HEALTH, BOSS_FIVE_STAT_ID_MELEE_DAMAGE, BOSS_FIVE_STAT_ID_SHADOW_WORD,
            BOSS_FIVE_STAT_ID_SONIC_SCREECH, BOSS_FIVE_STAT_ID_SHADOW_BOLT, BOSS_FIVE_STAT_ID_SHADOW_BREATH, BOSS_FIVE_STAT_ID_SHADOW_WORD_HEAL_RAT });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_FIVE_STAT_ID_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_FIVE_STAT_ID_MELEE_DAMAGE:
                {
                    uint32 minDamage = ref.second.StatValue * ref.second.StatVariance;
                    uint32 maxDamage = ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_FIVE_STAT_ID_SHADOW_WORD:
                {
                    _shadowWordPct = ref.second.StatVariance;
                    break;
                }
                case BOSS_FIVE_STAT_ID_SONIC_SCREECH:
                {
                    _sonicScreechDamage = ref.second.StatValue;
                    break;
                }
                case BOSS_FIVE_STAT_ID_SHADOW_BOLT:
                {
                    _shadowBoltDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                case BOSS_FIVE_STAT_ID_SHADOW_BREATH:
                {
                    _shadowbreathDamage = ref.second.StatValue;
                    break;
                }
                case BOSS_FIVE_STAT_ID_SHADOW_WORD_HEAL_RAT:
                {
                    _shadowWordHealRatio = ref.second.StatValue;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void SpellHitTarget(Unit* who, SpellInfo const* spellInfo) override
    {
        if (who->IsPlayer() && spellInfo->Id == SPELL_BOSS_FIVE_SONIC_SCREECH && !who->HasAura(SPELL_BOSS_FIVE_PARALYZE))
        {
            if (me->GetVictim() && me->GetVictim() != who)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT1, 0);
                who->CastCustomSpell(SPELL_BOSS_FIVE_PARALYZE, val, who, TRIGGERED_FULL_MASK, NullItemRef, (const AuraEffect*)nullptr, me->GetGUID());
                if (Aura* aura = who->GetAura(SPELL_BOSS_FIVE_PARALYZE))
                {
                    aura->SetMaxDuration(10000);
                    aura->RefreshDuration();
                }
            }
        }
    }

    void JustSummoned(Creature* creature) override
    {
        if (creature->GetEntry() == NPC_BOSS_FIVE_BIG_ADD || creature->GetEntry() == NPC_BOSS_FIVE_FEARER || creature->GetEntry() == NPC_BOSS_FIVE_BURNER)
            creature->AddAura(SPELL_BOSS_FIVE_SHADOWFORM_VISUAL, creature);

        summons.Summon(creature);
        if (creature->GetEntry() == NPC_BOSS_FIVE_FIERY_WORGEN || creature->GetEntry() == NPC_BOSS_FIVE_SWARM_SPREADER)
            return;

        creature->AI()->DoZoneInCombat(creature, 100.f);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_FROSTY_WORGEN_KILLED && value == DATA_FROSTY_WORGEN_KILLED)
        {
            for (auto && spellId : { SPELL_BOSS_FIVE_FOG_VISUAL, SPELL_BOSS_FIVE_SARONITE_BARRIER })
                me->RemoveAurasDueToSpell(spellId);
            DoCastAOE(SPELL_BOSS_FIVE_SHADOW_PRISON, true);
            me->AttackStop();
            me->SetPassive();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->GetMotionMaster()->MovePoint(POINT_MOVE_TO_KABOOM, me->GetHomePosition());
        }
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (me->HasUnitState(UNIT_STATE_UNATTACKABLE))
            return;

        if (me->GetVictim())
            return;

        Player* player = who->ToPlayer();
        if (!player)
            return;

        if (player->IsGameMaster())
            return;

        float distance = who->IsWalking() ? 5.f : 10.f;

        if (!me->IsWithinDistInMap(who, distance))
            return;

        _introScene = true;
        AttackStart(who);
    }

    void EnterCombat(Unit* who) override
    {
        if (!_EnterCombat())
            return;

        _fightTimer = getMSTime();
        if (_introDoneOnce)
            events.ScheduleEvent(EVENT_FINISH_INTRO, 1s);
        else if (Unit* champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
        {
            if (!champion->IsAIEnabled || champion->GetAI()->GetData(0) != STATE_GAUNTLET_DONE || !champion->IsAlive())
                events.ScheduleEvent(EVENT_FINISH_INTRO, 1s);
            else
            {
                DoCastAOE(SPELL_BOSS_FIVE_SHADOW_PRISON, true);
                events.ScheduleEvent(EVENT_INTRO_STEP_ONE, 1s);
            }
        }
    }

    void AttackStart(Unit* who) override
    {
        if (me->GetDisplayId() == DISPLAY_ID_BOSS_FIVE_BAT)
            return;

        if (_introScene)
        {
            BossAI::AttackStart(who);
            me->SetPassive();
            me->AttackStop();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
        }
        else
        {
            if (who && me->Attack(who, true))
            {
                if (me->HasUnitState(UNIT_STATE_DISTRACTED))
                {
                    me->ClearUnitState(UNIT_STATE_DISTRACTED);
                    me->GetMotionMaster()->Clear();
                }

                me->GetMotionMaster()->MoveChase(who);
            }
        }
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (pointId == POINT_MOVE_TO_WANDERER)
        {
            me->MonsterYell("Why are you still alive?", 0, nullptr);

            if (Unit * champion = instance->GetCreature(DATA_NPC_WANDERER_CHAMPION))
            {
                if (champion->IsAIEnabled)
                    champion->GetAI()->DoAction(ACTION_VAMPIRE_STRANGULATE);
                me->CastSpell(champion, SPELL_BOSS_FIVE_VISUAL_LINK);
                me->SetTarget(champion->GetGUID());
            }

            events.ScheduleEvent(EVENT_INTRO_MOVE_TO_EDGE, 5s);
        }
        else if (pointId == POINT_MOVE_TO_PLATFORM_EDGE)
        {
            if (_lastPhaseScene)
                events.ScheduleEvent(EVENT_GRIP_WANDERER, 2s);
            else
            {
                me->MonsterYell("Weakness disgusts me, begone.", LANG_UNIVERSAL, nullptr);
                events.ScheduleEvent(EVENT_FINISH_INTRO, 3s);
                me->RemoveAurasDueToSpell(SPELL_BOSS_FIVE_VISUAL_LINK);
            }
        }
        else if (pointId == POINT_MOVE_OUTSIDE_PLATFORM)
        {
            me->SetFacingTo(me->GetAngle(me->GetHomePosition().GetPositionX(), me->GetHomePosition().GetPositionY()));
            std::rotate(_platformSplits.begin(), _platformSplits.begin() + 1, _platformSplits.end());
            _currentSplit = _platformSplits.front();
            events.ScheduleEvent(EVENT_SHADOW_BOLT, 1s);
            events.ScheduleEvent(EVENT_MOVE_TO_SPLIT_START, 10s);
        }
        else if (pointId == POINT_MOVE_TO_SPLIT)
            events.ScheduleEvent(EVENT_MOVE_TO_END_SPLIT, 6s);
        else if (pointId == POINT_MOVE_TO_SPLIT_END)
            events.ScheduleEvent(EVENT_MOVE_BACK_TO_EDGE, 3s);
        else if (pointId == POINT_MOVE_BACK_TO_MIDDLE)
        {
            me->UpdateSpeed(MOVE_RUN);
            DoCastSelf(SPELL_BOSS_FIVE_TRANSFORM_VIS, true);
            me->SetAggressive();
            me->RestoreDisplayId();
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            me->AttackStop();
            DoResetThreat();
            DoZoneInCombat(me, 200.f);
            if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                AttackStart(target);
            else
                EnterEvadeMode();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        }
        else if (pointId == POINT_MOVE_TO_KABOOM)
        {
            if (Unit * wanderer = instance->GetCreature(DATA_NPC_WANDERER))
                if (wanderer->IsAIEnabled)
                    wanderer->GetAI()->DoAction(ACTION_VAMPIRE_BIGBANG);
            DoCastAOE(64584);
        }
    }

    void MoveToProperSplit(bool endPoint)
    {
        Position pos;
        switch (_currentSplit)
        {
            case GO_TO_PLATFORM_LEFT:
            {
                if (!endPoint)
                    pos = _splitPositions[2];
                else
                    pos = _splitEndPositions[2];
                break;
            }
            case GO_TO_PLATFORM_MIDDLE:
            {
                if (!endPoint)
                    pos = _splitPositions[1];
                else
                    pos = _splitEndPositions[1];
                break;
            }
            case GO_TO_PLATFORM_RIGHT:
            {
                if (!endPoint)
                    pos = _splitPositions[0];
                else
                    pos = _splitEndPositions[0];
                break;
            }
            default:
                return;
        }

        if (pos.IsPositionValid())
            me->GetMotionMaster()->MovePoint(!endPoint ? POINT_MOVE_TO_SPLIT : POINT_MOVE_TO_SPLIT_END, pos);
    }

    void DamageTaken(Unit* attacker, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        if (me->HealthBelowPctDamaged(30, damage) && !_did30pct)
        {
            events.Reset();
            _did30pct = true;
            DoCastAOE(SPELL_BOSS_FIVE_SHADOW_PRISON, true);
            me->SetPassive();
            me->AttackStop();
            me->GetMotionMaster()->Clear();
            me->GetMotionMaster()->MoveIdle();
            _lastPhaseScene = true;
            events.ScheduleEvent(EVENT_BEGIN_LAST_PHASE_SCENE, 2s);
            summons.Broadcast([](Creature* summon)
            {
                summon->AddAura(22682, summon);
                summon->SetPassive();
                summon->AttackStop();
                summon->GetMotionMaster()->Clear();
                summon->GetMotionMaster()->MoveIdle();
                summon->DespawnOrUnsummon(3s);
            });
        }
        if (attacker && attacker->GetEntry() == NPC_WANDENER)
            damage = me->GetMaxHealth();
    }

    void UpdateAI(uint32 diff) override
    {
        if (!_introScene && !_lastPhaseScene && !UpdateVictim())
            return;

        events.Update(diff);
        scheduler.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_INTRO_STEP_ONE:
                {
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_TO_WANDERER, _wandererPosition);
                    break;
                }
                case EVENT_INTRO_MOVE_TO_EDGE:
                {
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_TO_PLATFORM_EDGE, _platformEdgePosition);
                    break;
                }
                case EVENT_FINISH_INTRO:
                {
                    _introDoneOnce = true;
                    _introScene = false;
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BOSS_FIVE_SHADOW_PRISON);
                    me->AttackStop();
                    me->SetAggressive();
                    DoZoneInCombat();
                    DoResetThreat();
                    if (Player* player = me->SelectNearestPlayer(200.f))
                        AttackStart(player);
                    else
                        EnterEvadeMode();

                    ScheduleCombatEvents((BOSS_EVENT_TYPE_BAT_PHASE | BOSS_EVENT_TYPE_SONIC_SCREECH | BOSS_EVENT_TYPE_SUMMONS | BOSS_EVENT_TYPE_SWD));
                    break;
                }
                case EVENT_SUMMON_BURNER:
                {
                    me->SummonCreature(NPC_BOSS_FIVE_BURNER, Trinity::Containers::SelectRandomContainerElement(_roomCorners));
                    events.Repeat(20s, 25s);
                    break;
                }
                case EVENT_SUMMON_FEARER:
                {
                    me->SummonCreature(NPC_BOSS_FIVE_FEARER, Trinity::Containers::SelectRandomContainerElement(_roomCorners));
                    events.Repeat(20s, 25s);
                    break;
                }
                case EVENT_SUMMON_BIG_ADD:
                {
                    me->SummonCreature(NPC_BOSS_FIVE_BIG_ADD, Trinity::Containers::SelectRandomContainerElement(_roomCorners));
                    events.Repeat(40s, 45s);
                    break;
                }
                case EVENT_SUMMON_BATS:
                {
                    for (uint16 i = 0; i < MAX_AMOUNT_OF_BATS; ++i)
                    {
                        Position movePosition = i ? _batRightCorner : _batLeftCorner;
                        if (Creature* bat = me->SummonCreature(NPC_BOSS_FIVE_BAT, _batSpawnPosition))
                        {
                            bat->SetCanFly(true);
                            bat->SetDisableGravity(true);
                            bat->GetMotionMaster()->MovePoint(1, movePosition);
                        }
                    }
                    break;
                }
                case EVENT_SHADOW_WORD_DEATH:
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, 30.f, true))
                    {
                        auto _damageToDeal = target->GetHealth() * _shadowWordPct;
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _damageToDeal);
                        val.AddSpellMod(SPELLVALUE_BASE_POINT1, 0);
                        me->CastCustomSpell(SPELL_BOSS_FIVE_SHADOW_WORD, val, target, TRIGGERED_FULL_MASK);

                        auto _damageToHeal = std::min(me->GetMaxHealth(), uint32(_damageToDeal * _shadowWordHealRatio));
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _damageToHeal);
                        me->CastCustomSpell(SPELL_BOSS_FIVE_BLOODTHRIST, val, me, TRIGGERED_FULL_MASK);

                        events.Repeat(15s, 25s);
                    }
                    break;
                }
                case EVENT_SONIC_SCREECH:
                {
                    CustomSpellValues val;
                    val.AddSpellMod(SPELLVALUE_BASE_POINT0, _sonicScreechDamage);
                    me->CastCustomSpell(SPELL_BOSS_FIVE_SONIC_SCREECH, val, me->GetVictim());
                    events.Repeat(45s);
                    break;
                }
                case EVENT_BAT_PHASE:
                {
                    scheduler.CancelGroup(GROUP_SWARMING_SHADOWS);

                    std::vector<Position> _orbsPosition = _swarmingOrbsPositions;
                    Trinity::Containers::RandomResize(_orbsPosition, size_t(2));
                    for (auto && pos : _orbsPosition)
                    {
                        if (Creature* swarmer = me->SummonCreature(NPC_BOSS_FIVE_SWARM_SPREADER, pos))
                        {
                            HellforgeStatValues val;
                            sWorldCache.GetStatValue(BOSS_FIVE_ADD_CRYSTAL_HEALTH, val);
                            swarmer->SetMaxHealth(val.StatValue);
                            swarmer->SetFullHealth();
                            swarmer->SetPassive();
                            swarmer->SetCanFly(true);
                            swarmer->SetDisableGravity(true);
                        }
                    }

                    scheduler.Schedule(4s, GROUP_SWARMING_SHADOWS, [this](TaskContext func)
                    {
                        std::set<uint64> _playerGUIDs;
                        for (auto && guid : summons)
                        {
                            Creature* sum = ObjectAccessor::GetCreature(*me, guid);
                            if (!sum)
                                continue;

                            if (sum->GetEntry() != NPC_BOSS_FIVE_SWARM_SPREADER)
                                continue;

                            if (!sum->IsAlive())
                                continue;

                            Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 150.f, true);
                            if (!target)
                                continue;

                            if (_playerGUIDs.find(target->GetGUID()) != _playerGUIDs.end())
                                continue;

                            _playerGUIDs.insert(target->GetGUID());
                            sum->CastSpell(target, SPELL_BOSS_FIVE_SWARMING_SHADOW, true);
                        }

                        func.Repeat(20s);
                    });

                    me->SetSpeedRate(MOVE_RUN, me->GetSpeedRate(MOVE_RUN) * 2.0f);
                    DelayNonBatEvents();
                    me->SetCanFly(true);
                    me->SetDisableGravity(true);
                    DoCastSelf(SPELL_BOSS_FIVE_TRANSFORM_VIS);
                    me->SetDisplayId(DISPLAY_ID_BOSS_FIVE_BAT);
                    me->MonsterYell("You will all burn!", LANG_UNIVERSAL, nullptr);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    me->GetMotionMaster()->Clear();
                    me->GetMotionMaster()->MoveIdle();
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_OUTSIDE_PLATFORM, _edgeOfPlatform);
                    events.ScheduleEvent(EVENT_END_BAT_PHASE, 90s);
                    break;
                }
                case EVENT_MOVE_TO_SPLIT_START:
                {
                    events.CancelEvent(EVENT_SHADOW_BOLT);
                    MoveToProperSplit(false);
                    break;
                }
                case EVENT_MOVE_TO_END_SPLIT:
                {
                    scheduler.Schedule(1s, GROUP_CANCELABLE, [&](TaskContext func)
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _shadowbreathDamage);
                        me->CastCustomSpell(SPELL_BOSS_FIVE_SHADOW_BREATH, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                        DoCastAOE(SPELL_BOSS_FIVE_SHADOW_BREATH, true);
                        func.Repeat(1s);
                    });

                    MoveToProperSplit(true);
                    break;
                }
                case EVENT_MOVE_BACK_TO_EDGE:
                {
                    scheduler.CancelGroup(GROUP_CANCELABLE);
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_OUTSIDE_PLATFORM, _edgeOfPlatform);
                    break;
                }
                case EVENT_END_BAT_PHASE:
                {
                    scheduler.CancelGroup(GROUP_CANCELABLE);
                    events.CancelEvent(EVENT_BAT_SHADOW_BOLT);
                    events.CancelEvent(EVENT_MOVE_TO_SPLIT_START);
                    events.CancelEvent(EVENT_MOVE_TO_END_SPLIT);
                    events.CancelEvent(EVENT_MOVE_BACK_TO_EDGE);
                    DoCastSelf(SPELL_BOSS_FIVE_VALKYR_QUICKNESS, true);
                    if (Aura* aura = me->GetAura(SPELL_BOSS_FIVE_VALKYR_QUICKNESS))
                    {
                        aura->SetMaxDuration(-1);
                        aura->RefreshDuration();
                    }

                    me->GetMotionMaster()->MovePoint(POINT_MOVE_BACK_TO_MIDDLE, me->GetHomePosition());
                    events.ScheduleEvent(EVENT_BAT_PHASE, 90s);
                    break;
                }
                case EVENT_SHADOW_BOLT:
                {
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 200.f, true))
                    {
                        CustomSpellValues val;
                        val.AddSpellMod(SPELLVALUE_BASE_POINT0, _shadowBoltDamage);
                        me->CastCustomSpell(SPELL_BOSS_FIVE_SHADOW_BOLT, val, target, TRIGGERED_FULL_MASK);
                    }
                    events.Repeat(2s);
                    break;
                }
                case EVENT_BEGIN_LAST_PHASE_SCENE:
                {
                    me->GetMotionMaster()->MovePoint(POINT_MOVE_TO_PLATFORM_EDGE, _platformEdgePosition);
                    break;
                }
                case EVENT_GRIP_WANDERER:
                {
                    DoCastSelf(43085);
                    events.ScheduleEvent(EVENT_MOVE_WANDERER, 2s);
                    break;
                }
                case EVENT_MOVE_WANDERER:
                {
                    me->MonsterYell("Jonas! Bring me their heads!", LANG_UNIVERSAL, nullptr);
                    if (Creature* worgen = me->SummonCreature(NPC_BOSS_FIVE_FIERY_WORGEN, _fieryWorgenSpawnPosition))
                    {
                        worgen->SetPassive();
                        worgen->SetSelectable(false);
                        _worgenGUID = worgen->GetGUID();

                        Movement::MoveSplineInit init(worgen);
                        float x = _fieryWorgenJumpPosition.GetPositionX();
                        float y = _fieryWorgenJumpPosition.GetPositionY();
                        float z = _fieryWorgenJumpPosition.GetPositionZ();
                        init.MoveTo(x, y, z);
                        init.SetParabolic(45.f, 0);
                        init.SetVelocity(20.f);

                        for (auto && spellId : { SPELL_BOSS_FIVE_FOG_VISUAL, SPELL_BOSS_FIVE_SARONITE_BARRIER })
                            DoCastSelf(spellId, true);

                        events.ScheduleEvent(EVENT_END_LAST_PHASE_SCENE, init.Launch() + 4500);
                    }
                    else
                        EnterEvadeMode();
                    break;
                }
                case EVENT_END_LAST_PHASE_SCENE:
                {
                    me->RemoveAurasDueToSpell(43085);
                    instance->DoRemoveAurasDueToSpellOnPlayers(SPELL_BOSS_FIVE_SHADOW_PRISON);
                    me->SetAggressive();

                    if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                        me->GetMotionMaster()->MoveChase(target);
                    else
                        EnterEvadeMode();

                    if (Creature* worgen = ObjectAccessor::GetCreature(*me, _worgenGUID))
                    {
                        worgen->SetSelectable(true);
                        worgen->SetAggressive();
                        worgen->AI()->DoZoneInCombat();
                    }
                    _lastPhaseScene = false;
                    ScheduleCombatEvents((BOSS_EVENT_TYPE_SUMMONS | BOSS_EVENT_TYPE_SWD));
                    break;
                }
                default:
                    break;
            }
        }

        if (me->GetDisplayId() != DISPLAY_ID_BOSS_FIVE_BAT)
            DoMeleeAttackIfReady();
        EnterEvadeIfOutOfCombatArea();
    }

    bool CheckEvadeIfOutOfCombatArea() const override
    {
        return me->GetDistance(me->GetHomePosition()) >= 100.f;
    }

    void JustDied(Unit* killer) override
    {
        me->MonsterYell("Lord of Terror...", LANG_UNIVERSAL, me);
        if (Unit * wanderer = instance->GetCreature(DATA_NPC_WANDERER))
            if (wanderer->IsAIEnabled)
                wanderer->GetAI()->DoAction(ACTION_VAMPIRE_KILLED);
        CheckCreatureRecord(killer, HELLFORGE_CREATURE_RECORD_MIN_VALUE + 4, RAID_DIFFICULTY_10MAN_NORMAL, "", 1, _fightTimer);
        BossAI::JustDied(killer);
    }
private:
    bool _introDoneOnce;
    bool _introScene;
    bool _did30pct;
    bool _lastPhaseScene;
    uint64 _worgenGUID;
    std::array<BossFivePlatformFires, 3> _platformSplits;
    BossFivePlatformFires _currentSplit;

    float _shadowWordPct;
    uint32 _sonicScreechDamage;
    uint32 _shadowBoltDamage;
    uint32 _fightTimer;
    uint32 _shadowbreathDamage;
    uint32 _shadowWordHealRatio;
};

//struct npc_boss_five_flame_spreader_AI : public ScriptedAI
//{
//    npc_boss_five_flame_spreader_AI(Creature* creature) : ScriptedAI(creature)
//    {
//        _task.CancelAll();
//    }
//
//    void Reset() override
//    {
//        DoZoneInCombat(me, 150.f);
//    }
//
//    void AttackStart(Unit* who) override
//    {
//        me->Attack(who, false);
//    }
//
//    void EnterCombat(Unit* /*who*/) override
//    {
//        _task.Schedule(4s, [this](TaskContext func)
//        {
//            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 0.f, true))
//                DoCast(target, SPELL_BOSS_FIVE_SWARMING_SHADOW, true);
//            func.Repeat(20s);
//        });
//    }
//
//    void MoveInLineOfSight(Unit* /*who*/) override { }
//    void UpdateAI(uint32 diff) override
//    {
//        _task.Update(diff);
//    }
//private:
//    TaskScheduler _task;
//};

enum BossFiveFieryWorgen
{
    SPELL_FIERY_WORGEN_FIERY_AURA           = 38841,
    SPELL_FIERY_WORGEN_FIERY_AURA_LEGION    = 39839
};

struct npc_boss_five_frosty_worgen_AI : public ScriptedAI
{
    npc_boss_five_frosty_worgen_AI(Creature* creature) : ScriptedAI(creature), _instance(me->GetInstanceScript()) { }

    void Reset() override
    {
        LoadStats();
        HellforgeStatValues val;
        sWorldCache.GetStatValue(BOSS_FIVE_ADD_WORGEN_HEALTH, val);
        me->SetMaxHealth(val.StatValue);
        me->SetFullHealth();

        _task.CancelAll();
        for (auto && spellId : { SPELL_FIERY_WORGEN_FIERY_AURA, SPELL_FIERY_WORGEN_FIERY_AURA_LEGION })
            DoCastSelf(spellId);
        ScriptedAI::Reset();
        _meleeAttackExplosion = true;
    }

    void LoadStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_FIVE_ADD_WORGEN_HEALTH, BOSS_FIVE_ADD_WORGEN_MELEE_DMG });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_FIVE_ADD_WORGEN_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_FIVE_ADD_WORGEN_MELEE_DMG:
                {
                    uint32 minDamage = ref.second.StatValue;
                    uint32 maxDamage = ref.second.StatValue * ref.second.StatVariance;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
            }
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _task.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }

    void JustDied(Unit* killer) override
    {
        if (Creature* boss = _instance->GetCreature(DATA_BOSS_FIVE))
            boss->AI()->SetData(DATA_FROSTY_WORGEN_KILLED, DATA_FROSTY_WORGEN_KILLED);
        ScriptedAI::JustDied(killer);
    }

    void OnMeleeAttack(VictimState state, WeaponAttackType attackType, Unit* victim) override
    {
        if (attackType != BASE_ATTACK)
            return;

        if (state == VICTIMSTATE_HIT && _meleeAttackExplosion)
        {
            if (Creature* explosionTrigger = me->SummonCreature(NPC_BOSS_FIVE_WORGEN_MELEE_EXPLOSION, victim->GetPosition()))
            {
                explosionTrigger->SetPassive();
                explosionTrigger->DespawnOrUnsummon(4s);
            }

            _meleeAttackExplosion = false;
            //! Add a delay between explosions, so each attack doesnt trigger it, would look terrible
            _task.Schedule(3s, [this](TaskContext /*func*/)
            {
                _meleeAttackExplosion = true;
            });
        }
    }

public:
    bool _meleeAttackExplosion;
    TaskScheduler _task;
    InstanceScript* _instance;
};

struct npc_boss_five_melee_explosion_AI : public ScriptedAI
{
    npc_boss_five_melee_explosion_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        DoCastAOE(70823, true);
        _task.Schedule(2s, [this](TaskContext /*func*/)
        {
            DoCastAOE(71746);
        });
    }

    void AttackStart(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }
    void UpdateAI(uint32 diff) override { _task.Update(diff); }
private:
    TaskScheduler _task;
};

struct npc_boss_five_fearer_AI : public ScriptedAI
{
    npc_boss_five_fearer_AI(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
    }

    void AttackStart(Unit* who) override
    {
        ScriptedAI::AttackStartCaster(who, 10.f);
    }

    void SpellHitTarget(Unit* victim, SpellInfo const* spellInfo) override
    {
        if (victim && spellInfo->Id == SPELL_BOSS_FIVE_WITHER)
        {
            victim->CastSpell(victim, SPELL_BOSS_FIVE_FADE_OUT, true);
            if (Aura* aura = victim->GetAura(SPELL_BOSS_FIVE_FADE_OUT))
            {
                aura->SetMaxDuration(3000);
                aura->RefreshDuration();
            }
        }
    }

    void Reset() override
    {
        _task.CancelAll();
        LoadBossStats();
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_FIVE_ADD_MINDMASTER_HEALTH, BOSS_FIVE_ADD_MINDMASTER_MANA, BOSS_FIVE_ADD_MINDMASTER_WITHER_DAMAGE,
            BOSS_FIVE_ADD_MINDMASTER_WITHER_DOT_DMG, BOSS_FIVE_ADD_CASTER_MELEE_DAMAGE,  });
        for (auto const& _ref : _stats)
        {
            switch (_ref.first)
            {
                case BOSS_FIVE_ADD_MINDMASTER_HEALTH:
                {
                    me->SetMaxHealth(_ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_FIVE_ADD_MINDMASTER_MANA:
                {
                    me->SetMaxPower(POWER_MANA, _ref.second.StatValue);
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    break;
                }
                case BOSS_FIVE_ADD_MINDMASTER_WITHER_DAMAGE:
                {
                    _witherDamage = urand((_ref.second.StatValue * _ref.second.StatVariance), _ref.second.StatValue);
                    break;
                }
                case BOSS_FIVE_ADD_MINDMASTER_WITHER_DOT_DMG:
                {
                    _witherDotDamage = urand((_ref.second.StatValue * _ref.second.StatVariance), _ref.second.StatValue);
                    break;
                }
                case BOSS_FIVE_ADD_CASTER_MELEE_DAMAGE:
                {
                    uint32 minDamage = _ref.second.StatValue * _ref.second.StatVariance;
                    uint32 maxDamage = _ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);

        _task.Schedule(2s, [this](TaskContext func)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, [this](Unit* object) -> bool
            {
                Creature* boss = _instance->GetCreature(DATA_BOSS_FIVE);
                if (!boss)
                    return false;

                if (!boss->AI())
                    return false;

                if (me->GetDistance(object->GetPosition()) > 40.f)
                    return false;

                Unit* target = boss->AI()->SelectTarget(SELECT_TARGET_TOPAGGRO);
                if (!target)
                    return false;

                if (object->GetGUID() == target->GetGUID())
                    return false;

                return true;
            }))
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _witherDamage);
                val.AddSpellMod(SPELLVALUE_BASE_POINT1, _witherDotDamage);
                me->CastCustomSpell(SPELL_BOSS_FIVE_WITHER, val, target);
            }

            func.Repeat(4s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _task.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }
private:
    TaskScheduler _task;
    InstanceScript* _instance;
    uint32 _witherDamage;
    uint32 _witherDotDamage;
};

struct npc_boss_five_burner_AI : public ScriptedAI
{
    npc_boss_five_burner_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        ScriptedAI::Reset();
        LoadBossStats();
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_FIVE_ADD_WARLOCK_HEALTH, BOSS_FIVE_ADD_WARLOCK_MANA, BOSS_FIVE_ADD_WARLOCK_BURN_DAMAGE,
            BOSS_FIVE_ADD_CASTER_MELEE_DAMAGE });

        for (auto const& _ref : _stats)
        {
            switch (_ref.first)
            {
                case BOSS_FIVE_ADD_WARLOCK_HEALTH:
                {
                    me->SetMaxHealth(_ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_FIVE_ADD_WARLOCK_MANA:
                {
                    me->SetMaxPower(POWER_MANA, _ref.second.StatValue);
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    break;
                }
                case BOSS_FIVE_ADD_WARLOCK_BURN_DAMAGE:
                {
                    _burnDamage = urand((_ref.second.StatValue * _ref.second.StatVariance), _ref.second.StatValue);
                    break;
                }
                case BOSS_FIVE_ADD_CASTER_MELEE_DAMAGE:
                {
                    uint32 minDamage = _ref.second.StatValue * _ref.second.StatVariance;
                    uint32 maxDamage = _ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);

        _task.Schedule(4s, [this](TaskContext func)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 10.f, true))
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _burnDamage);
                me->CastCustomSpell(SPELL_BOSS_FIVE_MANA_BURN_CHANNEL, val, target);
            }
            func.Repeat(4s);
        });
    }

    void AttackStart(Unit* who) override
    {
        ScriptedAI::AttackStartCaster(who, 5.f);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _task.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }
private:
    TaskScheduler _task;
    uint32 _burnDamage;
};

struct npc_boss_five_big_add_AI : public ScriptedAI
{
    npc_boss_five_big_add_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        ScriptedAI::Reset();
        LoadBossStats();
    }

    void LoadBossStats()
    {

        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_FIVE_ADD_SLAUGHTER_HEALTH, BOSS_FIVE_ADD_SLAUGHTER_MELEE_DMG, BOSS_FIVE_ADD_SLAUGHTER_CLEAVE_DMG,
            BOSS_FIVE_ADD_SLAUGHTER_HAMSTRING_DMG });

        for (auto const& _ref : _stats)
        {
            switch (_ref.first)
            {
                case BOSS_FIVE_ADD_SLAUGHTER_HEALTH:
                {
                    me->SetMaxHealth(_ref.second.StatValue);
                    me->SetFullHealth();
                    break;
                }
                case BOSS_FIVE_ADD_SLAUGHTER_MELEE_DMG:
                {
                    uint32 minDamage = _ref.second.StatValue * _ref.second.StatVariance;
                    uint32 maxDamage = _ref.second.StatValue;
                    me->SetBaseWeaponDamage(BASE_ATTACK, MINDAMAGE, minDamage);
                    me->SetBaseWeaponDamage(BASE_ATTACK, MAXDAMAGE, maxDamage);
                    me->UpdateDamagePhysical(BASE_ATTACK);
                    break;
                }
                case BOSS_FIVE_ADD_SLAUGHTER_CLEAVE_DMG:
                {
                    _cleaveWeaponDmg = _ref.second.StatValue;
                    break;
                }
                case BOSS_FIVE_ADD_SLAUGHTER_HAMSTRING_DMG:
                {
                    _hamstringDmg = _ref.second.StatValue;
                    break;
                }
                default:
                    break;
            }
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);

        _task.Schedule(5s, [this](TaskContext func)
        {
            std::list<Creature*> _bigAddsInRange;
            me->GetCreatureListWithEntryInGrid(_bigAddsInRange, me->GetEntry(), 11.0f);
            _bigAddsInRange.remove_if([this](Creature* creature)
            {
                return creature->GetGUID() == me->GetGUID() || !creature->IsAlive();
            });

            if (!_bigAddsInRange.empty())
            {
                size_t stackSize = std::min(static_cast<size_t>(3), _bigAddsInRange.size());
                DoCastSelf(SPELL_BOSS_FIVE_HULK);
                if (Aura* aura = me->GetAura(SPELL_BOSS_FIVE_HULK))
                    aura->SetStackAmount(stackSize);
            }
            else
                me->RemoveAurasDueToSpell(SPELL_BOSS_FIVE_HULK);

            func.Repeat(2s);
        });

        _task.Schedule(2s, [this](TaskContext func)
        {
            if (me->GetVictim())
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _cleaveWeaponDmg);
                me->CastCustomSpell(SPELL_BOSS_FIVE_CLEAVE, val, me->GetVictim(), TRIGGERED_FULL_MASK);
            }

            func.Repeat(5s);
        });

        _task.Schedule(8s, [this](TaskContext func)
        {
            if (me->GetVictim())
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _hamstringDmg);
                me->CastCustomSpell(SPELL_BOSS_FIVE_ADD_HAMSTRING, val, me->GetVictim(), TRIGGERED_FULL_MASK);
            }

            func.Repeat(8s, 12s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _task.Update(diff, std::bind(&ScriptedAI::DoMeleeAttackIfReady, this));
    }
private:
    TaskScheduler _task;
    uint32 _cleaveWeaponDmg;
    uint32 _hamstringDmg;
};

struct npc_boss_five_bat_AI : public ScriptedAI
{
    npc_boss_five_bat_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _task.CancelAll();
        LoadBossStats();
    }

    void LoadBossStats()
    {
        HellforgeStats _stats = sWorldCache.GetStatValues({ BOSS_FIVE_ADD_BAT_HEALTH, BOSS_FIVE_ADD_BAT_SHADOW_BOLT });

        for (auto const& ref : _stats)
        {
            switch (ref.first)
            {
                case BOSS_FIVE_ADD_BAT_HEALTH:
                {
                    me->SetMaxHealth(ref.second.StatValue);
                    me->SetFullHealth();
                    me->SetMaxPower(POWER_MANA, ref.second.StatValue);
                    me->SetPower(POWER_MANA, me->GetMaxPower(POWER_MANA));
                    break;
                }
                case BOSS_FIVE_ADD_BAT_SHADOW_BOLT:
                {
                    _shadowBoltDamage = urand((ref.second.StatValue * ref.second.StatVariance), ref.second.StatValue);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void AttackStart(Unit* who) override
    {
        me->Attack(who, false);
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (pointId == 1)
        {
            DoZoneInCombat(me, 200.f);
            _task.Schedule(2s, [this](TaskContext func)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, _shadowBoltDamage);
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0U, 200.f, true))
                    me->CastCustomSpell(SPELL_BOSS_FIVE_SHADOW_BOLT_BAT, val, target);
                func.Repeat(4s);
            });
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _task.Update(diff);
    }
private:
    uint32 _shadowBoltDamage;
    TaskScheduler _task;
};

struct npc_boss_five_flame_spreader_AI : public ScriptedAI
{
    npc_boss_five_flame_spreader_AI(Creature* creature) : ScriptedAI(creature) {}
    void JustDied(Unit* killer) override
    {
        me->DespawnOrUnsummon();
    }
};

class spell_hellforge_boss_five_flame : public SpellScript
{
    PrepareSpellScript(spell_hellforge_boss_five_flame);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (GetCaster() && GetCaster()->GetMapId() == HELLFORGE_MAP_ID)
        {
            HellforgeStatValues val;
            sWorldCache.GetStatValue(BOSS_FIVE_STAT_ID_FLAMES, val);
            SetEffectValue(val.StatValue);
        }
    }

    void Register() override
    {
        OnEffectLaunchTarget += SpellEffectFn(spell_hellforge_boss_five_flame::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

void AddSC_hellforge_boss_five()
{
    new CreatureAILoader<boss_hellforge_five_AI>("boss_hellforge_five");
    new CreatureAILoader<npc_boss_five_flame_spreader_AI>("npc_boss_five_flame_spreader");
    new CreatureAILoader<npc_boss_five_frosty_worgen_AI>("npc_boss_five_frosty_worgen");
    new CreatureAILoader<npc_boss_five_melee_explosion_AI>("npc_boss_five_melee_explosion");
    new CreatureAILoader<npc_boss_five_fearer_AI>("npc_boss_five_fearer");
    new CreatureAILoader<npc_boss_five_burner_AI>("npc_boss_five_burner");
    new CreatureAILoader<npc_boss_five_big_add_AI>("npc_boss_five_big_add");
    new CreatureAILoader<npc_boss_five_bat_AI>("npc_boss_five_bat");

    new SpellScriptLoaderEx<spell_hellforge_boss_five_flame>("spell_hellforge_boss_five_flame");
}
