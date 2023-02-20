//
// Created by user on 04.02.23.
//

#include "Monster.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../../src/hook.h"
#include <iostream>

void Monster::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZN7Monster5_hurtERK18EntityDamageSourceibb"), (void *) &Monster::_hurt, (void **) &Monster::Monster__hurt);
}

bool Monster::_hurt(const EntityDamageSource &s, int i, bool b, bool bb) {
    //std::cout << "_hurt\n";
    Monster__hurt(this, s, i, b, bb);
}
