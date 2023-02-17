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
#include "../server/item/FlintAndSteelItem.h"
#include "../server/math/vec3/Vec3.h"
#include "../server/math/vec2/Vec2.h"
#include "../server/math/aabb/AABB.h"
#include "../server/level/BlockSource.h"
#include "../server/block/Block.h"
#include "../server/item/Item.h"
#include "../server/network/networkHandler/Connection.h"
#include "../server/network/packets/MovePlayerPacket.h"
#include "../server/network/packets/SetTitlePacket.h"
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
#include "../server/level/explodeComponent/ExplodeComponent.h"
#include "../serverGamemode/regionGuard/RegionGuard.h"
#include "../serverGamemode/spawnColors/SpawnColors.h"
#include "../serverGamemode/tpa/Tpa.h"
#include "../serverGamemode/bans/Bans.h"

#include "android_symbols.h"
#include "egl_symbols.h"
#include "gles_symbols.h"
#include "fmod_symbols.h"

#include <sys/mman.h>
#include <EGL/egl.h>

extern "C" {
#include "../hybris/include/hybris/dlfcn.h"
#include "../hybris/include/hybris/hook.h"
#include "../hybris/src/jb/linker.h"
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

    if (!loadLibrary("libc.so") || !loadLibrary("libstdc++.so") || !loadLibrary("libm.so") || !loadLibrary("libz.so"))
        return -1;
    // load stub libraries
    if (!loadLibrary("libandroid.so") || !loadLibrary("liblog.so") || !loadLibrary("libEGL.so") || !loadLibrary("libGLESv2.so") || !loadLibrary("libOpenSLES.so") || !loadLibrary("libfmod.so") || !loadLibrary("libGLESv1_CM.so"))
        return -1;

    // if (glesLib == nullptr || fmodLib == nullptr)
    //    return -1;
    // std::cout << "loading MCPE\n";
    void *handle = hybris_dlopen(CWDD "libs/libminecraftpe0.so", RTLD_NOW);
    if (handle == nullptr) {
        std::cout << "failed to load MCPE: " << hybris_dlerror() << "\n";
        return -1;
    }

    addHookLibrary(handle, CWDD "libs/libminecraftpe0.so");
    //unsigned int libBase = ((soinfo *) handle)->base;
    //std::cout << "loaded MCPE (at " << libBase << ")\n";

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
    FlintAndSteelItem::initHooks(handle);
    BlockSource::initHooks(handle);
    RakNetInstance::initHooks(handle);
    Bans::init();
    RakPeer::initHooks(handle);
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
    ContainerSetSlotPacket::initHooks(handle);
    Arrow::initHooks(handle);
    MobEffectInstance::initHooks(handle);

    RegionGuard::loadAllUsers();
    RegionGuard::scheduleAutoSave();
    //SpawnColors::loadBlocks();
    SpawnColors::initThreads();
    Tpa::init();

    Loader::load(handle);
    sleep(3);
    return 0;
}
