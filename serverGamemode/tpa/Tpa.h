//
// Created by user on 10.02.23.
//

#ifndef MCPELAUNCHER_TPA_H
#define MCPELAUNCHER_TPA_H


#include <string>
#include <map>
#include "../../server/player/Player.h"

class Tpa {
public:
    static void init();
    static void startTimerThread();
    struct issue {
        std::string issuerNick;
        std::string receiverNick;
        int requestValidTill; //time before valid
    };
    static inline std::vector<issue> issues;
    static inline std::mutex mux;
};


#endif //MCPELAUNCHER_TPA_H
