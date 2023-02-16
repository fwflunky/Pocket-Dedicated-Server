//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_FILEPATHMANAGER_H
#define PDSERVER_FILEPATHMANAGER_H


#include <string>

class FilePathManager {
public:
    char filler[25];
    static inline void (*FilePathManager_construct)(FilePathManager*, std::string, bool) = nullptr;

    FilePathManager(std::string str, bool b);
};


#endif //PDSERVER_FILEPATHMANAGER_H
