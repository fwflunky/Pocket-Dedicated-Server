//
// Created by user on 28.02.23.
//

#ifndef PDSERVER_PLUGINEVENTING_H
#define PDSERVER_PLUGINEVENTING_H


#include <vector>
#include <map>
#include <functional>
#include "events/EventObject.h"
namespace PluginEventing {
    enum class EventPriority {
        LOW = 0,
        MEDIUM,
        HIGH
    };

    struct EventSubscriber {
        std::string eventName;
        std::function<void(EventObject &event)> callable;
    };
    class PluginEventing {
    public:

        static inline PluginEventing* instance = nullptr;
        static void initEventing();
        static void callEvent(EventObject &eObj);

        virtual void subscribe(EventPriority ePrior, EventSubscriber eSub);
    private:
        static inline std::map<EventPriority, std::vector<EventSubscriber>, std::greater<>> subscribers;
    };
}


#endif //PDSERVER_PLUGINEVENTING_H
