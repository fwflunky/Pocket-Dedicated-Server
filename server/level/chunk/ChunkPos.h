//
// Created by user on 02.02.23.
//

#ifndef MCPELAUNCHER_CHUNKPOS_H
#define MCPELAUNCHER_CHUNKPOS_H

class BlockPos;
class ChunkPos {
public:
    static void initHooks(void* handle);
    static inline void (*ChunkPos_ctor)(ChunkPos*,BlockPos const&) = nullptr;
    ChunkPos(BlockPos const&);
};


#endif //MCPELAUNCHER_CHUNKPOS_H
