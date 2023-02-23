//
// Created by user on 28.01.23.
//

#include "ChunkSource.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"

void ChunkSource::initHooks(void *handle) {
    ChunkSource_getOrLoadChunk = (LevelChunk* (*)(ChunkSource*, ChunkPos const&, int)) hybris_dlsym(handle, "_ZN11ChunkSource14getOrLoadChunkERK8ChunkPosNS_8LoadModeE");
    ChunkSource_getAvailableChunk = (LevelChunk* (*)(ChunkSource*, ChunkPos const&)) hybris_dlsym(handle, "_ZN11ChunkSource17getAvailableChunkERK8ChunkPos");
}

LevelChunk *ChunkSource::getOrLoadChunk(const ChunkPos &p , int mode) {
    return ChunkSource_getOrLoadChunk(this, p, mode);
}

LevelChunk *ChunkSource::getAvailableChunk(const ChunkPos &p) {
    return ChunkSource_getAvailableChunk(this, p);
}
