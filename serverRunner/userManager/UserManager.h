//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_USERMANAGER_H
#define PDSERVER_USERMANAGER_H

namespace Social {
    class UserManager {
    public:
        static inline void (*UserManager_construct)(UserManager*) = nullptr;
        UserManager();

        char filler[0x300];

    };
}


#endif //PDSERVER_USERMANAGER_H
