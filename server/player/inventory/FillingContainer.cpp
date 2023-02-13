//
// Created by user on 28.01.23.
//

#include "FillingContainer.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void FillingContainer::initHooks(void *handle) {
    FillingContainer_removeItem = (void (*)(FillingContainer *, int, int)) hybris_dlsym(handle, "_ZN16FillingContainer10removeItemEii");
    FillingContainer_add = (bool (*)(FillingContainer *, ItemInstance&, bool)) hybris_dlsym(handle, "_ZN16FillingContainer3addER12ItemInstanceb");
    FillingContainer_canAdd = (bool (*)(FillingContainer *, ItemInstance const&)) hybris_dlsym(handle, "_ZNK16FillingContainer6canAddERK12ItemInstance");
    FillingContainer_clearInventory = (void (*)(FillingContainer *, int)) hybris_dlsym(handle, "_ZN16FillingContainer14clearInventoryEi");
}

void FillingContainer::removeItem(int a, int b) {
    FillingContainer_removeItem(this, a, b);
}

void FillingContainer::clearInventory(int a) {
    FillingContainer_clearInventory(this, a);
}

bool FillingContainer::add(ItemInstance &i, bool b) {
    return FillingContainer_add(this, i, b);
}

bool FillingContainer::canAdd(ItemInstance const&i) {
    return FillingContainer_canAdd(this, i);
}
