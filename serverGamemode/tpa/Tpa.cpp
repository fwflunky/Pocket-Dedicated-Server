//
// Created by user on 10.02.23.
//

#include "Tpa.h"
#include "../customCommands/CustomCommands.h"
#include "../server/level/Level.h"
#include "../../server/network/packets/MovePlayerPacket.h"
#include "../../server/statics.h"

void Tpa::init() {
    startTimerThread();

    CustomCommands::registerCommand("tpa send", [&](ServerPlayer *player, nlohmann::json &input) -> bool {
        std::scoped_lock<std::mutex> lock(mux);

        auto myNick = player->nickname;
        std::transform(myNick.begin(), myNick.end(), myNick.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        for (auto &reqs: issues) {
            if (reqs.issuerNick == myNick) {
                player->sendMessage("Вы ожидаете ответа на запрос от игрока " + reqs.receiverNick + ". Запрос истечет сам через минуту или Вы можете отменить его самостоятельно написав команду /tpa cancel");
                player->sendMessage("Только после этого шага Вы сможете телепортироваться к другому игроку.");
                return true;
            } else if(reqs.receiverNick == myNick) {
                player->sendMessage("Игрок " + reqs.issuerNick + " ожидает ответа от Вас на телепортацию, для принятия напишите команду /tpa accept. Запрос истечет сам через минуту или Вы можете отменить его самостоятельно написав команду /tpa cancel");
                player->sendMessage("Только после этого шага Вы сможете телепортироваться к другому игроку.");
                return true;
            }
        }

        try {
            auto nick = input["player"]["rules"][0]["value"].get<std::string>();
            std::transform(nick.begin(), nick.end(), nick.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (input["player"]["selector"].get<std::string>() != "nearestPlayer") {
                player->sendMessage("Укажите конкретный ник игрока. Использовать обобщения может только оператор.");
                return false;
            }

            if(myNick == nick){
                player->sendMessage("Нельзя делать самоотсос.");
                return false;
            }
            Player *receiver = nullptr;

            for (auto user: *player->getLevel()->getUsers()) {
                auto unick = user->nickname;
                std::transform(unick.begin(), unick.end(), unick.begin(),
                               [](unsigned char c) { return std::tolower(c); });
                if (unick == nick) {
                    receiver = user;
                    break;
                }
            }
            if (!receiver) {
                player->sendMessage("Указанный игрок не в сети.");
                return true;
            }

            issues.push_back(Tpa::issue {
                .issuerNick = myNick,
                .receiverNick = nick,
                .requestValidTill = time(nullptr) + 60
            });

            player->sendMessage("Запрос на телепортацию отправлен игроку " + receiver->nickname);
            receiver->sendMessage("Игрок " + player->nickname + " отправил Вам запрос на телепортацию.");
            receiver->sendMessage("Вы можете принять запрос от игрока " + player->nickname + " написав команду /tpa accept");
            return true;
        } catch (...) {
            player->sendMessageTranslated("§c%commands.generic.exception", {});
            return true;
        }
    });

    CustomCommands::registerCommand("tpa accept", [&](ServerPlayer *player, nlohmann::json &input) -> bool {
        std::scoped_lock<std::mutex> lock(mux);

        auto nick = player->nickname;
        std::transform(nick.begin(), nick.end(), nick.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        int index = 0;
        Player *issuer = nullptr;
        for (auto &reqs: issues) {
            if (reqs.receiverNick == nick) {
                for (auto user: *player->getLevel()->getUsers()) {
                    auto unick = user->nickname;
                    std::transform(unick.begin(), unick.end(), unick.begin(),
                                   [](unsigned char c) { return std::tolower(c); });
                    if (unick == reqs.issuerNick) {
                        issuer = user;
                        break;
                    }
                }
                break;
            }
            index++;
        }

        if (!issuer) {
            player->sendMessage("Вам не поступали запросы на телепортацию, либо старые уже истекли. Возможно, игрок отправивший Вам запрос вышел с сервера.");
            return true;
        }
        issues.erase(issues.begin() + index);

        issuer->teleportTo({player->x, player->y, player->z}, 0, 0);
        MovePlayerPacket mpk;
        mpk.entityRuntimeId = issuer->runtimeId;
        mpk.pos = {player->x, player->y, player->z};
        mpk.yawPitch = {0, 0};
        mpk.bodyYaw = 90;
        mpk.mode = 2;
        mpk.onGround = false;
        mpk.entityRuntimeId2 = 0;

        statics::serverNetworkHandler->networkHandler->send(issuer->identifier, mpk);
        player->sendMessage("Запрос принят. К Вам телепортировался игрок " + issuer->nickname);
        issuer->sendMessage("Игрок " + player->nickname + " принял Ваш запрос на телепортацию.");
        return true;
    });

    CustomCommands::registerCommand("tpa cancel", [&](ServerPlayer *player, nlohmann::json &input) -> bool {
        std::scoped_lock<std::mutex> lock(mux);

        auto nick = player->nickname;
        std::transform(nick.begin(), nick.end(), nick.begin(),
                       [](unsigned char c) { return std::tolower(c); });

        int index = 0;
        std::string found;
        bool globalFound = false;

        for (auto &reqs: issues) {
            if (reqs.receiverNick == nick) {
                for (auto user: *player->getLevel()->getUsers()) {
                    auto unick = user->nickname;
                    std::transform(unick.begin(), unick.end(), unick.begin(),
                                   [](unsigned char c) { return std::tolower(c); });
                    if (unick == reqs.issuerNick) {
                        user->sendMessage("Игрок " + player->nickname + " отклонил Ваш запрос на телепортацию.");
                        break;
                    }
                }
                globalFound = true; //fix for test with server holder (empty nick)
                found = reqs.issuerNick;
                break;
            }
            index++;
        }

        if(!found.empty() || globalFound) {
            player->sendMessage("Отклонен запрос на телепортацию от игрока " + found);
            issues.erase(issues.begin() + index);
        }
        index = 0;
        found.clear();

        for (auto &reqs: issues) {
            if (reqs.issuerNick == nick) {
                globalFound = true;
                found = reqs.receiverNick;
                break;
            }
            index++;
        }
        if(!found.empty()) {
            player->sendMessage("Отменен запрос на телепортацию к игроку " + found);
            issues.erase(issues.begin() + index);
        }

        if(!globalFound){
            player->sendMessage("Запросы подлежащие отмене не найдены.");
        }
        return true;
    });
}

void Tpa::startTimerThread() {
    std::thread([](){
        while (true){
            sleep(5);
            {
                std::scoped_lock<std::mutex> lock(mux);
                std::vector<int> indexes;
                int index = 0;
                for (auto &reqs: issues) {
                    if(reqs.requestValidTill <= time(nullptr)){
                        statics::runOnNextTick([reqs]() {
                            for (auto user: *statics::serverNetworkHandler->mainLevel->getUsers()) {
                                auto unick = user->nickname;
                                std::transform(unick.begin(), unick.end(), unick.begin(),
                                               [](unsigned char c) { return std::tolower(c); });
                                int c = 0;
                                if (unick == reqs.issuerNick) {
                                    user->sendMessage("Запрос на телепортацию к игроку " + reqs.receiverNick + " истек.");
                                    c++;
                                } else if(unick == reqs.receiverNick){
                                    user->sendMessage("Запрос на телепортацию от игрока " + reqs.issuerNick + " истек.");
                                    c++;
                                }
                                if(c == 2)
                                    break;
                            }
                        });
                        indexes.push_back(index);
                    }
                    index++;
                }
                for(int in : indexes)
                    issues.erase(issues.begin() + in);
            }
        }
    }).detach();
}
