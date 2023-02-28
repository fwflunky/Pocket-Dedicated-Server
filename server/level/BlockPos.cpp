//
// Created by user on 27.01.23.
//

#include "BlockPos.h"
#include <cmath>
BlockPos::BlockPos(float xx, float yy, float zz) {
    x = std::floor(xx);
    y = std::floor(yy);
    z = std::floor(zz);
}

std::string BlockPos::toString() const {
    return "x=" + std::to_string(x) + ", y=" + std::to_string(y) + ", z=" + std::to_string(z);
}

BlockPos::BlockPos(int xx, int yy, int zz) {
    x = xx;
    y = yy;
    z = zz;
}

bool BlockPos::operator==(const BlockPos &pos) const {
    return x == pos.x && y == pos.y && z == pos.z;
}

BlockPos::BlockPos() {
    x = 0;
    y = 0;
    z = 0;
}
