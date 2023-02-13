//
// Created by user on 30.01.23.
//

#ifndef MCPELAUNCHER_INVENTORYFIXER_H
#define MCPELAUNCHER_INVENTORYFIXER_H

#include <vector>
#include <map>
#include "../../item/ItemInstance.h"
class VirtualInventory {
public:
    std::vector<ItemInstance> items;

};
class InventoryFixer {
public:
    static inline std::map<std::string, VirtualInventory*> inventories;
    static VirtualInventory* createOrGetInventory(std::string const& nick);

    static std::string getFixReason(std::string const& nick, int slot, ItemInstance* item);
    static void copyAllInventory(const std::string& nick, std::vector<ItemInstance *> inv);
    static void copySlot(const std::string& nick, int slotid, ItemInstance* slot);
    static bool slotsChanged(const std::string& nick, std::vector<ItemInstance *> inv);
};


#endif //MCPELAUNCHER_INVENTORYFIXER_H
