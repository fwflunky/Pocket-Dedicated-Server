//
// Created by user on 28.01.23.
//

#include "Inventory.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void Inventory::initHooks(void *handle) {
    Inventory_removeItemInstance = (void (*)(Inventory*, ItemInstance*)) hybris_dlsym(handle, "_ZN9Inventory18removeItemInstanceEPK12ItemInstance");
    Inventory_getComplexItems = (std::vector<ItemInstance*> (*)(Inventory*)) hybris_dlsym(handle, "_ZN9Inventory15getComplexItemsEv");
}

void Inventory::removeItemInstance(ItemInstance * i) {
    Inventory_removeItemInstance(this, i);
}

std::vector<ItemInstance*> Inventory::getComplexItems() {
    return Inventory_getComplexItems(this);
}
