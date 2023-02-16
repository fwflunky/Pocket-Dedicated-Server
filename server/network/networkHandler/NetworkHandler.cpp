//
// Created by user on 29.01.23.
//

#include <iostream>
#include "NetworkHandler.h"
#include "Connection.h"
#include "../../../src/hook.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void NetworkHandler::NetworkHandler::initHooks(void *handle) {
    NetworkHandler_getPeerForUser = (BatchedNetworkPeer *(*)(NetworkHandler *, NetworkIdentifier const &)) hybris_dlsym(handle, "_ZN14NetworkHandler14getPeerForUserERK17NetworkIdentifier");
    NetworkHandler_closeConnection = (void (*)(NetworkHandler *, NetworkIdentifier const &, const std::string &)) hybris_dlsym(handle, "_ZN14NetworkHandler15closeConnectionERK17NetworkIdentifierRKSs");
    NetworkHandler_send = (void (*)(NetworkHandler *, NetworkIdentifier const &, Packet const&)) hybris_dlsym(handle, "_ZN14NetworkHandler4sendERK17NetworkIdentifierRK6Packet");
    NetworkHandler_ctor = (void (*)(NetworkHandler *)) hybris_dlsym(handle, "_ZN14NetworkHandlerC2Ev");
}

BatchedNetworkPeer *NetworkHandler::NetworkHandler::getPeerForUser(NetworkIdentifier const &i) {
    return NetworkHandler_getPeerForUser(this, i);
}

void NetworkHandler::NetworkHandler::closeConnection(const NetworkIdentifier &i, const std::string &s) {
    NetworkHandler_closeConnection(this, i, s);
}

void NetworkHandler::NetworkHandler::send(const NetworkIdentifier &i, const Packet &p) {
    NetworkHandler_send(this, i, p);
}

NetworkHandler::NetworkHandler::NetworkHandler() {
    NetworkHandler_ctor(this);
}
