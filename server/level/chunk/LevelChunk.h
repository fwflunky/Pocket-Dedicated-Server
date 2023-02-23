//
// Created by user on 02.02.23.
//

#ifndef MCPELAUNCHER_LEVELCHUNK_H
#define MCPELAUNCHER_LEVELCHUNK_H

#include <unordered_map>
#include <vector>

class Entity;

class LevelChunk {
public:
    static void initHooks(void* handle);
    //static inline void (*LevelChunk_)(Player*, ItemInstance&) = nullptr;

    char filler[2868];
    std::vector<Entity*> entities;
};


#endif //MCPELAUNCHER_LEVELCHUNK_H
