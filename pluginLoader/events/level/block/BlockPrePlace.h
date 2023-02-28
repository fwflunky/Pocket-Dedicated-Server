//
// Created by user on 28.02.23.
//

#ifndef PDSERVER_BLOCKPREPLACE_H
#define PDSERVER_BLOCKPREPLACE_H


#include "../../EventObject.h"
namespace PluginEventing {
class BlockPrePlace : public EventObject {
    public:
        static inline const std::string EventName = "BlockPrePlace";

        int blockBreaked = 0;

        std::string getEventName() override {
            return EventName;
        }
    };
}


#endif //PDSERVER_BLOCKPREPLACE_H
