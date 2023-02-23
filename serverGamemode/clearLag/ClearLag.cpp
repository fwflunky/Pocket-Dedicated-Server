//
// Created by user on 24.02.23.
//

#include <set>
#include "ClearLag.h"
#include "../../serverRunner/Loader.h"
#include "spdlog/spdlog.h"
#include "../../server/statics.h"
#include "../../server/level/Level.h"
#include "../../server/level/chunk/LevelChunk.h"

void ClearLag::onInit() {
    Loader::callAfterLoad.emplace_back([](void* h){
        ClearLag::load();
    });
}

void ClearLag::load() {
    std::thread([](){
        while (true){
            sleep(60 * 19);
            statics::serverNetworkHandler->_displayGameMessage("", "§eОчистка вещей через 1 минуту. Подберите все нужные вам вещи.");
            sleep(60);

            int cnt = 0;
            std::unordered_map<std::string, int> deleted;

            statics::runOnNextTick([&](){
                auto chs = statics::serverNetworkHandler->mainLevel->getDimension(0)->mainChunkSource;
                for (auto &ch: chs->chunks) {
                    auto lch = chs->getAvailableChunk(ch.first);
                    if (lch && !lch->entities.empty()) { //don't load unneeded chunks
                        for (auto *ent: lch->entities) {
                            if(ent->maybeEntityType == 4) { //itementity
                                cnt += ((ItemEntity*)ent)->item.count;
                                if(((ItemEntity*)ent)->item.itemOrBlock) {
                                    if(!deleted.contains(((ItemEntity*)ent)->item.itemOrBlock->name)){
                                        deleted.insert({((ItemEntity*)ent)->item.itemOrBlock->name, ((ItemEntity*)ent)->item.count});
                                    } else {
                                        deleted.at(((ItemEntity*)ent)->item.itemOrBlock->name) += ((ItemEntity*)ent)->item.count;
                                    }
                                }

                                statics::serverNetworkHandler->mainLevel->addParticleCustom(17, 0, {ent->x, ent->y, ent->z});
                                ent->remove();
                            }
                        }
                    }
                }
                statics::serverNetworkHandler->_displayGameMessage("", "§eИз мира удалено " + std::to_string(cnt) + " вещей (-и)");
            });

            statics::runOnNextTick([&]() {
                std::string out;
                for (auto &it: deleted)
                    out += it.first + " §f(x" + std::to_string(it.second) + ")§e, ";
                statics::serverNetworkHandler->_displayGameMessage("", "§eИз них: " + out);
            });
        }
    }).detach();
}
