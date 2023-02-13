//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_ITEM_H
#define MCPELAUNCHER_ITEM_H

#include <string>

class Item {
public:
    static void initHooks(void* handle);

    static inline Item** Item_Items = nullptr;
    static inline void (*Item_ctor)(Item*, std::string const&, short) = nullptr;
    Item() = default;
    Item(std::string const& name, short id);

    char filler[0x11];
    short id;
    std::string fullName;
    std::string name;
    char filler1[85];

   static void copy(Item* i1, Item* i2);
};


#endif //MCPELAUNCHER_ITEM_H
