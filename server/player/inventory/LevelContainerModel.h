//
// Created by user on 12.02.23.
//

#ifndef MCPELAUNCHER_LEVELCONTAINERMODEL_H
#define MCPELAUNCHER_LEVELCONTAINERMODEL_H


#include "ContainerModel.h"

class LevelContainerModel : public ContainerModel { //size of LevelContainerModel must be 100
public:
    char filler[38 - 4];
};


#endif //MCPELAUNCHER_LEVELCONTAINERMODEL_H
