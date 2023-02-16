//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_ENTITLEMENTMANAGER_H
#define PDSERVER_ENTITLEMENTMANAGER_H

class MinecraftEventing;
namespace Social {
    class UserManager;
}

class EntitlementManager {
public:
    static inline void (*EntitlementManager_construct)(EntitlementManager*, MinecraftEventing&, Social::UserManager&) = nullptr;
    EntitlementManager(MinecraftEventing&, Social::UserManager&);
};


#endif //PDSERVER_ENTITLEMENTMANAGER_H
