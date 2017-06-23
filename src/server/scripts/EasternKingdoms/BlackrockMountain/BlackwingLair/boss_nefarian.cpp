#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "ScriptedCreature.h"
#include "blackwing_lair.h"
#include "Player.h"

enum Events
{
    // Victor Nefarius
    EVENT_SPAWN_ADD             = 1,
    EVENT_SHADOW_BOLT,
    EVENT_SHADOW_BOLT_VOLLEY,
    EVENT_FEAR,
    EVENT_MIND_CONTROL,
    EVENT_SILENCE,
    EVENT_SHADOWBLINK,
    EVENT_BEGIN_FIGHT,
    // Nefarian
    EVENT_SHADOWFLAME,
    EVENT_VEILOFSHADOW,
    EVENT_CLEAVE,
    EVENT_TAILLASH,
    EVENT_CLASSCALL,
    // UBRS
    EVENT_CHAOS_1,
    EVENT_CHAOS_2,
    EVENT_PATH_2,
    EVENT_PATH_3,
    EVENT_SUCCESS_1,
    EVENT_SUCCESS_2,
    EVENT_SUCCESS_3
};

enum Says
{
    // Nefarius
    // UBRS
    SAY_CHAOS_SPELL             = 9,
    SAY_SUCCESS,
    SAY_FAILURE,
    // BWL
    SAY_GAMESBEGIN_1,
    SAY_GAMESBEGIN_2,

    // Nefarian
    SAY_AGGRO                   = 0,
    SAY_XHEALTH,
    SAY_SHADOWFLAME,
    SAY_RAISE_SKELETONS,
    SAY_SLAY,
    SAY_DEATH,
    SAY_MAGE,
    SAY_WARRIOR,
    SAY_DRUID,
    SAY_PRIEST,
    SAY_PALADIN,
    SAY_SHAMAN,
    SAY_WARLOCK,
    SAY_HUNTER,
    SAY_ROGUE,
    SAY_DEATH_KNIGHT
};

enum Gossip
{
    GOSSIP_ID                   = 21332,
    GOSSIP_OPTION_ID            = 0
};

enum Paths
{
    NEFARIUS_PATH_2             = 1379671,
    NEFARIUS_PATH_3             = 1379672
};

enum GameObjects
{
    GO_PORTCULLIS_ACTIVE        = 164726,
    GO_PORTCULLIS_TOBOSSROOMS   = 175186,
    GO_CONSTRUCT_BONES          = 179804
};

enum Creatures
{
    NPC_BRONZE_DRAKANOID        = 14263,
    NPC_BLUE_DRAKANOID          = 14261,
    NPC_RED_DRAKANOID           = 14264,
    NPC_GREEN_DRAKANOID         = 14262,
    NPC_BLACK_DRAKANOID         = 14265,
    NPC_CHROMATIC_DRAKANOID     = 14302,
    NPC_BONE_CONSTRUCT          = 14605,
    // UBRS
    NPC_GYTH                    = 10339
};

enum Spells
{
    // Victor Nefarius
    // UBRS Spells
    SPELL_CHROMATIC_CHAOS       = 16337, 
    SPELL_VAELASTRASZZ_SPAWN    = 16354, 
    // BWL Spells
    SPELL_SHADOWBOLT            = 22677,
    SPELL_SHADOWBOLT_VOLLEY     = 22665,
    SPELL_SHADOW_COMMAND        = 22667,
    SPELL_FEAR                  = 22678,
    SPELL_SILENCE               = 22666,
    SPELL_SHADOWBLINK           = 22681, 
    SPELL_SUMMON_DRAKONID_BONES = 23363,

    SPELL_NEFARIANS_BARRIER     = 22663,

    // Nefarian
    SPELL_SHADOWFLAME_INITIAL   = 22992,
    SPELL_SHADOWFLAME           = 22539,
    SPELL_BELLOWINGROAR         = 22686,
    SPELL_VEILOFSHADOW          = 7068,
    SPELL_CLEAVE                = 20691,
    SPELL_TAILLASH              = 23364,

    SPELL_MAGE                  = 23410, 
    SPELL_WARRIOR               = 23397, 
    SPELL_DRUID                 = 23398, 
    SPELL_PRIEST                = 23401, 
    SPELL_PALADIN               = 23418, 
    SPELL_SHAMAN                = 23425, 
    SPELL_WARLOCK               = 23427, 
    SPELL_HUNTER                = 23436, 
    SPELL_ROGUE                 = 23414, 
    SPELL_DEATH_KNIGHT          = 49576  
};

Position const DrakeSpawnLoc[2] = 
{
    { -7591.151855f, -1204.051880f, 476.800476f, 3.0f },
    { -7514.598633f, -1150.448853f, 476.796570f, 3.0f }
};

Position const NefarianLoc[2] =
{
    { -7498.177f, -1273.277f, 481.649f, 1.798f },               
    { -7502.002f, -1256.503f, 476.758f },                    
};

struct boss_victor_nefariusAI : public BossAI
{
    boss_victor_nefariusAI(Creature* creature) : BossAI(creature, DATA_LORD_VICTOR_NEFARIUS)
    {
        std::vector<uint32> adds = { NPC_BLUE_DRAKANOID, NPC_RED_DRAKANOID, NPC_GREEN_DRAKANOID, NPC_BLACK_DRAKANOID, NPC_BRONZE_DRAKANOID };
        _firstAdd = Trinity::Containers::SelectRandomContainerElement(adds);
        adds.erase(std::remove(adds.begin(), adds.end(), _firstAdd), adds.end());
        _secondAdd = Trinity::Containers::SelectRandomContainerElement(adds);
    }

    void Reset() override
    {
        std::list<GameObject*> constructBonesList;
        me->GetGameObjectListWithEntryInGrid(constructBonesList, GO_CONSTRUCT_BONES, 250.0f);
        if (!constructBonesList.empty())
            for (auto itr : constructBonesList)
                itr->Delete();

        _addsSpawned = 0;
        if (me->GetMapId() == 469)
        {
            if (!instance->GetCreature(DATA_NEFARIAN))
                _Reset();

            me->SetVisible(true);
            me->SetPhaseMask(1, true);
            me->SetUInt32Value(UNIT_NPC_FLAGS, 1);
            me->setFaction(35);
            me->SetStandState(UNIT_STAND_STATE_SIT_HIGH_CHAIR);
            me->RemoveAura(SPELL_NEFARIANS_BARRIER);
        }

        summons.DespawnAll();
    }

    void BeginEvent(Player* target)
    {
        _EnterCombat();
        Talk(SAY_GAMESBEGIN_2);
        me->setFaction(103);
        me->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
        DoCast(me, SPELL_NEFARIANS_BARRIER);
        me->SetStandState(UNIT_STAND_STATE_STAND);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC);
        AttackStart(target);
        events.ScheduleEvent(EVENT_SHADOW_BOLT, urand(3000, 10000));
        events.ScheduleEvent(EVENT_SHADOW_BOLT_VOLLEY, 13000);
        events.ScheduleEvent(EVENT_FEAR, urand(10000, 20000));
        events.ScheduleEvent(EVENT_MIND_CONTROL, urand(30000, 35000));
        events.ScheduleEvent(EVENT_SPAWN_ADD, 10000);
        events.ScheduleEvent(EVENT_SHADOWBLINK, 2000);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        if (summon->GetEntry() != NPC_NEFARIAN)
            summon->CastSpell(summon, SPELL_SUMMON_DRAKONID_BONES, true);
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
        if (summon->GetEntry() != NPC_NEFARIAN)
        {
            summon->setFaction(103);
            summon->SetInCombatWithZone();
        }
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type == 1 && data == 1)
        {
            me->StopMoving();
            events.ScheduleEvent(EVENT_PATH_2, 9000);
        }

        if (type == 1 && data == 2)
            events.ScheduleEvent(EVENT_SUCCESS_1, 5000);
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_BEGIN_FIGHT:
                        BeginEvent(_player);
                        break;
                    case EVENT_PATH_2:
                        me->GetMotionMaster()->MovePath(NEFARIUS_PATH_2, false);
                        events.ScheduleEvent(EVENT_CHAOS_1, 7000);
                        break;
                    case EVENT_CHAOS_1:
                        if (Creature* gyth = me->FindNearestCreature(NPC_GYTH, 75.0f, true))
                        {
                            me->SetFacingToObject(gyth);
                            Talk(SAY_CHAOS_SPELL);
                        }
                        events.ScheduleEvent(EVENT_CHAOS_2, 2000);
                        break;
                    case EVENT_CHAOS_2:
                        DoCast(SPELL_CHROMATIC_CHAOS);
                        me->SetFacingTo(1.570796f);
                        break;
                    case EVENT_SUCCESS_1:
                        if (Player* player = me->SelectNearestPlayer(60.0f))
                        {
                            me->SetInFront(player);
                            Talk(SAY_SUCCESS);
                            if (GameObject* portcullis1 = me->FindNearestGameObject(GO_PORTCULLIS_ACTIVE, 65.0f))
                                portcullis1->SetGoState(GO_STATE_ACTIVE);
                            if (GameObject* portcullis2 = me->FindNearestGameObject(GO_PORTCULLIS_TOBOSSROOMS, 80.0f))
                                portcullis2->SetGoState(GO_STATE_ACTIVE);
                        }
                        events.ScheduleEvent(EVENT_SUCCESS_2, 4000);
                        break;
                    case EVENT_SUCCESS_2:
                        DoCast(me, SPELL_VAELASTRASZZ_SPAWN);
                        me->DespawnOrUnsummon(1000);
                        break;
                    case EVENT_PATH_3:
                        me->GetMotionMaster()->MovePath(NEFARIUS_PATH_3, false);
                        break;
                    default:
                        break;
                }
            }
            return;
        }

        if (UpdateVictim() && _addsSpawned <= 42)
        {
            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SHADOW_BOLT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                            DoCast(target, SPELL_SHADOWBOLT);
                        events.Repeat(urand(2000, 4000));
                        break;
                    case EVENT_SHADOW_BOLT_VOLLEY:
                        DoCastAOE(SPELL_SHADOWBOLT_VOLLEY);
                        events.Repeat(urand(19000, 28000));
                        break;
                    case EVENT_SILENCE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                            DoCast(target, SPELL_SILENCE);
                        events.Repeat(urand(14000, 23000));
                        break;
                    case EVENT_FEAR:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 40.0f, true))
                            DoCast(target, SPELL_FEAR);
                        events.Repeat(urand(10000, 20000));
                        break;
                    case EVENT_MIND_CONTROL:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 40.0f, true))
                            DoCast(target, SPELL_SHADOW_COMMAND);
                        events.Repeat(urand(24000, 30000));
                        break;
                    case EVENT_SPAWN_ADD:
                        me->SummonCreature(urand(0, 2) ? _firstAdd : NPC_CHROMATIC_DRAKANOID, DrakeSpawnLoc[0], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                        me->SummonCreature(urand(0, 2) ? _secondAdd : NPC_CHROMATIC_DRAKANOID, DrakeSpawnLoc[1], TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                        _addsSpawned += 2;
                        if (_addsSpawned >= 42)
                        {
                            if (Creature* nefarian = me->SummonCreature(NPC_NEFARIAN, NefarianLoc[0], TEMPSUMMON_DEAD_DESPAWN))
                            {
                                nefarian->setActive(true);
                                nefarian->CastSpell((Unit*)nullptr, SPELL_SHADOWFLAME_INITIAL, true);
                                nefarian->AI()->Talk(SAY_AGGRO);
                                nefarian->GetMotionMaster()->MovePoint(1, NefarianLoc[1]);
                            }
                            events.Reset();
                            me->SetVisible(false);
                            return;
                        }
                        events.ScheduleEvent(EVENT_SPAWN_ADD, 4000);
                        break;
                    case EVENT_SHADOWBLINK:
                        DoCastAOE(SPELL_SHADOWBLINK);
                        events.Repeat(urand(30000, 40000));
                        break;
                    default:
                        break;
                }

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
            }
        }
    }

    void sGossipSelect(Player* player, uint32 menuId, uint32 gossipListId) override
    {
        if (menuId == GOSSIP_ID && gossipListId == GOSSIP_OPTION_ID)
        {
            player->CLOSE_GOSSIP_MENU();
            Talk(SAY_GAMESBEGIN_1);
            _player = player;
            events.ScheduleEvent(EVENT_BEGIN_FIGHT, 2000);
        }
    }

private:
    Player* _player;
    uint32 _addsSpawned, _firstAdd, _secondAdd;
};

struct classSpellsHolder
{
    uint8 _class, _text;
};

struct boss_nefarianAI : public BossAI
{
    boss_nefarianAI(Creature* creature) : BossAI(creature, DATA_NEFARIAN) { }

    void Reset() override
    {
        if (!me->IsAlive())
            return;

        me->ResetLootMode();
        events.Reset();
        _addsSpawned = false;
        _lowHPYelled = false;
    }

    void EnterCombat(Unit* /*who*/) override
    {
        events.Reset();
        events.ScheduleEvent(EVENT_SHADOWFLAME, 12000);
        events.ScheduleEvent(EVENT_FEAR, urand(25000, 35000));
        events.ScheduleEvent(EVENT_VEILOFSHADOW, urand(25000, 35000));
        events.ScheduleEvent(EVENT_CLEAVE, 7000);
        events.ScheduleEvent(EVENT_TAILLASH, 10000);
        events.ScheduleEvent(EVENT_CLASSCALL, urand(30000, 35000));
    }

    void JustDied(Unit* /*Killer*/) override
    {
        _JustDied();
        if (Creature* nefarius = instance->GetCreature(DATA_LORD_VICTOR_NEFARIUS))
            nefarius->DespawnOrUnsummon();
        Talk(SAY_DEATH);
    }

    void KilledUnit(Unit* victim) override
    {
        if (roll_chance_i(80))
            Talk(SAY_SLAY, victim);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (id == 1)
        {
            me->RemoveAurasDueToSpell(SPELL_SHADOWFLAME_INITIAL, 0, 0, AURA_REMOVE_BY_EXPIRE);
            me->RemoveByteFlag(UNIT_FIELD_BYTES_1, 3, UNIT_BYTE1_FLAG_ALWAYS_STAND | UNIT_BYTE1_FLAG_HOVER);
            me->SetCanFly(false);
            me->SetDisableGravity(false);
            Talk(SAY_SHADOWFLAME);
            DoZoneInCombat();
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 250.0f, true))
                AttackStart(target);
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        if (me->HealthBelowPctDamaged(20, damage) && !_addsSpawned)
        {
            _addsSpawned = true;
            std::list<GameObject*> constructList;
            me->GetGameObjectListWithEntryInGrid(constructList, GO_CONSTRUCT_BONES, 250.0f);
            for (auto itr : constructList)
            {
                me->SummonCreature(NPC_BONE_CONSTRUCT, *itr, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
                itr->Delete();
            }
            Talk(SAY_RAISE_SKELETONS);
        }
        if (me->HealthBelowPctDamaged(5, damage) && !_lowHPYelled)
        {
            _lowHPYelled = true;
            Talk(SAY_XHEALTH);
        }
    }

    void HandleClassCall(uint8 classId)
    {
        for (auto itr : _classSpells)
            if (itr._class == classId)
                Talk(itr._text);

        if (classId == CLASS_PALADIN)
        {
            DoCast(me, SPELL_PALADIN, true);
            return;
        }
        else if (classId == CLASS_MAGE)
        {
            DoCastAOE(SPELL_MAGE, true);
            return;
        }

        Map::PlayerList const& players = me->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
        {
            if (Player* player = itr->GetSource())
            {
                if (player->getClass() == classId)
                {
                    switch (classId)
                    {
                        case CLASS_WARRIOR:
                            player->AddAura(SPELL_WARRIOR, player);
                            break;
                        case CLASS_HUNTER:
                            player->AddAura(SPELL_HUNTER, player);
                            break;
                        case CLASS_SHAMAN:
                            player->AddAura(SPELL_SHAMAN, player);
                            break;
                        case CLASS_ROGUE:
                            float destX, destY, destZ;
                            me->GetRandomContactPoint(me, destX, destY, destZ);
                            player->NearTeleportTo(destX, destY, destZ, frand(0.0f, 2 * M_PI));
                            break;
                        case CLASS_PRIEST:
                            player->AddAura(SPELL_PRIEST, player);
                            break;
                        case CLASS_WARLOCK:
                            player->AddAura(SPELL_WARLOCK, player);
                            me->SummonCreature(14668, *player, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
                            me->SummonCreature(14668, *player, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
                            break;
                        case CLASS_DRUID:
                            player->AddAura(SPELL_DRUID, player);
                            break;
                        case CLASS_DEATH_KNIGHT:
                            me->CastSpell(player, SPELL_DEATH_KNIGHT);
                            break;
                    }
                }
            }
        }
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SHADOWFLAME:
                DoCastVictim(SPELL_SHADOWFLAME);
                events.Repeat(12000);
                break;
            case EVENT_FEAR:
                DoCastVictim(SPELL_BELLOWINGROAR);
                events.Repeat(30000);
                break;
            case EVENT_VEILOFSHADOW:
                DoCastVictim(SPELL_VEILOFSHADOW);
                events.Repeat(15000);
                break;
            case EVENT_CLEAVE:
                DoCastVictim(SPELL_CLEAVE);
                events.Repeat(7000);
                break;
            case EVENT_TAILLASH:
                DoCastVictim(SPELL_TAILLASH);
                events.Repeat(10000);
                break;
            case EVENT_CLASSCALL:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100.0f, true))
                    HandleClassCall(target->getClass());
                events.Repeat(urand(35000, 40000));
                break;
            default:
                break;
        }
    }

private:
    bool _addsSpawned, _lowHPYelled;
    std::vector<classSpellsHolder> _classSpells =
    {
        { CLASS_WARRIOR     , SAY_WARRIOR, },
        { CLASS_PALADIN     , SAY_PALADIN },
        { CLASS_HUNTER      , SAY_HUNTER },
        { CLASS_ROGUE       , SAY_ROGUE },
        { CLASS_PRIEST      , SAY_PRIEST },
        { CLASS_DEATH_KNIGHT, SAY_DEATH_KNIGHT },
        { CLASS_SHAMAN      , SAY_SHAMAN },
        { CLASS_MAGE        , SAY_MAGE },
        { CLASS_WARLOCK     , SAY_WARLOCK },
        { CLASS_DRUID       , SAY_DRUID }
    };
};

class spell_nefarius_shadowblink_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_nefarius_shadowblink_SpellScript);

    std::vector<uint32> spells = { 22668, 22669, 22670, 22671, 22672, 22673, 22674, 22675, 22676 };

    bool Validate(SpellInfo const* spellInfo) override
    {
        return ValidateSpellInfo({ SPELL_SHADOWBLINK, 22668, 22669, 22670, 22671, 22672, 22673, 22674, 22675, 22676 });
    }

    void HandleScript(SpellEffIndex /*effIndex*/)
    {
        GetCaster()->CastSpell(GetCaster(), Trinity::Containers::SelectRandomContainerElement(spells), true);
    }

    void Register() override
    {
        OnEffectHitTarget += SpellEffectFn(spell_nefarius_shadowblink_SpellScript::HandleScript, EFFECT_0, SPELL_EFFECT_DUMMY);
    }
};

void AddSC_boss_nefarian()
{
    new CreatureAILoader<boss_victor_nefariusAI>("boss_victor_nefarius");
    new CreatureAILoader<boss_nefarianAI>("boss_nefarian");
    new SpellScriptLoaderEx<spell_nefarius_shadowblink_SpellScript>("spell_nefarius_shadowblink");
}