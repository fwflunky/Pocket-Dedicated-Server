//
// Created by user on 28.02.23.
//

#include "Item.h"

dataWrapper::Item::Item(ItemInstance *is) {
    itemInstance = is;
}

int dataWrapper::Item::getCount(const std::string &msg) {
    return itemInstance->count;
}


