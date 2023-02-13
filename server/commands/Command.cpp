//
// Created by user on 05.02.23.
//

#include "Command.h"
#include "../../hybris/include/hybris/dlfcn.h"

void Command::initHooks(void *handle) {
    Command_ctor = (void (*)(Command*, std::string const&, int, std::string const&)) hybris_dlsym(handle, "_ZN7CommandC2ERKSs22CommandPermissionLevelS1_");
}

Command::Command(std::string const& s, int i, std::string const& ss) {
    Command_ctor(this, s, i, ss);
}
