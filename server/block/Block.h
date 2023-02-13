

#ifndef MCPELAUNCHER_BLOCK_H
#define MCPELAUNCHER_BLOCK_H


#include <string>
#include "../material/Material.h"
#include <map>

class Block {
public:
    static void initHooks(void* handle);

    static inline void (*Block_setDestroyTime)(Block*, float) = nullptr;
    static inline Block** Block_Blocks = nullptr;

    char filler[4];
    unsigned char blockId;
    std::string fullBlockName; //4
    std::string blockName; //4
    char filler1[36];
    Material* material;
    //bs.getBlock(pos)
    char filler2[569];


    void setDestroyTime(float time);
};


#endif //MCPELAUNCHER_BLOCK_H
