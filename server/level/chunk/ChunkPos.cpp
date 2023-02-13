//
// Created by user on 02.02.23.
//

#include "ChunkPos.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void ChunkPos::initHooks(void *handle) {
    ChunkPos_ctor = (void (*)(ChunkPos*, BlockPos const&)) hybris_dlsym(handle, "_ZN8ChunkPosC2ERK8BlockPos");
}

ChunkPos::ChunkPos(const BlockPos &p) {
    ChunkPos_ctor(this, p);
}
