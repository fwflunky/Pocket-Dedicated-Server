//
// Created by user on 28.01.23.
//

#include "Mob.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
void Mob::initHooks(void *handle) {
    Mob_heal = (void (*)(Mob*, int)) hybris_dlsym(handle, "_ZN3Mob4healEi");
    Mob_getHealth = (int (*)(Mob*)) hybris_dlsym(handle, "_ZNK3Mob9getHealthEv");
    Mob_setInvisible = (void (*)(Mob*, bool)) hybris_dlsym(handle, "_ZN3Mob12setInvisibleEb");
    Mob_addEffect = (void (*)(Mob*, MobEffectInstance const&)) hybris_dlsym(handle, "_ZN3Mob9addEffectERK17MobEffectInstance");
    Mob_updateInvisibilityStatus = (void (*)(Mob*)) hybris_dlsym(handle, "_ZN3Mob24updateInvisibilityStatusEv");
    Mob_pickUpItem = (void (*)(Mob*, ItemEntity&)) hybris_dlsym(handle, "_ZN3Mob10pickUpItemER10ItemEntity");
    //hookFunction((void *) hybris_dlsym(handle, "_ZN3Mob10pickUpItemER10ItemEntity"), (void *) &Mob::pickUpItem, (void **) &Mob::Mob_pickUpItem);

}

void Mob::heal(int hp) {
    Mob_heal(this, hp);
}

int Mob::getHealth() {
    return Mob_getHealth(this);
}

void Mob::setInvisible(bool v) {
    Mob_setInvisible(this, v);
}

void Mob::updateInvisibilityStatus() {
    Mob_updateInvisibilityStatus(this);
}

void Mob::addEffect(const MobEffectInstance &effect) {
    Mob_addEffect(this, effect);
}

void Mob::pickUpItem(ItemEntity &i) {
    //std::cout << "pickUpItem\n";
    Mob_pickUpItem(this, i);
}
/*
bool Mob::canAttack(Entity *e, bool b) {
    std::cout << "canAttack\n";
    return true;
}*/
