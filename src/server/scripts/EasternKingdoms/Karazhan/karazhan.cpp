/*
 * Rewritten by Afgann
 */

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedGossip.h"
#include "karazhan.h"
#include "ScriptedEscortAI.h"
#include "Player.h"

enum Spells
{
    // Berthold
    SPELL_TELEPORT              = 39567,

    // Image of Medivh
    SPELL_FIRE_BALL             = 30967,
    SPELL_UBER_FIREBALL         = 30971,
    SPELL_CONFLAGRATION_BLAST   = 30977,
    SPELL_MANA_SHIELD           = 31635
};

enum Creatures
{
    NPC_ARCANAGOS               = 17652,
    NPC_SPOTLIGHT               = 19525
};

/*###
# npc_image_of_medivh
####*/

#define SAY_DIALOG_MEDIVH_1         "You've got my attention, dragon. You'll find I'm not as easily scared as the villagers below."
#define SAY_DIALOG_ARCANAGOS_2      "Your dabbling in the arcane has gone too far, Medivh. You've attracted the attention of powers beyond your understanding. You must leave Karazhan at once!"
#define SAY_DIALOG_MEDIVH_3         "You dare challenge me at my own dwelling? Your arrogance is astounding, even for a dragon!"
#define SAY_DIALOG_ARCANAGOS_4      "A dark power seeks to use you, Medivh! If you stay, dire days will follow. You must hurry, we don't have much time!"
#define SAY_DIALOG_MEDIVH_5         "I do not know what you speak of, dragon... but I will not be bullied by this display of insolence. I'll leave Karazhan when it suits me!"
#define SAY_DIALOG_ARCANAGOS_6      "You leave me no alternative. I will stop you by force if you won't listen to reason!"
#define EMOTE_DIALOG_MEDIVH_7       "begins to cast a spell of great power, weaving his own essence into the magic."
#define SAY_DIALOG_ARCANAGOS_8      "What have you done, wizard? This cannot be! I'm burning from... within!"
#define SAY_DIALOG_MEDIVH_9         "He should not have angered me. I must go... recover my strength now..."


static float MedivPos[4] = { -11161.49f, -1902.24f, 91.48f, 1.94f };
static float ArcanagosPos[4] = { -11169.75f, -1881.48f, 95.39f, 4.83f };

// @todo rewrite this mess
class npc_image_of_medivh : public CreatureScript
{
public:
    npc_image_of_medivh() : CreatureScript("npc_image_of_medivh") { }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_image_of_medivhAI>(creature);
    }

    struct npc_image_of_medivhAI : public ScriptedAI
    {
        npc_image_of_medivhAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
            Step = 0;
            FireArcanagosTimer = 0;
            FireMedivhTimer = 0;
            instance = creature->GetInstanceScript();
        }

        void Initialize()
        {
            ArcanagosGUID = 0;
            EventStarted = false;
            YellTimer = 0;
        }

        InstanceScript* instance;

        uint64 ArcanagosGUID;

        uint32 YellTimer;
        uint32 Step;
        uint32 FireMedivhTimer;
        uint32 FireArcanagosTimer;

        bool EventStarted;

        void Reset() override
        {
            Initialize();

            if (!instance->GetData64(DATA_IMAGE_OF_MEDIVH))
            {
                instance->SetData64(DATA_IMAGE_OF_MEDIVH, me->GetGUID());
                (*me).GetMotionMaster()->MovePoint(1, MedivPos[0], MedivPos[1], MedivPos[2]);
                Step = 0;
            }
            else
                me->DespawnOrUnsummon();
        }
        void EnterCombat(Unit* /*who*/) override { }

        void MovementInform(uint32 type, uint32 id) override
        {
            if (type != POINT_MOTION_TYPE)
                return;
            if (id == 1)
            {
                StartEvent();
                me->SetOrientation(MedivPos[3]);
                me->SetOrientation(MedivPos[3]);
            }
        }

        void StartEvent()
        {
            Step = 1;
            EventStarted = true;
            Creature* Arcanagos = me->SummonCreature(NPC_ARCANAGOS, ArcanagosPos[0], ArcanagosPos[1], ArcanagosPos[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 20000);
            if (!Arcanagos)
                return;
            ArcanagosGUID = Arcanagos->GetGUID();
            Arcanagos->GetMotionMaster()->MovePoint(0, ArcanagosPos[0], ArcanagosPos[1], ArcanagosPos[2]);
            Arcanagos->SetOrientation(ArcanagosPos[3]);
            me->SetOrientation(MedivPos[3]);
            YellTimer = 10000;
        }

        uint32 NextStep(uint32 step)
        {
            switch (step)
            {
            case 0: return 9999999;
            case 1:
                me->MonsterYell(SAY_DIALOG_MEDIVH_1, LANG_UNIVERSAL, nullptr);
                return 10000;
            case 2:
                if (Creature* arca = ObjectAccessor::GetCreature(*me, ArcanagosGUID))
                    arca->MonsterYell(SAY_DIALOG_ARCANAGOS_2, LANG_UNIVERSAL, nullptr);
                return 20000;
            case 3:
                me->MonsterYell(SAY_DIALOG_MEDIVH_3, LANG_UNIVERSAL, nullptr);
                return 10000;
            case 4:
                if (Creature* arca = ObjectAccessor::GetCreature(*me, ArcanagosGUID))
                    arca->MonsterYell(SAY_DIALOG_ARCANAGOS_4, LANG_UNIVERSAL, nullptr);
                return 20000;
            case 5:
                me->MonsterYell(SAY_DIALOG_MEDIVH_5, LANG_UNIVERSAL, nullptr);
                return 20000;
            case 6:
                if (Creature* arca = ObjectAccessor::GetCreature(*me, ArcanagosGUID))
                    arca->MonsterYell(SAY_DIALOG_ARCANAGOS_6, LANG_UNIVERSAL, nullptr);
                return 10000;
            case 7:
                FireArcanagosTimer = 500;
                return 5000;
            case 8:
                FireMedivhTimer = 500;
                DoCastSelf(SPELL_MANA_SHIELD);
                return 10000;
            case 9:
                me->MonsterTextEmote(EMOTE_DIALOG_MEDIVH_7, nullptr);
                return 10000;
            case 10:
                if (Creature* arca = ObjectAccessor::GetCreature(*me, ArcanagosGUID))
                    DoCast(arca, SPELL_CONFLAGRATION_BLAST, false);
                return 1000;
            case 11:
                if (Creature* arca = ObjectAccessor::GetCreature(*me, ArcanagosGUID))
                    arca->MonsterYell(SAY_DIALOG_ARCANAGOS_8, LANG_UNIVERSAL, nullptr);
                return 5000;
            case 12:
                if (Creature* arca = ObjectAccessor::GetCreature(*me, ArcanagosGUID))
                {
                    arca->GetMotionMaster()->MovePoint(0, -11010.82f, -1761.18f, 156.47f);
                    arca->setActive(true);
                    arca->InterruptNonMeleeSpells(true);
                    arca->SetSpeedRate(MOVE_FLIGHT, 2.0f);
                }
                return 10000;
            case 13:
                me->MonsterYell(SAY_DIALOG_MEDIVH_9, LANG_UNIVERSAL, nullptr);
                return 10000;
            case 14:
            {
                me->SetVisible(false);
                me->ClearInCombat();

                InstanceMap::PlayerList const &PlayerList = me->GetMap()->GetPlayers();
                for (const auto& i : PlayerList)
                {
                    if (i.GetSource()->IsAlive())
                    {
                        if (i.GetSource()->GetQuestStatus(9645) == QUEST_STATUS_INCOMPLETE)
                            i.GetSource()->CompleteQuest(9645);
                    }
                }
                return 50000;
            }
            case 15:
                if (Creature* arca = ObjectAccessor::GetCreature(*me, ArcanagosGUID))
                    arca->DealDamage(arca, arca, arca->GetHealth(), nullptr, SPELL_DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr);
                return 5000;
            default:
                return 9999999;
            }
        }

        void UpdateAI(uint32 diff) override
        {
            if (YellTimer <= diff)
            {
                if (EventStarted)
                    YellTimer = NextStep(Step++);
            }
            else YellTimer -= diff;

            if (Step >= 7 && Step <= 12)
            {
                Unit* arca = ObjectAccessor::GetUnit(*me, ArcanagosGUID);

                if (FireArcanagosTimer <= diff)
                {
                    if (arca)
                        arca->CastSpell(me, SPELL_FIRE_BALL, false);
                    FireArcanagosTimer = 6000;
                }
                else FireArcanagosTimer -= diff;

                if (FireMedivhTimer <= diff)
                {
                    if (arca)
                        DoCast(arca, SPELL_FIRE_BALL);
                    FireMedivhTimer = 5000;
                }
                else FireMedivhTimer -= diff;
            }
        }
    };
};

struct npc_servant_quartersAI : public ScriptedAI
{
    npc_servant_quartersAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _events.Reset();
    }

    virtual void DoEvent(uint32 eventId) = 0;

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->IsCasting())
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            DoEvent(eventId);
            if (me->IsCasting())
                return;
        }

        DoMeleeAttackIfReady();
    }

    void JustDied(Unit* /*killer*/) override
    {
        _events.Reset();
        if (InstanceScript* instance = me->GetInstanceScript())
            instance->SetData(DATA_SERVANT_QUARTERS_TRASH, 1);
    }

    protected:
        EventMap _events;
};

enum ColdmistStalker
{
    SPELL_SNEAK             = 22766,
    SPELL_CHILLING_POISON   = 29291
};

struct npc_coldmist_stalkerAI : public npc_servant_quartersAI
{
    npc_coldmist_stalkerAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_SNEAK, true);
        DoCastSelf(SPELL_CHILLING_POISON, true);
    }

    void DoEvent(uint32 /*eventId*/) override { }
};

enum ColdmistWidow
{
    SPELL_FROST_MIST            = 29292,
    SPELL_POISON_BOLT_VOLLEY    = 29293,

    EVENT_FROST_MIST            = 1,
    EVENT_POISON_BOLT_VOLLEY
};

struct npc_coldmist_widowAI : public npc_servant_quartersAI
{
    npc_coldmist_widowAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_FROST_MIST, 2s, 6s);
        _events.ScheduleEvent(EVENT_POISON_BOLT_VOLLEY, 4s, 8s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_FROST_MIST:
                DoCastSelf(SPELL_FROST_MIST);
                _events.Repeat(15s, 20s);
                break;
            case EVENT_POISON_BOLT_VOLLEY:
                DoCastSelf(SPELL_POISON_BOLT_VOLLEY);
                _events.Repeat(15s, 20s);
                break;
            default:
                break;
        }
    }
};

enum Shadowbat
{
    SPELL_DARK_SHRIEK   = 29298,

    EVENT_DARK_SHRIEK   = 1
};

struct npc_shadowbatAI : public npc_servant_quartersAI
{
    npc_shadowbatAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_DARK_SHRIEK, 3s, 9s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_DARK_SHRIEK:
                DoCastSelf(SPELL_DARK_SHRIEK);
                _events.Repeat(14s, 21s);
                break;
            default:
                break;
        }
    }
};

enum GreaterShadowbat
{
    SPELL_SONIC_BLAST   = 29300,
    SPELL_WING_BEAT     = 29303,

    EVENT_SONIC_BLAST   = 1,
    EVENT_WING_BEAT
};

struct npc_greater_shadowbatAI : public npc_servant_quartersAI
{
    npc_greater_shadowbatAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_SONIC_BLAST, 4s, 11s);
        _events.ScheduleEvent(EVENT_WING_BEAT, 5s, 10s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_SONIC_BLAST:
                DoCastVictim(SPELL_SONIC_BLAST);
                _events.Repeat(14s, 21s);
                break;
            case EVENT_WING_BEAT:
                DoCastSelf(SPELL_WING_BEAT);
                _events.Repeat(14s, 21s);
                break;
            default:
                break;
        }
    }
};

enum VampiricShadowbat
{
    SPELL_DRAINING_TOUCH = 32429
};

struct npc_vampiric_shadowbatAI : public npc_servant_quartersAI
{
    npc_vampiric_shadowbatAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_DRAINING_TOUCH);
    }

    void DoEvent(uint32 /*eventId*/) override { }
};

enum Shadowbeast
{
    SPELL_HOWL_OF_THE_BROKEN_HILLS  = 29304,

    EVENT_HOWL_OF_THE_BROKEN_HILLS  = 1
};

struct npc_shadowbeastAI : public npc_servant_quartersAI
{
    npc_shadowbeastAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_HOWL_OF_THE_BROKEN_HILLS, 5s, 10s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_HOWL_OF_THE_BROKEN_HILLS:
                DoCastSelf(SPELL_HOWL_OF_THE_BROKEN_HILLS);
                _events.Repeat(20s, 30s);
                break;
            default:
                break;
        }
    }
};

enum Dreadbeast
{
    SPELL_CLEAVE    = 29561,

    EVENT_CLEAVE    = 1
};

struct npc_dreadbeastAI : public npc_servant_quartersAI
{
    npc_dreadbeastAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_CLEAVE, 3s, 8s);
    }

    void DoEvent(uint32 eventId) override
    {
        switch (eventId)
        {
            case EVENT_CLEAVE:
                DoCastVictim(SPELL_CLEAVE);
                _events.Repeat(6s, 9s);
                break;
            default:
                break;
        }
    }
};

enum PhaseHound
{
    SPELL_PHASE_SHIFT = 29315
};

struct npc_phase_houndAI : public npc_servant_quartersAI
{
    npc_phase_houndAI(Creature* creature) : npc_servant_quartersAI(creature) { }

    void Reset() override
    {
        DoCastSelf(SPELL_PHASE_SHIFT, true);
    }

    void DoEvent(uint32 /*eventId*/) override { }
};

void AddSC_karazhan()
{
    new npc_image_of_medivh();

    new CreatureAILoader<npc_coldmist_stalkerAI>("npc_coldmist_stalker");
    new CreatureAILoader<npc_coldmist_widowAI>("npc_coldmist_widow");
    new CreatureAILoader<npc_shadowbatAI>("npc_shadowbat");
    new CreatureAILoader<npc_greater_shadowbatAI>("npc_greater_shadowbat");
    new CreatureAILoader<npc_vampiric_shadowbatAI>("npc_vampiric_shadowbat");
    new CreatureAILoader<npc_shadowbeastAI>("npc_shadowbeast");
    new CreatureAILoader<npc_dreadbeastAI>("npc_dreadbeast");
    new CreatureAILoader<npc_phase_houndAI>("npc_phase_hound");
}
