//
// Created by user on 12.02.23.
//

#ifndef MCPELAUNCHER_CONTAINERMODEL_H
#define MCPELAUNCHER_CONTAINERMODEL_H

#include <vector>
#include "../../item/ItemInstance.h"

class ContainerModel {
public:
    char filler[15];
    std::vector<ItemInstance> items;  //16
    char fille1[68-30];
};


#endif //MCPELAUNCHER_CONTAINERMODEL_H
