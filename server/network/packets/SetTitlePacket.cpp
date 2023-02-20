//
// Created by user on 10.02.23.
//

#include "SetTitlePacket.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void SetTitlePacket::initHooks(void *handle) {
    SetTitlePacket_write = (void (*)(SetTitlePacket *, void*)) hybris_dlsym(handle, "_ZNK14SetTitlePacket5writeER12BinaryStream");
}

void SetTitlePacket::write(void *bs) {
    SetTitlePacket_write(this, bs);
}

unsigned char SetTitlePacket::getId() {
    return 0x59;
}
