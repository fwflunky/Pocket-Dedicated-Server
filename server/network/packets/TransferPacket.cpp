//
// Created by user on 18.02.23.
//

#include "TransferPacket.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void TransferPacket::initHooks(void *handle) {
    TransferPacket_write = (void (*)(TransferPacket *, void*)) hybris_dlsym(handle, "_ZNK14TransferPacket5writeER12BinaryStream");
}

void TransferPacket::write(void *bs) {
    TransferPacket_write(this, bs);
}

unsigned char TransferPacket::getId() {
    return 0x56;
}
