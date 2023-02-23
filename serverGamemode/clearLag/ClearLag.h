//
// Created by user on 24.02.23.
//

#ifndef PDSERVER_CLEARLAG_H
#define PDSERVER_CLEARLAG_H


class ClearLag {
public:
    __attribute__((constructor)) static void onInit();
    static void load();
};


#endif //PDSERVER_CLEARLAG_H
