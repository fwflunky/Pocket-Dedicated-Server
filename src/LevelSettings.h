#pragma once

#include <string>

class LevelSettings {

public:

    static inline void (*LevelSettings_construct)(LevelSettings*) = nullptr;
    static inline void (*LevelSettings_setGenerateDocs)(LevelSettings*, bool) = nullptr;

    char filler[64];

    LevelSettings() {
        LevelSettings_construct(this);
    }
    void setGenerateDocs(bool ok){
        //
    }
};