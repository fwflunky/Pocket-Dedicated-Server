//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_LOGINCHECKS_H
#define MCPELAUNCHER_LOGINCHECKS_H


#include "../../server/player/Player.h"

class LoginChecks {
public:
    static bool checkOnLogin(const NetworkIdentifier& identifier); //todo
    static bool checkOnSpawn(Player& p);
};


#endif //MCPELAUNCHER_LOGINCHECKS_H
