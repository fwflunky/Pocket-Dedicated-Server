//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_PACKET_H
#define MCPELAUNCHER_PACKET_H
#include <string>
#include <iostream>
#include "../NetworkIdentifier.h"

class Packet {
public:
    virtual ~Packet() = default;

    virtual unsigned char getId() {
        std::cout << "pure virtual packet getId method called\n";
        return 0x00;
    };

    virtual std::string getName() {
        std::cout << "pure virtual packet getName method called\n";
        return "packet";
    };

    virtual void write(void* bs){
        std::cout << "pure virtual packet write method called\n";
    };

    virtual void read(void* bs){
        std::cout << "pure virtual packet read method called\n";
    };

    virtual void handle(NetworkIdentifier& ident, void* netcallb){
        std::cout << "pure virtual packet handle method called\n";
    };

    virtual bool disallowBatching(){
        std::cout << "pure virtual packet disallowBatching method called\n";
        return false;
    };
    int s1 = 2;
    int s2 = 1;
};

#endif //MCPELAUNCHER_PACKET_H
