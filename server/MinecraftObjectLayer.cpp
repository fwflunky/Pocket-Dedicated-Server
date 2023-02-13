//
// Created by user on 31.01.23.
//

#include "MinecraftObjectLayer.h"
#include "../hybris/include/hybris/dlfcn.h"

void MinecraftObjectLayer::initHooks(void *handle) {
    MinecraftObjectLayer_getFeetPos = (Vec3 (*)(Entity&)) hybris_dlsym(handle, "_ZNK20MinecraftObjectLayer10getFeetPosERK6Entity");
}

Vec3 MinecraftObjectLayer::getFeetPos(Entity& e) {
    return MinecraftObjectLayer_getFeetPos(e);
}
