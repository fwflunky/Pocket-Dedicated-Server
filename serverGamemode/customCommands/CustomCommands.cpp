//
// Created by user on 10.02.23.
//

#include "CustomCommands.h"
#include "../../server/statics.h"

void CustomCommands::handleStep(CommandStepPacket &packet, ServerPlayer *player) {
    if(packet.command.size() > 30 || packet.inputJson.size() > 500)
        return statics::minecraft->disconnectClient(player->identifier, "%disconnectionScreen.badPacket (CommandStepPacket)"); //block here

    nlohmann::json jsonObj = nlohmann::json::parse(packet.inputJson);
    if(registeredCommands.contains(packet.command)) {
        if(!registeredCommands.at(packet.command)(player, jsonObj)){
            player->sendMessageTranslated("§c%commands.generic.permission", {});
        }
    } else {
        player->sendMessageTranslated("§c%commands.agent.outofrange", {"anus"}); //commands.generic.step.failed
    }
}

/*
 * {
                  "name": "oldBlockHandling",
                  "type": "stringenum",
                  "optional": true,
                  "enum_values": [
                    "destroy",
                    "hollow",
                    "keep",
                    "outline"
                  ]
                }
 */

bool CustomCommands::registerCommand(const std::string &name, std::function<bool(ServerPlayer *, nlohmann::json &)> fun) {
    if(registeredCommands.contains(name))
        return false;

    registeredCommands.insert({name, std::move(fun)});
    return true;
}
