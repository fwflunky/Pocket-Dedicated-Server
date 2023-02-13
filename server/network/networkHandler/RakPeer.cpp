//
// Created by user on 13.02.23.
//

#include "RakPeer.h"
#include "../../../hybris/include/hybris/dlfcn.h"
void RakPeer::initHooks(void *handle) {
    RakPeer_GetSystemAddressFromGuid = (SystemAddress (*)(RakPeer*, RakNetGUID)) hybris_dlsym(handle, "_ZNK6RakNet7RakPeer24GetSystemAddressFromGuidENS_10RakNetGUIDE");
    RakPeer_NumberOfConnections = (int (*)(RakPeer*)) hybris_dlsym(handle, "_ZNK6RakNet7RakPeer19NumberOfConnectionsEv");
}

SystemAddress RakPeer::GetSystemAddressFromGuid(RakNetGUID i) {
    return RakPeer_GetSystemAddressFromGuid(this, i);
}

int RakPeer::NumberOfConnections() {
    return RakPeer_NumberOfConnections(this);
}
