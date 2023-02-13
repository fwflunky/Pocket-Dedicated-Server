//
// Created by user on 05.02.23.
//

#ifndef MCPELAUNCHER_PLAYERCOMMANDORIGIN_H
#define MCPELAUNCHER_PLAYERCOMMANDORIGIN_H


#include "CommandOrigin.h"
class Player;

class PlayerCommandOrigin : public CommandOrigin {
public:
    static void initHooks(void* handle);
    static inline void (*PlayerCommandOrigin_ctor)(PlayerCommandOrigin*, Player&) = nullptr;

    ~PlayerCommandOrigin() override = default;
    PlayerCommandOrigin(Player&);

    void* getRequestId() override;
    std::string getName() override;
    BlockPos getBlockPosition() override;
    BlockPos getWorldPosition() override;
    Level* getLevel() override;
    Entity* getEntity() override;
    BlockSource* getRegion() override;
    unsigned char getPermissionsLevel() override;
    CommandOrigin* clone() override;
    int getOriginType() override;
    void* toCommandOriginData() override;

    char filler[160 - 12];
};


#endif //MCPELAUNCHER_PLAYERCOMMANDORIGIN_H
