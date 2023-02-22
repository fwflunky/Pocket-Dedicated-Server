//
// Created by user on 31.01.23.
//

#ifndef MCPELAUNCHER_WHITELIST_H
#define MCPELAUNCHER_WHITELIST_H

#include <set>
#include <string>
class Whitelist {
public:
    static inline std::set<std::string> allowedPlayers = {"ssss"};
    static void reloadFromFile();
    static bool byNickIsAllowed(const std::string& nick);
    static void initHooks(void* handle);

    static inline bool (*Whitelist_isAllowed)(Whitelist*, void* uuid, std::string const& nick) = nullptr;

    bool isAllowed(void* uuid, std::string const& nick);

};


#endif //MCPELAUNCHER_WHITELIST_H
