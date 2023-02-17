//
// Created by user on 17.02.23.
//

#ifndef PDSERVER_WOLF_H
#define PDSERVER_WOLF_H


#include "../damageSource/EntityDamageSource.h"
#include "../animal/Animal.h"

class Wolf : public Animal {
public:
    static void initHooks(void* handle);
    static inline bool (*Wolf__hurt)(Wolf*, EntityDamageSource const&, int, bool, bool) = nullptr;

    bool _hurt(EntityDamageSource const& s, int i, bool b, bool bb);
};


#endif //PDSERVER_WOLF_H
