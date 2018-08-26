#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "molten_core.h"
#include "Player.h"
#include "CreatureTextMgr.h"

enum Texts
{
    SAY_AGGRO               = 0,
    SAY_SPAWN               = 1,
    SAY_SLAY_1              = 2,
    SAY_SLAY_2              = 3,
    SAY_LAST_ADD            = 4,
    // Defeat (before teleport)
    SAY_DEFEAT_1            = 5,
    SAY_DEFEAT_2            = 6,
    SAY_DEFEAT_3            = 7,
    // Ragnaros summon (Executus texts)
    SAY_SUMMON_MAJ          = 8,
    SAY_SUMMON_MAJ_1        = 9,
    SAY_SUMMON_MAJ_2        = 10,
    SAY_SUMMON_MAJ_3        = 11,
    // Ragnaros summon (Ragnaros texts)
    SAY_SUMMON_RAG_1        = 0,
    SAY_SUMMON_RAG_2        = 1
};

enum Spells
{
    SPELL_MAGIC_REFLECTION  = 20619,
    SPELL_DAMAGE_REFLECTION = 21075,
    SPELL_AEGIS             = 20620,
    SPELL_TELEPORT_RANDOM   = 20618,
    SPELL_TELEPORT_TARGET   = 20534,
    SPELL_IMMUNE_POLY       = 21087,

    SPELL_TELEPORT_VISUAL   = 19484,
    SPELL_TELEPORT_EFFECT   = 19527,
    SPELL_SUMMON_RAGNAROS   = 19774,
    SPELL_ELEMENTAL_FIRE    = 19773,
};

enum Events
{
    EVENT_REFLECTION_SHIELD = 1,
    EVENT_TELEPORT_TARGET,
    EVENT_TELEPORT_RANDOM,

    // Defeat (before teleport)
    EVENT_DEFEAT_1,
    EVENT_DEFEAT_2,
    EVENT_DEFEAT_3,
    EVENT_TELE_TO_RAGNAROS_VISUAL,
    EVENT_TELE_TO_RAGNAROS_EFFECT,

    // Ragnaros summon stuff
    EVENT_RAG_SUMMON_1,
    EVENT_RAG_SUMMON_2,
    EVENT_RAG_SUMMON_3,
    EVENT_RAG_SUMMON_4,
    EVENT_RAG_SUMMON_5,
    EVENT_RAG_SUMMON_6,
    EVENT_RAG_SUMMON_7,
    EVENT_RAG_SUMMON_8,
};

enum Misc
{
    POINT_DEFEAT            = 1,

    MENU_SUMMON_RAG         = 2002
};

struct boss_majordomoAI : public BossAI
{
    boss_majordomoAI(Creature* creature) : BossAI(creature, BOSS_MAJORDOMO_EXECUTUS)
    {
        if (instance->GetBossState(BOSS_MAJORDOMO_EXECUTUS) != DONE)
            sCreatureTextMgr->SendChat(me, SAY_SPAWN, nullptr, CHAT_MSG_ADDON, LANG_ADDON, TEXT_RANGE_ZONE);
    }

    void Reset() override
    {
        _addsKilled = 0;
    }

    void KilledUnit(Unit* victim)
    {
        if (victim->GetTypeId() == TYPEID_PLAYER && roll_chance_i(25))
            Talk(RAND(SAY_SLAY_1, SAY_SLAY_2));
    }

    void JustSummoned(Creature* summon) override
    {
        summons.Summon(summon);
    }

    void EnterEvadeMode() override
    {
        _EnterEvadeMode();
        me->GetMotionMaster()->MoveTargetedHome();
        summons.Broadcast([](Creature* summon)
        {
            summon->Respawn();
            summon->AI()->EnterEvadeMode();
            summon->GetMotionMaster()->MoveTargetedHome();
        });
    }

    void EnterCombat(Unit* /*who*/)
    {
        _EnterCombat();
        Talk(SAY_AGGRO);
        summons.DoZoneInCombat();
        events.ScheduleEvent(EVENT_REFLECTION_SHIELD, 15000);
        events.ScheduleEvent(EVENT_TELEPORT_RANDOM, 15000);
        events.ScheduleEvent(EVENT_TELEPORT_TARGET, 30000);
    }

    void SummonedCreatureDies(Creature* summon, Unit* /*killer*/) override
    {
        if (summon->GetEntry() == NPC_FLAMEWAKER_HEALER || summon->GetEntry() == NPC_FLAMEWAKER_ELITE)
        {
            switch (++_addsKilled)
            {
                case 4:
                    DoCastSelf(SPELL_IMMUNE_POLY, true);
                    break;
                case 7:
                    Talk(SAY_LAST_ADD);
                    break;
                case 8:
                    _JustDied();
                    me->GetMap()->UpdateEncounterState(ENCOUNTER_CREDIT_KILL_CREATURE, me->GetEntry(), me);
                    me->setFaction(35);
                    _EnterEvadeMode();
                    me->GetMotionMaster()->MovePoint(1, me->GetHomePosition(), false);
                    me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                    break;
                default:
                    break;
            }
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (me->movespline->Finalized())
            me->SetFacingTo(5.2f);
        if (id == POINT_DEFEAT && type == POINT_MOTION_TYPE)
        {
            events.ScheduleEvent(EVENT_DEFEAT_1, 1);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
    }

    void DamageTaken(Unit* /*attacker*/, uint32& damage, DamageEffectType /*damagetype*/, SpellSchoolMask /*spellschoolmask*/) override
    {
        if (damage > me->GetHealth())
            damage = me->GetHealth() - 1;
        if (me->HealthBelowPctDamaged(50, damage))
            DoCast(me, SPELL_AEGIS, true);
    }

    void UpdateAI(uint32 diff) override
    {
        if (instance->GetBossState(BOSS_MAJORDOMO_EXECUTUS) != DONE)
        {
            if (!UpdateVictim())
                return;

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_REFLECTION_SHIELD:
                        DoCast(me, RAND(SPELL_DAMAGE_REFLECTION, SPELL_MAGIC_REFLECTION));
                        events.Repeat(30000);
                        break;
                    case EVENT_TELEPORT_TARGET:
                        DoCastVictim(SPELL_TELEPORT_TARGET);
                        events.Repeat(urand(25000, 30000));
                        break;
                    case EVENT_TELEPORT_RANDOM:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 1, 0.f, true))
                            DoCast(target, SPELL_TELEPORT_RANDOM);
                        events.Repeat(urand(25000, 30000));
                        break;
                    default:
                        break;
                }

                if (me->HasUnitState(UNIT_STATE_CASTING))
                    return;
            }

            DoMeleeAttackIfReady();
        }
        else
        {
            events.Update(diff);

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_DEFEAT_1:
                        summons.DespawnAll();
                        me->SetFacingTo(3.12414f);
                        Talk(SAY_DEFEAT_1);
                        events.ScheduleEvent(EVENT_DEFEAT_2, 7500);
                        break;
                    case EVENT_DEFEAT_2:
                        Talk(SAY_DEFEAT_2);
                        events.ScheduleEvent(EVENT_DEFEAT_3, 8000);
                        break;
                    case EVENT_DEFEAT_3:
                        Talk(SAY_DEFEAT_3);
                        events.ScheduleEvent(EVENT_TELE_TO_RAGNAROS_VISUAL, 21500);
                        break;
                    case EVENT_TELE_TO_RAGNAROS_VISUAL:
                        DoCastSelf(SPELL_TELEPORT_VISUAL, true);
                        me->setFaction(35);
                        events.ScheduleEvent(EVENT_TELE_TO_RAGNAROS_EFFECT, 1000);
                        break;
                    case EVENT_TELE_TO_RAGNAROS_EFFECT:
                        me->DespawnOrUnsummon();                        
                        break;
                    case EVENT_RAG_SUMMON_1:
                        me->setActive(false);
                        Talk(SAY_SUMMON_MAJ_1);
                        events.ScheduleEvent(EVENT_RAG_SUMMON_2, 1000);
                        break;
                    case EVENT_RAG_SUMMON_2:
                    {
                        DoCast(SPELL_SUMMON_RAGNAROS);
                        me->SetWalk(true);
                        Movement::PointsArray path;
                        for (uint8 i = 0; i < 3; ++i)
                            path.push_back(G3D::Vector3(MajordomoPath[i].GetPositionX(), MajordomoPath[i].GetPositionY(), MajordomoPath[i].GetPositionZ()));

                        me->GetMotionMaster()->MoveSplinePath(&path);
                        events.ScheduleEvent(EVENT_RAG_SUMMON_3, 11500);
                        break;
                    }
                    case EVENT_RAG_SUMMON_3:
                        Talk(SAY_SUMMON_MAJ_2);
                        events.ScheduleEvent(EVENT_RAG_SUMMON_4, 8000);
                        break;
                    case EVENT_RAG_SUMMON_4:
                        instance->instance->SummonCreature(NPC_RAGNAROS, RagnarosSummonPos, nullptr, 172800000);
                        if (Creature* ragnaros = _GetRagnaros())
                            ragnaros->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
                        events.ScheduleEvent(EVENT_RAG_SUMMON_5, 8700);
                        break;
                    case EVENT_RAG_SUMMON_5:
                        if (Creature* ragnaros = _GetRagnaros())
                            ragnaros->AI()->Talk(SAY_SUMMON_RAG_1);
                        events.ScheduleEvent(EVENT_RAG_SUMMON_6, 11700);
                        break;
                    case EVENT_RAG_SUMMON_6:
                        Talk(SAY_SUMMON_MAJ_3);
                        events.ScheduleEvent(EVENT_RAG_SUMMON_7, 8700);
                        break;
                    case EVENT_RAG_SUMMON_7:
                        if (Creature* ragnaros = _GetRagnaros())
                            ragnaros->AI()->Talk(SAY_SUMMON_RAG_2);
                        events.ScheduleEvent(EVENT_RAG_SUMMON_8, 16500);
                        break;
                    case EVENT_RAG_SUMMON_8:
                        if (Creature* ragnaros = _GetRagnaros())
                        {
                            ragnaros->CastSpell(me, SPELL_ELEMENTAL_FIRE);
                            ragnaros->AI()->DoAction(1);
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }

    void sGossipSelect(Player* player, uint32 menuId, uint32 /*gossipListId*/) override
    {
        if (menuId == MENU_SUMMON_RAG)
        {
            player->CLOSE_GOSSIP_MENU();
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
            Talk(SAY_SUMMON_MAJ, player);
            events.ScheduleEvent(EVENT_RAG_SUMMON_1, 5000);
        }
    }
    private:
        uint8 _addsKilled;
        Creature* const _GetRagnaros()
        {
            return instance->GetCreature(BOSS_RAGNAROS);
        }
};

class spell_executus_shield_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_executus_shield_SpellScript);

    void FilterTargets(std::list<WorldObject*>& targets)
    {
        targets.remove_if([&](WorldObject* target) -> bool
        {
            if(Unit* tar = target->ToUnit())
                return !GetCaster()->IsFriendlyTo(tar);
            return true;
        });
    }

    void Register() override
    {
        OnObjectAreaTargetSelect += SpellObjectAreaTargetSelectFn(spell_executus_shield_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_SRC_AREA_ENTRY);
    }
};

void AddSC_boss_majordomo()
{
    new CreatureAILoader<boss_majordomoAI>("boss_majordomo");
    new SpellScriptLoaderEx<spell_executus_shield_SpellScript>("spell_executus_shield");
}
