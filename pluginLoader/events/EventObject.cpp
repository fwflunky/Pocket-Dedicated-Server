//
// Created by user on 28.02.23.
//

#include "EventObject.h"

bool PluginEventing::EventObject::isCancelled() {
    return cancelled;
}

void PluginEventing::EventObject::setCancelled(bool c) {
    cancelled = c;
}
