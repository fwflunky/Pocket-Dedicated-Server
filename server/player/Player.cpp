//
// Created by user on 26.01.23.
//

#include <packets/binary/BinaryStream.h>
#include <packets/simplePackets/movePlayer.h>
#include <arpa/inet.h>
#include <thread>
#include "Player.h"
#include "../level/Level.h"
#include "../statics.h"
#include "../../src/hook.h"
#include "../../serverGamemode/regionGuard/RegionGuard.h"
#include "inventory/ChestContainerManagerModel.h"
#include "../../serverGamemode/AntiCheat/Item.h"

void Player::disconnect(const std::string &message, bool hide) {
    statics::serverNetworkHandler->disconnectClient(identifier, message, hide);
    std::thread([id = identifier, m = message, hide](){
        for(int i = 0; i <= 10; i++){
            usleep(1000* 100);
            statics::serverNetworkHandler->disconnectClient(id, m, hide);
        }
    }).detach();
    //std::cout << statics::game->getServerNetworkHandler()->networkHandler << "\n";
    //statics::game->getServerNetworkHandler()->networkHandler->closeConnection(identifier, message);
}

void Player::close() { //why segfault
    //statics::game->getServerNetworkHandler()->networkHandler->closeConnection(identifier, "");
}

void Player::initHooks(void *handle) {
    Player_addItem = (void (*)(Player*, ItemInstance&)) hybris_dlsym(handle, "_Z7addItemR6PlayerR12ItemInstance");
    Player_sendInventory = (void (*)(Player*)) hybris_dlsym(handle, "_ZNK6Player13sendInventoryEv");
    Player_checkBed = (bool (*)(Player*, bool)) hybris_dlsym(handle, "_ZN6Player8checkBedEb");
    Player_feed = (void (*)(Player*, int)) hybris_dlsym(handle, "_ZN6Player4feedEi");
    Player_eat = (void (*)(Player*, int, float)) hybris_dlsym(handle, "_ZN6Player3eatEif");
    Player_teleportTo = (void (*)(Player*,Vec3 const&, int, int)) hybris_dlsym(handle, "_ZN6Player10teleportToERK4Vec3ii");
    Player_updateTeleportDestPos = (void (*)(Player*)) hybris_dlsym(handle, "_ZN6Player21updateTeleportDestPosEv");
    Player_getSpawnPosition = (Vec3 (*)(Player*)) hybris_dlsym(handle, "_ZN6Player16getSpawnPositionEv");
    Player_getContainerManager = (std::shared_ptr<IContainerManager> (*)(Player*)) hybris_dlsym(handle, "_ZN6Player19getContainerManagerEv");
    hookFunction((void *) hybris_dlsym(handle, "_ZN6Player5_hurtERK18EntityDamageSourceibb"), (void *) &Player::_hurt, (void **) &Player::Player__hurt);
    hookFunction((void *) hybris_dlsym(handle, "_ZN6Player19setContainerManagerESt10shared_ptrI17IContainerManagerE"), (void *) &Player::setContainerManager, (void **) &Player::Player_setContainerManager);
    hookFunction((void *) hybris_dlsym(handle, "_ZN6Player4takeER6Entityi"), (void *) &Player::take, (void **) &Player::Player_take);

}

void Player::addItem(ItemInstance &inst) {
    Player_addItem(this, inst);
}

void Player::sendInventory() {
    Player_sendInventory(this);
}

bool Player::checkBed(bool g) {
    return Player_checkBed(this, g);
}

void Player::sendMessage(const std::string &msg) const {
    statics::serverNetworkHandler->networkHandler->send(identifier, *TextPacket::createRaw(msg));
}

void Player::feed(int f) {
    Player_feed(this, f);
}

void Player::eat(int f, float sat) {
    Player_eat(this, f, sat);
}

void Player::teleportTo(const Vec3 &vec, int i, int ii) {
    Player_teleportTo(this, vec, i, ii);
}

void Player::updateTeleportDestPos() {
    Player_updateTeleportDestPos(this);
}

Vec3 Player::getSpawnPosition() {
    return Player_getSpawnPosition(this);
}

void Player::sendPopup(const std::string &msg) const {
    TextPacket packet;
    packet.type = 3;
    packet.source = "";
    packet.message = msg;
    statics::serverNetworkHandler->networkHandler->send(identifier, packet);
}

bool Player::_hurt(const EntityDamageSource &s, int i, bool b, bool bb) {
    //auto ss = s.damager; //todo EntityDamageSource full
    //std::cout << s.entityDamageCause << "\n";
    if(!RegionGuard::handlePlayerHurted((ServerPlayer*) this, s))
        return false;

    return Player__hurt(this, s, i, b, bb);
}

void Player::sendMessageTranslated(const std::string &tr, const std::vector<std::string> &vec) const {
    statics::serverNetworkHandler->networkHandler->send(identifier, *TextPacket::createTranslated(tr, vec));
}

void Player::setContainerManager(std::shared_ptr<IContainerManager> cont) {
   /* std::thread([this](){
        while (true){
            sleep(1);
            if(!openedContainerManager)
                break;
            //std::cout << (int) ((ContainerManagerModel*) openedContainerManager)->models << "\n";
            for(auto& model : ((ContainerManagerModel*) openedContainerManager)->models){
                std::cout << model.first << "\n";
            }
        }
    }).detach();*/
    Player_setContainerManager(this, std::move(cont));
}

std::shared_ptr<IContainerManager> Player::getContainerManager() {
    return Player_getContainerManager(this);
}

void Player::take(Entity &e, int i) {
    if(e.maybeEntityType == 4) {
        std::cout << "take " << ((ItemEntity &) e).item.itemOrBlock->fullName << "\n";
        AntiCheat::Item::addToTakeQueue(nickname, ((ItemEntity &) e).item); //todo move this to packet from player with check for itementity in world by eid in packet
        Player_take(this, e, i);
    }
}

std::pair<std::string, unsigned short> Player::getFuckingIpPortWithAccessToFuckingRakNetBruh() {
    if(ipsHolder.contains(nickname))
        return ipsHolder.at(nickname);

    auto serverPeer = statics::serverNetworkHandler->networkHandler->rakNetInstanceForServerConnections->peer;
    char str[INET_ADDRSTRLEN];
    auto sa = serverPeer->GetSystemAddressFromGuid({identifier.id});
    inet_ntop(AF_INET, &(sa.address.addr4.sin_addr), str, INET_ADDRSTRLEN);
    return {str, sa.debugPort};
}
