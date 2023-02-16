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
    static inline void (*MinecraftEventing_construct)(MinecraftEventing*, std::string const&) = nullptr;
    static inline void (*MinecraftEventing_tick)(MinecraftEventing*) = nullptr;

    char filler[0x100];
    MinecraftEventing(std::string const& str);

    void tick();
    void fireEventPlayerMessageChat(std::string const& name, std::string const& msg);
    void fireEventItemUsed(Player&, ItemInstance&, int);
};


#endif //MCPELAUNCHER_MINECRAFTEVENTING_H
