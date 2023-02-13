//
// Created by user on 29.01.23.
//

#include "BatchedNetworkPeer.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../../src/hook.h"
#include <iostream>
void BatchedNetworkPeer::initHooks(void *handle) {
    BatchedNetworkPeer_sendPacket = (void (*)(BatchedNetworkPeer *,std::string,int,int)) hybris_dlsym(handle, "_ZN18BatchedNetworkPeer10sendPacketESsN11NetworkPeer11ReliabilityEi");//, (void *) &BatchedNetworkPeer::sendPacket, (void **) &BatchedNetworkPeer::BatchedNetworkPeer_sendPacket);

}

void BatchedNetworkPeer::sendPacket(std::string s, int i, int ii) {
    BatchedNetworkPeer_sendPacket(this, s,i,ii);
}
