//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_RemoveBlockPacket_H
#define MCPELAUNCHER_RemoveBlockPacket_H

#include "Packet.h"

class RemoveBlockPacket : public Packet {
public:
    int x,y,z;

};
#endif //MCPELAUNCHER_RemoveBlockPacket_H
