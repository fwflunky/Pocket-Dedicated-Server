//
// Created by user on 09.02.23.
//

#ifndef MCPELAUNCHER_CONTAINER_H
#define MCPELAUNCHER_CONTAINER_H


#include <string>

class Container { //72
public:
    static void initHooks(void* handle);
    static inline void (*Container_setCustomName)(Container*, std::string const&) = nullptr;

    virtual ~Container() = default;

    char filler1[60];
    std::string* customName;
    bool nameChanged;

    void setCustomName(std::string const& name);
};


#endif //MCPELAUNCHER_CONTAINER_H
