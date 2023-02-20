//
// Created by user on 16.02.23.
//

#include "ResourcePackStack.h"

ResourcePackStack::ResourcePackStack() {
    vtable = vtable_sym + 2;
    memset(filler, 0, sizeof(filler));
}

void ResourcePackStack::add(ResourcePack *i, const ResourcePackRepository &r, bool b) {
    ResourcePackStack_add(this, i, r, b);
}

ResourcePackStack *ResourcePackStack::deserialize(std::basic_fstream<char, std::char_traits<char>> &fs, const ResourcePackRepository & rpr) {
    return ResourcePackStack_deserialize(this, fs, rpr);
}
