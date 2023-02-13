//
// Created by user on 04.02.23.
//

#include "ExplodeComponent.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../../src/hook.h"
#include "../../../serverGamemode/regionGuard/RegionGuard.h"
#include "../../level/Level.h"
#include "../../statics.h"
#include <thread>
#include <iostream>
void ExplodeComponent::initHooks(void *handle) {
   // ExplodeComponent_explode = (void (*)(ExplodeComponent*, BlockSource&, Vec3 const&, float)) hybris_dlsym(handle, "_ZN16ExplodeComponent7explodeER11BlockSourceRK4Vec3f");
    hookFunction((void *) hybris_dlsym(handle, "_ZN16ExplodeComponent7explodeER11BlockSourceRK4Vec3f"), (void *) &ExplodeComponent::explode, (void **) &ExplodeComponent::ExplodeComponent_explode);

}
//MinecraftCommands::registerSingleStepCommand
/* MinecraftCommands::registerSingleStepCommand(std::basic_string<char, std::char_traits<char>,
   std::allocator<char> > const&, int, std::basic_string<char, std::char_traits<char>,
   std::allocator<char> > const&, CommandType const&, std::function<MCRESULT (CommandOrigin const&,
   CommandPropertyBag const&, CommandPropertyBag&)>) */


void ExplodeComponent::explode(BlockSource &bs, const Vec3 &pos, float r) {
    auto reg = RegionGuard::getRegionWhereVec(creature->getDimension()->dimensionId,pos);
    if(reg && !reg->explodesAllowed) {
        std::thread([&bs, pos]() {
            auto lvl = bs.getLevel();
            for (int i = 0; i <= 5; i++) {
                Vec3 np = pos;
                np.x -= (i * 0.07);
                np.y += (i * 0.07);
                np.z -= (i * 0.07);
                statics::runOnNextTick([&]() {
                    lvl->addParticleCustom(17, 0, np);
                });
            }
        }).detach();
        return creature->remove();
    }
    return ExplodeComponent_explode(this, bs, pos, r);
}
