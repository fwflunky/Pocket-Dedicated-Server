//
// Created by user on 16.02.23.
//

#include "ResourcePackManager.h"

ResourcePackManager::ResourcePackManager(std::function<std::string()> f)  {
    ResourcePackManager_construct(this, std::move(f));
}

void ResourcePackManager::setStack(std::unique_ptr<ResourcePackStack> st, int t, bool b) {
    ResourcePackManager_setStack(this, std::move(st), t, b);
}
