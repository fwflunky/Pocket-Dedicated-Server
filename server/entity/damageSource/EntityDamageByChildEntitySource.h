//
// Created by user on 04.02.23.
//

#ifndef MCPELAUNCHER_ENTITYDAMAGEBYCHILDENTITYSOURCE_H
#define MCPELAUNCHER_ENTITYDAMAGEBYCHILDENTITYSOURCE_H


class Entity;

class EntityDamageByChildEntitySource {
public:
    virtual ~EntityDamageByChildEntitySource() = default;
    int entityDamageCause;
    Entity* damager;
    Entity* damaged;
};


#endif //MCPELAUNCHER_ENTITYDAMAGEBYCHILDENTITYSOURCE_H
