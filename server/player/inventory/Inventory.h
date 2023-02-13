//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_INVENTORY_H
#define MCPELAUNCHER_INVENTORY_H


#include "../../item/ItemInstance.h"
#include "FillingContainer.h"

class Inventory : public FillingContainer {
public:
    static void initHooks(void* handle);
    static inline void (*Inventory_removeItemInstance)(Inventory*, ItemInstance*) = nullptr;
    static inline std::vector<ItemInstance*> (*Inventory_getComplexItems)(Inventory*) = nullptr;

    void removeItemInstance(ItemInstance*);
    std::vector<ItemInstance*> getComplexItems();
};


#endif //MCPELAUNCHER_INVENTORY_H
