#include "ObjectMgr.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "Spell.h"
#include "SpellAuraEffects.h"
#include "PassiveAI.h"
#include "GridNotifiers.h"
#include "Player.h"
#include "Group.h"
#include "Language.h"
#include "ScriptedEscortAI.h"
#include "CustomEventMgr.h"

enum Spells
{

    SPELL_CAPTURE_SOUL                 = 21054,
    SPELL_CLEAVE                       = 20677,
    SPELL_SHADOW_BOLT_VOLLEY           = 21341,
    SPELL_THUNDER_CLAP                 = 23931,
    SPELL_TWISTED_REFLECTION           = 21063,
    SPELL_VOID_BOLT                    = 21066,
    SPELL_SHADOW_CRASH                 = 60848,
    SPELL_BERSERK                      = 21340
};

enum Events
{
    EVENT_SPELL_CLEAVE                = 1,
    EVENT_SPELL_SHADOW_CRASH          = 2,
    EVENT_SPELL_SHADOW_BOLT_VOLLEY    = 3,
    EVENT_SPELL_THUNDER_CLAP          = 4,
    EVENT_SPELL_TWISTED_REFLECTION    = 5,
    EVENT_SPELL_VOID_BOLT             = 6,
    EVENT_SPELL_BERSERK               = 7
};



class boss_highlord_kruul : public CreatureScript
{
public:
    boss_highlord_kruul() : CreatureScript("boss_highlord_kruul") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_highlord_kruulAI (pCreature);
    }

    struct boss_highlord_kruulAI : public npc_escortAI
    {
        boss_highlord_kruulAI(Creature *c) : npc_escortAI(c) 
        {
            // Waypoints
            if (uint32 pathId = GetPathId())
            {
                LoadWaypointsFromWaypointData(pathId);
                Start(true);
            }
        }

        EventMap events;
        
        void Reset()
        {
            events.Reset();
            events.ScheduleEvent(EVENT_SPELL_CLEAVE, 3000);
            events.ScheduleEvent(EVENT_SPELL_SHADOW_CRASH, 15000);
            events.ScheduleEvent(EVENT_SPELL_SHADOW_BOLT_VOLLEY, 21000);
            events.ScheduleEvent(EVENT_SPELL_THUNDER_CLAP, 5000);
            events.ScheduleEvent(EVENT_SPELL_TWISTED_REFLECTION, 30000);
            events.ScheduleEvent(EVENT_SPELL_VOID_BOLT, 30000);
            events.ScheduleEvent(EVENT_SPELL_BERSERK, 600000);

            playerRaidGUID = 0;
        }

        void MoveInLineOfSight(Unit* who)
        {
            if (who && who->GetTypeId() != TYPEID_PLAYER)
                return;

            ScriptedAI::MoveInLineOfSight(who);
        }
 
        uint32 GetPathId()
        {
            switch (me->GetZoneId())
            {
                case 3:
                    return 999994;
                case 11:
                    return 999993;
                case 38:
                    return 999992;
                case 44:
                    return 999999;
                case 400:
                    return 999997;
                case 405:
                    return 999995;
                case 406:
                    return 999998;
                case 618:
                    return 999996;
                default:
                    return 0;
            }
        }

        bool CanCapture(Player* player)
        {
            if (Player* Raider = player->ToPlayer())
                if (Group* group = Raider->GetGroup())
                    for (GroupReference* itr = group->GetFirstMember(); itr != NULL; itr = itr->next())
                        if (Player* member = itr->GetSource())
                            if (member->GetGUID() == playerRaidGUID)
                                return true;
            return false;
        }

        void KilledUnit(Unit* who)
        {
            if (who->GetTypeId() != TYPEID_PLAYER)
                return;

            if (who->GetTypeId() == TYPEID_PLAYER)
            {
                if (CanCapture(who->ToPlayer()))
                {
                    int32 heal = 1000000;
                    me->CastCustomSpell(me, SPELL_CAPTURE_SOUL, &heal, NULL, NULL, false);
                }

                uint8 roll = urand(0, 1);

                if (roll == 0)
                    me->MonsterYell("Your own strength feeds me, $n!", LANG_UNIVERSAL, who);
                else
                    me->MonsterYell("Your fate is sealed, Azeroth! I will find the Aspect Shards, and then you will not stand against our might!", LANG_UNIVERSAL, 0); 
            }
        }

        void JustDied(Unit* /*Killer*/) { me->MonsterYell("Ha! This place is not yet worthy of my infliction.", LANG_UNIVERSAL, 0); }

        void EnterCombat(Unit* who)
        {
            if (who && who->GetTypeId() == TYPEID_PLAYER)
                playerRaidGUID = who->GetGUID();
        }

        bool RollZone()
        {
            switch (sCustomEventMgr->GetKruulSpawnLoc())
            {
                case 0:
                    if (me->GetZoneId() == 406 || me->GetZoneId() == 44)
                        return true;
                    break;
                case 1:
                    if (me->GetZoneId() == 400 || me->GetZoneId() == 3)
                        return true;
                    break;
                case 2:
                    if (me->GetZoneId() == 618 || me->GetZoneId() == 11)
                        return true;
                    break;
                case 3:
                    if (me->GetZoneId() == 405 || me->GetZoneId() == 38)
                        return true;
                    break;
                case 4:
                    if (me->GetZoneId() == 406 || me->GetZoneId() == 38)
                        return true;
                    break;
                case 5:
                    if (me->GetZoneId() == 400 || me->GetZoneId() == 11)
                        return true;
                    break;
                case 6:
                    if (me->GetZoneId() == 618 || me->GetZoneId() == 44)
                        return true;
                    break;
                case 7:
                    if (me->GetZoneId() == 405 || me->GetZoneId() == 3)
                        return true;
                    break;
                case 8:
                    if (me->GetZoneId() == 14 || me->GetZoneId() == 1519)
                        return true;
            }

            return false;
        }

 
        void RunEvent()
        {
            if (RollZone() && !sCustomEventMgr->KruulListCheck(me->GetGUID()))
            {
                if (!me->GetMap()->IsGridLoaded(me->GetPositionX(), me->GetPositionY()))
                    me->GetMap()->LoadGrid(me->GetPositionX(), me->GetPositionY());

                me->SetPhaseMask(1, true);
                sCustomEventMgr->KruulListInsert(me->GetGUID());
            }
        }

        Unit* FindCrashTarget()
        {
            Unit* target = NULL;
            ThreatContainer::StorageType const &threatlist = me->getThreatManager().getThreatList();
            for (ThreatContainer::StorageType::const_iterator i = threatlist.begin(); i != threatlist.end(); ++i)
            {
                Unit* unit = ObjectAccessor::GetUnit(*me, (*i)->getUnitGuid());
                if (unit && unit->IsAlive() && unit->GetDistance(me) > 15.0f)
                    if (!target)
                        target = unit;
            }

            return target;
        }

        void UpdateEscortAI(uint32 diff)
        {
            if (!UpdateVictim())
            {
                if (sWorld->getBoolConfig(CONFIG_KRUUL_EVENT))
                {
                    time_t now = time(nullptr);
                    tm* aTm = localtime(&now);
             
                    if (aTm->tm_wday == sCustomEventMgr->GetKruulDay()
                        && aTm->tm_hour == sCustomEventMgr->GetKruulHour()
                        && aTm->tm_min >= sCustomEventMgr->GetKruulMinute())                  
                        RunEvent();
                }
                return;
            }

            events.Update(diff);

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;

            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_SPELL_CLEAVE:
                    {
                        me->CastSpell(me->GetVictim(), SPELL_CLEAVE, false);
                        events.ScheduleEvent(EVENT_SPELL_CLEAVE, 5000);
                        break;
                    }
                    case EVENT_SPELL_SHADOW_CRASH:
                    {
                        if (Unit* target = FindCrashTarget())
                        {
                            me->SetUInt64Value(UNIT_FIELD_TARGET, target->GetGUID());
                            me->CastSpell(target, SPELL_SHADOW_CRASH, false);
                        }
                        events.ScheduleEvent(EVENT_SPELL_SHADOW_CRASH, 15000);
                        break;
                    }
                    case EVENT_SPELL_SHADOW_BOLT_VOLLEY:
                    {
                        me->CastSpell(me, SPELL_SHADOW_BOLT_VOLLEY, false);
                        events.ScheduleEvent(EVENT_SPELL_SHADOW_BOLT_VOLLEY, 21000);
                        break;
                    }
                    case EVENT_SPELL_THUNDER_CLAP:
                    {
                        int32 dmg = urand(7000, 7500);
                        me->CastCustomSpell(me, SPELL_THUNDER_CLAP, &dmg, NULL, NULL, false);
                        events.ScheduleEvent(EVENT_SPELL_THUNDER_CLAP, 10000);
                        break;
                    }
                    case EVENT_SPELL_TWISTED_REFLECTION:
                    {
                        me->CastSpell(me->GetVictim(), SPELL_TWISTED_REFLECTION, false);
                        events.ScheduleEvent(EVENT_SPELL_TWISTED_REFLECTION, 30000);
                        break;
                    }
                    case EVENT_SPELL_VOID_BOLT:
                    {
                        int32 dmg = urand(14800, 15200);
                        me->CastCustomSpell(me->GetVictim(), SPELL_VOID_BOLT, &dmg, NULL, NULL, false);
                        events.ScheduleEvent(EVENT_SPELL_VOID_BOLT, 10000);
                        break;
                    } 
                    case EVENT_SPELL_BERSERK:
                    {
                        me->CastSpell(me, SPELL_BERSERK, false);
                        events.PopEvent();
                        break;
                    }
                }
            }

            DoMeleeAttackIfReady();
        }

        void WaypointReached(uint32 id) {}

        private:
            uint64 playerRaidGUID;
    };
};

void AddSC_boss_highlord_kruul()
{
    new boss_highlord_kruul();
}