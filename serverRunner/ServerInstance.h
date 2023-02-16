//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_SERVERINSTANCE_H
#define PDSERVER_SERVERINSTANCE_H

#include <chrono>
#include <vector>
#include "level/LevelSettings.h"

class IMinecraftApp;
class Minecraft;
class OriginalOpsList;
class OriginalWhiteList;
namespace minecraft::api { class Api; }
namespace mce { class UUID; }
class MinecraftEventing;
class ResourcePackRepository;
class ResourcePackManager;
class FilePathManager;

class ServerInstance {
public:

    static inline void (*ServerInstance_construct)(ServerInstance*, IMinecraftApp& app, OriginalWhiteList const& wl, OriginalOpsList const& opl,
                                            FilePathManager*, std::chrono::duration<long long, std::ratio<1ll, 1ll> >,
                                            std::string s1, std::string s2, std::string s3, std::string s4, std::string s5,
                                            LevelSettings &ls,  minecraft::api::Api& api, int i1, bool b1, int i2, int i3, int i4, bool b2,
                                            std::vector<std::string> const& vs, std::string s6, bool b3,  mce::UUID const& uuid,
                                            MinecraftEventing& ev,  ResourcePackRepository& rpr, ResourcePackManager& rpm, ResourcePackManager* rmpm
                                            ) = nullptr;

    static inline void (*ServerInstance_update)(ServerInstance*) = nullptr;
    static inline void (*ServerInstance_stop)(ServerInstance*) = nullptr;

    ServerInstance(IMinecraftApp& app, OriginalWhiteList const& wl, OriginalOpsList const& opl,
                   FilePathManager*, std::chrono::duration<long long, std::ratio<1ll, 1ll> >,
                   std::string s1, std::string s2, std::string s3, std::string s4, std::string s5,
                   LevelSettings &ls,  minecraft::api::Api& api, int i1, bool b1, int i2, int i3, int i4, bool b2,
                   std::vector<std::string> const& vs, std::string s6, bool b3,  mce::UUID const& uuid,
                   MinecraftEventing& ev,  ResourcePackRepository& rpr, ResourcePackManager& rpm, ResourcePackManager* rmpm);
    void update();
    void stop();

    char filler[12];
    Minecraft* minecraft;
    char filler2[0x200];


};


#endif //PDSERVER_SERVERINSTANCE_H
