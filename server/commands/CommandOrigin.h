//
// Created by user on 05.02.23.
//

#ifndef MCPELAUNCHER_COMMANDORIGIN_H
#define MCPELAUNCHER_COMMANDORIGIN_H


#include "../network/NetworkIdentifier.h"
#include "Command.h"
#include "../level/BlockPos.h"
class BlockSource;
class Entity;
class Level;
class CommandOrigin {
public:
    static void initHooks(void* handle);
   // static inline void (*PlayerCommandOrigin_ctor)(PlayerCommandOrigin*, Player&) = nullptr;

    virtual ~CommandOrigin() = default;
    virtual void* getRequestId() = 0;
    virtual std::string getName() = 0;
    virtual BlockPos getBlockPosition() = 0;
    virtual BlockPos getWorldPosition() = 0;
    virtual Level* getLevel() = 0;
    virtual Entity* getEntity() = 0;
    virtual BlockSource* getRegion() = 0;
    virtual unsigned char getPermissionsLevel() = 0;
    virtual CommandOrigin* clone() = 0;
    virtual bool canCallHiddenCommands(){return false;};
    virtual bool canRunCommand(Command const&){return false;};
    virtual bool hasChatPerms(){return false;};
    virtual bool hasTellPerms(){return false;};
    virtual void setSourceId(NetworkIdentifier const&){};
    virtual NetworkIdentifier getSourceId(){};
    virtual void* getOutputReceiver(){};
    virtual int getOriginType() = 0;
    virtual void* toCommandOriginData() = 0;

    char filler[168 - 4]; //CommandOrigin::fromCommandOriginData
};


#endif //MCPELAUNCHER_COMMANDORIGIN_H
