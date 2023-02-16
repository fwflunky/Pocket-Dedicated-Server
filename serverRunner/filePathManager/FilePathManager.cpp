//
// Created by user on 16.02.23.
//

#include "FilePathManager.h"

FilePathManager::FilePathManager(std::string str, bool b)  {
    FilePathManager_construct(this, std::move(str), b);
}
