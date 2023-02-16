//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_RESOURCEPACKMANAGER_H
#define PDSERVER_RESOURCEPACKMANAGER_H


#include <string>
#include <functional>
#include <memory>
#include "ResourcePackStack.h"

class ResourcePackManager {
public:

    char filler[0x100];

    static inline void (*ResourcePackManager_construct)(ResourcePackManager*, std::function<std::string ()>) = nullptr;
    static inline void (*ResourcePackManager_setStack)(ResourcePackManager*, std::unique_ptr<ResourcePackStack>, int, bool) = nullptr;

    void setStack(std::unique_ptr<ResourcePackStack> st, int t, bool b);

    ResourcePackManager(std::function<std::string ()> f);

};

#endif //PDSERVER_RESOURCEPACKMANAGER_H
