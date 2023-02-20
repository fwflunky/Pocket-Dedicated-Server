//
// Created by user on 13.02.23.
//

#include "RakNetInstance.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void RakNetInstance::initHooks(void *handle) {
    RakNetInstance__getPeer = (RakPeer* (*)(RakNetInstance*, NetworkIdentifier const&)) hybris_dlsym(handle, "_ZN14RakNetInstance8_getPeerERK17NetworkIdentifier");
}

RakPeer *RakNetInstance::_getPeer(const NetworkIdentifier &i) {
    return RakNetInstance__getPeer(this, i);
}
