//
// Created by user on 01.02.23.
//

#include "SynchedEntityData.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"

void SynchedEntityData::initHooks(void *handle) {
    SynchedEntityData_getInt = (int (*)(SynchedEntityData*, unsigned short)) hybris_dlsym(handle, "_ZNK17SynchedEntityData6getIntEt");
}

int SynchedEntityData::getInt(unsigned short param) {
    return SynchedEntityData_getInt(this, param);
}
