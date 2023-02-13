//
// Created by user on 11.02.23.
//

#ifndef MCPELAUNCHER_CONTAINERMANAGERMODEL_H
#define MCPELAUNCHER_CONTAINERMANAGERMODEL_H

#include <memory>
#include <map>
#include <unordered_map>
#include "IContainerManager.h"
#include "ContainerModel.h"

typedef unsigned char ContainerID;
typedef unsigned char ContainerType;
class Player;

enum ContainerTypes {
    chest = 0,
    furnace = 2,
};
class ContainerManagerModel : public IContainerManager {
public:
    ~ContainerManagerModel() override = default;
    Player* whoOpen;
    ContainerID id;
    ContainerType type;
    //char filler[3];
    std::unordered_map<std::string, std::shared_ptr<ContainerModel>> models;
    char filler1[44 - 6 - 4 - 24 - 2];
};


#endif //MCPELAUNCHER_CONTAINERMANAGERMODEL_H
