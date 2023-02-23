//
// Created by user on 11.02.23.
//

#ifndef MCPELAUNCHER_FREEBOAT_H
#define MCPELAUNCHER_FREEBOAT_H


#include <string>
#include <unordered_map>

class FreeBoat {
public:
    static inline std::unordered_map<std::string, time_t> waits;
    __attribute__((constructor)) static void onInit();
    static void load();
    static void clearWaitFor(const std::string& ln);
    static void addWaitFor(const std::string& ln);
    static bool isWait(const std::string& ln);
};


#endif //MCPELAUNCHER_FREEBOAT_H
