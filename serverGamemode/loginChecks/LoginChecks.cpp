//
// Created by user on 13.02.23.
//

#include <algorithm>
#include <arpa/inet.h>
#include "LoginChecks.h"
#include "../server/level/Level.h"
#include "../../server/whitelist/Whitelist.h"
#include "../../server/statics.h"
#include "../../server/network/packets/SetTitlePacket.h"
#include "../bans/Bans.h"

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
        p.disconnect("§bИгрок с этим ником §fуже онлайн");
        return false;
    }

    if (lowerNick.contains("§") || lowerNick.length() > 16 || lowerNick.length() < 3) {
        p.disconnect("§bНекорректный §fникнейм");
        return false;
    }

    if (!Whitelist::byNickIsAllowed(p.nickname)) {
        p.disconnect("§bВход без проходки §fзапрещен\n§bКупить проходку можно в §fгруппе ВКонтакте\n§fvk.com/§batmospherepe");
        return false;
    }
   // Json::Value val("ss");
   // auto ss = p.certificate->getExtraData("idendtity", val);
   // std::cout << ss.toStyledString() << "\n";

    p.sendInventory();

    statics::serverNetworkHandler->_displayGameMessage("§l§bAtmosphere§f'PE§r", "§bИгрок §f" + p.nickname + " §bприсоединился §fк игре");
    statics::serverNetworkHandler->_displayGameMessage("§l§bAtmosphere§f'PE§r", "§bТекущий онлайн: §f" + std::to_string(statics::serverNetworkHandler->_getActivePlayerCount()) + " §bигроков §f(-а)");

    p.sendMessage(p.getFuckingIpPortWithAccessToFuckingRakNetBruh().first);

    SetTitlePacket pk;

    pk.fadeIn = 3;
    pk.fadeOut = 1;
    pk.duration = 3;

    pk.type = 3;
    pk.title = "§f§lPE";
    statics::serverNetworkHandler->networkHandler->send(p.identifier, pk);

    pk.type = 2;
    pk.title = "§bAtmosphere";
    statics::serverNetworkHandler->networkHandler->send(p.identifier, pk);

    return true;
}

bool LoginChecks::checkOnLogin(const NetworkIdentifier &identifier) {
    auto serverPeer = statics::serverNetworkHandler->networkHandler->rakNetInstanceForServerConnections->peer;
    char str[INET_ADDRSTRLEN];
    auto sa = serverPeer->GetSystemAddressFromGuid({identifier.id});
    inet_ntop(AF_INET, &(sa.address.addr4.sin_addr), str, INET_ADDRSTRLEN);

    auto reason = Bans::isIpBanned(str);
    if(!reason.empty()){
        statics::game->getServerNetworkHandler()->disconnectClient(identifier, "", true); //не надо показывать причину
        //serverPeer->CloseConnection({.rakNetGuid = {.g = identifier.id}, .systemAddress = sa}, true, 0, 0);
        //statics::game->getServerNetworkHandler()->networkHandler->closeConnection(identifier, reason); //why that works and not works in player
        return false;
    }
    return true;
}
