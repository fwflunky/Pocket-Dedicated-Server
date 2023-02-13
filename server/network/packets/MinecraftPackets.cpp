//
// Created by user on 29.01.23.
//

#include "MinecraftPackets.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void MinecraftPackets::initHooks(void *handle) {
    MinecraftPackets_createPacket = (void* (*)(MinecraftPackets*, int)) hybris_dlsym(handle, "_ZN16MinecraftPackets12createPacketEi");
}

void *MinecraftPackets::createPacket(int a) {
    return MinecraftPackets_createPacket(this, a);
}
