//
// Created by user on 05.02.23.
//

#ifndef MCPELAUNCHER_COMMANDPROPERTYBAG_H
#define MCPELAUNCHER_COMMANDPROPERTYBAG_H


#include "PropertyBag.h"

class CommandPropertyBag : public PropertyBag {
public:
    static void initHooks(void* handle);

    static inline void (*CommandPropertyBag_ctor0)(CommandPropertyBag*) = nullptr;
    ~CommandPropertyBag() override = default;

    CommandPropertyBag();
};


#endif //MCPELAUNCHER_COMMANDPROPERTYBAG_H
