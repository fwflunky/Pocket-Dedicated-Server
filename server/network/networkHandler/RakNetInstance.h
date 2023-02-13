//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_RAKNETINSTANCE_H
#define MCPELAUNCHER_RAKNETINSTANCE_H


#include "../NetworkIdentifier.h"
#include "RakPeer.h"

class RakNetInstance {
public:
    static void initHooks(void *handle);
    static inline RakPeer* (*RakNetInstance__getPeer)(RakNetInstance*, NetworkIdentifier const&) = nullptr;
    char filler[188];
    RakPeer *peer;
    char filler1[604 - 188 - 4];//604

    RakPeer* _getPeer(NetworkIdentifier const& i);
};


#endif //MCPELAUNCHER_RAKNETINSTANCE_H
