//
// Created by user on 05.02.23.
//

#include "MinecraftCommands.h"

#include <utility>
#include <iostream>
#include "../../src/hook.h"
#include "../../hybris/include/hybris/dlfcn.h"

void MinecraftCommands::initHooks(void *handle) {
    MinecraftCommands_registerSingleStepCommand = (void (*)(MinecraftCommands *, std::string const&, int, std::string const&, CommandType const&, std::function<MCRESULT (CommandOrigin const&, CommandPropertyBag const&, CommandPropertyBag&)>)) hybris_dlsym(handle, "_ZN17MinecraftCommands25registerSingleStepCommandERKSsiS1_RK11CommandTypeSt8functionIF8MCRESULTRK13CommandOriginRK18CommandPropertyBagRSA_EE");
    hookFunction((void *) hybris_dlsym(handle, "_ZN17MinecraftCommands25registerSingleStepCommandERKSsiS1_RK11CommandTypeSt8functionIF8MCRESULTRK13CommandOriginRK18CommandPropertyBagRSA_EE"), (void *) &MinecraftCommands::registerSingleStepCommand, (void **) &MinecraftCommands_registerSingleStepCommand);

}

void MinecraftCommands::registerSingleStepCommand(const std::string &s, int i, const std::string &ss, const CommandType &ct, std::function<MCRESULT (const CommandOrigin &, const CommandPropertyBag &, CommandPropertyBag &)> fun) {
    std::cout << s << " " << i << " " << ss << " " << (int) ct  << "\n";
    //std::cout << sizeof(ct) << "\n";
    MinecraftCommands_registerSingleStepCommand(this, s, i, ss, ct, std::move(fun));
}


