//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_STATICS_H
#define MCPELAUNCHER_STATICS_H


#include "../mcpe/MinecraftGame.h"
#include <functional>
class statics {
public:
    static inline MinecraftGame* game = nullptr;
    static inline ServerNetworkHandler* serverNetworkHandler = nullptr;
    static inline std::mutex onTickLock;
    static inline std::mutex waitForFuncRuns;

    static inline std::function<void()> runFunc = nullptr;
    static void runOnNextTick(std::function<void()> func) {
        waitForFuncRuns.lock();
        std::scoped_lock<std::mutex> lock(onTickLock);
        runFunc = std::move(func);
    }
};


#endif //MCPELAUNCHER_STATICS_H
