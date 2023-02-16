//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_RESOURCEPACKSTACK_H
#define PDSERVER_RESOURCEPACKSTACK_H


#include <cstring>
#include "ResourcePackRepository.h"


class ResourcePackStack {
public:
    static inline void** vtable_sym = nullptr;
    static inline void (*ResourcePackStack_add)(ResourcePackStack*, ResourcePack *i, ResourcePackRepository const& r, bool b) = nullptr;
    void** vtable;
    char filler[0x10];

    ResourcePackStack();

    void add(ResourcePack *i, ResourcePackRepository const& r, bool b);
};


#endif //PDSERVER_RESOURCEPACKSTACK_H
