//
// Created by user on 19.02.23.
//

#ifndef PDSERVER_CONFIG_H
#define PDSERVER_CONFIG_H


#include <nlohmann/json.hpp>

class Config {
public:
    static inline nlohmann::json object;
    static void read();

    static int getServerPort();
    static int getMaxOnline();
    static std::string getMOTD();

    static int getWorldGenerator();
    static int getWorldSeed();
    static int getWorldGameType();
    static int getWorldDifficulty();

    static std::string getWorldLevelName();
    static std::string getWorldLevelId();


    static bool debugEnabled();
};


#endif //PDSERVER_CONFIG_H
