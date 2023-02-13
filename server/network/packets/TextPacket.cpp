//
// Created by user on 03.02.23.
//
#include "TextPacket.h"

void TextPacket::initHooks(void *handle) {
    TextPacket_createRaw = (TextPacket* (*)(TextPacket *, std::string const&)) hybris_dlsym(handle, "_ZN10TextPacket9createRawERKSs");
    TextPacket_createTranslated = (TextPacket* (*)(TextPacket *, std::string const&, std::vector<std::string> const&)) hybris_dlsym(handle, "_ZN10TextPacket16createTranslatedERKSsRKSt6vectorISsSaISsEE");
    TextPacket_write = (void (*)(TextPacket *, void*)) hybris_dlsym(handle, "_ZNK10TextPacket5writeER12BinaryStream");
}

TextPacket *TextPacket::createRaw(std::string const& msg) {
    auto tp = new TextPacket;
    return TextPacket_createRaw(tp, msg);
}

void TextPacket::write(void *bs) {
    TextPacket_write(this, bs);
}

unsigned char TextPacket::getId() {
    return 0x9;
}

TextPacket *TextPacket::createTranslated(const std::string &msg, const std::vector<std::string> &tr) {
    auto tp = new TextPacket;
    return TextPacket_createTranslated(tp, msg, tr);
}
