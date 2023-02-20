//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_STATICS_H
#define MCPELAUNCHER_STATICS_H


#include <functional>
#include <iomanip>
#include "../server/network/ServerNetworkHandler.h"
#include "../serverRunner/minecraftGame/Minecraft.h"

class statics {
public:
    static inline ServerNetworkHandler* serverNetworkHandler = nullptr;
    static inline Minecraft* minecraft = nullptr;
    static inline std::mutex onTickLock;
    static inline std::mutex waitForFuncRuns;

    static inline std::function<void()> runFunc = nullptr;
    static void runOnNextTick(std::function<void()> func);
};


#endif //MCPELAUNCHER_STATICS_H
