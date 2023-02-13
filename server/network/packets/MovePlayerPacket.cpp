//
// Created by user on 11.02.23.
//

#include "MovePlayerPacket.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void MovePlayerPacket::initHooks(void *handle) {
    MovePlayerPacket_write = (void (*)(MovePlayerPacket *, void*)) hybris_dlsym(handle, "_ZNK16MovePlayerPacket5writeER12BinaryStream");
}

void MovePlayerPacket::write(void *bs) {
    MovePlayerPacket_write(this, bs);
}

unsigned char MovePlayerPacket::getId() {
    return 0x13;
}
