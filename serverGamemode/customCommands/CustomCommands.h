//
// Created by user on 10.02.23.
//

#ifndef MCPELAUNCHER_CUSTOMCOMMANDS_H
#define MCPELAUNCHER_CUSTOMCOMMANDS_H


#include "../../server/network/packets/CommandStepPacket.h"
#include "../../server/player/ServerPlayer.h"
#include <nlohmann/json.hpp>

class CustomCommands {
public:
    static void handleStep(CommandStepPacket& packet, ServerPlayer* player);
    static inline std::map<std::string, std::function<bool(ServerPlayer*, nlohmann::json&)>> registeredCommands;

    static bool registerCommand(const std::string& name, std::function<bool(ServerPlayer*, nlohmann::json&)> fun);
};


#endif //MCPELAUNCHER_CUSTOMCOMMANDS_H
