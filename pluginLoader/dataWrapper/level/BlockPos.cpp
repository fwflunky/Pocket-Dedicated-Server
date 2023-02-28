//
// Created by user on 28.02.23.
//

#include "BlockPos.h"

dataWrapper::BlockPos::BlockPos(const ::BlockPos &pos) {
    blockPos = pos;
}

int dataWrapper::BlockPos::getX() {
    return blockPos.x;
}

int dataWrapper::BlockPos::getY() {
    return blockPos.y;
}

int dataWrapper::BlockPos::getZ() {
    return blockPos.z;
}
