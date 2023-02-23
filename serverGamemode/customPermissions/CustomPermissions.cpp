//
// Created by user on 23.02.23.
//

#include "CustomPermissions.h"
#include "spdlog/spdlog.h"

unsigned char CustomPermissions::StringToCommandPermissionLevel(const std::string &pname) {
    spdlog::debug("CustomPermissions::StringToCommandPermissionLevel: get level of {0}", pname);

    if(pname == "sex"){
        return 255;
    } else if(pname == "any"){
        return 0;
    }
    return 255;
}
