//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_CHUNKSOURCE_H
#define MCPELAUNCHER_CHUNKSOURCE_H

#include "ChunkPos.h"

class LevelChunk;

class ChunkSource {
public:
    static void initHooks(void* handle);
    static inline LevelChunk* (*ChunkSource_getOrLoadChunk)(ChunkSource*,ChunkPos const&, int) = nullptr;

    LevelChunk* getOrLoadChunk(ChunkPos const&, int);
};


#endif //MCPELAUNCHER_CHUNKSOURCE_H
