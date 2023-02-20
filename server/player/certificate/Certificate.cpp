//
// Created by user on 13.02.23.
//

#include "Certificate.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void Certificate::initHooks(void *handle) {
    Certificate_getExtraData = (Json::Value (*)(Certificate *, std::string const&, Json::Value const&)) hybris_dlsym(handle, "_ZNK11Certificate12getExtraDataERKSsRKN4Json5ValueE");
}

Json::Value Certificate::getExtraData(const std::string &str, const Json::Value &val) {
    return Certificate_getExtraData(this, str, val);
}
