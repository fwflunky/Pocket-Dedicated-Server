//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_ITEMINSTANCE_H
#define MCPELAUNCHER_ITEMINSTANCE_H


#include "Item.h"
#include "blockItem/BlockItem.h"

class ItemInstance {
public:
    static void initHooks(void* handle);
    static inline void (*ItemInstance_add)(ItemInstance*, int) = nullptr;
    static inline void (*ItemInstance_remove)(ItemInstance*, int) = nullptr;
    static inline void (*ItemInstance__setItem)(ItemInstance*, int) = nullptr;
    static inline void (*ItemInstance_ctoriii)(ItemInstance*, int, int, int) = nullptr;
    static inline bool (*ItemInstance_operatoreq)(ItemInstance*, ItemInstance const&) = nullptr;

    unsigned char count; //1
    short damageOrAux; //3
    bool someBool1; //7
    char filler[7];
    //void* someVoid2; //11
    Item* itemOrBlock; //15
    char filler1[25];
    //BlockItem* itemOrBlock1; //19

    ItemInstance(int id, int count, int damage);
    bool operator==(ItemInstance const& sec);
    bool equals(ItemInstance const&);
    void add(int c);
    void remove(int c);
    void _setItem(int c);
};


#endif //MCPELAUNCHER_ITEMINSTANCE_H
