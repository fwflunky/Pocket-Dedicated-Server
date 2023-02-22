//
// Created by user on 19.02.23.
//

#include "Config.h"
#include "../../server/statics.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <spdlog/spdlog.h>

void Config::read() {
    auto fs = std::ifstream(std::filesystem::current_path().string() + "/settings.json");
    if(fs) {
        std::stringstream ss;
        ss << fs.rdbuf();
        try {
            object = nlohmann::json::parse(ss);
            return;
        } catch(...){
        }
    }
    spdlog::error("Unable to load server config {0}/settings.json. Using default values", std::filesystem::current_path().string());
}

int Config::getServerPort() {
    try {
        return object["serverPort"].get<int>();
    } catch (...){
        return 19132;
    }
}

int Config::getMaxOnline() {
    try {
        return object["maxOnline"].get<int>();
    } catch (...){
        return 10;
    }
}

std::string Config::getMOTD() {
    try {
        return object["MOTD"].get<std::string>();
    } catch (...){
        return "No config loaded";
    }
}

int Config::getWorldGenerator() {
    try {
        return object["world"]["generator"].get<int>();
    } catch (...){
        return 0;
    }
}

int Config::getWorldSeed() {
    try {
        return object["world"]["seed"].get<int>();
    } catch (...){
        return 0;
    }
}

int Config::getWorldGameType() {
    try {
        return object["world"]["gameType"].get<int>();
    } catch (...){
        return 0;
    }
}

int Config::getWorldDifficulty() {
    try {
        return object["world"]["difficulty"].get<int>();
    } catch (...){
        return 2;
    }
}

std::string Config::getWorldLevelName() {
    try {
        return object["world"]["levelName"].get<std::string>();
    } catch (...){
        return "No config loaded";
    }
}

std::string Config::getWorldLevelId() {
    try {
        return object["world"]["levelId"].get<std::string>();
    } catch (...){
        return "No_config_loaded";
    }
}
