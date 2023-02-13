//
// Created by user on 05.02.23.
//

#ifndef MCPELAUNCHER_SERVERCOMMANDS_H
#define MCPELAUNCHER_SERVERCOMMANDS_H


#include <string>

class ServerCommands {
public:
    static void initHooks(void* handle);

    static inline void (*ServerCommands_setupStandardServer)(ServerCommands*, std::string const&, std::string const&) = nullptr;
    void setupStandardServer(std::string const& a, std::string const& b);

};


#endif //MCPELAUNCHER_SERVERCOMMANDS_H
