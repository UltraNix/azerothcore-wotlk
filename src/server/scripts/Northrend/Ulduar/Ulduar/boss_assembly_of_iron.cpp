/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "ulduar.h"
#include "SpellAuraEffects.h"
#include "Player.h"

enum AssemblySpells
{
    // Any boss
    SPELL_SUPERCHARGE                  = 61920,
    SPELL_BERSERK                      = 47008,

    // Steelbreaker
    SPELL_HIGH_VOLTAGE_10              = 61890,
    SPELL_HIGH_VOLTAGE_25              = 63498,
    SPELL_FUSION_PUNCH_10              = 61903,
    SPELL_FUSION_PUNCH_25              = 63493,
    SPELL_STATIC_DISRUPTION_10         = 61911,
    SPELL_STATIC_DISRUPTION_25         = 63495,
    SPELL_OVERWHELMING_POWER_10        = 64637,
    SPELL_OVERWHELMING_POWER_25        = 61888,
    SPELL_ELECTRICAL_CHARGE            = 61902,

    // Runemaster Molgeim
    SPELL_SHIELD_OF_RUNES_BUFF         = 62277,
    SPELL_SHIELD_OF_RUNES_10           = 62274,
    SPELL_SHIELD_OF_RUNES_25           = 63489,
    SPELL_RUNE_OF_POWER                = 61973,
    SPELL_RUNE_OF_DEATH_10             = 62269,
    SPELL_RUNE_OF_DEATH_25             = 63490,
    SPELL_RUNE_OF_SUMMONING            = 62273,
    SPELL_RUNE_OF_SUMMONING_VISUAL     = 62019,
    SPELL_LIGHTNING_BLAST_10           = 62054,
    SPELL_LIGHTNING_BLAST_25           = 63491,
    CREATURE_LIGHTNING_ELEMENTAL       = 32958,
    CREATURE_RUNE_OF_SUMMONING         = 33051,
    SPELL_RUNE_OF_POWER_OOC_CHANNEL    = 61975,

    // Stormcaller Brundir
    SPELL_CHAIN_LIGHTNING_10           = 61879,
    SPELL_CHAIN_LIGHTNING_25           = 63479,
    SPELL_OVERLOAD_10                  = 61869,
    SPELL_OVERLOAD_25                  = 63481,
    SPELL_OVERLOAD_GROW_VISUAL         = 61877,
    SPELL_LIGHTNING_WHIRL_10           = 61915,
    SPELL_LIGHTNING_WHIRL_25           = 63483,
    SPELL_LIGHTNING_TENDRILS_10        = 61887,
    SPELL_LIGHTNING_TENDRILS_25        = 63486,
    SPELL_STORMSHIELD                  = 64187,
    SPELL_LIGHTNING_CHANNEL_PRE        = 61942,
};

#define SPELL_HIGH_VOLTAGE            RAID_MODE(SPELL_HIGH_VOLTAGE_10, SPELL_HIGH_VOLTAGE_25)
#define SPELL_FUSION_PUNCH            RAID_MODE(SPELL_FUSION_PUNCH_10, SPELL_FUSION_PUNCH_25)
#define SPELL_STATIC_DISRUPTION        RAID_MODE(SPELL_STATIC_DISRUPTION_10, SPELL_STATIC_DISRUPTION_25)
#define SPELL_OVERWHELMING_POWER    RAID_MODE(SPELL_OVERWHELMING_POWER_10, SPELL_OVERWHELMING_POWER_25)
#define SPELL_SHIELD_OF_RUNES        RAID_MODE(SPELL_SHIELD_OF_RUNES_10, SPELL_SHIELD_OF_RUNES_25)
#define SPELL_RUNE_OF_DEATH            RAID_MODE(SPELL_RUNE_OF_DEATH_10, SPELL_RUNE_OF_DEATH_25)
#define SPELL_LIGHTNING_BLAST        RAID_MODE(SPELL_LIGHTNING_BLAST_10, SPELL_LIGHTNING_BLAST_25)
#define SPELL_CHAIN_LIGHTNING        RAID_MODE(SPELL_CHAIN_LIGHTNING_10, SPELL_CHAIN_LIGHTNING_25)
#define SPELL_OVERLOAD                RAID_MODE(SPELL_OVERLOAD_10, SPELL_OVERLOAD_25)
#define SPELL_LIGHTNING_WHIRL        RAID_MODE(SPELL_LIGHTNING_WHIRL_10, SPELL_LIGHTNING_WHIRL_25)
#define SPELL_LIGHTNING_TENDRILS    RAID_MODE(SPELL_LIGHTNING_TENDRILS_10, SPELL_LIGHTNING_TENDRILS_25)


enum eEnums
{
    // Steelbreaker
    EVENT_FUSION_PUNCH            = 1,
    EVENT_STATIC_DISRUPTION        = 2,
    EVENT_OVERWHELMING_POWER    = 3,
    //EVENT_CHECK_MAIN_TANK        = 4,

    // Molgeim
    EVENT_RUNE_OF_POWER            = 11,
    EVENT_SHIELD_OF_RUNES        = 12,
    EVENT_RUNE_OF_DEATH            = 13,
    EVENT_RUNE_OF_SUMMONING        = 14,
    EVENT_LIGHTNING_BLAST        = 15,

    // Brundir
    EVENT_CHAIN_LIGHTNING        = 21,
    EVENT_OVERLOAD                = 22,
    EVENT_LIGHTNING_WHIRL        = 23,
    EVENT_LIGHTNING_TENDRILS    = 24,
    EVENT_LIGHTNING_LAND        = 25,
    EVENT_LAND_LAND                = 26,
    EVENT_IMMUNE                = 27,

    EVENT_ENRAGE                = 30,
};

enum AOISounds
{
    // molgeim
    SOUND_MOLGEIM_AGGRO            = 15657,
    SOUND_MOLGEIM_SLAY1            = 15658,
    SOUND_MOLGEIM_SLAY2            = 15659,
    SOUND_MOLGEIM_POWER            = 15660,
    SOUND_MOLGEIM_SUMMON        = 15661,
    SOUND_MOLGEIM_DEATH1        = 15662,
    SOUND_MOLGEIM_DEATH2        = 15663,
    SOUND_MOLGEIM_BERSERK        = 15664,

    // steelbreaker
    SOUND_SB_AGGRO                = 15674,
    SOUND_SB_SLAY1                = 15675,
    SOUND_SB_SLAY2                = 15676,
    SOUND_SB_POWER                = 15677,
    SOUND_SB_DEATH1                = 15678,
    SOUND_SB_DEATH2                = 15679,
    SOUND_SB_BERSERK            = 15680,

    // brundir
    SOUND_BRUNDIR_AGGRO            = 15684,
    SOUND_BRUNDIR_SLAY1            = 15685,
    SOUND_BRUNDIR_SLAY2            = 15686,
    SOUND_BRUNDIR_POWER            = 15687,
    SOUND_BRUNDIR_FLIGHT        = 15688,
    SOUND_BRUNDIR_DEATH1        = 15689,
    SOUND_BRUNDIR_DEATH2        = 15690,
    SOUND_BRUNDIR_BERSERK        = 15691,
};

enum Misc
{
    ACTION_ADD_CHARGE            = 1,
    POINT_CHANNEL_STEELBREAKER    = 1
};

bool IsEncounterComplete(InstanceScript* pInstance, Creature* me)
{
   if (!pInstance || !me)
        return false;

    for (uint8 i = 0; i < 3; ++i)
    {
        uint64 guid = pInstance->GetData64(DATA_STEELBREAKER+i);
        if (!guid)
            return false;

        if (Creature *boss = (ObjectAccessor::GetCreature(*me, guid)))
        {
            if (boss->IsAlive())
                return false;
            continue;
        }
        else
            return false;
    }
    return true;
}

void RespawnAssemblyOfIron(InstanceScript* pInstance, Creature* me)
{
    if (!pInstance || !me)
        return;

    for (uint8 i = 0; i < 3; ++i)
    {
        uint64 guid = pInstance->GetData64(DATA_STEELBREAKER+i);
        if (!guid)
            return;

        if (Creature *boss = (ObjectAccessor::GetCreature((*me), guid)))
            if (!boss->IsAlive())
                boss->Respawn();
    }
    return;
}

void RestoreAssemblyHealth(uint64 guid1, uint64 guid2, Creature *me)
{
    if(Creature* cr = ObjectAccessor::GetCreature(*me, guid1))
        if(cr->IsAlive())
            cr->SetHealth(cr->GetMaxHealth());

    if(Creature* cr2 = ObjectAccessor::GetCreature(*me, guid2))
        if(cr2->IsAlive())
            cr2->SetHealth(cr2->GetMaxHealth());

}

class boss_steelbreaker : public CreatureScript
{
public:
    boss_steelbreaker() : CreatureScript("boss_steelbreaker") {}

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_steelbreakerAI(pCreature);
    }

    struct boss_steelbreakerAI : public ScriptedAI
    {
        boss_steelbreakerAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
        }

        bool IsInRoom()
        {
            if (me->GetPositionX() > 1680.0f || me->GetPositionX() < 1490.0f || me->GetPositionY() > 180.0f || me->GetPositionY() < 64.0f)
            {
                EnterEvadeMode();
                return false;
            }

            return true;
        }

        void Reset()
        {
            _hardMode = false;
            _fightTimer = 0;
            me->SetLootMode(0);
            RespawnAssemblyOfIron(pInstance, me);

            _lastOverwhelmingPowerTargetGUID = 0;
            _phase = 0;
            events.Reset();
            if (pInstance)
                pInstance->SetData(TYPE_ASSEMBLY, NOT_STARTED);
        }

        void JustReachedHome()
        {
            me->setActive(false);
            me->RemoveAllAuras();
        }

        void EnterCombat(Unit* who)
        {
            if (pInstance)
                pInstance->SetData(TYPE_ASSEMBLY, IN_PROGRESS);

            _fightTimer = getMSTime();
            me->setActive(true);
            me->SetInCombatWithZone();
            me->CastSpell(me, SPELL_HIGH_VOLTAGE, true);
            events.ScheduleEvent(EVENT_ENRAGE, sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) ? 600000 : 900000);
            UpdatePhase();

            if (!pInstance)
                return;

            if (Creature *boss = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_STEELBREAKER + urand(0, 2))))
            {
                switch (boss->GetEntry())
                {
                    case NPC_STEELBREAKER:
                        boss->MonsterYell("You will not defeat the Assembly of Iron so easily, invaders!", LANG_UNIVERSAL, 0);
                        boss->PlayDirectSound(SOUND_SB_AGGRO);
                        break;
                    case NPC_MOLGEIM:
                        boss->MonsterYell("Nothing short of total decimation will suffice.", LANG_UNIVERSAL, 0);
                        boss->PlayDirectSound(SOUND_MOLGEIM_AGGRO);
                        break;
                    case NPC_BRUNDIR:
                        boss->MonsterYell("Whether the world's greatest gnats or the world's greatest heroes, you're still only mortal!", LANG_UNIVERSAL, 0);
                        boss->PlayDirectSound(SOUND_BRUNDIR_AGGRO);
                        break;
                }
            }

            for (uint8 i = 0; i < 3; ++i)
                if (Creature *boss = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_STEELBREAKER + i)))
                    if (!boss->IsInCombat())
                        boss->AI()->AttackStart(who);
        }

        void UpdatePhase()
        {
            if (_phase >= 3)
                return;

            ++_phase;

            switch (_phase)
            {
                case 1:
                    events.RescheduleEvent(EVENT_FUSION_PUNCH, 15000);
                    break;
                case 2:
                    events.RescheduleEvent(EVENT_STATIC_DISRUPTION, 20000);
                    break;
                case 3:
                    _hardMode = true;
                    me->ResetLootMode();
                    events.RescheduleEvent(EVENT_OVERWHELMING_POWER, 8000);
                    break;
            }
        }

        void JustDied(Unit* killer)
        {
            if (!pInstance)
                return;

            if (IsEncounterComplete(pInstance, me))
            {
                pInstance->SetData(TYPE_ASSEMBLY, DONE);
                me->CastSpell(me, 65195, true); // credit

                if (Map* map = me->GetMap())
                    CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry + _hardMode, Difficulty(map->GetDifficulty() + 2 * _hardMode), "Assembly of Iron", 15000, _fightTimer);
            }
            else
            {
                RestoreAssemblyHealth(pInstance->GetData64(DATA_BRUNDIR), pInstance->GetData64(DATA_MOLGEIM), me);
                me->CastSpell(me, SPELL_SUPERCHARGE, true);
            }

            if (urand(0, 1))
            {
                me->MonsterYell("My death only serves to hasten your demise.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SB_DEATH1);
            }
            else
            {
                me->MonsterYell("Impossible!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SB_DEATH2);
            }
        }

        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (_phase == 3 && who->GetGUID() != _lastOverwhelmingPowerTargetGUID)
                me->CastSpell(me, SPELL_ELECTRICAL_CHARGE, true);

            if (urand(0, 1))
            {
                me->MonsterYell("So fragile and weak!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SB_SLAY1);
            }
            else
            {
                me->MonsterYell("Flesh... such a hindrance.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_SB_SLAY2);
            }
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_ADD_CHARGE)
            {
                if (me->IsInCombat() && !me->IsInEvadeMode())
                    me->CastSpell(me, SPELL_ELECTRICAL_CHARGE, true);
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spellInfo)
        {
            if (spellInfo->Id == SPELL_SUPERCHARGE)
                UpdatePhase();
        }

        void UpdateAI(uint32 diff)
        {
            if (!IsInRoom())
                return;

            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_FUSION_PUNCH:
                    me->CastSpell(me->GetVictim(), SPELL_FUSION_PUNCH, false);
                    events.RepeatEvent(15000 + rand() % 5000);
                    break;
                case EVENT_STATIC_DISRUPTION:
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_FARTHEST, 0, 0, true))
                        me->CastSpell(pTarget, SPELL_STATIC_DISRUPTION, false);

                    events.RepeatEvent(20000 + rand() % 20000);
                    break;
                case EVENT_OVERWHELMING_POWER:
                    me->MonsterYell("You seek the secrets of Ulduar? Then take them!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_SB_POWER);
                    if (Unit* target = me->GetVictim())
                    {
                        me->CastSpell(me->GetVictim(), SPELL_OVERWHELMING_POWER, true);
                        _lastOverwhelmingPowerTargetGUID = target->GetGUID();
                    }
                    events.RepeatEvent(RAID_MODE(61000, 36000));
                    break;
                case EVENT_ENRAGE:
                    me->MonsterYell("This meeting of the Assembly of Iron is adjourned!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_SB_BERSERK);
                    me->CastSpell(me, SPELL_BERSERK, true);
                    events.PopEvent();
                    break;
            }

            DoMeleeAttackIfReady();
        }
    private:
        EventMap events;
        InstanceScript* pInstance;
        uint8 _phase;
        uint64 _lastOverwhelmingPowerTargetGUID;
        uint32 _fightTimer;
        bool _hardMode;
    };
};

class CastRunesEvent : public BasicEvent
{
    public:
        CastRunesEvent(Creature& owner) : BasicEvent(), _owner(owner) { }

        bool Execute(uint64 /*eventTime*/, uint32 /*diff*/)
        {
            if (!_owner.IsInCombat())
                _owner.CastSpell(&_owner, SPELL_RUNE_OF_POWER_OOC_CHANNEL, true);
            return true;
        }

    private:
        Creature& _owner;
};

class boss_runemaster_molgeim : public CreatureScript
{
public:
    boss_runemaster_molgeim() : CreatureScript("boss_runemaster_molgeim") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_runemaster_molgeimAI (pCreature);
    }

    struct boss_runemaster_molgeimAI : public ScriptedAI
    {
        boss_runemaster_molgeimAI(Creature *c) : ScriptedAI(c), summons(me)
        {
            pInstance = c->GetInstanceScript();
        }

        InstanceScript* pInstance;
        SummonList summons;
        EventMap events;
        uint8 _phase;
        uint32 _fightTimer;

        bool IsInRoom()
        {
            if (me->GetPositionX() > 1680.0f || me->GetPositionX() < 1490.0f || me->GetPositionY() > 180.0f || me->GetPositionY() < 64.0f)
            {
                EnterEvadeMode();
                return false;
            }

            return true;
        }

        void Reset()
        {
            me->SetLootMode(0);
            RespawnAssemblyOfIron(pInstance, me);

            _fightTimer = 0;
            _phase = 0;
            events.Reset();
            summons.DespawnAll();

            if (pInstance)
                pInstance->SetData(TYPE_ASSEMBLY, NOT_STARTED);

            me->m_Events.AddEvent(new CastRunesEvent(*me), me->m_Events.CalculateTime(8000));
        }

        void JustReachedHome()
        {
            me->setActive(false);
            me->RemoveAllAuras();
        }

        void EnterCombat(Unit* who)
        {
            _fightTimer = getMSTime();
            me->InterruptNonMeleeSpells(false);
            me->setActive(true);
            me->SetInCombatWithZone();
            events.ScheduleEvent(EVENT_ENRAGE, sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) ? 600000 : 900000);
            UpdatePhase();

            if (!pInstance)
                return;

            for (uint8 i = 0; i < 3; ++i)
                if (Creature* boss = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_STEELBREAKER+i)))
                    if (!boss->IsInCombat())
                        boss->AI()->AttackStart(who);
        }

        void JustSummoned(Creature* summon) override
        {
            summons.Summon(summon);
        }

        void UpdatePhase()
        {
            if (_phase >= 3)
                return;

            ++_phase;

            switch (_phase)
            {
                case 1:
                    events.RescheduleEvent(EVENT_SHIELD_OF_RUNES, 20000);
                    events.RescheduleEvent(EVENT_RUNE_OF_POWER, 30000);
                    break;
                case 2:
                    events.RescheduleEvent(EVENT_RUNE_OF_DEATH, 35000);
                    break;
                case 3:
                    me->ResetLootMode();
                    events.RescheduleEvent(EVENT_RUNE_OF_SUMMONING, 20000+rand()%10000);
                    break;
            }
        }

        void JustDied(Unit* killer)
        {
            if (!pInstance)
                return;

            if (IsEncounterComplete(pInstance, me))
            {
                pInstance->SetData(TYPE_ASSEMBLY, DONE);
                me->CastSpell(me, 65195, true); // credit

                if (Map* map = me->GetMap())
                    CheckCreatureRecord(killer, map->GetDifficulty() ? 33693 : NPC_STEELBREAKER, Difficulty(map->GetDifficulty()), "Assembly of Iron", 15000, _fightTimer);
            }
            else
            {
                RestoreAssemblyHealth(pInstance->GetData64(DATA_STEELBREAKER), pInstance->GetData64(DATA_BRUNDIR), me);
                me->CastSpell(me, SPELL_SUPERCHARGE, true);
            }

            if (urand(0,1))
            {
                me->MonsterYell("The legacy of storms shall not be undone.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_MOLGEIM_DEATH1);
            }
            else
            {
                me->MonsterYell("What have you gained from my defeat? You are no less doomed, mortals!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_MOLGEIM_DEATH2);
            }
        }

        void KilledUnit(Unit *who)
        {
            if (who->GetTypeId() != TYPEID_PLAYER || urand(0,2))
                return;

            if (urand(0,1))
            {
                me->MonsterYell("The world suffers yet another insignificant loss.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_MOLGEIM_SLAY1);
            }
            else
            {
                me->MonsterYell("Death is the price of your arrogance.", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_MOLGEIM_SLAY2);
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spellInfo)
        {
            if (spellInfo->Id == SPELL_SUPERCHARGE)
                UpdatePhase();
        }

        void UpdateAI(uint32 diff)
        {
            if (!IsInRoom())
                return;

            if (!UpdateVictim())
                return;

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch(events.GetEvent())
            {
                case EVENT_RUNE_OF_POWER:
                {
                    std::list<Creature*> assemblyList;
                    for (uint8 i = DATA_STEELBREAKER; i <= DATA_BRUNDIR; ++i)
                        if (Creature* boss = ObjectAccessor::GetCreature(*me, pInstance->GetData64(i)))
                            if (boss->IsAlive())
                                assemblyList.push_back(boss);

                    if (!assemblyList.empty())
                        if (Creature* target = Trinity::Containers::SelectRandomContainerElement(assemblyList))
                            DoCast(target, SPELL_RUNE_OF_POWER, true);

                    events.RepeatEvent(60000);
                    break;
                }
                case EVENT_SHIELD_OF_RUNES:
                    me->CastSpell(me, SPELL_SHIELD_OF_RUNES, false);
                    events.RescheduleEvent(EVENT_SHIELD_OF_RUNES, 27000+ rand()%7000);
                    break;
                case EVENT_RUNE_OF_DEATH:
                {
                    Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true);

                    if (!target)
                        target = me->GetVictim();

                    if (target)
                        me->CastSpell(target, SPELL_RUNE_OF_DEATH, true);

                    me->MonsterYell("Decipher this!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_MOLGEIM_POWER);
                    events.RepeatEvent(30000 + rand() % 10000);
                    break;
                }
                case EVENT_RUNE_OF_SUMMONING:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                        if (Creature * rune = me->SummonCreature(CREATURE_RUNE_OF_SUMMONING, target->GetPositionX(), target->GetPositionY(), target->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 11000))
                            rune->CastSpell(rune, SPELL_RUNE_OF_SUMMONING_VISUAL, true);

                    me->MonsterYell("Face the lightning surge!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_MOLGEIM_SUMMON);
                    events.RepeatEvent(20000+rand()%10000);
                    break;
                case EVENT_ENRAGE:
                    me->CastSpell(me, SPELL_BERSERK, true);
                    me->MonsterYell("This meeting of the Assembly of Iron is adjourned!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_MOLGEIM_BERSERK);
                    events.PopEvent();
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

struct npc_assembly_lightningAI : public ScriptedAI
{
    npc_assembly_lightningAI(Creature* creature) : ScriptedAI(creature)
    {
        _boomed = false;
        me->ApplySpellImmune(0, IMMUNITY_SCHOOL, SPELL_SCHOOL_MASK_NATURE, true);

        if (me->GetInstanceScript())
            if (Creature* molgeim = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(DATA_MOLGEIM)))
                if (molgeim->IsAIEnabled)
                    molgeim->AI()->JustSummoned(me);
    }

    void Reset() override
    {
        DoZoneInCombat(me, 150.0f);

        if (me->GetInstanceScript())
            if (Creature* molgeim = ObjectAccessor::GetCreature(*me, me->GetInstanceScript()->GetData64(DATA_MOLGEIM)))
                if (!molgeim->IsInCombat())
                    me->DespawnOrUnsummon();
    }

    void OnCharmed(bool /*apply*/) override { }

    void DamageDealt(Unit* /*doneTo*/, uint32& /*damage*/, DamageEffectType) override
    {
        if (!_boomed)
        {
            _boomed = true;
            DoCastAOE(SPELL_LIGHTNING_BLAST, true);
            me->DespawnOrUnsummon(1s);
            me->SetReactState(REACT_PASSIVE);
            me->AttackStop();
            me->GetMotionMaster()->Clear();
        }
    }
private:
    bool _boomed;
};
class boss_stormcaller_brundir : public CreatureScript
{
public:
    boss_stormcaller_brundir() : CreatureScript("boss_stormcaller_brundir") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_stormcaller_brundirAI (pCreature);
    }

    struct boss_stormcaller_brundirAI : public ScriptedAI
    {
        boss_stormcaller_brundirAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
        }

        EventMap events;
        InstanceScript* pInstance;
        uint32 _phase;
        bool _flyPhase;
        bool _needReturnFromFly;

        Unit* _flyTarget;
        uint32 _channelTimer;
        uint32 _fightTimer = 0;

        bool _stunnedAchievement;

        bool IsInRoom()
        {
            if (me->GetPositionX() > 1680.0f || me->GetPositionX() < 1490.0f || me->GetPositionY() > 180.0f || me->GetPositionY() < 64.0f)
            {
                EnterEvadeMode();
                return false;
            }

            return true;
        }

        void Reset()
        {
            me->SetLootMode(0);
            RespawnAssemblyOfIron(pInstance, me);

            _fightTimer = 0;
            _channelTimer = 0;
            _phase = 0;
            _flyPhase = false;
            _needReturnFromFly = false;
            _flyTarget = nullptr;
            _stunnedAchievement = true;

            events.Reset();

            me->SetDisableGravity(false);
            me->SetRegeneratingHealth(true);
            me->SetReactState(REACT_AGGRESSIVE);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);

            if (pInstance)
                pInstance->SetData(TYPE_ASSEMBLY, NOT_STARTED);
        }

        void JustReachedHome()
        {
            me->setActive(false);
            me->RemoveAllAuras();
        }

        void EnterCombat(Unit* who)
        {
            _fightTimer = getMSTime();
            me->InterruptNonMeleeSpells(false);
            me->setActive(true);
            me->SetInCombatWithZone();
            events.ScheduleEvent(EVENT_ENRAGE, sWorld->getBoolConfig(CONFIG_ULDUAR_PRE_NERF) ? 600000 : 900000);
            UpdatePhase();

            if (!pInstance)
                return;

            for (uint8 i = 0; i < 3; ++i)
                if (Creature *boss = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_STEELBREAKER+i)))
                    if (!boss->IsInCombat())
                        boss->AI()->AttackStart(who);
        }

        void UpdatePhase()
        {
            if (_phase >= 3)
                return;

            ++_phase;

            switch (_phase)
            {
                case 1:
                    events.RescheduleEvent(EVENT_CHAIN_LIGHTNING, 9000+ rand()%8000);
                    events.RescheduleEvent(EVENT_OVERLOAD, 40000);
                    break;
                case 2:
                    events.RescheduleEvent(EVENT_LIGHTNING_WHIRL, 20000+ rand()%20000);
                    break;
                case 3:
                    me->ResetLootMode();
                    me->CastSpell(me, SPELL_STORMSHIELD, true);
                    events.RescheduleEvent(EVENT_LIGHTNING_TENDRILS, 15000+ rand()%1000);
                    break;
            }
        }

        void JustDied(Unit* killer)
        {
            if (!pInstance)
                return;

            if (IsEncounterComplete(pInstance, me))
            {
                pInstance->SetData(TYPE_ASSEMBLY, DONE);
                me->CastSpell(me, 65195, true); // credit

                if (Map* map = me->GetMap())
                    CheckCreatureRecord(killer, map->GetDifficulty() ? 33693 : NPC_STEELBREAKER, Difficulty(map->GetDifficulty()), "Assembly of Iron", 15000, _fightTimer);
            }
            else
            {
                RestoreAssemblyHealth(pInstance->GetData64(DATA_STEELBREAKER), pInstance->GetData64(DATA_MOLGEIM), me);
                me->CastSpell(me, SPELL_SUPERCHARGE, true);
            }

            if (urand(0,1))
            {
                me->MonsterYell("The power of the storm lives on...", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_BRUNDIR_DEATH1);
            }
            else
            {
                me->MonsterYell("You rush headlong into the maw of madness!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_BRUNDIR_DEATH2);
            }

            // To be sure players gonna be allowed to loot.
            me->NearTeleportTo(me->GetPositionX(), me->GetPositionY(), 427.5f, me->GetOrientation());
        }

        void KilledUnit(Unit *who)
        {
            if (who->GetTypeId() != TYPEID_PLAYER || urand(0,2))
                return;

            if (urand(0,1))
            {
                me->MonsterYell("A merciful kill!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_BRUNDIR_SLAY1);
            }
            else
            {
                me->MonsterYell("HAH!", LANG_UNIVERSAL, 0);
                me->PlayDirectSound(SOUND_BRUNDIR_SLAY2);
            }
        }

        void SpellHit(Unit* caster, const SpellInfo* spellInfo)
        {
            if (spellInfo->Id == SPELL_SUPERCHARGE)
                UpdatePhase();
        }

        void SpellHitTarget(Unit* target, const SpellInfo* spellInfo)
        {
            if (spellInfo->Id == SPELL_CHAIN_LIGHTNING || spellInfo->Id == RAID_MODE(61916, 63482)) // Lightning Whirl triggered
                _stunnedAchievement = false;
        }

        uint32 GetData(uint32 param) const
        {
            if (param == DATA_BRUNDIR)
                return _stunnedAchievement;

            return 0;
        }

        void MovementInform(uint32 type, uint32 point)
        {
            if (type == POINT_MOTION_TYPE && point == POINT_CHANNEL_STEELBREAKER)
                me->CastSpell(me, SPELL_LIGHTNING_CHANNEL_PRE, true);
        }

        void UpdateAI(uint32 diff)
        {
            if (!IsInRoom())
                return;

            if (!me->IsInCombat() && me->GetReactState() == REACT_AGGRESSIVE)
            {
                _channelTimer += diff;
                if (_channelTimer >= 10000)
                {
                    _channelTimer = 0;
                    float o = urand(0, 5) * M_PI / 3.0f;
                    me->InterruptNonMeleeSpells(false);
                    me->GetMotionMaster()->MovePoint(POINT_CHANNEL_STEELBREAKER, 1587.18f + 10.0f * cos(o), 121.02f + 10.0f * sin(o), 427.3f);
                }
            }

            if (!UpdateVictim())
                return;

            if (_flyPhase)
            {
                if (_flyTarget && me->GetDistance2d(_flyTarget) >= 6)
                {
                    //float speed = me->GetDistance(_flyTarget->GetPositionX(), _flyTarget->GetPositionY(), _flyTarget->GetPositionZ()+15) / (1500.0f * 0.001f);
                    me->SendMonsterMove(_flyTarget->GetPositionX(), _flyTarget->GetPositionY(), _flyTarget->GetPositionZ()+15, 1500, SPLINEFLAG_FLYING);
                    me->SetPosition(_flyTarget->GetPositionX(), _flyTarget->GetPositionY(), _flyTarget->GetPositionZ(), _flyTarget->GetOrientation());
                }
            }
            else if (!_flyPhase && _needReturnFromFly)
            {
                _needReturnFromFly = false;

                if (_flyTarget)
                {
                    me->SendMonsterMove(_flyTarget->GetPositionX(), _flyTarget->GetPositionY(), _flyTarget->GetPositionZ(), 1500, SPLINEFLAG_FLYING);
                    me->SetPosition(_flyTarget->GetPositionX(), _flyTarget->GetPositionY(), _flyTarget->GetPositionZ(), _flyTarget->GetOrientation());
                }
                else
                {
                    me->SendMonsterMove(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 1500, SPLINEFLAG_FLYING);
                    me->SetPosition(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), me->GetOrientation());
                }
            }

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            switch (events.GetEvent())
            {
                case EVENT_CHAIN_LIGHTNING:
                    me->ApplySpellImmune(1, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0))
                        me->CastSpell(target, SPELL_CHAIN_LIGHTNING, false);

                    events.RepeatEvent(9000+ rand()%8000);
                    break;
                case EVENT_IMMUNE:
                    me->ApplySpellImmune(1, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                    events.PopEvent();
                    break;
                case EVENT_OVERLOAD:
                    me->ApplySpellImmune(1, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                    me->CastSpell(me, SPELL_OVERLOAD, true);
                    events.RescheduleEvent(EVENT_OVERLOAD, 60000);
                    events.RescheduleEvent(EVENT_IMMUNE, 5999);
                    break;
                case EVENT_LIGHTNING_WHIRL:
                    me->ApplySpellImmune(1, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                    me->MonsterYell("Stand still and stare into the light!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_BRUNDIR_POWER);
                    me->CastSpell(me, SPELL_LIGHTNING_WHIRL, true);
                    events.RepeatEvent(10000+ rand()%15000);
                    break;
                case EVENT_LIGHTNING_TENDRILS:
                {
                    // Reschedule old
                    events.RepeatEvent(35000);
                    events.DelayEvents(18000);
                    me->MonsterYell("Let the storm clouds rise and rain down death from above!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_BRUNDIR_FLIGHT);

                    _flyPhase = true;
                    _needReturnFromFly = true;
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, [&](Unit* tar) -> bool { return tar->IsPlayer() && tar->IsWithinLOSInMap(me); }))
                        _flyTarget = target;
                    else
                        _flyTarget = me->GetVictim();
                    me->SetRegeneratingHealth(false);
                    me->SetDisableGravity(true);

                    me->CombatStop();
                    me->StopMoving();
                    me->SetReactState(REACT_PASSIVE);
                    me->SetUInt64Value(UNIT_FIELD_TARGET, 0);
                    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
                    me->SendMonsterMove(_flyTarget->GetPositionX(), _flyTarget->GetPositionY(), _flyTarget->GetPositionZ()+15, 1500, SPLINEFLAG_FLYING);
                    me->SetTarget(_flyTarget->GetGUID());

                    me->CastSpell(me, SPELL_LIGHTNING_TENDRILS, true);
                    me->CastSpell(me, 61883, true);
                    events.ScheduleEvent(EVENT_LIGHTNING_LAND, 16000);

                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, true);
                    break;
                }
                case EVENT_LIGHTNING_LAND:
                {
                    float speed = me->GetDistance(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ()) / (1000.0f * 0.001f);
                    me->MonsterMoveWithSpeed(me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), speed);
                    _flyPhase = false;
                    events.ScheduleEvent(EVENT_LAND_LAND, 1000);
                    events.PopEvent();
                    break;
                }
                case EVENT_LAND_LAND:
                    me->SetCanFly(false);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->SetDisableGravity(false);
                    if (_flyTarget)
                        me->Attack(_flyTarget, false);

                    me->SetRegeneratingHealth(true);
                    _flyTarget = NULL;
                    me->RemoveAura(SPELL_LIGHTNING_TENDRILS);
                    me->RemoveAura(61883);
                    DoResetThreat();
                    events.PopEvent();
                    me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_INTERRUPT_CAST, false);
                    break;
                case EVENT_ENRAGE:
                    me->MonsterYell("This meeting of the Assembly of Iron is adjourned!", LANG_UNIVERSAL, 0);
                    me->PlayDirectSound(SOUND_BRUNDIR_BERSERK);
                    me->CastSpell(me, SPELL_BERSERK, true);
                    events.PopEvent();
                    break;
            }

            DoMeleeAttackIfReady();
        }
    };
};

struct npc_overload_ball_assembly_AI : public ScriptedAI
{
    npc_overload_ball_assembly_AI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        me->SetReactState(REACT_PASSIVE);
        DoCastSelf(SPELL_OVERLOAD_GROW_VISUAL);
        me->DespawnOrUnsummon(6s);
    }
    
    void MoveInLineOfSight(Unit* /*who*/) override { }
    void EnterCombat(Unit* /*who*/) override { }
    void AttackStart(Unit* /*who*/) override { }
    void EnterEvadeMode() override { }
};

class spell_shield_of_runes : public SpellScriptLoader
{
    public:
        spell_shield_of_runes() : SpellScriptLoader("spell_shield_of_runes") { }

        class spell_shield_of_runes_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_shield_of_runes_AuraScript);

            void OnRemove(AuraEffect const* aurEff, AuraEffectHandleModes /*mode*/)
            {
                if (Unit* owner = GetUnitOwner())
                    if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_ENEMY_SPELL && aurEff->GetAmount() <= 0)
                        owner->CastSpell(owner, SPELL_SHIELD_OF_RUNES_BUFF, false);
            }

            void Register()
            {
                 AfterEffectRemove += AuraEffectRemoveFn(spell_shield_of_runes_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_SCHOOL_ABSORB, AURA_EFFECT_HANDLE_REAL);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_shield_of_runes_AuraScript();
        }
};

class spell_assembly_overwhelming_power_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_assembly_overwhelming_power_AuraScript);

    void HandleRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (!GetCaster())
            return;

        if (InstanceScript* instance = GetCaster()->GetInstanceScript())
            if (Creature* Steelbreaker = ObjectAccessor::GetCreature(*GetCaster(), instance->GetData64(DATA_STEELBREAKER)))
                Steelbreaker->AI()->DoAction(ACTION_ADD_CHARGE);
    }

    void Register() override
    {
        OnEffectRemove += AuraEffectRemoveFn(spell_assembly_overwhelming_power_AuraScript::HandleRemove, EFFECT_0, SPELL_AURA_MOD_DAMAGE_PERCENT_DONE, AURA_EFFECT_HANDLE_REAL);
    }
};

class spell_assembly_rune_of_summoning : public SpellScriptLoader
{
    public:
        spell_assembly_rune_of_summoning() : SpellScriptLoader("spell_assembly_rune_of_summoning") { }

        class spell_assembly_rune_of_summoning_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_assembly_rune_of_summoning_AuraScript);

            void OnPeriodic(AuraEffect const* aurEff)
            {
                if (Unit* caster = GetCaster())
                    if (aurEff->GetTickNumber() % 2 == 0)
                        caster->SummonCreature(CREATURE_LIGHTNING_ELEMENTAL, caster->GetPositionX(), caster->GetPositionY(), caster->GetPositionZ(), 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 2000);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_assembly_rune_of_summoning_AuraScript::OnPeriodic, EFFECT_0, SPELL_AURA_PERIODIC_DUMMY);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_assembly_rune_of_summoning_AuraScript();
        }
};

class spell_summon_overload_ball_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_summon_overload_ball_SpellScript);

    void ModDestHeight(SpellEffIndex effIndex)
    {
        if (!GetCaster())
            return;

        WorldLocation* dest = const_cast<WorldLocation*>(GetExplTargetDest());
        Position pos = GetCaster()->GetPosition();
        GetCaster()->GetClosePoint(pos.m_positionX, pos.m_positionY, pos.m_positionZ, GetCaster()->GetObjectSize() / 3, 0.5f);

        pos.m_positionZ += 3.0f;
        dest->Relocate(pos);
        GetHitDest()->Relocate(pos);
    }

    void Register()
    {
        OnEffectHit += SpellEffectFn(spell_summon_overload_ball_SpellScript::ModDestHeight, EFFECT_0, SPELL_EFFECT_SUMMON);
    }
};

class achievement_assembly_of_iron : public AchievementCriteriaScript
{
    public:
        achievement_assembly_of_iron(char const* name, uint32 entry) : AchievementCriteriaScript(name),
            _targetEntry(entry)
        {
        }

        bool OnCheck(Player* player, Unit* target)
        {
            return target && target->GetAuraCount(SPELL_SUPERCHARGE) >= 2 && (!_targetEntry || target->GetEntry() == _targetEntry);
        }

    private:
        uint32 const _targetEntry;
};

class achievement_cant_do_that_while_stunned : public AchievementCriteriaScript
{
    public:
        achievement_cant_do_that_while_stunned() : AchievementCriteriaScript("achievement_cant_do_that_while_stunned") {}

        bool OnCheck(Player* player, Unit* target)
        {
            bool allow = target && target->GetAuraCount(SPELL_SUPERCHARGE) >= 2;
            if (!allow)
                return false;

            if (InstanceScript* instance = target->GetInstanceScript())
                if (Creature* cr = ObjectAccessor::GetCreature(*target, instance->GetData64(DATA_BRUNDIR)))
                    return cr->AI()->GetData(DATA_BRUNDIR);

            return false;
        }
};

void AddSC_boss_assembly_of_iron()
{
    new boss_steelbreaker();
    new boss_runemaster_molgeim();
    new boss_stormcaller_brundir();
    new CreatureAILoader<npc_assembly_lightningAI>("npc_assembly_lightning");
    new CreatureAILoader<npc_overload_ball_assembly_AI>("npc_overload_ball_assembly");

    new spell_shield_of_runes();
    new AuraScriptLoaderEx<spell_assembly_overwhelming_power_AuraScript>("spell_assembly_overwhelming_power");
    new spell_assembly_rune_of_summoning();
    new SpellScriptLoaderEx<spell_summon_overload_ball_SpellScript>("spell_summon_overload_ball");

    new achievement_assembly_of_iron("achievement_but_im_on_your_side", 0);
    new achievement_assembly_of_iron("achievement_assembly_steelbreaker", NPC_STEELBREAKER);
    new achievement_assembly_of_iron("achievement_assembly_runemaster", NPC_MOLGEIM);
    new achievement_assembly_of_iron("achievement_assembly_stormcaller", NPC_BRUNDIR);
    new achievement_cant_do_that_while_stunned();
}
