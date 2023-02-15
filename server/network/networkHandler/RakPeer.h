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
};

class RakNetGUID {
public:
    uint64_t g;
    short systemIndex;
    int padding;
};

class AddressOrGUID {
public:
    RakNetGUID rakNetGuid;
    SystemAddress systemAddress;
};

class RakPeer {
public:
    static void initHooks(void *handle);
    static inline SystemAddress (*RakPeer_GetSystemAddressFromGuid)(RakPeer*, const RakNetGUID input) = nullptr;
    static inline int (*RakPeer_NumberOfConnections)(RakPeer*) = nullptr;
    static inline void (*RakPeer_CloseConnection)(RakPeer*, AddressOrGUID, bool, unsigned char, int) = nullptr;
    //static inline bool (*RakPeer_opeq)(RakNetGUID*, RakNetGUID const&) = nullptr;

    SystemAddress GetSystemAddressFromGuid(const RakNetGUID input);
    int NumberOfConnections();
    void CloseConnection(AddressOrGUID a, bool send, unsigned char rel, int prior);

    char filler[16];
    unsigned int maxIncomingConnections;
   // static bool opeq(RakNetGUID*a , RakNetGUID const& s);
};


#endif //MCPELAUNCHER_RAKPEER_H
