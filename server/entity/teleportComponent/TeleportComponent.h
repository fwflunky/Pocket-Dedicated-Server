//
// Created by user on 02.02.23.
//

#ifndef MCPELAUNCHER_TELEPORTCOMPONENT_H
#define MCPELAUNCHER_TELEPORTCOMPONENT_H

class Mob;
class TeleportComponent {
public:
    static void initHooks(void* handle);

    static inline bool (*TeleportComponent_randomTeleport)(TeleportComponent*) = nullptr;
    static inline void (*TeleportComponent_ctor)(TeleportComponent*, Mob&) = nullptr;
    TeleportComponent(Mob&);
    bool randomTeleport();
};


#endif //MCPELAUNCHER_TELEPORTCOMPONENT_H
