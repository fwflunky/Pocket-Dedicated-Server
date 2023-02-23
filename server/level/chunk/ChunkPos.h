//
// Created by user on 02.02.23.
//

#ifndef MCPELAUNCHER_CHUNKPOS_H
#define MCPELAUNCHER_CHUNKPOS_H

#include <unordered_map>
#include <cstddef>

class BlockPos;
class ChunkPos {
public:
    static void initHooks(void* handle);
    static inline void (*ChunkPos_ctor)(ChunkPos*,BlockPos const&) = nullptr;
    ChunkPos(BlockPos const&);

    int x,z;
    bool operator==(const ChunkPos& p) const;
    struct HashFunction
    {
        size_t operator()(const ChunkPos& pos) const
        {
            size_t rowHash = std::hash<int>()(pos.x);
            size_t colHash = std::hash<int>()(pos.z) << 1;
            return rowHash ^ colHash;
        }
    };
};


#endif //MCPELAUNCHER_CHUNKPOS_H
