/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "ulduar.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "Player.h"

#include <cmath>

#define BASE_CAMP    200
#define GROUNDS      201
#define FORGE        202
#define SCRAPYARD    203
#define ANTECHAMBER  204
#define WALKWAY      205
#define CONSERVATORY 206
#define MADNESS         207
#define SPARK         208

class go_ulduar_teleporter : public GameObjectScript
{
public:
    go_ulduar_teleporter() : GameObjectScript("ulduar_teleporter") { }

    bool OnGossipHello(Player* player, GameObject* go)
    {
        InstanceScript* pInstance = go->GetInstanceScript();
        if (!pInstance)
            return true;

        player->ADD_GOSSIP_ITEM(0, "Teleport to the Expedition Base Camp.", GOSSIP_SENDER_MAIN, BASE_CAMP);
        if (pInstance->GetData(TYPE_LEVIATHAN) >= DONE) // count special
        {
            player->ADD_GOSSIP_ITEM(0, "Teleport to the Formation Grounds.", GOSSIP_SENDER_MAIN, GROUNDS);
            if (pInstance->GetData(TYPE_LEVIATHAN) == DONE)
            {
                player->ADD_GOSSIP_ITEM(0, "Teleport to the Colossal Forge.", GOSSIP_SENDER_MAIN, FORGE);
                if (pInstance->GetData(TYPE_XT002) == DONE)
                {
                    player->ADD_GOSSIP_ITEM(0, "Teleport to the Scrapyard.", GOSSIP_SENDER_MAIN, SCRAPYARD);
                    player->ADD_GOSSIP_ITEM(0, "Teleport to the Antechamber of Ulduar.", GOSSIP_SENDER_MAIN, ANTECHAMBER);
                    if (pInstance->GetData(TYPE_KOLOGARN) == DONE)
                    {
                        player->ADD_GOSSIP_ITEM(0, "Teleport to the Shattered Walkway.", GOSSIP_SENDER_MAIN, WALKWAY);
                        if (pInstance->GetData(TYPE_AURIAYA) == DONE)
                        {
                            player->ADD_GOSSIP_ITEM(0, "Teleport to the Conservatory of Life.", GOSSIP_SENDER_MAIN, CONSERVATORY);
                            if (pInstance->GetData(DATA_CALL_TRAM))
                                player->ADD_GOSSIP_ITEM(0, "Teleport to the Spark of Imagination.", GOSSIP_SENDER_MAIN, SPARK);
                            if (pInstance->GetData(TYPE_VEZAX) == DONE)
                                player->ADD_GOSSIP_ITEM(0, "Teleport to the Prison of Yogg-Saron.", GOSSIP_SENDER_MAIN, MADNESS);
                        }
                    }
                }
            }
        }

        player->SEND_GOSSIP_MENU(14424, go->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action)
    {
        if (sender != GOSSIP_SENDER_MAIN || !player->getAttackers().empty())
            return true;

        if (player->HasAuraType(SPELL_AURA_MOUNTED))
            player->RemoveAurasByType(SPELL_AURA_MOUNTED);

        switch (action)
        {
            case BASE_CAMP:
                player->TeleportTo(603, -706.122f, -92.6024f, 429.876f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
            case GROUNDS:
                player->TeleportTo(603, 131.248f, -35.3802f, 409.804f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
            case FORGE:
                player->TeleportTo(603, 553.233f, -12.3247f, 409.679f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
            case SCRAPYARD:
                player->TeleportTo(603, 926.292f, -11.4635f, 418.595f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
            case ANTECHAMBER:
                player->TeleportTo(603, 1498.09f, -24.246f, 420.967f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
            case WALKWAY:
                player->TeleportTo(603, 1859.45f, -24.1f, 448.9f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
            case CONSERVATORY:
                player->TeleportTo(603, 2086.27f, -24.3134f, 421.239f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
            case MADNESS:
                player->TeleportTo(603, 1854.8f, -11.46f, 334.57f, 4.8f);
                player->CLOSE_GOSSIP_MENU(); break;
            case SPARK:
                player->TeleportTo(603, 2517.9f, 2568.9f, 412.7f, 0);
                player->CLOSE_GOSSIP_MENU(); break;
        }

        return true;
    }
};

class npc_ulduar_keeper : public CreatureScript
{
public:
    npc_ulduar_keeper() : CreatureScript("npc_ulduar_keeper_gossip") { }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Lend us your aid, keeper. Together we shall defeat Yogg-Saron.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(DEFAULT_GOSSIP_MESSAGE, pCreature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 uiSender, uint32 uiAction)
    {
        creature->SetUInt32Value(UNIT_NPC_FLAGS, 0);
        uint8 _keeper = 0;
        switch (creature->GetEntry())
        {
            case NPC_FREYA_GOSSIP:
                creature->MonsterYell("Eonar, your servant calls for your blessing!", LANG_UNIVERSAL, 0);
                creature->PlayDirectSound(15535);
                _keeper = KEEPER_FREYA;
                break;
            case NPC_HODIR_GOSSIP:
                creature->MonsterYell("The veil of winter will protect you, champions!", LANG_UNIVERSAL, 0);
                creature->PlayDirectSound(15559);
                _keeper = KEEPER_HODIR;
                break;
            case NPC_MIMIRON_GOSSIP:
                creature->MonsterYell("Combat matrix enhanced. Behold wonderous rapidity!", LANG_UNIVERSAL, 0);
                creature->PlayDirectSound(15630);
                _keeper = KEEPER_MIMIRON;
                break;
            case NPC_THORIM_GOSSIP:
                creature->MonsterYell("Golganneth, lend me your strengh! Grant my mortal allies the power of thunder!", LANG_UNIVERSAL, 0);
                creature->PlayDirectSound(15750);
                _keeper = KEEPER_THORIM;
                break;
        }

        if (creature->GetInstanceScript())
        {
            creature->GetInstanceScript()->SetData(TYPE_WATCHERS, _keeper);
            creature->DespawnOrUnsummon(6000);
        }

        return true;
    }
};

class spell_ulduar_energy_sap : public SpellScriptLoader
{
public:
    spell_ulduar_energy_sap() : SpellScriptLoader("spell_ulduar_energy_sap") { }

    class spell_ulduar_energy_sap_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ulduar_energy_sap_AuraScript)

        void HandleEffectPeriodic(AuraEffect const * aurEff)
        {
            if (Unit* target = GetTarget())
                target->CastSpell(target, (aurEff->GetId() == 64740) ? 64747 : 64863, true);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ulduar_energy_sap_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_ulduar_energy_sap_AuraScript();
    }
};

enum SnowMound
{
    NPC_WHITE_JORMUNGAR         = 34137,
    NPC_SNOW_MOUND_4            = 34146,
    NPC_SNOW_MOUND_6            = 34150,
    NPC_SNOW_MOUND_8            = 34151,

    SPELL_SNOW_MOUND_PARTICLE   = 64615
};

struct npc_ulduar_snow_mound : public ScriptedAI
{
    npc_ulduar_snow_mound(Creature* creature) : ScriptedAI(creature)
    {
        DoCastSelf(SPELL_SNOW_MOUND_PARTICLE);
        _spawnJormungars = true;
    }

    void AttackStart(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }

    void MoveInLineOfSight(Unit* who) override
    {
        if (_spawnJormungars && who->IsPlayer() && !who->ToPlayer()->IsGameMaster() && who->IsWithinDistInMap(me, 5.f))
        {
            _spawnJormungars = false;
            uint32 jormungarCount = 8;

            if (me->GetEntry() == NPC_SNOW_MOUND_4)
                jormungarCount = 4;
            else if (me->GetEntry() == NPC_SNOW_MOUND_6)
                jormungarCount = 6;
            else if (me->GetEntry() == NPC_SNOW_MOUND_8)
                jormungarCount = 8;

            float const angleStep = static_cast<float>(2 * M_PI) / jormungarCount;
            float currentAngle = 0.f;
            Position spawnAt = me->GetPosition();
            for (uint32 i = 0; i < jormungarCount; ++i)
            {
                Creature* jormungar = me->SummonCreature(NPC_WHITE_JORMUNGAR, spawnAt);
                if (jormungar)
                {
                    Position jumpPosition = spawnAt;
                    jumpPosition.m_positionX = spawnAt.GetPositionX() + 3.5f * cosf(currentAngle);
                    jumpPosition.m_positionY = spawnAt.GetPositionY() + 3.5f * sinf(currentAngle);
                    jumpPosition.m_positionZ = jormungar->GetMap()->GetWaterOrGroundLevel(jormungar->GetPhaseMask(), jumpPosition.GetPositionX(), jumpPosition.GetPositionY(), jumpPosition.GetPositionZ());
                    currentAngle += angleStep;
                    jormungar->GetMotionMaster()->MoveJump(jumpPosition, 10.f, 10.f);
                    jormungar->SetHomePosition(jumpPosition);
                }
            }

            me->RemoveAurasDueToSpell(SPELL_SNOW_MOUND_PARTICLE);
            if (GameObject* go = me->FindNearestGameObject(GO_SNOW_MOUND, 5.0f))
                go->SetLootState(GO_JUST_DEACTIVATED);
            me->DespawnOrUnsummon(1500ms);
        }
    }

private:
    bool _spawnJormungars;
};

enum WhiteJormungar
{
    SPELL_JORMUNGAR_ACIDIC_BITE    = 64638
};

struct npc_white_jormungar_ulduar : public ScriptedAI
{
    npc_white_jormungar_ulduar(Creature* creature) : ScriptedAI(creature)
    {
        me->SetImmuneToAll(true);
        _jumped = false;
    }

    void Reset() override
    {
        task.CancelAll();
        if (!_jumped)
        {
            _jumped = true;
            task.Schedule(1500ms, [&](TaskContext /*func*/)
            {
                me->SetImmuneToAll(false);
                DoZoneInCombat(me, 100.f);
            });
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);
        task.Schedule(1s, [&](TaskContext func)
        {
            if (me->GetVictim())
                DoCastVictim(SPELL_JORMUNGAR_ACIDIC_BITE);
            func.Repeat(3s, 5s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        task.Update(diff);
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }

private:
    TaskScheduler task;
    bool _jumped;
};

enum storm_tempered_keeper
{
    NPC_STORM_TEMPERED_KEEPER_R    = 33722,
    NPC_STORM_TEMPERED_KEEPER_L    = 33699,
    NPC_CHARGED_SPHERE             = 33715,

    SPELL_VENGEFUL_SURGE           = 63630,
    SPELL_SEPARATION_ANXIETY       = 63539,
    SPELL_SUPERCHARGED             = 63528,
    SPELL_FORKED_LIGHTNING         = 63541,
    SPELL_SUMMON_CHARGED_SPHERE    = 63527
};

class npc_ulduar_storm_tempered_keeper : public CreatureScript
{
public:
    npc_ulduar_storm_tempered_keeper() : CreatureScript("npc_ulduar_storm_tempered_keeper") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_storm_tempered_keeperAI(pCreature);
    }

    struct npc_ulduar_storm_tempered_keeperAI : public ScriptedAI
    {
        npc_ulduar_storm_tempered_keeperAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            otherGUID = 0;
        }

        EventMap events;
        uint64 otherGUID;

        void Reset()
        {
            events.Reset();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->GetEntry() == NPC_SWARMING_GUARDIAN)
                return;

            ScriptedAI::MoveInLineOfSight(who);
        }

        void EnterCombat(Unit* who)
        {
            events.Reset();
            events.ScheduleEvent(1, 2000); // checking Separation Anxiety, Charged Sphere
            events.ScheduleEvent(2, urand(5000,8000)); // Forked Lightning
            events.ScheduleEvent(3, (me->GetEntry() == NPC_STORM_TEMPERED_KEEPER_R ? 20000 : 50000)); // Summon Charged Sphere
            if (Creature* c = me->FindNearestCreature((me->GetEntry() == NPC_STORM_TEMPERED_KEEPER_R ? NPC_STORM_TEMPERED_KEEPER_L : NPC_STORM_TEMPERED_KEEPER_R), 30.0f, true))
            {
                if (c->IsAlive() && c->IsAIEnabled)
                    c->AI()->AttackStart(who);
                otherGUID = c->GetGUID();
            }
            else
                me->CastSpell(me, SPELL_VENGEFUL_SURGE, true); // Vengeful Surge
        }

        void JustDied(Unit* /*killer*/)
        {
            if (Creature* c = ObjectAccessor::GetCreature(*me, otherGUID))
                c->CastSpell(c, SPELL_VENGEFUL_SURGE, true); // Vengeful Surge
        }

        void JustSummoned(Creature* s)
        {
            if (Creature* c = ObjectAccessor::GetCreature(*me, otherGUID))
                s->GetMotionMaster()->MoveFollow(c, 0.0f, 0.0f);
        }

        void UpdateAI(uint32 diff)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case 0:
                    break;
                case 1:
                    if (Creature* c = ObjectAccessor::GetCreature(*me, otherGUID))
                        if (c->IsAlive() && me->GetExactDist2d(c) > 45.0f)
                            me->CastSpell(me, SPELL_SEPARATION_ANXIETY, true);
                    if (Creature* c = me->FindNearestCreature(NPC_CHARGED_SPHERE, 2.0f, true))
                        if (c->IsSummon())
                            if (c->ToTempSummon()->GetSummonerGUID() != me->GetGUID())
                            {
                                me->CastSpell(me, SPELL_SUPERCHARGED, true);
                                c->DespawnOrUnsummon();
                            }
                    events.RepeatEvent(2000);
                    break;
                case 2:
                    me->CastSpell(me->GetVictim(), SPELL_FORKED_LIGHTNING, false);
                    events.RepeatEvent(urand(10000,14000));
                    break;
                case 3:
                    if (!me->HasAura(SPELL_VENGEFUL_SURGE))
                        me->CastSpell(me, SPELL_SUMMON_CHARGED_SPHERE, false);
                    events.RepeatEvent(60000);
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

class npc_ulduar_arachnopod_destroyer : public CreatureScript
{
public:
    npc_ulduar_arachnopod_destroyer() : CreatureScript("npc_ulduar_arachnopod_destroyer") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_ulduar_arachnopod_destroyerAI(pCreature);
    }

    struct npc_ulduar_arachnopod_destroyerAI : public ScriptedAI
    {
        npc_ulduar_arachnopod_destroyerAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            _spawnedMechanic = false;
            me->ApplySpellImmune(0, IMMUNITY_ID, 64919, true); // Ice Nova from Ice Turret
        }

        EventMap events;
        bool _spawnedMechanic;

        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(1, urand(5000, 8000)); // Flame Spray
            events.ScheduleEvent(2, urand(3000, 6000)); // Machine Gun
            events.ScheduleEvent(3, 1000); // Charged Leap
        }

        void PassengerBoarded(Unit* p, int8 seat, bool apply)
        {
            me->setFaction(p->getFaction());
            me->SetReactState(REACT_PASSIVE);
        }

        void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask)
        {
            if (!_spawnedMechanic && me->HealthBelowPctDamaged(20, damage))
            {
                _spawnedMechanic = true;
                if (Creature* c = me->SummonCreature(34184, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation(), TEMPSUMMON_MANUAL_DESPAWN, 0))
                    c->AI()->AttackStart(me->GetVictim());
                me->InterruptNonMeleeSpells(false);
                me->CombatStop(true);
                me->SetReactState(REACT_PASSIVE);
                me->SetRegeneratingHealth(false);
                me->setFaction(31);
                me->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                me->CastSpell(me, 64770, true);
            }
        }

        void AttackStart(Unit* who)
        {
            if (me->getFaction() == 16)
                ScriptedAI::AttackStart(who);
        }

        void EnterEvadeMode()
        {
            if (me->getFaction() == 16)
                ScriptedAI::EnterEvadeMode();
        }

        void OnCharmed(bool apply) {}

        void UpdateAI(uint32 diff)
        {
            if (me->getFaction() != 16)
            {
                if (me->IsAlive() && (me->GetExactDist2dSq(2058.0f, 42.0f) < 25.0f*25.0f || me->GetExactDist2dSq(2203.0f, 292.0f) < 25.0f*25.0f || me->GetExactDist2dSq(2125.0f, 170.0f) > 160.0f*160.0f))
                    Unit::Kill(me, me, false);
            }
            else
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;

                switch (events.GetEvent())
                {
                    case 0:
                        break;
                    case 1:
                        me->CastSpell(me->GetVictim(), RAID_MODE(64717, 65241), false);
                        events.RepeatEvent(urand(15000, 25000));
                        break;
                    case 2:
                        me->CastSpell(me->GetVictim(), RAID_MODE(64776, 65240), false);
                        events.RepeatEvent(urand(10000, 15000));
                        break;
                    case 3:
                        {
                            float dist = me->GetDistance(me->GetVictim());
                            if (dist > 10.0f && dist < 40.0f)
                            {
                                me->CastSpell(me->GetVictim(), 64779, false);
                                events.RepeatEvent(25000);
                            }
                            else
                                events.RepeatEvent(3000);
                        }
                        break;
                }

                DoMeleeAttackIfReady();
            }
        }
    };
};

class spell_ulduar_arachnopod_damaged : public SpellScriptLoader
{
public:
    spell_ulduar_arachnopod_damaged() : SpellScriptLoader("spell_ulduar_arachnopod_damaged") { }

    class spell_ulduar_arachnopod_damaged_AuraScript : public AuraScript
    {
        PrepareAuraScript(spell_ulduar_arachnopod_damaged_AuraScript)

        void HandleEffectPeriodic(AuraEffect const * aurEff)
        {
            if (Unit* c = GetCaster())
                Unit::Kill(c, c, false);
        }

        void Register()
        {
            OnEffectPeriodic += AuraEffectPeriodicFn(spell_ulduar_arachnopod_damaged_AuraScript::HandleEffectPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_TRIGGER_SPELL);
        }
    };

    AuraScript *GetAuraScript() const
    {
        return new spell_ulduar_arachnopod_damaged_AuraScript();
    }
};

class AreaTrigger_at_celestial_planetarium_enterance : public AreaTriggerScript
{
    public:

        AreaTrigger_at_celestial_planetarium_enterance()
            : AreaTriggerScript("at_celestial_planetarium_enterance")
        {
        }

        bool OnTrigger(Player* player, AreaTriggerEntry const* /*trigger*/)
        {
            if (player->IsAlive())
                if (uint32 questId = (player->GetMap()->Is25ManRaid() ? 13816 : 13607 /*QUEST_CELESTIAL_PLANETARIUM*/))
                    if (player->GetQuestStatus(questId) == QUEST_STATUS_INCOMPLETE)
                        player->AreaExploredOrEventHappens(questId);
            return false;
        }
};

class go_call_tram : public GameObjectScript
{
public:
    go_call_tram() : GameObjectScript("go_call_tram") { }

    bool OnGossipHello(Player* /*pPlayer*/, GameObject* pGo)
    {
        InstanceScript* pInstance = pGo->GetInstanceScript();

        if (!pInstance)
            return false;

        switch(pGo->GetEntry())
        {
            case 194914:
            case 194438:
                pInstance->SetData(DATA_CALL_TRAM, 0);
                break;
            case 194912:
            case 194437:
                pInstance->SetData(DATA_CALL_TRAM, 1);
                break;
        }
        return true;
    }
};

uint32 const SPELL_BOMB_BOT_EXPLOSION_GAUNTLET = 63801;

struct npc_boomer_xp500_ulduar_AI : public ScriptedAI
{
    npc_boomer_xp500_ulduar_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        _exploded = false;
        _arcRunners = me->GetHomePosition().GetPositionZ() < 400.f;
    }

    void EnterCombat(Unit* who) override
    {
        if (!_arcRunners)
            ScriptedAI::EnterCombat(who);
    }

    void AttackStart(Unit* who) override
    {
        if (!_arcRunners)
            ScriptedAI::AttackStart(who);
    }

    void DamageDealt(Unit* who, uint32& /*damage*/, DamageEffectType /*damageType*/) override
    {
        if (!_arcRunners && who->IsPlayer())
            HandleExplosion();
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!_arcRunners)
        {
            ScriptedAI::MoveInLineOfSight(who);
            return;
        }

        if (who && who->ToPlayer() && !who->ToPlayer()->IsGameMaster() && who->IsWithinDist(me, 4.0f))
        {
            HandleExplosion();
        }
    }

    void HandleExplosion()
    {
        if (_exploded)
            return;

        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->StopMoving();
        me->SetReactState(REACT_PASSIVE);
        me->AttackStop();
        _exploded = true;
        me->DespawnOrUnsummon(3s);
        DoCastAOE(SPELL_BOMB_BOT_EXPLOSION_GAUNTLET, true);
    }
private:
    //! check wheter they're running outside of the mimiron room
    //! or just trash to mimiron (before mimirons tram) | false means they're not runners
    bool _arcRunners;
    bool _exploded;
};

constexpr uint32 SPELL_UNQUENCHABLE_FLAMES_AOE{ 64706 };
constexpr uint32 NPC_IGNIS_WATER_TRIGGER{ 22515 };
class spell_unquenchable_flames : public AuraScript
{
    PrepareAuraScript(spell_unquenchable_flames);

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        switch (GetTargetApplication()->GetRemoveMode())
        {
            case AURA_REMOVE_BY_ENEMY_SPELL:
            case AURA_REMOVE_BY_EXPIRE:
            case AURA_REMOVE_BY_DEATH:
                break;
            default:
                return;
        }

        CustomSpellValues val;
        val.AddSpellMod(SPELLVALUE_MAX_TARGETS, 1);
        GetTarget()->CastCustomSpell(SPELL_UNQUENCHABLE_FLAMES_AOE, val, (Unit*)nullptr, TRIGGERED_FULL_MASK);
    }

    void HandlePeriodic(AuraEffect const* /*aurEff*/)
    {
        if (GetTarget() && GetTarget()->FindNearestCreature(NPC_IGNIS_WATER_TRIGGER, 18.0f, true))
            Remove(AURA_REMOVE_BY_CANCEL);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_unquenchable_flames::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE_PERCENT, AURA_EFFECT_HANDLE_REAL);
        OnEffectPeriodic += AuraEffectPeriodicFn(spell_unquenchable_flames::HandlePeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE_PERCENT);
    }
};

enum MechagnomeBattletank
{
    SPELL_MECHAGNOME_JUMPATTACK         = 64953,
    SPELL_MECHAGNOME_FLAME_CANNON       = 64692
};

struct npc_mechagnome_battletank : public ScriptedAI
{
    npc_mechagnome_battletank(Creature* creature) : ScriptedAI(creature)
    {
        me->m_SightDistance = 150.f;
    }

    void Reset() override
    {
        ScriptedAI::Reset();
        scheduler.CancelAll();
        //me->GetMotionMaster()->MoveRandom(0.3f);
    }

    bool CanSeeAlways(WorldObject const* /*obj*/) override
    {
        return true;
    }

    void MoveInLineOfSight(Unit* who) override
    {
        if (!me->IsInCombat() && who && !me->IsFriendlyTo(who) && me->GetDistance(who) < 150.f && me->CanCreatureAttack(who, true))
        {
            DoZoneInCombat(me, 300.f);
            AttackStart(who);
        }
    }

    void EnterCombat(Unit* who) override
    {
        ScriptedAI::EnterCombat(who);

        scheduler.Schedule(1s, [&](TaskContext func)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 150.f, true))
                DoCast(target, SPELL_MECHAGNOME_JUMPATTACK, true);

            func.Repeat(10s, 15s);
        }).Schedule
        (3s, [&](TaskContext func)
        {
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200.f, true))
                DoCast(target, SPELL_MECHAGNOME_FLAME_CANNON, true);

            func.Repeat(3s, 6s);
        });
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        scheduler.Update(diff);
        DoMeleeAttackIfReady();
    }
private:
    TaskScheduler scheduler;
};

enum SuperHeatedEnum
{
    SPELL_SUPERHEATED_WINDS_PERIODIC = 64724,

    POINT_MOVE_SUPERHEATED_WINDS     = 1
};

struct npc_superheated_winds : public ScriptedAI
{
    npc_superheated_winds(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        task.CancelAll();
        task.Schedule(500ms, [&](TaskContext func)
        {
            DoCastSelf(SPELL_SUPERHEATED_WINDS_PERIODIC, true);
        }).Schedule(1500ms, [&](TaskContext func)
        {
            me->GetMotionMaster()->MovePoint(POINT_MOVE_SUPERHEATED_WINDS, GetRandomMovePosition());
        });
    }

    void MovementInform(uint32 type, uint32 pointId) override
    {
        if (type == POINT_MOTION_TYPE && pointId == POINT_MOVE_SUPERHEATED_WINDS)
            task.Schedule(5s, [&](TaskContext func)
        {
            me->GetMotionMaster()->MovePoint(POINT_MOVE_SUPERHEATED_WINDS, GetRandomMovePosition());
        });
    }

    Position const GetRandomMovePosition()
    {
        Creature* summoner = me->GetSummoner();
        if (summoner && summoner->IsAIEnabled && summoner->IsInCombat())
        {
            Unit* target = summoner->AI()->SelectTarget(SELECT_TARGET_TOPAGGRO, 0U, 0.f, true);
            if (target)
                return me->GetNearPositionFromPos(target->GetPosition(), 2.5f);
        }

        return me->GetNearPositionFromPos(me->GetPosition(), 5.f);
    }

    void UpdateAI(uint32 diff) override
    {
        task.Update(diff);
    }

    void AttackStart(Unit* /*who*/) override { }
    void MoveInLineOfSight(Unit* /*who*/) override { }

private:
    TaskScheduler task;
};

enum RavagerThundererMisc
{
    SPELL_THUNDERER_LIGHTNING_BRAND     = 63610,
    SPELL_RAVAGER_RAVAGE_ARMOR          = 63616,

    NPC_DARK_RUNE_THUNDERER_TRASH       = 33754
};

struct npc_dark_rune_ravager_thunderer : public ScriptedAI
{
    npc_dark_rune_ravager_thunderer(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        uint32 spellId = me->GetEntry() == NPC_DARK_RUNE_THUNDERER_TRASH ?
            SPELL_THUNDERER_LIGHTNING_BRAND : SPELL_RAVAGER_RAVAGE_ARMOR;
        me->RemoveAurasDueToSpell(spellId);
        DoCastSelf(spellId, true);
    }
};

void AddSC_ulduar()
{
    RegisterCreatureAI(npc_superheated_winds);
    RegisterCreatureAI(npc_ulduar_snow_mound);
    RegisterCreatureAI(npc_white_jormungar_ulduar);
    RegisterCreatureAI(npc_dark_rune_ravager_thunderer);
    new go_ulduar_teleporter();
    new npc_ulduar_keeper();

    new spell_ulduar_energy_sap();
    new npc_ulduar_storm_tempered_keeper();
    new npc_ulduar_arachnopod_destroyer();
    new spell_ulduar_arachnopod_damaged();

    new AreaTrigger_at_celestial_planetarium_enterance();
    new go_call_tram();

    new CreatureAILoader<npc_boomer_xp500_ulduar_AI>("npc_boomer_xp500_ulduar");
    new AuraScriptLoaderEx<spell_unquenchable_flames>("spell_unquenchable_flames");
    new CreatureAILoader<npc_mechagnome_battletank>("npc_mechagnome_battletank");
}
