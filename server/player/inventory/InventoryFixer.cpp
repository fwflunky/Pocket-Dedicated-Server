//
// Created by user on 30.01.23.
//

#include <cstring>
#include "InventoryFixer.h"

VirtualInventory* InventoryFixer::createOrGetInventory(const std::string &nick) {
    if(!inventories.contains(nick)){
        auto inv = new VirtualInventory();
        inv->items = {};
        for(int i = 0; i < 54; i++){
            inv->items.emplace_back(0,0,0);
        }
        inventories.insert({nick, inv});
    }
    return inventories.at(nick);
}

std::string InventoryFixer::getFixReason(std::string const& nick, int slot, ItemInstance *item) {
    std::string res;
    auto ti = inventories[nick]->items[slot];
    if(ti.itemOrBlock->id != item->itemOrBlock->id){
        res = "id_mismatch";
    } else if(ti.count != item->count){
        res = "count_mismatch";
    } else if(ti.damageOrAux != item->damageOrAux){
        res = "aux_mismatch";
    }
    return res;
}

void InventoryFixer::copyAllInventory(const std::string &nick, std::vector<ItemInstance *> inv) {
    auto local = inventories[nick]->items;
    for(int i = 0; i < inv.size(); i++){
        inv[i]->damageOrAux = local[i].damageOrAux;
        inv[i]->count = local[i].count;
        if(local[i].itemOrBlock)
            Item::copy(local[i].itemOrBlock, inv[i]->itemOrBlock);
        memcpy(&inv[i]->filler,&local[i].filler, sizeof(local[i].filler));
        memcpy(&inv[i]->filler1,&local[i].filler1, sizeof(local[i].filler1));
    }
}

void InventoryFixer::copySlot(const std::string &nick, int slotid, ItemInstance *slot) {
    auto local = inventories[nick]->items;
    slot->damageOrAux = local[slotid].damageOrAux;
    slot->count = local[slotid].count;
    Item::copy(local[slotid].itemOrBlock, slot->itemOrBlock);
    memcpy(&slot->filler,&local[slotid].filler, sizeof(local[slotid].filler));
    memcpy(&slot->filler1,&local[slotid].filler1, sizeof(local[slotid].filler1));
}

bool InventoryFixer::slotsChanged(const std::string &nick, std::vector<ItemInstance *> inv) {
    auto local = inventories[nick]->items;
    for(int i = 0; i < inv.size(); i++){
        if( inv[i]->damageOrAux != local[i].damageOrAux)
            return true;
        if(inv[i]->count != local[i].count)
            return true;
        if(!inv[i]->itemOrBlock){
            if(local[i].itemOrBlock){
                return true;
            }
        }
    }
    return false;
}
