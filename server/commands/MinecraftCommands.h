//
// Created by user on 05.02.23.
//

#ifndef MCPELAUNCHER_MINECRAFTCOMMANDS_H
#define MCPELAUNCHER_MINECRAFTCOMMANDS_H


#include <string>
#include "CommandType.h"
#include "CommandOrigin.h"
#include "CommandPropertyBag.h"
#include <functional>
enum MCRESULT {
    FailedToParseCommand,
    CommandNotFound,
    NotEnoughPermissions,
    //...
};
class MinecraftCommands {
public:
    static void initHooks(void* handle);

    static inline void (*MinecraftCommands_registerSingleStepCommand)(MinecraftCommands*, std::string const&, int, std::string const&, CommandType const&, std::function<MCRESULT (CommandOrigin const&, CommandPropertyBag const&, CommandPropertyBag&)>) = nullptr;

    void registerSingleStepCommand(std::string const& s, int i, std::string const& ss, CommandType const& ct, std::function<MCRESULT (CommandOrigin const&, CommandPropertyBag const&, CommandPropertyBag&)>);
};


#endif //MCPELAUNCHER_MINECRAFTCOMMANDS_H
