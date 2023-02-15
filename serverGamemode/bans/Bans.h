//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_BANS_H
#define MCPELAUNCHER_BANS_H


#include <leveldb/db.h>
#include <mutex>
#include "../../server/player/ServerPlayer.h"

class Bans {
public:
    static inline leveldb::DB* db = nullptr;
    static inline std::mutex mux;

    static void init();
    static bool banIp(const std::string& ip, const std::string& reason);
    static std::string isIpBanned(const std::string& ip);

    static void continueBanIp(ServerPlayer *adminPlayer, std::string const &targetNick, const std::string & reason);
};


#endif //MCPELAUNCHER_BANS_H
