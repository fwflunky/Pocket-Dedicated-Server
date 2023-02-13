//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_RAKPEER_H
#define MCPELAUNCHER_RAKPEER_H

#include "../NetworkIdentifier.h"
class SystemAddress {
public:
    union
    {
        struct sockaddr_storage sa_stor;
		sockaddr_in6 addr6;

        sockaddr_in addr4;
    } address;
    unsigned short debugPort;
    unsigned short systemIndex;
    int padding;
};

class RakNetGUID {
public:
    uint64_t g;
    short systemIndex;
    int padding;
};

class RakPeer {
public:
    static void initHooks(void *handle);
    static inline SystemAddress (*RakPeer_GetSystemAddressFromGuid)(RakPeer*, const RakNetGUID input) = nullptr;
    static inline int (*RakPeer_NumberOfConnections)(RakPeer*) = nullptr;

    SystemAddress GetSystemAddressFromGuid(const RakNetGUID input);
    int NumberOfConnections();

    char filler[16];
    unsigned int maxIncomingConnections;
};


#endif //MCPELAUNCHER_RAKPEER_H
