//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_MINECRAFTEVENTING_H
#define MCPELAUNCHER_MINECRAFTEVENTING_H


#include <string>
#include "../player/Player.h"

class MinecraftEventing {
public:
    static void initHooks(void* handle);

    static inline void (*MinecraftEventing_fireEventPlayerMessageChat)(MinecraftEventing*, std::string const&, std::string const&) = nullptr;
    static inline void (*MinecraftEventing_fireEventItemUsed)(MinecraftEventing*, Player&, ItemInstance&, int) = nullptr;

    void fireEventPlayerMessageChat(std::string const& name, std::string const& msg);
    void fireEventItemUsed(Player&, ItemInstance&, int);
};


#endif //MCPELAUNCHER_MINECRAFTEVENTING_H
