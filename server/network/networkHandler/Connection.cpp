//
// Created by user on 29.01.23.
//

#include "Connection.h"
#include "../../../src/hook.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../../src/common.h"
#include "../../statics.h"
#include <iostream>
namespace NetworkHandler {


    void Connection::initHooks(void *handle) {
  //     hookFunction((void *) hybris_dlsym(handle, "_ZN14NetworkHandler10ConnectionC2ERK17NetworkIdentifierR11NetworkPeerNSt6chrono10time_pointINS6_3_V212steady_clockENS6_8durationIxSt5ratioILx1ELx1000000000EEEEEEbP14PacketObserver"), (void *) &Connection::ctor, (void **) &Connection::Connection_ctor);
    }
}