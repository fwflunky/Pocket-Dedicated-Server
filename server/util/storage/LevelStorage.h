//
// Created by user on 22.02.23.
//

#ifndef PDSERVER_LEVELSTORAGE_H
#define PDSERVER_LEVELSTORAGE_H


class LevelStorage {
public:
    void** vtable;
    char filler[0x200];
};


#endif //PDSERVER_LEVELSTORAGE_H
