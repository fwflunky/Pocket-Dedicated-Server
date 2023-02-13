//
// Created by user on 29.01.23.
//

#ifndef MCPELAUNCHER_BATCHEDNETWORKPEER_H
#define MCPELAUNCHER_BATCHEDNETWORKPEER_H


#include "NetworkPeer.h"
#include <string>

class __attribute__((packed)) BatchedNetworkPeer  {
public:
    static void initHooks(void *handle);

    static inline void (*BatchedNetworkPeer_sendPacket)(BatchedNetworkPeer *, std::string, int, int) = nullptr; //

    void sendPacket(std::string, int, int);
};


#endif //MCPELAUNCHER_BATCHEDNETWORKPEER_H
