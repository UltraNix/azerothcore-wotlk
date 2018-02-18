/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "naxxramas.h"
#include "SpellScript.h"
#include "Player.h"

enum Says
{
    // Stalagg
    SAY_STAL_AGGRO                     = 0,
    SAY_STAL_SLAY                      = 1,
    SAY_STAL_DEATH                     = 2,

    // Feugen
    SAY_FEUG_AGGRO                     = 0,
    SAY_FEUG_SLAY                      = 1,
    SAY_FEUG_DEATH                     = 2,

    // Thaddius
    SAY_GREET                          = 0,
    SAY_AGGRO                          = 1,
    SAY_SLAY                           = 2,
    SAY_ELECT                          = 3,
    SAY_DEATH                          = 4,
    SAY_SCREAM                         = 5
};

enum Spells
{
    SPELL_MAGNETIC_PULL                = 28337,
    SPELL_TESLA_SHOCK                  = 28099,

    // Stalagg
    SPELL_POWER_SURGE_10               = 54529,
    SPELL_POWER_SURGE_25               = 28134,
    SPELL_STALAGG_CHAIN                = 28096,

    // Feugen
    SPELL_STATIC_FIELD_10              = 28135,
    SPELL_STATIC_FIELD_25              = 54528,
    SPELL_FEUGEN_CHAIN                 = 28111,

    // Thaddius
    SPELL_POLARITY_SHIFT               = 28089,
    SPELL_BALL_LIGHTNING               = 28299,
    SPELL_CHAIN_LIGHTNING_10           = 28167,
    SPELL_CHAIN_LIGHTNING_25           = 54531,
    SPELL_BERSERK                      = 27680,

    SPELL_THADDIUS_VISUAL_LIGHTNING    = 28136,
    SPELL_THADDIUS_SPAWN_STUN          = 28160,

    SPELL_POSITIVE_CHARGE              = 28062,
    SPELL_POSITIVE_CHARGE_STACK        = 29659,
    SPELL_NEGATIVE_CHARGE              = 28085,
    SPELL_NEGATIVE_CHARGE_STACK        = 29660,
    SPELL_POSITIVE_POLARITY            = 28059,
    SPELL_NEGATIVE_POLARITY            = 28084,
    SPELL_STOMP_BOOST                  = 45185
};

enum Events
{
    EVENT_MINION_SPELL_POWER_SURGE               = 1,
    EVENT_MINION_SPELL_MAGNETIC_PULL             = 2,
    EVENT_MINION_CHECK_DISTANCE                  = 3,
    EVENT_MINION_SPELL_STATIC_FIELD              = 4,

    EVENT_THADDIUS_START                         = 10,
    EVENT_THADDIUS_SPELL_CHAIN_LIGHTNING         = 11,
    EVENT_THADDIUS_SPELL_BERSERK                 = 12,
    EVENT_THADDIUS_POLARITY_SHIFT                = 13,
    EVENT_THADDIUS_START_2                       = 14,
    EVENT_STOMP_BOOST                            = 15
};

enum Misc
{
    ACTION_MAGNETIC_PULL                         = 1,
    ACTION_SUMMON_DIED                           = 2,
    ACTION_RESTORE                               = 3,
    NPC_TESLA_COIL                               = 16218 // the coils (emotes "Tesla Coil overloads!")
};

Position const ThaddiusMiddleOfTheRoom = { 3472.996826f, -2966.209717f, 315.730194f, 3.972281f };

class boss_thaddius : public CreatureScript
{
public:
    boss_thaddius() : CreatureScript("boss_thaddius") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thaddiusAI (pCreature);
    }

    struct boss_thaddiusAI : public ScriptedAI
    {
        boss_thaddiusAI(Creature *c) : ScriptedAI(c), summons(me)
        {
            pInstance = me->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        SummonList summons;

        uint32 summonTimer;
        uint32 reviveTimer;
        uint32 resetTimer;
        uint32 _fightTimer;

        void StartEvent()
        {
            me->RemoveAllAuras();
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            events.ScheduleEvent(EVENT_THADDIUS_START_2, 1000);

            for (SummonList::const_iterator itr = summons.begin(); itr != summons.end(); ++itr)
            {
                if (Creature* cr = ObjectAccessor::GetCreature(*me, (*itr)))
                {
                    if (cr->GetEntry() == NPC_TESLA_COIL)
                    {
                        cr->CastSpell(me, SPELL_TESLA_SHOCK, true); // till smth better is found ;( ZOMG
                        Unit::Kill(cr, cr);
                    }
                }
            }
        }

        void DespawnThaddiusAtEvade()
        {
            summons.DespawnAll();

            me->DespawnOrUnsummon(0, 20);

            if (pInstance)
            {
                pInstance->SetData(EVENT_THADDIUS, NOT_STARTED);
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetData64(DATA_THADDIUS_GATE)))
                    go->SetGoState(GO_STATE_ACTIVE);
            }
        }

        void JustReachedHome() override
        {
            DespawnThaddiusAtEvade();
        }

        bool CheckEvadeIfOutOfCombatArea() const override
        {
            return !SelectTargetFromPlayerList(125.0f) || me->GetDistance(ThaddiusMiddleOfTheRoom) > 75.0f;
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_SUMMON_DIED)
            {
                // Hooray, we did it!
                if (summonTimer)
                {
                    summonTimer = 0;
                    reviveTimer = 1;
                    //events.ScheduleEvent(EVENT_THADDIUS_START, 12000);
                    return;
                }

                summonTimer = 1;
            }
        }

        void Reset()
        {
            _fightTimer = 0;
            events.Reset();
            summons.DespawnAll();
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            summonTimer = 0;
            reviveTimer = 0;
            resetTimer = 1;
            me->SetPosition(me->GetHomePosition());

            if (pInstance)
            {
                pInstance->SetData(EVENT_THADDIUS, NOT_STARTED);
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetData64(DATA_THADDIUS_GATE)))
                    go->SetGoState(GO_STATE_ACTIVE);
            }

            me->SummonCreature(NPC_STALAGG, 3450.45f, -2931.42f, 312.091f, 5.49779f);
            me->SummonCreature(NPC_FEUGEN, 3508.14f, -2988.65f, 312.092f, 2.37365f);

            if (Creature* cr = me->SummonCreature(NPC_TESLA_COIL, 3527.34f, -2951.56f, 318.75f, 0.0f))
            {
                cr->RemoveAllAuras();
                cr->InterruptNonMeleeSpells(true);
                cr->CastSpell(cr, SPELL_FEUGEN_CHAIN, false);
                cr->SetDisableGravity(true);
            }

            if (Creature* cr = me->SummonCreature(NPC_TESLA_COIL, 3487.04f, -2911.68f, 318.75f, 0.0f))
            {
                cr->RemoveAllAuras();
                cr->InterruptNonMeleeSpells(true);
                cr->CastSpell(cr, SPELL_STALAGG_CHAIN, false);
                cr->SetDisableGravity(true);
            }
        }

        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (!urand(0,3))
                Talk(SAY_SLAY);

            if (pInstance)
                pInstance->SetData(DATA_IMMORTAL_FAIL, 0);
        }

        void JustDied(Unit* killer)
        {
            Talk(SAY_DEATH);

            if (pInstance)
            {
                pInstance->SetData(EVENT_THADDIUS, DONE);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(28059);
                pInstance->DoRemoveAurasDueToSpellOnPlayers(28084);
            }

            if (Map* map = me->GetMap())
                CheckCreatureRecord(killer, me->GetCreatureTemplate()->Entry, map->GetDifficulty(), "", 15000, _fightTimer);
        }

        void JustSummoned(Creature* cr)
        {
            summons.Summon(cr);
        }

        void EnterCombat(Unit *who)
        {
            me->SetHealth(me->GetMaxHealth());
            _fightTimer = getMSTime();
            me->SetInCombatWithZone();
            summons.DoZoneInCombat(NPC_FEUGEN);
            summons.DoZoneInCombat(NPC_STALAGG);

            if (pInstance)
            {
                pInstance->SetData(EVENT_THADDIUS, IN_PROGRESS);
                if (GameObject* go = me->GetMap()->GetGameObject(pInstance->GetData64(DATA_THADDIUS_GATE)))
                    go->SetGoState(GO_STATE_READY);
            }
        }

        void PolarityDamage()
        {
            if (!sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS))
                return;

            uint32 polarDamage = urand(4200, 5000);

            Map::PlayerList const &pl = me->GetMap()->GetPlayers();
            for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
                Unit::DealDamage(itr->GetSource(), itr->GetSource(), polarDamage, nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
        }

        void UpdateAI(uint32 diff)
        {
            if (resetTimer)
            {
                resetTimer += diff;
                if (resetTimer > 1000)
                {
                    resetTimer = 0;
                    me->CastSpell(me, SPELL_THADDIUS_SPAWN_STUN, true);
                }
                return;
            }
            if (reviveTimer)
            {
                reviveTimer += diff;
                if (reviveTimer >= 12000)
                {
                    StartEvent();
                    reviveTimer = 0;
                }
                return;
            }

            if (!UpdateVictim())
               return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            // Revive code!
            if (summonTimer)
            {
                summonTimer += diff;
                if (summonTimer >= 5000)
                {
                    summons.DoAction(ACTION_RESTORE);
                    summonTimer = 0;
                }
            }

            switch (events.GetEvent())
            {
                //case EVENT_THADDIUS_START:
                //    StartEvent();
                //    events.PopEvent();
                //    break;
                case EVENT_THADDIUS_START_2:
                    events.PopEvent();
                    Talk(SAY_AGGRO);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->SetControlled(false, UNIT_STATE_STUNNED);
                    me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    me->setAttackTimer(BASE_ATTACK, 4000);

                    if (sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS) && me->GetMap()->Is25ManRaid())
                        events.ScheduleEvent(EVENT_STOMP_BOOST, 10000);

                    events.ScheduleEvent(EVENT_THADDIUS_SPELL_CHAIN_LIGHTNING, 14000);
                    events.ScheduleEvent(EVENT_THADDIUS_SPELL_BERSERK, 360000);
                    events.ScheduleEvent(EVENT_THADDIUS_POLARITY_SHIFT, 30000);
                    return;
                case EVENT_STOMP_BOOST:
                    if (!sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS))
                        break;
                    me->CastSpell(me->GetVictim(), SPELL_STOMP_BOOST, false);
                    me->GetMap()->Is25ManRaid() ? events.RepeatEvent(10000) : events.PopEvent();
                    break;
                case EVENT_THADDIUS_SPELL_BERSERK:
                    me->CastSpell(me, SPELL_BERSERK, true);
                    events.PopEvent();
                    break;
                case EVENT_THADDIUS_SPELL_CHAIN_LIGHTNING:
                    me->CastSpell(me->GetVictim(), RAID_MODE(SPELL_CHAIN_LIGHTNING_10, SPELL_CHAIN_LIGHTNING_25), false);
                    events.RepeatEvent(15000);
                    break;
                case EVENT_THADDIUS_POLARITY_SHIFT:
                    me->CastSpell(me, SPELL_POLARITY_SHIFT, false);
                    PolarityDamage();
                    events.RepeatEvent(sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS) ? RAID_MODE(30000, 20000) : 30000);
                    break;
            }

            if (me->isAttackReady())
            {
                if (!me->IsWithinMeleeRange(me->GetVictim()))
                    me->CastSpell(me->GetVictim(), SPELL_BALL_LIGHTNING, false);
                else
                    DoMeleeAttackIfReady();
            }
            EnterEvadeIfOutOfCombatArea();
        }
    };
};

class boss_thaddius_summon : public CreatureScript
{
public:
    boss_thaddius_summon() : CreatureScript("boss_thaddius_summon") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_thaddius_summonAI (pCreature);
    }

    struct boss_thaddius_summonAI : public ScriptedAI
    {
        boss_thaddius_summonAI(Creature *c) : ScriptedAI(c)
        {
           pInstance = me->GetInstanceScript();
        }

        InstanceScript* pInstance;
        EventMap events;
        uint32 pullTimer;
        uint32 visualTimer;

        void Reset()
        {
            if (me->IsInCombat())
                return;

            pullTimer = 0;
            visualTimer = 1;

            events.Reset();
            me->SetControlled(false, UNIT_STATE_STUNNED);
            if (Creature* cr = me->FindNearestCreature(NPC_TESLA_COIL, 150.0f))
                cr->CastSpell(cr, me->GetEntry() == NPC_STALAGG ? SPELL_STALAGG_CHAIN : SPELL_FEUGEN_CHAIN, false);
        }

        void EnterEvadeMode()
        {
           me->SetControlled(false, UNIT_STATE_STUNNED);
           ScriptedAI::EnterEvadeMode();

           if (pInstance)
           {
               if (Creature* thaddius = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_THADDIUS_BOSS)))
                   if (thaddius->GetAI())
                       if (!thaddius->IsInEvadeMode())
                           thaddius->AI()->EnterEvadeMode();
           }
        }

        void EnterCombat(Unit* pWho)
        {
            me->SetInCombatWithZone();

            if (me->GetEntry() == NPC_STALAGG)
            {
                events.ScheduleEvent(EVENT_MINION_SPELL_POWER_SURGE, 10s);
                Talk(SAY_STAL_AGGRO);
            }
            else
            {
                events.ScheduleEvent(EVENT_MINION_SPELL_STATIC_FIELD, 5s);
                Talk(SAY_FEUG_AGGRO);
            }

            events.ScheduleEvent(EVENT_MINION_CHECK_DISTANCE, 5s);

            // This event needs synchronisation, called for stalagg only
            if (me->GetEntry() == NPC_STALAGG)
                events.ScheduleEvent(EVENT_MINION_SPELL_MAGNETIC_PULL, 25s);

            if (pInstance)
                if (Creature* cr = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_THADDIUS_BOSS)))
                {
                    cr->AI()->AttackStart(pWho);
                    cr->AddThreat(pWho, 10.0f);
                }
        }

        void DoAction(int32 param)
        {
            if (param == ACTION_MAGNETIC_PULL)
            {
                pullTimer = 1;
                me->SetControlled(true, UNIT_STATE_STUNNED);
            }
            else if (param == ACTION_RESTORE)
            {
                if (!me->IsAlive())
                {
                    me->Respawn();
                    Reset();
                    DoZoneInCombat(nullptr, 500.f);
                }
                else
                    me->SetHealth(me->GetMaxHealth());
            }
        }

        void JustDied(Unit* )
        {
            Talk(me->GetEntry() == NPC_STALAGG ? SAY_FEUG_DEATH : SAY_STAL_DEATH);
            if (pInstance)
                if (Creature* cr = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_THADDIUS_BOSS)))
                    cr->AI()->DoAction(ACTION_SUMMON_DIED);
        }

        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (pInstance)
                pInstance->SetData(DATA_IMMORTAL_FAIL, 0);

            if (!urand(0,2))
                Talk(me->GetEntry() == NPC_STALAGG ? SAY_FEUG_SLAY : SAY_STAL_SLAY);
        }

        bool IsUnitInRoom(Unit* who)
        {
            if (!who)
                return false;

            if (who->GetDistance(ThaddiusMiddleOfTheRoom) > 80.0f)
                return false;

            return true;
        }

        bool CheckEvadeIfOutOfCombatArea() const override
        {
            return me->GetDistance(ThaddiusMiddleOfTheRoom) > 80.0f;
        }

        void UpdateAI(uint32 diff)
        {
            if (visualTimer)
            {
                visualTimer += diff;
                if (visualTimer >= 3000)
                {
                    visualTimer = 0;
                    if (Creature* cr = me->FindNearestCreature(NPC_TESLA_COIL, 150.0f))
                        cr->CastSpell(cr, me->GetEntry() == NPC_STALAGG ? SPELL_STALAGG_CHAIN : SPELL_FEUGEN_CHAIN, false);
                }
            }

            if (!UpdateVictim())
                return;

            // Disable AI during pull
            if (pullTimer)
            {
                pullTimer += diff;
                if (pullTimer >= 3000)
                {
                    me->SetControlled(false, UNIT_STATE_STUNNED);
                    pullTimer = 0;
                }
                return;
            }

            events.Update(diff);
            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_MINION_SPELL_POWER_SURGE:
                        me->CastSpell(me, RAID_MODE(SPELL_POWER_SURGE_10, SPELL_POWER_SURGE_25), false);
                        events.Repeat(19s);
                        break;
                    case EVENT_MINION_SPELL_STATIC_FIELD:
                        if (sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS))
                        {
                            if (me->GetMap()->Is25ManRaid())
                            {
                                int32 dmg = urand(5000, 5400);
                                me->CastCustomSpell(me, SPELL_STATIC_FIELD_25, &dmg, nullptr, nullptr, false);
                            }
                            else
                                me->CastSpell(me, SPELL_STATIC_FIELD_10, false);
                        }
                        else
                            me->CastSpell(me, RAID_MODE(SPELL_STATIC_FIELD_10, SPELL_STATIC_FIELD_25), false);

                        events.Repeat(3s);
                        break;
                    case EVENT_MINION_SPELL_MAGNETIC_PULL:
                        events.Repeat(25s);
                        if (pInstance)
                        {
                            if (Creature* feugen = ObjectAccessor::GetCreature(*me, pInstance->GetData64(DATA_FEUGEN_BOSS)))
                            {
                                if (!feugen->IsAlive() || !feugen->GetVictim() || !me->GetVictim())
                                    return;

                                float threatFeugen = feugen->getThreatManager().getThreat(feugen->GetVictim());
                                float threatStalagg = me->getThreatManager().getThreat(me->GetVictim());
                                Unit* tankFeugen = feugen->GetVictim();
                                Unit* tankStalagg = me->GetVictim();

                                if (!IsUnitInRoom(tankFeugen) || !IsUnitInRoom(tankStalagg))
                                    return;

                                feugen->getThreatManager().modifyThreatPercent(tankFeugen, -100);
                                feugen->AddThreat(tankStalagg, threatFeugen);
                                feugen->CastSpell(tankStalagg, SPELL_MAGNETIC_PULL, true);
                                feugen->AI()->DoAction(ACTION_MAGNETIC_PULL);

                                me->getThreatManager().modifyThreatPercent(tankStalagg, -100);
                                me->AddThreat(tankFeugen, threatStalagg);
                                me->CastSpell(tankFeugen, SPELL_MAGNETIC_PULL, true);
                                DoAction(ACTION_MAGNETIC_PULL);
                            }
                        }
                        break;
                    case EVENT_MINION_CHECK_DISTANCE:
                        if (Creature* cr = me->FindNearestCreature(NPC_TESLA_COIL, 150.0f))
                        {
                            if (me->GetExactDist(cr) > 60.0f || me->GetExactDist(cr) < 20.0f)
                            {
                                cr->InterruptNonMeleeSpells(true);
                                cr->CastSpell(me->GetVictim(), SPELL_TESLA_SHOCK, true); // dont know real spell
                                events.Repeat(1.5s);
                                break;
                            }
                            else
                            {
                                cr->CastSpell(cr, me->GetEntry() == NPC_STALAGG ? SPELL_STALAGG_CHAIN : SPELL_FEUGEN_CHAIN, false);
                            }
                        }

                        events.Repeat(5s);
                        break;
                }
            }

            EnterEvadeIfOutOfCombatArea();
            DoMeleeAttackIfReady();
        }
    };
};

class spell_thaddius_pos_neg_charge : public SpellScriptLoader
{
    public:
        spell_thaddius_pos_neg_charge() : SpellScriptLoader("spell_thaddius_pos_neg_charge") { }

        class spell_thaddius_pos_neg_charge_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_thaddius_pos_neg_charge_SpellScript);

            void HandleTargets(std::list<WorldObject*>& targets)
            {
                uint8 count = 0;
                for (std::list<WorldObject*>::iterator ihit = targets.begin(); ihit != targets.end(); ++ihit)
                    if ((*ihit)->GetGUID() != GetCaster()->GetGUID())
                        if (Player* target = (*ihit)->ToPlayer())
                            if (target->HasAura(GetTriggeringSpell()->Id))
                                ++count;

                if (count)
                {
                    uint32 spellId = 0;

                    if (GetSpellInfo()->Id == SPELL_POSITIVE_CHARGE)
                        spellId = SPELL_POSITIVE_CHARGE_STACK;
                    else // if (GetSpellInfo()->Id == SPELL_NEGATIVE_CHARGE)
                        spellId = SPELL_NEGATIVE_CHARGE_STACK;

                    GetCaster()->SetAuraStack(spellId, GetCaster(), count);
                }
            }

            void HandleDamage(SpellEffIndex /*effIndex*/)
            {
                if (!GetTriggeringSpell())
                    return;

                Unit* target = GetHitUnit();
                if (!target)
                    return;

                if (target->HasAura(GetTriggeringSpell()->Id) || target->GetTypeId() != TYPEID_PLAYER)
                    SetHitDamage(0);
                else if (target->GetInstanceScript())
                    target->GetInstanceScript()->SetData(DATA_CHARGES_CROSSED, 0);
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_thaddius_pos_neg_charge_SpellScript::HandleDamage, EFFECT_0, SPELL_EFFECT_SCHOOL_DAMAGE);
                OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_thaddius_pos_neg_charge_SpellScript::HandleTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ALLY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_thaddius_pos_neg_charge_SpellScript();
        }
};

class spell_thaddius_polarity_shift : public SpellScriptLoader
{
    public:
        spell_thaddius_polarity_shift() : SpellScriptLoader("spell_thaddius_polarity_shift") { }

        class spell_thaddius_polarity_shift_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_thaddius_polarity_shift_SpellScript);

            bool Validate(SpellInfo const* /*spell*/)
            {
                if (!sSpellMgr->GetSpellInfo(SPELL_POSITIVE_POLARITY) || !sSpellMgr->GetSpellInfo(SPELL_NEGATIVE_POLARITY))
                    return false;
                return true;
            }

            void HandleDummy(SpellEffIndex /* effIndex */)
            {
                Unit* caster = GetCaster();
                if (Unit* target = GetHitUnit())
                    target->CastSpell(target, roll_chance_i(50) ? SPELL_POSITIVE_POLARITY : SPELL_NEGATIVE_POLARITY, true, NULL, NULL, caster->GetGUID());
            }

            void Register()
            {
                OnEffectHitTarget += SpellEffectFn(spell_thaddius_polarity_shift_SpellScript::HandleDummy, EFFECT_0, SPELL_EFFECT_DUMMY);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_thaddius_polarity_shift_SpellScript();
        }
};

void AddSC_boss_thaddius()
{
    new boss_thaddius();
    new boss_thaddius_summon();

    new spell_thaddius_pos_neg_charge();
    new spell_thaddius_polarity_shift();
}
