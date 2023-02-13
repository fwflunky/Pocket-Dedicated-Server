//
// Created by user on 28.01.23.
//

#include "BlockSource.h"
#include "../../hybris/include/hybris/dlfcn.h"
#include <iostream>
#include <atomic>
#include "../../src/hook.h"
#include "../../src/common.h"

void BlockSource::initHooks(void *handle) {
    std::cout << "BlockSourcector0\n";
    BlockSource_getBlockAndData = (BlockIDAndData (*)(BlockSource*, BlockPos const&)) hybris_dlsym(handle, "_ZN11BlockSource15getBlockAndDataERK8BlockPos");
    BlockSource_setBlockAndData = (bool (*)(BlockSource*, BlockPos const&, FullBlock, int, Entity*)) hybris_dlsym(handle, "_ZN11BlockSource15setBlockAndDataERK8BlockPos9FullBlockiP6Entity");
    BlockSource_getBlock = (Block* (*)(BlockSource*, BlockPos const&)) hybris_dlsym(handle, "_ZN11BlockSource8getBlockERK8BlockPos");
    BlockSource_getBlockID = (BlockID (*)(BlockSource*, BlockPos const&)) hybris_dlsym(handle, "_ZN11BlockSource10getBlockIDERK8BlockPos");
    BlockSource_setBlock = (bool (*)(BlockSource*,int, int, int, BlockID, int)) hybris_dlsym(handle, "_ZN11BlockSource8setBlockEiii7BlockIDi");
    BlockSource_getChunkAt = (LevelChunk* (*)(BlockSource*, BlockPos const&)) hybris_dlsym(handle, "_ZN11BlockSource10getChunkAtERK8BlockPos");
    BlockSource_ctor = (void (*)(BlockSource*, Level&, Dimension&, ChunkSource&, bool, bool)) hybris_dlsym(handle, "_ZN11BlockSourceC2ER5LevelR9DimensionR11ChunkSourcebb");
    BlockSource_getLevel = (Level* (*)(BlockSource*)) hybris_dlsym(handle, "_ZN11BlockSource8getLevelEv");
    //hookFunction((void *) hybris_dlsym(handle, "_ZN11BlockSourceC2ER5LevelR9DimensionR11ChunkSourcebb"), (void *) &BlockSource::ctorTest, (void **) &BlockSource::BlockSource_ctor);
}

BlockIDAndData BlockSource::getBlockAndData(BlockPos const&p) {
    return BlockSource_getBlockAndData(this, p);
}

BlockSource::BlockSource(Level &l, Dimension &d, ChunkSource &c, bool b, bool bb) {
    BlockSource_ctor(this, l,d,c,b,bb);
}

Block* BlockSource::getBlock(const BlockPos & b) {
    return BlockSource_getBlock(this, b);
}

bool BlockSource::setBlock(const BlockPos &p, BlockID id, int data) {
    return BlockSource_setBlock(this, p.x, p.y, p.z, id, data);
}

BlockID BlockSource::getBlockID(const BlockPos &b) {
    return BlockSource_getBlockID(this, b);
}

bool BlockSource::simpleSetBlock(const BlockPos & a, int b, int c) {
    BlockID block{
            .id = (unsigned char*) new unsigned char (b)
    };
    auto r = setBlock(a, block, c);
    delete block.id;
    return r;
}

bool BlockSource::setBlockAndData(const BlockPos & p, FullBlock f, int i, Entity* e) {
    return BlockSource_setBlockAndData(this, p, f, i, e);
}

LevelChunk *BlockSource::getChunkAt(const BlockPos &pos) {
    return BlockSource_getChunkAt(this, pos);
}

Level *BlockSource::getLevel() {
    return BlockSource_getLevel(this);
}
/*
void BlockSource::ctorTest(BlockSource * a, Level & b , Dimension & c, ChunkSource & d, bool e, bool f) {
    std::cout << "Level pointer: " << &b << ", Dimension pointer: " << &c << ", ChunkSource pointer: " << &d << ", b1: " << e << ", b2: " << f << "\n";
    BlockSource_ctor(a,b,c,d, e, f);
}*/

