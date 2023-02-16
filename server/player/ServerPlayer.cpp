//
// Created by user on 26.01.23.
//

#include "ServerPlayer.h"
#include "../../hybris/include/hybris/dlfcn.h"

void ServerPlayer::initHooks(void *handle) {
    ServerPlayer_changeDimension = (void (*)(ServerPlayer *, int)) hybris_dlsym(handle, "_ZN12ServerPlayer15changeDimensionE11DimensionId");
    ServerPlayer_displayWhisperMessage = (void (*)(ServerPlayer *, std::string const&, std::string const&)) hybris_dlsym(handle, "_ZN12ServerPlayer21displayWhisperMessageERKSsS1_");
    ServerPlayer__sendQueuedChunk = (bool (*)(ServerPlayer *, ServerPlayer::QueuedChunk const&)) hybris_dlsym(handle, "_ZN12ServerPlayer16_sendQueuedChunkERKNS_11QueuedChunkE");
    ServerPlayer_openInventory = (void (*)(ServerPlayer *)) hybris_dlsym(handle, "_ZN12ServerPlayer13openInventoryEv");
    ServerPlayer_setPlayerGameType = (void (*)(ServerPlayer *, int)) hybris_dlsym(handle, "_ZN12ServerPlayer17setPlayerGameTypeE8GameType");

}

void ServerPlayer::changeDimension(int dimensionId) {
    ServerPlayer_changeDimension(this, dimensionId);
}

void ServerPlayer::displayWhisperMessage(const std::string &source, const std::string & msg) {
    ServerPlayer_displayWhisperMessage(this, source, msg);
}

bool ServerPlayer::_sendQueuedChunk(const ServerPlayer::QueuedChunk &ch) {
    return ServerPlayer__sendQueuedChunk(this, ch);
}

void ServerPlayer::openInventory() {
    ServerPlayer_openInventory(this);
}

void ServerPlayer::setPlayerGameType(int type) {
    ServerPlayer_setPlayerGameType(this, type);
}
