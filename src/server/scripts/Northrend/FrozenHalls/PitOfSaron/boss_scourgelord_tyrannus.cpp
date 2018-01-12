#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "pit_of_saron.h"
#include "Vehicle.h"

enum Texts
{
    SAY_AGGRO                       = 53,
    SAY_SLAY_1,
    SAY_SLAY_2,
    SAY_DEATH,
    SAY_MARK,
    SAY_SMASH,
    EMOTE_RIMEFANG_ICEBOLT,
    EMOTE_SMASH
};

enum Spells
{
    SPELL_OVERLORDS_BRAND           = 69172,
    SPELL_OVERLORDS_BRAND_HEAL      = 69190,
    SPELL_OVERLORDS_BRAND_DAMAGE    = 69189,
    SPELL_FORCEFUL_SMASH            = 69155,
    SPELL_UNHOLY_POWER              = 69167,
    RIMEFANG_SPELL_ICY_BLAST        = 69232,
    SPELL_MARK_OF_RIMEFANG          = 69275,
    RIMEFANG_SPELL_HOARFROST        = 69246
};

enum Events
{
    EVENT_FORCEFUL_SMASH            = 1,
    EVENT_UNHOLY_POWER,
    EVENT_OVERLORDS_BRAND,
    EVENT_RIMEFANG_ICY_BLAST,
    EVENT_MARK_OF_RIMEFANG,
    EVENT_KILL_TALK
};

struct boss_tyrannusAI : public BossAI
{
    boss_tyrannusAI(Creature* creature) : BossAI(creature, DATA_TYRANNUS)
    {
        me->SetReactState(REACT_PASSIVE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NON_ATTACKABLE);
        if (Creature* rimefang = instance->GetCreature(DATA_RIMEFANG_GUID))
            rimefang->SetCanFly(true);
    }

    void Reset() override
    {
        _Reset();
        if (me->HasReactState(REACT_AGGRESSIVE))
        {
            if (Creature* martinOrGorkun = instance->GetCreature(DATA_MARTIN_OR_GORKUN_GUID))
            {
                if (martinOrGorkun->IsAIEnabled)
                    martinOrGorkun->AI()->DoAction(1);
                martinOrGorkun->DespawnOrUnsummon();
            }
            if (Creature* rimefang = instance->GetCreature(DATA_RIMEFANG_GUID))
            {
                rimefang->GetMotionMaster()->Clear();
                rimefang->GetMotionMaster()->MoveIdle();
                rimefang->RemoveAllAuras();
                rimefang->UpdatePosition(1017.3f, 168.974f, 642.926f, 5.2709f, true);
                rimefang->StopMovingOnCurrentPos();
                if (Vehicle* vehicle = rimefang->GetVehicleKit())
                    vehicle->InstallAllAccessories(false);
            }
        }
    }

    void DoAction(int32 actionId) override
    {
        if (actionId != 1)
            return;

        Position exitPos = { 1023.46f, 159.12f, 628.2f, 5.23f };
        me->RemoveAllAuras();
        if (Creature* rimefang = instance->GetCreature(DATA_RIMEFANG_GUID))
        {
            rimefang->RemoveAura(46598);
            rimefang->GetMotionMaster()->Clear();
            rimefang->GetMotionMaster()->MovePath(PATH_BEGIN_VALUE + 18, true);
        }
        me->SetHomePosition(exitPos);
        me->GetMotionMaster()->MoveJump(exitPos, 10.0f, 2.0f);

        // start real fight
        _EnterCombat();
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PC | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NON_ATTACKABLE);
        Talk(SAY_AGGRO);
        events.RescheduleEvent(EVENT_FORCEFUL_SMASH, 14s, 16s);
        events.RescheduleEvent(EVENT_OVERLORDS_BRAND, 4s, 6s);
        events.RescheduleEvent(EVENT_RIMEFANG_ICY_BLAST, 5s);
        events.RescheduleEvent(EVENT_MARK_OF_RIMEFANG, 25s);
    }

    void ExecuteEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_FORCEFUL_SMASH:
                if (me->IsWithinMeleeRange(me->GetVictim()))
                {
                    DoCastVictim(SPELL_FORCEFUL_SMASH);
                    events.RescheduleEvent(EVENT_UNHOLY_POWER, 1s);
                    break;
                }
                events.Repeat(3s);
                break;
            case EVENT_UNHOLY_POWER:
                Talk(SAY_SMASH);
                Talk(EMOTE_SMASH);
                DoCastSelf(SPELL_UNHOLY_POWER);
                events.RescheduleEvent(EVENT_FORCEFUL_SMASH, 40s, 48s);
                break;
            case EVENT_OVERLORDS_BRAND:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 95.0f, true))
                    DoCast(target, SPELL_OVERLORDS_BRAND);
                events.Repeat(11s, 12s);
                break;
            case EVENT_RIMEFANG_ICY_BLAST:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 190.0f, true))
                    if (Creature* rimefang = instance->GetCreature(DATA_RIMEFANG_GUID))
                        rimefang->CastSpell(target, RIMEFANG_SPELL_ICY_BLAST, false);
                events.Repeat(5s);
                break;
            case EVENT_MARK_OF_RIMEFANG:
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 190.0f, true))
                    if (Creature* rimefang = instance->GetCreature(DATA_RIMEFANG_GUID))
                    {
                        Talk(SAY_MARK);
                        if (rimefang->IsAIEnabled)
                            rimefang->AI()->Talk(EMOTE_RIMEFANG_ICEBOLT, target);
                        rimefang->CastSpell(target, RIMEFANG_SPELL_HOARFROST, false);
                    }
                events.Repeat(25s);
                events.RescheduleEvent(EVENT_RIMEFANG_ICY_BLAST, 10s);
                break;
            default:
                break;
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        _JustDied();
        Talk(SAY_DEATH);
        if (me->IsSummon())
            me->ToTempSummon()->SetTempSummonType(TEMPSUMMON_MANUAL_DESPAWN);
    }

    void KilledUnit(Unit* /*who*/) override
    {
        if (events.GetNextEventTime(EVENT_KILL_TALK) == 0)
        {
            Talk(RAND(SAY_SLAY_1, SAY_SLAY_2));
            events.ScheduleEvent(EVENT_KILL_TALK, 6s);
        }
    }

    bool CanAIAttack(const Unit* who) const
    {
        switch (who->GetEntry())
        {
            case NPC_MARTIN_VICTUS_2:
            case NPC_GORKUN_IRONSKULL_2:
            case NPC_FREED_SLAVE_1_ALLIANCE:
            case NPC_FREED_SLAVE_2_ALLIANCE:
            case NPC_FREED_SLAVE_3_ALLIANCE:
            case NPC_FREED_SLAVE_1_HORDE:
            case NPC_FREED_SLAVE_2_HORDE:
            case NPC_FREED_SLAVE_3_HORDE:
                return false;
            default:
                return true;
        }
    }

    void EnterEvadeMode() override
    {
        Reset();
        me->DespawnOrUnsummon();
    }
};

void AddSC_boss_tyrannus()
{
    new CreatureAILoader<boss_tyrannusAI>("boss_tyrannus");
}