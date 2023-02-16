//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_API_H
#define PDSERVER_API_H


#include <string>

namespace minecraft::api {
    class Api {
    public:
        void **vtable;
        std::string envPath;
        void **playerIfaceVtable;
        void **networkIfaceVtable;
    };

}


#endif //PDSERVER_API_H
