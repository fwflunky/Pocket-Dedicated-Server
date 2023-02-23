//
// Created by user on 24.02.23.
//

#include "MainChunkSource.h"
#include "../../../serverRunner/Loader.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void MainChunkSource::onInit() {
    Loader::callOnLoad.emplace_back([](void* h){
        MainChunkSource::initHooks(h);
    });
}

void MainChunkSource::initHooks(void *handle) {

}
