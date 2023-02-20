//
// Created by user on 26.01.23.
//

#include "statics.h"

void statics::runOnNextTick(std::function<void()> func)  {
    waitForFuncRuns.lock();
    std::scoped_lock<std::mutex> lock(onTickLock);
    runFunc = std::move(func);
}
