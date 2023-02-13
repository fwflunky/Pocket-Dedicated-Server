//
// Created by user on 27.01.23.
//

#include "Vec3.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void Vec3::initHooks(void *handle) {
    ZERO = (Vec3*) hybris_dlsym(handle, "_ZN4Vec34ZEROE");
}

Vec3::Vec3(float xx, float yy, float zz) {
    x = xx;
    y = yy;
    z = zz;
}
