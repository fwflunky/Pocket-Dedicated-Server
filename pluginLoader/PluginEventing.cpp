//
// Created by user on 28.02.23.
//

#include "PluginEventing.h"
#include "spdlog/spdlog.h"

void PluginEventing::PluginEventing::initEventing() {
    subscribers.insert({EventPriority::LOW, {}});
    subscribers.insert({EventPriority::MEDIUM, {}});
    subscribers.insert({EventPriority::HIGH, {}});

    instance = new PluginEventing();
}

[[maybe_unused]] void PluginEventing::PluginEventing::subscribe(EventPriority ePrior, EventSubscriber eSub) {
    spdlog::debug("subscribed eventing");
    subscribers.at(ePrior).push_back(std::move(eSub));
}

void PluginEventing::PluginEventing::callEvent(EventObject &eObj) {
    for(auto& prior : subscribers){
        for(auto& sub : prior.second){
            if(sub.eventName == eObj.getEventName()) {
                sub.callable(eObj);
            }
        }
    }
}
