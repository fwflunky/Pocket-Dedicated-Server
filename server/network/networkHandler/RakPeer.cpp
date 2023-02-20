//
// Created by user on 13.02.23.
//

#include <iostream>
#include "RakPeer.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../../src/hook.h"

void RakPeer::initHooks(void *handle) {
    RakPeer_GetSystemAddressFromGuid = (SystemAddress (*)(RakPeer*, RakNetGUID)) hybris_dlsym(handle, "_ZNK6RakNet7RakPeer24GetSystemAddressFromGuidENS_10RakNetGUIDE");
    RakPeer_NumberOfConnections = (int (*)(RakPeer*)) hybris_dlsym(handle, "_ZNK6RakNet7RakPeer19NumberOfConnectionsEv");
    RakPeer_CloseConnection = (void (*)(RakPeer*, AddressOrGUID, bool, unsigned char, int)) hybris_dlsym(handle, "_ZN6RakNet7RakPeer15CloseConnectionENS_13AddressOrGUIDEbh14PacketPriority");
    //hookFunction((void *) hybris_dlsym(handle, "_ZNK6RakNet10RakNetGUIDeqERKS0_"), (void *) &RakPeer::opeq, (void **) &RakPeer::RakPeer_opeq);

}

SystemAddress RakPeer::GetSystemAddressFromGuid(RakNetGUID i) {
    return RakPeer_GetSystemAddressFromGuid(this, i);
}

int RakPeer::NumberOfConnections() {
    return RakPeer_NumberOfConnections(this);
}

void RakPeer::CloseConnection(AddressOrGUID a, bool send, unsigned char rel, int prior) {
    RakPeer_CloseConnection(this, a, send, rel, prior);
}

