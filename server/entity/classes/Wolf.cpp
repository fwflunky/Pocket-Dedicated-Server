//
// Created by user on 17.02.23.
//

#include "Wolf.h"
#include "../../hybris/include/hybris/dlfcn.h"
#include "../../serverGamemode/petHelper/PetHelper.h"
#include "../../src/hook.h"
void Wolf::initHooks(void *handle) {
    hookFunction((void *) hybris_dlsym(handle, "_ZN4Wolf5_hurtERK18EntityDamageSourceibb"), (void *) &Wolf::_hurt, (void **) &Wolf::Wolf__hurt);
}

bool Wolf::_hurt(const EntityDamageSource &s, int i, bool b, bool bb) {
    //std::cout << s.entityDamageCause << "\n";
    if(!PetHelper::Wolf::onDamage(this, s.damager, s.entityDamageCause))
        return false;
    return Wolf__hurt(this, s, i, b, bb);
}
