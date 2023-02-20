//
// Created by user on 05.02.23.
//

#include <iostream>
#include "ServerCommands.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
#include "../statics.h"

void ServerCommands::initHooks(void *handle) {
    //ServerCommands_setupStandardServer = (void (*)(ServerCommands*, const std::string &, const std::string &)) hybris_dlsym(handle, "_ZN14ServerCommands19setupStandardServerER9MinecraftRKSsS3_");
    hookFunction((void *) hybris_dlsym(handle, "_ZN14ServerCommands19setupStandardServerER9MinecraftRKSsS3_"), (void *) &ServerCommands::setupStandardServer, (void **) &ServerCommands::ServerCommands_setupStandardServer);
}

void ServerCommands::setupStandardServer(const std::string &a, const std::string &b) {
   ServerCommands_setupStandardServer(this, a, b);
}
