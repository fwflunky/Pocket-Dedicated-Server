//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_SERVERPLAYER_H
#define MCPELAUNCHER_SERVERPLAYER_H

#include "Player.h"
#include "../network/networkHandler/NetworkHandler.h"

class ServerPlayer : public Player {
public:
    class QueuedChunk {
    public:
        int dimensionId;
        ChunkPos pos;
    };

    static void initHooks(void* handle);

    static inline void (*ServerPlayer_changeDimension)(ServerPlayer*, int dimensionId) = nullptr;
    static inline void (*ServerPlayer_displayWhisperMessage)(ServerPlayer*, std::string const&, std::string const&) = nullptr;
    static inline bool (*ServerPlayer__sendQueuedChunk)(ServerPlayer*, QueuedChunk const&) = nullptr;
    static inline void (*ServerPlayer_openInventory)(ServerPlayer*) = nullptr;
    static inline void (*ServerPlayer_setPlayerGameType)(ServerPlayer*, int) = nullptr;

    NetworkHandler::NetworkHandler* networkHandler;
    char filler[4772 - (4626+4)];

    void changeDimension(int dimensionId);
    void displayWhisperMessage(std::string const&, std::string const&);
    bool _sendQueuedChunk(QueuedChunk const& ch);
    void openInventory();
    void setPlayerGameType(int type);
};

#endif //MCPELAUNCHER_SERVERPLAYER_H
