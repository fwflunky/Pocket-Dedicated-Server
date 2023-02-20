//
// Created by user on 08.02.23.
//

#include <thread>
#include "Arrow.h"
#include "../../../src/hook.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../../serverGamemode/regionGuard/RegionGuard.h"
#include "../../statics.h"
#include "../../level/Level.h"

void Arrow::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZN5Arrow11playerTouchER6Player"), (void *) &Arrow::playerTouch, (void **) &Arrow::Arrow_playerTouch);
}

void Arrow::playerTouch(Player &p) {
    if(RegionGuard::handleArrowPickup((ServerPlayer*) &p, this))
        Arrow_playerTouch(this, p);
}
