//
// Created by user on 29.01.23.
//

#ifndef MCPELAUNCHER_CONNECTION_H
#define MCPELAUNCHER_CONNECTION_H


#include <map>
#include <mutex>
#include "../networkPeer/EncryptedNetworkPeer.h"
#include "../networkPeer/CompressedNetworkPeer.h"
#include "../networkPeer/BatchedNetworkPeer.h"
#include "../NetworkIdentifier.h"

namespace NetworkHandler {
    class Connection {
    public:
        static void initHooks(void *handle);

      //  static inline void (*Connection_ctor)(Connection *, NetworkIdentifier &, NetworkPeer &, std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<long long, std::ratio<1ll, 1000000000ll>>>, bool, void *) = nullptr; //_ZN14NetworkHandler10ConnectionC2ERK17NetworkIdentifierR11NetworkPeerNSt6chrono10time_pointINS6_3_V212steady_clockENS6_8durationIxSt5ratioILx1ELx1000000000EEEEEEbP14PacketObserver
        //static inline void ctor(Connection *a, NetworkIdentifier &b, NetworkPeer &c, std::chrono::time_point<std::chrono::_V2::steady_clock, std::chrono::duration<long long, std::ratio<1ll, 1000000000ll>>> d, bool f, void *g);

        NetworkIdentifier identifier; //144
        char filler[7];
        EncryptedNetworkPeer *encryptedNetworkPeer;
        CompressedNetworkPeer *compressedNetworkPeer;
        BatchedNetworkPeer *batchedNetworkPeer;
        //164
        char filler2[5];
    };
}

#endif //MCPELAUNCHER_CONNECTION_H
