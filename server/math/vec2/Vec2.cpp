//
// Created by user on 28.01.23.
//

#include "Vec2.h"

#include "../../../hybris/include/hybris/dlfcn.h"

void Vec2::initHooks(void *handle) {
    ZERO = (Vec2*) hybris_dlsym(handle, "_ZN4Vec24ZEROE");
}

Vec2::Vec2(float xx, float zz) {
    x = xx;
    z = zz;
}