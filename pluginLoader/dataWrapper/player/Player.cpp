//
// Created by user on 28.02.23.
//

#include "Player.h"

dataWrapper::Player::Player(ServerPlayer* sp) {
    player = sp;
}

void dataWrapper::Player::sendMessage(const std::string &msg) {
    player->sendMessage(msg);
}
