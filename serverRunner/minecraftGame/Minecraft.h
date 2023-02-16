//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_MINECRAFT_H
#define PDSERVER_MINECRAFT_H


#include "../../server/network/ServerNetworkHandler.h"

class Minecraft {
public:
    static inline ServerNetworkHandler* (*Minecraft_getServerNetworkHandler)(Minecraft*) = nullptr;
    static inline Level* (*Minecraft_getLevel)(Minecraft*) = nullptr;
    static inline void (*Minecraft_disconnectClient)(Minecraft*, NetworkIdentifier const&, std::string const&) = nullptr;

    ServerNetworkHandler* getServerNetworkHandler();
    Level* getLevel();
    void disconnectClient(NetworkIdentifier const& id, std::string const& res);
};


#endif //PDSERVER_MINECRAFT_H
