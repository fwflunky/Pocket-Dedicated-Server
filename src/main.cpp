#include <iostream>
#include <cstring>
#include <string>
#include "common.h"
#include "../serverRunner/Loader.h"

#include "../server/network/ServerNetworkHandler.h"
#include "../server/player/ServerPlayer.h"
#include "../server/player/Player.h"
#include "../server/player/inventory/Inventory.h"
#include "../server/player/inventory/Container.h"
#include "../server/player/inventory/PlayerInventoryProxy.h"
#include "../server/player/inventory/FillingContainer.h"
#include "../server/statics.h"
#include "../server/eventing/MinecraftEventing.h"
#include "../server/network/packets/TextPacket.h"
#include "../server/network/packets/UpdateBlockPacket.h"
#include "../server/network/packets/MinecraftPackets.h"
#include "../server/level/Dimension.h"
#include "../server/level/Level.h"
#include "../server/raknet/RakNetServerLocator.h"
#include "../server/gameMode/GameMode.h"
#include "../server/gameMode/SurvivalMode.h"
#include "../server/item/ItemInstance.h"
#include "../server/math/vec3/Vec3.h"
#include "../server/math/vec2/Vec2.h"
#include "../server/math/aabb/AABB.h"
#include "../server/level/BlockSource.h"
#include "../server/block/Block.h"
#include "../server/item/Item.h"
#include "../server/network/networkHandler/Connection.h"
#include "../server/network/packets/MovePlayerPacket.h"
#include "../server/network/packets/SetTitlePacket.h"
#include "../server/network/packets/TransferPacket.h"
#include "../server/network/connectionRequest/ConnectionRequest.h"
#include "../server/player/certificate/Certificate.h"
#include "../server/network/packets/ContainerSetSlotPacket.h"
#include "../server/network/networkHandler/NetworkHandler.h"
#include "../server/network/networkHandler/RakNetInstance.h"
#include "../server/network/networkHandler/RakPeer.h"
#include "../server/network/networkPeer/EncryptedNetworkPeer.h"
#include "../server/network/networkPeer/BatchedNetworkPeer.h"
#include "../server/MinecraftObjectLayer.h"
#include "../server/whitelist/Whitelist.h"
#include "../server/entity/SynchedEntityData.h"
#include "../server/entity/monster/Monster.h"
#include "../server/entity/classes/Arrow.h"
#include "../server/entity/classes/Wolf.h"
#include "../server/entity/teleportComponent/TeleportComponent.h"
#include "../server/entity/mob/Mob.h"
#include "../server/entity/mob/MobEffectInstance.h"
#include "../server/level/chunk/ChunkPos.h"
#include "../server/level/chunk/ChunkSource.h"
#include "../server/commands/CommandOrigin.h"
#include "../server/commands/CommandPropertyBag.h"
#include "../server/commands/Command.h"
#include "../server/commands/ServerCommands.h"
#include "../server/commands/MinecraftCommands.h"
#include "../server/commands/PlayerCommandOrigin.h"
#include "../server/components/explodeComponent/ExplodeComponent.h"
#include "../serverGamemode/regionGuard/RegionGuard.h"
#include "../serverGamemode/spawnColors/SpawnColors.h"
#include "../serverGamemode/tpa/Tpa.h"
#include "../serverGamemode/bans/Bans.h"

#include "android_symbols.h"
#include "egl_symbols.h"
#include "gles_symbols.h"
#include "fmod_symbols.h"
#include "../server/components/angryComponent/AngryComponent.h"
#include "hook.h"
#include "../serverGamemode/hotBar/HotBar.h"
#include "libm_symbols.h"

#define CWDD std::filesystem::current_path().string() + "/"
#include <filesystem>

extern "C" {
#include "../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../thirdParty/hybris/include/hybris/hook.h"
#include "../thirdParty/hybris/src/jb/linker.h"
}

void stubFunc() {
}

int main(int argc, char *argv[]) {
    if (sizeof(std::string("")) != 4) {
        throw std::invalid_argument("sizeof(std::string()) != 4, size = " + std::to_string(sizeof(std::string(""))));
        return 0;
    }
    registerCrashHandler();

    //auto glesLib = loadLibraryOS("libGLESv2.so", gles_symbols);
    //auto fmodLib = loadLibraryOS(getCWD() + "libs/native/libfmod.so.8.2", fmod_symbols);
    stubSymbols(android_symbols, (void *) stubFunc);
    stubSymbols(egl_symbols, (void *) stubFunc);
    stubSymbols(gles_symbols, (void *) stubFunc);
    stubSymbols(fmod_symbols, (void *) stubFunc);
    hybris_hook("eglGetProcAddress", (void *) stubFunc);
    hookAndroidLog();

    if (!load_empty_library("libc.so") || !load_empty_library("libstdc++.so") || !loadLibraryOS("libm.so", libm_symbols) || !load_empty_library("libz.so") || !load_empty_library("libm.so"))
        return -1;
    // load stub libraries
    if (!load_empty_library("libandroid.so") || !load_empty_library("liblog.so") || !load_empty_library("libEGL.so") || !load_empty_library("libGLESv2.so") || !load_empty_library("libOpenSLES.so") || !load_empty_library("libfmod.so") || !load_empty_library("libGLESv1_CM.so"))
        return -1;

    void *handle = hybris_dlopen((CWDD "libs/libminecraftpe.so").data(), RTLD_NOW);
    if (handle == nullptr) {
        std::cout << "failed to load MCPE: " << hybris_dlerror() << "\n";
        return -1;
    }

    addHookLibrary(handle, CWDD "libs/libminecraftpe.so");
    //unsigned int libBase = ((soinfo *) handle)->base;
    //std::cout << "loaded MCPE (at " << libBase << ")\n";

    for(auto& fn : Loader::callOnLoad){
        fn(handle);
    }
    NetworkIdentifier::initHooks(handle);
    ServerNetworkHandler::initHooks(handle);
    Entity::initHooks(handle);
    Player::initHooks(handle);
    Inventory::initHooks(handle);
    PlayerInventoryProxy::initHooks(handle);
    FillingContainer::initHooks(handle);
    Vec3::initHooks(handle);
    Vec2::initHooks(handle);
    ServerPlayer::initHooks(handle);
    Container::initHooks(handle);
    SetTitlePacket::initHooks(handle);
    MinecraftEventing::initHooks(handle);
    Dimension::initHooks(handle);
    Level::initHooks(handle);
    TeleportComponent::initHooks(handle);
    RakNetServerLocator::initHooks(handle);
    GameMode::initHooks(handle);
    ItemInstance::initHooks(handle);
    BlockSource::initHooks(handle);
    AngryComponent::initHooks(handle);
    RakNetInstance::initHooks(handle);
    Bans::init();
    RakPeer::initHooks(handle);
    Wolf::initHooks(handle);
    Block::initHooks(handle);
    Item::initHooks(handle);
    MinecraftPackets::initHooks(handle);
    NetworkHandler::Connection::initHooks(handle);
    NetworkHandler::NetworkHandler::initHooks(handle);
    MinecraftObjectLayer::initHooks(handle);
    BatchedNetworkPeer::initHooks(handle);
    MovePlayerPacket::initHooks(handle);
    Certificate::initHooks(handle);
    Whitelist::initHooks(handle);
    SynchedEntityData::initHooks(handle);
    Mob::initHooks(handle);
    Monster::initHooks(handle);
    AABB::initHooks(handle);
    ChunkPos::initHooks(handle);
    ChunkSource::initHooks(handle);

    TextPacket::initHooks(handle);
    UpdateBlockPacket::initHooks(handle);
    ExplodeComponent::initHooks(handle);
    MinecraftCommands::initHooks(handle);
    CommandPropertyBag::initHooks(handle);
    CommandOrigin::initHooks(handle);
    Command::initHooks(handle);
    PlayerCommandOrigin::initHooks(handle);
    ServerCommands::initHooks(handle);
    ConnectionRequest::initHooks(handle);
    TransferPacket::initHooks(handle);
    ContainerSetSlotPacket::initHooks(handle);
    Arrow::initHooks(handle);
    MobEffectInstance::initHooks(handle);

    RegionGuard::loadAllUsers();
    RegionGuard::scheduleAutoSave();
    HotBar::scheduleUpdate();
    //SpawnColors::loadBlocks();
    SpawnColors::initThreads();
    Tpa::init();

    Loader::load(handle);
    sleep(2);
    return 0;
}
