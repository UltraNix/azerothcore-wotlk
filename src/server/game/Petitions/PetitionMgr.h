/*
Xinef
 */

#ifndef _PETITIONMGR_H
#define _PETITIONMGR_H
#include <map>
#include "LinkedList.h"
#include <ace/Singleton.h>

typedef std::map<uint32, uint32> SignatureMap;

struct Petition
{
    uint32 petitionItemGuid; // actual item, item_instance | inventory
    uint32 petitionGuid; // per charter GUID
    uint32 ownerGuid;
    uint8  petitionType;
    std::string petitionName;
};

struct Signatures
{
    uint32 petitionGuid;
    SignatureMap signatureMap;
};

typedef std::map<uint32, Signatures> SignatureContainer;
typedef std::map<uint32, Petition> PetitionContainer;

class PetitionMgr
{
    friend class ACE_Singleton<PetitionMgr, ACE_Thread_Mutex>;

    private:
        PetitionMgr();
        ~PetitionMgr();

    public:
        void LoadPetitions();
        void LoadSignatures();
        
        // Petitions
        void AddPetition(uint32 petitionId, uint32 ownerGuid, std::string const& name, uint8 type, uint32 petitionGuid);
        void RemovePetition(uint32 petitionId);
        void RemovePetitionByOwnerAndType(uint32 ownerGuid, uint8 type);
        Petition const* GetPetition(uint32 petitionId) const;
        Petition const* GetPetitionByOwnerWithType(uint32 ownerGuid, uint8 type) const;
        Petition const* GetPetitionByGuid(uint32 petitionGUID) const;
        PetitionContainer* GetPetitionStore() { return &PetitionStore; }

        // Signatures
        void AddSignature(uint32 petitionId, uint32 accountId, uint32 playerGuid);
        void RemoveSignaturesByPlayer(uint32 playerGuid);
        void RemoveSignaturesByPlayerAndType(uint32 playerGuid, uint8 type);
        Signatures const* GetSignature(uint32 petitionId) const;
        SignatureContainer* GetSignatureStore() { return &SignatureStore; }

    protected:
        PetitionContainer PetitionStore;
        SignatureContainer SignatureStore;
};

#define sPetitionMgr ACE_Singleton<PetitionMgr, ACE_Thread_Mutex>::instance()
#endif
