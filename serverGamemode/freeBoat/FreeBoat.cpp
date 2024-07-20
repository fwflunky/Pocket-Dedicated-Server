//
// Created by user on 11.02.23.
//

#include "FreeBoat.h"
#include "../customCommands/CustomCommands.h"
#include "../../serverRunner/Loader.h"
#include "spdlog/spdlog.h"
#include "../../server/statics.h"

void FreeBoat::onInit() {
    Loader::registerCallAfterLoad(FreeBoat::load);
}

void FreeBoat::load() {
    CustomCommands::registerCommand("freeboat", [&](ServerPlayer* player, nlohmann::json& input) -> bool {
        clearWaitFor(player->getLowerName());
        if(isWait(player->getLowerName())){
            player->sendMessage("§l§7⋗ §r§cВы уже брали лодку. Повторите попытку позже.");
            return true;
        }
        ItemInstance boat(333, 1, 3);
        if(!player->inventoryProxy->canAdd(boat)){
            player->sendMessage("§l§7⋗ §r§7В инвентаре недостаточно места для добавления лодки.");
            return true;
        }
        addWaitFor(player->getLowerName());
        player->addItem(boat);
        player->sendMessage("§l§7⋗ §r§7Вы получили лодку.");
        return true;
    });
}

void FreeBoat::clearWaitFor(const std::string &ln) {
    if(waits.contains(ln)){
        if(time(nullptr) >= waits.at(ln)){
            waits.erase(ln);
        }
    }
}

void FreeBoat::addWaitFor(const std::string &ln) {
    if(!waits.contains(ln)){
        waits.insert({ln, time(nullptr) + (60 * 30)});
    }
}

bool FreeBoat::isWait(const std::string &ln) {
    return waits.contains(ln);
}