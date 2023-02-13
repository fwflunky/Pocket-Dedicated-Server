//
// Created by user on 28.01.23.
//

#include "ChunkSource.h"
#include "../../../hybris/include/hybris/dlfcn.h"

void ChunkSource::initHooks(void *handle) {
    ChunkSource_getOrLoadChunk = (LevelChunk* (*)(ChunkSource*, ChunkPos const&, int)) hybris_dlsym(handle, "_ZN11ChunkSource14getOrLoadChunkERK8ChunkPosNS_8LoadModeE");
}

LevelChunk *ChunkSource::getOrLoadChunk(const ChunkPos &p , int mode) {
    return ChunkSource_getOrLoadChunk(this, p, mode);
}
