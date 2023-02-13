//
// Created by user on 05.02.23.
//

#include <iostream>
#include "ServerCommands.h"
#include "../../hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
#include "../statics.h"

void ServerCommands::initHooks(void *handle) {
    //ServerCommands_setupStandardServer = (void (*)(ServerCommands*, const std::string &, const std::string &)) hybris_dlsym(handle, "_ZN14ServerCommands19setupStandardServerER9MinecraftRKSsS3_");
    hookFunction((void *) hybris_dlsym(handle, "_ZN14ServerCommands19setupStandardServerER9MinecraftRKSsS3_"), (void *) &ServerCommands::setupStandardServer, (void **) &ServerCommands::ServerCommands_setupStandardServer);

}

void ServerCommands::setupStandardServer(const std::string &a, const std::string &b) {
    std::cout << statics::game->getServerNetworkHandler() << "\n";
   ServerCommands_setupStandardServer(this, a, b);

   // void *local_44 [2];
  //  local_44[0] = malloc(1);

    MinecraftGame::MinecraftGame_getMinecraft(statics::game)->cmds->registerSingleStepCommand("anus", 1, "byName", (CommandType) 3, [](CommandOrigin const&, CommandPropertyBag const&, CommandPropertyBag&) -> MCRESULT {
        std::cout << "registerSingleStepCommand cb\n";
        return MCRESULT::NotEnoughPermissions;
    });
}
