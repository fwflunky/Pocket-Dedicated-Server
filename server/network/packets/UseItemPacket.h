//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_USEITEMPACKET_H
#define MCPELAUNCHER_USEITEMPACKET_H

#include "Packet.h"
#include "../../level/BlockPos.h"
#include "../../item/ItemInstance.h"

class UseItemPacket : public Packet {
public:
    ~UseItemPacket() override = default;
    void write(void* bs) override;
    unsigned char getId() override;

    int x,y,z; //23
    char filler1[28];
    ItemInstance item;
};
#endif //MCPELAUNCHER_USEITEMPACKET_H
