//
// Created by user on 27.02.23.
//

#ifndef PDSERVER_PLUGININTERFACE_H
#define PDSERVER_PLUGININTERFACE_H

#include <string>
#include <boost/dll.hpp>

class BOOST_SYMBOL_VISIBLE PluginInterface {
public:
    struct pluginInstance {
        boost::dll::shared_library lib;
        boost::shared_ptr<PluginInterface> thisPlugin;
    };

    virtual ~PluginInterface() = default;
    virtual std::string getName() = 0;

    virtual void onLoad() = 0;
    virtual void onUnload() = 0;

    virtual bool isEnabled() = 0;
};
#endif //PDSERVER_PLUGININTERFACE_H
