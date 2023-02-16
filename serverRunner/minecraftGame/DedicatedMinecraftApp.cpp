//
// Created by user on 16.02.23.
//

#include <iostream>
#include "DedicatedMinecraftApp.h"

Minecraft *DedicatedMinecraftApp::getPrimaryMinecraft() {
    return nullptr;
}

Automation::AutomationClient *DedicatedMinecraftApp::getAutomationClient() {
    return automationClient;
}

bool DedicatedMinecraftApp::isEduMode() {
    return false;
}

bool DedicatedMinecraftApp::isDedicatedServer() {
    return true;
}

int DedicatedMinecraftApp::getDefaultNetworkMaxPlayers() {
    return 525;
}

void DedicatedMinecraftApp::onNetworkMaxPlayersChanged(unsigned int max) {

}
