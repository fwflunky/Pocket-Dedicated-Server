#pragma once

#include "IMinecraftApp.h"

namespace Automation {

    class AutomationClient {

    public:
        static void (*AutomationClient_construct)(AutomationClient*, IMinecraftApp&);

        char filler[0x300];

        //static inline IMinecraftApp* imapp = nullptr;
        AutomationClient(IMinecraftApp& a) {
           // imapp = &a;
            AutomationClient_construct(this, a);
        }


    };

}