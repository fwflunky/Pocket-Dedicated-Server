//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_RESOURCEPACKREPOSITORY_H
#define PDSERVER_RESOURCEPACKREPOSITORY_H

#include "ResourcePack.h"

class MinecraftEventing;
class PackManifestFactory;
class EntitlementManager;
class FilePathManager;


class ResourcePackRepository {
public:

    char filler[0x1c];
    ResourcePack* vanillaBehaviorPack;
    char filler1[0x100];

    static inline void (*ResourcePackRepository_construct)(ResourcePackRepository*, MinecraftEventing&, PackManifestFactory&, EntitlementManager*, FilePathManager*) = nullptr;
    static inline int (*ResourcePackRepository_getPackLoadingReport)(ResourcePackRepository*) = nullptr;

    int getPackLoadingReport();
    ResourcePackRepository(MinecraftEventing& ev, PackManifestFactory& fact, EntitlementManager* em, FilePathManager* pm);
};


#endif //PDSERVER_RESOURCEPACKREPOSITORY_H
