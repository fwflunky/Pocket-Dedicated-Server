//
// Created by user on 05.02.23.
//

#ifndef MCPELAUNCHER_ENTITYDAMAGEBYENTITYSOURCE_H
#define MCPELAUNCHER_ENTITYDAMAGEBYENTITYSOURCE_H

#include "EntityDamageByChildEntitySource.h"

class Entity;

class EntityDamageByEntitySource : public EntityDamageByChildEntitySource {
public:
    ~EntityDamageByEntitySource() override = default;
};


#endif //MCPELAUNCHER_ENTITYDAMAGEBYENTITYSOURCE_H
