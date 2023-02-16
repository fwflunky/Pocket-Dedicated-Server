//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_SCHEDULER_H
#define PDSERVER_SCHEDULER_H


#include <chrono>

class Scheduler {
public:

    static inline Scheduler* (*singleton)() = nullptr;
    static inline void (*Scheduler_processCoroutines)(Scheduler*, double) = nullptr;

    void processCoroutines(double d);
};


#endif //PDSERVER_SCHEDULER_H
