//
// Created by user on 13.02.23.
//

#ifndef MCPELAUNCHER_CERTIFICATE_H
#define MCPELAUNCHER_CERTIFICATE_H


#include <string>
#include <json/json.h>

class Certificate {
public:
    static void initHooks(void* handle);

    static inline Json::Value (*Certificate_getExtraData)(Certificate*, std::string const&, Json::Value const&) = nullptr;
    Json::Value vals;

    Json::Value getExtraData(std::string const& str, Json::Value const& val);
};


#endif //MCPELAUNCHER_CERTIFICATE_H
