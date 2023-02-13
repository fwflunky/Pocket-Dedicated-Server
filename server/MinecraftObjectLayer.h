//
// Created by user on 31.01.23.
//

#ifndef MCPELAUNCHER_MINECRAFTOBJECTLAYER_H
#define MCPELAUNCHER_MINECRAFTOBJECTLAYER_H

#include "math/vec3/Vec3.h"

class Entity;
class MinecraftObjectLayer {
public:
    static void initHooks(void* handle);
    static inline Vec3 (*MinecraftObjectLayer_getFeetPos)(Entity&) = nullptr;

    static Vec3 getFeetPos(Entity&);
};


#endif //MCPELAUNCHER_MINECRAFTOBJECTLAYER_H
