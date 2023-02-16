//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_ORIGINALWHITELIST_H
#define PDSERVER_ORIGINALWHITELIST_H

#include <vector>

class OriginalWhiteList {
    struct Entry {
        char filler[0x20];
    };

    std::vector<Entry> entries;
};


#endif //PDSERVER_ORIGINALWHITELIST_H
