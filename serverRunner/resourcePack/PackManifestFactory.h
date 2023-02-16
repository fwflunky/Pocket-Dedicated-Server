//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_PACKMANIFESTFACTORY_H
#define PDSERVER_PACKMANIFESTFACTORY_H

class MinecraftEventing;

class PackManifestFactory {
public:
    MinecraftEventing* eventing;

    static inline void (*PackManifestFactory_construct)(PackManifestFactory*, MinecraftEventing&) = nullptr;

    PackManifestFactory(MinecraftEventing& ev);
};


#endif //PDSERVER_PACKMANIFESTFACTORY_H
