//
// Created by user on 28.01.23.
//

#include "PlayerInventoryProxy.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../../src/hook.h"
#include <iostream>

void PlayerInventoryProxy::initHooks(void *handle) {
    PlayerInventoryProxy_add = (void (*)(PlayerInventoryProxy *, ItemInstance&, bool)) hybris_dlsym(handle, "_ZN20PlayerInventoryProxy3addER12ItemInstanceb");
    PlayerInventoryProxy__getCurrentSlotCount = (int (*)(PlayerInventoryProxy *)) hybris_dlsym(handle, "_ZN20PlayerInventoryProxy20_getCurrentSlotCountEv");
    PlayerInventoryProxy_getAndRemoveResource = (bool (*)(PlayerInventoryProxy *, ItemInstance &, bool)) hybris_dlsym(handle, "_ZN20PlayerInventoryProxy20getAndRemoveResourceER12ItemInstanceb");
    PlayerInventoryProxy_getSlots = (std::vector<ItemInstance*> (*)(PlayerInventoryProxy *)) hybris_dlsym(handle, "_ZNK20PlayerInventoryProxy8getSlotsEv");
    PlayerInventoryProxy_getSelectedSlot = (void* (*)(PlayerInventoryProxy *)) hybris_dlsym(handle, "_ZNK20PlayerInventoryProxy15getSelectedSlotEv");
    //PlayerInventoryProxy_removeItem = (void (*)(PlayerInventoryProxy *, int, int, int)) hybris_dlsym(handle, "_ZN20PlayerInventoryProxy10removeItemEii11ContainerID");
    hookFunction((void *) hybris_dlsym(handle, "_ZN20PlayerInventoryProxy10removeItemEii11ContainerID"), (void *) &PlayerInventoryProxy::removeItem, (void **) &PlayerInventoryProxy::PlayerInventoryProxy_removeItem);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20PlayerInventoryProxy12getItemCountEii"), (void *) &PlayerInventoryProxy::getItemCount, (void **) &PlayerInventoryProxy::PlayerInventoryProxy_getItemCount);
}

void PlayerInventoryProxy::add(ItemInstance &i, bool b) {
    PlayerInventoryProxy_add(this, i, b);
}

int PlayerInventoryProxy::_getCurrentSlotCount() {
    return PlayerInventoryProxy__getCurrentSlotCount(this);
}

bool PlayerInventoryProxy::getAndRemoveResource(ItemInstance & i, bool b) {
    return PlayerInventoryProxy_getAndRemoveResource(this, i, b);
}

void PlayerInventoryProxy::removeItem(int a, int b, int c) {
    std::cout << a << " " << b << " " << c << "\n";
    PlayerInventoryProxy_removeItem(this, a, b, c);
}

int PlayerInventoryProxy::getItemCount(int a, int b) {
    //std::cout << "getItemCount " << a << " " << b << "\n";
    return PlayerInventoryProxy_getItemCount(this, a, b);
}

std::vector<ItemInstance*> PlayerInventoryProxy::getSlots() {
    return PlayerInventoryProxy_getSlots(this);
}

void* PlayerInventoryProxy::getSelectedSlot() {
    return PlayerInventoryProxy_getSelectedSlot(this);
}
