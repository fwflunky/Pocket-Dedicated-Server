//
// Created by user on 04.02.23.
//

#ifndef MCPELAUNCHER_BLOCKSOURCELISTENER_H
#define MCPELAUNCHER_BLOCKSOURCELISTENER_H


#include "../block/BlockID.h"
class BlockPos;
class BlockSource;
class Entity;
#include "../entity/blockEntity/BlockEntity.h"
#include <memory>

class BlockSourceListener {
public:
    virtual ~BlockSourceListener() = default;
    virtual void onSourceCreated(BlockSource&){};
    virtual void onSourceDestroyed(BlockSource&){};
    virtual void onAreaChanged(BlockSource&, BlockPos const&, BlockPos const& ){};
    virtual void onBlockChanged(BlockSource&, BlockPos const&, FullBlock, FullBlock, int, Entity*){};
    virtual void onBrightnessChanged(BlockSource&, BlockPos const&){};
    virtual void onBlockEntityChanged(BlockSource&, BlockEntity&){};
    virtual void onEntityChanged(BlockSource&, Entity&){};
    virtual void onBlockEntityRemoved(BlockSource&, std::unique_ptr<BlockEntity>){};
    virtual void onBlockEvent(BlockSource&, int, int, int, int, int){};
};


#endif //MCPELAUNCHER_BLOCKSOURCELISTENER_H
