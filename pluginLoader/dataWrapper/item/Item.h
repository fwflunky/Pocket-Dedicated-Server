//
// Created by user on 28.02.23.
//

#ifndef PDSERVER_DITEM_H
#define PDSERVER_DITEM_H

#include "../../../server/item/ItemInstance.h"

namespace dataWrapper {
    class Item {
    public:
        explicit Item(ItemInstance* is);
        Item() = default;
        ~Item() = default;

        virtual int getCount(const std::string& msg);
    private:
        ItemInstance* itemInstance = nullptr;
    };
}

#endif //PDSERVER_DITEM_H
