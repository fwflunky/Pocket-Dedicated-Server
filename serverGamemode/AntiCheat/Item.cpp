//
// Created by user on 12.02.23.
//

#include "Item.h"
#include "../../server/player/inventory/ContainerManagerModel.h"
#include "../../server/player/inventory/ChestContainerManagerModel.h"
#include "../../server/statics.h"

bool AntiCheat::Item::onContainerSetSlotPacket(ServerPlayer *player, ContainerSetSlotPacket &pk) {
    return true;
    auto setItem = pk.item;
    if(setItem.count == 0){
        return true;
    }
    std::cout << "onContainerSetSlotPacket " << setItem.itemOrBlock->fullName << "\n";
    //todo узнать из контейнера транзакция или в контейнер
    //std::cout << "csp id " << (int) pk.<< "\n";

    if(pk.windowId == 0 || pk.windowId == 122) {
        if (checkFromLocalInventory(player, setItem)) { //test from player inventory
            return true;
        }

        if (checkFromTookDrop(player, setItem)) { //test from drop nearby
            return true;
        }
    }

    if(player->openedContainerManager && ((ContainerManagerModel*) player->openedContainerManager)->id == pk.windowId){
        if(checkFromOpenContainer(player, setItem)) { //test from open container
            return true;
        }
    }


    player->sendMessage("possible inventory hack detected");
    player->sendInventory();
    return false;
}

void AntiCheat::Item::addToTakeQueue(const std::string &name, ItemInstance &item) {
    std::scoped_lock<std::mutex> lock(mux);

    if(!takeQueue.contains(name)){
        takeQueue.insert({name, {}});
    }
    takeQueue.at(name).push_back(item);
}

bool AntiCheat::Item::checkFromLocalInventory(ServerPlayer *player, ItemInstance &setItem) {
    bool got = false;
    for(auto item : player->inventoryProxy->getSlots()) {
        if(item->count == 0)
            continue;
        if(item->damageOrAux == setItem.damageOrAux){
            if(item->itemOrBlock->id == setItem.itemOrBlock->id){
                got = true;
                break;
            }
        }
    }
    return got;
}

bool AntiCheat::Item::checkFromTookDrop(ServerPlayer *player, ItemInstance &setItem) {
    bool got = false;

    std::scoped_lock<std::mutex> lock(mux);
    if(!takeQueue.contains(player->nickname)){
        takeQueue.insert({player->nickname, {}});
    }

    int index = 0;
    for(auto& item : takeQueue.at(player->nickname)){
        if(item.count == setItem.count && item.damageOrAux == setItem.damageOrAux){
            if(item.itemOrBlock->id == setItem.itemOrBlock->id){
                got = true;
                takeQueue.at(player->nickname).erase(takeQueue.at(player->nickname).begin() + index);
                break;
            }
        }
        index++;
    }
    return got;
}

bool AntiCheat::Item::checkFromOpenContainer(ServerPlayer *player, ItemInstance &setItem) {
    bool got = false;
    if(player->openedContainerManager){
        std::cout << " open " << (int) ((ContainerManagerModel *) player->openedContainerManager)->type << "\n";
        switch (((ContainerManagerModel *) player->openedContainerManager)->type) {
            case ContainerTypes::chest: {
                auto chest = (ChestContainerManagerModel *) player->openedContainerManager;
                std::cout << " open chest\n";
                for(auto& item : chest->models["container_items"]->items){
                    if(item.count == 0)
                        continue;
                    if(item.damageOrAux == setItem.damageOrAux) {
                        if(item.itemOrBlock->id == setItem.itemOrBlock->id) {
                            got = true;
                            break;
                        }
                    }
                }
                break;
            }
            default: {
                statics::minecraft->disconnectClient(player->identifier, "unknown container opened with type " + std::to_string(((ContainerManagerModel *) player->openedContainerManager)->type));
            }
        }
    }
    return got;
}
