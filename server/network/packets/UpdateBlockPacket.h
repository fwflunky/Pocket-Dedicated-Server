//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_updateblockPACKET_H
#define MCPELAUNCHER_updateblockPACKET_H

#include "Packet.h"
#include "../../level/BlockPos.h"

class UpdateBlockPacket : public Packet {
public:
    static void initHooks(void* handle);
    static inline void (*UpdateBlockPacket_write)(UpdateBlockPacket* update, void* bs) = nullptr;

    ~UpdateBlockPacket() override = default;
    void write(void* bs) override;
    unsigned char getId() override;

    int x,y,z;
    unsigned char blockId;
    unsigned char blockData;
    unsigned char flags;
};
#endif //MCPELAUNCHER_updateblockPACKET_H
