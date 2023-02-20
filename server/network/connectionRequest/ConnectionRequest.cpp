//
// Created by user on 13.02.23.
//

#include "ConnectionRequest.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void ConnectionRequest::initHooks(void *handle) {
    ConnectionRequest_verifySelfSigned = (bool (*)(ConnectionRequest*)) hybris_dlsym(handle, "_ZN17ConnectionRequest16verifySelfSignedEv");

}

bool ConnectionRequest::verifySelfSigned() {
    return ConnectionRequest_verifySelfSigned(this);
}
