//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_PLAYERINVENTORYPROXY_H
#define MCPELAUNCHER_PLAYERINVENTORYPROXY_H


#include <memory>
#include "../../item/ItemInstance.h"

class Inventory;
#include <vector>


class PlayerInventoryProxy {
public:
    static void initHooks(void* handle);
    static inline void (*PlayerInventoryProxy_add)(PlayerInventoryProxy*, ItemInstance&, bool) = nullptr;
    static inline bool (*PlayerInventoryProxy_canAdd)(PlayerInventoryProxy*, const ItemInstance&) = nullptr;
    static inline int (*PlayerInventoryProxy__getCurrentSlotCount)(PlayerInventoryProxy*) = nullptr;
    static inline bool (*PlayerInventoryProxy_getAndRemoveResource)(PlayerInventoryProxy*, ItemInstance&, bool) = nullptr;
    static inline void (*PlayerInventoryProxy_removeItem)(PlayerInventoryProxy*, int, int, int) = nullptr;
    static inline int (*PlayerInventoryProxy_getItemCount)(PlayerInventoryProxy*, int, int) = nullptr;
    static inline std::vector<ItemInstance*> (*PlayerInventoryProxy_getSlots)(PlayerInventoryProxy*) = nullptr;
    static inline void* (*PlayerInventoryProxy_getSelectedSlot)(PlayerInventoryProxy*) = nullptr;

    char filler[7];
    int selectedSlot;
    char filler1[48];
    std::unique_ptr<Inventory> inventory;
    void add(ItemInstance& i, bool b);
    bool canAdd(const ItemInstance& i);
    int _getCurrentSlotCount();
    bool getAndRemoveResource(ItemInstance&, bool);
    void removeItem(int, int, int);
    int getItemCount(int, int);
    std::vector<ItemInstance*> getSlots();
    void* getSelectedSlot();
};


#endif //MCPELAUNCHER_PLAYERINVENTORYPROXY_H
