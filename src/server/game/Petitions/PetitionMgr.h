/*
Xinef
 */

#ifndef _PETITIONMGR_H
#define _PETITIONMGR_H

#include "LinkedList.h"

#include <ace/Singleton.h>
#include <map>
#include <atomic>
#include <set>
#include <vector>

struct Signature
{
    uint32 accountId;
    uint32 playerGuid;

    // unique per account
    bool operator<( const Signature & rhs ) const
    {
        return accountId < rhs.accountId;
    }
};

using SignaturesSet = std::set< Signature >;

struct Petition
{
    uint32          itemGuid;               // actual item, item_instance | inventory
    uint32          ownerGuid;
    uint8           petitionType;
    std::string     petitionName;
    uint32          petitionId;             // per charter GUID
    SignaturesSet   signatures;
};

using PetitionSet = std::set< uint32 >;

typedef std::unordered_map<uint32, Petition> PetitionContainer;

class PetitionMgr
{
    friend class ACE_Singleton<PetitionMgr, ACE_Thread_Mutex>;

    private:
        PetitionMgr();
        ~PetitionMgr();

    public:
        void LoadPetitions();
        void LoadSignatures();
        
        uint32  GeneratePetitionId();
        // Petitions
        void AddPetition(uint32 petitionid, uint32 itemGuid, uint32 ownerGuid, std::string const& name, uint8 type);

        void RemovePetition(uint32 petitionId);
        void RemovePetitionByOwnerAndType(uint32 ownerGuid, uint8 type);

        Petition const*     GetPetitionById(uint32 petitionId) const;
        Petition*           GetPetitionById(uint32 petitionId);

        Petition const*     GetPetitionByItemGuid(uint64 itemGuid) const;

        Petition const*     GetPetitionByOwnerWithType(uint32 ownerGuid, uint8 type) const;
        PetitionContainer*  GetPetitionStore() { return &PetitionStore; }

        // Signatures
        void                AddSignature(uint32 petitionId, uint32 accountId, uint32 playerGuid);
        bool                RemoveSignature( uint32 petitionId, uint32 playerGuid );

        void                RemoveSignaturesByPlayer(uint32 playerGuid);
        void                RemoveSignaturesByPlayerAndType(uint32 playerGuid, uint8 type);

        PetitionSet         GetSignedPetitionsForPlayer( uint32 playerGuid ) const;

    protected:
        std::atomic<uint32>  m_petitionIds;
        PetitionContainer    PetitionStore;

        std::unordered_map<uint32, PetitionSet> m_playerToPetition;
};

#define sPetitionMgr ACE_Singleton<PetitionMgr, ACE_Thread_Mutex>::instance()
#endif
