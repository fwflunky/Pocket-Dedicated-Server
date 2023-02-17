//
// Created by user on 01.02.23.
//

#ifndef MCPELAUNCHER_REGIONGUARD_H
#define MCPELAUNCHER_REGIONGUARD_H

#include <map>
#include <string>
#include "../../server/math/aabb/AABB.h"
#include "Region.h"
#include "../../server/player/Player.h"
#include "../../server/player/ServerPlayer.h"
#include "../../server/network/packets/UseItemPacket.h"
#include "../../server/network/packets/RemoveBlockPacket.h"
#include <mutex>

class RegionGuard {
public:
    struct tempCreation {
        int stage = 0;
        Vec3 start;
        Vec3 end;
        std::string name;
    };
    static inline std::map<std::string, Region*> playerRegions{};
    static inline std::map<std::string, tempCreation> tempCreations{};
    static inline std::mutex mux;

    static void initCommands();
    static void loadAllUsers();
    static void saveAllUsers();
    static void scheduleAutoSave();

    static Region* getRegion(const std::string& nick);
    static Region* getRegionWhereVec(int dim, const Vec3 &v);
    static bool makeRegion(const std::string& nick,const std::string &region, const AABB& a, int dimId);
    static std::vector<Vec3> getHollowCube(Vec3 const& start, Vec3 const& end);

    static void handleStage(ServerPlayer* player, tempCreation& stage);
    static bool handleUseItem(ServerPlayer* player, UseItemPacket& pk);
    static bool handleRemoveBlock(ServerPlayer* player, RemoveBlockPacket& pk);
    static bool handleArrowPickup(ServerPlayer* player, Entity* arrow);
    static bool handleExplode(Entity* creature);
    static bool handlePlayerHurted(ServerPlayer* player, const EntityDamageSource &damageSource);
    static void startThreadedDraw(ServerPlayer* player, tempCreation& stage);
};




#endif //MCPELAUNCHER_REGIONGUARD_H
