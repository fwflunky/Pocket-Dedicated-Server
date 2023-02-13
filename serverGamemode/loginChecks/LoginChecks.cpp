//
// Created by user on 13.02.23.
//

#include <algorithm>
#include "LoginChecks.h"
#include "../server/level/Level.h"
#include "../../server/whitelist/Whitelist.h"
#include "../../server/statics.h"
#include "../../server/network/packets/SetTitlePacket.h"

bool LoginChecks::checkOnLogin() {
    return false;
}

bool LoginChecks::checkOnSpawn(Player& p) {
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
    Json::Value val("ss");
    auto ss = p.certificate->getExtraData("idendtity", val);
    std::cout << ss.toStyledString() << "\n";

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

    /*auto iff = InventoryFixer::createOrGetInventory(*p.getNameTag());
    auto sl = p.inventoryProxy->getSlots();
    for (int i = 0; i < sl.size(); i++) {
        iff->items[i] = *sl[i];

    }*/

//ss->maxIncomingConnections = 0;
//sleep(9999);
    // p.enderChestContainer->nameChanged = true;
    //auto idd = p.identifier;
    //NetworkIdentifier id;
    //memcpy(&id, &p.identifier, sizeof(NetworkIdentifier));
    // auto ss = *_getServerPlayer(p.identifier)->getDimension()->blockSource;

    // std::cout << "checkBed: " << p.checkBed(true) << "\n";
    //std::cout << "server network: player level ptr: " << p.getLevel() << ", dimension ptr: " << p.getDimension() << ", chunksource: " << p.playerChunkSource << "\n";
    // std::cout << "checkBed done" << "\n";

    // char str[INET_ADDRSTRLEN];
    //inet_ntop(AF_INET, &p.identifier.addr1, str, INET_ADDRSTRLEN);
    //std::cout << p.identifier.id << "\n";
    //sleep(9999);
    //auto bs = BlockSource(*p.getLevel(), *p.getDimension(), *p.playerChunkSource, true, false);

    // std::cout << p.playerChunkSource.maxText << "\n";
    //std::cout << bs.getBlockID({321,61,137})<< "\n"; //TODO GET BLOCK AND ID
    // p.inventoryProxy->getSlots()[p.inventoryProxy->selectedSlot]->count = 64;
    //p.sendInventory();
    // std::cout << BlockSource::inst->getBlockAndData({321,61,137}) << "\n";
    //std::cout << BlockSource::inst->getBlockAndData({321,60,137}) << "\n";
    //p.sendInventory();

    //->encryptedNetworkPeer->sendPacket("ss", 1, 0);
    // sleep(5); //0x585b1a10

    //auto n = _getServerPlayer(p.identifier);
    // p.addEffect({14, 20 * 30, 0});
    //n->openInventory();
    /*std::thread([this, n, name, id = p.identifier]() {
        sleep(1);
        //n->getLevel()->suspendPlayer(*n);


        SetTitlePacket pk;

        pk.fadeIn = 1;
        pk.fadeOut = 1;
        pk.duration = 3;

        pk.type = 3;
        pk.title = "§f§lPE";
        networkHandler->send(id, pk);

        pk.type = 2;
        pk.title = "§bAtmosphere";
        networkHandler->send(id, pk);

        sleep(5);

        pk.type = 3;
        pk.title = "§f§l" + name;
        networkHandler->send(id, pk);

        pk.type = 2;
        pk.title = "§bДобро пожаловать,";
        networkHandler->send(id, pk);
        // sleep(10);
        // n->getLevel()->resumePlayer(*n);
    }).detach();*/
}
