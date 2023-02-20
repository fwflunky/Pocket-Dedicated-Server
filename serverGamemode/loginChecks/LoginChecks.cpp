//
// Created by user on 13.02.23.
//

#include <algorithm>
#include <arpa/inet.h>
#include <thread>
#include "LoginChecks.h"
#include "../../server/level/Level.h"
#include "../../server/whitelist/Whitelist.h"
#include "../../server/statics.h"
#include "../../server/network/packets/SetTitlePacket.h"
#include "../bans/Bans.h"
#include <fstream>
#include <filesystem>
#include <spdlog/spdlog.h>
#include "range/v3/range.hpp"
#include "range/v3/view/split.hpp"
#include "../../server/network/packets/TransferPacket.h"


bool LoginChecks::checkOnSpawn(Player& p) { //todo block all packets if not spawned
    auto lowerNick = p.nickname;
    std::transform(lowerNick.begin(), lowerNick.end(), lowerNick.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    int gotc = 0;
    for (auto user: *p.getLevel()->getUsers()) {
        auto unick = user->nickname;
        std::transform(unick.begin(), unick.end(), unick.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (unick == lowerNick) {
            gotc++; //todo move to pre login
        }
    }

    if(gotc > 1){
        statics::minecraft->disconnectClient(p.identifier, "§bИгрок с этим ником §fуже онлайн");
        return false;
    }

    if (lowerNick.contains("§") || lowerNick.contains("dinnerbone") || lowerNick.contains("grumm") || lowerNick.length() > 16 || lowerNick.length() < 3) {
        statics::minecraft->disconnectClient(p.identifier, "§bНекорректный §fникнейм");
        return false;
    }

    if (!Whitelist::byNickIsAllowed(p.nickname)) {
        statics::minecraft->disconnectClient(p.identifier, "§bВход без проходки §fзапрещен\n§bКупить проходку можно в §fгруппе ВКонтакте\n§fvk.com/§batmospherepe");
        return false;
    }
   // Json::Value val("ss");
   // auto ss = p.certificate->getExtraData("idendtity", val);
   // std::cout << ss.toStyledString() << "\n";
    spdlog::info("Player {0} ({1}:{2}) joined the game", p.nickname, p.getFuckingIpPortWithAccessToFuckingRakNetBruh().first, p.getFuckingIpPortWithAccessToFuckingRakNetBruh().second);

    p.sendInventory();

    statics::serverNetworkHandler->_displayGameMessage("§l§bAtmosphere§f'PE§r", "§bИгрок §f" + p.nickname + " §bприсоединился §fк игре");
    statics::serverNetworkHandler->_displayGameMessage("§l§bAtmosphere§f'PE§r", "§bТекущий онлайн: §f" + std::to_string(statics::serverNetworkHandler->_getActivePlayerCount()) + " §bигроков §f(-а)");

    p.sendMessage(p.getFuckingIpPortWithAccessToFuckingRakNetBruh().first);

    std::thread([id = p.identifier]() {
        sleep(2);
        SetTitlePacket pk;

        pk.fadeIn = 3;
        pk.fadeOut = 1;
        pk.duration = 3;

        pk.type = 3;
        pk.title = "§f§lPE";
        statics::serverNetworkHandler->networkHandler->send(id, pk);

        pk.type = 2;
        pk.title = "§bAtmosphere";
        statics::serverNetworkHandler->networkHandler->send(id, pk);
    }).detach();

    return true;
}

bool LoginChecks::checkOnLogin(LoginPacket* login, const NetworkIdentifier &identifier) {
    auto serverPeer = statics::serverNetworkHandler->networkHandler->rakNetInstanceForServerConnections->peer;
    char str[INET_ADDRSTRLEN];
    auto sa = serverPeer->GetSystemAddressFromGuid({identifier.id});
    inet_ntop(AF_INET, &(sa.address.addr4.sin_addr), str, INET_ADDRSTRLEN);

    Json::Value val("");
    auto ss = login->req->certificate->getExtraData("identity", val);
    auto identity = std::string(ss.asCString() -4); //todo why?
    try {
        auto fs = std::ifstream(std::filesystem::current_path().string() + "/register/authed/" + identity); //wtf with strings in json
        std::stringstream buffer;

        if(!fs)
            throw std::exception();
        buffer << fs.rdbuf();
        auto bstr = buffer.str();
        auto parts = bstr | ranges::views::split(';') | ranges::to<std::vector<std::string>>();

        if(parts[0] != str)
            throw std::exception();

        int timed = std::stoi(parts[1]);

        if((time(nullptr) - timed) >= 3)
            throw std::exception();

        std::filesystem::remove(std::filesystem::current_path().string() + "/register/authed/" + std::string(ss.asCString() -4 ));
    }catch (...){
        spdlog::debug("Player with identity {0} and IP {1}:{2} not registered", identity, str, sa.debugPort);
        //TransferPacket packet; cant transfer on login
        //statics::minecraft->disconnectClient(identifier, "");
       // return false; //todo
    }

    auto reason = Bans::isIpBanned(str);
    if(!reason.empty()){
        //statics::serverNetworkHandler->disconnectClient(identifier, "", true); //не надо показывать причину
        statics::minecraft->disconnectClient(identifier, "");
        //serverPeer->CloseConnection({.rakNetGuid = {.g = identifier.id}, .systemAddress = sa}, true, 0, 0);
        //statics::game->getServerNetworkHandler()->networkHandler->closeConnection(identifier, reason); //why that works and not works in player
       return false;
    }
    spdlog::info("Player with identity {0} and IP {1}:{2} connected", identity, str, sa.debugPort);
    return true;
}

void LoginChecks::checkOnDisconnect(const NetworkIdentifier &identifier) {
    auto player = statics::serverNetworkHandler->_getServerPlayer(identifier);
    if(!player)
        return;
    auto ip = player->getFuckingIpPortWithAccessToFuckingRakNetBruh();
    spdlog::info("Player {0} ({1}:{2}) disconnected", player->nickname, ip.first, ip.second);
}
