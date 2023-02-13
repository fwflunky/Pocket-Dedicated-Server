//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_PLAYERCHUNKSOURCE_H
#define MCPELAUNCHER_PLAYERCHUNKSOURCE_H

#include "ChunkViewSource.h"
class Player;
class __attribute__((packed)) PlayerChunkSource : public ChunkViewSource {
public:
    char filler[151]; //192
    Player* player;
    char filler1[37];

    //todo ПОСМОТРЕТЬ КОНСТРУКТОР БЛОКСУРСА ПРИ checkBed и справнить указатели переданные в него с указателями полученными из классов level demension playerchunksource
};


#endif //MCPELAUNCHER_PLAYERCHUNKSOURCE_H
