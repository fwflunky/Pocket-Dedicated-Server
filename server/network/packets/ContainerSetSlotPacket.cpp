//
// Created by user on 12.02.23.
//

#include "ContainerSetSlotPacket.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void ContainerSetSlotPacket::initHooks(void *handle) {
    ContainerSetSlotPacket_write = (void (*)(ContainerSetSlotPacket *, void*)) hybris_dlsym(handle, "_ZNK22ContainerSetSlotPacket5writeER12BinaryStream");
}

void ContainerSetSlotPacket::write(void *bs) {
    ContainerSetSlotPacket_write(this, bs);
}

unsigned char ContainerSetSlotPacket::getId() {
    return 0x32;
}
