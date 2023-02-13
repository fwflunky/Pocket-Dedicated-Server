//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_FILLINGCONTAINER_H
#define MCPELAUNCHER_FILLINGCONTAINER_H

#include <vector>
#include "../../item/ItemInstance.h"
#include "Container.h"

class FillingContainer : public Container {
public:
    static void initHooks(void* handle);
    static inline void (*FillingContainer_removeItem)(FillingContainer*, int, int) = nullptr;
    static inline bool (*FillingContainer_add)(FillingContainer*, ItemInstance&, bool) = nullptr;
    static inline bool (*FillingContainer_canAdd)(FillingContainer*, ItemInstance const&) = nullptr;
    static inline void (*FillingContainer_clearInventory)(FillingContainer*, int) = nullptr;

    char filler[18];
    std::vector<ItemInstance> items;

    void removeItem(int a, int b);
    void clearInventory(int a);
    bool add(ItemInstance& i, bool b);
    bool canAdd(ItemInstance const& i);
};


#endif //MCPELAUNCHER_FILLINGCONTAINER_H
