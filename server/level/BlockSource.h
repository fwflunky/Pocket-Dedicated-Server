//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_BLOCKSOURCE_H
#define MCPELAUNCHER_BLOCKSOURCE_H


#include "../block/Block.h"

class Dimension;
class Level;
class ChunkSource;
class Entity;
class LevelChunk;
#include "../level/BlockPos.h"
#include "../block/BlockID.h"

class BlockSource {
public:
    static void initHooks(void* handle);

    static inline BlockIDAndData (*BlockSource_getBlockAndData)(BlockSource*, BlockPos const&) = nullptr;
    static inline Block* (*BlockSource_getBlock)(BlockSource*, BlockPos const&) = nullptr;
    static inline BlockID (*BlockSource_getBlockID)(BlockSource*, BlockPos const&) = nullptr;
    static inline bool (*BlockSource_setBlock)(BlockSource*, int, int, int, BlockID, int) = nullptr;
    static inline bool (*BlockSource_setBlockAndData)(BlockSource*, BlockPos const&, FullBlock, int, Entity*) = nullptr;
    static inline void (*BlockSource_ctor)(BlockSource*, Level&, Dimension&, ChunkSource&, bool, bool) = nullptr;
    static inline LevelChunk* (*BlockSource_getChunkAt)(BlockSource*, BlockPos const&) = nullptr;
    static inline Level* (*BlockSource_getLevel)(BlockSource*) = nullptr;

   // static void ctorTest(BlockSource*, Level&, Dimension&, ChunkSource&, bool e, bool f);
    BlockSource(Level&, Dimension&, ChunkSource&, bool, bool);
    char filler[92];
    BlockIDAndData getBlockAndData(BlockPos const&);
    Block* getBlock(BlockPos const&);
    BlockID getBlockID(BlockPos const&);
    bool setBlock(BlockPos const&, BlockID, int);
    bool setBlockAndData(BlockPos const&, FullBlock, int, Entity*);
    bool simpleSetBlock(BlockPos const&, int, int);
    LevelChunk* getChunkAt(BlockPos const& pos);
    Level* getLevel();
};


#endif //MCPELAUNCHER_BLOCKSOURCE_H
