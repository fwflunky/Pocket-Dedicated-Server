//
// Created by user on 18.02.23.
//

#ifndef PDSERVER_TRANSFERPACKET_H
#define PDSERVER_TRANSFERPACKET_H


#include "Packet.h"

class TransferPacket : public Packet {
public:
    static void initHooks(void* handle);

    static inline void (*TransferPacket_write)(TransferPacket* move, void* bs) = nullptr;

    ~TransferPacket() override = default;
    void write(void* bs) override;

    unsigned char getId() override;

    std::string ip;
    unsigned short port;
};


#endif //PDSERVER_TRANSFERPACKET_H
