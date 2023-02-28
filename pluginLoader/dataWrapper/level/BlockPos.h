//
// Created by user on 28.02.23.
//

#ifndef PDSERVER_DBLOCKPOS_H
#define PDSERVER_DBLOCKPOS_H
#include "../../../server/level/BlockPos.h"

namespace dataWrapper {
    class BlockPos {
    public:
        explicit BlockPos(const ::BlockPos& pos);
        BlockPos() = default;
        ~BlockPos() = default;

        virtual int getX();
        virtual int getY();
        virtual int getZ();
    private:
        ::BlockPos blockPos;
    };
}

#endif //PDSERVER_DBLOCKPOS_H
