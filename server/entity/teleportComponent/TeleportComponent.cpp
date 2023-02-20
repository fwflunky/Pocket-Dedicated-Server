//
// Created by user on 02.02.23.
//

#include "TeleportComponent.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void TeleportComponent::initHooks(void *handle) {
    TeleportComponent_randomTeleport = (bool (*)(TeleportComponent*)) hybris_dlsym(handle, "_ZN17TeleportComponent14randomTeleportEv");
    TeleportComponent_ctor = (void (*)(TeleportComponent*, Mob&)) hybris_dlsym(handle, "_ZN17TeleportComponentC2ER3Mob");
}

bool TeleportComponent::randomTeleport() {
    return TeleportComponent_randomTeleport(this);
}

TeleportComponent::TeleportComponent(Mob &m) {
    TeleportComponent_ctor(this, m);
}
