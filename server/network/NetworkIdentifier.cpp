//
// Created by user on 26.01.23.
//

#include <iostream>
#include "NetworkIdentifier.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
NetworkIdentifier::NetworkIdentifier(const std::string &a, unsigned short b) {
    NetworkIdentifier_ctor1(this, a, b);
}

std::string NetworkIdentifier::toString() {
    return *NetworkIdentifier_toString(this);
}

void NetworkIdentifier::initHooks(void* handle) {
    NetworkIdentifier_ctor1 = (void (*)(NetworkIdentifier*, std::string const&, unsigned short)) hybris_dlsym(handle, "_ZN17NetworkIdentifierC2ERKSst");
    NetworkIdentifier_toString = (std::string* (*)(NetworkIdentifier*)) hybris_dlsym(handle, "_ZNK17NetworkIdentifier8toStringEv");
    //NetworkIdentifier__init = (void (*)(NetworkIdentifier*, void* sa)) hybris_dlsym(handle, "_ZN17NetworkIdentifier5_initERKN6RakNet13SystemAddressE");
    SystemAddress_toString = (char* (*)(void*, bool)) hybris_dlsym(handle, "_ZNK6RakNet13AddressOrGUID8ToStringEb");
    RakPeer_GetSystemAddressFromGuid = (void* (*)(void*, NetworkIdentifier)) hybris_dlsym(handle, "_ZNK6RakNet7RakPeer24GetSystemAddressFromGuidENS_10RakNetGUIDE");
   // hookFunction((void *) hybris_dlsym(handle, "_ZN17NetworkIdentifierC2ERKN6RakNet13SystemAddressE"), (void *) &NetworkIdentifier::_init, (void **) &NetworkIdentifier::NetworkIdentifier__init);


}

bool NetworkIdentifier::operator==(const NetworkIdentifier &idd) const {
    return idd.id == id;
}

std::string NetworkIdentifier::getAddress() {
   // return SystemAddress_toString(ptr2, true, ':');
}

std::string NetworkIdentifier::satos(bool a) {
    return SystemAddress_toString(this, a);
   // NetworkIdentifier__init(this, sa);
}
