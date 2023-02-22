//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_LOGINCHECKS_H
#define MCPELAUNCHER_LOGINCHECKS_H


#include "../../server/player/Player.h"
#include "../../server/network/packets/LoginPacket.h"

class LoginChecks {
public:
    static bool checkOnLogin(LoginPacket* login, const NetworkIdentifier& identifier); //todo
    static bool checkOnSpawn(Player& p);
    static void checkOnDisconnect(const NetworkIdentifier& identifier, const std::string& reason);
};


#endif //MCPELAUNCHER_LOGINCHECKS_H
