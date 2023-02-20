//
// Created by user on 04.02.23.
//

#include "ExplodeComponent.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../../src/hook.h"
#include "../../../serverGamemode/regionGuard/RegionGuard.h"
#include "../../level/Level.h"
#include "../../statics.h"
#include <thread>
#include <iostream>
void ExplodeComponent::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZN16ExplodeComponent7explodeER11BlockSourceRK4Vec3f"), (void *) &ExplodeComponent::explode, (void **) &ExplodeComponent::ExplodeComponent_explode);
}

void ExplodeComponent::explode(BlockSource &bs, const Vec3 &pos, float r) {
    if(RegionGuard::handleExplode(creature))
        return ExplodeComponent_explode(this, bs, pos, r);
}
