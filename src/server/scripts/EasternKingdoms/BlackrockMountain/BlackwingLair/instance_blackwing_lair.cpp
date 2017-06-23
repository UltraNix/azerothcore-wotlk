#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "PassiveAI.h"
#include "blackwing_lair.h"
#include "Player.h"

Position const SummonPosition[8] =
{
    {-7661.207520f, -1043.268188f, 407.199554f, 6.280452f},
    {-7644.145020f, -1065.628052f, 407.204956f, 0.501492f},
    {-7624.260742f, -1095.196899f, 407.205017f, 0.544694f},
    {-7608.501953f, -1116.077271f, 407.199921f, 0.816443f},
    {-7531.841797f, -1063.765381f, 407.199615f, 2.874187f},
    {-7547.319336f, -1040.971924f, 407.205078f, 3.789175f},
    {-7568.547852f, -1013.112488f, 407.204926f, 3.773467f},
    {-7584.175781f, -989.6691289f, 407.199585f, 4.527447f},
};

uint32 const Entry[5] = {12422, 12458, 12416, 12420, 12459};

ObjectData const creatureData[] =
{
    { NPC_RAZORGORE,       DATA_RAZORGORE_THE_UNTAMED },
    { NPC_VAELASTRAZ,      DATA_VAELASTRAZ_THE_CORRUPT },
    { NPC_BROODLORD,       DATA_BROODLORD_LASHLAYER },
    { NPC_FIREMAW,         DATA_FIREMAW },
    { NPC_EBONROC,         DATA_EBONROC },
    { NPC_FLAMEGOR,        DATA_FLAMEGOR },
    { NPC_CHROMAGGUS,      DATA_CHROMAGGUS },
    { NPC_NEFARIAN,        DATA_NEFARIAN },
    { NPC_VICTOR_NEFARIUS, DATA_LORD_VICTOR_NEFARIUS },
    { 0,                   0 } // END
};

struct instance_blackwing_lair_InstanceMapScript : public InstanceScript
{
    instance_blackwing_lair_InstanceMapScript(Map* map) : InstanceScript(map)
    {
        SetBossNumber(EncounterCount);
        LoadObjectData(creatureData, nullptr);
    }

    void Initialize()
    {
        // Razorgore
        EggCount = 0;
        EggEvent = 0;
        RazorgoreDoorGUID = 0;
        EggList.clear();
        // Vaelastrasz the Corrupt
        VaelastraszDoorGUID = 0;
        // Broodlord Lashlayer
        BroodlordDoorGUID = 0;
        // Chormaggus
        ChrommagusDoorGUID = 0;
        NefarianDoorGUID = 0;
    }

    void OnCreatureCreate(Creature* creature)
    {
        switch (creature->GetEntry())
        {
            case NPC_BLACKWING_DRAGON:
            case NPC_BLACKWING_TASKMASTER:
            case NPC_BLACKWING_LEGIONAIRE:
            case NPC_BLACKWING_WARLOCK:
                if (Creature* razor = GetCreature(DATA_RAZORGORE_THE_UNTAMED))
                    razor->AI()->JustSummoned(creature);
                break;
        }

        InstanceScript::OnCreatureCreate(creature);
    }

    void OnGameObjectCreate(GameObject* go)
    {
        switch (go->GetEntry())
        {
            case 177807: // Egg
                if (GetBossState(BOSS_FIREMAW) == DONE)
                    go->SetPhaseMask(2, true);
                else
                    EggList.push_back(go->GetGUID());
                break;
            case 175946: // Door
                RazorgoreDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_RAZORGORE) == DONE, go);
                break;
            case 175185: // Door
                VaelastraszDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_VAELASTRAZ) == DONE, go);
                break;
            case 180424: // Door
                BroodlordDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_BROODLORD) == DONE, go);
                break;
            case 185483: // Door
                ChrommagusDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_FIREMAW) == DONE && GetBossState(BOSS_EBONROC) == DONE && GetBossState(BOSS_FLAMEGOR) == DONE, go);
                break;
            case 181125: // Door
                NefarianDoorGUID = go->GetGUID();
                HandleGameObject(0, GetBossState(BOSS_CHROMAGGUS) == DONE, go);
                break;
        }
    }

    void OnGameObjectRemove(GameObject* go)
    {
        if (go->GetEntry() == 177807) // Egg
            EggList.remove(go->GetGUID());
    }

    bool SetBossState(uint32 type, EncounterState state)
    {
        // pussywizard:
        if (GetBossState(type) == DONE && state != DONE) // prevent undoneing a boss xd
            return false;

        if (!InstanceScript::SetBossState(type, state))
            return false;

        switch (type)
        {
            case BOSS_RAZORGORE:
                HandleGameObject(RazorgoreDoorGUID, state == DONE);
                if (state == DONE)
                {
                    for (std::list<uint64>::const_iterator itr = EggList.begin(); itr != EggList.end(); ++itr)
                        if (GameObject* egg = instance->GetGameObject((*itr)))
                            egg->SetPhaseMask(2, true);
                }
                SetData(DATA_EGG_EVENT, NOT_STARTED);
                break;
            case BOSS_VAELASTRAZ:
                HandleGameObject(VaelastraszDoorGUID, state == DONE);
                break;
            case BOSS_BROODLORD:
                HandleGameObject(BroodlordDoorGUID, state == DONE);
                break;
            case BOSS_FIREMAW:
            case BOSS_EBONROC:
            case BOSS_FLAMEGOR:
                HandleGameObject(ChrommagusDoorGUID, GetBossState(BOSS_FIREMAW) == DONE && GetBossState(BOSS_EBONROC) == DONE && GetBossState(BOSS_FLAMEGOR) == DONE);
                break;
            case BOSS_CHROMAGGUS:
                HandleGameObject(NefarianDoorGUID, state == DONE);
                break;
            case BOSS_NEFARIAN:
                switch (state)
                {
                    case NOT_STARTED:
                        if (Creature* nefarian = GetCreature(DATA_NEFARIAN))
                            nefarian->DespawnOrUnsummon();
                        break;
                    case FAIL:
                        _events.ScheduleEvent(EVENT_RESPAWN_NEFARIUS, 15*IN_MILLISECONDS*MINUTE);
                        SetBossState(BOSS_NEFARIAN, NOT_STARTED);
                        break;
                    default:
                        break;
                }
                break;
        }
        return true;
    }

    void SetData(uint32 type, uint32 data)
    {
        if (type == DATA_EGG_EVENT)
        {
            switch (data)
            {
                case IN_PROGRESS:
                    _events.ScheduleEvent(EVENT_RAZOR_SPAWN, 45*IN_MILLISECONDS);
                    EggEvent = data;
                    EggCount = 0;
                    break;
                case NOT_STARTED:
                    _events.CancelEvent(EVENT_RAZOR_SPAWN);
                    EggEvent = data;
                    EggCount = 0;
                    break;
                case SPECIAL:
                    if (++EggCount == 15)
                    {
                        if (Creature* razor = GetCreature(DATA_RAZORGORE_THE_UNTAMED))
                        {
                            SetData(DATA_EGG_EVENT, DONE);
                            razor->RemoveAurasDueToSpell(42013); // MindControl
                            DoRemoveAurasDueToSpellOnPlayers(42013);
                        }
                        _events.ScheduleEvent(EVENT_RAZOR_PHASE_TWO, IN_MILLISECONDS);
                        _events.CancelEvent(EVENT_RAZOR_SPAWN);
                    }
                    if (EggEvent == NOT_STARTED)
                        SetData(DATA_EGG_EVENT, IN_PROGRESS);
                    break;
            }
        }
    }

    void OnUnitDeath(Unit* unit)
    {
        //! HACK, needed because of buggy CreatureAI after charm
        if (unit->GetEntry() == NPC_RAZORGORE && GetBossState(BOSS_RAZORGORE) != DONE)
            SetBossState(BOSS_RAZORGORE, DONE);
    }

    void Update(uint32 diff)
    {
        if (_events.Empty())
            return;

        _events.Update(diff);

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_RAZOR_SPAWN:
                    for (uint8 i = urand(2, 5); i > 0 ; --i)
                        if (Creature* summon =  instance->SummonCreature(Entry[urand(0, 4)], SummonPosition[urand(0, 7)]))
                            summon->SetInCombatWithZone();
                    _events.ScheduleEvent(EVENT_RAZOR_SPAWN, urand(12, 17)*IN_MILLISECONDS);
                    break;
                case EVENT_RAZOR_PHASE_TWO:
                    _events.CancelEvent(EVENT_RAZOR_SPAWN);
                    if (Creature* razor = GetCreature(DATA_RAZORGORE_THE_UNTAMED))
                        razor->AI()->DoAction(ACTION_PHASE_TWO);
                    break;
                case EVENT_RESPAWN_NEFARIUS:
                    if (Creature* nefarius = GetCreature(DATA_LORD_VICTOR_NEFARIUS))
                    {
                        nefarius->SetPhaseMask(1, true);
                        nefarius->setActive(true);
                        nefarius->Respawn();
                        nefarius->GetMotionMaster()->MoveTargetedHome();
                    }
                    break;
            }
        }
    }

protected:
    // Misc
    EventMap _events;
    // Razorgore
    uint8 EggCount;
    uint32 EggEvent;
    uint64 RazorgoreDoorGUID;
    std::list<uint64> EggList;

    // Vaelastrasz the Corrupt
    uint64 VaelastraszDoorGUID;

    // Broodlord Lashlayer
    uint64 BroodlordDoorGUID;

    // 3 Dragons
    uint64 ChrommagusDoorGUID;

    // Chormaggus
    uint64 NefarianDoorGUID;
};

void AddSC_instance_blackwing_lair()
{
    new InstanceMapScriptLoader<instance_blackwing_lair_InstanceMapScript>(BRLScriptName, 469);
}
