//
// Created by user on 31.01.23.
//

#include "Whitelist.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
#include "spdlog/spdlog.h"
#include "nlohmann/json.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

void Whitelist::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZNK9Whitelist9isAllowedERKN3mce4UUIDERKSs"), (void *) &Whitelist::isAllowed, (void **) &Whitelist::Whitelist_isAllowed);
}

bool Whitelist::isAllowed(void *uuid, const std::string &nick) {
    return false;
}

bool Whitelist::byNickIsAllowed(const std::string &nick) {
    return !enabled || allowedPlayers.contains(nick);
}

void Whitelist::reloadFromFile() {
    auto fs = std::ifstream(std::filesystem::current_path().string() + "/whitelist.json");
    if(fs) {
        std::stringstream ss;
        ss << fs.rdbuf();
        try {
            auto obj = nlohmann::json::parse(ss);
            enabled = obj["enabled"].get<bool>();
            allowedPlayers = obj["entries"].get<std::set<std::string>>();
            return;
        } catch(...){
        }
    }
    spdlog::error("Unable to load whitelist {0}/whitelist.json", std::filesystem::current_path().string());
}
