//
// Created by user on 10.02.23.
//

#include "MobEffectInstance.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void MobEffectInstance::initHooks(void *handle) {
    MobEffectInstance_ctor = (void (*)(MobEffectInstance *, int, int, int)) hybris_dlsym(handle, "_ZN17MobEffectInstanceC2Eiii");
}

MobEffectInstance::MobEffectInstance(int id, int duration, int ampf) {
    MobEffectInstance_ctor(this, id, duration, ampf);
}
