//
// Created by user on 05.02.23.
//

#include "PlayerCommandOrigin.h"
#include "../../hybris/include/hybris/dlfcn.h"

void *PlayerCommandOrigin::getRequestId() {
    return nullptr;
}

std::string PlayerCommandOrigin::getName() {
    return std::string();
}

BlockPos PlayerCommandOrigin::getBlockPosition() {
    return BlockPos(0, 0, 0);
}

BlockPos PlayerCommandOrigin::getWorldPosition() {
    return BlockPos(0, 0, 0);
}

Level *PlayerCommandOrigin::getLevel() {
    return nullptr;
}

Entity *PlayerCommandOrigin::getEntity() {
    return nullptr;
}

BlockSource *PlayerCommandOrigin::getRegion() {
    return nullptr;
}

unsigned char PlayerCommandOrigin::getPermissionsLevel() {
    return 0;
}

CommandOrigin *PlayerCommandOrigin::clone() {
    return nullptr;
}

int PlayerCommandOrigin::getOriginType() {
    return 0;
}

void *PlayerCommandOrigin::toCommandOriginData() {
    return nullptr;
}

void PlayerCommandOrigin::initHooks(void *handle) {
    PlayerCommandOrigin_ctor = (void (*)(PlayerCommandOrigin*, Player&)) hybris_dlsym(handle, "_ZN19PlayerCommandOriginC2ER6Player");
}

PlayerCommandOrigin::PlayerCommandOrigin(Player &p) {
    PlayerCommandOrigin_ctor(this, p);
}
