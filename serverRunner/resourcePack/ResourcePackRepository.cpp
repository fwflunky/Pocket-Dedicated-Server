//
// Created by user on 16.02.23.
//

#include <iostream>
#include "ResourcePackRepository.h"

ResourcePackRepository::ResourcePackRepository(MinecraftEventing &ev, PackManifestFactory &fact, EntitlementManager *em, FilePathManager *pm)  {
    ResourcePackRepository_construct(this, ev, fact, em, pm);
}

int ResourcePackRepository::getPackLoadingReport() {
    //std::cout << this << "\n";
    return ResourcePackRepository_getPackLoadingReport(this);
}