//
// Created by user on 16.02.23.
//

#include "Minecraft.h"

ServerNetworkHandler *Minecraft::getServerNetworkHandler() {
    return Minecraft_getServerNetworkHandler(this);
}

Level *Minecraft::getLevel() {
    return Minecraft_getLevel(this);
}

void Minecraft::disconnectClient(const NetworkIdentifier &id, const std::string &res) {
    Minecraft_disconnectClient(this, id, res);
}

void Minecraft::stopGame() {
    Minecraft_stopGame(this);
}
