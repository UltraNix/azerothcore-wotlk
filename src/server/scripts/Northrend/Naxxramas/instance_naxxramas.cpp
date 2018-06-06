/*
REWRITTEN FROM SCRATCH BY XINEF, IT OWNS NOW!
*/

#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "naxxramas.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "PassiveAI.h"

const float HeiganPos[2] = {2796.0f, -3707.0f};
const float HeiganEruptionSlope[3] =
{
    (-3685.0f - HeiganPos[1]) /(2724.0f - HeiganPos[0]),
    (-3647.0f - HeiganPos[1]) /(2749.0f - HeiganPos[0]),
    (-3637.0f - HeiganPos[1]) /(2771.0f - HeiganPos[0]),
};

inline uint8 GetEruptionSection(float x, float y)
{
    y -= HeiganPos[1];
    if (y < 1.0f)
        return 0;

    x -= HeiganPos[0];
    if (x > -1.0f)
        return 3;

    float slope = y/x;
    for (uint32 i = 0; i < 3; ++i)
        if (slope > HeiganEruptionSlope[i])
            return i;
    return 3;
}

class instance_naxxramas : public InstanceMapScript
{
public:
    instance_naxxramas() : InstanceMapScript("instance_naxxramas", 533) { }

    InstanceScript* GetInstanceScript(InstanceMap* pMap) const
    {
        return new instance_naxxramas_InstanceMapScript(pMap);
    }

    struct instance_naxxramas_InstanceMapScript : public InstanceScript
    {
        instance_naxxramas_InstanceMapScript(Map* pMap) : InstanceScript(pMap)
        {
            memset(&Encounters, 0, sizeof(Encounters));

            for (uint8 i = 0; i < 4; ++i)
                HeiganEruption[i].clear();

            // GOs
            _patchwerkGateGUID     = 0;
            _gluthGateGUID         = 0;
            _nothGateGUID          = 0;
            _heiganGateGUID        = 0;
            _heiganGateExitGUID    = 0;
            _loathebGateGUID       = 0;
            _anubGateGUID          = 0;
            _anubNextGateGUID      = 0;
            _faerlinaGateGUID      = 0;
            _maexxnaGateGUID       = 0;
            _thaddiusGateGUID      = 0;
            _horsemanGateGUID      = 0;
            _kelthuzadfloorGUID    = 0;
            _kelthuzadgateGUID     = 0;
            _sapphironGateGUID     = 0;
            _horsemanPortalGUID    = 0;
            _loathebPortalGUID     = 0;
            _maexxnaPortalGUID     = 0;
            _thaddiusPortalGUID    = 0;
            _horsemanPortalEyeGUID = 0;
            _loathebPortalEyeGUID  = 0;
            _maexxnaPortalEyeGUID  = 0;
            _thaddiusPortalEyeGUID = 0;
            _naxxramasOrbGUID      = 0;
            _mChestGUID            = 0;

            // NPCs
            _thaddiusGUID  = 0;
            _stalaggGUID   = 0;
            _feugenGUID    = 0;
            _zeliekGUID    = 0;
            _rivendareGUID = 0;
            _blaumeuxGUID  = 0;
            _korthazzGUID  = 0;
            _sapphironGUID = 0;
            _kelthuzadGUID = 0;
            _lichkingGUID  = 0;

            // Controls
            _horsemanKilled = 0;
            _speakTimer     = 0;
            _horsemanTimer  = 0;

            // Achievements
            abominationsKilled   = 0;
            faerlinaAchievement  = true;
            thaddiusAchievement  = true;
            loathebAchievement   = true;
            sapphironAchievement = true;
            heiganAchievement    = true;
            sapphironAllowed     = false;
            immortalAchievement  = 1;
            kelthuzadPortals.clear();
        }

        uint32 Encounters[MAX_ENCOUNTERS];
        std::set<GameObject*> HeiganEruption[4];

        // GOs
        uint64 _patchwerkGateGUID;
        uint64 _gluthGateGUID;
        uint64 _nothGateGUID;
        uint64 _heiganGateGUID;
        uint64 _heiganGateExitGUID;
        uint64 _loathebGateGUID;
        uint64 _anubGateGUID;
        uint64 _anubNextGateGUID;
        uint64 _faerlinaGateGUID;
        uint64 _maexxnaGateGUID;
        uint64 _thaddiusGateGUID;
        uint64 _gothikGUID;
        uint64 _gothikEnterGateGUID;
        uint64 _gothikInnerGateGUID;
        uint64 _gothikExitGateGUID;
        uint64 _horsemanGateGUID;
        uint64 _kelthuzadfloorGUID;
        uint64 _kelthuzadgateGUID;
        uint64 _sapphironGateGUID;
        uint64 _horsemanPortalGUID;
        uint64 _loathebPortalGUID;
        uint64 _maexxnaPortalGUID;
        uint64 _thaddiusPortalGUID;
        uint64 _horsemanPortalEyeGUID;
        uint64 _loathebPortalEyeGUID;
        uint64 _maexxnaPortalEyeGUID;
        uint64 _thaddiusPortalEyeGUID;
        uint64 _naxxramasOrbGUID;
        uint64 _nothEntranceGateGUID;
        uint64 _mChestGUID;
        uint64 _goThaddiusEntrance;
        uint64 _goMexannaEntrance;
        uint64 _goHorsemanEntrance;
        uint64 _goLoathebEntrance;
        std::vector<uint64> kelthuzadPortals;

        // NPCs
        uint64 _thaddiusGUID;
        uint64 _stalaggGUID;
        uint64 _feugenGUID;
        uint64 _zeliekGUID;
        uint64 _rivendareGUID;
        uint64 _blaumeuxGUID;
        uint64 _korthazzGUID;
        uint64 _sapphironGUID;
        uint64 _kelthuzadGUID;
        uint64 _lichkingGUID;

        // Controls
        uint8 _horsemanKilled;
        uint32 _speakTimer;
        uint32 _horsemanTimer;

        // Achievements
        uint8 abominationsKilled;
        bool faerlinaAchievement;
        bool thaddiusAchievement;
        bool loathebAchievement;
        bool sapphironAchievement;
        bool heiganAchievement;
        bool sapphironAllowed;

        uint32 immortalAchievement;

        void HeiganEruptSections(uint32 section)
        {
            for (uint8 i = 0; i < 4; ++i)
            {
                if (i == section)
                    continue;

                for (std::set<GameObject*>::iterator itr = HeiganEruption[i].begin(); itr != HeiganEruption[i].end(); ++itr)
                {
                    (*itr)->SendCustomAnim((*itr)->GetGoAnimProgress());
                    (*itr)->CastSpell(NULL, SPELL_ERUPTION);
                }
            }
        }

        bool IsEncounterInProgress() const
        {
            for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
            {
                if (Encounters[i] == IN_PROGRESS)
                    return true;
            }
            return false;
        }

        void OnCreatureCreate(Creature* creature)
        {
            switch(creature->GetEntry())
            {
                case NPC_THADDIUS:
                    _thaddiusGUID = creature->GetGUID();
                    return;
                case NPC_STALAGG:
                    _stalaggGUID = creature->GetGUID();
                    return;
                case NPC_FEUGEN:
                    _feugenGUID = creature->GetGUID();
                    return;
                case NPC_LADY_BLAUMEUX:
                    _blaumeuxGUID = creature->GetGUID();
                    return;
                case NPC_SIR_ZELIEK:
                    _zeliekGUID = creature->GetGUID();
                    return;
                case NPC_BARON_RIVENDARE:
                    _rivendareGUID = creature->GetGUID();
                    return;
                case NPC_THANE_KORTHAZZ:
                    _korthazzGUID = creature->GetGUID();
                    return;
                case NPC_SAPPHIRON:
                    _sapphironGUID = creature->GetGUID();
                    return;
                case NPC_KELTHUZAD:
                    _kelthuzadGUID = creature->GetGUID();
                    return;
                case NPC_LICH_KING:
                    _lichkingGUID = creature->GetGUID();
                    return;
                case NPC_GOTHIK:
                    _gothikGUID = creature->GetGUID();
                    return;
            }
        }

        void OnGameObjectCreate(GameObject* pGo)
        {
            if (pGo->GetGOInfo()->displayId == 6785 || pGo->GetGOInfo()->displayId == 1287)
            {
                HeiganEruption[GetEruptionSection(pGo->GetPositionX(), pGo->GetPositionY())].insert(pGo);
                return;
            }

            switch(pGo->GetEntry())
            {
                case GO_HORSEMEN_CHEST_10:
                case GO_HORSEMEN_CHEST_25:
                    pGo->SetVisible(false);
                    pGo->EnableCollision(false);
                    _mChestGUID = pGo->GetGUID();
                    break;
                case GO_PATCHWERK_GATE:
                    _patchwerkGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_PATCHWERK] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_GLUTH_GATE:
                    _gluthGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_GLUTH] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_NOTH_GATE:
                    _nothGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_NOTH] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_HEIGAN_ENTERANCE_GATE:
                    _heiganGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_HEIGAN] == DONE || Encounters[EVENT_NOTH] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_HEIGAN_EXIT_GATE:
                    _heiganGateExitGUID = pGo->GetGUID();
                    if (Encounters[EVENT_HEIGAN] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_LOATHEB_GATE:
                    _loathebGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_LOATHEB] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_ANUB_GATE:
                    _anubGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_ANUB] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_ANUB_NEXT_GATE:
                    _anubNextGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_ANUB] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_FAERLINA_GATE:
                    _faerlinaGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_FAERLINA] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_MAEXXNA_GATE:
                    _maexxnaGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_FAERLINA] == DONE) // faerlina is correct
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_THADDIUS_GATE:
                    _thaddiusGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_GLUTH] == DONE) // gluth is correct
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_GOTHIK_ENTER_GATE:
                    _gothikEnterGateGUID = pGo->GetGUID();
                    break;
                case GO_GOTHIK_INNER_GATE:
                    _gothikInnerGateGUID = pGo->GetGUID();
                    break;
                case GO_GOTHIK_EXIT_GATE:
                    _gothikExitGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_GOTHIK] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_HORSEMAN_GATE:
                    _horsemanGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_GOTHIK] == DONE) // correct
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_KELTHUZAD_FLOOR:
                    _kelthuzadfloorGUID = pGo->GetGUID();
                    break;
                case GO_KELTHUZAD_GATE:
                    _kelthuzadgateGUID = pGo->GetGUID();
                break;
                case GO_SAPPHIRON_GATE:
                    _sapphironGateGUID = pGo->GetGUID();
                    if (Encounters[EVENT_SAPPHIRON] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_DEATHKNIGHT_WING:
                    _loathebPortalGUID = pGo->GetGUID();
                    if (Encounters[EVENT_LOATHEB] == DONE)
                         pGo->SetPhaseMask(1, true);
                    break;
                case GO_DEATHKNIGHT_WING_EYE:
                    _loathebPortalEyeGUID = pGo->GetGUID();
                    if (Encounters[EVENT_LOATHEB] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_THADDIUS_PORTAL:
                    _thaddiusPortalGUID = pGo->GetGUID();
                    if (Encounters[EVENT_THADDIUS] == DONE)
                        pGo->SetPhaseMask(1, true);
                    break;
                case GO_THADDIUS_PORTAL_EYE:
                    _thaddiusPortalEyeGUID = pGo->GetGUID();
                    if (Encounters[EVENT_THADDIUS] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_MAEXXNA_PORTAL:
                    _maexxnaPortalGUID = pGo->GetGUID();
                    if (Encounters[EVENT_MAEXXNA] == DONE)
                        pGo->SetPhaseMask(1, true);
                    break;
                case GO_MAEXXNA_PORTAL_EYE:
                    _maexxnaPortalEyeGUID = pGo->GetGUID();
                    if (Encounters[EVENT_MAEXXNA] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_HORSEMAN_PORTAL:
                    _horsemanPortalGUID = pGo->GetGUID();
                    if (Encounters[EVENT_HORSEMAN] == DONE)
                        pGo->SetPhaseMask(1, true);
                    break;
                case GO_HORSEMAN_PORTAL_EYE:
                    _horsemanPortalEyeGUID = pGo->GetGUID();
                    if (Encounters[EVENT_HORSEMAN] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    break;
                case GO_NAXXRAMAS_ORB:
                    _naxxramasOrbGUID = pGo->GetGUID();
                    break;
                case GO_NOTH_ENTRANCE_GATE:
                    _nothEntranceGateGUID = pGo->GetGUID();
                    break;
                case GO_THADDIUS_ENTRANCE:
                    if (Encounters[EVENT_THADDIUS] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    _goThaddiusEntrance = pGo->GetGUID();
                    break;
                case GO_MEXANNA_ENTRANCE:
                    if (Encounters[EVENT_MAEXXNA] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    _goMexannaEntrance = pGo->GetGUID();
                    break;
                case GO_HORSEMAN_ENTRANCE:
                    if (Encounters[EVENT_HORSEMAN] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    _goHorsemanEntrance = pGo->GetGUID();
                    break;
                case GO_LOATHEB_ENTRANCE:
                    if (Encounters[EVENT_LOATHEB] == DONE)
                        pGo->SetGoState(GO_STATE_ACTIVE);
                    _goLoathebEntrance = pGo->GetGUID();
                    break;
                case GO_KELTHUZAD_PORTAL_1:
                case GO_KELTHUZAD_PORTAL_2:
                case GO_KELTHUZAD_PORTAL_3:
                case GO_KELTHUZAD_PORTAL_4:
                    kelthuzadPortals.push_back(pGo->GetGUID());
                    break;
            }

        }

        void OnGameObjectRemove(GameObject* pGo)
        {
            if (pGo->GetGOInfo()->displayId == 6785 || pGo->GetGOInfo()->displayId == 1287)
            {
                uint32 section = GetEruptionSection(pGo->GetPositionX(), pGo->GetPositionY());
                HeiganEruption[section].erase(pGo);
                return;
            }

            if (pGo->GetEntry() == GO_SAPPHIRON_BIRTH)
                if (Creature* cr = instance->GetCreature(_sapphironGUID))
                    cr->AI()->DoAction(ACTION_SAPPHIRON_BIRTH);
        }

        bool CheckAchievementCriteriaMeet(uint32 criteria_id, Player const* source, Unit const* target = NULL, uint32 miscvalue1 = 0)
        {
            switch(criteria_id)
            {
                case 7600: // And They Would All Go Down Together (10 player)
                case 7601: // And They Would All Go Down Together (25 player)
                    return (_horsemanTimer < 15*IN_MILLISECONDS);
                case 7614: // Just Can't Get Enough (10 player)
                case 7615: // Just Can't Get Enough (25 player)
                    return abominationsKilled >= 18;
                case 7265: // Momma Said Knock You Out (10 player)
                case 7549: // Momma Said Knock You Out (25 player)
                    return faerlinaAchievement;
                case 7604: // Shocking! (10 player)
                case 7605: // Shocking! (25 player)
                    return thaddiusAchievement;
                case 7612: // Spore Loser (10 player)
                case 7613: // Spore Loser (25 player)
                    return loathebAchievement;
                case 7264: // The Safety Dance (10 player)
                case 7548: // The Safety Dance (25 player)
                    return heiganAchievement;
                case 7608: // Subtraction (10 player)
                // The Dedicated few (10 player)
                case 6802: case 7146: case 7147: case 7148: case 7149:
                case 7150: case 7151: case 7152: case 7153: case 7154:
                case 7155: case 7156: case 7157: case 7158:
                    return (instance->GetPlayersCountExceptGMs() < 9);
                case 7609: // Subtraction (25 player)
                // The Dedicated few (25 player)
                case 7159: case 7160: case 7161: case 7162: case 7163:
                case 7164: case 7165: case 7166: case 7167: case 7168:
                case 7169: case 7170: case 7171: case 7172:
                    return (instance->GetPlayersCountExceptGMs() < 21);
                case 7567: // The Hundred Club (10 player)
                case 7568: // The Hundred Club (25 player)
                    return sapphironAchievement;
                // The Undying
                case 7617: case 13237: case 13238: case 13239: case 13240:
                // The Immortal
                case 7616: case 13233: case 13234: case 13235: case 13236:
                {
                    uint8 count = 0;
                    for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                        if (Encounters[i] == NOT_STARTED)
                            ++count;

                    return !count && immortalAchievement;
                }
            }
            return false;
        }

        void OnUnitDeath(Unit* who) override
        {
            InstanceScript::OnUnitDeath(who);

            //! Immortal/Undying achievement handling
            if (Player* player = who->ToPlayer())
            {
                if (immortalAchievement && IsEncounterInProgress() && player->GetSession()->GetSecurity() == SEC_PLAYER)
                {
                    immortalAchievement = 0;
                    SaveToDB();
                }
            }
        }

        void SetData(uint32 id, uint32 data)
        {
            // Bosses data
            switch(id)
            {
                case EVENT_PATCHWERK:
                case EVENT_GLUTH:
                case EVENT_NOTH:
                case EVENT_ANUB:
                case EVENT_RAZUVIOUS:
                case EVENT_GOTHIK:
                case EVENT_GROBBULUS:
                // EVENT_HORSEMAN HANDLED BELOW
                    Encounters[id] = data;
                    break;
                case EVENT_MAEXXNA:
                    if (data == DONE)
                        if (GameObject* go = instance->GetGameObject(_goMexannaEntrance))
                            go->SetGoState(GO_STATE_ACTIVE);

                    Encounters[id] = data;
                    break;
                case EVENT_KELTHUZAD:
                    if (data == NOT_STARTED)
                        abominationsKilled = 0;
                    Encounters[id] = data;

                    for (auto i : kelthuzadPortals)
                    {
                        if (GameObject* go = instance->GetGameObject(i))
                        {
                            if (data == NOT_STARTED)
                                go->SetGoState(GO_STATE_READY);
                            else if (data == DONE)
                                go->SetGoState(GO_STATE_ACTIVE);
                        }
                    }
                    break;
                case DATA_ACTIVATE_KEL_PORTALS:
                {
                    for (auto i : kelthuzadPortals)
                    {
                        if (GameObject* go = instance->GetGameObject(i))
                            go->SetGoState(GO_STATE_ACTIVE);
                    }
                    break;
                }
                case EVENT_FAERLINA:
                    if (data == NOT_STARTED)
                        faerlinaAchievement = true;
                    Encounters[id] = data;
                    break;
                case EVENT_THADDIUS:
                    if (data == NOT_STARTED)
                    {
                        thaddiusAchievement = true;
                        if (GameObject* go = instance->GetGameObject(_goThaddiusEntrance))
                            go->SetGoState(GO_STATE_READY);
                    }
                    Encounters[id] = data;
                    break;
                case EVENT_LOATHEB:
                    if (data == NOT_STARTED)
                        loathebAchievement = true;

                    if (data == DONE)
                        if (GameObject* go = instance->GetGameObject(_goLoathebEntrance))
                            go->SetGoState(GO_STATE_ACTIVE);

                    Encounters[id] = data;
                    break;
                case EVENT_HEIGAN:
                    if (data == NOT_STARTED)
                        heiganAchievement = true;
                    Encounters[id] = data;
                    break;
                case DATA_HEIGAN_ERUPTION:
                    HeiganEruptSections(data);
                    return;
                case EVENT_SAPPHIRON:
                    Encounters[id] = data;
                    if (data == DONE)
                        _speakTimer = 1;
                    else if (data == NOT_STARTED)
                        sapphironAchievement = true;
                    break;
                case DATA_ABOMINATION_KILLED:
                    abominationsKilled++;
                    return;
                case DATA_FRENZY_REMOVED:
                    faerlinaAchievement = false;
                    return;
                case DATA_CHARGES_CROSSED:
                    thaddiusAchievement = false;
                    return;
                case DATA_SPORE_KILLED:
                    loathebAchievement = false;
                    return;
                case DATA_HUNDRED_CLUB:
                    sapphironAchievement = false;
                    return;
                case DATA_DANCE_FAIL:
                    heiganAchievement = false;
                    return;
                //case DATA_IMMORTAL_FAIL:
                //    immortalAchievement = 0;
                //    SaveToDB();
                //    return;
                case DATA_HORSEMAN_CHEST:
                    if (GameObject* chest = instance->GetGameObject(_mChestGUID))
                    {
                        chest->SetVisible(true);
                        chest->EnableCollision(true);
                    }
                    return;
            }

            // Horseman handling
            if (id == EVENT_HORSEMAN)
            {
                if (data == DONE)
                {
                    _horsemanTimer++;
                    _horsemanKilled++;
                    if (_horsemanKilled < 4)
                        return;

                    // All horsemans are killed
                    if (Creature* cr = instance->GetCreature(_blaumeuxGUID))
                        cr->CastSpell(cr, 59450, true); // credit

                    if (GameObject* go = instance->GetGameObject(_goHorsemanEntrance))
                        go->SetGoState(GO_STATE_ACTIVE);
                }

                // respawn
                else if (data == NOT_STARTED && _horsemanKilled > 0)
                {
                    Creature* cr;
                    _horsemanKilled = 0;
                    if (cr = instance->GetCreature(_blaumeuxGUID))
                        if (!cr->IsAlive())
                        {
                            cr->SetPosition(cr->GetHomePosition());
                            cr->Respawn();
                        }
                    if (cr = instance->GetCreature(_rivendareGUID))
                        if (!cr->IsAlive())
                        {
                            cr->SetPosition(cr->GetHomePosition());
                            cr->Respawn();
                        }
                    if (cr = instance->GetCreature(_zeliekGUID))
                        if (!cr->IsAlive())
                        {
                            cr->SetPosition(cr->GetHomePosition());
                            cr->Respawn();
                        }
                    if (cr = instance->GetCreature(_korthazzGUID))
                        if (!cr->IsAlive())
                        {
                            cr->SetPosition(cr->GetHomePosition());
                            cr->Respawn();
                        }
                }
                else if (data == IN_PROGRESS)
                {
                    Creature* cr;
                    if (cr = instance->GetCreature(_blaumeuxGUID))
                        cr->SetInCombatWithZone();
                    if (cr = instance->GetCreature(_rivendareGUID))
                        cr->SetInCombatWithZone();
                    if (cr = instance->GetCreature(_zeliekGUID))
                        cr->SetInCombatWithZone();
                    if (cr = instance->GetCreature(_korthazzGUID))
                        cr->SetInCombatWithZone();
                }

                if (data == NOT_STARTED)
                    _horsemanTimer = 0;

                Encounters[id] = data;
            }

            // Save instance and open gates
            if (data == DONE)
            {
                SaveToDB();

                switch (id)
                {
                    case EVENT_PATCHWERK:
                        if (GameObject* go = instance->GetGameObject(_patchwerkGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_GLUTH:
                        if (GameObject* go = instance->GetGameObject(_gluthGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_thaddiusGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_goThaddiusEntrance))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_NOTH:
                        if (GameObject* go = instance->GetGameObject(_nothGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_heiganGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_HEIGAN:
                        if (GameObject* go = instance->GetGameObject(_heiganGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_heiganGateExitGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_LOATHEB:
                        if (GameObject* go = instance->GetGameObject(_loathebGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_loathebPortalGUID))
                            go->SetPhaseMask(1, true);
                        if (GameObject* go = instance->GetGameObject(_loathebPortalEyeGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_ANUB:
                        if (GameObject* go = instance->GetGameObject(_anubGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_anubNextGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_FAERLINA:
                        if (GameObject* go = instance->GetGameObject(_faerlinaGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_maexxnaGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_MAEXXNA:
                        if (GameObject* go = instance->GetGameObject(_maexxnaGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_maexxnaPortalGUID))
                            go->SetPhaseMask(1, true);
                        if (GameObject* go = instance->GetGameObject(_maexxnaPortalEyeGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_GOTHIK:
                        if (GameObject* go = instance->GetGameObject(_gothikEnterGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_gothikExitGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_horsemanGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_SAPPHIRON:
                        if (GameObject* go = instance->GetGameObject(_sapphironGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_THADDIUS:
                        if (GameObject* go = instance->GetGameObject(_thaddiusPortalGUID))
                            go->SetPhaseMask(1, true);
                        if (GameObject* go = instance->GetGameObject(_thaddiusPortalEyeGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_thaddiusGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_goThaddiusEntrance))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_HORSEMAN:
                        if (GameObject* go = instance->GetGameObject(_horsemanPortalGUID))
                            go->SetPhaseMask(1, true);
                        if (GameObject* go = instance->GetGameObject(_horsemanPortalEyeGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        if (GameObject* go = instance->GetGameObject(_horsemanGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                    case EVENT_GROBBULUS:
                        if (GameObject* go = instance->GetGameObject(_patchwerkGateGUID))
                            go->SetGoState(GO_STATE_ACTIVE);
                        break;
                }
            }
        }

        uint32 GetData(uint32 identifier) const
        {
            return Encounters[identifier];
        }

        void Update(uint32 diff)
        {
            if (_speakTimer)
            {
                Creature* kel = instance->GetCreature(_kelthuzadGUID);
                Creature* lich = instance->GetCreature(_lichkingGUID);
                if (kel && lich)
                    _speakTimer += diff;
                else
                    return;
                if (_speakTimer > 8000 && _speakTimer < 18000)
                {
                    kel->AI()->Talk(SAY_SAPP_DIALOG1);
                    _speakTimer = 18000;
                }
                else if (_speakTimer > 33000 && _speakTimer < 38000)
                {
                    lich->AI()->Talk(SAY_SAPP_DIALOG2_LICH);
                    _speakTimer = 38000;
                }
                else if (_speakTimer > 46000 && _speakTimer < 58000)
                {
                    kel->AI()->Talk(SAY_SAPP_DIALOG3);
                    _speakTimer = 58000;
                }
                else if (_speakTimer > 66000 && _speakTimer < 78000)
                {
                    lich->AI()->Talk(SAY_SAPP_DIALOG4_LICH);
                    _speakTimer = 78000;
                }
                else if (_speakTimer > 86000)
                {
                    kel->AI()->Talk(SAY_SAPP_DIALOG5);
                    _speakTimer = 0;
                }
            }

            // And They would all
            if (_horsemanTimer)
                _horsemanTimer += diff;
        }

        uint64 GetData64(uint32 id) const
        {
            switch (id)
            {
                // GameObjects
                case DATA_HEIGAN_ENTER_GATE:
                    return _heiganGateGUID;
                case DATA_LOATHEB_GATE:
                    return _loathebGateGUID;
                case DATA_ANUB_GATE:
                    return _anubGateGUID;
                case DATA_MAEXXNA_GATE:
                    return _maexxnaGateGUID;
                case DATA_GOTHIK_ENTER_GATE:
                    return _gothikEnterGateGUID;
                case DATA_GOTHIK_INNER_GATE:
                    return _gothikInnerGateGUID;
                case DATA_GOTHIK_EXIT_GATE:
                    return _gothikExitGateGUID;
                case DATA_KELTHUZAD_FLOOR:
                    return _kelthuzadfloorGUID;
                case DATA_KELTHUZAD_GATE:
                    return _kelthuzadgateGUID;
                case DATA_NOTH_ENTRANCE_GATE:
                    return _nothEntranceGateGUID;
                case DATA_HORSEMAN_GATE:
                    return _horsemanGateGUID;
                case DATA_THADDIUS_GATE:
                    return _thaddiusGateGUID;
                case DATA_PATCHWERK_GATE:
                    return _patchwerkGateGUID;

                // NPCs
                case DATA_THADDIUS_BOSS:
                    return _thaddiusGUID;
                case DATA_STALAGG_BOSS:
                    return _stalaggGUID;
                case DATA_FEUGEN_BOSS:
                    return _feugenGUID;
                case DATA_LICH_KING_BOSS:
                    return _lichkingGUID;
                case DATA_GOTHIK:
                    return _gothikGUID;
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "N X X " << Encounters[0] << ' ' << Encounters[1] << ' ' << Encounters[2] << ' ' << Encounters[3]
                 << ' ' << Encounters[4] << ' ' << Encounters[5] << ' ' << Encounters[6] << ' ' << Encounters[7]
                 << ' ' << Encounters[8] << ' ' << Encounters[9] << ' ' << Encounters[10] << ' ' << Encounters[11]
                 << ' ' << Encounters[12] << ' ' << Encounters[13] << ' ' << Encounters[14] << ' ' << immortalAchievement;

            OUT_SAVE_INST_DATA_COMPLETE;
            return saveStream.str();
        }

        void Load(const char* in)
        {
            if (!in)
            {
                OUT_LOAD_INST_DATA_FAIL;
                return;
            }

            OUT_LOAD_INST_DATA(in);

            char dataHead1, dataHead2, dataHead3;
            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> dataHead3;

            if (dataHead1 == 'N' && dataHead2 == 'X' && dataHead3 == 'X')
            {
                for (uint8 i = 0; i < MAX_ENCOUNTERS; ++i)
                {
                    loadStream >> Encounters[i];
                    if (Encounters[i] == IN_PROGRESS)
                        Encounters[i] = NOT_STARTED;
                }
                loadStream >> immortalAchievement;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
            else
                OUT_LOAD_INST_DATA_FAIL;
        }

    };
};
class boss_naxxramas_misc : public CreatureScript
{
public:
    boss_naxxramas_misc() : CreatureScript("boss_naxxramas_misc") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_naxxramas_miscAI (pCreature);
    }

    struct boss_naxxramas_miscAI : public NullCreatureAI
    {
        boss_naxxramas_miscAI(Creature* c) : NullCreatureAI(c)
        {
            timer = 0;
        }

        uint32 timer;

        void JustDied(Unit* )
        {
            if (me->GetEntry() == NPC_MR_BIGGLESWORTH && me->GetInstanceScript())
            {
                if (Creature* cr = me->SummonCreature(20350/*NPC_KELTHUZAD*/, *me, TEMPSUMMON_TIMED_DESPAWN, 1))
                {
                    cr->SetDisplayId(11686);
                    cr->AI()->Talk(SAY_CAT_DIED);
                }
            }
        }

        void UpdateAI(uint32 diff)
        {
            if (me->GetEntry() == NPC_NAXXRAMAS_TRIGGER)
            {
                timer += diff;
                if (timer >= 5000)
                {
                    if (Creature* cr = me->SummonCreature(NPC_LIVING_POISON, *me, TEMPSUMMON_TIMED_DESPAWN, 14000))
                    {
                        cr->AddUnitMovementFlag(MOVEMENTFLAG_WALKING);
                        cr->GetMotionMaster()->MovePoint(0, me->GetPositionX()+50*cos(me->GetOrientation()), me->GetPositionY()+50*sin(me->GetOrientation()), me->GetPositionZ(), false);
                    }
                    timer = 0;
                }
            }
            else if (me->GetEntry() == NPC_LIVING_POISON)
            {
                Unit* target = NULL;
                Trinity::AnyUnfriendlyUnitInObjectRangeCheck u_check(me, me, 0.5f);
                Trinity::UnitLastSearcher<Trinity::AnyUnfriendlyUnitInObjectRangeCheck> searcher(me, target, u_check);
                me->VisitNearbyObject(1.5f, searcher);
                if (target)
                    me->CastSpell(me, SPELL_FROGGER_EXPLODE, true);
            }
        }
    };
};

enum StoneskinGargoyle
{
    SPELL_ACID_VOLLEY_10 = 29325,
    SPELL_ACID_VOLLEY_25 = 54714,
    SPELL_STONESKIN_10   = 28995,
    SPELL_STONESKIN_25   = 54722,

    EVENT_ACID_VOLLEY    = 1,
    EVENT_STONESKIN,

    ACTION_RESET_STONESKIN = 1
};

struct npc_stoneskin_gargoyleAI : public ScriptedAI
{
    npc_stoneskin_gargoyleAI(Creature* creature) : ScriptedAI(creature) { }

    void Reset() override
    {
        _canUseStoneskin = false;
        _events.Reset();
    }

    void EnterCombat(Unit* /*attacker*/) override
    {
        _events.ScheduleEvent(EVENT_ACID_VOLLEY, 1s);
    }

    void DoAction(int32 actionId) override
    {
        if (actionId == ACTION_RESET_STONESKIN)
            _canUseStoneskin = false;
    }

    void DamageTaken(Unit* /*attacker*/, uint32 &damage, DamageEffectType /*damageType*/, SpellSchoolMask /*schoolMask*/) override
    {
        if (!_canUseStoneskin && me->HealthBelowPctDamaged(30, damage))
        {
            _canUseStoneskin = true;
            _events.ScheduleEvent(EVENT_STONESKIN, 0s);
        }
    }

    void UpdateAI(uint32 diff) override
    {
        if (!UpdateVictim())
            return;

        _events.Update(diff);

        if (me->HasAura(RAID_MODE(SPELL_STONESKIN_10, SPELL_STONESKIN_25)))
            return;

        if (me->HasUnitState(UNIT_STATE_CASTING))
            return;

        while (uint32 eventId = _events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ACID_VOLLEY:
                    DoCastSelf(RAID_MODE(SPELL_ACID_VOLLEY_10, SPELL_ACID_VOLLEY_25));
                    _events.Repeat(10s, 15s);
                    break;
                case EVENT_STONESKIN:
                    DoCastSelf(RAID_MODE(SPELL_STONESKIN_10, SPELL_STONESKIN_25));
                    break;
                default:
                    break;
            }

            if (me->HasUnitState(UNIT_STATE_CASTING))
                return;
        }

        DoMeleeAttackIfReady();
    }


    private:
        EventMap _events;
        bool _canUseStoneskin;
};

class spell_gargoyle_stoneskin_AuraScript : public AuraScript
{
    PrepareAuraScript(spell_gargoyle_stoneskin_AuraScript);

    void OnApply(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
        {
            if (Creature* caster = GetCaster()->ToCreature())
            {
                caster->SetControlled(true, UNIT_STATE_ROOT);
                caster->SetReactState(REACT_PASSIVE);
                caster->SetByteValue(UNIT_FIELD_BYTES_1, 0, 9);
            }
        }
    }

    void OnRemove(AuraEffect const* /*aurEff*/, AuraEffectHandleModes /*mode*/)
    {
        if (GetCaster())
        {
            if (Creature* caster = GetCaster()->ToCreature())
            {
                if (GetTargetApplication()->GetRemoveMode() == AURA_REMOVE_BY_EXPIRE)
                    if (caster->IsAIEnabled)
                        caster->AI()->DoAction(ACTION_RESET_STONESKIN);

                caster->SetControlled(false, UNIT_STATE_ROOT);
                caster->SetReactState(REACT_AGGRESSIVE);
                caster->SetByteValue(UNIT_FIELD_BYTES_1, 0, 0);
            }
        }
    }

    void Register() override
    {
        OnEffectApply += AuraEffectApplyFn(spell_gargoyle_stoneskin_AuraScript::OnApply, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
        OnEffectRemove += AuraEffectRemoveFn(spell_gargoyle_stoneskin_AuraScript::OnRemove, EFFECT_0, SPELL_AURA_PERIODIC_HEAL, AURA_EFFECT_HANDLE_REAL);
    }
};

class go_sapphiron_teleport_downstairs : public GameObjectScript
{
public:
    go_sapphiron_teleport_downstairs() : GameObjectScript("go_sapphiron_teleport_downstairs") { }

    bool OnGossipHello(Player* player, GameObject* /*go*/) override
    {
        // debug handling if player has GM on turned on, would be great if we had proper bossAI scripts
        // so i could implement a command to get boss states via that but well, we do not
        // if by any chance we do get them for naxx bosses in the future we can drop this entire code
        std::ostringstream stream;

        InstanceScript* instance = player->GetInstanceScript();

        if (!instance)
            return false;

        if (!sWorld->getBoolConfig(CONFIG_BOOST_NAXXRAMAS))
        {
            player->CastSpell(player, 72617, true);
            return false;
        }

        //! We're allowing to enter sapphiron (10) without killing entire instance now
        //! if we want to disable it in the future for whatever reason, just delete those two lines
        if (!player->GetMap()->Is25ManRaid())
        {
            player->CastSpell(player, 72617, true);
            return true;
        }

        uint8 bossCount = 0;
        for (uint8 i = 0; i < MAX_ENCOUNTERS - 2; ++i)
        {
            if (instance->GetData(i) == DONE)
            {
                if (++bossCount >= 13)
                {
                    player->CastSpell(player, 72617, true);
                    return true;
                }
            }
            stream << "Encounter number: " << std::to_string(i) << " state: " << std::to_string(instance->GetData(i)) << "\n";
        }
        stream << "State definition: 0 = not started, 1 = in progress, 3 = done, all bosses have to be set to 3 in order for teleport to work\n";
        stream << "Encounter number definition has been posted on IRC and pinned to the channel (GENERAL EN)\n";
        if (player->IsGameMaster())
            ChatHandler(player->GetSession()).PSendSysMessage(stream.str().c_str());
        return true;
    }
};

void AddSC_instance_naxxramas()
{
    new instance_naxxramas();
    new boss_naxxramas_misc();
    new CreatureAILoader<npc_stoneskin_gargoyleAI>("npc_stoneskin_gargoyle");
    new AuraScriptLoaderEx<spell_gargoyle_stoneskin_AuraScript>("spell_gargoyle_stoneskin");
    new go_sapphiron_teleport_downstairs();
}
