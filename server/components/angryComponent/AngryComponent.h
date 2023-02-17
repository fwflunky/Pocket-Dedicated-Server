//
// Created by user on 04.02.23.
//

#ifndef MCPELAUNCHER_AngryComponent_H
#define MCPELAUNCHER_AngryComponent_H

#include "../../math/vec3/Vec3.h"
#include "../../level/BlockSource.h"
#include "../../entity/Entity.h"
class AngryComponent {
public:
    static void initHooks(void* handle);

    static inline void (*AngryComponent_setAngry)(AngryComponent*, bool) = nullptr;

    void setAngry(bool a);
    Entity* creature;
    Entity* someMob;
    char filler[20 - 8];
};


#endif //MCPELAUNCHER_AngryComponent_H
