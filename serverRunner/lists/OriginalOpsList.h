//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_ORIGINALOPSLIST_H
#define PDSERVER_ORIGINALOPSLIST_H

#include <vector>
class OriginalOpsList {
    struct Entry {
        char filler[0x10];
    };

    bool b;
    std::vector<Entry> entries;
};


#endif //PDSERVER_ORIGINALOPSLIST_H
