//
// Created by user on 01.02.23.
//

#include <cmath>
#include "RegionGuard.h"
#include <leveldb/db.h>
#include <filesystem>
#include <thread>
#include "range/v3/range.hpp"
#include "range/v3/view/split.hpp"
#include "../customCommands/CustomCommands.h"
#include "../../server/network/packets/UpdateBlockPacket.h"
#include "../../server/statics.h"
#include "../server/level/BlockSource.h"
#define spath std::string("/home/user/Видео/mcpelauncher-linux-2ebee1b9a70479685a4c430370c3fdfa47988b54/serverGamemode/storage/regionGuard/")
Region *RegionGuard::getRegion(const std::string &nick) {
    std::scoped_lock<std::mutex> lock(mux);
    if(!playerRegions.contains(nick))
        return nullptr;
    return playerRegions.at(nick);
}

bool RegionGuard::makeRegion(const std::string &nick,const std::string &region, const AABB& a, int dimId) {
    std::scoped_lock<std::mutex> lock(mux);
    if(playerRegions.contains(nick))
        return false;
    playerRegions.insert({nick, new Region(nick, region, a, dimId)});
    return true;
}

Region *RegionGuard::getRegionWhereVec(int dim, const Vec3 &v) {
    std::scoped_lock<std::mutex> lock(mux);
    for(const auto& reg : playerRegions){
        if(reg.second->dimensionId == dim && reg.second->box.contains(v)) {
            return reg.second;
        }
    }
    return nullptr;
}

std::vector<Vec3> RegionGuard::getHollowCube(const Vec3 &start, const Vec3 &end) {
    std::vector<Vec3> out;

    int minX = std::floor(std::min(start.x, end.x));
    int minY = std::floor(std::min(start.y, end.y));
    int minZ = std::floor(std::min(start.z, end.z));

    int maxX = std::floor(std::max(start.x, end.x));
    int maxY = std::floor(std::max(start.y, end.y));
    int maxZ = std::floor(std::max(start.z, end.z));

    for(int x = minX; x <= maxX; x++) {
        for(int y = minY; y <= maxY; y++) {
            for(int z = minZ; z <= maxZ; z++) {
                int comp = 0;
                if(x == minX || x == maxX) comp++;
                if(y == minY || y == maxY) comp++;
                if(z == minZ || z == maxZ) comp++;
                if(comp >= 2) {
                    out.emplace_back((float) x, (float) y,(float) z);
                }
            }
        }
    }
    return out;
}

void RegionGuard::loadAllUsers() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    std::scoped_lock<std::mutex> lock(mux);

    for (const auto & entry : std::filesystem::directory_iterator(spath)) {
        std::string path = entry.path();
        leveldb::Status status = leveldb::DB::Open(options,entry.path(), &db);
        if(status.ok()){
            std::string ownerName;
            std::string dimensionId;
            std::string boxString;
            std::string membersString;
            std::string monstersAllowed;
            std::string explodesAllowed;
            std::string pvPAllowed;
            std::string pvEAllowed;

            std::string enderChestAccess;
            std::string chestAccess;
            std::string furnaceAccess;
            std::string boatPlaceOnWaterAllowed;
            std::string breweryAccess;

            db->Get(leveldb::ReadOptions(), "ownerName", &ownerName);
            db->Get(leveldb::ReadOptions(), "dimensionId", &dimensionId);
            db->Get(leveldb::ReadOptions(), "boxString", &boxString);
            db->Get(leveldb::ReadOptions(), "membersString", &membersString);
            db->Get(leveldb::ReadOptions(), "monstersAllowed", &monstersAllowed);
            db->Get(leveldb::ReadOptions(), "explodesAllowed", &explodesAllowed);
            db->Get(leveldb::ReadOptions(), "pvPAllowed", &pvPAllowed);
            db->Get(leveldb::ReadOptions(), "pvEAllowed", &pvEAllowed);

            db->Get(leveldb::ReadOptions(), "enderChestAccess", &enderChestAccess);
            db->Get(leveldb::ReadOptions(), "chestAccess", &chestAccess);
            db->Get(leveldb::ReadOptions(), "furnaceAccess", &furnaceAccess);
            db->Get(leveldb::ReadOptions(), "boatPlaceOnWaterAllowed", &boatPlaceOnWaterAllowed);
            db->Get(leveldb::ReadOptions(), "breweryAccess", &breweryAccess);

            AABB aabb;
            if(aabb.fromString(boxString)){
                auto members = membersString | ranges::views::split(';') | ranges::to<std::set<std::string>>();
                auto pathsl = path | ranges::views::split('/') | ranges::to<std::vector<std::string>>();
                auto rg = new Region(ownerName, pathsl[pathsl.size()-1], aabb, std::stoi(dimensionId));
                rg->memberNames = members;
                rg->monstersAllowed = monstersAllowed == "1";
                rg->explodesAllowed = explodesAllowed == "1";
                rg->pvPAllowed = pvPAllowed == "1";
                rg->pvEAllowed = pvEAllowed == "1";
                rg->enderChestAccess = enderChestAccess == "1";
                rg->chestAccess = chestAccess == "1";
                rg->furnaceAccess = furnaceAccess == "1";
                rg->breweryAccess = breweryAccess == "1";
                rg->boatPlaceOnWaterAllowed = boatPlaceOnWaterAllowed == "1";
                playerRegions.insert({ownerName, rg});
                std::cout << "loaded region " << pathsl[pathsl.size()-1] << "\n";
            }
        }
        delete db;
        db = nullptr;
    }

    initCommands();
}

void RegionGuard::saveAllUsers() {
    leveldb::DB* db;
    leveldb::Options options;
    options.create_if_missing = true;
    std::scoped_lock<std::mutex> lock(mux);

    for(const auto& reg : playerRegions) {
        leveldb::Status status = leveldb::DB::Open(options, spath +reg.second->regionName, &db);
        if(status.ok()){
            db->Put(leveldb::WriteOptions(), "ownerName", reg.second->ownerName);
            db->Put(leveldb::WriteOptions(), "dimensionId", std::to_string(reg.second->dimensionId));
            db->Put(leveldb::WriteOptions(), "boxString", reg.second->box.toString());
            std::string membersString;
            for(auto& mem : reg.second->memberNames)
                membersString += mem + ";";

            db->Put(leveldb::WriteOptions(), "membersString", membersString);
            db->Put(leveldb::WriteOptions(), "monstersAllowed", reg.second->monstersAllowed ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "explodesAllowed", reg.second->explodesAllowed ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "pvPAllowed", reg.second->pvPAllowed ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "pvEAllowed", reg.second->pvEAllowed ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "enderChestAccess", reg.second->enderChestAccess ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "chestAccess", reg.second->chestAccess ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "furnaceAccess", reg.second->furnaceAccess ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "boatPlaceOnWaterAllowed", reg.second->boatPlaceOnWaterAllowed ? "1" : "0");
            db->Put(leveldb::WriteOptions(), "breweryAccess", reg.second->breweryAccess ? "1" : "0");
        }
        delete db;
        db = nullptr;
    }
}

void RegionGuard::scheduleAutoSave() {
    std::thread([](){
        while(true){
            sleep(1);
            RegionGuard::saveAllUsers();
        }
    }).detach();
}

void RegionGuard::initCommands() {
    CustomCommands::registerCommand("rg pos", [&](ServerPlayer* player, nlohmann::json& input) -> bool {
        if (RegionGuard::getRegion(player->nickname)) {
            player->sendMessage("У Вас уже есть регион.");
            return true;
        }
        if (!RegionGuard::tempCreations.contains(player->nickname))
            RegionGuard::tempCreations.insert({player->nickname, RegionGuard::tempCreation{0, *Vec3::ZERO, *Vec3::ZERO, player->nickname + "-s region"}});

        auto& tmp = RegionGuard::tempCreations.at(player->nickname); //todo clear on disconnect
        handleStage(player, tmp);
        return true;
    });

    CustomCommands::registerCommand("rg flag", [&](ServerPlayer* player, nlohmann::json& input) -> bool {
        auto reg = RegionGuard::getRegion(player->nickname);
        if (!reg) {
            player->sendMessage("У Вас нет региона.");
            return true;
        }

        try {
            auto flag = input["flag"].get<std::string >();
            auto value = input["value"].get<bool>();

            if(flag == "all"){
                reg->pvPAllowed = value;
                reg->pvEAllowed = value;
                reg->monstersAllowed = value;
                reg->explodesAllowed = value;
                reg->enderChestAccess = value;
                reg->chestAccess = value;
                reg->furnaceAccess = value;
                reg->breweryAccess = value;
                reg->boatPlaceOnWaterAllowed = value;
                player->sendMessage("Все флаги установлены на " + (value ? std::string("разрешено") : "запрещено") + ".");
            } else if(flag == "pvp") {
                reg->pvPAllowed = value;
                player->sendMessage("pvPAllowed установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
            } else if(flag == "pve") {
                reg->pvEAllowed = value;
                player->sendMessage("pvEAllowed установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
            } else if(flag == "explodes") {
                reg->explodesAllowed = value;
                player->sendMessage("explodesAllowed установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
            } else if(flag == "echest") {
                reg->enderChestAccess = value;
                player->sendMessage("enderChestAccess установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
            } else if(flag == "chest") {
                reg->chestAccess = value;
                player->sendMessage("chestAccess установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
            } else if(flag == "furnace") {
                reg->furnaceAccess = value;
                player->sendMessage("furnaceAccess установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
              } else if(flag == "boatwater") {
                reg->boatPlaceOnWaterAllowed = value;
                player->sendMessage("boatPlaceOnWaterAllowed установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
             } else if(flag == "brewery") {
                reg->breweryAccess = value;
                player->sendMessage("breweryAccess установлен на " + (value ? std::string("разрешено") : "запрещено") + ".");
            } else {
                player->sendMessage("§cUnimplemented flag \"" + flag+"\"");
            }

        } catch(...){
            player->sendMessageTranslated("§c%commands.generic.exception", {});
            return true;
        }
        return true;
    });
}

void RegionGuard::handleStage(ServerPlayer *player, RegionGuard::tempCreation& stage) {
    if(stage.stage == 0){
        stage.start = {player->x, player->y - 2, player->z};
        stage.stage++;
        player->sendMessage("Позиция §l#1§r установлена. Перейдите на позицию §l#2§r и напишите команду §l/rg pos§r еще раз.");

        UpdateBlockPacket packet;
        packet.x = std::floor(stage.start.x);
        packet.y = std::floor(stage.start.y);
        packet.z = std::floor(stage.start.z);
        packet.blockId = 35;
        packet.blockData = 5;
        packet.flags = ((0b0001 | 0b0010) << 4);
        statics::serverNetworkHandler->networkHandler->send(player->identifier, packet);
    } else if(stage.stage == 1){
        stage.end = {player->x, player->y - 2, player->z};

        AABB fblock({stage.start.x, stage.start.y, stage.start.z}, {stage.start.x + 1, stage.start.y + 1, stage.start.z + 1});
        if(std::abs(fblock.distanceTo({{stage.end.x, stage.end.y, stage.end.z}, {stage.end.x + 1, stage.end.y + 1, stage.end.z + 1}})) > 30) {
            player->sendMessage("Выбрана слишком большая территория. Допускается местность не больше §l30 блоков§r. Попробуйте еще раз написать команду §l/rg pos§r, но уже выбрав местность меньше.");
           return player->sendMessage("Начинайте со §lвторой точки, §rпервая точка §lне была сброшена.");
        } else if(std::abs(fblock.distanceTo({{stage.end.x, stage.end.y, stage.end.z}, {stage.end.x + 1, stage.end.y + 1, stage.end.z + 1}})) < 3) {
            player->sendMessage("Выбрана слишком маленькая территория. Допускается местность не больше §l30 блоков§r. Попробуйте еще раз написать команду §l/rg pos§r, но уже выбрав местность больше.");
            return player->sendMessage("Начинайте со §lвторой точки, §rпервая точка §lне была сброшена.");
        }

        //todo threaded
        AABB aabb(stage.start, stage.end);
        {
            std::scoped_lock<std::mutex> lock(mux);
            for (const auto &reg: playerRegions) {
                if (reg.second->box.intersects(aabb)) {
                    player->sendMessage("Выбранная территория пересекает территорию \"" + reg.second->regionName + "\"");
                    stage.stage = 0;
                    return player->sendMessage("Прогресс сброшен. Начните снова");
                }
            }
        }

        RegionGuard::makeRegion(player->nickname, stage.name, aabb, player->getDimension()->dimensionId);

        player->sendMessage("Позиция §l#2§r установлена. §lРегион создан§r, отмечаю его в мире...");
        UpdateBlockPacket packet;
        packet.x = std::floor(stage.end.x);
        packet.y = std::floor(stage.end.y);
        packet.z = std::floor(stage.end.z);
        packet.blockId = 35;
        packet.blockData = 14;
        packet.flags = ((0b0001 | 0b0010) << 4);
        statics::serverNetworkHandler->networkHandler->send(player->identifier, packet);

        startThreadedDraw(player, stage);
    }
}

void RegionGuard::startThreadedDraw(ServerPlayer *player, RegionGuard::tempCreation &stage) {
    std::thread([tstage = stage, id = player->identifier,
                 nick = player->nickname,
                 bs = BlockSource(*player->getLevel(), *player->getDimension(), *player->playerChunkSource, false, true)]() {
        tempCreations.erase(nick);

        auto hollow = RegionGuard::getHollowCube(tstage.start, tstage.end);
        int blockCounter = 0;
        int woolColor = 2; //3
        for (int i = 0; i < 3; i++) {
            auto mstimeForBlock = hollow.size() / (hollow.size() / 3);
            for (auto &pos: hollow) {
                usleep(1000 * mstimeForBlock);
                UpdateBlockPacket packet;
                packet.x = std::floor(pos.x);
                packet.y = std::floor(pos.y);
                packet.z = std::floor(pos.z);
                packet.blockId = 35;
                packet.blockData = woolColor;
                packet.flags = ((0b0001 | 0b0010) << 4);

                blockCounter++;
                if (blockCounter > 3) {
                    blockCounter = 0;
                    if (woolColor == 2)
                        woolColor = 3;
                    else
                        woolColor = 2;
                }

                statics::serverNetworkHandler->networkHandler->send(id, packet);
            }
            for (auto &pos: hollow) {
                usleep(1000 * mstimeForBlock);

                auto& bsHack = (BlockSource&) bs;
                auto bld = bsHack.getBlockAndData({pos.x, pos.y, pos.z});
                UpdateBlockPacket packet;
                packet.x = std::floor(pos.x);
                packet.y = std::floor(pos.y);
                packet.z = std::floor(pos.z);
                packet.blockId = bld.id;
                packet.blockData = bld.data;
                packet.flags = ((0b0001 | 0b0010) << 4);

                statics::serverNetworkHandler->networkHandler->send(id, packet);
            }
        }
    }).detach();
}

bool RegionGuard::handleUseItem(ServerPlayer *player, UseItemPacket &pk) {
    auto reg = RegionGuard::getRegionWhereVec(player->getDimension()->dimensionId, {(float) pk.x, (float) pk.y, (float) pk.z});
    //std::cout << (reg->ownerName != p->nickname )<< "\n";
    if (reg && ((reg->ownerName != player->nickname) && !reg->isMember(player->nickname))) {
        auto bs = BlockSource(*player->getLevel(), *player->getDimension(), *player->getDimension()->getChunkSource(), true, false);
        auto tapBlock = bs.getBlock({pk.x, pk.y, pk.z});
        if((
                (tapBlock->blockId == 61 || tapBlock->blockId == 62) && reg->furnaceAccess) ||
                (tapBlock->blockId == 54 && reg->chestAccess) ||
                (tapBlock->blockId == 130 && reg->enderChestAccess) ||
                ((tapBlock->blockId == 8 || tapBlock->blockId == 9) && reg->boatPlaceOnWaterAllowed && player->inventoryProxy->getSlots()[player->inventoryProxy->selectedSlot]->itemOrBlock->id == 333))
            return true;


        player->sendPopup("§bДанная местность §fзапривачена §bигроком §f" + reg->ownerName);

        player->sendInventory();

        for (int x = pk.x - 3; x <= pk.x + 6; x++) {
            for (int y = pk.y - 3; y <= pk.y + 6; y++) {
                for (int z = pk.z - 3; z <= pk.z + 6; z++) {
                    auto tt = bs.getBlockAndData({x, y, z});

                    UpdateBlockPacket packet;
                    packet.x = x;
                    packet.y = y;
                    packet.z = z;
                    packet.blockId = tt.id;
                    packet.blockData = tt.data;
                    packet.flags = ((0b0001 | 0b0010) << 4);
                    statics::serverNetworkHandler->networkHandler->send(player->identifier, packet);
                }
            }
        }
        return false;
    }
    return true;
}

bool RegionGuard::handleRemoveBlock(ServerPlayer *player, RemoveBlockPacket &pk) {
    auto reg = RegionGuard::getRegionWhereVec(player->getDimension()->dimensionId, {(float) pk.x, (float) pk.y, (float) pk.z});
    if (reg && ((reg->ownerName != player->nickname) && !reg->isMember(player->nickname))) {
        player->sendPopup("§bДанная местность §fзапривачена §bигроком §f" + reg->ownerName);
        if (player->getHealth() > 15) {
            player->burn(1, true);
            player->sendMessage("<§l§bAtmosphere§f'PE§r> §bПерестань трогать §fчужую местность");
        }

        player->sendInventory();
        auto bs = BlockSource(*player->getLevel(), *player->getDimension(), *player->getDimension()->getChunkSource(), true, false);

        for (int x = pk.x - 3; x <= pk.x + 6; x++) {
            for (int y = pk.y - 3; y <= pk.y + 6; y++) {
                for (int z = pk.z - 3; z <= pk.z + 6; z++) {
                    auto tt = bs.getBlockAndData({x, y, z});

                    UpdateBlockPacket packet;
                    packet.x = x;
                    packet.y = y;
                    packet.z = z;
                    packet.blockId = tt.id;
                    packet.blockData = tt.data;
                    packet.flags = ((0b0001 | 0b0010) << 4);
                    statics::serverNetworkHandler->networkHandler->send(player->identifier, packet);
                }
            }
        }
        return false;
    }
    return true;
}
