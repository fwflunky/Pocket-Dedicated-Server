//
// Created by user on 05.02.23.
//

#ifndef MCPELAUNCHER_COMMAND_H
#define MCPELAUNCHER_COMMAND_H


#include <string>

class Command {
public:
    static void initHooks(void* handle);
    static inline void (*Command_ctor)(Command*, std::string const&, int, std::string const&) = nullptr;

    Command(std::string const&, int, std::string const&);
};


#endif //MCPELAUNCHER_COMMAND_H
