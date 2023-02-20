//
// Created by user on 27.01.23.
//

#include "ItemInstance.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"

void ItemInstance::initHooks(void *handle) {
    ItemInstance_add = (void (*)(ItemInstance *, int)) hybris_dlsym(handle, "_ZN12ItemInstance3addEi");
    ItemInstance__setItem = (void (*)(ItemInstance *, int)) hybris_dlsym(handle, "_ZN12ItemInstance8_setItemEi");
    ItemInstance_remove = (void (*)(ItemInstance *, int)) hybris_dlsym(handle, "_ZN12ItemInstance6removeEi");
    ItemInstance_ctoriii = (void (*)(ItemInstance *, int, int, int)) hybris_dlsym(handle, "_ZN12ItemInstanceC2Eiii");
    ItemInstance_operatoreq = (bool (*)(ItemInstance *, ItemInstance const&)) hybris_dlsym(handle, "_ZNK12ItemInstanceeqERKS_");
}

void ItemInstance::add(int c) {
    ItemInstance_add(this, c);
}

void ItemInstance::remove(int c) {
    ItemInstance_remove(this, c);
}

void ItemInstance::_setItem(int c) {
    ItemInstance__setItem(this, c);
}


ItemInstance::ItemInstance(int id, int count, int damage) {
    ItemInstance_ctoriii(this, id, count, damage);
}

bool ItemInstance::operator==(const ItemInstance &sec) {
    return ItemInstance_operatoreq(this, sec);
}

bool ItemInstance::equals(const ItemInstance &i) {
    return ItemInstance_operatoreq(this, i);
}
