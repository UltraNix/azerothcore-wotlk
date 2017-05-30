
#include "CreatureGroups.h"
#include "GameObjectAI.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptedEscortAI.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "battle_for_undercity.h"

/*######
## Battle for Undercity
######*/

// Quests: Fate, Up Against Your Will (13369), Herald of War (13257)

enum ThrallBattleForUndercity
{
    QUEST_FATE_UP_AGAINST_YOUR_WILL = 13369,
    QUEST_HERALD_OF_WAR = 13257,

    NPC_THRALL_ALLY = 32363,
    NPC_THRALL_HORDE = 31412,
    NPC_JAINA_ALLY = 32364,
    NPC_JAINA_HORDE = 31418,
    NPC_PORTAL = 31640,
    NPC_GUARD_ALLY = 32367,
    NPC_GUARD_HORDE = 31417,

    GO_PORTAL = 193948,

    AREATRIGGER_ALLY = 5311,

    DATA_IS_ALREADY_BUSY = 0
};

class npc_thrall_pre_battle_undercity : public CreatureScript
{
public:
    npc_thrall_pre_battle_undercity() : CreatureScript("npc_thrall_pre_battle_undercity") { }

    struct npc_thrall_pre_battle_undercityAI : public ScriptedAI
    {
        npc_thrall_pre_battle_undercityAI(Creature* creature) : ScriptedAI(creature)
        {
            JainaEntry = me->GetEntry() == NPC_THRALL_ALLY ? NPC_JAINA_ALLY : NPC_JAINA_HORDE;
            GuardsEntry = me->GetEntry() == NPC_THRALL_ALLY ? NPC_GUARD_ALLY : NPC_GUARD_HORDE;
        }

        bool RunScript;
        uint32 ScriptTimer;
        uint8 ScriptPhase;

        uint64 JainaGUID;
        uint64 PortalGUID;

        std::list<Creature*> GuardList;

        uint32 JainaEntry;
        uint32 GuardsEntry;

        void Reset() override
        {
            RunScript = false;
            ScriptTimer = 3000;
            ScriptPhase = 0;

            JainaGUID = 0;
            PortalGUID = 0;

            GuardList.clear();
        }

        void SetData(uint32 type, uint32 data) override
        {
            switch (data)
            {
            case 1:
                Talk(0);
                ScriptPhase = 1;
                break;
            case 2:
                Talk(7);
                ScriptPhase = 2;
                break;
            case 3:
                RunScript = true;
                me->GetMotionMaster()->MovePoint(1, 1920.57f, -4136.53f, 40.5368f);
                break;
            }
        }

        uint32 GetData(uint32 data) const override
        {
            return uint32(RunScript);
        }

        void MovementInform(uint32 type, uint32 pointId) override
        {
            if (type != POINT_MOTION_TYPE)
                return;

            if (Creature* Jaina = me->FindNearestCreature(JainaEntry, 20.0f))
            {
                JainaGUID = Jaina->GetGUID();
                if (Jaina->AI())
                    Jaina->AI()->SetData(0, 1);
            }

            if (Creature* Portal = me->FindNearestCreature(NPC_PORTAL, 20.0f))
            {
                PortalGUID = Portal->GetGUID();
                if (Portal->AI())
                    Portal->AI()->SetData(0, 1);
            }

            if (GuardList.empty())
                me->GetCreatureListWithEntryInGrid(GuardList, GuardsEntry, 20.0f);
            if (!GuardList.empty())
                for (std::list<Creature*>::iterator itr = GuardList.begin(); itr != GuardList.end(); ++itr)
                    if (Creature* Guard = (*itr))
                        if (Guard->AI())
                            Guard->AI()->SetData(0, 1);

        }

        void UpdateAI(uint32 diff) override
        {
            if (!ScriptPhase)
                return;

            if (ScriptTimer <= diff)
            {
                switch (ScriptPhase)
                {
                case 1:
                    ScriptTimer = 15000;
                    ScriptPhase = 0;

                    Talk(1);

                    if (Creature* Jaina = ObjectAccessor::GetCreature(*me, JainaGUID))
                        if (Jaina->AI())
                            Jaina->AI()->SetData(0, 2);

                    if (!GuardList.empty())
                        for (std::list<Creature*>::iterator itr = GuardList.begin(); itr != GuardList.end(); ++itr)
                            if (Creature* Guard = (*itr))
                                Guard->GetMotionMaster()->MoveTargetedHome();
                    break;
                case 2:
                    EnterEvadeMode();
                    break;
                }
            }
            else
                ScriptTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_thrall_pre_battle_undercityAI(creature);
    }
};

class npc_runthak_pre_battle_undercity : public CreatureScript
{
public:
    npc_runthak_pre_battle_undercity() : CreatureScript("npc_runthak_pre_battle_undercity") { }

    struct npc_runthak_pre_battle_undercityAI : public ScriptedAI
    {
        npc_runthak_pre_battle_undercityAI(Creature* creature) : ScriptedAI(creature)
        {
            MerchantList.clear();
        }

        bool StartScene;
        uint32 SceneTimer;
        uint8 ScenePhase;

        std::list<Unit*> MerchantList;

        void Reset() override
        {
            StartScene = false;
            SceneTimer = 1000;
            ScenePhase = 0;

            if (MerchantList.empty())
                PrepareMerchantsList();
        }

        void MoveInLineOfSight(Unit* who) override
        {
            if (who->GetTypeId() != TYPEID_PLAYER || !me->IsWithinDist(who, 50.0f))
                return;

            if (!StartScene)
                StartScene = true;
        }

        void PrepareMerchantsList()
        {
            Trinity::AnyFriendlyUnitInObjectRangeCheck u_check(me, me, 20.0f);
            Trinity::UnitListSearcher<Trinity::AnyFriendlyUnitInObjectRangeCheck> searcher(me, MerchantList, u_check);
            me->VisitNearbyObject(20.0f, searcher);
        }

        Unit* SelectMerchant()
        {
            Unit* merchant = NULL;

            if (!MerchantList.empty())
                merchant = Trinity::Containers::SelectRandomContainerElement(MerchantList);

            return merchant;
        }

        void JumpToNextPhase(uint32 timer)
        {
            ++ScenePhase;
            SceneTimer = timer;
        }

        void UpdateAI(uint32 diff) override
        {
            if (!StartScene)
                return;

            if (SceneTimer <= diff)
            {
                switch (ScenePhase)
                {
                case 0:
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                    if (Unit* merchant = SelectMerchant())
                        if (merchant->ToCreature() && merchant->ToCreature()->AI())
                            merchant->ToCreature()->AI()->Talk(0);
                    JumpToNextPhase(5000);
                    break;
                case 6:
                    Talk(0);
                    JumpToNextPhase(5000);
                    break;
                case 7:
                    Talk(1);
                    JumpToNextPhase(8000);
                    break;
                case 8:
                    Talk(2);
                    JumpToNextPhase(12000);
                case 9:
                    Talk(3);
                    JumpToNextPhase(20000);
                    break;
                case 10:
                    Reset();
                    break;
                }
            }
            else
                SceneTimer -= diff;
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_runthak_pre_battle_undercityAI(creature);
    }
};

class go_battle_for_undercity_portals : public GameObjectScript
{
public:
    go_battle_for_undercity_portals() : GameObjectScript("go_battle_for_undercity_portals") { }

    struct go_battle_for_undercity_portalsAI : public GameObjectAI
    {
        go_battle_for_undercity_portalsAI(GameObject* gameObject) : GameObjectAI(gameObject)
        {
            go->m_invisibility.AddFlag(INVISIBILITY_UNK7);
            go->m_invisibility.AddValue(INVISIBILITY_UNK7, 1000);
        }
    };

    GameObjectAI* GetAI(GameObject* go) const override
    {
        return new go_battle_for_undercity_portalsAI(go);
    }
};

class AreaTrigger_at_orgrimmar : public AreaTriggerScript
{
public:
    AreaTrigger_at_orgrimmar() : AreaTriggerScript("AreaTrigger_at_orgrimmar") { }

    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger) override
    {
        if (!player || !player->IsAlive())
            return false;

        uint32 QuestId = trigger->id == AREATRIGGER_ALLY ? QUEST_FATE_UP_AGAINST_YOUR_WILL : QUEST_HERALD_OF_WAR;
        uint32 ThrallEntry = trigger->id == AREATRIGGER_ALLY ? NPC_THRALL_ALLY : NPC_THRALL_HORDE;

        if (player->GetQuestStatus(QuestId) == QUEST_STATUS_COMPLETE &&
            player->GetQuestStatus(QuestId) != QUEST_STATUS_REWARDED)
        {
            if (Creature* Thrall = player->FindNearestCreature(ThrallEntry, 20.0f))
                if (Thrall->GetAI() && !Thrall->GetAI()->GetData(DATA_IS_ALREADY_BUSY))
                {
                    Thrall->GetAI()->SetData(DATA_IS_ALREADY_BUSY, 3);
                    return true;
                }
        }

        return false;
    }
};

class spell_portal_to_orgrimmar : public SpellScriptLoader
{
public:
    spell_portal_to_orgrimmar() : SpellScriptLoader("spell_portal_to_orgrimmar") { }

    class spell_portal_to_orgrimmar_SpellScript : public SpellScript
    {
        PrepareSpellScript(spell_portal_to_orgrimmar_SpellScript);

        void HandleSendEvent(SpellEffIndex effIndex)
        {
            PreventHitDefaultEffect(effIndex);

            if (Unit* caster = GetCaster())
                caster->SummonGameObject(GO_PORTAL, -8446.12f, 332.768f, 122.163f, 1.4659f, 0.0f, 0.0f, 0.669065f, 0.743204f, 15);
        }

        void Register() override
        {
            OnEffectHit += SpellEffectFn(spell_portal_to_orgrimmar_SpellScript::HandleSendEvent, EFFECT_0, SPELL_EFFECT_SEND_EVENT);
        }
    };

    SpellScript* GetSpellScript() const override
    {
        return new spell_portal_to_orgrimmar_SpellScript();
    }
};

// Battle_for_the_undercity
enum WaveMobNames
{
    NPC_TREACHEROUS_GUARDIAN,
    NPC_DREADLORD,
    NPC_FELBEAST,
    NPC_MARAUDER,
    NPC_BETRAYER,
    NPC_CHEMIST,
    NPC_COLLABORATOR,
    NPC_DOCTOR
};

uint32 HordeMobs[8] =
{
    NPC_TREACHEROUS_GUARDIAN_H,
    NPC_DREADLORD_H,
    NPC_FELBEAST_H,
    NPC_MARAUDER_H,
    NPC_BETRAYER_H,
    NPC_CHEMIST_H,
    NPC_COLLABORATOR_H,
    NPC_DOCTOR_H
};

class npc_wave_trigger_battle_undercity : public CreatureScript
{
public:
    npc_wave_trigger_battle_undercity() : CreatureScript("npc_wave_trigger_battle_undercity") { }

    struct npc_wave_trigger_battle_undercityAI : public ScriptedAI
    {
        npc_wave_trigger_battle_undercityAI(Creature* creature) : ScriptedAI(creature), _summons(me)
        {
            IsPermament = true;
            SummonerGUID = 0;
            zoneScript = me->GetZoneScript();
        }

        ZoneScript* zoneScript;

        SummonList _summons;

        uint64 SummonerGUID;

        uint32 GetWaveMobEntryByName[8];

        uint32 PhaseTimer;
        uint8 Phase;

        int32 TreachorousCount;
        uint8 PhaseCount;

        bool IsPermament;
        bool DoAttackSummoner;

        void Reset() override
        {
            PhaseTimer = 5000;
            Phase = 0;

            TreachorousCount = 0;
            PhaseCount = 0;

            DoAttackSummoner = true;

            DefineWaves();
        }

        void IsSummonedBy(Unit* summoner) override
        {
            IsPermament = false;

            SummonerGUID = summoner->GetGUID();
        }

        void JustSummoned(Creature* creature) override
        {
            _summons.Summon(creature);
            if (creature->GetEntry() == NPC_DOOMGUARD_PILLARGER)
            {
                creature->SetReactState(REACT_PASSIVE);
                creature->GetMotionMaster()->Clear();
                creature->GetMotionMaster()->MovePath(NPC_DOOMGUARD_PILLARGER * 10, true);
            }
        }

        void SummonedCreatureDies(Creature* creature, Unit* /*killer*/) override
        {
            _summons.Despawn(creature);

            Creature* Summoner = ObjectAccessor::GetCreature(*me, SummonerGUID);
            if (!Summoner || !Summoner->GetAI())
                return;

            switch (creature->GetEntry())
            {
            case NPC_TREACHEROUS_GUARDIAN_A:
            case NPC_TREACHEROUS_GUARDIAN_H:
            {
                ++TreachorousCount;
                if (TreachorousCount >= 30)
                {
                    TreachorousCount = -200;
                    Summoner->GetAI()->SetData(0, 4);
                    return;
                }
                break;
            }
            case NPC_DREADLORD_H:
                Summoner->GetAI()->DoAction(DATA_DREADLORD_COUNT);
                break;
            default:
                break;
            }

            if (_summons.empty())
                if (!IsPermament)
                    if (TreachorousCount >= 10)
                        Summoner->GetAI()->SetData(0, 5);
                    else
                        Summoner->GetAI()->SetData(0, 0);
        }

        void DoAction(int32 /*action*/) override
        {
            _summons.DespawnAll();
        }

        void SetData(uint32 /*type*/, uint32 data) override
        {
            switch (data)
            {
            case 0:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1);
                break;
            case 1:
                SummonMobs(GetWaveMobEntryByName[NPC_DREADLORD], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_BETRAYER], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], 2, 5000);
                Phase = 1;
                break;
            case 2:
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 2);
                break;
            case 3:
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_DREADLORD], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], 2);
                break;
            case 4:
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 2);
                break;
            case 5:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 2);
                break;
            case 6:
                Phase = 2;
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(1, 3), 0, true);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(1, 3), 0, true);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(1, 3), 5000, true);
                IsPermament = true;
                break;
            case 7:
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(1, 3));
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(1, 3));
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(1, 3), 5000);
                Phase = 3;
                IsPermament = true;
                break;
            case 8:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1, 10000);
                Phase = 4;
                IsPermament = true;
                break;
            case 9:
                DoAttackSummoner = false;
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 2, 20000);
                Phase = 7;
                IsPermament = true;
                break;
            case 10:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1, 1000);
                Phase = 8;
                break;
            case 11:
                SummonMobs(GetWaveMobEntryByName[NPC_DREADLORD], 1, 1000);
                Phase = 9;
                break;
            case 12:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 5, 10000);
                Phase = 10;
                IsPermament = true;
                break;
            case 13:
                Phase = 13;
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(1, 3), 0, true);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(1, 3), 0, true);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(1, 3), 5000, true);
                IsPermament = true;
                break;
            case 14:
                Phase = 14;
                SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(1, 3), 0, true);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(1, 3), 0, true);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(1, 3), 5000, true);
                IsPermament = true;
                break;
            case 15:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 2, 5000);
                Phase = 15;
                IsPermament = true;
                break;
            case 16:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_MARAUDER], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_BETRAYER], 1);
                SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], 2, 20000);
                Phase = 16;
                IsPermament = true;
                break;
            case 17:
                SummonMobs(GetWaveMobEntryByName[NPC_MARAUDER], 6);
                SummonMobs(GetWaveMobEntryByName[NPC_BETRAYER], 2);
                IsPermament = true;
                break;
            case 18:
                SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], 4, 20000);
                Phase = 19;
                IsPermament = true;
                break;
            case 19:
                SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1, 20000);
                Phase = 18;
                IsPermament = true;
                break;
            case 20:
            case 21:
            {
                switch (urand(0, 1))
                {
                case 0:
                    SummonMobs(GetWaveMobEntryByName[NPC_DREADLORD], 1, 20000);
                    break;
                case 1:
                {
                    switch (urand(0, 2))
                    {
                    case 0:
                        SummonMobs(GetWaveMobEntryByName[NPC_MARAUDER], urand(1, 3));
                        SummonMobs(GetWaveMobEntryByName[NPC_BETRAYER], urand(1, 3));
                        SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], urand(1, 4), 20000);
                        break;
                    case 1:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], urand(1, 2));
                        SummonMobs(GetWaveMobEntryByName[NPC_BETRAYER], urand(1, 3));
                        SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], urand(1, 3), 20000);
                        break;
                    case 2:
                        SummonMobs(GetWaveMobEntryByName[NPC_BETRAYER], urand(1, 3));
                        SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], urand(1, 3), 20000);
                        break;
                    }
                    break;
                }
                }
                Phase = 21;
                IsPermament = true;
                break;
            }
            case 22:
                DoAttackSummoner = false;
                SummonMobs(NPC_DOOMGUARD_PILLARGER, 1, 10000, false, true);
                Phase = 22;
                IsPermament = true;
                break;
            }
        }

        void DefineWaves()
        {
            bool IsAlly = (me->GetPhaseMask() == 128);
            for (uint8 i = 0; i < 8; ++i)
                GetWaveMobEntryByName[i] = IsAlly ? (NPC_TREACHEROUS_GUARDIAN_A + i) : HordeMobs[i];
        }

        void SummonMobs(uint32 entry, uint8 num, uint32 timer = 0, bool Jump = false, bool forceDespawn = false)
        {
            for (uint8 i = 0; i < num; ++i)
                if (Creature* summon = DoSpawnCreature(entry, 0.0f, 0.0f, 1.0f, 0.0f, (forceDespawn ? TEMPSUMMON_TIMED_DESPAWN : TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT), 60000))
                {
                    Creature* Summoner = ObjectAccessor::GetCreature(*me, SummonerGUID);

                    if (DoAttackSummoner)
                        summon->m_CombatDistance = 100.0f;

                    summon->SetCorpseDelay(10);

                    if (IsPermament && zoneScript)
                    {
                        uint64 targetGUID = zoneScript->GetData64(DATA_GET_ENEMY);
                        if (targetGUID)
                            if (Creature* Target = ObjectAccessor::GetCreature(*me, targetGUID))
                                if (summon->AI() && Target->IsAlive())
                                    summon->AI()->AttackStart(Target);
                    }
                    else if (Summoner && DoAttackSummoner && summon->AI())
                    {
                        if (Jump)
                        {
                            Position pos;
                            float speedXY = 30.0f;
                            float speedZ = 20.0f;
                            switch (Phase)
                            {
                            case 2:
                                summon->SetFacingToObject(Summoner);
                                me->GetNearPosition(pos, 10.0f, me->GetOrientation());
                                speedXY = 10.0f;
                                speedZ = 10.0f;
                                break;
                            case 13:
                                if (urand(0, 1) == 0)
                                    pos.Relocate(1757.23f, 284.50f, 70.40f);
                                else
                                    Jump = false;
                                break;
                            case 14:
                                if (urand(0, 1) == 0)
                                    pos.Relocate(1756.20f, 194.43f, 70.40f);
                                else
                                    Jump = false;
                                break;
                            }

                            if (Jump)
                                summon->GetMotionMaster()->MoveJump(pos, speedXY, speedZ);
                        }

                        summon->AI()->AttackStart(Summoner);
                    }
                }

            if (timer)
                PhaseTimer = timer;
        }

        void UpdateAI(uint32 diff) override
        {
            if (Phase)
            {
                if (PhaseTimer <= diff)
                {
                    switch (Phase)
                    {
                    case 1:
                        if (Creature* Summoner = ObjectAccessor::GetCreature(*me, SummonerGUID))
                            if (Summoner->GetAI())
                                Summoner->GetAI()->SetData(0, 0);
                        Phase = 0;
                        PhaseTimer = 0;
                        IsPermament = false;
                        break;
                    case 2:
                        SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(1, 3), 0, true);
                        SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(1, 3), 0, true);
                        SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(1, 3), 10000, true);
                        break;
                    case 3:
                        SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(1, 3));
                        SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(1, 3));
                        SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(1, 3), 10000);
                        break;
                    case 4:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 2, 10000);
                        Phase = 5;
                        break;
                    case 5:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 3, 10000);
                        Phase = 6;
                        break;
                    case 6:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1, 10000);
                        Phase = 4;
                        break;
                    case 7:
                        SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], 1);
                        SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                        SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 2, 20000);
                        break;
                    case 8:
                        ++PhaseCount;
                        if (PhaseCount >= 10)
                        {
                            PhaseTimer = 0;
                            Phase = 0;
                            IsPermament = false;
                        }
                        else
                            SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1, 1000);
                        break;
                    case 9:
                        ++PhaseCount;
                        if (PhaseCount >= 10)
                        {
                            PhaseTimer = 0;
                            Phase = 0;
                            IsPermament = false;
                        }
                        else
                            SummonMobs(GetWaveMobEntryByName[NPC_DREADLORD], 1, 1000);
                        break;
                    case 10:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 2, 10000);
                        Phase = 11;
                        break;
                    case 11:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 3, 10000);
                        Phase = 12;
                        break;
                    case 12:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1, 10000);
                        Phase = 10;
                        break;
                    case 13:
                        SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(1, 3), 0, true);
                        SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(1, 3), 0, true);
                        SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(1, 3), 5000, true);
                        break;
                    case 14:
                        SummonMobs(GetWaveMobEntryByName[NPC_COLLABORATOR], urand(3, 5), 0, true);
                        SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], urand(3, 5), 0, true);
                        SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], urand(3, 5), 5000, true);
                        break;
                    case 15:
                        SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                        SummonMobs(GetWaveMobEntryByName[NPC_CHEMIST], 1);
                        SummonMobs(GetWaveMobEntryByName[NPC_DOCTOR], 2, 5000);
                        Phase = 0;
                        PhaseTimer = 0;
                        IsPermament = false;
                        break;
                    case 16:
                        SummonMobs(GetWaveMobEntryByName[NPC_MARAUDER], 6, 5000);
                        Phase = 0;
                        PhaseTimer = 0;
                        IsPermament = false;
                        break;
                    case 18:
                        SummonMobs(GetWaveMobEntryByName[NPC_FELBEAST], 6, 20000);
                        Phase = 19;
                        break;
                    case 19:
                        SummonMobs(GetWaveMobEntryByName[NPC_TREACHEROUS_GUARDIAN], 1, 20000);
                        Phase = 18;
                        break;
                    case 21:
                        SetData(0, 21);
                        break;
                    case 22:
                        SummonMobs(NPC_DOOMGUARD_PILLARGER, 1, 10000);
                        break;
                    }
                }
                else
                    PhaseTimer -= diff;
            }
            else if (IsPermament)
            {
                if (PhaseTimer <= diff)
                {
                    SetData(0, urand(1, 4));
                    Phase = 0;
                    PhaseTimer = 120000;
                }
                else
                    PhaseTimer -= diff;
            }
        }
    };

    CreatureAI* GetAI(Creature* creature) const override
    {
        return new npc_wave_trigger_battle_undercityAI(creature);
    }
};

void AddSC_battle_for_undercity()
{
    // pre battle
    new npc_thrall_pre_battle_undercity();
    new npc_runthak_pre_battle_undercity();
    new go_battle_for_undercity_portals();
    new AreaTrigger_at_orgrimmar();
    new spell_portal_to_orgrimmar();

    // battle
    new npc_wave_trigger_battle_undercity();
}
