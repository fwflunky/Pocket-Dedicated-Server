//
// Created by user on 13.02.23.
//

#include "LoginPacket.h"

void LoginPacket::initHooks(void *handle) {
    //not used
}

void LoginPacket::write(void *bs) {
    //not used
}

unsigned char LoginPacket::getId() {
    return 0x01;
}
