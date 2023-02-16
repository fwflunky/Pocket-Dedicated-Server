//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_DEDICATEDMINECRAFTAPP_H
#define PDSERVER_DEDICATEDMINECRAFTAPP_H

#include "IMinecraftApp.h"

class DedicatedMinecraftApp : public IMinecraftApp {
public:
    Automation::AutomationClient* automationClient = nullptr;

    Minecraft* getPrimaryMinecraft() override;
    Automation::AutomationClient* getAutomationClient() override;
    bool isEduMode() override;
    bool isDedicatedServer() override;
    int getDefaultNetworkMaxPlayers() override;
    void onNetworkMaxPlayersChanged(unsigned int max) override;
};


#endif //PDSERVER_DEDICATEDMINECRAFTAPP_H
