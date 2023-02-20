//
// Created by user on 29.01.23.
//

#include "Block.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"

void Block::initHooks(void *handle) {
    Block_setDestroyTime = (void (*)(Block *, float)) hybris_dlsym(handle, "_ZN5Block14setDestroyTimeEf");
    Block_Blocks = (Block**) hybris_dlsym(handle, "_ZN5Block7mBlocksE"); //256 max
}

void Block::setDestroyTime(float time) {
    Block_setDestroyTime(this,time);
}
