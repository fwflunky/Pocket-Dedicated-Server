//
// Created by user on 07.02.23.
//

#ifndef MCPELAUNCHER_SPAWNCOLORS_H
#define MCPELAUNCHER_SPAWNCOLORS_H


#include <mutex>
#include <vector>
#include <set>
#include "../../server/level/BlockPos.h"
#include "../../server/player/ServerPlayer.h"

class SpawnColors {
public:
    static inline std::vector<BlockPos> woolBlocks;
    static inline BlockPos spawnPos = {715, 67, 42};
    static inline std::mutex mux;
    static void initThreads();

    static inline std::set<std::string> rtpPrepares;
    static bool tryRTP(ServerPlayer* p);

    static inline std::set<std::string> spawnPrepares;
    static bool toSpawn(ServerPlayer* p);
};


#endif //MCPELAUNCHER_SPAWNCOLORS_H
