//
// Created by user on 28.02.23.
//

#ifndef PDSERVER_EVENTOBJECT_H
#define PDSERVER_EVENTOBJECT_H


#include <string>
namespace PluginEventing {
    class EventObject {
    public:
        virtual std::string getEventName() = 0;

        virtual bool isCancelled() final;

        virtual void setCancelled(bool c = true) final;

    private:
        bool cancelled = false;
    };
}

#endif //PDSERVER_EVENTOBJECT_H
