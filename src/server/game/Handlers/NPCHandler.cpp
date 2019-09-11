/*
 * Copyright (C) 
 * Copyright (C) 
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Common.h"
#include "Language.h"
#include "DatabaseEnv.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "Player.h"
#include "GossipDef.h"
#include "UpdateMask.h"
#include "ObjectAccessor.h"
#include "Creature.h"
#include "Pet.h"
#include "ReputationMgr.h"
#include "BattlegroundMgr.h"
#include "Battleground.h"
#include "ScriptMgr.h"
#include "CreatureAI.h"
#include "SpellInfo.h"

#include <utility>
#include <vector>

enum StableResultCode
{
    STABLE_ERR_MONEY        = 0x01,                         // "you don't have enough money"
    STABLE_ERR_STABLE       = 0x06,                         // currently used in most fail cases
    STABLE_SUCCESS_STABLE   = 0x08,                         // stable success
    STABLE_SUCCESS_UNSTABLE = 0x09,                         // unstable/swap success
    STABLE_SUCCESS_BUY_SLOT = 0x0A,                         // buy slot success
    STABLE_ERR_EXOTIC       = 0x0C,                         // "you are unable to control exotic creatures"
};

void WorldSession::HandleTabardVendorActivateOpcode(WorldPacket & recvData)
{
    uint64 guid;
    recvData >> guid;

#ifndef DISABLE_DRESSNPCS_CORESOUNDS
    bool IsAnyTypeCreature = IS_CREATURE_GUID(guid) || IS_PET_GUID(guid) || IS_VEHICLE_GUID(guid);
    if (IsAnyTypeCreature)
        if (Creature* creature = _player->GetMap()->GetCreature(guid))
            creature->SendMirrorSound(_player, 0);
#endif

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_TABARDDESIGNER);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleTabardVendorActivateOpcode - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    SendTabardVendorActivate(guid);
}

void WorldSession::SendTabardVendorActivate(uint64 guid)
{
    WorldPacket data(MSG_TABARDVENDOR_ACTIVATE, 8);
    data << guid;
    SendPacket(&data);
}

void WorldSession::HandleBankerActivateOpcode(WorldPacket & recvData)
{
    uint64 guid;

    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_BANKER_ACTIVATE");

    recvData >> guid;

#ifndef DISABLE_DRESSNPCS_CORESOUNDS
    bool IsAnyTypeCreature = IS_CREATURE_GUID(guid) || IS_PET_GUID(guid) || IS_VEHICLE_GUID(guid);
    if (IsAnyTypeCreature)
        if (Creature* creature = _player->GetMap()->GetCreature(guid))
            creature->SendMirrorSound(_player, 0);
#endif

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_BANKER);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleBankerActivateOpcode - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    SendShowBank(guid);
}

void WorldSession::SendShowBank(uint64 guid)
{
    WorldPacket data(SMSG_SHOW_BANK, 8);
    data << guid;
    m_currentBankerGUID = guid;
    SendPacket(&data);
}

void WorldSession::SendShowMailBox(uint64 guid)
{
    WorldPacket data(SMSG_SHOW_MAILBOX, 8);
    data << guid;
    SendPacket(&data);
}

void WorldSession::HandleTrainerListOpcode(WorldPacket & recvData)
{
    uint64 guid;

    recvData >> guid;

    Creature* npc = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_TRAINER);
    if (!npc)
        return;

#ifndef DISABLE_DRESSNPCS_CORESOUNDS
    npc->SendMirrorSound(_player, 0);
#endif

    SendTrainerList(guid);
}

void WorldSession::SendTrainerList(uint64 guid)
{
    std::string str = GetTrinityString(LANG_NPC_TAINER_HELLO);
    SendTrainerList(guid, str);
}

void WorldSession::SendTrainerList(uint64 guid, const std::string& strTitle)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: SendTrainerList");

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_TRAINER);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: SendTrainerList - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    CreatureTemplate const* ci = unit->GetCreatureTemplate();

    if (!ci)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: SendTrainerList - (GUID: %u) NO CREATUREINFO!", GUID_LOPART(guid));
        return;
    }

    TrainerSpellData const* trainer_spells = unit->GetTrainerSpells();
    if (!trainer_spells)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: SendTrainerList - Training spells not found for creature (GUID: %u Entry: %u)",
            GUID_LOPART(guid), unit->GetEntry());
        return;
    }

    WorldPacket data(SMSG_TRAINER_LIST, 8+4+4+trainer_spells->spellList.size()*38 + strTitle.size()+1);
    data << guid;
    data << uint32(trainer_spells->trainerType);

    size_t count_pos = data.wpos();
    data << uint32(trainer_spells->spellList.size());

    // reputation discount
    float fDiscountMod = _player->GetReputationPriceDiscount(unit);
    bool can_learn_primary_prof = GetPlayer()->GetFreePrimaryProfessionPoints() > 0;

    uint32 count = 0;
    for (TrainerSpellMap::const_iterator itr = trainer_spells->spellList.begin(); itr != trainer_spells->spellList.end(); ++itr)
    {
        TrainerSpell const* tSpell = &itr->second;

        bool valid = true;
        bool primary_prof_first_rank = false;
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            if (!tSpell->learnedSpell[i])
                continue;
            if (!_player->IsSpellFitByClassAndRace(tSpell->learnedSpell[i]))
            {
                valid = false;
                break;
            }
            SpellInfo const* learnedSpellInfo = sSpellMgr->GetSpellInfo(tSpell->learnedSpell[i]);
            if (learnedSpellInfo && learnedSpellInfo->IsPrimaryProfessionFirstRank())
                primary_prof_first_rank = true;
        }
        if (!valid)
            continue;

        TrainerSpellState state = _player->GetTrainerSpellState(tSpell);

        data << uint32(tSpell->spell);                      // learned spell (or cast-spell in profession case)
        data << uint8(state == TRAINER_SPELL_GREEN_DISABLED ? TRAINER_SPELL_GREEN : state);

        if(sWorld->getBoolConfig(CONFIG_PTR_REALM))
            data << uint32(0);
        else
            data << uint32(floor(tSpell->spellCost * fDiscountMod));

        data << uint32(primary_prof_first_rank && can_learn_primary_prof ? 1 : 0);
                                                            // primary prof. learn confirmation dialog
        data << uint32(primary_prof_first_rank ? 1 : 0);    // must be equal prev. field to have learn button in enabled state
        data << uint8(tSpell->reqLevel);
        data << uint32(tSpell->reqSkill);
        data << uint32(tSpell->reqSkillValue);
        //prev + req or req + 0
        uint8 maxReq = 0;
        for (uint8 i = 0; i < MAX_SPELL_EFFECTS; ++i)
        {
            if (!tSpell->learnedSpell[i])
                continue;
            if (uint32 prevSpellId = sSpellMgr->GetPrevSpellInChain(tSpell->learnedSpell[i]))
            {
                data << uint32(prevSpellId);
                ++maxReq;
            }
            if (maxReq == 3)
                break;
            SpellsRequiringSpellMapBounds spellsRequired = sSpellMgr->GetSpellsRequiredForSpellBounds(tSpell->learnedSpell[i]);
            for (SpellsRequiringSpellMap::const_iterator itr2 = spellsRequired.first; itr2 != spellsRequired.second && maxReq < 3; ++itr2)
            {
                data << uint32(itr2->second);
                ++maxReq;
            }
            if (maxReq == 3)
                break;
        }
        while (maxReq < 3)
        {
            data << uint32(0);
            ++maxReq;
        }

        ++count;
    }

    data << strTitle;

    data.put<uint32>(count_pos, count);
    SendPacket(&data);
}

void WorldSession::HandleTrainerBuySpellOpcode(WorldPacket & recvData)
{
    uint64 guid;
    uint32 spellId = 0;

    recvData >> guid >> spellId;
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_TRAINER_BUY_SPELL NpcGUID=%u, learn spell id is: %u", uint32(GUID_LOPART(guid)), spellId);

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_TRAINER);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleTrainerBuySpellOpcode - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    // check present spell in trainer spell list
    TrainerSpellData const* trainer_spells = unit->GetTrainerSpells();
    if (!trainer_spells)
        return;

    // not found, cheat?
    TrainerSpell const* trainer_spell = trainer_spells->Find(spellId);
    if (!trainer_spell)
        return;

    // can't be learn, cheat? Or double learn with lags...
    if (_player->GetTrainerSpellState(trainer_spell) != TRAINER_SPELL_GREEN)
        return;

    // apply reputation discount
    uint32 nSpellCost = uint32(floor(trainer_spell->spellCost * _player->GetReputationPriceDiscount(unit)));

    // check money requirement
    if (!sWorld->getBoolConfig(CONFIG_PTR_REALM) && !_player->HasEnoughMoney(nSpellCost))
        return;

    if(sWorld->getBoolConfig(CONFIG_PTR_REALM))
        _player->ModifyMoney(0);
    else
        _player->ModifyMoney(-int32(nSpellCost));

    unit->SendPlaySpellVisual(179); // 53 SpellCastDirected
    unit->SendPlaySpellImpact(_player->GetGUID(), 362); // 113 EmoteSalute

    // learn explicitly or cast explicitly
    if (trainer_spell->IsCastable())
        _player->CastSpell(_player, trainer_spell->spell, true);
    else
        _player->learnSpell(spellId);

    WorldPacket data(SMSG_TRAINER_BUY_SUCCEEDED, 12);
    data << uint64(guid);
    data << uint32(spellId);                                // should be same as in packet from client
    SendPacket(&data);
}

void WorldSession::HandleGossipHelloOpcode(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Received CMSG_GOSSIP_HELLO");

    uint64 guid;
    recvData >> guid;

    time_t now = time(nullptr);
    tm* aTm = localtime(&now);

#ifndef DISABLE_DRESSNPCS_CORESOUNDS
    bool IsAnyTypeCreature = IS_CREATURE_GUID(guid) || IS_PET_GUID(guid) || IS_VEHICLE_GUID(guid);
    if (IsAnyTypeCreature)
        if (Creature* creature = _player->GetMap()->GetCreature(guid))
            creature->SendMirrorSound(_player, 0);
#endif

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_NONE);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleGossipHelloOpcode - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    /*
    // Prvent WinTrade - Disable Arena Masters between 2:00 AM and 10:00 AM
    if (unit->IsBattleMaster())
    {
        switch (aTm->tm_hour)
        {
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                return;

            default:
                break;
        }

    }
    */
    // xinef: check if we have ANY npc flags
    if (unit->GetUInt32Value(UNIT_NPC_FLAGS) == UNIT_NPC_FLAG_NONE)
        return;

    // xinef: do not allow to open gossip when npc is in combat
    // Piootrek: allow to open gossip when npc is in combat in Karazhan (needed for chess event encounter)
    if (unit->GetUInt32Value(UNIT_NPC_FLAGS) == UNIT_NPC_FLAG_GOSSIP && unit->IsInCombat() && unit->GetMapId() != 532) // should work on all flags?
        return;

    // set faction visible if needed
    if (FactionTemplateEntry const* factionTemplateEntry = sFactionTemplateStore.LookupEntry(unit->getFaction()))
        _player->GetReputationMgr().SetVisible(factionTemplateEntry);

    GetPlayer()->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_TALK);
    // remove fake death
    //if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
    //    GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    // xinef: and if he has pure gossip or is banker and moves or is tabard designer?
    //if (unit->IsArmorer() || unit->IsCivilian() || unit->IsQuestGiver() || unit->IsServiceProvider() || unit->IsGuard())
    {
        //if (!unit->GetTransport()) // pussywizard: reverted with new spline (old: without this check, npc would stay in place and the transport would continue moving, so the npc falls off. NPCs on transports don't have waypoints, so stopmoving is not needed)
            unit->StopMoving();
    }

    // If spiritguide, no need for gossip menu, just put player into resurrect queue
    if (unit->IsSpiritGuide())
    {
        Battleground* bg = _player->GetBattleground();
        if (bg)
        {
            bg->AddPlayerToResurrectQueue(unit->GetGUID(), _player->GetGUID());
            sBattlegroundMgr->SendAreaSpiritHealerQueryOpcode(_player, bg, unit->GetGUID());
            return;
        }
    }

    if (!sScriptMgr->OnGossipHello(_player, unit))
    {
//        _player->TalkedToCreature(unit->GetEntry(), unit->GetGUID());
        _player->PrepareGossipMenu(unit, unit->GetCreatureTemplate()->GossipMenuId, true);
        _player->SendPreparedGossip(unit);
    }
    unit->AI()->sGossipHello(_player);
}

/*void WorldSession::HandleGossipSelectOptionOpcode(WorldPacket & recvData)
{
    ;//sLog->outDebug(LOG_FILTER_PACKETIO, "WORLD: CMSG_GOSSIP_SELECT_OPTION");

    uint32 option;
    uint32 unk;
    uint64 guid;
    std::string code = "";

    recvData >> guid >> unk >> option;

    if (_player->PlayerTalkClass->GossipOptionCoded(option))
    {
        ;//sLog->outDebug(LOG_FILTER_PACKETIO, "reading string");
        recvData >> code;
        ;//sLog->outDebug(LOG_FILTER_PACKETIO, "string read: %s", code.c_str());
    }

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_NONE);
    if (!unit)
    {
        ;//sLog->outDebug(LOG_FILTER_PACKETIO, "WORLD: HandleGossipSelectOptionOpcode - Unit (GUID: %u) not found or you can't interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    if (!code.empty())
    {
        if (!Script->GossipSelectWithCode(_player, unit, _player->PlayerTalkClass->GossipOptionSender (option), _player->PlayerTalkClass->GossipOptionAction(option), code.c_str()))
            unit->OnGossipSelect (_player, option);
    }
    else
    {
        if (!Script->OnGossipSelect (_player, unit, _player->PlayerTalkClass->GossipOptionSender (option), _player->PlayerTalkClass->GossipOptionAction (option)))
           unit->OnGossipSelect (_player, option);
    }
}*/

void WorldSession::HandleSpiritHealerActivateOpcode(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_SPIRIT_HEALER_ACTIVATE");

    uint64 guid;

    recvData >> guid;

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_SPIRITHEALER);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleSpiritHealerActivateOpcode - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(guid)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    SendSpiritResurrect();
}

void WorldSession::SendSpiritResurrect()
{
    _player->ResurrectPlayer(0.5f, true);

    _player->DurabilityLossAll(0.25f, true);

    // get corpse nearest graveyard
    WorldSafeLocsEntry const* corpseGrave = NULL;
    Corpse* corpse = _player->GetCorpse();
    if (corpse)
        corpseGrave = sObjectMgr->GetClosestGraveyard(corpse->GetPositionX(), corpse->GetPositionY(), corpse->GetPositionZ(), corpse->GetMapId(), _player->GetTeamId());

    // now can spawn bones
    _player->SpawnCorpseBones();

    // teleport to nearest from corpse graveyard, if different from nearest to player ghost
    if (corpseGrave)
    {
        WorldSafeLocsEntry const* ghostGrave = sObjectMgr->GetClosestGraveyard(_player->GetPositionX(), _player->GetPositionY(), _player->GetPositionZ(), _player->GetMapId(), _player->GetTeamId());

        if (corpseGrave != ghostGrave)
            _player->TeleportTo(corpseGrave->map_id, corpseGrave->x, corpseGrave->y, corpseGrave->z, _player->GetOrientation());
        // or update at original position
        //else
        //    _player->UpdateObjectVisibility(); // xinef: not needed, called in ResurrectPlayer
    }
    // or update at original position
    //else
    //    _player->UpdateObjectVisibility(); // xinef: not needed, called in ResurrectPlayer
}

void WorldSession::HandleBinderActivateOpcode(WorldPacket & recvData)
{
    uint64 npcGUID;
    recvData >> npcGUID;

    if (!GetPlayer()->IsInWorld() || !GetPlayer()->IsAlive())
        return;

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(npcGUID, UNIT_NPC_FLAG_INNKEEPER);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleBinderActivateOpcode - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(npcGUID)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    SendBindPoint(unit);
}

void WorldSession::SendBindPoint(Creature* npc)
{
    // prevent set homebind to instances in any case
    if (GetPlayer()->GetMap()->Instanceable())
        return;

    uint32 bindspell = 3286;

    // send spell for homebinding (3286)
    npc->CastSpell(_player, bindspell, true);

    WorldPacket data(SMSG_TRAINER_BUY_SUCCEEDED, (8+4));
    data << uint64(npc->GetGUID());
    data << uint32(bindspell);
    SendPacket(&data);

    _player->PlayerTalkClass->SendCloseGossip();
}

void WorldSession::HandleListStabledPetsOpcode(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recv MSG_LIST_STABLED_PETS");
    uint64 npcGUID;

    recvData >> npcGUID;

#ifndef DISABLE_DRESSNPCS_CORESOUNDS
    bool IsAnyTypeCreature = IS_CREATURE_GUID(npcGUID) || IS_PET_GUID(npcGUID) || IS_VEHICLE_GUID(npcGUID);
    if (IsAnyTypeCreature)
        if (Creature* creature = _player->GetMap()->GetCreature(npcGUID))
            creature->SendMirrorSound(_player, 0);
#endif

    if (!CheckStableMaster(npcGUID))
        return;

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    // remove mounts this fix bug where getting pet from stable while mounted deletes pet.
    if (GetPlayer()->IsMounted())
        GetPlayer()->RemoveAurasByType(SPELL_AURA_MOUNTED);

    SendStablePet(npcGUID);
}

void WorldSession::SendStablePet(uint64 guid)
{
    if ( !GetPlayer() )
        return;

    sLog->outDebug( LOG_FILTER_NETWORKIO, "WORLD: Recv MSG_LIST_STABLED_PETS Send." );

    WorldPacket data( MSG_LIST_STABLED_PETS, 200 );           // guess size
    data << uint64( guid );

    size_t wpos = data.wpos();
    data << uint8( 0 );
    data << uint8( GetPlayer()->m_stableSlots );

    uint8 petsCount = 0;       
    
    PetSlotData* current = GetPlayer()->GetPetSlotData(PET_SAVE_AS_CURRENT);
    if ( current == nullptr || current->Type != HUNTER_PET )
    {
        current = GetPlayer()->GetPetSlotData( PET_SAVE_NOT_IN_SLOT );
    }

    if ( current != nullptr && current->Type == HUNTER_PET )
    {
        ++petsCount;

        data << uint32( current->Id );              // petnumber
        data << uint32( current->Entry );           // creature entry
        data << uint32( current->Level );           // level
        data << current->Name;                      // name
        data << uint8( 1 );                         // 1 = current, 2/3 = in stable (any from 4, 5, ... create problems with proper show)
    }

    for ( PetSaveMode slot = PET_SAVE_FIRST_STABLE_SLOT; slot <= PET_SAVE_LAST_STABLE_SLOT; slot = PetSaveMode( slot + 1 ) )
    {
        PetSlotData* petSlot = GetPlayer()->GetPetSlotData( slot );
        if ( petSlot == nullptr || petSlot->Type != HUNTER_PET )
            continue;

        ++petsCount;

        data << uint32( petSlot->Id );              // petnumber
        data << uint32( petSlot->Entry );           // creature entry
        data << uint32( petSlot->Level );           // level
        data << petSlot->Name;                      // name
        data << uint8( 2 );                         // 1 = current, 2/3 = in stable (any from 4, 5, ... create problems with proper show)
    }

    data.put<uint8>( wpos, petsCount );             // set real data to placeholder
    SendPacket( &data );
}

void WorldSession::SendStableResult(uint8 res)
{
    WorldPacket data(SMSG_STABLE_RESULT, 1);
    data << uint8(res);
    SendPacket(&data);
}

void WorldSession::HandleStablePet(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recv CMSG_STABLE_PET");
    uint64 npcGUID;

    recvData >> npcGUID;

    if (!GetPlayer()->IsAlive())
    {
        SendStableResult(STABLE_ERR_STABLE);
        return;
    }

    if (!CheckStableMaster(npcGUID))
    {
        SendStableResult(STABLE_ERR_STABLE);
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    Pet* pet = _player->GetPet();
    if (pet && (pet->getPetType() != HUNTER_PET || !pet->IsAlive()))
    {
        SendStableResult(STABLE_ERR_STABLE);
        return;
    }

    size_t stableSlotIdx = 0u;
    for ( PetSaveMode slot = PET_SAVE_FIRST_STABLE_SLOT; slot <= PET_SAVE_LAST_STABLE_SLOT; slot = PetSaveMode( slot + 1 ) )
    {
        if ( stableSlotIdx++ > GetPlayer()->m_stableSlots )
            break;

        PetSlotData* stableSlot = GetPlayer()->GetPetSlotData( slot, true );
        if ( stableSlot != nullptr && stableSlot->Empty )
        {
            for ( PetSaveMode slot2 : { PET_SAVE_AS_CURRENT, PET_SAVE_NOT_IN_SLOT } )
            {
                if ( PetSlotData* currSlot = GetPlayer()->GetPetSlotData( slot2 ) )
                {
                    if ( currSlot->Type != HUNTER_PET )
                        continue;

                    PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement( CHAR_UDP_CHAR_HUNTER_PET_SLOT_BY_SLOT );
                    stmt->setUInt8( 0, slot );
                    stmt->setUInt32( 1, _player->GetGUIDLow() );
                    stmt->setUInt8( 2, uint8( slot2 ) );

                    CharacterDatabase.Execute( stmt );

                    std::swap( *stableSlot, *currSlot );
                    break;
                }
            }

            if ( Pet* pet = _player->GetPet() )
            {
                _player->RemovePet( pet, slot );
            }

            SendStableResult( STABLE_SUCCESS_STABLE );
            return;
        }
    }

    SendStableResult( STABLE_ERR_STABLE );
}

static void SwapHunterPetsInSlots( Player* owner, uint8 slot1, uint8 slot2 )
{
    SQLTransaction trans = CharacterDatabase.BeginTransaction();

    //! Current pet is offline, we need to swap entries
    // NOT_IN_SLOT -> DELETED
    // SLOT -> NOT_IN_SLOT
    // DELETED -> SLOT

    PetSlotData* slot1Data = owner->GetPetSlotData( PetSaveMode( slot1 ), true );
    PetSlotData* slot2Data = owner->GetPetSlotData( PetSaveMode( slot2 ), true );

    std::swap( *slot1Data, *slot2Data );

    const std::vector< std::pair< uint8, uint8 > > swapOrder =
    {
        { slot1, PET_SAVE_SWAP_TEMP },
        { slot2, slot1 },
        { PET_SAVE_SWAP_TEMP, slot2 }
    };

    for ( auto && it : swapOrder )
    {
        PreparedStatement* stmt = CharacterDatabase.GetPreparedStatement( CHAR_UDP_CHAR_HUNTER_PET_SLOT_BY_SLOT );
        stmt->setUInt8( 0, it.second );
        stmt->setUInt32( 1, owner->GetGUIDLow() );
        stmt->setUInt8( 2, it.first );
        trans->Append( stmt );
    }

    CharacterDatabase.CommitTransaction( trans );
}

void WorldSession::HandleUnstablePet(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recv CMSG_UNSTABLE_PET.");
    uint64 npcGUID;
    uint32 petnumber;

    recvData >> npcGUID >> petnumber;

    if (!CheckStableMaster(npcGUID))
    {
        SendStableResult(STABLE_ERR_STABLE);
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    //! player have saved pet
    if ( _player->GetPetSlotData( PET_SAVE_AS_CURRENT ) || _player->GetPetSlotData( PET_SAVE_NOT_IN_SLOT ) )
    {
        SendStableResult( STABLE_ERR_STABLE );
        return;
    }

    for ( PetSaveMode slot = PET_SAVE_FIRST_STABLE_SLOT; slot <= PET_SAVE_LAST_STABLE_SLOT; slot = PetSaveMode( slot + 1 ) )
    {
        PetSlotData* stableSlot = _player->GetPetSlotData( slot );
        if ( stableSlot != nullptr && stableSlot->Id == petnumber )
        {
            if ( !stableSlot->Entry )
            {
                SendStableResult( STABLE_ERR_STABLE );
                return;
            }

            CreatureTemplate const* creatureInfo = sObjectMgr->GetCreatureTemplate( stableSlot->Entry );
            if ( !creatureInfo || !creatureInfo->IsTameable( _player->CanTameExoticPets() ) )
            {
                // if problem in exotic pet
                if ( creatureInfo && creatureInfo->IsTameable( true ) )
                    SendStableResult( STABLE_ERR_EXOTIC );
                else
                    SendStableResult( STABLE_ERR_STABLE );

                return;
            }

            uint32 petEntry = stableSlot->Entry;
            uint32 petId = stableSlot->Id;

            SwapHunterPetsInSlots( _player, PET_SAVE_AS_CURRENT, slot );

            //! Dead pet saved, move to stable
            PetSlotData* data = _player->GetPetSlotData( PET_SAVE_NOT_IN_SLOT );
            if ( data != nullptr && data->Type == HUNTER_PET )
            {
                SwapHunterPetsInSlots( _player, PET_SAVE_NOT_IN_SLOT, slot );
            }

            if ( !Pet::LoadPetFromDB( _player, PET_LOAD_HANDLE_UNSTABLE_CALLBACK, petEntry, petId ) )
            {
                return SendStableResult( STABLE_ERR_STABLE );
            }

            return;
        }
    }

    SendStableResult( STABLE_ERR_STABLE );
}

void WorldSession::HandleBuyStableSlot(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recv CMSG_BUY_STABLE_SLOT.");
    uint64 npcGUID;

    recvData >> npcGUID;

    if (!CheckStableMaster(npcGUID))
    {
        SendStableResult(STABLE_ERR_STABLE);
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    if (GetPlayer()->m_stableSlots < MAX_PET_STABLES)
    {
        StableSlotPricesEntry const* SlotPrice = sStableSlotPricesStore.LookupEntry(GetPlayer()->m_stableSlots+1);
        if (_player->HasEnoughMoney(SlotPrice->Price))
        {
            ++GetPlayer()->m_stableSlots;
            _player->ModifyMoney(-int32(SlotPrice->Price));
            SendStableResult(STABLE_SUCCESS_BUY_SLOT);
        }
        else
            SendStableResult(STABLE_ERR_MONEY);
    }
    else
        SendStableResult(STABLE_ERR_STABLE);
}

void WorldSession::HandleStableRevivePet(WorldPacket &/* recvData */)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "HandleStableRevivePet: Not implemented");
}

void WorldSession::HandleStableSwapPet(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: Recv CMSG_STABLE_SWAP_PET.");
    uint64 npcGUID;
    uint32 petId;

    recvData >> npcGUID >> petId;

    if (!CheckStableMaster(npcGUID))
    {
        SendStableResult(STABLE_ERR_STABLE);
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    for ( PetSaveMode slot = PET_SAVE_FIRST_STABLE_SLOT; slot <= PET_SAVE_LAST_STABLE_SLOT; slot = PetSaveMode( slot + 1 ) )
    {
        PetSlotData* data = GetPlayer()->GetPetSlotData( slot );
        if ( data && data->Id == petId )
        {
            if ( !data->Entry )
            {
                SendStableResult( STABLE_ERR_STABLE );
                return;
            }

            CreatureTemplate const* creatureInfo = sObjectMgr->GetCreatureTemplate( data->Entry );
            if ( !creatureInfo || !creatureInfo->IsTameable( _player->CanTameExoticPets() ) )
            {
                // if problem in exotic pet
                if ( creatureInfo && creatureInfo->IsTameable( true ) )
                    SendStableResult( STABLE_ERR_EXOTIC );
                else
                    SendStableResult( STABLE_ERR_STABLE );
                return;
            }

            Pet* pet = _player->GetPet();
            if ( pet != nullptr )
            {
                if ( !pet->IsAlive() )
                {
                    SendStableResult( STABLE_ERR_STABLE );
                    return;
                }

                SwapHunterPetsInSlots( _player, PET_SAVE_AS_CURRENT, slot );

                // move alive pet to slot or delete dead pet
                _player->RemovePet( pet, PetSaveMode( slot ) );
            }
            else
            {
                SwapHunterPetsInSlots( _player, PET_SAVE_NOT_IN_SLOT, slot );
            }

            // summon unstabled pet
            if ( !Pet::LoadPetFromDB( _player, PET_LOAD_HANDLE_UNSTABLE_CALLBACK, data->Entry, petId ) )
            {
                SendStableResult( STABLE_ERR_STABLE );
            }
            else
                SendStableResult( STABLE_SUCCESS_UNSTABLE );
        }

    }

    SendStableResult( STABLE_ERR_STABLE );
}

void WorldSession::HandleRepairItemOpcode(WorldPacket & recvData)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_REPAIR_ITEM");

    uint64 npcGUID, itemGUID;
    uint8 guildBank;                                        // new in 2.3.2, bool that means from guild bank money

    recvData >> npcGUID >> itemGUID >> guildBank;

    Creature* unit = GetPlayer()->GetNPCIfCanInteractWith(npcGUID, UNIT_NPC_FLAG_REPAIR);
    if (!unit)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: HandleRepairItemOpcode - Unit (GUID: %u) not found or you can not interact with him.", uint32(GUID_LOPART(npcGUID)));
        return;
    }

    // remove fake death
    if (GetPlayer()->HasUnitState(UNIT_STATE_DIED))
        GetPlayer()->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);

    // reputation discount
    float discountMod = _player->GetReputationPriceDiscount(unit);

    if (itemGUID)
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "ITEM: Repair item, itemGUID = %u, npcGUID = %u", GUID_LOPART(itemGUID), GUID_LOPART(npcGUID));

        ItemRef item = _player->GetItemByGuid(itemGUID);
        if (item)
            _player->DurabilityRepair(item->GetPos(), true, discountMod, guildBank);
    }
    else
    {
        sLog->outDebug(LOG_FILTER_NETWORKIO, "ITEM: Repair all items, npcGUID = %u", GUID_LOPART(npcGUID));
        _player->DurabilityRepairAll(true, discountMod, guildBank);
    }
}

