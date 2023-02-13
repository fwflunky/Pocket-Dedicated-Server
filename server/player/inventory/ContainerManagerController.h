//
// Created by user on 12.02.23.
//

#ifndef MCPELAUNCHER_CONTAINERMANAGERCONTROLLER_H
#define MCPELAUNCHER_CONTAINERMANAGERCONTROLLER_H


#include "ContainerManagerModel.h"

class ContainerManagerController {
public:
    virtual ~ContainerManagerController() = default;

    char filler[11-4];
    ContainerManagerModel* managerModel;
};


#endif //MCPELAUNCHER_CONTAINERMANAGERCONTROLLER_H
