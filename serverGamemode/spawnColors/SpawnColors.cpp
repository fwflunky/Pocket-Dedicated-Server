//
// Created by user on 07.02.23.
//

#include <leveldb/db.h>
#include <iostream>
#include <thread>
#include <random>
#include "SpawnColors.h"
#include "range/v3/range.hpp"
#include "range/v3/view/split.hpp"
#include "../../server/statics.h"
#include "../../server/network/packets/UpdateBlockPacket.h"
#include "../../server/level/Level.h"
#include "../../server/level/BlockSource.h"
#include "../customCommands/CustomCommands.h"

void SpawnColors::initThreads() {
    std::thread([]() {
        sleep(5);
        while (true) {
            //  sleep(1);
            float x = spawnPos.x + 0.5;
            float y = spawnPos.y;
            float z = spawnPos.z + 0.5;
            statics::runOnNextTick([x, y, z]() {
                statics::serverNetworkHandler->mainLevel->addParticleCustom(31, 0, {x, y, z}); //change with dimanesion sendBroadcast leveleventpacket
            });

        }
    }).detach();
    CustomCommands::registerCommand("spawn", [&](ServerPlayer *player, nlohmann::json &input) -> bool {
        toSpawn(player);
        return true;
    });

    CustomCommands::registerCommand("rtp", [&](ServerPlayer *player, nlohmann::json &input) -> bool {
        tryRTP(player);
        return true;
    });
}

void SpawnColors::loadBlocks() {
    std::string in;
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    std::scoped_lock<std::mutex> lock(mux);

    leveldb::Status status = leveldb::DB::Open(options, scpath + "blocks", &db);
    if (status.ok())
        db->Get(leveldb::ReadOptions(), "blocks", &in);
    delete db;

    auto datas = in | ranges::views::split('|') | ranges::to<std::vector<std::string>>();
    for (auto &spos: datas) {
        auto xyz = spos | ranges::views::split(';') | ranges::to<std::vector<std::string>>();
        woolBlocks.emplace_back(std::stoi(xyz[0]), std::stoi(xyz[1]), std::stoi(xyz[2]));
    }
    std::cout << " SpawnColors: loaded " << woolBlocks.size() << " wool blocks\n";
}

void SpawnColors::saveBlocks() {
    std::string out;
    for (auto &bp: woolBlocks) {
        out += std::to_string(bp.x) + ";" + std::to_string(bp.y) + ";" + std::to_string(bp.z) + "|";
    }
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    std::scoped_lock<std::mutex> lock(mux);

    leveldb::Status status = leveldb::DB::Open(options, scpath + "blocks", &db);
    if (status.ok())
        db->Put(leveldb::WriteOptions(), "blocks", out);
    delete db;

    std::cout << " SpawnColors: saved " << woolBlocks.size() << " wool blocks\n";
}

void SpawnColors::scheduleAutoSave() {
    std::thread([]() {
        while (true) {
            sleep(1);
            SpawnColors::saveBlocks();
        }
    }).detach();
}

bool SpawnColors::tryRTP(ServerPlayer *p) {
    std::scoped_lock<std::mutex> lock(mux);

    if (p->getDimension()->dimensionId != 0) {
        p->sendMessage("<§l§bAtmosphere§f'PE§r> §bДля §fсовершения телепортации §bнужно находиться в §fобычном мире...");
        return false;
    } else if (rtpPrepares.contains(p->nickname)) {
        p->sendMessage("<§l§bAtmosphere§f'PE§r> §bПоиск §fточки телепортации §bуже начат, §fподождите...");
        return false;
    }

    p->sendMessage("<§l§bAtmosphere§f'PE§r> §bПоиск точки телепортации, §fподождите...");
    rtpPrepares.insert(p->nickname);

    std::thread([p, nick = p->nickname]() {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> dist6(-1000, 1000);

        Vec3 spos = {(float) dist6(rng), (float) 80, (float) dist6(rng)};

        LevelChunk *result = nullptr;
        for (int i = 0; i < 10 && !result; i++) {
            statics::runOnNextTick([spos, &result]() {
                result = statics::serverNetworkHandler->mainLevel->getDimension(0)->getChunkSource()->getOrLoadChunk(ChunkPos({spos.x, spos.y, spos.z}), 1);
            });
            usleep(100 * 500);
        }
        if (!result) {
            //failed
            rtpPrepares.erase(nick);
            return statics::runOnNextTick([p]() {
                if (!p)
                    return;
                p->sendMessage("<§l§bAtmosphere§f'PE§r> §bНе удалось найти §fточку телепортации§b. Попробуйте §fещё раз (1)");
            });
        }
        //todo check for load failed
        BlockSource blockSource(*statics::serverNetworkHandler->mainLevel, *statics::serverNetworkHandler->mainLevel->getDimension(0), *statics::serverNetworkHandler->mainLevel->getDimension(0)->getChunkSource(), false, true);
        int floorY = 250;
        for (int y = floorY; y > 1; y--) {
            if (blockSource.getBlock({(int) spos.x, y, (int) spos.z})->blockId != 0) {
                floorY = y;
                break;
            }
        }
        if (floorY == 250) {
            //failed
            rtpPrepares.erase(nick);
            return statics::runOnNextTick([p]() {
                if (!p)
                    return;
                p->sendMessage("<§l§bAtmosphere§f'PE§r> §bНе удалось найти §fточку телепортации§b. Попробуйте §fещё раз");
            });
        }
        spos.y = (float) floorY + 2;
        auto sendResult = false;
        for (int i = 0; i < 10 && !sendResult; i++) {
            statics::runOnNextTick([nick, spos, p, &sendResult]() {
                if (!p) {
                    rtpPrepares.erase(nick);
                    return;
                }

                sendResult = p->_sendQueuedChunk(ServerPlayer::QueuedChunk{
                        .dimensionId = 0,
                        .pos = ChunkPos({spos.x, spos.y, spos.z})
                });
            });
            usleep(1000 * 500);
        }

        rtpPrepares.erase(nick);
        if (!p)
            return;
        MovePlayerPacket mpk;
        mpk.entityRuntimeId = p->runtimeId;
        mpk.pos = spos;
        mpk.yawPitch = {0, 0};
        mpk.bodyYaw = 90;
        mpk.mode = 2;
        mpk.onGround = false;

        mpk.entityRuntimeId2 = 0;

        std::scoped_lock<std::mutex> lock(mux);
        statics::runOnNextTick([nick, mpk, spos, p]() {
            if (!p)
                return;
            p->teleportTo(spos, 0, 0);
            statics::serverNetworkHandler->networkHandler->send(p->identifier, mpk);
            p->sendMessage("<§l§bAtmosphere§f'PE§r> §bТелепортирован на §fточку случайной телепортации");
        });
    }).detach();
    return true;
}

bool SpawnColors::toSpawn(ServerPlayer *p) {
    std::scoped_lock<std::mutex> lock(mux);

    if (p->getDimension()->dimensionId != 0) {
        p->sendMessage("<§l§bAtmosphere§f'PE§r> §bДля §fсовершения телепортации §bнужно находиться в §fобычном мире...");
        return false;
    } else if (spawnPrepares.contains(p->nickname)) {
        p->sendMessage("<§l§bAtmosphere§f'PE§r> §bЗагрузка §fточки спавна §bуже начата, §fподождите...");
        return false;
    }

    p->sendMessage("<§l§bAtmosphere§f'PE§r> §bЗагрузка точки спавна, §fподождите...");
    spawnPrepares.insert(p->nickname);

    std::thread([p]() {
        Vec3 spos = {(float) SpawnColors::spawnPos.x, (float) SpawnColors::spawnPos.y, (float) SpawnColors::spawnPos.z};
        //pl->setPos(spos);

        if (!p)
            return;
        MovePlayerPacket mpk;
        mpk.entityRuntimeId = p->runtimeId;
        mpk.pos = spos;
        mpk.yawPitch = {0, 0};
        mpk.bodyYaw = 90;
        mpk.mode = 2;
        mpk.onGround = false;

        mpk.entityRuntimeId2 = 0;

        LevelChunk *result = nullptr;
        for (int i = 0; i < 10 && !result; i++) {
            statics::runOnNextTick([spos, p, &result]() {
                if (!p)
                    return;
                result = statics::serverNetworkHandler->mainLevel->getDimension(0)->getChunkSource()->getOrLoadChunk(ChunkPos({spos.x, spos.y, spos.z}), 1);
            });
            usleep(100 * 500);
        }
        if (!result) {
            //failed
            return statics::runOnNextTick([p]() {
                if (!p)
                    return;
                p->sendMessage("<§l§bAtmosphere§f'PE§r> §bНе удалось загрузить §fточку спавна§b. Попробуйте §fещё раз (1)");
            });
        }
        //todo check for load failed
        if (!p)
            return;
        auto sendResult = false;
        for (int i = 0; i < 10 && !sendResult; i++) {
            statics::runOnNextTick([spos, p, &sendResult]() {
                if (!p)
                    return;
                sendResult = p->_sendQueuedChunk(ServerPlayer::QueuedChunk{
                        .dimensionId = 0,
                        .pos = ChunkPos({spos.x, spos.y, spos.z})
                });
            });
            usleep(1000 * 500);
        }

        std::scoped_lock<std::mutex> lock(mux);
        statics::runOnNextTick([mpk, spos, p]() {
            if (!p)
                return;
            p->teleportTo(spos, 0, 0);
            statics::serverNetworkHandler->networkHandler->send(p->identifier, mpk);
            p->sendMessage("<§l§bAtmosphere§f'PE§r> §bТелепортирован на §fточку спавна");
            spawnPrepares.erase(p->nickname);
        });
    }).detach();
    return true;
}
