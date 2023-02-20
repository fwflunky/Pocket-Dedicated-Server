//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_CONNECTIONREQUEST_H
#define MCPELAUNCHER_CONNECTIONREQUEST_H


#include "../../player/certificate/Certificate.h"

class ConnectionRequest { //12 size
public:
    static void initHooks(void* handle);

    static inline bool (*ConnectionRequest_verifySelfSigned)(ConnectionRequest*) = nullptr;

    bool verifySelfSigned();
    char filler[4];
    Certificate* certificate;
};


#endif //MCPELAUNCHER_CONNECTIONREQUEST_H
