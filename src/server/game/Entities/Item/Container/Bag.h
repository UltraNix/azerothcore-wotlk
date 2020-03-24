
#ifndef TRINITY_BAG_H
#define TRINITY_BAG_H

// Maximum 36 Slots ((CONTAINER_END - CONTAINER_FIELD_SLOT_1)/2
#define MAX_BAG_SIZE 36                                     // 2.0.12

#include "Item.h"
#include "ItemPrototype.h"

class Bag : public Item
{
    public:

        Bag();
        ~Bag();

        void AddToWorld();
        void RemoveFromWorld();

        bool Create(uint32 guidlow, uint32 itemid, Player const* owner);

        void StoreItem(uint8 slot, ItemRef const& pItem, bool update);
        void RemoveItem(uint8 slot, bool update);

        ItemRef GetItemByPos(uint8 slot) const;
        uint32 GetItemCount(uint32 item, ItemRef const& eItem = NullItemRef ) const;
        uint32 GetItemCountWithLimitCategory(uint32 limitCategory, ItemRef const& skipItem = NullItemRef ) const;

        uint8 GetSlotByItemGUID(uint64 guid) const;
        bool IsEmpty() const;
        uint32 GetFreeSlots() const;
        uint32 GetBagSize() const { return GetUInt32Value(CONTAINER_FIELD_NUM_SLOTS); }

        // DB operations
        // overwrite virtual Item::SaveToDB
        void SaveToDB(SQLTransaction& trans);
        // overwrite virtual Item::LoadFromDB
        bool LoadFromDB(uint32 guid, uint64 owner_guid, Field* fields, uint32 entry);
        // overwrite virtual Item::DeleteFromDB
        void DeleteFromDB(SQLTransaction& trans);

        void BuildCreateUpdateBlockForPlayer(UpdateData* data, Player* target) const;

    protected:

        // Bag Storage space
        Item* m_bagslot[MAX_BAG_SIZE];
};

inline ItemRef NewItemOrBag(ItemTemplate const* proto)
{
    return (proto->InventoryType == INVTYPE_BAG) ? new Bag : new Item;
}
#endif

