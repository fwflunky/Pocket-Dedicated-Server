//
// Created by user on 13.02.23.
//

#include "Bans.h"
#include "../customCommands/CustomCommands.h"
#include "../server/level/Level.h"
#include "../../server/statics.h"

void Bans::init() {
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, "/home/user/Видео/mcpelauncher-linux-2ebee1b9a70479685a4c430370c3fdfa47988b54/serverGamemode/storage/bans/database", &db);

    CustomCommands::registerCommand("ban", [&](ServerPlayer* player, nlohmann::json& input) -> bool {
        try {
            auto bantype = input["ban type"].get<std::string>();
            auto reason = input["reason"].get<std::string>();
            if(reason.empty()) {
                player->sendMessage("Укажите причину бана");
            }
            auto targetNick = input["player"]["rules"][0]["value"].get<std::string>();
            std::transform(targetNick.begin(), targetNick.end(), targetNick.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (input["player"]["selector"].get<std::string>() != "nearestPlayer") {
                player->sendMessage("Укажите конкретный ник игрока. Использовать обобщения может только оператор.");
                return false;
            }

            if(bantype == "ip")
                continueBanIp(player, targetNick, reason);

        } catch(...){
            player->sendMessageTranslated("§c%commands.generic.exception", {});
            return true;
        }
        return true;
    });
}

bool Bans::banIp(const std::string &ip, const std::string &reason) {
    if(reason.empty())
        return false;

    std::scoped_lock<std::mutex> lock(mux);

    std::string result;
    db->Get(leveldb::ReadOptions(), ip, &result).ok();
    if(!result.empty())
        return false;

    std::cout << "b " << ip.size() << "\n";
    return db->Put(leveldb::WriteOptions(), ip, reason).ok();
}

std::string Bans::isIpBanned(const std::string &ip) {
    std::cout << "isb " << ip.size() << "\n";
    std::scoped_lock<std::mutex> lock(mux);

    std::string result;
    db->Get(leveldb::ReadOptions(), ip, &result);
    std::cout << "isb res: " << result << "\n";
    return result;
}

void Bans::continueBanIp(ServerPlayer *adminPlayer, const std::string &targetNick, const std::string & reason) {
    Player *receiver = nullptr;

    for (auto user: *adminPlayer->getLevel()->getUsers()) {
        auto unick = user->nickname;
        std::transform(unick.begin(), unick.end(), unick.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (unick == targetNick) {
            receiver = user;
            break;
        }
    }
    if (!receiver) {
        return adminPlayer->sendMessage("Указанный игрок не в сети.");
    }

    banIp(receiver->getFuckingIpPortWithAccessToFuckingRakNetBruh().first, reason);
    statics::minecraft->disconnectClient(receiver->identifier, "banned"); //не показывать причину
   // receiver->close();
    adminPlayer->sendMessage("Указанный игрок успешно заблокирован.");
}

