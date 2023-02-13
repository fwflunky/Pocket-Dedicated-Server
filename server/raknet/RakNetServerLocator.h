//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_RAKNETSERVERLOCATOR_H
#define MCPELAUNCHER_RAKNETSERVERLOCATOR_H

#include <string>
class __attribute__((packed)) RakNetServerLocator {
public:
    static void initHooks(void* handle);
    static inline void (*RakNetServerLocator_announceServer)(RakNetServerLocator*, std::string const&, std::string const&, int, int, int) = nullptr;

    void announceServer(std::string const&, std::string const&, int, int, int);
};


#endif //MCPELAUNCHER_RAKNETSERVERLOCATOR_H
