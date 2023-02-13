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

#define scpath std::string("/home/user/Видео/mcpelauncher-linux-2ebee1b9a70479685a4c430370c3fdfa47988b54/serverGamemode/storage/spawnColors/")
class SpawnColors {
public:
    static inline std::vector<BlockPos> woolBlocks;
    static inline BlockPos spawnPos = {715, 67, 42};
    static inline std::mutex mux;
    static void initThreads();
    static void scheduleAutoSave();
    static void loadBlocks();
    static void saveBlocks();

    static inline std::set<std::string> rtpPrepares;
    static bool tryRTP(ServerPlayer* p);

    static inline std::set<std::string> spawnPrepares;
    static bool toSpawn(ServerPlayer* p);
};


#endif //MCPELAUNCHER_SPAWNCOLORS_H
