//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_MOB_H
#define MCPELAUNCHER_MOB_H

#include "../Entity.h"
#include "MobEffectInstance.h"
#include "../itemEntity/ItemEntity.h"

class Mob : public Entity {
public:
    static void initHooks(void* handle);

    static inline void(*Mob_heal)(Mob*, int) = nullptr;
    static inline int (*Mob_getHealth)(Mob*) = nullptr;
    static inline void (*Mob_setInvisible)(Mob*, bool) = nullptr;
    static inline void (*Mob_updateInvisibilityStatus)(Mob*) = nullptr;
    static inline void (*Mob_addEffect)(Mob*, MobEffectInstance const&) = nullptr;
    static inline void (*Mob_pickUpItem)(Mob*, ItemEntity&) = nullptr;
    //static inline bool (*Mob_canAttack)(Mob*, Entity*, bool) = nullptr;

    ~Mob() override = default;

    char filler[3992 - sizeof(Entity)]; //3992
    void* invalidatePtrWhatIsThat;

    void heal(int hp);
    int getHealth();
    void setInvisible(bool v);
    void updateInvisibilityStatus();
    void addEffect(MobEffectInstance const& effect);
    void pickUpItem(ItemEntity&);
    //bool canAttack(Entity* e, bool b);
};


#endif //MCPELAUNCHER_MOB_H
