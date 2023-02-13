//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_LOGINPACKET_H
#define MCPELAUNCHER_LOGINPACKET_H


#include "Packet.h"
#include "../connectionRequest/ConnectionRequest.h"

class LoginPacket : public Packet {
public:
    static void initHooks(void* handle);

    static inline void (*LoginPacket_write)(LoginPacket* pk, void* bs) = nullptr;

    ~LoginPacket() override = default;
    void write(void* bs) override;

    unsigned char getId() override;

    unsigned char gameEdition;
    int proto;
    ConnectionRequest* req;
};


#endif //MCPELAUNCHER_LOGINPACKET_H
