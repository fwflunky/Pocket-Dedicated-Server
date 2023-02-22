//
// Created by user on 29.01.23.
//

#include <iostream>
#include "NetworkHandler.h"
#include "Connection.h"
#include "../../../src/hook.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../statics.h"
#include "spdlog/spdlog.h"

void NetworkHandler::NetworkHandler::initHooks(void *handle) {
    NetworkHandler_getPeerForUser = (BatchedNetworkPeer *(*)(NetworkHandler *, NetworkIdentifier const &)) hybris_dlsym(handle, "_ZN14NetworkHandler14getPeerForUserERK17NetworkIdentifier");
    //NetworkHandler_closeConnection = (void (*)(NetworkHandler *, NetworkIdentifier const &, const std::string &)) hybris_dlsym(handle, "_ZN14NetworkHandler15closeConnectionERK17NetworkIdentifierRKSs");
    hookFunction((void *) hybris_dlsym(handle, "_ZN14NetworkHandler15closeConnectionERK17NetworkIdentifierRKSs"), (void *) &NetworkHandler::closeConnection, (void **) &NetworkHandler::NetworkHandler_closeConnection);

    NetworkHandler_setCloseConnection = (void (*)(NetworkHandler *, NetworkIdentifier const &)) hybris_dlsym(handle, "_ZN14NetworkHandler18setCloseConnectionERK17NetworkIdentifier");
    NetworkHandler_send = (void (*)(NetworkHandler *, NetworkIdentifier const &, Packet const&)) hybris_dlsym(handle, "_ZN14NetworkHandler4sendERK17NetworkIdentifierRK6Packet");
    NetworkHandler_ctor = (void (*)(NetworkHandler *)) hybris_dlsym(handle, "_ZN14NetworkHandlerC2Ev");
}

BatchedNetworkPeer *NetworkHandler::NetworkHandler::getPeerForUser(NetworkIdentifier const &i) {
    return NetworkHandler_getPeerForUser(this, i);
}

void NetworkHandler::NetworkHandler::closeConnection(const NetworkIdentifier &i, const std::string &s) {
    if(statics::serverNetworkHandler->_getServerPlayer(i))
        NetworkHandler_closeConnection(this, i, s); //erase in ServerNetworkHandler::onDisconnect
    else {
        if(Player::ipsHolder.contains(i.id)) {
            auto [ip, port] = Player::ipsHolder.at(i.id);
            spdlog::debug("NetworkHandler::closeConnection: address {0}:{1} disconnected before spawn with reason: {2}", ip, port, s);
            Player::ipsHolder.erase(i.id); //erase here cuz ServerNetworkHandler::onDisconnect get segfault
        }
    }
}

void NetworkHandler::NetworkHandler::send(const NetworkIdentifier &i, const Packet &p) {
    NetworkHandler_send(this, i, p);
}

NetworkHandler::NetworkHandler::NetworkHandler() {
    NetworkHandler_ctor(this);
}

void NetworkHandler::NetworkHandler::setCloseConnection(const NetworkIdentifier &id) {
    NetworkHandler_setCloseConnection(this, id);
}
