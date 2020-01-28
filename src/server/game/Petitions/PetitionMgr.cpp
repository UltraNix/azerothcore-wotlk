/*
Xinef
 */

#include "PetitionMgr.h"

#include "DatabaseEnv.h"
#include "Timer.h"
#include "ObjectDefines.h"
#include "QueryResult.h"

PetitionMgr::PetitionMgr()
{
    m_petitionIds = 0u;
}

PetitionMgr::~PetitionMgr()
{
}

void PetitionMgr::LoadPetitions()
{
    uint32 oldMSTime = getMSTime();
    PetitionStore.clear();

    QueryResult result = CharacterDatabase.Query("SELECT ownerguid, petitionguid, name, type, petitionid FROM petition");
    if (!result)
    {
        sLog->outString(">>  Loaded 0 Petitions!");
        sLog->outString();
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        uint32 petitionId = fields[ 4 ].GetUInt32();
        AddPetition(petitionId, fields[1].GetUInt32(), fields[0].GetUInt32(), fields[2].GetString(), fields[3].GetUInt8());

        m_petitionIds = std::max( m_petitionIds.load(), petitionId );
        ++count;
    } while (result->NextRow());

    m_petitionIds += 1;

    sLog->outString(">> Loaded %d Petitions in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

void PetitionMgr::LoadSignatures()
{
    uint32 oldMSTime = getMSTime();

    QueryResult result = CharacterDatabase.Query("SELECT petitionguid, playerguid, player_account FROM petition_sign");
    if (!result)
    {
        sLog->outString(">>  Loaded 0 Petition signs!");
        sLog->outString();
        return;
    }

    uint32 count = 0;
    do
    {
        Field* fields = result->Fetch();

        auto petition = GetPetitionByItemGuid( fields[ 0 ].GetUInt32() );
        if ( petition != nullptr )
        {
            AddSignature( petition->petitionId, fields[ 2 ].GetUInt32(), fields[ 1 ].GetUInt32() );
        }
        ++count;
    } while (result->NextRow());

    sLog->outString(">> Loaded %d Petition signs in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
    sLog->outString();
}

uint32 PetitionMgr::GeneratePetitionId()
{
    return ++m_petitionIds;
}

void PetitionMgr::AddPetition( uint32 petitionid, uint32 itemGuid, uint32 ownerGuid, std::string const& name, uint8 type)
{
    Petition& p = PetitionStore[ petitionid ];
    p.itemGuid = itemGuid;
    p.ownerGuid = ownerGuid;
    p.petitionName = name;
    p.petitionType = type;
    p.petitionId = petitionid;
}

void PetitionMgr::RemovePetition(uint32 petitionId)
{
    //! Remove all signatures for petition
    for ( auto && p : m_playerToPetition )
    {
        p.second.erase( petitionId );
    }

    PetitionStore.erase(petitionId);
}

void PetitionMgr::RemovePetitionByOwnerAndType(uint32 ownerGuid, uint8 type)
{
    for (PetitionContainer::iterator itr = PetitionStore.begin(); itr != PetitionStore.end();)
    {
        Petition & petition = itr->second;
        if (petition.ownerGuid == ownerGuid && (!type || type == petition.petitionType))
        {
            //! Remove all signatures for petition
            for ( auto && p : m_playerToPetition )
            {
                p.second.erase( petition.petitionId );
            }

            // remove signatures
            itr = PetitionStore.erase(itr);
        }
        else
            ++itr;
    }
}

Petition const* PetitionMgr::GetPetitionById(uint32 petitionId) const
{
    PetitionContainer::const_iterator itr = PetitionStore.find(petitionId);
    if (itr != PetitionStore.end())
        return &itr->second;

    return nullptr;
}

Petition* PetitionMgr::GetPetitionById( uint32 petitionId )
{
    PetitionContainer::iterator itr = PetitionStore.find( petitionId );
    if ( itr != PetitionStore.end() )
        return &itr->second;

    return nullptr;
}

Petition const* PetitionMgr::GetPetitionByItemGuid( uint64 itemGuid ) const
{
    uint32 lowGuid = GUID_LOPART( itemGuid );
    for ( auto && it : PetitionStore )
    {
        Petition const & petition = it.second;
        if ( petition.itemGuid == lowGuid )
            return &petition;
    }

    return nullptr;
}

Petition const* PetitionMgr::GetPetitionByOwnerWithType(uint32 ownerGuid, uint8 type) const
{
    for (PetitionContainer::const_iterator itr = PetitionStore.begin(); itr != PetitionStore.end(); ++itr)
        if (itr->second.ownerGuid == ownerGuid && itr->second.petitionType == type)
            return &itr->second;

    return nullptr;
}

void PetitionMgr::AddSignature(uint32 petitionId, uint32 accountId, uint32 playerGuid)
{
    Petition* petition = GetPetitionById( petitionId );
    if ( petition == nullptr )
        return;

    auto result = petition->signatures.insert( { accountId, playerGuid } );
    if ( result.second )
    {
        m_playerToPetition[ playerGuid ].insert( petitionId );
    }
}

bool PetitionMgr::RemoveSignature( uint32 petitionId, uint32 playerGuid )
{
    Petition* petition = GetPetitionById( petitionId );
    if ( !petition )
        return false;

    bool signatureFound = false;

    m_playerToPetition[ playerGuid ].erase( petitionId );
    for ( auto it = petition->signatures.begin(); it != petition->signatures.end(); )
    {
        const Signature & signature = *it;
        if ( signature.playerGuid == playerGuid )
        {
            m_playerToPetition[ playerGuid ].erase( petitionId );
            it = petition->signatures.erase( it );

            signatureFound = true;
        }
        else
            ++it;
    }

    return signatureFound;
}

void PetitionMgr::RemoveSignaturesByPlayer(uint32 playerGuid)
{
    auto petitions = GetSignedPetitionsForPlayer( playerGuid );
    for ( uint32 petitionId : petitions )
    {
        RemoveSignature( petitionId, playerGuid );
    }
}

void PetitionMgr::RemoveSignaturesByPlayerAndType(uint32 playerGuid, uint8 type)
{
    auto petitions = GetSignedPetitionsForPlayer( playerGuid );
    for ( uint32 petitionId : petitions )
    {
        Petition* petition = GetPetitionById( petitionId );
        if (!petition || petition->petitionType != type )
            continue;

        RemoveSignature( petitionId, playerGuid );
    }
}

PetitionSet PetitionMgr::GetSignedPetitionsForPlayer( uint32 playerGuid ) const
{
    auto it = m_playerToPetition.find( playerGuid );
    if ( it == m_playerToPetition.end() )
        return {};

    return it->second;
}
