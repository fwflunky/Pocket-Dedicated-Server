//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_CHUNKSOURCE_H
#define MCPELAUNCHER_CHUNKSOURCE_H

#include <unordered_map>
#include "ChunkPos.h"

class LevelChunk;

class ChunkSource {
public:
    static void initHooks(void* handle);
    static inline LevelChunk* (*ChunkSource_getOrLoadChunk)(ChunkSource*,ChunkPos const&, int) = nullptr;
    static inline LevelChunk* (*ChunkSource_getAvailableChunk)(ChunkSource*,ChunkPos const&) = nullptr;

    virtual ~ChunkSource() = default;

    char filler[24 - 4];
    LevelChunk* getOrLoadChunk(ChunkPos const&, int);
    LevelChunk* getAvailableChunk(ChunkPos const&);
};


#endif //MCPELAUNCHER_CHUNKSOURCE_H
