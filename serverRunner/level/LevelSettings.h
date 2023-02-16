//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_LEVELSETTINGS_H
#define PDSERVER_LEVELSETTINGS_H


class LevelSettings {
public:
    static inline void (*LevelSettings_construct)(LevelSettings *) = nullptr;
    //static void (*LevelSettings_construct2)(LevelSettings *, LevelSettings const &);

    unsigned int seed; // 4
    int gameType; // 8
    int difficulty; // c
    int forceGameType; // 10
    int generator; // 14
    bool hasAchievementsDisabled; // 18
    int dimension; // 1c
    int time; // 20
    bool edu; // 21
    float rainLevel, lightningLevel; // 28, 2c
    bool mpGame, lanBroadcast, xblBroadcast, commandsEnabled, texturepacksRequired, overrideSavedSettings; // 2d, 2e, 2f, 30, 31, 32~34
    bool generateDocs;
    float spawnX;
    float spawnY;
    float spawnZ;
    char filler[112 - 64];

    LevelSettings();
};

#endif //PDSERVER_LEVELSETTINGS_H
