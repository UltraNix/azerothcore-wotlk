/*
REWRITTEN BY XINEF
*/

#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "sethekk_halls.h"

Position const PosCenter = { -87.5742f, 287.856f, 26.4832f, 4.4f };
Position const SummonAnzuPos = { -87.5742f, 287.856f, 26.4832f, 0.08f };

class instance_sethekk_halls : public InstanceMapScript
{
public:
    instance_sethekk_halls() : InstanceMapScript("instance_sethekk_halls", 556) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_sethekk_halls_InstanceMapScript(map);
    }

    struct instance_sethekk_halls_InstanceMapScript : public InstanceScript
    {
        instance_sethekk_halls_InstanceMapScript(Map* map) : InstanceScript(map) {}

        void Initialize()
        {
            AnzuEncounter = NOT_STARTED;
            m_uiIkissDoorGUID = 0;
            _talonKingsCofferGUID = 0;
            _anzuGUID = 0;
            _ravenGodTargetGUID = 0;
            _ravenGodPortalGUID = 0;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch (creature->GetEntry())
            {
                case NPC_ANZU:
                {
                    _anzuGUID = creature->GetGUID();
                    break;
                }
                case NPC_RAVEN_GOD_TARGET:
                {
                    _ravenGodTargetGUID = creature->GetGUID();
                    break;
                }
                case NPC_RAVEN_GOD_PORTAL:
                {
                    _ravenGodPortalGUID = creature->GetGUID();
                    break;
                }
                case NPC_RAVEN_GOD_CASTER:
                {
                    _ravenGodCasters.push_back(creature->GetGUID());
                    break;
                }
                case NPC_AVIAN_FLYER:
                {
                    creature->SetCanFly(true);
                    creature->SetDisableGravity(true);
                    creature->SetInhabitType(INHABIT_AIR);
                    break;
                }

            }

            if (creature->GetEntry() == NPC_ANZU || creature->GetEntry() == NPC_VOICE_OF_THE_RAVEN_GOD)
                if (AnzuEncounter >= IN_PROGRESS)
                    creature->DespawnOrUnsummon(1);
        }

        void OnGameObjectCreate(GameObject* go)
        {
            switch (go->GetEntry())
            {
                case GO_IKISS_DOOR:
                    m_uiIkissDoorGUID = go->GetGUID();
                    break;
                case GO_THE_TALON_KINGS_COFFER:
                    _talonKingsCofferGUID = go->GetGUID();
                    break;
                case GO_RAVENS_CLAW:
                {
                    _ravenClawGUID = go->GetGUID();
                    if (AnzuEncounter == DONE)
                    {
                        go->SetRespawnTime(DAY);
                        go->SetLootState(GO_JUST_DEACTIVATED);
                        go->SetPhaseMask(2, false);
                    }
                    break;
                }
                case GO_MOONSTONE:
                    _moonstoneGUID = go->GetGUID();
                    break;
                case GO_RIFT:
                    _riftGUID = go->GetGUID();
                    break;
            }
        }

        void SetData(uint32 type, uint32 data)
        {
            switch (type)
            {
                case DATA_IKISSDOOREVENT:
                    if (data == DONE)
                    {
                        DoUseDoorOrButton(m_uiIkissDoorGUID, DAY*IN_MILLISECONDS);
                        if (GameObject* coffer = instance->GetGameObject(_talonKingsCofferGUID))
                            coffer->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE|GO_FLAG_INTERACT_COND);
                    }
                    break;
                case TYPE_ANZU_ENCOUNTER:
                    AnzuEncounter = data;
                    SaveToDB();
                    break;
                case DATA_ANZU_STARTEVENT:
                {
                    if (_anzuGUID && GetBossState(BOSS_ANZU) != DONE)
                        events.ScheduleEvent(EVENT_ANZU_1, 1s);
                    break;
                }
            }
        }

        void Update(const uint32 diff) override
        {
            if (events.Empty())
                return;

            events.Update(diff);

            while (auto eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                case EVENT_ANZU_1:
                {
                    if (Creature * redBall = instance->GetCreature(_ravenGodTargetGUID))
                    {
                        // Summon Rift GO
                        redBall->SummonGameObject(GO_RIFT, PosCenter.GetPositionX(), PosCenter.GetPositionY(), PosCenter.GetPositionZ() + 4.5f, PosCenter.GetOrientation(),
                            0.f, 0.f, 0.f, 0.f, 0);

                        // Summon Moonstone GO
                        // Place Moonstone in Claw
                        redBall->SummonGameObject(GO_MOONSTONE, -87.5740f, 287.986f, 30.4532f, 3.97019f,
                            0.f, 0.f, 0.f, 0.f, 0);

                        // Purple Banish Trigger NPC
                        redBall->CastSpell(redBall, SPELL_PURPLE_BANISH, true);
                    }

                    // summonTarget is used as handler
                    if (Creature * c = instance->GetCreature(_ravenGodPortalGUID))
                        c->CastSpell(c, SPELL_PORTAL, true);

                    if (GameObject * go = instance->GetGameObject(_ravenClawGUID))
                        go->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NOT_SELECTABLE);

                    events.ScheduleEvent(EVENT_ANZU_2, 2s);
                    break;
                }
                case EVENT_ANZU_2:
                {
                    if (Creature * redBall = instance->GetCreature(_ravenGodTargetGUID))
                    {
                        for (auto& guid : _ravenGodCasters)
                            if (Creature * creature = instance->GetCreature(guid))
                                creature->CastSpell(redBall, SPELL_SUMMONING_BEAMS, true);
                        // NPC_RAVEN_GOD_TARGET starting to move to center position
                        if (Creature * redBall = instance->GetCreature(_ravenGodTargetGUID))
                        {
                            redBall->SetWalk(true);
                            Position pos = PosCenter;
                            pos.m_positionZ += 8.5f;
                            redBall->GetMotionMaster()->MovePoint(0, pos, false);
                        }
                    }

                    events.ScheduleEvent(EVENT_ANZU_3, 18s);
                    break;
                }

                case EVENT_ANZU_3:
                {
                    // Cast SPELL_SHAKE_CAMERA on all players
                    Map::PlayerList const& players = instance->GetPlayers();
                    for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                        if (Player * player = itr->GetSource()->ToPlayer())
                            player->CastSpell(player, SPELL_SHAKE_CAMERA, true);

                    events.ScheduleEvent(EVENT_ANZU_4, 8s);
                    break;
                }
                case EVENT_ANZU_4:
                {
                    // Cast SPELL_RED_LIGHTNING on NPC_RAVEN_GOD_TARGET
                    if (Creature * c = instance->GetCreature(_ravenGodTargetGUID))
                        c->CastSpell(c, SPELL_RED_LIGHTNING, true);

                    if (GameObject * go = instance->GetGameObject(_moonstoneGUID))
                    {
                        go->SetRespawnTime(DAY);
                        go->SetLootState(GO_JUST_DEACTIVATED);
                    }

                    events.ScheduleEvent(EVENT_ANZU_5, 2.5s);
                    break;
                }
                case EVENT_ANZU_5:
                {
                    // Summon NPC_ANZU and despawn intro objects
                    if (Creature * creature = instance->GetCreature(_ravenGodTargetGUID))
                        creature->SummonCreature(NPC_ANZU, SummonAnzuPos, TEMPSUMMON_DEAD_DESPAWN, 0);

                    DespawnIntroObjects();
                    break;
                }
                default:
                    break;
                }
            }
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "S H " << AnzuEncounter;

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* strIn)
        {
            if (!strIn)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(strIn);

            char dataHead1, dataHead2;

            std::istringstream loadStream(strIn);
            loadStream >> dataHead1 >> dataHead2;

            if (dataHead1 == 'S' && dataHead2 == 'H')
            {
                loadStream >> AnzuEncounter;
                if (AnzuEncounter == IN_PROGRESS)
                    AnzuEncounter = NOT_STARTED;
            }

            OUT_LOAD_INST_DATA_COMPLETE;
        }

        void DespawnIntroObjects()
        {
            if (GameObject * go = instance->GetGameObject(_ravenClawGUID))
            {
                go->SetRespawnTime(DAY);
                go->SetLootState(GO_JUST_DEACTIVATED);
            }

            if (GameObject * go = instance->GetGameObject(_riftGUID))
            {
                go->SetRespawnTime(DAY);
                go->SetLootState(GO_JUST_DEACTIVATED);
            }

            if (Creature * c = instance->GetCreature(_ravenGodTargetGUID))
                c->DespawnOrUnsummon();

            if (Creature * c = instance->GetCreature(_ravenGodPortalGUID))
            {
                c->RemoveAllAuras();
                c->InterruptNonMeleeSpells(false);
                c->DespawnOrUnsummon();
            }

            for (auto& guid : _ravenGodCasters)
            {
                if (Creature * creature = instance->GetCreature(guid))
                {
                    creature->InterruptNonMeleeSpells(false);
                    creature->DespawnOrUnsummon();
                }
            }
        }

    private:
        uint32 AnzuEncounter;
        uint64 m_uiIkissDoorGUID;
        uint64 _talonKingsCofferGUID;
        uint64 _anzuGUID;
        uint64 _ravenGodTargetGUID;
        uint64 _ravenGodPortalGUID;
        uint64 _ravenClawGUID;
        uint64 _moonstoneGUID;
        uint64 _riftGUID;

        std::vector<uint64> _ravenGodCasters;

        EventMap events;
    };

};

void AddSC_instance_sethekk_halls()
{
    new instance_sethekk_halls();
}
