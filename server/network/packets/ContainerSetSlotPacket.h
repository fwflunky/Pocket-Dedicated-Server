//
// Created by user on 12.02.23.
//

#ifndef MCPELAUNCHER_CONTAINERSETSLOTPACKET_H
#define MCPELAUNCHER_CONTAINERSETSLOTPACKET_H


#include "Packet.h"
#include "../../item/ItemInstance.h"

class ContainerSetSlotPacket : public Packet {
public:
    static void initHooks(void* handle);

    static inline void (*ContainerSetSlotPacket_write)(ContainerSetSlotPacket* move, void* bs) = nullptr;

    ~ContainerSetSlotPacket() override = default;
    void write(void* bs) override;

    unsigned char getId() override;

    unsigned char windowId;
    int slot, hotbarSlot;
    ItemInstance item;
    unsigned char selectSlot;
};


#endif //MCPELAUNCHER_CONTAINERSETSLOTPACKET_H
