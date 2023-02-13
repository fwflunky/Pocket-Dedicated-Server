//
// Created by user on 08.02.23.
//

#include <thread>
#include "Arrow.h"
#include "../../../src/hook.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../../serverGamemode/regionGuard/RegionGuard.h"
#include "../../statics.h"
#include "../../level/Level.h"

void Arrow::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZN5Arrow11playerTouchER6Player"), (void *) &Arrow::playerTouch, (void **) &Arrow::Arrow_playerTouch);
}

void Arrow::playerTouch(Player &p) {
    auto reg = RegionGuard::getRegionWhereVec(this->getDimension()->dimensionId, {x, y, z});
    if (reg && (!reg->pvEAllowed || !reg->pvPAllowed || !reg->monstersAllowed)) {
        p.sendPopup("§bПоднимать стрелы в регионе §fзапрещено");
        for (int i = 0; i <= 5; i++) {
            Vec3 np = {x, y + 1, z};
            np.x -= (i * 0.07);
            np.y += (i * 0.07);
            np.z -= (i * 0.07);
            this->getLevel()->addParticleCustom(17, 0, np);
        }
        this->remove();
        return;
    }

    Arrow_playerTouch(this, p);
}
