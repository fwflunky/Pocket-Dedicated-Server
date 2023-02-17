//
// Created by user on 17.02.23.
//

#ifndef PDSERVER_PetHelper_H
#define PDSERVER_PetHelper_H


#include "../../server/entity/Entity.h"

namespace PetHelper {
    class Wolf {
    public:
        static bool onDamage(Entity *wolf, Entity *damager, int cause);
    };

    class Cat {
    public:

    };

    class Horse {
    public:

    };

}

#endif //PDSERVER_PetHelper_H
