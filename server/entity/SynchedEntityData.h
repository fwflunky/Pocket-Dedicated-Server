//
// Created by user on 01.02.23.
//

#ifndef MCPELAUNCHER_SYNCHEDENTITYDATA_H
#define MCPELAUNCHER_SYNCHEDENTITYDATA_H


class SynchedEntityData {
public:
    static void initHooks(void* handle);

    static inline int (*SynchedEntityData_getInt)(SynchedEntityData*, unsigned short param) = nullptr;

    int getInt(unsigned short param);
};


#endif //MCPELAUNCHER_SYNCHEDENTITYDATA_H
