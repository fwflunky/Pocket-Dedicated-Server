//
// Created by user on 29.01.23.
//

#ifndef MCPELAUNCHER_MINECRAFTPACKETS_H
#define MCPELAUNCHER_MINECRAFTPACKETS_H


class __attribute__((packed)) MinecraftPackets {
public:
    static void initHooks(void* handle);
    static inline void* (*MinecraftPackets_createPacket)(MinecraftPackets*, int) = nullptr;
    void* createPacket(int);
};


#endif //MCPELAUNCHER_MINECRAFTPACKETS_H
