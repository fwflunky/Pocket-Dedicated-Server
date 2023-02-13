//
// Created by user on 29.01.23.
//

#ifndef MCPELAUNCHER_BLOCKID_H
#define MCPELAUNCHER_BLOCKID_H


class BlockID {
public:
    unsigned char* id;
};

class BlockIDAndData {
public:
    unsigned char id;
    unsigned char data;
};
class FullBlock {
public:
    BlockIDAndData *blockIdAndData;
};
/*fullblock
 * 1
 * 1
*/


#endif //MCPELAUNCHER_BLOCKID_H
