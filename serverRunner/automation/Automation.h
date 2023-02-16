#pragma once

#include "../minecraftGame/IMinecraftApp.h"

namespace Automation {
    class AutomationClient {
    public:
        static inline void (*AutomationClient_ctor)(AutomationClient*, IMinecraftApp&) = nullptr;
        virtual ~AutomationClient() = default;

        char filler[3248 - 4];

        AutomationClient(IMinecraftApp& a) {
            AutomationClient_ctor(this, a);
        }
    };

}