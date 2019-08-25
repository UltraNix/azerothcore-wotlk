#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "onyxias_lair.h"
#include "SpellScript.h"
#include "MoveSplineInit.h"
#include "GameObjectAI.h"

#pragma message(CompileMessage "usunac shadow realm aure przy evade")
enum DiabloSpells
{
    SPELL_DIABLO_NETHER_PORTAL_VISUAL       = 66263, // We have to disable proc on this map
    SPELL_DIABLO_EYE_BEAM                   = 49544,
    SPELL_DIABLO_HEART_BEAM_VISUAL          = 54988,
    SPELL_DIABLO_REALM_OF_SHADOWS           = 52693,
    SPELL_DIABLO_RED_BEAM_DROPS             = 30944,
    SPELL_DIABLO_SMOKEY_MARKER              = 16714,
    SPELL_DIABLO_FLAME_BUFFET               = 34121,
    SPELL_DIABLO_RUNE_DETONATION            = 62527, // used instead of base triggered spell in Armageddon spell
};

enum DiabloCreatures
{
    NPC_BOSS_SIX_DIABLO                     = 250200,
    NPC_BOSS_SIX_PORTAL_TRIGGER             = 250201,
    NPC_BOSS_SIX_ABYSS_KNIGHT               = 250202,
    NPC_BOSS_SIX_OMOR_COPY                  = 250203,
    NPC_BOSS_SIX_BEAM_TRIGGER               = 250204,
    NPC_BOSS_SIX_BEAM_TRIGGER_EXPLO_TRIGGER = 250205,
    NPC_BOSS_SIX_HEART_BEAM_TRIGGER         = 250206,
    NPC_BOSS_SIX_FIERY_COMET_TRIGGER        = 250207,
    NPC_BOSS_SIX_PENTAGON_TRIGGER_1         = 250208, // all the way to 250212
    NPC_BOSS_SIX_DIABOLIC_INFERNAL          = 250213,
    NPC_BOSS_SIX_INCREASED_DAMAGE_TRIGGER   = 250214,
    NPC_BOSS_SIX_UNSTABLE_FIRE_ELEMENTAL    = 250215
};

enum DiabloGameobjects
{
    GAMEOBJECT_DIABLO_JUMPER                = 400800
};

enum DiabloMisc
{
    DIABLO_MAP_ID                           = 249,
    DATA_SET_DEMON_TYPE,
    DATA_SWITCH_DEMON_TYPE,
    GROUP_DEMON_SWITCHABLE,
    DATA_EXPLOSION_TIMER
};

constexpr uint32 NETHER_PORTAL_SPAWN_POSITION_SIZE{ 2 };
Position const netherPortalSpawnPosition[NETHER_PORTAL_SPAWN_POSITION_SIZE] =
{
    { 2.635f, -235.231f, -86.79315f, 2.989f }, // left
    { 6.315f, -198.990f, -86.32233f, 3.040f }  // right
};

constexpr uint32 ABYSS_KNIGHT_MOVEMENT_POSITION_SIZE{ 12 };
Position const abyssKnightMovementPosition[ABYSS_KNIGHT_MOVEMENT_POSITION_SIZE] =
{
    // left side move positions
    // first row
    { -25.086f, -237.386f, -89.133f, 3.018f },
    { -24.598f, -233.447f, -89.062f, 3.018f },
    { -23.981f, -228.466f, -89.125f, 3.018f },
    // second row
    { -18.283f, -238.588f, -88.312f, 3.018f },
    { -17.766f, -234.413f, -88.274f, 3.018f },
    { -17.135f, -229.314f, -88.306f, 3.018f },

    // right side move positions
    // first row
    { -20.363f, -195.671f, -88.646f, 3.238f },
    { -21.231f, -190.138f, -88.743f, 3.297f },
    { -21.990f, -185.298f, -88.769f, 3.297f },
    // second row
    { -12.642f, -194.651f, -87.898f, 3.280f },
    { -13.466f, -188.765f, -87.762f, 3.280f },
    { -14.842f, -183.720f, -87.663f, 3.360f }
};

constexpr uint32 ABYSS_KNIGHT_SPAWN_POSITIONS_SIZE{ 3 };
Position const abyssKnightLeftSpawnPos[ABYSS_KNIGHT_SPAWN_POSITIONS_SIZE] =
{
    {  0.724f, -238.747f, -86.92437f, 3.402f },
    { -0.148f, -235.480f, -87.07575f, 3.402f },
    { -1.322f, -231.084f, -86.81894f, 3.402f }
};

Position const abyssKnightRightSpawnPos[ABYSS_KNIGHT_SPAWN_POSITIONS_SIZE] =
{
    { 3.859f, -201.951f, -86.28029f, 3.128f },
    { 2.760f, -197.746f, -86.65012f, 3.128f },
    { 2.832f, -192.615f, -86.78608f, 3.128f }
};

constexpr uint32 FLYING_DOOM_MOVE_POSITION_SIZE{ 2 };
Position const flyingDoomMovePositions[FLYING_DOOM_MOVE_POSITION_SIZE] =
{
    { -10.542f, -245.968f, -83.27728f, 2.379f },
    { -9.295f, -176.949f, -83.61343f, 3.980f }
};

constexpr uint32 PENTAGON_TRIGGER_POSITION_SIZE{ 5 };
Position const pentagonSpawnPositions[PENTAGON_TRIGGER_POSITION_SIZE] =
{
    {  11.383f, -216.512f, -85.07498f, 3.124f },
    { -71.069f, -234.472f, -85.07175f, 0.076f },
    { -30.769f, -178.096f, -85.18916f, 4.808f },
    { -31.841f, -256.225f, -85.55862f, 4.663f },
    { -75.104f, -196.174f, -85.60699f, 1.667f }
};

constexpr uint32 INCREASED_DAMAGE_TRIGGER_POSITION_SIZE{ 3 };
Position const increasedDamageTriggerPositions[INCREASED_DAMAGE_TRIGGER_POSITION_SIZE] =
{
    { -33.114f, -236.784f, -88.78085f },
    { -33.074f, -188.624f, -88.94382f },
    { -71.761f, -213.107f, -83.74525f }
};

Position const _dummyFacingPosition{ -54.503f, -212.654f, -85.46500f, 6.268f };
Position const _centerOfFightingArea{ -28.712f, -213.297f, -89.08712f, 6.233f };
Position const _shadowRealmExitPosition{ -33.654663f, -212.973740f, -87.879509f, 6.218901f };
// ID - 54111 Summon Target Visual spell pod aure od dmg buff
// ID - 46907 Boss Fel Portal State fajny portal visual

// 18036 fajny infernal visual
// ID - 40736 Death Blast

// ID - 27673 Five Fat Finger Exploding Heart Technique
// + explosion at 5stacks ID - 27676 Exploding Heart
#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_diablo_AI : public BossAI
{
    npc_boss_six_diablo_AI(Creature* creature) : BossAI(creature, DATA_DIABLO)
    {
        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 10.f);
        scheduler.ClearValidator();
        me->SetCanMissSpells(false);
    }

    void JustSummoned(Creature* summon) override
    {
        if (summon->GetEntry() == NPC_BOSS_SIX_ABYSS_KNIGHT || summon->GetEntry() == NPC_BOSS_SIX_OMOR_COPY)
            summons.Summon(summon);
        else
            BossAI::JustSummoned(summon);
    }

    void OnMeleeAttack(VictimState state, WeaponAttackType attType, Unit* victim) override
    {
        if (attType != BASE_ATTACK)
            return;

        if (!victim)
            return;

        if (!victim->ToPlayer())
            return;

        if (!roll_chance_i(50 /*config*/))
            return;

        DoCast(victim, 27673, true);
    }

    void Reset() override
    {
        me->SetFloatValue(UNIT_FIELD_COMBATREACH, 10.f);
        BossAI::Reset();
        _intro = true;
        //me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        _pentagramIndex = 0;
        _shadowRealmTargetGUID = 0;
        _elementalPhase = false;
        _intermission = false;
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*Type*/, SpellSchoolMask /*mask*/) override
    {
        if (me->HealthBelowPctDamaged(20, damage) && !_elementalPhase)
        {
            _elementalPhase = true;
            HandleFireElementals();
            DoCastSelf(55086, true);
            return;
        }

        if (me->HealthBelowPctDamaged(50, damage) && !_intermission)
        {
            _intermission = true;
            me->MonsterYell("Super add piootrka sie zrespi teraz", LANG_UNIVERSAL, nullptr);
            return;
        }
    }

    void SummonedMovementInform(uint32 type, uint32 pointId, Unit* who) override
    {
        if (type == POINT_MOTION_TYPE && pointId == 100 && who)
            who->SetFacingTo(who->GetAngle(_dummyFacingPosition.GetPositionX(), _dummyFacingPosition.GetPositionY()));
    }

    void ReceiveEmote(Player* player, uint32 emoteId) override
    {
        if (!me->IsInCombat())
        {
            me->MonsterYell("nie jestem w combacie, nie moge zaczac", LANG_UNIVERSAL, nullptr);
            return;
        }

        _intro = true;

        if (emoteId == 34)
            SpawnInitialAdds();

        if (emoteId == 60)
            HandleKnockbackPlayer();

        if (emoteId == 101)
            BeginShadowRealm();

        if (emoteId == 17)
            HandleFireBeam();
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type == DATA_JUMPER_CLICKED && value == DATA_JUMPER_CLICKED)
            DrawPentagram();
    }

    void AttackStart(Unit* who) override
    {
        //me->Attack(who, false);
        BossAI::AttackStart(who);
    }

    void EnterCombat(Unit* who) override
    {
        BossAI::EnterCombat(who);
        me->MonsterYell("Faza z feniksami poki co ma crash wiec nie wrzucam, poprawie jutro", LANG_UNIVERSAL, nullptr);
    }

    void SummonedCreatureDies(Creature* summon, Unit* killer) override
    {
        BossAI::SummonedCreatureDies(summon, killer);
        if (summon->GetEntry() == NPC_BOSS_SIX_HEART_BEAM_TRIGGER)
        {
            instance->DoRemoveAurasDueToSpellOnPlayers(62794);
            me->MonsterYell("SKONCZYLEM FAZE SHADOW", LANG_UNIVERSAL, nullptr);
            EnterEvadeMode();
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim() && !_intro)
            return;

        scheduler.Update(diff);

#pragma message(CompileMessage "to tylko do testow, przepisac")
        if (me->GetVictim())
            DoMeleeAttackIfReady();

        if (_intro)
            return;

        DoMeleeAttackIfReady();
    }

    //! Spawn wave of adds when fight begins
    void SpawnInitialAdds()
    {
        scheduler.Schedule(20s, [this](TaskContext func)
        {
            _intro = false;
            me->AttackStop();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetAggressive();
            DoZoneInCombat(me, 200.f);
        });

        scheduler.Schedule(5s, [this](TaskContext func)
        {
            for (auto pos : netherPortalSpawnPosition)
            {
                if (Creature* portal = me->SummonCreature(NPC_BOSS_SIX_PORTAL_TRIGGER, pos))
                {
                    portal->SetPassive();
                    portal->SetImmuneToAll(true);
                    portal->CastSpell(portal, SPELL_DIABLO_NETHER_PORTAL_VISUAL, TRIGGERED_DISALLOW_PROC_EVENTS);
                }
            }

            scheduler.Schedule(2s, [this](TaskContext /*func*/)
            {
                //! spawn first wave
                for (uint32 i = 0; i < 6; ++i)
                {
                    Position spawnPos;
                    Position movePos;
                    if (i < 3)
                    {
                        movePos = abyssKnightMovementPosition[i];
                        spawnPos = abyssKnightLeftSpawnPos[i];
                    }
                    else
                    {
                        spawnPos = abyssKnightRightSpawnPos[i - 3];
                        movePos = abyssKnightMovementPosition[i + 3];
                    }

                    if (Creature* knight = me->SummonCreature(NPC_BOSS_SIX_ABYSS_KNIGHT, spawnPos))
                    {
                        knight->SetPassive();
                        knight->SetImmuneToAll(true);
                        knight->SetWalk(true);
                        knight->GetMotionMaster()->MovePoint(100, movePos);
                    }
                }
            });

            //! spawn second wave
            scheduler.Schedule(5s, [this](TaskContext /*func*/)
            {
                for (uint32 i = 6; i < 12; ++i)
                {
                    Position spawnPos;
                    Position movePos;
                    if (i < 9)
                    {
                        spawnPos = abyssKnightLeftSpawnPos[i - 6];
                        movePos = abyssKnightMovementPosition[i - 3];
                    }
                    else
                    {
                        spawnPos = abyssKnightRightSpawnPos[i - 9];
                        movePos = abyssKnightMovementPosition[i];
                    }

                    if (Creature* knight = me->SummonCreature(NPC_BOSS_SIX_ABYSS_KNIGHT, spawnPos))
                    {
                        knight->SetPassive();
                        knight->SetImmuneToAll(true);
                        knight->SetWalk(true);
                        knight->GetMotionMaster()->MovePoint(100, movePos);
                    }
                }
            });

            //! spawn third wave
            scheduler.Schedule(9s, [this](TaskContext /*func*/)
            {
                uint32 _moveIndex = 0;
                int32 _demonType = -1;

                for (auto pos : netherPortalSpawnPosition)
                {
                    Position realPosition = pos;
                    realPosition.m_positionZ += 4.5f;
                    if (Creature* flyingDoom = me->SummonCreature(NPC_BOSS_SIX_OMOR_COPY, realPosition))
                    {
                        flyingDoom->AI()->SetData(DATA_SET_DEMON_TYPE, ++_demonType);
                        flyingDoom->SetPassive();
                        flyingDoom->SetImmuneToAll(true);
                        flyingDoom->SetCanFly(true);
                        flyingDoom->SetDisableGravity(true);
                        flyingDoom->GetMotionMaster()->MovePoint(100, flyingDoomMovePositions[_moveIndex]);
                        ++_moveIndex;
                    }
                }
            });

            scheduler.Schedule(14s, [this](TaskContext /*func*/)
            {
                summons.DespawnEntry(NPC_BOSS_SIX_PORTAL_TRIGGER);

                summons.Broadcast([](Creature* summon)
                {
                    summon->SetAggressive();
                    summon->SetImmuneToAll(false);
                    summon->SetWalk(false);
                    summon->AI()->DoZoneInCombat(summon, 150.f);
                });
            });
        });
    }

    void HandleKnockbackPlayer()
    {
        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U);
        if (!target)
            return;

        target->KnockbackFrom(target->GetPositionX(), target->GetPositionY(), 0.1f, 45.f);
        target->CastSpell(target, 32474, true);
    }

    /** Shadow realm handling **/
    void BeginShadowRealm()
    {
        DespawnPreviousJumpers();
        _pentagramIndex = 0;
        Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1U, 200.f, true);
        if (!target)
        {
            me->MonsterYell("Nie mam targetu", LANG_UNIVERSAL, nullptr);
            return;
        }

        me->AddAura(SPELL_DIABLO_REALM_OF_SHADOWS, target);
        _shadowRealmTargetGUID = target->GetGUID();

        SpawnShadowrealmJumpers();
        SpawnPentagramTriggers();
#pragma message(CompileMessage "dokonczyc wiper timer - shadow realm")
        //schedule wipe
    }

    void DespawnPreviousJumpers()
    {
        for (auto && ref : _jumperGUIDs)
        {
            if (GameObject* go = ObjectAccessor::GetGameObject(*me, ref))
                go->Delete();
        }

        _jumperGUIDs.clear();
    }

    void SpawnShadowrealmJumpers()
    {
        for (uint32 i = 0; i < 5; ++i)
        {
            if (GameObject* go = me->SummonGameObject(GAMEOBJECT_DIABLO_JUMPER, Trinity::Containers::SelectRandomContainerElement(_diabloRandomSpawnPositions), 0.f, 0.f, 0.f, 0.f, 0, false))
            {
                go->SetPhaseMask(32, true);
                _jumperGUIDs.push_back(go->GetGUID());
            }
        }
    }

    void SpawnPentagramTriggers()
    {
        _pentagramTriggerGUIDs.clear();
        for (uint32 i = 0; i < PENTAGON_TRIGGER_POSITION_SIZE; ++i)
        {
            summons.DespawnEntry(NPC_BOSS_SIX_PENTAGON_TRIGGER_1 + i);
            Position _spawnPos = pentagonSpawnPositions[i];
            _spawnPos.m_positionZ = me->GetMap()->GetHeight(_spawnPos.GetPositionX(), _spawnPos.GetPositionY(), _spawnPos.GetPositionZ(), true, 100.f);
            if (Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_PENTAGON_TRIGGER_1 + i, _spawnPos))
            {
                trigger->SetCanFly(true);
                trigger->SetDisableGravity(true);
                _pentagramTriggerGUIDs.push_back(trigger->GetGUID());
            }
        }
    }

    void DrawPentagram()
    {
        uint64 casterGUID = _pentagramTriggerGUIDs[_pentagramIndex];
        //! if it's last trigger then target trigger at position 0 otherwise get another trigger
        uint64 targetGUID = _pentagramTriggerGUIDs[_pentagramIndex == size_t(_pentagramTriggerGUIDs.size() - 1) ? 0 : _pentagramIndex + 1];
        if (!casterGUID || !targetGUID)
        {
            me->MonsterYell("brak pentagram triggera", LANG_UNIVERSAL, 0);
            return;
        }

        Creature* caster = ObjectAccessor::GetCreature(*me, casterGUID);
        Creature* target = ObjectAccessor::GetCreature(*me, targetGUID);
        if (!caster || !target)
            return;

        caster->CastSpell(target, SPELL_DIABLO_RED_BEAM_DROPS, true);
        if (size_t(_pentagramIndex >= _pentagramTriggerGUIDs.size() - 1))
            me->MonsterYell("END OF SHADOW REALM PHASE", LANG_UNIVERSAL, nullptr);
        ++_pentagramIndex;

        if (_pentagramIndex >= size_t(_pentagramTriggerGUIDs.size()))
        {
            _pentagramIndex = 0;
            HandleShadowRealmExit(_shadowRealmTargetGUID);
        }
    }

    void HandleShadowRealmExit(uint64 playerGUID)
    {
        Player* player = ObjectAccessor::GetPlayer(*me, playerGUID);
        if (!player)
            return;

        player->RemoveAurasDueToSpell(SPELL_DIABLO_REALM_OF_SHADOWS);
        player->NearTeleportTo(_shadowRealmExitPosition);
        player->AddAura(62794, player);
        player->AddAura(SPELL_DIABLO_HEART_BEAM_VISUAL, player);
        if (Creature* heartbeam = me->SummonCreature(NPC_BOSS_SIX_HEART_BEAM_TRIGGER, _shadowRealmExitPosition))
        {
            heartbeam->SetPassive();
            player->CastSpell(heartbeam, 69198, true);
#pragma message(CompileMessage "dorobic conditions pod ten target, breakuje aure przy dmg")
            heartbeam->CastSpell(heartbeam, SPELL_DIABLO_HEART_BEAM_VISUAL, true);
            for (auto && pos : increasedDamageTriggerPositions)
            {
                Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_INCREASED_DAMAGE_TRIGGER, pos);
                if (trigger)
                    trigger->AI()->SetGUID(heartbeam->GetGUID());
            }
        }
    }
    /** END OF SHADOW REALM HANDLING **/

    void HandleTriggerCharge(Unit* who, Unit* target)
    {
        if (!who || !target)
            return;

        Position initialPosition = who->GetPosition();
        Position chargePosition = target->GetPosition();
        initialPosition.SetOrientation(who->GetAngle(target->GetPositionX(), target->GetPositionY()));

        Movement::MoveSplineInit init(who);
        chargePosition.m_positionZ += 1.5f;
        init.MoveTo({ chargePosition.GetPositionX(), chargePosition.GetPositionY(), chargePosition.GetPositionZ() }, false, false);
        init.SetVelocity(42.f);
        std::chrono::milliseconds _timer(init.Launch());

        float const distance = who->GetDistance2d(target);

        for (float f = 0.f; f <= 1.2f; f += 0.1f)
        {
            float x, y, z;
            x = initialPosition.GetPositionX() + ((distance * f) * cos(initialPosition.GetOrientation()));
            y = initialPosition.GetPositionY() + ((distance * f) * sin(initialPosition.GetOrientation()));
            z = who->GetMap()->GetHeight(x, y, who->GetPositionZ() + 15.f, true, 150.f);

            if (Creature* exploTrigger = me->SummonCreature(NPC_BOSS_SIX_BEAM_TRIGGER_EXPLO_TRIGGER, { x, y, z, who->GetOrientation() }))
                exploTrigger->AI()->SetData(DATA_EXPLOSION_TIMER, static_cast<uint32>(_timer.count() * f));
        }

        //me->DespawnOrUnsummon(_timer.count() + 200U);
    }

    void HandleFireBeam()
    {
        me->GetMotionMaster()->Clear();
        me->GetMotionMaster()->MoveIdle();

        Position pos = me->GetPosition();
        float mapHeight = me->GetMap()->GetHeight(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), true, 150.f);

        pos.m_positionZ += 2.5f;
        me->NearTeleportTo(pos);
        pos.m_positionZ = mapHeight;

        if (Creature* trigger = me->SummonCreature(NPC_BOSS_SIX_BEAM_TRIGGER, pos))
        {
            trigger->SetCanFly(true);
            trigger->SetDisableGravity(true);
            trigger->SetPassive();
            trigger->SetImmuneToPC(true);

            me->CastSpell(trigger, SPELL_DIABLO_EYE_BEAM, true);
            if (Aura* aura = trigger->GetAura(SPELL_DIABLO_EYE_BEAM))
            {
                aura->SetMaxDuration(25000);
                aura->RefreshDuration();
            }

            if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0U))
                HandleTriggerCharge(trigger, target);
        }
    }

    void HandleFireElementals()
    {
        for (uint32 i = 0; i < 5; ++i)
        {
            Position pos = Trinity::Containers::SelectRandomContainerElement(_diabloRandomSpawnPositions);
            me->SummonCreature(NPC_BOSS_SIX_UNSTABLE_FIRE_ELEMENTAL, pos);
        }
    }

private:
    bool _intro;
    uint32 _pentagramIndex;
    std::vector<uint64> _pentagramTriggerGUIDs;
    std::vector<uint64> _jumperGUIDs;
    uint64 _shadowRealmTargetGUID;
    bool _elementalPhase;
    bool _intermission;
};

enum DemonSpells
{
    SPELL_DEMON_REFLECT_SPELLS              = 35158,
    SPELL_DEMON_SHADOW_NOVA                 = 51073, // radius_mod 8000 and damage of 5k config
    SPELL_DEMON_NETHER_POWER                = 67108
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_flying_demon_AI : public ScriptedAI
{
    npc_boss_six_flying_demon_AI(Creature* creature) : ScriptedAI(creature)
    {
        _reflectingDemonType = false;
    }

    void Reset() override
    {
        _scheduler.CancelAll();
        ScriptedAI::Reset();
    }

    void SetData(uint32 type, uint32 value)
    {
        if (type == DATA_SET_DEMON_TYPE)
        {
            if (!value)
                _reflectingDemonType = true;
        }
        else if (type == DATA_SWITCH_DEMON_TYPE)
        {
            me->RemoveAurasDueToSpell(SPELL_DEMON_REFLECT_SPELLS);
            _reflectingDemonType = !_reflectingDemonType;
        }

        ScheduleCombatEvents();
    }

    void ScheduleCombatEvents()
    {
        _scheduler.CancelGroup(GROUP_DEMON_SWITCHABLE);
        if (_reflectingDemonType)
        {
            DoCastSelf(SPELL_DEMON_REFLECT_SPELLS, true);
            if (Aura* aura = me->GetAura(SPELL_DEMON_REFLECT_SPELLS))
            {
                aura->SetCharges(0);
                aura->SetMaxDuration(-1);
                aura->RefreshDuration();
            }
        }
        else
        {
            _scheduler.Schedule(5s, GROUP_DEMON_SWITCHABLE, [this](TaskContext func)
            {
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 8000); // config
                val.AddSpellMod(SPELLVALUE_BASE_POINT0, 5000/*config*/);
                me->CastCustomSpell(SPELL_DEMON_SHADOW_NOVA, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
                func.Repeat(1s);
            });
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);
        _scheduler.Schedule(20s, [this](TaskContext func)
        {
            SetData(DATA_SWITCH_DEMON_TYPE, DATA_SWITCH_DEMON_TYPE);
            func.Repeat(20s);
        });

        _scheduler.Schedule(2s, [this](TaskContext func)
        {
            std::list<Creature*> _demons;
            me->GetCreatureListWithEntryInGrid(_demons, me->GetEntry(), 20.f/*config*/);
            _demons.remove_if([this](Creature* ref)
            {
                return ref->GetGUID() == me->GetGUID();
            });

            if (!_demons.empty())
            {
                DoCastSelf(SPELL_DEMON_NETHER_POWER, true);
                if (Aura* aura = me->GetAura(SPELL_DEMON_NETHER_POWER))
                {
                    aura->SetMaxDuration(-1);
                    aura->RefreshDuration();
                }
            }

            func.Repeat(2s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
        DoMeleeAttackIfReady();
    }
private:
    TaskScheduler _scheduler;
    bool _reflectingDemonType;
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_beam_trigger : public ScriptedAI
{
    npc_boss_six_beam_trigger(Creature* creature) : ScriptedAI(creature) { }

    void MoveInLineOfSight(Unit* who) override { }
    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
};

struct npc_boss_six_beam_trigger_explosion : public ScriptedAI
{
    npc_boss_six_beam_trigger_explosion(Creature* creature) : ScriptedAI(creature)
    {
        _scheduler.CancelAll();
    }

    void MoveInLineOfSight(Unit* who) override { }
    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

    void SetData(uint32 type, uint32 value) override
    {
        if (type != DATA_EXPLOSION_TIMER)
            return;

        _scheduler.Schedule(std::chrono::milliseconds(value), [this](TaskContext func)
        {
            DoCastSelf(35470, true);
            DoCastSelf(69671, true);
        });
    }

private:
    TaskScheduler _scheduler;
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_diablo_playerclone : public ScriptedAI
{
    npc_boss_diablo_playerclone(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
    }

    void Reset() override { }
    void AttackStart(Unit* /*attacker*/) override { }
    void EnterCombat(Unit* /*who*/) override { }

    void IsSummonedBy(Unit* /*summoner*/) override
    {
        me->MonsterYell("Poprawic przerywanie aury przy wejsciu w combat/damage", LANG_UNIVERSAL, nullptr);
        _scheduler.CancelAll();
        DoZoneInCombat(me, 200.f);
#pragma message(CompileMessage "Zmienic ten grid search")
        _scheduler.Schedule(4s, [this](TaskContext func)
        {
            for (uint32 i = 0; i < 5/*config*/; ++i)
            {
                Player* player = me->SelectNearestPlayer(150.f);
                Creature* diablo = _instance->GetCreature(DATA_DIABLO);
                if (player && diablo)
                {
                    if (Creature* trigger = player->SummonCreature(NPC_BOSS_SIX_FIERY_COMET_TRIGGER, Trinity::Containers::SelectRandomContainerElement(_diabloRandomSpawnPositions)))
                    {
                        diablo->AI()->JustSummoned(trigger);
                        trigger->SetCanFly(true);
                        trigger->SetDisableGravity(true);
                        me->AI()->JustSummoned(trigger);
                        trigger->CastSpell(trigger, SPELL_DIABLO_SMOKEY_MARKER, true);
                    }
                }
            }
            func.Repeat(14s); // config
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    InstanceScript* _instance;
    TaskScheduler _scheduler;
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct go_click_me_diablo : public GameObjectAI
{
    go_click_me_diablo(GameObject* go) : GameObjectAI(go)
    {
        _instance = go->GetInstanceScript();
        _clicked = false;
    }

    bool GossipHello(Player* player, bool /*reportUse*/) override
    {
#pragma message(CompileMessage "tu ma sie spawnic clicker nad tym GO, ktory gracz musi clicknac")
        if (_clicked)
            return false;

        _clicked = true;
        //player->KnockbackFrom(go->GetPositionX(), go->GetPositionY(), 0.1f, 25.f);
        if (Creature* diablo = _instance->GetCreature(DATA_DIABLO))
            diablo->AI()->SetData(DATA_JUMPER_CLICKED, DATA_JUMPER_CLICKED);
        return false;
    }
private:
    InstanceScript* _instance;
    bool _clicked;
};

class spell_boss_diablo_nether_portal_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_diablo_nether_portal_AuraScript);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetTarget() && GetTarget()->GetMapId() == DIABLO_MAP_ID)
            PreventDefaultAction();
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_diablo_nether_portal_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_diablo_comet_trigger : public ScriptedAI
{
    npc_boss_diablo_comet_trigger(Creature* creature) : ScriptedAI(creature)
    {
        _instance = me->GetInstanceScript();
        _didSpawnInfernal = false;
        me->SetCanMissSpells(false);
    }

    void Reset() override
    {
        DoCastSelf(43467);
        me->SetSelectable(false);
        _scheduler.CancelAll();

        _scheduler.Schedule(10s, [this](TaskContext /*func*/)
        {
            Creature* diablo = _instance->GetCreature(DATA_DIABLO);
            if (diablo)
                diablo->CastSpell(me, 36837, true, NullItemRef, (AuraEffect*)nullptr, me->GetGUID());
        });

        me->DespawnOrUnsummon(20s);
    }

    void SetData(uint32 type, uint32 value) override
    {
#pragma message(CompileMessage "zmienic magic numbers")
        if (type == 52 && value)
            _didSpawnInfernal = true;
        //! if we didnt hit anything, spawn infernal
        else if (type == 51 && !_didSpawnInfernal)
        {
            Creature* diablo = _instance->GetCreature(DATA_DIABLO);
            diablo->SummonCreature(NPC_BOSS_SIX_DIABOLIC_INFERNAL, me->GetPosition());
            me->RemoveAllAuras();
        }

        me->DespawnOrUnsummon(4s);
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    InstanceScript* _instance;
    TaskScheduler _scheduler;
    bool _didSpawnInfernal;
};

class spell_boss_six_diablo_meteor : public SpellScript
{
    PrepareSpellScript(spell_boss_six_diablo_meteor);

    //! this executes after BeforeBHit()
    //! BeforeBHit sets a value in trigger script
    //! and HandleHit informs trigger that effect was executed
    //! and we then check if BeforeBHit was ever true
    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        Unit* oCaster = GetOriginalCaster();
        if (oCaster && oCaster->IsCreature())
            oCaster->ToCreature()->AI()->SetData(51, 51);
    }


    void BeforeBHit()
    {
        if (Player* target = GetHitPlayer())
            GetOriginalCaster()->ToCreature()->AI()->SetData(52, uint32(true));
    }

    void Register() override
    {
        BeforeHit += SpellHitFn(spell_boss_six_diablo_meteor::BeforeBHit);
        OnEffectHit += SpellEffectFn(spell_boss_six_diablo_meteor::HandleHit, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
    }
};

#pragma message(CompileMessage "przerzucic wszystkie timery i wartosci do hellforge_boss_stats")
struct npc_boss_six_diabolic_infernal : public NullCreatureAI
{
    npc_boss_six_diabolic_infernal(Creature* creature) : NullCreatureAI(creature) { }

    void DamageTaken(Unit* /*att*/, uint32& damage, DamageEffectType /*type*/, SpellSchoolMask /*mask*/) override
    {
        damage = 0;
    }

    void Reset() override
    {
        me->SetSelectable(false);
        _scheduler.CancelAll();
        _scheduler.Schedule(2s, [this](TaskContext func)
        {
            if (!me->IsCasting())
            {
                //! change radius of trigger spell
                CustomSpellValues val;
                val.AddSpellMod(SPELLVALUE_BASE_POINT1, 0);
                me->CastCustomSpell(68147, val, (Unit*)nullptr, TRIGGERED_IGNORE_POWER_AND_REAGENT_COST);
            }

            func.Repeat(4s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }

private:
    TaskScheduler _scheduler;
};

struct npc_boss_six_increased_damage_trigger : public NullCreatureAI
{
    npc_boss_six_increased_damage_trigger(Creature* creature) : NullCreatureAI(creature)
    {
        _scheduler.ClearValidator();
        _heartBeamTargetGUID = 0;
        me->SetCanMissSpells(false);
    }

    void Reset() override
    {
        DoCastSelf(54111);
        _scheduler.CancelAll();
        me->SetSelectable(false);
        _scheduler.Schedule(3s, [this](TaskContext func)
        {
            _playerNearby = false;
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            me->CastCustomSpell(56543, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

#pragma message(CompileMessage "Ten szajs sie nie refreshuje poprawnie jezeli zmienimy castera - retest")
            val.AddSpellMod(SPELLVALUE_AURA_DURATION, 35000);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 5000); // config
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 1); // 1/1000 = 0.0001 | base radius of 50,000 * 0.0001 equals 5 yards radius
            me->CastCustomSpell(SPELL_DIABLO_FLAME_BUFFET, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);

            _scheduler.Schedule(1s, [this](TaskContext /*func*/)
            {
                if (_playerNearby)
                {
                    if (Creature* clone = ObjectAccessor::GetCreature(*me, _heartBeamTargetGUID))
                    {
                        if (!me->IsCasting())
                        {
                            CustomSpellValues val;
                            val.AddSpellMod(SPELLVALUE_AURA_DURATION, 30000);
                            val.AddSpellMod(SPELLVALUE_SPELL_RANGE, 100.f);
                            me->CastCustomSpell(64668, val, clone, TRIGGERED_FULL_MASK);
                        }
                    }
                }
                else
                    me->CastStop();
            });

            func.Repeat(3s);
        });
    }

    void SpellHitTarget(Unit* who, SpellInfo const* spellInfo) override
    {
        if (spellInfo->Id == 56543 && who && who->IsPlayer())
            _playerNearby = true;
    }

    void SetGUID(uint64 guid, int32 /*data*/) override
    {
        _heartBeamTargetGUID = guid;
    }

    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    TaskScheduler _scheduler;
    uint64 _heartBeamTargetGUID;
    bool _playerNearby;
};

class spell_five_finger_death_punch : public SpellScript
{
    PrepareSpellScript(spell_five_finger_death_punch);

    void HandleHit(SpellEffIndex /*effIndex*/)
    {
        if (!GetHitUnit())
            return;

        Aura* aura = GetHitUnit()->GetAura(GetSpellInfo()->Id);
        if (!aura)
            return;

        if (aura->GetStackAmount() >= 5)
        {
#pragma message(CompileMessage "wyjebac magiczne liczby z calego pliku")
            GetHitUnit()->CastSpell(GetHitUnit(), 27676, true);
            GetHitUnit()->RemoveAurasDueToSpell(GetSpellInfo()->Id);
            if (GetHitUnit()->GetMapId() == 249/*onyxias lair*/)
            {
                GetHitUnit()->CastSpell(GetHitUnit(), 20478, true);
                if (InstanceScript* instance = GetHitUnit()->GetInstanceScript())
                {
                    if (Creature* diablo = instance->GetCreature(DATA_DIABLO))
                        diablo->getThreatManager().modifyThreatPercent(GetHitUnit(), -100);
                }
            }
        }
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_five_finger_death_punch::HandleHit, EFFECT_0, SPELL_EFFECT_APPLY_AURA);
    }
};

class spell_boss_diablo_armageddon_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_boss_diablo_armageddon_AuraScript);

    void OnPeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetTarget() && GetTarget()->GetMapId() == 249)
        {
            PreventDefaultAction();
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_RADIUS_MOD, 6666);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 500000/*config*/);
            val.AddSpellMod(SPELLVALUE_TARGET_PLAYERS_ONLY, 1);
            GetTarget()->CastCustomSpell(SPELL_DIABLO_RUNE_DETONATION, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_boss_diablo_armageddon_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
    }
};

class spell_buffeting_winds_diablo : public AuraScript
{
    PrepareAuraScript(spell_buffeting_winds_diablo);

    void OnEffectRemoved(AuraEffect const* aurEff, AuraEffectHandleModes mode)
    {
        if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_DEFAULT && GetTarget() && GetTarget()->GetMapId() == 249)
        {
            //59798
            CustomSpellValues val;
            val.AddSpellMod(SPELLVALUE_ENABLE_SHARE_DAMAGE, 1);
            val.AddSpellMod(SPELLVALUE_BASE_POINT0, 50000);
            GetTarget()->CastCustomSpell(59798, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
        }
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_buffeting_winds_diablo::OnEffectRemoved, EFFECT_0, SPELL_AURA_SAFE_FALL, AURA_EFFECT_HANDLE_REAL);
    }
};

struct npc_boss_diablo_fire_elementals : public NullCreatureAI
{
    npc_boss_diablo_fire_elementals(Creature* creature) : NullCreatureAI(creature) { }

    void Reset() override
    {
        me->SetSpeedRate(MOVE_RUN, 0.3f);
        me->SetSpeedRate(MOVE_WALK, 0.3f);
        me->SetWalk(true);

        _scheduler.CancelAll();
        if (Unit* target = me->GetSummoner())
        {
            float angle = me->GetAngle(target->GetPositionX(), target->GetPositionY());
            me->GetMotionMaster()->MoveFollow(target, 0.2f, angle, MOTION_SLOT_CONTROLLED);
        }

        _scheduler.Schedule(5s, [this](TaskContext func)
        {
            bool _repeat = true;
            if (Unit* target = me->GetSummoner())
            {
                if (target->GetDistance2d(me) <= 0.5f)
                {
                    me->MonsterYell("DOSZEDLEM DO BOSSA, DESPAWN. Nie ma dmg, znalezc spell, ile ma bic", LANG_UNIVERSAL, nullptr);
                    JustDied(target);
                    me->DespawnOrUnsummon(1s);
                    _repeat = false;
                }
            }

            if (_repeat)
            {
                me->DealDamage(me, me, me->GetMaxHealth() * 0.1);
                func.Repeat(2s);
            }
        });
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void UpdateAI(uint32 diff) override
    {
        _scheduler.Update(diff);
    }
private:
    TaskScheduler _scheduler;
};

void AddSC_hellforge_boss_six()
{
    new CreatureAILoader<npc_boss_six_diablo_AI>("npc_boss_six_diablo");
    new CreatureAILoader<npc_boss_six_flying_demon_AI>("npc_boss_six_flying_demon");
    new CreatureAILoader<npc_boss_six_beam_trigger>("npc_boss_six_beam_trigger");
    new CreatureAILoader<npc_boss_six_beam_trigger_explosion>("npc_boss_six_beam_trigger_explosion");
    new CreatureAILoader<npc_boss_diablo_playerclone>("npc_boss_diablo_playerclone");
    new CreatureAILoader<npc_boss_diablo_comet_trigger>("npc_boss_diablo_comet_trigger");
    new CreatureAILoader<npc_boss_six_diabolic_infernal>("npc_boss_six_diabolic_infernal");
    new CreatureAILoader<npc_boss_six_increased_damage_trigger>("npc_boss_six_increased_damage_trigger");
    new CreatureAILoader<npc_boss_diablo_fire_elementals>("npc_boss_diablo_fire_elementals");
    new GameObjectAILoader<go_click_me_diablo>("go_click_me_diablo");

    new AuraScriptLoaderEx<spell_boss_diablo_nether_portal_AuraScript>("spell_boss_diablo_nether_portal");
    new SpellScriptLoaderEx<spell_boss_six_diablo_meteor>("spell_boss_six_diablo_meteor");
    new SpellScriptLoaderEx<spell_five_finger_death_punch>("spell_five_finger_death_punch");
    new AuraScriptLoaderEx<spell_boss_diablo_armageddon_AuraScript>("spell_boss_diablo_armageddon");
    new AuraScriptLoaderEx<spell_buffeting_winds_diablo>("spell_buffeting_winds_diablo");
}
