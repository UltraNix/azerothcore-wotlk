/*
REWRITTEN FROM SCRATCH BY PUSSYWIZARD, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "Vehicle.h"
#include "trial_of_the_champion.h"
#include "PassiveAI.h"
#include "Player.h"
#include "SpellInfo.h"
#include "CombatAI.h"

enum MountSpells
{
    SPELL_PLAYER_VEHICLE_DEFEND                 = 66482,
    SPELL_MINIONS_DEFEND                        = 64100,
    SPELL_BOSS_DEFEND                           = 62719,
    SPELL_BOSS_DEFEND_PERIODIC                  = 64553,
    SPELL_SHIELD_LEVEL_1_VISUAL                 = 63130,
    SPELL_SHIELD_LEVEL_2_VISUAL                 = 63131,
    SPELL_SHIELD_LEVEL_3_VISUAL                 = 63132,

    SPELL_PLAYER_VEHICLE_SHIELD_BREAKER         = 62575,
    SPELL_PLAYER_SHIELD_BREAKER_DAMAGE          = 62626,
    SPELL_NPC_SHIELD_BREAKER                    = 68504,

    SPELL_PLAYER_VEHICLE_CHARGE                 = 68284,
    SPELL_CHARGE_DAMAGE_20000                   = 68498,
    SPELL_MINIONS_CHARGE                        = 63010,
    SPELL_BOSS_CHARGE                           = 68301, // triggers SPELL_MINIONS_CHARGE (should be with custom damage?)

    SPELL_PLAYER_VEHICLE_THRUST                 = 68505,

    SPELL_TRAMPLE_AURA                          = 67865,
    SPELL_TRAMPLE_TRIGGERED_DUMMY               = 67866,
    SPELL_TRAMPLE_STUN                          = 67867
};

enum ChampionSpells
{
    // Mage (Ambrose Boltspark, Eressea Dawnsinger)
    SPELL_FIREBALL                              = 66042,
    SPELL_BLAST_WAVE                            = 66044,
    SPELL_HASTE                                 = 66045,
    SPELL_POLYMORPH                             = 66043,

    // Shaman (Colosos, Runok Wildmane)
    SPELL_CHAIN_LIGHTNING                       = 67529,
    SPELL_EARTH_SHIELD                          = 67530,
    SPELL_HEALING_WAVE                          = 67528,
    SPELL_HEX_OF_MENDING                        = 67534,

    // Hunter (Jaelyne Evensong, Zul'tore)
    SPELL_DISENGAGE                             = 68339,
    SPELL_LIGHTNING_ARROWS                      = 66083,
    SPELL_MULTI_SHOT                            = 66081,
    SPELL_SHOOT                                 = 65868,

    // Rogue (Lana Stouthammer Evensong, Deathstalker Visceri)
    SPELL_EVISCERATE                            = 67709,
    SPELL_FAN_OF_KNIVES                         = 67706,
    SPELL_POISON_BOTTLE                         = 67701,

    // Warrior (Marshal Jacob Alerius, Mokra the Skullcrusher)
    SPELL_MORTAL_STRIKE                         = 68783,
    SPELL_BLADESTORM                            = 63784,
    SPELL_INTERCEPT                             = 67540,
    SPELL_ROLLING_THROW                         = 67546  // not implemented yet!
};

enum MountEvents
{
    EVENT_MOUNT_CHARGE                          = 1,
    EVENT_SHIELD_BREAKER,
    EVENT_THRUST,
    EVENT_FIND_NEW_MOUNT,
};

enum ChampionEvents
{
    EVENT_MAGE_SPELL_FIREBALL                   = 101,
    EVENT_MAGE_SPELL_BLAST_WAVE,
    EVENT_MAGE_SPELL_HASTE,
    EVENT_MAGE_SPELL_POLYMORPH,

    EVENT_SHAMAN_SPELL_CHAIN_LIGHTNING,
    EVENT_SHAMAN_SPELL_EARTH_SHIELD,
    EVENT_SHAMAN_SPELL_HEALING_WAVE,
    EVENT_SHAMAN_SPELL_HEX_OF_MENDING,

    EVENT_HUNTER_SPELL_DISENGAGE,
    EVENT_HUNTER_SPELL_LIGHTNING_ARROWS,
    EVENT_HUNTER_SPELL_MULTI_SHOT,
    EVENT_HUNTER_SPELL_SHOOT,

    EVENT_ROGUE_SPELL_EVISCERATE,
    EVENT_ROGUE_SPELL_FAN_OF_KNIVES,
    EVENT_ROGUE_SPELL_POISON_BOTTLE,        

    EVENT_WARRIOR_SPELL_MORTAL_STRIKE,
    EVENT_WARRIOR_SPELL_BLADESTORM,
    EVENT_WARRIOR_SPELL_INTERCEPT,
    EVENT_WARRIOR_SPELL_ROLLING_THROW,
};

struct npc_toc5_player_vehicleAI : public NullCreatureAI
{
    npc_toc5_player_vehicleAI(Creature* creature) : NullCreatureAI(creature)
    {
        _conditions = sConditionMgr->GetConditionsForNotGroupedEntry(CONDITION_SOURCE_TYPE_CREATURE_TEMPLATE_VEHICLE, me->GetEntry());
        _conditionsTimer = 1000;
    }

    void Reset() override
    {
        _despawnTimer = 0;
        _respawn = false;
        me->SetReactState(REACT_PASSIVE);
        me->getHostileRefManager().setOnlineOfflineState(false);
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (damage > me->GetHealth())
        {
            damage = me->GetHealth() - 1;
            if (me->GetVehicleKit())
                me->GetVehicleKit()->RemoveAllPassengers();
            me->SetVisible(false);
            _respawn = true;
            _despawnTimer = 5000;
            Position pos(me->GetHomePosition());
            me->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), true, true);
        }
    }

    void OnCharmed(bool apply) override
    {
        if (me->IsDuringRemoveFromWorld())
            return;

        if (apply)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetSpeed(MOVE_RUN, 2.0f, false);
            DoCastSelf(SPELL_TRAMPLE_AURA, true);
        }
        else
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->StopMoving();
            Position pos;
            me->SetWalk(true);
            me->GetRandomNearPosition(pos, 15.0f);
            me->GetMotionMaster()->MovePoint(1, pos);
            me->RemoveAura(SPELL_TRAMPLE_AURA);
        }
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (type != POINT_MOTION_TYPE)
            return;

        if (id == 1)
        {
            me->SetWalk(false);
            _despawnTimer = 5000;
            _respawn = true;
            me->SetVisible(false);
            me->SetHealth(me->CountPctFromMaxHealth(100));
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            Position pos(me->GetHomePosition());
            me->NearTeleportTo(pos.GetPositionX(), pos.GetPositionY(), pos.GetPositionZ(), pos.GetOrientation(), true, true);
        }
    }

    // just in case, should be done in spell_gen_defend
    void PassengerBoarded(Unit* who, int8 /*seat*/, bool apply) override
    {
        if (me->IsDuringRemoveFromWorld())
            return;

        if (!apply)
        {
            me->RemoveAura(SPELL_PLAYER_VEHICLE_DEFEND);
            who->RemoveAura(SPELL_PLAYER_VEHICLE_DEFEND);
            for (uint8 i = 0; i<3; ++i)
                who->RemoveAura(SPELL_SHIELD_LEVEL_1_VISUAL + i);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (_despawnTimer <= diff)
        {
            if (_respawn)
            {
                if (me->IsInCombat())
                    me->ClearInCombat();
                _respawn = false;
                me->SetVisible(true);
            }
            _despawnTimer = 5000;
        }
        else 
            _despawnTimer -= diff;

        if (_conditionsTimer <= diff)
        {
            if (!_conditions.empty())
                if (Unit* passenger = me->GetVehicleKit()->GetPassenger(0))
                    if (!sConditionMgr->IsObjectMeetToConditions(passenger, me, _conditions))
                        passenger->ExitVehicle();
            _conditionsTimer = VEHICLE_CONDITION_CHECK_TIME;
        }
        else
            _conditionsTimer -= diff;
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}
    void AttackStart(Unit* /*who*/) override {}
    void EnterCombat(Unit* /*who*/) override {}

private:
    ConditionList _conditions;
    uint16 _conditionsTimer;
    uint16 _despawnTimer;
    bool _respawn;
};

struct npc_toc5_grand_champion_minionAI : public ScriptedAI
{
    npc_toc5_grand_champion_minionAI(Creature* creature) : ScriptedAI(creature)
    {
        instance = me->GetInstanceScript();
    }

    void Reset() override
    {
        _shieldTimer = 0;
        _events.Reset();
    }

    void EnterCombat(Unit* /*who*/) override
    {
        me->CallForHelp(15.0f);
        _events.Reset();
        _events.ScheduleEvent(EVENT_MOUNT_CHARGE, urand(2500,4000));
        _events.ScheduleEvent(EVENT_SHIELD_BREAKER, urand(5000,8000));
        _events.ScheduleEvent(EVENT_THRUST, urand(3000,5000));
        DoCastSelf(SPELL_TRAMPLE_AURA, true);
    }

    void UpdateAI(uint32 diff) override
    {
        if (_shieldTimer <= diff)
        {
            DoCastSelf(SPELL_MINIONS_DEFEND, true);
            _shieldTimer = 5000;
        }
        else
            _shieldTimer -= diff;

        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_MOUNT_CHARGE:
                {
                    std::vector<uint64> list;
                    Map::PlayerList const &players = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* player = itr->GetSource())
                        {
                            if (!me->IsInRange(player, 8.0f, 25.0f) || player->isDead())
                                continue;
                            if (Vehicle* vehicle = player->GetVehicle())
                                if (Unit* mount = vehicle->GetBase())
                                    list.push_back(mount->GetGUID());
                        }

                    std::list<Unit*> vehicleList;

                    if (!list.empty())
                        for (auto itr : list)
                            if (Unit* vehicle = ObjectAccessor::GetUnit(*me, itr))
                                vehicleList.push_back(vehicle);

                    Unit* target = nullptr;
                    if (!vehicleList.empty())
                        target = Trinity::Containers::SelectRandomContainerElement(vehicleList);

                    if (target)
                    {
                        me->getThreatManager().resetAllAggro();
                        me->AddThreat(target, 10000.0f);
                        AttackStart(target);
                        DoCast(target, SPELL_MINIONS_CHARGE);
                    }
                    _events.Repeat(urand(4500, 6000));
                }
                break;
                case EVENT_SHIELD_BREAKER:
                {
                    std::vector<uint64> list;
                    Map::PlayerList const &players = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* player = itr->GetSource())
                        {
                            if (!me->IsInRange(player, 10.0f, 30.0f))
                                continue;
                            if (Vehicle* vehicle = player->GetVehicle())
                                if (Unit* mount = vehicle->GetBase())
                                    list.push_back(mount->GetGUID());
                        }

                    if (!list.empty())
                    {
                        uint64 guid = Trinity::Containers::SelectRandomContainerElement(list);
                        if (Unit* target = ObjectAccessor::GetCreature(*me, guid))
                            DoCast(target, SPELL_NPC_SHIELD_BREAKER);
                    }
                    _events.Repeat(urand(6000, 8000));
                }
                break;
                case EVENT_THRUST:
                    if (Unit* victim = me->GetVictim())
                        if (me->GetExactDist(victim) <= 5.5f)
                            DoCast(victim, SPELL_PLAYER_VEHICLE_THRUST);
                    _events.Repeat(urand(3000, 5000));
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }
    }

    void MoveInLineOfSight(Unit* /*who*/) override {}

    void JustDied(Unit* /*killer*/) override
    {
        me->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 0);
        me->DespawnOrUnsummon(10000);
        if (instance)
            instance->SetData(DATA_MOUNT_DIED, 0);
    }

private:
    InstanceScript* instance;
    uint32 _shieldTimer;
    EventMap _events;
};

struct boss_grand_championAI : public npc_escortAI
{
    boss_grand_championAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        AddCreatureAddonAuras();
        instance = pCreature->GetInstanceScript();
        _mountPhase = true;
        SetDespawnAtEnd(false);
        me->SetReactState(REACT_PASSIVE);
        _bossOrder = 0;
        _newMountGUID = 0;
        DoCastSelf(SPELL_BOSS_DEFEND_PERIODIC, true);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);

        _events.Reset();
        _events.ScheduleEvent(EVENT_MOUNT_CHARGE, urand(2500,4000));
        _events.ScheduleEvent(EVENT_SHIELD_BREAKER, urand(5000,8000));
        _events.ScheduleEvent(EVENT_THRUST, urand(3000,5000));

        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_CHARM, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISORIENTED, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DISTRACT, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FEAR, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_ROOT, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SLEEP, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SNARE, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_FREEZE, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_KNOCKOUT, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_POLYMORPH, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_BANISH, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SHACKLE, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_TURN, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_HORROR, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_DAZE, true);
        me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SAPPED, true);
    }

    void Reset() override
    {
        if (instance && instance->GetData(DATA_INSTANCE_PROGRESS) == INSTANCE_PROGRESS_CHAMPIONS_UNMOUNTED)
        {
            DoAction(1);
            DoAction(2);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 0);
            me->SetReactState(REACT_AGGRESSIVE);
        }
    }

    void EnterCombat(Unit* /*who*/) override
    {
        if (instance && instance->GetData(DATA_INSTANCE_PROGRESS) == INSTANCE_PROGRESS_CHAMPIONS_UNMOUNTED)
        {
            me->CallForHelp(100.0f);
            DoAction(2);
            instance->SetData(579, 0);
        }
    }

    void ScheduleAbilitiesEvents()
    {
        me->m_spellImmune[IMMUNITY_MECHANIC].clear();
        _events.Reset();
        switch (me->GetEntry())
        {
            case NPC_AMBROSE: // Ambrose Boltspark
            case NPC_ERESSEA: // Eressea Dawnsinger
                _events.RescheduleEvent(EVENT_MAGE_SPELL_FIREBALL, 5000);
                _events.RescheduleEvent(EVENT_MAGE_SPELL_BLAST_WAVE, 12000);
                _events.RescheduleEvent(EVENT_MAGE_SPELL_HASTE, 22000);
                _events.RescheduleEvent(EVENT_MAGE_SPELL_POLYMORPH, 8000);
                break;
            case NPC_COLOSOS: // Colosos
            case NPC_RUNOK: // Runok Wildmane
                _events.RescheduleEvent(EVENT_SHAMAN_SPELL_CHAIN_LIGHTNING, 16000);
                _events.RescheduleEvent(EVENT_SHAMAN_SPELL_EARTH_SHIELD, urand(30000,35000));
                _events.RescheduleEvent(EVENT_SHAMAN_SPELL_HEALING_WAVE, 12000);
                _events.RescheduleEvent(EVENT_SHAMAN_SPELL_HEX_OF_MENDING, urand(20000,25000));
                break;
            case NPC_JAELYNE: // Jaelyne Evensong
            case NPC_ZULTORE: // Zul'tore
                _events.RescheduleEvent(EVENT_HUNTER_SPELL_LIGHTNING_ARROWS, 7000);
                _events.RescheduleEvent(EVENT_HUNTER_SPELL_MULTI_SHOT, 12000);
                break;
            case NPC_LANA: // Lana Stouthammer
            case NPC_VISCERI: // Deathstalker Visceri
                _events.RescheduleEvent(EVENT_ROGUE_SPELL_EVISCERATE, 8000);
                _events.RescheduleEvent(EVENT_ROGUE_SPELL_FAN_OF_KNIVES, 14000);
                _events.RescheduleEvent(EVENT_ROGUE_SPELL_POISON_BOTTLE, 19000);
                break;
            case NPC_JACOB: // Marshal Jacob Alerius
            case NPC_MOKRA: // Mokra the Skullcrusher
                _events.RescheduleEvent(EVENT_WARRIOR_SPELL_MORTAL_STRIKE, urand(8000,12000));
                _events.RescheduleEvent(EVENT_WARRIOR_SPELL_BLADESTORM, urand(15000,20000));
                _events.RescheduleEvent(EVENT_WARRIOR_SPELL_INTERCEPT, 7000);
                break;
            default:
                break;
        }
    }

    void AddCreatureAddonAuras()
    {
        CreatureAddon const *cainfo = me->GetCreatureAddon();
        if (!cainfo)
            return;

        if (!cainfo->auras.empty())
        {
            for (std::vector<uint32>::const_iterator itr = cainfo->auras.begin(); itr != cainfo->auras.end(); ++itr)
            {
                SpellInfo const *AdditionalSpellInfo = sSpellMgr->GetSpellInfo(*itr);
                if (!AdditionalSpellInfo)
                    continue;

                if (me->HasAura(AdditionalSpellInfo->Id))
                    continue;

                me->AddAura(AdditionalSpellInfo->Id, me);
            }
        }
    }

    void DoAction(int32 param) override
    {
        if (param == 1)
        {
            _mountPhase = false;
            _newMountGUID = 0;
            me->SetHealth(me->GetMaxHealth());
            me->SetRegeneratingHealth(true);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PACIFIED);
            me->SetSpeed(MOVE_RUN, 1.0f, false);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
            me->RemoveAurasDueToSpell(67867);
            me->RemoveAurasDueToSpell(67866);
            me->RemoveAurasDueToSpell(67865);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_STUNNED);
            AddCreatureAddonAuras();
            _events.Reset();
        }
        else if (param == 2)
            ScheduleAbilitiesEvents();
    }

    void SetData(uint32 type, uint32 data) override
    {
        _bossOrder = type;
        if (data > 1)
            return;

        switch (_bossOrder)
        {
            case 0:
                if (data == 0) // 1 == short version
                {
                    AddWaypoint(0,747.36f,634.07f,411.572f);
                    AddWaypoint(1,780.43f,607.15f,411.82f);
                }
                AddWaypoint(2,785.99f,599.41f,411.92f);
                AddWaypoint(3,778.44f,601.64f,411.79f);
                break;
            case 1:
                if (data == 0) // 1 == short version
                {
                    AddWaypoint(0,747.35f,634.07f,411.57f); 
                    AddWaypoint(1,768.72f,581.01f,411.92f);
                }
                AddWaypoint(2,763.55f,590.52f,411.71f);
                break;
            case 2:
                if (data == 0) // 1 == short version
                {
                    AddWaypoint(0,747.35f,634.07f,411.57f);
                    AddWaypoint(1,784.02f,645.33f,412.39f);
                }
                AddWaypoint(2,775.67f,641.91f,411.91f);
                break;
            default:
                return;
        }

        Start(false, true, 0, nullptr);
    }

    void DamageTaken(Unit*, uint32 &damage, DamageEffectType, SpellSchoolMask) override
    {
        if (_mountPhase)
        {
            if( me->GetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID) == 0 )
                damage = 0;
            else if( damage >= me->GetHealth() )
            {
                _events.Reset();
                damage = me->GetHealth()-1;
                me->SetReactState(REACT_PASSIVE);
                me->RemoveAllAuras();
                AddCreatureAddonAuras();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->Clear();
                me->StopMoving();
                me->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, 0);
                me->SetRegeneratingHealth(false);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                if (instance)
                {
                    instance->SetData(DATA_MOUNT_DIED, _bossOrder);
                    if (Creature* mount = me->FindNearestCreature(instance->GetData(DATA_TEAMID_IN_INSTANCE) == TEAM_HORDE ? VEHICLE_ARGENT_WARHORSE : VEHICLE_ARGENT_BATTLEWORG, 100.0f, true))
                    {
                        _newMountGUID = mount->GetGUID();
                        me->GetMotionMaster()->MovePoint(7, *mount);
                        _events.RescheduleEvent(EVENT_FIND_NEW_MOUNT, 1000);
                    }
                }
            }
        }
        else
        {
            if (damage >= me->GetHealth())
            {
                _events.Reset();
                damage = me->GetHealth()-1;
                me->SetReactState(REACT_PASSIVE);
                me->RemoveAllAuras();
                AddCreatureAddonAuras();
                me->DeleteThreatList();
                me->CombatStop(true);
                me->GetMotionMaster()->Clear();
                me->SetRegeneratingHealth(false);
                me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                if (instance)
                    instance->SetData(DATA_GRAND_CHAMPION_DIED, _bossOrder);
            }
        }
    }

    void EnterEvadeMode() override {}

    void WaypointReached(uint32 id) override
    {
        if (!instance)
            return;

        if ((id == 2 && (_bossOrder == 1 || _bossOrder == 2)) || (id == 3 && _bossOrder == 0))
            instance->SetData(DATA_GRAND_CHAMPION_REACHED_DEST, _bossOrder);
    }

    void MovementInform(uint32 type, uint32 id) override
    {
        if (id < 4)
            npc_escortAI::MovementInform(type, id);

        if (type == POINT_MOTION_TYPE)
        {
            if (id == 5)
                me->SetFacingTo(3 * M_PI / 2);
            else if (id == 7) // reached new mount!
            {
                if (_newMountGUID)
                    if (Creature* mount = ObjectAccessor::GetCreature(*me, _newMountGUID))
                    {
                        mount->DespawnOrUnsummon();
                        me->SetUInt32Value(UNIT_FIELD_MOUNTDISPLAYID, mount->GetDisplayId());
                        me->RemoveUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        me->SetHealth(50000);
                        me->CastSpell(me, SPELL_BOSS_DEFEND_PERIODIC, true);
                        me->SetRegeneratingHealth(true);
                        _events.Reset();
                        _events.ScheduleEvent(EVENT_MOUNT_CHARGE, urand(2500, 4000));
                        _events.ScheduleEvent(EVENT_SHIELD_BREAKER, urand(5000, 8000));
                        _events.ScheduleEvent(EVENT_THRUST, urand(3000, 5000));
                        me->SetReactState(REACT_AGGRESSIVE);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        if (Unit* target = me->SelectNearestTarget(200.0f))
                            AttackStart(target);
                        DoZoneInCombat();
                        DoCastSelf(SPELL_TRAMPLE_AURA, true);
                        me->CastSpell(me, SPELL_TRAMPLE_AURA, true);
                        if (instance)
                            instance->SetData(DATA_REACHED_NEW_MOUNT, 0);
                        _newMountGUID = 0;
                    }
            }
            else if (id == 9)
                me->DespawnOrUnsummon();
        }
    }

    void SpellHit(Unit* /*caster*/, const SpellInfo* spell) override
    {
        switch (spell->Id)
        {
            case SPELL_TRAMPLE_STUN:
            {
                char buffer[50];
                sprintf(buffer, "%s is trampled!", me->GetName().c_str());
                me->MonsterTextEmote(buffer, 0);
            }
            break;
        }
    }

    void UpdateAI(uint32 diff) override
    {
        npc_escortAI::UpdateAI(diff);

        if (!UpdateVictim() && !_newMountGUID)
            return;
            
        _events.Update(diff);

        if (me->HasUnitState(UNIT_STATE_CASTING) || ((me->GetEntry() == NPC_JACOB || me->GetEntry() == NPC_MOKRA) && me->HasAura(SPELL_BLADESTORM)))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_FIND_NEW_MOUNT:
                    if (me->HasAura(SPELL_TRAMPLE_STUN))
                    {
                        _events.Repeat(200);
                        break;
                    }

                    // hackfix, trample won't hit grand champions because of UNIT_FLAG_NON_ATTACKABLE
                    if (instance)
                    {
                        bool trample = false;
                        Map::PlayerList const &players = me->GetMap()->GetPlayers();
                        for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                            if (Player* player = itr->GetSource())
                                if (me->GetExactDist(player) <= 5.0f)
                                    if (Vehicle* vehicle = player->GetVehicle())
                                        if (Unit* mount = vehicle->GetBase())
                                            if (mount->GetTypeId() == TYPEID_UNIT && mount->ToCreature()->GetEntry() == (instance->GetData(DATA_TEAMID_IN_INSTANCE) == TEAM_HORDE ? VEHICLE_ARGENT_BATTLEWORG : VEHICLE_ARGENT_WARHORSE))
                                            {
                                                me->GetMotionMaster()->MovementExpired();
                                                me->GetMotionMaster()->MoveIdle();
                                                me->StopMoving();
                                                DoCastSelf(SPELL_TRAMPLE_STUN);
                                                trample = true;
                                                break;
                                            }

                        if (trample)
                        {
                            _events.Repeat(15100);
                            break;
                        }
                    }

                    if (Creature* mount = ObjectAccessor::GetCreature(*me, _newMountGUID))
                        if (mount->IsAlive())
                        {
                            if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
                                me->GetMotionMaster()->MovePoint(7, *mount);
                            _events.Repeat(200);
                            break;
                        }

                    if (Creature* mount = me->FindNearestCreature(instance->GetData(DATA_TEAMID_IN_INSTANCE) == TEAM_HORDE ? VEHICLE_ARGENT_WARHORSE : VEHICLE_ARGENT_BATTLEWORG, 100.0f, true))
                    {
                        me->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        _newMountGUID = mount->GetGUID();
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                        me->GetMotionMaster()->MovePoint(7, *mount);
                        _events.Repeat(200);
                        break;
                    }

                    break;
                case EVENT_MOUNT_CHARGE:
                {
                    std::vector<uint64> list;
                    Map::PlayerList const &players = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* player = itr->GetSource())
                        {
                            if (!me->IsInRange(player, 8.0f, 25.0f) || player->isDead())
                                continue;
                            if (Vehicle* vehicle = player->GetVehicle())
                                if (Unit* mount = vehicle->GetBase())
                                    list.push_back(mount->GetGUID());
                        }

                    std::list<Unit*> vehicleList;

                    if (!list.empty())
                        for (auto itr : list)
                            if (Unit* vehicle = ObjectAccessor::GetUnit(*me, itr))
                                vehicleList.push_back(vehicle);

                    Unit* target = nullptr;
                    if (!vehicleList.empty())
                        target = Trinity::Containers::SelectRandomContainerElement(vehicleList);

                    if (target)
                    {
                        me->getThreatManager().resetAllAggro();
                        me->AddThreat(target, 10000.0f);
                        AttackStart(target);
                        DoCast(target, SPELL_MINIONS_CHARGE);
                    }
                    _events.Repeat(urand(4500, 6000));
                }
                break;
                case EVENT_SHIELD_BREAKER:
                {
                    std::vector<uint64> list;
                    Map::PlayerList const &players = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player* player = itr->GetSource())
                        {
                            if (!me->IsInRange(player, 10.0f, 30.0f))
                                continue;
                            if (Vehicle* vehicle = player->GetVehicle())
                                if (Unit* mount = vehicle->GetBase())
                                    list.push_back(mount->GetGUID());
                        }
                    
                    if (!list.empty())
                    {
                        uint64 guid = Trinity::Containers::SelectRandomContainerElement(list);
                        if (Unit* target = ObjectAccessor::GetUnit(*me, guid))
                            DoCast(target, SPELL_NPC_SHIELD_BREAKER);
                    }
                    _events.Repeat(urand(6000, 8000));
                }
                break;
                case EVENT_THRUST:
                    if (Unit* victim = me->GetVictim())
                        if (me->GetExactDist(victim) <= 6.0f)
                            DoCast(victim, SPELL_PLAYER_VEHICLE_THRUST);
                    _events.Repeat(urand(3000, 5000));
                    break;

                    /******************* MAGE *******************/
                case EVENT_MAGE_SPELL_FIREBALL:
                    DoCastVictim(SPELL_FIREBALL);
                    _events.Repeat(5000);
                    break;
                case EVENT_MAGE_SPELL_BLAST_WAVE:
                    DoCastAOE(SPELL_BLAST_WAVE);
                    _events.Repeat(13000);
                    break;
                case EVENT_MAGE_SPELL_HASTE:
                    DoCastSelf(SPELL_HASTE);
                    _events.Repeat(22000);
                    break;
                case EVENT_MAGE_SPELL_POLYMORPH:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        DoCast(target, SPELL_POLYMORPH);
                    _events.Repeat(8000);
                    break;
                    /***************** MAGE END *****************/

                    /****************** SHAMAN ******************/
                case EVENT_SHAMAN_SPELL_CHAIN_LIGHTNING:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        DoCast(target, SPELL_CHAIN_LIGHTNING);
                    _events.Repeat(16000);
                    break;
                case EVENT_SHAMAN_SPELL_EARTH_SHIELD:
                    DoCastSelf(SPELL_EARTH_SHIELD);
                    _events.Repeat(urand(30000, 35000));
                    break;
                case EVENT_SHAMAN_SPELL_HEALING_WAVE:
                {
                    Unit* target = nullptr;
                    if (urand(0, 1))
                    {
                        target = DoSelectLowestHpFriendly(40.0f);
                        if (!target)
                            target = me;
                    }
                    else
                        target = me;

                    DoCast(target, SPELL_HEALING_WAVE);
                    _events.Repeat(22000);
                }
                break;
                case EVENT_SHAMAN_SPELL_HEX_OF_MENDING:
                    DoCastVictim(SPELL_HEX_OF_MENDING);
                    _events.Repeat(urand(20000, 25000));
                    break;
                    /**************** SHAMAN END ****************/

                    /****************** HUNTER ******************/
                case EVENT_HUNTER_SPELL_LIGHTNING_ARROWS:
                    DoCastAOE(SPELL_LIGHTNING_ARROWS);
                    _events.Repeat(urand(20000, 25000));
                    break;
                case EVENT_HUNTER_SPELL_MULTI_SHOT:
                {
                    if (!_unitTargetGUID)
                    {
                        if (Unit* target = SelectTarget(SELECT_TARGET_FARTHEST, 0, 30.0f, true))
                        {
                            DoCast(target, SPELL_SHOOT);
                            _unitTargetGUID = target->GetGUID();
                        }
                        _events.Repeat(2000);
                        break;
                    }
                    else
                    {
                        Unit* target = ObjectAccessor::GetUnit(*me, _unitTargetGUID);
                        if (target && me->IsInRange(target, 5.0f, 30.0f, false))
                            DoCast(target, SPELL_MULTI_SHOT);
                        else
                        {
                            Map::PlayerList const& players = me->GetMap()->GetPlayers();
                            for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                            {
                                Player* player = itr->GetSource();
                                if (player && me->IsInRange(player, 5.0f, 30.0f, false))
                                {
                                    DoCast(player, SPELL_MULTI_SHOT);
                                    break;
                                }
                            }
                        }
                        _unitTargetGUID = 0;
                    }
                    _events.Repeat(urand(15000, 20000));
                }
                break;
                /**************** HUNTER END ****************/

                /****************** ROGUE *******************/
                case EVENT_ROGUE_SPELL_EVISCERATE:
                    DoCastVictim(SPELL_EVISCERATE);
                    _events.Repeat(8000);
                    break;
                case EVENT_ROGUE_SPELL_FAN_OF_KNIVES:
                    _events.Repeat(14000);
                    break;
                case EVENT_ROGUE_SPELL_POISON_BOTTLE:
                    if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 30.0f, true))
                        DoCast(target, SPELL_POISON_BOTTLE);
                    _events.Repeat(19000);
                    break;
                    /**************** ROGUE END *****************/

                    /***************** WARRIOR ******************/
                case EVENT_WARRIOR_SPELL_MORTAL_STRIKE:
                    DoCastVictim(SPELL_MORTAL_STRIKE);
                    _events.Repeat(urand(8000, 12000));
                    break;
                case EVENT_WARRIOR_SPELL_BLADESTORM:
                    DoCastVictim(SPELL_BLADESTORM);
                    _events.Repeat(urand(15000, 20000));
                    break;
                case EVENT_WARRIOR_SPELL_INTERCEPT:
                {
                    Map::PlayerList const& pl = me->GetMap()->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = pl.begin(); itr != pl.end(); ++itr)
                    {
                        Player* player = itr->GetSource();
                        if (player && me->IsInRange(player, 8.0f, 25.0f, false))
                        {
                            DoResetThreat();
                            me->AddThreat(player, 5.0f);
                            DoCast(player, SPELL_INTERCEPT);
                            break;
                        }
                    }
                    _events.Repeat(7000);
                }
                break;
                    /*************** WARRIOR END ****************/
                default:
                    break;
            }
            
            if (me->HasUnitState(UNIT_STATE_CASTING) || ((me->GetEntry() == NPC_JACOB || me->GetEntry() == NPC_MOKRA) && me->HasAura(SPELL_BLADESTORM)))
                return;
        }

        DoMeleeAttackIfReady();
    }

private:
    InstanceScript* instance;
    EventMap _events;
    uint32 _bossOrder;
    bool _mountPhase;
    uint64 _newMountGUID;
    uint64 _unitTargetGUID;
};

class spell_toc5_mount_SpellScript : public SpellScript
{
    PrepareSpellScript(spell_toc5_mount_SpellScript);

    SpellCastResult CheckIfLanceEquiped()
    {
        if (GetCaster()->GetMapId() != 650) // TOC5
            return SPELL_CAST_OK;

        if (auto caster = GetCaster()->ToPlayer())
            if (!caster->HasItemOrGemWithIdEquipped(46106, 1))
            {
                SetCustomCastResultMessage(SPELL_CUSTOM_ERROR_MUST_HAVE_LANCE_EQUIPPED);
                return SPELL_FAILED_CUSTOM_ERROR;
            }

        return SPELL_CAST_OK;
    }

    void Register() override
    {
        OnCheckCast += SpellCheckCastFn(spell_toc5_mount_SpellScript::CheckIfLanceEquiped);
    }
};

void AddSC_boss_grand_champions()
{
    new CreatureAILoader<boss_grand_championAI>("boss_grand_champion");
    new CreatureAILoader<npc_toc5_grand_champion_minionAI>("npc_toc5_grand_champion_minion");
    new CreatureAILoader<npc_toc5_player_vehicleAI>("npc_toc5_player_vehicle");
    new SpellScriptLoaderEx<spell_toc5_mount_SpellScript>("spell_toc5_mount");
}
