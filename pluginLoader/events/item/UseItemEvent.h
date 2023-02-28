//
// Created by user on 28.02.23.
//

#ifndef PDSERVER_UseItemEvent_H
#define PDSERVER_UseItemEvent_H


#include "../EventObject.h"
#include "../../dataWrapper/player/Player.h"
#include "../../dataWrapper/item/Item.h"
#include "../../dataWrapper/level/BlockPos.h"

namespace PluginEventing {
class UseItemEvent : public EventObject {
    public:
        static inline const std::string EventName = "UseItemEvent";
        ~UseItemEvent() {
            delete player;
            delete pos;
            delete item;
        }

        dataWrapper::Player* player;
        dataWrapper::BlockPos* pos;
        dataWrapper::Item* item;

        std::string getEventName() override {
            return EventName;
        }
    };
}


#endif //PDSERVER_UseItemEvent_H
