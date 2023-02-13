#include "MinecraftGame.h"
#include "../src/BotInstance.h"
#include <string>
#include "../src/common.h"
#include "../server/statics.h"

void ClientInstance::ctor(ClientInstance *self, void *mg, void *app, void *se, void *api, void *fpm, void *ev) {
    ClientInstance_ctor(self, mg, app, se, api, fpm, ev);
    inst = self;
}

void ClientInstance::quit() {
    ClientInstance_quit(this);
}

void ClientInstance::onTick(int a, int b) {
    ClientInstance_onTick(this, a, b);
}

MinecraftGame::MinecraftGame(int carg, char **args) : App() {
    MinecraftGame_construct(this, carg, args);
}

void MinecraftGame::update() {
    MinecraftGame_update(this);
}

void MinecraftGame::setRenderingSize(int w, int h) {
    MinecraftGame_setRenderingSize(this, w, h);
}

bool MinecraftGame::useTouchscreen() {
    return true;
}

void MinecraftGame::handleResourcePackConfirmation(int p1, bool p2) {
    MinecraftGame_handleResourcePackConfirmation(this, p1, p2);
}

void MinecraftGame::setUISizeAndScale(int w, int h, float px) {
    MinecraftGame_setUISizeAndScale(this, w, h, px);
}

void MinecraftGame::setServerToTransfer(const std::string &ip, unsigned short port) {
    MinecraftGame_setServerToTransfer(this, ip, port);
}

void MinecraftGame::onTransfer(const std::string &ip, unsigned short port) {
    Logger::WARN << "Трансфер на: " << ip << ":" << port << "\n";
    BotInstance::currentServerAddress = ip;
    BotInstance::currentServerPort = port;
    setServerToTransfer(ip, port);
}

Options *MinecraftGame::getOptions() {
    return MinecraftGame_getOptions(this);
}

GuiData *MinecraftGame::getGuiData() {
    return MinecraftGame_getGuiData(this);
}

MinecraftEventing *MinecraftGame::getEventing() {
    return MinecraftGame_getEventing(this);
}

void MinecraftGame::startLocalServer(std::string p1, std::string p2, std::string p3, std::string p4, LevelSettings p5) {
    std::cout << p1 << "/" << p2 << "/" << p3 << "/" << p4 << "\n";
    // handleSignal(11, nullptr);
    MinecraftGame_startLocalServer(this, p1, p2, p3, p4, p5);
}

ServerNetworkHandler *MinecraftGame::getServerNetworkHandler() {
    return MinecraftGame_getServerNetworkHandler(this);
}
