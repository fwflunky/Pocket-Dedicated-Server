//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_LEVEL_H
#define MCPELAUNCHER_LEVEL_H


#include <vector>
#include "../player/Player.h"
#include "../util/storage/LevelStorage.h"

class Level {
public:
    static void initHooks(void* handle);

    static inline std::vector<Player*>* (*Level_getUsers)(Level*) = nullptr;
    static inline void(*Level_setTime)(Level*, int) = nullptr;
    static inline void(*Level__syncTime)(Level*, int) = nullptr;
    static inline int (*Level_addParticle)(Level*, int, Vec3 const&, Vec3 const&, int) = nullptr;
    static inline void (*Level_broadcastLevelEvent)(Level*, short, Vec3 const&, int, Player*) = nullptr;
    static inline Dimension* (*Level_getDimension)(Level*, int) = nullptr;
    static inline void (*Level_suspendPlayer)(Level*, Player&) = nullptr;
    static inline void (*Level_resumePlayer)(Level*, Player&) = nullptr;
    static inline void (*Level_createDimension)(Level*, int) = nullptr;
    static inline void (*Level_saveGameData)(Level*) = nullptr;
    static inline void (*Level_forceFlushRemovedPlayers)(Level*) = nullptr;
    //static inline int (*Level_addTerrainParticle)(Level*, int, Vec3 const&, Vec3 const&, int) = nullptr;

    char filler[111];
    int someInt1;
    int someInt2;
    char filler1[4];
    LevelStorage* levelStorage;

    std::vector<Player*>* getUsers();
    void setTime(int time);
    void _syncTime(int time);
    int addParticle(int type, Vec3 const& pos, Vec3 const& size, int some);
    void addParticleCustom(int type, int data, Vec3 const& pos);
    void broadcastLevelEvent(short id, Vec3 const& pos, int data, Player* p);
    Dimension* getDimension(int id);
    void suspendPlayer(Player& p);
    void resumePlayer(Player& p);
    void createDimension(int id);
    void saveGameData();
    void forceFlushRemovedPlayers();
};


#endif //MCPELAUNCHER_LEVEL_H
