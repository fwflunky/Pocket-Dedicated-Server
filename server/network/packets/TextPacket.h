//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_TEXTPACKET_H
#define MCPELAUNCHER_TEXTPACKET_H

#include <string>
#include <vector>
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "Packet.h"
#include <iostream>
class TextPacket : public Packet {
public:
    static void initHooks(void* handle);
    static inline TextPacket* (*TextPacket_createRaw)(TextPacket*, std::string const&) = nullptr;
    static inline TextPacket* (*TextPacket_createTranslated)(TextPacket*, std::string const&, std::vector<std::string> const&) = nullptr;
    static inline void (*TextPacket_write)(TextPacket*, void* bs) = nullptr;
    static TextPacket* createRaw(std::string const& msg);
    static TextPacket* createTranslated(std::string const& msg, std::vector<std::string> const& tr);

    ~TextPacket() override = default;
    void write(void* bs) override;
    unsigned char getId() override;

    unsigned char type; //padding xd
    std::string source; //20
    std::string message; //24
    std::vector<std::string> translated; //18
};

#endif //MCPELAUNCHER_TEXTPACKET_H
