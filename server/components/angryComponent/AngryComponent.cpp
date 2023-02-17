//
// Created by user on 04.02.23.
//

#include "AngryComponent.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../statics.h"
#include <thread>
#include <iostream>
void AngryComponent::initHooks(void *handle) {
    AngryComponent_setAngry = (void (*)(AngryComponent*, bool)) hybris_dlsym(handle, "_ZN14AngryComponent8setAngryEb");
}

void AngryComponent::setAngry(bool a) {
    AngryComponent_setAngry(this, a);
}

