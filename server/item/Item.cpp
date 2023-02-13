//
// Created by user on 27.01.23.
//

#include <cstring>
#include "Item.h"

#include "../../hybris/include/hybris/dlfcn.h"

void Item::initHooks(void *handle) {
    Item_Items = (Item**) hybris_dlsym(handle, "_ZN4Item6mItemsE"); //256 max
    Item_ctor = (void(*)(Item*, std::string const&, short)) hybris_dlsym(handle, "_ZN4ItemC2ERKSss");
}

void Item::copy(Item *i1, Item *i2) {
    i2 = new Item;
    i2->fullName = i1->fullName;
    i2->id = i1->id;
    memcpy(&i2->filler[0], &i1->filler[0], sizeof(i1->filler));
    memcpy(&i2->filler1[0], &i1->filler1[0], sizeof(i1->filler1));
    i2->name = i1->name;
}

Item::Item(const std::string &name, short id) {
    Item_ctor(this, name, id);
}

