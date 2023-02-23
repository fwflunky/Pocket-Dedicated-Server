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


bool LoginChecks::checkOnSpawn(Player &p) { //todo block all packets if not spawned
    spdlog::info("Player {0} ({1}:{2}) joined the game", p.nickname, p.getFuckingIpPortWithAccessToFuckingRakNetBruh().first, p.getFuckingIpPortWithAccessToFuckingRakNetBruh().second);

    p.sendInventory();

    //statics::serverNetworkHandler->_displayGameMessage("§l§bAtmosphere§f'PE§r", "§bИгрок §f" + p.nickname + " §bприсоединился §fк игре");
    statics::serverNetworkHandler->_displayGameMessage("", "§eТекущий онлайн " + std::to_string(statics::serverNetworkHandler->_getActivePlayerCount()) + " игроков (-а)");

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

bool LoginChecks::checkOnLogin(LoginPacket *login, const NetworkIdentifier &identifier) {
    auto [ip, port] = Player::ipsHolder.at(identifier.id);

    Json::Value val("");
    auto displayName = std::string(login->req->certificate->getExtraData("displayName", val).asCString() - 4); //todo why?
    auto identity = std::string(login->req->certificate->getExtraData("identity", val).asCString() - 4); //todo why?
    try {
        auto fs = std::ifstream(std::filesystem::current_path().string() + "/register/authed/" + identity); //wtf with strings in json
        std::stringstream buffer;

        if (!fs)
            throw std::exception();
        buffer << fs.rdbuf();
        auto bstr = buffer.str();
        auto parts = bstr | ranges::views::split(';') | ranges::to<std::vector<std::string>>();

        if (parts[0] != ip)
            throw std::exception();

        int timed = std::stoi(parts[1]);

        if ((time(nullptr) - timed) >= 3)
            throw std::exception();

        std::filesystem::remove(std::filesystem::current_path().string() + "/register/authed/" + identity);
    } catch (...) {
        spdlog::debug("Player {3} with identity {0} and IP {1}:{2} not registered", identity, ip, port, displayName);
        //TransferPacket packet; cant transfer on login
        //statics::minecraft->disconnectClient(identifier, "disconnectionScreen.notAuthenticated");
        //return false; //todo
    }

    auto reason = Bans::isIpBanned(ip);
    if (!reason.empty()) {
        statics::minecraft->disconnectClient(identifier, "%disconnectionScreen.cantConnectToRealm:\nbanned");
        return false;
    }


    auto lowerNick = displayName;
    std::transform(lowerNick.begin(), lowerNick.end(), lowerNick.begin(),
                   [](unsigned char c) { return std::tolower(c); });

    if (lowerNick.contains("dinnerbone") || lowerNick.contains("grumm") || lowerNick.length() > 16 || lowerNick.length() < 3 ||
    (lowerNick.find_first_not_of("abcdefghijklmnopqrstuvwxyz0123456789-_") != std::string::npos)) {
        statics::minecraft->disconnectClient(identifier, "%disconnectionScreen.cantConnectToRealm:\nInvalid nickname");
        return false;
    }

    for (auto user: *statics::serverNetworkHandler->mainLevel->getUsers()) {
        auto unick = user->nickname;
        std::transform(unick.begin(), unick.end(), unick.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        if (unick == lowerNick) {
            statics::minecraft->disconnectClient(identifier, "%disconnectionScreen.loggedinOtherLocation:\nPlayer already in game");
            return false;
        }
    }

    if (!Whitelist::byNickIsAllowed(displayName)) { //not lower
        statics::minecraft->disconnectClient(identifier, "disconnectionScreen.notAllowed");
        return false;
    }

    Player::lowerNickHolder.insert({identifier.id, lowerNick});
    spdlog::info("Player {3} with identity {0} and IP {1}:{2} connected", identity, ip, port, displayName);
    return true;
}

void LoginChecks::checkOnDisconnect(const NetworkIdentifier &identifier, const std::string &reason) {
    auto player = statics::serverNetworkHandler->_getServerPlayer(identifier);
    if (!player)
        return;
    auto ip = player->getFuckingIpPortWithAccessToFuckingRakNetBruh();
    spdlog::debug("LoginChecks::checkOnDisconnect: player {0} ({1}:{2}) disconnected with reason: {3}", player->nickname, ip.first, ip.second, reason);
}
