//
// Created by user on 10.02.23.
//

#include <thread>
#include "Tpa.h"
#include "../customCommands/CustomCommands.h"
#include "../../server/level/Level.h"
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
                player->sendMessage("§l§7⋗ §r§7Вы ожидаете ответа на запрос от игрока §a" + reqs.receiverNick + "§7. Запрос истечет сам через минуту или Вы можете отменить его самостоятельно написав команду §f/tpa cancel");
                player->sendMessage("§l§7⋗ §r§7Только после этого шага Вы сможете телепортироваться к другому игроку.");
                return true;
            } else if(reqs.receiverNick == myNick) {
                player->sendMessage("§l§7⋗ §r§7Игрок §a" + reqs.issuerNick + " §7ожидает ответа от Вас на телепортацию, для принятия напишите команду §f/tpa accept§7. Запрос истечет сам через минуту или Вы можете отменить его самостоятельно написав команду §f/tpa cancel");
                player->sendMessage("§l§7⋗ §r§7Только после этого шага Вы сможете телепортироваться к другому игроку.");
                return true;
            }
        }

        try {
            auto nick = input["player"]["rules"][0]["value"].get<std::string>();
            std::transform(nick.begin(), nick.end(), nick.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (input["player"]["selector"].get<std::string>() != "nearestPlayer") {
                player->sendMessage("§l§7⋗ §r§cУкажите конкретный ник игрока. Использовать обобщения может только оператор.");
                return false;
            }

            if(myNick == nick){
                player->sendMessage("§l§7⋗ §r§cНельзя телепортироваться к самому себе!");
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
                player->sendMessage("§l§7⋗ §r§cУказанный игрок не в сети.");
                return true;
            }

            issues.push_back(Tpa::issue {
                .issuerNick = myNick,
                .receiverNick = nick,
                .requestValidTill = time(nullptr) + 60
            });

            player->sendMessage("§l§7⋗ §r§7Запрос на телепортацию отправлен игроку §a" + receiver->nickname);
            receiver->sendMessage("§l§7⋗ §r§7Игрок §a" + player->nickname + " §7отправил Вам запрос на телепортацию.");
            receiver->sendMessage("§l§7⋗ §r§7Вы можете принять запрос от игрока §a" + player->nickname + "§7, написав команду §f/tpa accept");
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
            player->sendMessage("§l§7⋗ §r§cВам не поступали запросы на телепортацию, либо старые уже истекли. Возможно, игрок отправивший Вам запрос вышел с сервера.");
            return true;
        }
        issues.erase(issues.begin() + index);
        if(player->getDimension()->dimensionId != issuer->getDimension()->dimensionId){
            player->sendMessage("§l§7⋗ §r§cНевозможно принять запрос. Игрок находится в другом мире.");
            issuer->sendMessage("§l§7⋗ §r§7Игрок §a" + player->nickname + " §7хотел принять Ваш запрос на телепортацию, но он находится в другом мире.");
            return true;
        }

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
        player->sendMessage("§l§7⋗ §r§7Запрос принят. К Вам телепортировался игрок §a" + issuer->nickname);
        issuer->sendMessage("§l§7⋗ §r§7Игрок §a" + player->nickname + " §7принял Ваш запрос на телепортацию.");
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
                        user->sendMessage("§l§7⋗ §r§7Игрок §a" + player->nickname + " §7отклонил Ваш запрос на телепортацию.");
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
            player->sendMessage("§l§7⋗ §r§7Отклонен запрос на телепортацию от игрока §a" + found);
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
            player->sendMessage("§l§7⋗ §r§7Отменен запрос на телепортацию к игроку §a" + found);
            issues.erase(issues.begin() + index);
        }

        if(!globalFound){
            player->sendMessage("§l§7⋗ §r§cЗапросы, подлежащие отмене не найдены.");
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
                                    user->sendMessage("§l§7⋗ §r§7Запрос на телепортацию к игроку §a" + reqs.receiverNick + " §7истек.");
                                    c++;
                                } else if(unick == reqs.receiverNick){
                                    user->sendMessage("§l§7⋗ §r§cЗапрос на телепортацию от игрока §a" + reqs.issuerNick + " §7истек.");
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
