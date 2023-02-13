//
// Created by user on 12.02.23.
//

#ifndef MCPELAUNCHER_AntiCheat_ITEM_H
#define MCPELAUNCHER_AntiCheat_ITEM_H


#include "../../server/network/packets/ContainerSetSlotPacket.h"
#include "../../server/player/ServerPlayer.h"

namespace AntiCheat {
    class Item {
    public:
        static bool onContainerSetSlotPacket(ServerPlayer *player, ContainerSetSlotPacket &pk);
        static bool checkFromLocalInventory(ServerPlayer *player, ItemInstance& inst);
        static bool checkFromTookDrop(ServerPlayer *player, ItemInstance& inst);
        static bool checkFromOpenContainer(ServerPlayer *player, ItemInstance& inst);

        static inline std::map<std::string, std::vector<ItemInstance>> takeQueue;
        static inline std::mutex mux;
        static void addToTakeQueue(const std::string& name, ItemInstance& item);
    };
}


#endif //MCPELAUNCHER_AntiCheat_ITEM_H
