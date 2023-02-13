//
// Created by user on 01.02.23.
//

#ifndef MCPELAUNCHER_ENTITYDAMAGESOURCE_H
#define MCPELAUNCHER_ENTITYDAMAGESOURCE_H


#include <string>
#include "EntityDamageByChildEntitySource.h"
class Entity;

class EntityDamageSource : public EntityDamageByChildEntitySource {
public:
    ~EntityDamageSource() override = default;
    virtual bool isEntitySource(){};
    virtual Entity* getEntity(){};
    virtual bool isChildEntitySource(){
        return true;
    };
    virtual Entity* getDamagingEntity(){};
    virtual bool isBlockSource(){};
    virtual std::string getDeathMessage(std::string, Entity*){};
};


#endif //MCPELAUNCHER_ENTITYDAMAGESOURCE_H
