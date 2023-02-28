//
// Created by user on 28.02.23.
//

#ifndef PDSERVER_DPLAYER_H
#define PDSERVER_DPLAYER_H

#include "../../../server/player/ServerPlayer.h"

namespace dataWrapper {
    class Player{
    public:
        explicit Player(ServerPlayer* sp);
        Player() = default;
        ~Player() {
            delete player;
        };

        virtual void sendMessage(const std::string& msg);
    private:
        ServerPlayer* player = nullptr;
    };
}

#endif //PDSERVER_DPLAYER_H
