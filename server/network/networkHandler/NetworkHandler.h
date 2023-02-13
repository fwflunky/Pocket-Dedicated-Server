//
// Created by user on 29.01.23.
//

#ifndef MCPELAUNCHER_NETWORKHANDLER_H
#define MCPELAUNCHER_NETWORKHANDLER_H


#include "../NetworkIdentifier.h"
#include "Connection.h"
#include "../packets/Packet.h"
#include "RakNetInstance.h"
#include <vector>
namespace NetworkHandler {
    class NetworkHandler {
    public:
        static void initHooks(void *handle);
        static inline BatchedNetworkPeer* (*NetworkHandler_getPeerForUser)(NetworkHandler*, NetworkIdentifier const&) = nullptr;
        static inline void (*NetworkHandler_closeConnection)(NetworkHandler*, NetworkIdentifier const&, std::string const&) = nullptr;
        static inline void (*NetworkHandler_send)(NetworkHandler*, NetworkIdentifier const&, Packet const&) = nullptr;
        BatchedNetworkPeer* getPeerForUser(NetworkIdentifier const& i);
        void closeConnection(NetworkIdentifier const&, std::string const&);
        void send(NetworkIdentifier const&, Packet const&);
        void** vtable; //todo
        RakNetInstance* rakNetInstanceForServerLocator;
        char filler[2];
        RakNetInstance* rakNetInstanceForServerConnections;
    };
}


#endif //MCPELAUNCHER_NETWORKHANDLER_H
