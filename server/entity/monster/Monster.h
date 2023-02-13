//
// Created by user on 04.02.23.
//

#ifndef MCPELAUNCHER_MONSTER_H
#define MCPELAUNCHER_MONSTER_H


#include "../damageSource/EntityDamageSource.h"
#include "../mob/Mob.h"

class Monster : public Mob {
public:
    static void initHooks(void* handle);
    static inline bool (*Monster__hurt)(Monster*, EntityDamageSource const&, int, bool, bool) = nullptr;

    bool _hurt(EntityDamageSource const& s, int i, bool b, bool bb);
};


#endif //MCPELAUNCHER_MONSTER_H
