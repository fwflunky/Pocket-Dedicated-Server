//
// Created by user on 09.02.23.
//

#include "Container.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void Container::initHooks(void *handle) {
    Container_setCustomName = (void (*)(Container *, const std::string &)) hybris_dlsym(handle, "_ZN9Container13setCustomNameERKSs");
}

void Container::setCustomName(const std::string &name) {
    Container_setCustomName(this, name);
}
