//
// Created by user on 26.01.23.
//

#include "ServerNetworkHandler.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
#include "../player/ServerPlayer.h"
#include "../level/Dimension.h"
#include "../level/Level.h"
#include "../raknet/RakNetServerLocator.h"
#include "../level/BlockSource.h"
#include "networkHandler/Connection.h"
#include "../statics.h"
#include "../player/inventory/InventoryFixer.h"
#include "packets/UpdateBlockPacket.h"
#include "../MinecraftObjectLayer.h"
#include "../whitelist/Whitelist.h"
#include "../../serverGamemode/regionGuard/RegionGuard.h"
#include "../../serverGamemode/spawnColors/SpawnColors.h"
#include "packets/SetTitlePacket.h"
#include "../../serverGamemode/customCommands/CustomCommands.h"
#include "../../serverGamemode/AntiCheat/Item.h"
#include "../../serverGamemode/loginChecks/LoginChecks.h"
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <cmath>

void ServerNetworkHandler::initHooks(void *handle) {
    ServerNetworkHandler_disconnectClient = (void (*)(ServerNetworkHandler *, NetworkIdentifier const &, std::string const &, bool)) hybris_dlsym(handle, "_ZN20ServerNetworkHandler16disconnectClientERK17NetworkIdentifierRKSsb");
    ServerNetworkHandler_onDisconnect = (void (*)(ServerNetworkHandler *, NetworkIdentifier const&, std::string const &, bool)) hybris_dlsym(handle, "_ZN20ServerNetworkHandler12onDisconnectERK17NetworkIdentifierRKSsb");
    ServerNetworkHandler__displayGameMessage = (void (*)(ServerNetworkHandler *, const std::string &, const std::string &)) hybris_dlsym(handle, "_ZN20ServerNetworkHandler19_displayGameMessageERKSsS1_");
    ServerNetworkHandler__getActivePlayerCount = (int (*)(ServerNetworkHandler *)) hybris_dlsym(handle, "_ZNK20ServerNetworkHandler21_getActivePlayerCountEv");
    ServerNetworkHandler__getServerPlayer = (ServerPlayer *(*)(ServerNetworkHandler *, NetworkIdentifier const &)) hybris_dlsym(handle, "_ZN20ServerNetworkHandler16_getServerPlayerERK17NetworkIdentifier");
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler24updateServerAnnouncementEv"), (void *) &ServerNetworkHandler::updateServerAnnouncement, (void **) &ServerNetworkHandler::ServerNetworkHandler_updateServerAnnouncement);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler12onDisconnectERK17NetworkIdentifierRKSsb"), (void *) &ServerNetworkHandler::onDisconnect, (void **) &ServerNetworkHandler::ServerNetworkHandler_onDisconnect);

    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler24onReady_ClientGenerationER6PlayerRK17NetworkIdentifier"), (void *) &ServerNetworkHandler::onReady_ClientGeneration, (void **) &ServerNetworkHandler::ServerNetworkHandler_onReady_ClientGeneration);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK10TextPacket"), (void *) &ServerNetworkHandler::handleTextPacket, (void **) &ServerNetworkHandler::ServerNetworkHandler_handle_TextPacket);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK13UseItemPacket"), (void *) &ServerNetworkHandler::handleUseItemPacket, (void **) &ServerNetworkHandler::ServerNetworkHandler_handle_UseItemPacket);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK17RemoveBlockPacket"), (void *) &ServerNetworkHandler::handleRemoveBlockPacket, (void **) &ServerNetworkHandler::ServerNetworkHandler_handle_RemoveBlockPacket);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK16MovePlayerPacket"), (void *) &ServerNetworkHandler::handleMovePlayerPacket, (void **) &ServerNetworkHandler::ServerNetworkHandler_handle_MovePlayerPacket);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK17CommandStepPacket"), (void *) &ServerNetworkHandler::handleCommandStepPacket, (void **) &ServerNetworkHandler::ServerNetworkHandler_handle_CommandStepPacket);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK22ContainerSetSlotPacket"), (void *) &ServerNetworkHandler::handleContainerSetSlotPacket, (void **) &ServerNetworkHandler::ServerNetworkHandler_handle_ContainerSetSlotPacket);
    hookFunction((void *) hybris_dlsym(handle, "_ZN20ServerNetworkHandler6handleERK17NetworkIdentifierRK11LoginPacket"), (void *) &ServerNetworkHandler::handleLoginPacket, (void **) &ServerNetworkHandler::ServerNetworkHandler_handle_LoginPacket);
}

void ServerNetworkHandler::onReady_ClientGeneration(Player &p, NetworkIdentifier &ne) {
    auto name = p.nickname;
    Player::ipsHolder.insert({p.nickname, p.getFuckingIpPortWithAccessToFuckingRakNetBruh()});

    if(LoginChecks::checkOnSpawn(p))
        ServerNetworkHandler_onReady_ClientGeneration(this, p, ne);
}

void ServerNetworkHandler::disconnectClient(const NetworkIdentifier &id, const std::string &msg, bool s) {
    ServerNetworkHandler_disconnectClient(this, id, msg, s);
}

void ServerNetworkHandler::_displayGameMessage(const std::string &pref, const std::string &msg) {
    ServerNetworkHandler__displayGameMessage(this, pref, msg);
}

int ServerNetworkHandler::_getActivePlayerCount() {
    return ServerNetworkHandler__getActivePlayerCount(this);
}

ServerPlayer *ServerNetworkHandler::_getServerPlayer(const NetworkIdentifier &i) {
    return ServerNetworkHandler__getServerPlayer(this, i); //must use getPlayer, they are the same (?)
}

void ServerNetworkHandler::handleTextPacket(const NetworkIdentifier &ident, TextPacket &pk) {
    auto pl = _getServerPlayer(ident);
    if (pk.message.contains("§") && pl) {
        return pl->sendMessage("<§l§bAtmosphere§f'PE§r> §bВ чате §fнельзя использовать §bсимвол параграфа §fдля покраски сообщения§b.");
    } else if (pk.message == ".end") {
        auto pkk = TextPacket::createRaw("<§l§bAtmosphere§f'PE§r> §bПеренесен в §fЭНД");
        pl->changeDimension(2);
        return pl->getDimension()->sendPacketForEntity(*pl, *pkk, nullptr);
    } else if (pk.message == ".hell") {
        auto pkk = TextPacket::createRaw("<§l§bAtmosphere§f'PE§r> §bПеренесен в §fАД");
        pl->changeDimension(1);
        return pl->getDimension()->sendPacketForEntity(*pl, *pkk, nullptr);
    } else if (pk.message == ".def") {
        auto pkk = TextPacket::createRaw("<§l§bAtmosphere§f'PE§r> §bПеренесен в §fОБЫЧНЫЙ МИР");
        pl->changeDimension(0);
        return pl->getDimension()->sendPacketForEntity(*pl, *pkk, nullptr);
    } else if (pk.message == ".i") {
        return pl->sendInventory();
    }

    ServerNetworkHandler_handle_TextPacket(this, ident, pk);
}

void ServerNetworkHandler::setMaxPlayers(int count) {
    maxPlayersCount = count;
    updateServerAnnouncement();
}

void ServerNetworkHandler::updateServerAnnouncement() const {
    serverLocator->announceServer(serverMOTD, serverCore, 0, currentPlayerCount, maxPlayersCount); //0 - game type
}

void ServerNetworkHandler::handleUseItemPacket(const NetworkIdentifier &ident, UseItemPacket &pk) {
    if(!RegionGuard::handleUseItem(_getServerPlayer(ident), pk)) {
        return;
    }

    return ServerNetworkHandler_handle_UseItemPacket(this, ident, pk);
}

//1128 != 0
void ServerNetworkHandler::handleRemoveBlockPacket(const NetworkIdentifier &ident, RemoveBlockPacket &pk) {
    if(!RegionGuard::handleRemoveBlock(_getServerPlayer(ident), pk)) {
        return;
    }

    return ServerNetworkHandler_handle_RemoveBlockPacket(this, ident, pk);
}

void ServerNetworkHandler::handleMovePlayerPacket(const NetworkIdentifier &ident, MovePlayerPacket &pk) {
    return ServerNetworkHandler_handle_MovePlayerPacket(this, ident, pk);
}

void ServerNetworkHandler::handleCommandStepPacket(const NetworkIdentifier &ident, CommandStepPacket &pk) {
    std::cout << pk.inputJson << "\n";
    CustomCommands::handleStep(pk, _getServerPlayer(ident));
}

void ServerNetworkHandler::handleContainerSetSlotPacket(const NetworkIdentifier &ident, ContainerSetSlotPacket &pk) {
    //if(pk.item.count != 0)
    //    std::cout << pk.item.itemOrBlock->fullName << "\n";
    if(!AntiCheat::Item::onContainerSetSlotPacket(_getServerPlayer(ident), pk)) {
        return;
    }
    ServerNetworkHandler_handle_ContainerSetSlotPacket(this, ident, pk);
}

void ServerNetworkHandler::handleLoginPacket(const NetworkIdentifier &ident, LoginPacket &pk) {
    pk.req->verifySelfSigned();
    if(LoginChecks::checkOnLogin(&pk, ident))
        ServerNetworkHandler_handle_LoginPacket(this, ident, pk);
}

void ServerNetworkHandler::onDisconnect(const NetworkIdentifier &identifier, const std::string &reason, bool hide) {
    LoginChecks::checkOnDisconnect(identifier);
    Player::ipsHolder.erase(_getServerPlayer(identifier)->nickname);
    ServerNetworkHandler_onDisconnect(this, identifier, reason, hide);
}
