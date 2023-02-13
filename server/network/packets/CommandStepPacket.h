//
// Created by user on 10.02.23.
//

#ifndef MCPELAUNCHER_COMMANDSTEPPACKET_H
#define MCPELAUNCHER_COMMANDSTEPPACKET_H

#include "Packet.h"
#include "../../commands/CommandOriginData.h"

class CommandStepPacket : public Packet {
public:
    ~CommandStepPacket() override = default;
    std::string command;
    std::string overload;
    unsigned char uvarint1;
    unsigned char currentStep;
    bool done;
    NetworkIdentifier identifier;
    CommandOriginData originData;
    std::string inputJson;
    std::string outputJson;
};


#endif //MCPELAUNCHER_COMMANDSTEPPACKET_H
