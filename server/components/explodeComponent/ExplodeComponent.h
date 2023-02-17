//
// Created by user on 04.02.23.
//

#ifndef MCPELAUNCHER_EXPLODECOMPONENT_H
#define MCPELAUNCHER_EXPLODECOMPONENT_H

#include "../../math/vec3/Vec3.h"
#include "../../level/BlockSource.h"
#include "../../entity/Entity.h"
class ExplodeComponent {
public:
    static void initHooks(void* handle);

    static inline void (*ExplodeComponent_explode)(ExplodeComponent*, BlockSource&, Vec3 const&, float) = nullptr;
    void explode(BlockSource& bs, Vec3 const& pos, float r);
    Entity* creature;
};


#endif //MCPELAUNCHER_EXPLODECOMPONENT_H
