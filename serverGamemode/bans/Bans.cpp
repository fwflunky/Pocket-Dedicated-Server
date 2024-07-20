//
// Created by user on 13.02.23.
//

#include <filesystem>
#include "Bans.h"
#include "../customCommands/CustomCommands.h"
#include "../../server/level/Level.h"
#include "../../server/statics.h"

void Bans::init() {
    leveldb::Options options;
    options.create_if_missing = true;

    leveldb::Status status = leveldb::DB::Open(options, std::filesystem::current_path().string() +  "/serverGamemode/storage/bans/database", &db);

    CustomCommands::registerCommand("ban", [&](ServerPlayer* player, nlohmann::json& input) -> bool {
        try {
            auto bantype = input["ban type"].get<std::string>();
            auto reason = input["reason"].get<std::string>();
            if(reason.empty()) {
                player->sendMessage("§l§7⋗ §r§cУкажите причину бана");
            }
            auto targetNick = input["player"]["rules"][0]["value"].get<std::string>();
            std::transform(targetNick.begin(), targetNick.end(), targetNick.begin(),
                           [](unsigned char c) { return std::tolower(c); });
            if (input["player"]["selector"].get<std::string>() != "nearestPlayer") {
                player->sendMessage("§l§7⋗ §r§cУкажите конкретный ник игрока. Использовать обобщения может только оператор.");
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
    std::scoped_lock<std::mutex> lock(mux);
    std::string result;
    db->Get(leveldb::ReadOptions(), ip, &result);
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
        return adminPlayer->sendMessage("§l§7⋗ §r§cУказанный игрок не в сети.");
    }

    banIp(receiver->getFuckingIpPortWithAccessToFuckingRakNetBruh().first, reason);
   // receiver->close();
    adminPlayer->sendMessage("§l§7⋗ §r§7Указанный игрок успешно заблокирован.");
    statics::minecraft->disconnectClient(receiver->identifier, ""); //не показывать причину
}