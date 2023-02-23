//
// Created by user on 24.02.23.
//

#ifndef PDSERVER_MAINCHUNKSOURCE_H
#define PDSERVER_MAINCHUNKSOURCE_H


#include "ChunkSource.h"

class MainChunkSource : public ChunkSource { //MainChunkSource 52 size
public:
    static void initHooks(void* handle);

    std::unordered_map<ChunkPos, bool, ChunkPos::HashFunction> chunks;
    ~MainChunkSource() override = default;
private:
    __attribute__((constructor)) static void onInit();
};


#endif //PDSERVER_MAINCHUNKSOURCE_H
