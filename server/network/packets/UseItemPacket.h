//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_USEITEMPACKET_H
#define MCPELAUNCHER_USEITEMPACKET_H

#include "Packet.h"
#include "../../level/BlockPos.h"

class UseItemPacket : public Packet {
public:
    int x,y,z; //23
    char filler1[28];
    ItemInstance item;
};
#endif //MCPELAUNCHER_USEITEMPACKET_H
