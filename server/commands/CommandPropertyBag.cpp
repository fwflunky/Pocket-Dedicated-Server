//
// Created by user on 05.02.23.
//

#include <iostream>
#include "CommandPropertyBag.h"
#include "../../hybris/include/hybris/dlfcn.h"

void CommandPropertyBag::initHooks(void *handle) {
    CommandPropertyBag_ctor0 = (void (*)(CommandPropertyBag *)) hybris_dlsym(handle, "_ZN18CommandPropertyBagC2Ev");
}

CommandPropertyBag::CommandPropertyBag() {
    std::cout << "CommandPropertyBag ctor\n";
    CommandPropertyBag_ctor0(this);
}
