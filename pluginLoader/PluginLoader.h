//
// Created by user on 27.02.23.
//

#ifndef PDSERVER_PLUGINLOADER_H
#define PDSERVER_PLUGINLOADER_H


#include <string>
#include "PluginInterface.h"
class PluginLoader {
private:
    static inline std::vector<PluginInterface::pluginInstance> pluginList;
public:
    static void loadPlugins(const std::string& path);
    static void callOnLoad();
    static void callOnUnload();
};


#endif //PDSERVER_PLUGINLOADER_H
