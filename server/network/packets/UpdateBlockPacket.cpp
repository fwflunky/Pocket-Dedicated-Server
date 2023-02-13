//
// Created by user on 03.02.23.
//
#include "UpdateBlockPacket.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void UpdateBlockPacket::initHooks(void *handle) {
    UpdateBlockPacket_write = (void (*)(UpdateBlockPacket *, void*)) hybris_dlsym(handle, "_ZNK17UpdateBlockPacket5writeER12BinaryStream");
}

unsigned char UpdateBlockPacket::getId() {
    return 0x16;
}

void UpdateBlockPacket::write(void *bs) {
    UpdateBlockPacket_write(this, bs);
}
