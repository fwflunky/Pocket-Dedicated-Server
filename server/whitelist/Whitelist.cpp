//
// Created by user on 31.01.23.
//

#include "Whitelist.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
#include <iostream>
void Whitelist::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZNK9Whitelist9isAllowedERKN3mce4UUIDERKSs"), (void *) &Whitelist::isAllowed, (void **) &Whitelist::Whitelist_isAllowed);
}

bool Whitelist::isAllowed(void *uuid, const std::string &nick) {
    return false;
}

bool Whitelist::byNickIsAllowed(const std::string &nick) {
    return true;
    return allowedPlayers.contains(nick);
}
