cmake_minimum_required(VERSION 2.8)
project(pdserver)

enable_language(C)

find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)

add_compile_definitions(PDSVER="1.7" SPDLOG_COMPILED_LIB)
include_directories(thirdParty/jsoncpp-1.8.1/include)
include_directories(thirdParty/range-v3/include)
include_directories(thirdParty/leveldb/include)
include_directories(thirdParty/spdlog-1.x/include)
include_directories(thirdParty/nlohmann/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-pmf-conversions -std=c++23 -D_GLIBCXX_USE_CXX11_ABI=0")

set(HYBRIS_SOURCES thirdParty/hybris/src/strlcpy.c thirdParty/hybris/src/cache.c thirdParty/hybris/src/dlfcn.c thirdParty/hybris/src/hooks.c thirdParty/hybris/src/hooks_shm.c thirdParty/hybris/src/logging.c thirdParty/hybris/src/properties.c thirdParty/hybris/src/ctype.c thirdParty/hybris/src/sysconf.c thirdParty/hybris/src/jb/dlfcn.c thirdParty/hybris/src/jb/linker.c thirdParty/hybris/src/jb/linker_environ.c thirdParty/hybris/src/jb/linker_format.c thirdParty/hybris/src/jb/rt.c thirdParty/hybris/src/hooks_pthread.c thirdParty/hybris/src/hooks_dirent.c thirdParty/hybris/src/hooks_io.c thirdParty/hybris/src/hooks_net.c)
set(LIBJSON_SOURCES thirdParty/jsoncpp-1.8.1/src/lib_json/json_reader.cpp thirdParty/jsoncpp-1.8.1/src/lib_json/json_value.cpp thirdParty/jsoncpp-1.8.1/src/lib_json/json_writer.cpp)
set(SPDLOG_SOURCES thirdParty/spdlog-1.x/src/async.cpp thirdParty/spdlog-1.x/src/bundled_fmtlib_format.cpp thirdParty/spdlog-1.x/src/cfg.cpp thirdParty/spdlog-1.x/src/color_sinks.cpp thirdParty/spdlog-1.x/src/file_sinks.cpp thirdParty/spdlog-1.x/src/spdlog.cpp thirdParty/spdlog-1.x/src/stdout_sinks.cpp)

set(SOURCE_FILES
        server/util/storage/DBStorage.cpp
        server/util/storage/LevelStorage.cpp
        server/entity/classes/Wolf.cpp
        server/entity/animal/Animal.cpp
        serverGamemode/petHelper/Wolf.cpp
        serverRunner/resourcePack/ResourcePackStack.cpp
        serverRunner/config/Config.cpp
        serverRunner/minecraftGame/Minecraft.cpp
        serverRunner/scheduler/Scheduler.cpp
        serverRunner/uuid/UUID.cpp
        serverRunner/ServerInstance.cpp
        serverRunner/userManager/UserManager.cpp
        serverRunner/entitlement/EntitlementManager.cpp
        serverRunner/resourcePack/ResourcePackRepository.cpp
        serverRunner/resourcePack/PackManifestFactory.cpp
        serverRunner/resourcePack/ResourcePackManager.cpp
        serverRunner/filePathManager/FilePathManager.cpp
        serverRunner/Loader.cpp
        serverRunner/level/LevelSettings.cpp
        serverRunner/minecraftGame/DedicatedMinecraftApp.cpp
        server/network/packets/UseItemPacket.cpp
        server/network/packets/LoginPacket.cpp
        server/network/connectionRequest/ConnectionRequest.cpp
        server/player/certificate/Certificate.cpp
        serverGamemode/loginChecks/LoginChecks.cpp
        server/network/networkHandler/RakPeer.cpp
        server/network/networkHandler/RakNetInstance.cpp
        serverGamemode/bans/Bans.cpp
        server/player/inventory/LevelContainerModel.cpp
        server/player/inventory/ContainerManagerController.cpp
        serverGamemode/AntiCheat/Item.cpp
        server/network/packets/ContainerSetSlotPacket.cpp
        server/network/packets/MovePlayerPacket.cpp
        serverGamemode/tpa/Tpa.cpp
        serverGamemode/customCommands/CustomCommands.cpp
        server/entity/mob/MobEffectInstance.cpp
        server/network/packets/SetTitlePacket.cpp
        serverGamemode/enderChestBonus/EnderChestBonus.cpp
        server/player/inventory/Container.cpp
        server/player/inventory/EnderChestContainer.cpp
        server/entity/classes/Arrow.cpp
        serverGamemode/spawnColors/SpawnColors.cpp
        server/commands/ServerCommands.cpp
        server/commands/Command.cpp
        server/commands/PlayerCommandOrigin.cpp
        server/commands/CommandOrigin.cpp
        server/commands/CommandPropertyBag.cpp
        server/commands/MinecraftCommands.cpp
        server/network/packets/TransferPacket.cpp
        server/entity/monster/Monster.cpp
        server/level/LevelListener.cpp
        server/level/BlockSourceListener.cpp
        server/components/angryComponent/AngryComponent.cpp
        server/components/explodeComponent/ExplodeComponent.cpp
        server/network/packets/UpdateBlockPacket.cpp
        server/network/packets/TextPacket.cpp
        server/level/chunk/ChunkPos.cpp
        server/level/chunk/ChunkSource.cpp
        server/level/chunk/LevelChunk.cpp
        server/entity/teleportComponent/TeleportComponent.cpp
        server/math/aabb/AABB.cpp
        serverGamemode/regionGuard/RegionGuard.cpp
        serverGamemode/regionGuard/Region.cpp
        server/entity/damageSource/EntityDamageSource.cpp
        server/entity/mob/Mob.cpp
        server/entity/SynchedEntityData.cpp
        server/whitelist/Whitelist.cpp
        server/MinecraftObjectLayer.cpp
        server/player/inventory/InventoryFixer.cpp
        server/network/networkPeer/CompressedNetworkPeer.cpp
        server/network/networkPeer/BatchedNetworkPeer.cpp
        server/network/networkPeer/NetworkPeer.cpp
        server/network/networkPeer/EncryptedNetworkPeer.cpp
        server/network/networkHandler/Connection.cpp
        server/network/networkHandler/NetworkHandler.cpp
        server/network/packets/MinecraftPackets.cpp
        server/block/Block.cpp
        server/level/BlockSource.cpp
        server/player/inventory/FillingContainer.cpp
        server/player/inventory/PlayerInventoryProxy.cpp
        server/math/vec2/Vec2.cpp
        server/player/inventory/Inventory.cpp
        server/item/Item.cpp
        server/item/blockItem/BlockItem.cpp
        server/item/ItemInstance.cpp
        server/level/BlockPos.cpp
        server/gameMode/GameMode.cpp
        server/gameMode/SurvivalMode.cpp
        server/math/vec3/Vec3.cpp
        server/raknet/RakNetServerLocator.cpp
        server/level/Dimension.cpp
        server/eventing/MinecraftEventing.cpp
        server/statics.cpp
        server/network/ServerNetworkHandler.cpp
        server/player/ServerPlayer.cpp
        server/level/Level.cpp
        server/network/NetworkIdentifier.cpp
        server/player/Player.cpp
        server/entity/Entity.cpp
        serverRunner/minecraftGame/api/Api.cpp
        src/main.cpp
        src/common.cpp
        src/hook.cpp
        serverRunner/appPlatform/LinuxAppPlatform.cpp serverGamemode/hotBar/HotBar.cpp serverGamemode/hotBar/HotBar.h serverGamemode/customPermissions/CustomPermissions.cpp serverGamemode/customPermissions/CustomPermissions.h)

add_executable(pdserver ${LIBJSON_SOURCES} ${SPDLOG_SOURCES} ${HYBRIS_SOURCES} ${SOURCE_FILES})
target_link_libraries(pdserver ${CMAKE_DL_LIBS} ${CMAKE_THREAD_LIBS_INIT} rt ${CMAKE_SOURCE_DIR}/thirdParty/leveldb/build/libleveldb.a uuid /usr/lib32/libcrypto.so /usr/lib32/libssl.so)
target_compile_definitions(pdserver PRIVATE ANDROID_X86_LINKER _GNU_SOURCE LINKER_TEXT_BASE=0xB0000100 LINKER_AREA_SIZE=0x01000000 LINKER_DEBUG=1)
set_target_properties(pdserver PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
