//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_STATICS_H
#define MCPELAUNCHER_STATICS_H


#include <functional>
#include <iomanip>
#include "../server/network/ServerNetworkHandler.h"
#include "../serverRunner/minecraftGame/Minecraft.h"

class statics {
public:
    static inline ServerNetworkHandler* serverNetworkHandler = nullptr;
    static inline Minecraft* minecraft = nullptr;
    static inline std::mutex onTickLock;
    static inline std::mutex waitForFuncRuns;

    static inline std::function<void()> runFunc = nullptr;
    static void runOnNextTick(std::function<void()> func) {
        waitForFuncRuns.lock();
        std::scoped_lock<std::mutex> lock(onTickLock);
        runFunc = std::move(func);
    }

    class log {
    public:
        static std::string getDate(){
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::stringstream ss;
            ss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
            return ss.str();
        }

        static void info(const std::string& message) {
            std::string type = "\033[1;37m[ \033[1;36mINFO \033[1;37m] \033[0m";
            std::string date = "\033[1;37m[ \033[1;36m"+getDate() +" \033[1;37m] \033[0m";
            std::cout << type << date << " \033[1;32m"+message+"\033[0m\n";
        }

        static void error(const std::string& message) {
            std::string type = "\033[1;37m[ \033[1;31mERROR \033[1;37m] \033[0m";
            std::string date = "\033[1;37m[ \033[1;31m"+getDate() +" \033[1;37m] \033[0m";
            std::cout << type << date << " \033[1;30m\033[1;41m"+message+"\033[0m\n";
        }
    };
};


#endif //MCPELAUNCHER_STATICS_H
