//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_FLINTANDSTEELITEM_H
#define MCPELAUNCHER_FLINTANDSTEELITEM_H
#include "Item.h"
#include <iostream>
#include "../entity/Entity.h"
#include "../level/BlockPos.h"
#include "ItemInstance.h"
#include "../../hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
class FlintAndSteelItem : Item {
public:
    static void initHooks(void* handle) {
        hookFunction((void *) hybris_dlsym(handle, "_ZNK17FlintAndSteelItem6_useOnER12ItemInstanceR6Entity8BlockPosafff"), (void *) &FlintAndSteelItem::_useOn, (void **) &FlintAndSteelItem::FlintAndSteelItem__useOn);
    }

    static inline bool (*FlintAndSteelItem__useOn)(FlintAndSteelItem*, ItemInstance&, Entity&, BlockPos, char, float, float , float) = nullptr;

    bool _useOn(ItemInstance& i, Entity& e, BlockPos p, char c, float f, float ff , float fff) {
        std::cout << "FlintAndSteelItem use\n";
        return FlintAndSteelItem__useOn(this, i, e, p, c, f, ff, fff);
    }
};
#endif //MCPELAUNCHER_FLINTANDSTEELITEM_H
