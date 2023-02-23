//
// Created by user on 23.02.23.
//

#ifndef PDSERVER_CUSTOMPERMISSIONS_H
#define PDSERVER_CUSTOMPERMISSIONS_H


#include <string>
#include <unordered_map>

class CustomPermissions {
public:
    static unsigned char StringToCommandPermissionLevel(const std::string& pname);
    static inline std::unordered_map<std::string, unsigned char>* permissions;
    static inline void* StringToCommandPermissionLevel_orig = nullptr;
};


#endif //PDSERVER_CUSTOMPERMISSIONS_H
