//
// Created by user on 16.02.23.
//

#include "ServerInstance.h"

void ServerInstance::update()  {
    ServerInstance_update(this);
}

ServerInstance::ServerInstance(IMinecraftApp &app, const OriginalWhiteList &wl, const OriginalOpsList &opl, FilePathManager * fpm, std::chrono::duration<long long int, std::ratio<1ll, 1ll>> dur, std::string s1, std::string s2, std::string s3, std::string s4, std::string s5, LevelSettings &ls, minecraft::api::Api &api, int i1, bool b1, int i2, int i3, int i4, bool b2, const std::vector<std::string> &vs, std::string s6, bool b3, const mce::UUID &uuid, MinecraftEventing &ev, ResourcePackRepository &rpr, ResourcePackManager &rpm, ResourcePackManager *rmpm) {
    ServerInstance_construct(this, app, wl, opl, fpm, dur, std::move(s1), std::move(s2), std::move(s3), std::move(s4), std::move(s5), ls, api, i1, b1, i2, i3, i4, b2, vs, std::move(s6), b3, uuid, ev, rpr, rpm, rmpm);
}

void ServerInstance::stop() {
    ServerInstance_stop(this);
}
