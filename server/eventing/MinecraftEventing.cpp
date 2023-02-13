//
// Created by user on 27.01.23.
//

#include "MinecraftEventing.h"
#include <iostream>
#include "../../hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
#include "../../src/common.h"

void MinecraftEventing::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZN17MinecraftEventing26fireEventPlayerMessageChatERKSsS1_"), (void *) &MinecraftEventing::fireEventPlayerMessageChat, (void **) &MinecraftEventing::MinecraftEventing_fireEventPlayerMessageChat);
    hookFunction((void *) hybris_dlsym(handle, "_ZN17MinecraftEventing17fireEventItemUsedEP6PlayerRK12ItemInstanceNS_9UseMethodE"), (void *) &MinecraftEventing::fireEventItemUsed, (void **) &MinecraftEventing::MinecraftEventing_fireEventItemUsed);

}

void MinecraftEventing::fireEventPlayerMessageChat(const std::string &name, const std::string &msg) {
    //handleSignal(11, 0);
    std::cout << "fireEventPlayerMessageChat " << name << " / " << msg << "\n";
}

void MinecraftEventing::fireEventItemUsed(Player & p, ItemInstance & i, int ii) {
    std::cout << "fireEventItemUsed " << "\n";
    MinecraftEventing_fireEventItemUsed(this, p, i, ii);

}
