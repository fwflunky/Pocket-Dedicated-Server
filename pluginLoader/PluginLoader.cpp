//
// Created by user on 27.02.23.
//

#include "PluginLoader.h"
#include "spdlog/spdlog.h"
#include <filesystem>
#include "range/v3/view/filter.hpp"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "PluginEventing.h"

void PluginLoader::loadPlugins(const std::string &path) {

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        auto ppath = entry.path().string();
        if(!entry.is_directory() && ppath.contains("_pds.so")) {
            //try {
                auto plugin = PluginInterface::pluginInstance{
                        .lib = boost::dll::shared_library(boost::dll::fs::path(ppath), boost::dll::load_mode::rtld_now)
                };
                if(!plugin.lib.has("PDSPlugin")){
                    spdlog::error("\"PDSPlugin\" symbol doesn't exists in plugin {0}", ppath);
                    throw std::exception();
                }
                plugin.thisPlugin = boost::dll::import_symbol<PluginInterface>(
                        plugin.lib,
                        "PDSPlugin"
                );
                if(plugin.lib.has("PDSLogger")){
                    auto* logger = new spdlog::logger(plugin.thisPlugin->getName(), std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
                    logger->set_pattern("[\033[1;34m%H:%M:%S\033[0m] [\033[1;31m"+logger->name()+"\033[1;24m\033[0m] [%^%l%$] %v");
                    plugin.lib.get<spdlog::logger*>("PDSLogger") = logger;
                }
                if(plugin.lib.has("PDSEventing")){
                    spdlog::debug("{0} eventing", ppath);
                    plugin.lib.get<PluginEventing::PluginEventing*>("PDSEventing") = PluginEventing::PluginEventing::instance;
                }

                spdlog::debug("Loaded plugin {0}", plugin.thisPlugin->getName());
                pluginList.push_back(std::move(plugin));
           // } catch (...){
           //     spdlog::error("Unable to load plugin {0}", ppath);
           // }
        }
    }
}

void PluginLoader::callOnLoad() {
    for (const auto& plugin : pluginList | ranges::views::filter([](const auto& plugin) {
        return plugin.thisPlugin->isEnabled();
    })) {
        plugin.thisPlugin->onLoad();
    }
}

void PluginLoader::callOnUnload() {
    for (const auto& plugin : pluginList | ranges::views::filter([](const auto& plugin) {
        return plugin.thisPlugin->isEnabled();
    })) {
        plugin.thisPlugin->onUnload();
    }
}
