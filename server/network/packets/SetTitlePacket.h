//
// Created by user on 10.02.23.
//

#ifndef MCPELAUNCHER_SETTITLEPACKET_H
#define MCPELAUNCHER_SETTITLEPACKET_H


#include "Packet.h"

class SetTitlePacket : public Packet {
public:
    static void initHooks(void* handle);
    static inline void (*SetTitlePacket_write)(SetTitlePacket* update, void* bs) = nullptr;

    ~SetTitlePacket() override = default;
    void write(void* bs) override;
    unsigned char getId() override;

    int type;
    std::string title;
    int fadeIn;
    int duration;
    int fadeOut;
};


#endif //MCPELAUNCHER_SETTITLEPACKET_H
