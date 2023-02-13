//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_BLOCKPOS_H
#define MCPELAUNCHER_BLOCKPOS_H

#include <string>
class BlockPos {
public:
    BlockPos(float xx, float yy, float zz);
    BlockPos(int xx, int yy, int zz);

    int x, y, z;
    std::string toString() const;
    bool operator==(const BlockPos& pos) const;
};


#endif //MCPELAUNCHER_BLOCKPOS_H
