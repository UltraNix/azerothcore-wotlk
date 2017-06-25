#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "zulfarrak.h"
#include "Player.h"
#include "SpellScript.h"
#include "GridNotifiers.h"
#include "CellImpl.h"

int const pyramidSpawnTotal = 54;
/* list of wave spawns: 0 = wave ID, 1 = creature id, 2 = x, 3 = y
no z coordinat b/c they're all the same */
float pyramidSpawns[pyramidSpawnTotal][4] = {
    { 1, 7789, 1894.64f, 1206.29f },
    { 1, 7787, 1890.08f, 1218.68f },
    { 1, 8876, 1883.76f, 1222.3f },
    { 1, 7789, 1874.18f, 1221.24f },
    { 1, 7787, 1892.28f, 1225.49f },
    { 1, 7788, 1889.94f, 1212.21f },
    { 1, 7787, 1879.02f, 1223.06f },
    { 1, 7789, 1874.45f, 1204.44f },
    { 1, 8876, 1898.23f, 1217.97f },
    { 1, 7787, 1882.07f, 1225.7f },
    { 1, 8877, 1896.46f, 1205.62f },
    { 1, 7787, 1886.97f, 1225.86f },
    { 1, 7787, 1894.72f, 1221.91f },
    { 1, 7787, 1883.5f, 1218.25f },
    { 1, 7787, 1886.93f, 1221.4f },
    { 1, 8876, 1889.82f, 1222.51f },
    { 1, 7788, 1893.07f, 1215.26f },
    { 1, 7788, 1878.57f, 1214.16f },
    { 1, 7788, 1883.74f, 1212.35f },
    { 1, 8877, 1877, 1207.27f },
    { 1, 8877, 1873.63f, 1204.65f },
    { 1, 8876, 1877.4f, 1216.41f },
    { 1, 8877, 1899.63f, 1202.52f },
    { 2, 7789, 1902.83f, 1223.41f },
    { 2, 8876, 1889.82f, 1222.51f },
    { 2, 7787, 1883.5f, 1218.25f },
    { 2, 7788, 1883.74f, 1212.35f },
    { 2, 8877, 1877, 1207.27f },
    { 2, 7787, 1890.08f, 1218.68f },
    { 2, 7789, 1894.64f, 1206.29f },
    { 2, 8876, 1877.4f, 1216.41f },
    { 2, 7787, 1892.28f, 1225.49f },
    { 2, 7788, 1893.07f, 1215.26f },
    { 2, 8877, 1896.46f, 1205.62f },
    { 2, 7789, 1874.45f, 1204.44f },
    { 2, 7789, 1874.18f, 1221.24f },
    { 2, 7787, 1879.02f, 1223.06f },
    { 2, 8876, 1898.23f, 1217.97f },
    { 2, 7787, 1882.07f, 1225.7f },
    { 2, 8877, 1873.63f, 1204.65f },
    { 2, 7787, 1886.97f, 1225.86f },
    { 2, 7788, 1878.57f, 1214.16f },
    { 2, 7787, 1894.72f, 1221.91f },
    { 2, 7787, 1886.93f, 1221.4f },
    { 2, 8876, 1883.76f, 1222.3f },
    { 2, 7788, 1889.94f, 1212.21f },
    { 2, 8877, 1899.63f, 1202.52f },
    { 3, 7788, 1878.57f, 1214.16f },
    { 3, 7787, 1894.72f, 1221.91f },
    { 3, 7787, 1886.93f, 1221.4f },
    { 3, 8876, 1883.76f, 1222.3f },
    { 3, 7788, 1889.94f, 1212.21f },
    { 3, 7275, 1889.23f, 1207.72f },
    { 3, 7796, 1879.77f, 1207.96f }
};

float Spawnsway[2][3] =
{
    { 1884.86f, 1228.62f, 9 },
    { 1887.53f, 1263, 41 }
};

class instance_zulfarrak : public InstanceMapScript
{
public:
    instance_zulfarrak() : InstanceMapScript("instance_zulfarrak", 209) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_zulfarrak_InstanceMapScript(map);
    }

    struct instance_zulfarrak_InstanceMapScript : public InstanceScript
    {
        instance_zulfarrak_InstanceMapScript(Map* map) : InstanceScript(map) { }

        uint32 GahzRillaEncounter;
        uint64 ZumrahGUID;
        uint64 BlyGUID;
        uint64 WeegliGUID;
        uint64 OroGUID;
        uint64 RavenGUID;
        uint64 MurtaGUID;
        uint64 EndDoorGUID;
        uint32 PyramidPhase;
        uint32 major_wave_Timer;
        uint32 minor_wave_Timer;
        uint32 addGroupSize;
        uint32 waypoint;

        void Initialize() override
        {
            GahzRillaEncounter = NOT_STARTED;
            ZumrahGUID = 0;
            BlyGUID = 0;
            WeegliGUID = 0;
            OroGUID = 0;
            RavenGUID = 0;
            MurtaGUID = 0;
            EndDoorGUID = 0;
            PyramidPhase = 0;
            major_wave_Timer = 0;
            minor_wave_Timer = 0;
            addGroupSize = 0;
            waypoint = 0;
        }

        void OnCreatureCreate(Creature* creature) override
        {
            switch (creature->GetEntry())
            {
            case ENTRY_ZUM_RAH:
                ZumrahGUID = creature->GetGUID();
                break;
            case ENTRY_BLY:
                BlyGUID = creature->GetGUID();
                creature->SetReactState(REACT_PASSIVE); // starts out passive (in a cage)
                break;
            case ENTRY_RAVEN:
                RavenGUID = creature->GetGUID();
                creature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            case ENTRY_ORO:
                OroGUID = creature->GetGUID();
                creature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            case ENTRY_WEEGLI:
                WeegliGUID = creature->GetGUID();
                creature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            case ENTRY_MURTA:
                MurtaGUID = creature->GetGUID();
                creature->SetReactState(REACT_PASSIVE);// starts out passive (in a cage)
                break;
            case ENTRY_GAHZRILLA:
                if (GahzRillaEncounter >= IN_PROGRESS)
                    creature->DisappearAndDie();
                else
                    GahzRillaEncounter = IN_PROGRESS;
                break;
            }
        }

        void OnGameObjectCreate(GameObject* go) override
        {
            switch (go->GetEntry())
            {
            case GO_END_DOOR:
                EndDoorGUID = go->GetGUID();
                break;
            }
        }

        uint32 GetData(uint32 type) const override
        {
            switch (type)
            {
            case EVENT_PYRAMID:
                return PyramidPhase;
            }
            return 0;
        }

        uint64 GetData64(uint32 data) const override
        {
            switch (data)
            {
            case ENTRY_ZUM_RAH:
                return ZumrahGUID;
            case ENTRY_BLY:
                return BlyGUID;
            case ENTRY_RAVEN:
                return RavenGUID;
            case ENTRY_ORO:
                return OroGUID;
            case ENTRY_WEEGLI:
                return WeegliGUID;
            case ENTRY_MURTA:
                return MurtaGUID;
            case GO_END_DOOR:
                return EndDoorGUID;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (type)
            {
            case EVENT_PYRAMID:
                PyramidPhase = data;
                break;
            };
        }

        virtual void Update(uint32 diff)
        {
            switch (PyramidPhase)
            {
            case PYRAMID_NOT_STARTED:
            case PYRAMID_KILLED_ALL_TROLLS:
                break;
            case PYRAMID_ARRIVED_AT_STAIR:
                SpawnPyramidWave(1);
                SetData(EVENT_PYRAMID, PYRAMID_WAVE_1);
                major_wave_Timer = 120000;
                minor_wave_Timer = 0;
                addGroupSize = 2;
                break;
            case PYRAMID_WAVE_1:
                if (IsWaveAllDead())
                {
                    SetData(EVENT_PYRAMID, PYRAMID_PRE_WAVE_2);
                    major_wave_Timer = 10000; //give players a few seconds before wave 2 starts to rebuff
                }
                else
                    if (minor_wave_Timer<diff)
                    {
                        SendAddsUpStairs(addGroupSize++);
                        minor_wave_Timer = 10000;
                    }
                    else
                        minor_wave_Timer -= diff;
                break;
            case PYRAMID_PRE_WAVE_2:
                if (major_wave_Timer<diff)
                {
                    // beginning 2nd wave!
                    SpawnPyramidWave(2);
                    SetData(EVENT_PYRAMID, PYRAMID_WAVE_2);
                    minor_wave_Timer = 0;
                    addGroupSize = 2;
                }
                else
                    major_wave_Timer -= diff;
                break;
            case PYRAMID_WAVE_2:
                if (IsWaveAllDead())
                {
                    SpawnPyramidWave(3);
                    SetData(EVENT_PYRAMID, PYRAMID_PRE_WAVE_3);
                    major_wave_Timer = 5000; //give NPCs time to return to their home spots
                }
                else
                    if (minor_wave_Timer<diff)
                    {
                        SendAddsUpStairs(addGroupSize++);
                        minor_wave_Timer = 10000;
                    }
                    else
                        minor_wave_Timer -= diff;
                break;
            case PYRAMID_PRE_WAVE_3:
                if (major_wave_Timer<diff)
                {
                    // move NPCs to bottom of stair
                    MoveNPCIfAlive(ENTRY_BLY, 1887.92f, 1228.179f, 9.98f, 4.78f);
                    MoveNPCIfAlive(ENTRY_MURTA, 1891.57f, 1228.68f, 9.69f, 4.78f);
                    MoveNPCIfAlive(ENTRY_ORO, 1897.23f, 1228.34f, 9.43f, 4.78f);
                    MoveNPCIfAlive(ENTRY_RAVEN, 1883.68f, 1227.95f, 9.543f, 4.78f);
                    MoveNPCIfAlive(ENTRY_WEEGLI, 1878.02f, 1227.65f, 9.485f, 4.78f);
                    SetData(EVENT_PYRAMID, PYRAMID_WAVE_3);
                }
                else
                    major_wave_Timer -= diff;
                break;
            case PYRAMID_WAVE_3:
                if (IsWaveAllDead()) // move NPCS to their final positions
                {
                    SetData(EVENT_PYRAMID, PYRAMID_KILLED_ALL_TROLLS);
                    MoveNPCIfAlive(ENTRY_BLY, 1883.82f, 1200.83f, 8.87f, 1.32f);
                    MoveNPCIfAlive(ENTRY_MURTA, 1891.83f, 1201.45f, 8.87f, 1.32f);
                    MoveNPCIfAlive(ENTRY_ORO, 1894.50f, 1204.40f, 8.87f, 1.32f);
                    MoveNPCIfAlive(ENTRY_RAVEN, 1874.11f, 1206.17f, 8.87f, 1.32f);
                    MoveNPCIfAlive(ENTRY_WEEGLI, 1877.52f, 1199.63f, 8.87f, 1.32f);
                }
                break;
            };
        }

        std::list<uint64> addsAtBase, movedadds;

        void MoveNPCIfAlive(uint32 entry, float x, float y, float z, float o)
        {
            if (Creature* npc = instance->GetCreature(GetData64(entry)))
            {
                if (npc->IsAlive())
                {
                    npc->SetWalk(true);
                    npc->GetMotionMaster()->MovePoint(1, x, y, z);
                    npc->SetHomePosition(x, y, z, o);
                }
            }
        }

        void SpawnPyramidWave(uint32 wave)
        {
            for (int i = 0; i < pyramidSpawnTotal; i++)
            {
                if (pyramidSpawns[i][0] == (float)wave)
                {
                    Position pos = { pyramidSpawns[i][2], pyramidSpawns[i][3], 8.87f, 0 };
                    TempSummon* ts = instance->SummonCreature(uint32(pyramidSpawns[i][1]), pos);
                    ts->GetMotionMaster()->MoveRandom(10);
                    addsAtBase.push_back(ts->GetGUID());
                }
            }
        }

        bool IsWaveAllDead()
        {
            for (std::list<uint64>::iterator itr = addsAtBase.begin(); itr != addsAtBase.end(); ++itr)
            {
                if (Creature* add = instance->GetCreature((*itr)))
                {
                    if (add->IsAlive())
                        return false;
                }
            }
            for (std::list<uint64>::iterator itr = movedadds.begin(); itr != movedadds.end(); ++itr)
            {
                if (Creature* add = instance->GetCreature(((*itr))))
                {
                    if (add->IsAlive())
                        return false;
                }
            }
            return true;
        }

        void SendAddsUpStairs(uint32 count)
        {
            //pop a add from list, send him up the stairs...
            for (uint32 addCount = 0; addCount<count && !addsAtBase.empty(); addCount++)
            {
                if (Creature* add = instance->GetCreature(*addsAtBase.begin()))
                {
                    add->GetMotionMaster()->MovePath(PATH_ADDS, false);
                    movedadds.push_back(add->GetGUID());
                }
                addsAtBase.erase(addsAtBase.begin());
            }
        }
    };

};

class spell_zulfarrak_summon_zulfarrak_zombies : public SpellScriptLoader
{
    public:
        spell_zulfarrak_summon_zulfarrak_zombies() : SpellScriptLoader("spell_zulfarrak_summon_zulfarrak_zombies") { }

        class spell_zulfarrak_summon_zulfarrak_zombies_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_zulfarrak_summon_zulfarrak_zombies_SpellScript);

            void HandleSummon(SpellEffIndex effIndex)
            {
                if (effIndex == EFFECT_0)
                {
                    if (roll_chance_i(30))
                    {
                        PreventHitDefaultEffect(effIndex);
                        return;
                    }
                }
                else if (roll_chance_i(40))
                {
                    PreventHitDefaultEffect(effIndex);
                    return;
                }
            }

            void Register()
            {
                OnEffectHit += SpellEffectFn(spell_zulfarrak_summon_zulfarrak_zombies_SpellScript::HandleSummon, EFFECT_0, SPELL_EFFECT_SUMMON);
                OnEffectHit += SpellEffectFn(spell_zulfarrak_summon_zulfarrak_zombies_SpellScript::HandleSummon, EFFECT_1, SPELL_EFFECT_SUMMON);
            }
        };

        SpellScript* GetSpellScript() const
        {
            return new spell_zulfarrak_summon_zulfarrak_zombies_SpellScript;
        }
};

/*######
## npc_sergeant_bly
######*/

enum blyAndCrewFactions
{
    FACTION_HOSTILE     = 14,
    FACTION_FRIENDLY    = 35,  //while in cages (so the trolls won't attack them while they're caged)
    FACTION_FREED       = 250  //after release (so they'll be hostile towards trolls)
};

enum blySays
{
    SAY_1,
    SAY_2
};

enum blySpells
{
    SPELL_SHIELD_BASH   = 11972,
    SPELL_REVENGE       = 12170
};

enum blyEvents
{
    EVENT_SHIELD_BASH   = 1,
    EVENT_REVENGE
};

#define GOSSIP_BLY                  "[PH] In that case, I will take my reward!"

class npc_sergeant_bly : public CreatureScript
{
    public:
        npc_sergeant_bly() : CreatureScript("npc_sergeant_bly") { }

        bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
        {
            player->PlayerTalkClass->ClearMenus();
            if (action == GOSSIP_ACTION_INFO_DEF + 1)
            {
                player->CLOSE_GOSSIP_MENU();
                CAST_AI(npc_sergeant_bly::npc_sergeant_blyAI, creature->AI())->PlayerGUID = player->GetGUID();
                creature->AI()->DoAction(0);
            }
            return true;
        }

        bool OnGossipHello(Player* player, Creature* creature) override
        {
            if (InstanceScript* instance = creature->GetInstanceScript())
            {
                if (instance->GetData(EVENT_PYRAMID) == PYRAMID_KILLED_ALL_TROLLS)
                {
                    player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_BLY, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                    player->SEND_GOSSIP_MENU(1517, creature->GetGUID());
                }
                else
                    if (instance->GetData(EVENT_PYRAMID) == PYRAMID_NOT_STARTED)
                        player->SEND_GOSSIP_MENU(1515, creature->GetGUID());
                    else
                        player->SEND_GOSSIP_MENU(1516, creature->GetGUID());
                return true;
            }
            return false;
        }

        CreatureAI* GetAI(Creature* creature) const override
        {
            return GetInstanceAI<npc_sergeant_blyAI>(creature);
        }

        struct npc_sergeant_blyAI : public ScriptedAI
        {
            npc_sergeant_blyAI(Creature* creature) : ScriptedAI(creature)
            {
                instance = creature->GetInstanceScript();
                postGossipStep = 0;
            }

            InstanceScript* instance;

            uint32 postGossipStep;
            uint32 Text_Timer;                               
            uint64 PlayerGUID;

            void Reset() override
            {
                me->setFaction(FACTION_FRIENDLY);
            }

            void UpdateAI(uint32 diff) override
            {
                if (postGossipStep>0 && postGossipStep<4)
                {
                    if (Text_Timer<diff)
                    {
                        switch (postGossipStep)
                        {
                            case 1:
                                //weegli doesn't fight - he goes & blows up the door
                                if (Creature* pWeegli = instance->instance->GetCreature(instance->GetData64(ENTRY_WEEGLI)))
                                    pWeegli->AI()->DoAction(0);
                                Talk(SAY_1);
                                Text_Timer = 5000;
                                break;
                            case 2:
                                Talk(SAY_2);
                                Text_Timer = 5000;
                                break;
                            case 3:
                                me->setFaction(FACTION_HOSTILE);
                                if (Player* target = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                                    AttackStart(target);

                                switchFactionIfAlive(instance, ENTRY_RAVEN);
                                switchFactionIfAlive(instance, ENTRY_ORO);
                                switchFactionIfAlive(instance, ENTRY_MURTA);
                            }
                            postGossipStep++;
                    }
                    else Text_Timer -= diff;
                }

                if (!UpdateVictim())
                    return;
                
                _events.Update(diff);

                while (uint32 eventId = _events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_SHIELD_BASH:
                            DoCastVictim(SPELL_SHIELD_BASH);
                            _events.Repeat(15000);
                            break;
                        case EVENT_REVENGE:
                            DoCastVictim(SPELL_REVENGE);
                            _events.Repeat(10000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void DoAction(int32 /*param*/) override
            {
                postGossipStep = 1;
                Text_Timer = 0;
            }

            void switchFactionIfAlive(InstanceScript* instance, uint32 entry)
            {
                if (Creature* crew = instance->instance->GetCreature(instance->GetData64(entry)))
                    if (crew->IsAlive() && crew->IsAIEnabled)
                    {
                        if (Player* target = ObjectAccessor::GetPlayer(*me, PlayerGUID))
                            crew->AI()->AttackStart(target);
                        crew->setFaction(FACTION_HOSTILE);
                    }
            }
        private:
            EventMap _events;
        };

};

/*######
+## go_troll_cage
+######*/

class go_troll_cage : public GameObjectScript
{
    public:
        go_troll_cage() : GameObjectScript("go_troll_cage") { }

        bool OnGossipHello(Player* /*player*/, GameObject* go) override
        {
            if (InstanceScript* instance = go->GetInstanceScript())
            {
                instance->SetData(EVENT_PYRAMID, PYRAMID_CAGES_OPEN);
                initBlyCrewMember(instance, ENTRY_BLY, 1884.99f, 1263, 41.52f, 4.76f);
                initBlyCrewMember(instance, ENTRY_RAVEN, 1882.5f, 1263, 41.52f, 4.76f);
                initBlyCrewMember(instance, ENTRY_ORO, 1886.47f, 1270.68f, 41.68f, 4.76f);
                initBlyCrewMember(instance, ENTRY_WEEGLI, 1890, 1263, 41.52f, 4.76f);
                initBlyCrewMember(instance, ENTRY_MURTA, 1891.19f, 1272.03f, 41.60f, 4.76f);
            }
            return false;
        }

    private:
        void initBlyCrewMember(InstanceScript* instance, uint32 entry, float x, float y, float z, float o)
        {
            if (Creature* crew = instance->instance->GetCreature(instance->GetData64(entry)))
            {
                crew->SetReactState(REACT_AGGRESSIVE);
                crew->SetWalk(true);
                crew->SetHomePosition(x, y, z, o);
                crew->GetMotionMaster()->MovePoint(1, x, y, z);
                crew->setFaction(FACTION_FREED);
            }
        }
};

/*######
## npc_weegli_blastfuse
######*/

enum weegliSpells
{
    SPELL_BOMB              = 8858,
    SPELL_GOBLIN_LAND_MINE  = 21688,
    SPELL_SHOOT             = 6660,
    SPELL_WEEGLIS_BARREL    = 10772
};

enum weegliSays
{
    SAY_WEEGLI_OHNO,
    SAY_WEEGLI_OK_I_GO
};

enum weegliEvents
{
    EVENT_BOMB              = 1
};

#define GOSSIP_WEEGLI               "[PH] Please blow up the door."

class npc_weegli_blastfuse : public CreatureScript
{
public:
    npc_weegli_blastfuse() : CreatureScript("npc_weegli_blastfuse") { }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 /*sender*/, uint32 action) override
    {
        player->PlayerTalkClass->ClearMenus();
        if (action == GOSSIP_ACTION_INFO_DEF + 1)
        {
            player->CLOSE_GOSSIP_MENU();
            //here we make him run to door, set the charge and run away off to nowhere
            creature->AI()->DoAction(0);
        }
        return true;
    }

    bool OnGossipHello(Player* player, Creature* creature) override
    {
        if (InstanceScript* instance = creature->GetInstanceScript())
        {
            switch (instance->GetData(EVENT_PYRAMID))
            {
            case PYRAMID_KILLED_ALL_TROLLS:
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_WEEGLI, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
                player->SEND_GOSSIP_MENU(1514, creature->GetGUID());  //if event can proceed to end
                break;
            case PYRAMID_NOT_STARTED:
                player->SEND_GOSSIP_MENU(1511, creature->GetGUID());  //if event not started
                break;
            default:
                player->SEND_GOSSIP_MENU(1513, creature->GetGUID());  //if event are in progress
            }
            return true;
        }
        return false;
    }

    CreatureAI* GetAI(Creature* creature) const override
    {
        return GetInstanceAI<npc_weegli_blastfuseAI>(creature);
    }

    struct npc_weegli_blastfuseAI : public ScriptedAI
    {
        npc_weegli_blastfuseAI(Creature* creature) : ScriptedAI(creature)
        {
            instance = creature->GetInstanceScript();
            destroyingDoor = false;
        }

        bool destroyingDoor;
        InstanceScript* instance;

        void Reset() override
        {
            /*instance->SetData(0, NOT_STARTED);*/
        }

        void AttackStart(Unit* victim) override
        {
            AttackStartCaster(victim, 10);//keep back & toss bombs/shoot
        }

        void JustDied(Unit* /*killer*/) override
        {
            /*instance->SetData(0, DONE);*/
        }

        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;

            if (_events.ExecuteEvent() == EVENT_BOMB)
            {
                DoCastVictim(SPELL_BOMB);
                _events.Repeat(10000);
            }

            if (me->isAttackReady() && !me->IsWithinMeleeRange(me->GetVictim()))
            {
                DoCastVictim(SPELL_SHOOT);
                me->SetSheath(SHEATH_STATE_RANGED);
            }
            else
            {
                me->SetSheath(SHEATH_STATE_MELEE);
                DoMeleeAttackIfReady();
            }
        }

        void MovementInform(uint32 /*type*/, uint32 /*id*/) override
        {
            if (instance->GetData(EVENT_PYRAMID) == PYRAMID_CAGES_OPEN)
            {
                instance->SetData(EVENT_PYRAMID, PYRAMID_ARRIVED_AT_STAIR);
                Talk(SAY_WEEGLI_OHNO);
                me->SetHomePosition(1882.69f, 1272.28f, 41.87f, 4.78f);
            }
            else
                if (destroyingDoor)
                {
                    instance->DoUseDoorOrButton(instance->GetData64(GO_END_DOOR));
                    /// @todo leave the area...
                    me->DespawnOrUnsummon();
                };
        }

        void DoAction(int32 /*param*/) override
        {
            DestroyDoor();
        }

        void DestroyDoor()
        {
            if (me->IsAlive())
            {
                me->setFaction(FACTION_FRIENDLY);
                me->GetMotionMaster()->MovePoint(0, 1858.57f, 1146.35f, 14.745f);
                me->SetHomePosition(1858.57f, 1146.35f, 14.745f, 3.85f); // in case he gets interrupted
                Talk(SAY_WEEGLI_OK_I_GO);
                destroyingDoor = true;
            }
        }

    private:
        EventMap _events;
    };
};

void AddSC_instance_zulfarrak()
{
    new instance_zulfarrak();
    new spell_zulfarrak_summon_zulfarrak_zombies();
    new npc_sergeant_bly();
    new go_troll_cage();
    new npc_weegli_blastfuse();
}
