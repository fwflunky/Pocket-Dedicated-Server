//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_UUID_H
#define PDSERVER_UUID_H

#include <string>

namespace mce {
    class UUID {
    public:
        static inline UUID *EMPTY = nullptr;

        static inline mce::UUID (*fromString)(std::string const &) = nullptr;

        char filler[16];
    };
}

#endif //PDSERVER_UUID_H
