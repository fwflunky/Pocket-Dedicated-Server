#pragma once

#include "App.h"
#include "../src/log.h"
#include "../src/LevelSettings.h"
#include "../server/network/ServerNetworkHandler.h"
#include "../server/eventing/MinecraftEventing.h"
#include "../server/network/networkHandler/NetworkHandler.h"
class Options;
class GuiData;
//#include "../src/BotInstance.h"
class ClientInstance {
public:
    static inline void(*ClientInstance_quit)(void* self) = nullptr;
    /* ClientInstance::ClientInstance(MinecraftGame&, IMinecraftApp&, SoundEngine&,
   minecraft::api::Api&, FilePathManager*, MinecraftEventing&) */
    //_ZN14ClientInstanceC2ER13MinecraftGameR13IMinecraftAppR11SoundEngineRN9minecraft3api3ApiEP15FilePathManagerR17MinecraftEventing
    static inline void(*ClientInstance_ctor)(ClientInstance* self, void* mg, void* app, void* se, void* api, void* fpm, void* ev) = nullptr;
    static inline void(*ClientInstance_onTick)(ClientInstance* self, int, int) = nullptr;
    static inline ClientInstance* inst = nullptr;

    static inline void ctor(ClientInstance* self, void* mg, void* app, void* se, void* api, void* fpm, void* ev);
    void onTick(int, int);
    void quit();
};


class LevelSummary {
public:
    std::string id;
    std::string name;
    char filler[0x100];
    static inline void(*LevelSummary_construct)(LevelSummary* self) = nullptr;

    LevelSummary(){
        LevelSummary_construct(this);
    }
};


class LocalWorldInfo {
public:
    //char filler[64];
    static inline void (*LocalWorldInfo_construct2)(LocalWorldInfo* self, LevelSummary const& summary) = nullptr;
    static inline LevelSummary& (*LocalWorldInfo_getLevelSummary)(LocalWorldInfo* self) = nullptr;
    LevelSummary& getLevelSummary(){
        return LocalWorldInfo_getLevelSummary(this);
    }
    LocalWorldInfo(LevelSummary const& s){
        LocalWorldInfo_construct2(this, s);
    }
    // std::string s1;
};

class MinecraftScreenModel {
public:
    static inline void(*MinecraftScreenModel_startLocalServer)(MinecraftScreenModel* self, LevelSummary const&) = nullptr;
    static inline void(*MinecraftScreenModel_executeCommand)(MinecraftScreenModel* self, std::string const&) = nullptr;
    static inline void(*MinecraftScreenModel_ctor)(MinecraftScreenModel* self, void*, void*) = nullptr;

    static inline MinecraftScreenModel* inst = nullptr;
    static void ctor(MinecraftScreenModel* self, void* p1, void* p2){
        std::cout << "MinecraftScreenModel ctor\n";
        inst = self;
        MinecraftScreenModel_ctor(self, p1, p2);
    }

    char filler[0x09];
    void* clientInstance;

    static void startLocalServer(){
      //  std::cout << std::string(p.filler, 64) << "\n";
        LevelSummary lsum;
        lsum.id = "bAwAAPcqAAA=";
        lsum.name = "Atmosphere";
        //std::cout << lsum.id << "\n"; //3wIAAF9AAAA=
       // std::cout << lsum.name << "\n"; //My World

       // LocalWorldInfo info(lsum);
        std::cout << lsum.id<< "\n";
        MinecraftScreenModel_startLocalServer(inst, lsum);
    }

   // static void executeCmd(const std::string& cmd){
       // MinecraftScreenModel_executeCommand(inst, cmd);
   // }
};

class AutomationClient {
public:
    char filler[3239];
    bool requireEncryption;
};

class Minecraft {
public:
char filler[35];
NetworkHandler::NetworkHandler* networkHandler;
char filler1[52];
MinecraftCommands* cmds;
};

class MinecraftGame : public App {

public:

    char filler [0x4000];
    static inline void (*MinecraftGame_construct)(MinecraftGame*, int, char**) = nullptr;
    static inline void (*MinecraftGame_update)(MinecraftGame*) = nullptr;
    static inline void (*MinecraftGame_setRenderingSize)(MinecraftGame*, int, int) = nullptr;
    static inline MinecraftEventing* (*MinecraftGame_getEventing)(MinecraftGame*) = nullptr;
    static inline void (*MinecraftGame_startLocalServer)(MinecraftGame*, std::string, std::string, std::string, std::string, LevelSettings) = nullptr;
    static inline void (*MinecraftGame_setUISizeAndScale)(MinecraftGame*, int, int, float) = nullptr;
    static inline void (*MinecraftGame_handleResourcePackConfirmation)(MinecraftGame*, int, bool) = nullptr;
    static inline void (*MinecraftGame_setServerToTransfer)(MinecraftGame*, const std::string&, unsigned short) = nullptr;
    static inline GuiData* (*MinecraftGame_getGuiData)(MinecraftGame*) = nullptr;
    static inline Options* (*MinecraftGame_getOptions)(MinecraftGame*) = nullptr;
    static inline Minecraft* (*MinecraftGame_getMinecraft)(MinecraftGame*) = nullptr;
    static inline AutomationClient* (*MinecraftGame_getAutomationClient)(MinecraftGame*) = nullptr; //_ZNK13MinecraftGame19getAutomationClientEv
    static inline ServerNetworkHandler* (*MinecraftGame_getServerNetworkHandler)(MinecraftGame*) = nullptr;

    MinecraftGame(int carg, char** args);

    void update();

    void setRenderingSize(int w, int h);

    bool useTouchscreen();

    void handleResourcePackConfirmation(int p1, bool p2);

    void setUISizeAndScale(int w, int h, float px);

    void setServerToTransfer(const std::string& ip, unsigned short port);

    void onTransfer(const std::string& ip, unsigned short port);

    MinecraftEventing* getEventing();

    /* MinecraftGame::startLocalServer(std::basic_string<char, std::char_traits<char>,
   std::allocator<char> >, std::basic_string<char, std::char_traits<char>, std::allocator<char> >,
   std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::basic_string<char,
   std::char_traits<char>, std::allocator<char> >, LevelSettings) */
    void startLocalServer(std::string, std::string, std::string, std::string, LevelSettings);
    ServerNetworkHandler* getServerNetworkHandler();

    Options* getOptions();

    GuiData* getGuiData();

};

