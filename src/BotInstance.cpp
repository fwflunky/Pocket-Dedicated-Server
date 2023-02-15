//
// Created by user on 05.01.23.
//

#include "BotInstance.h"
#include "common.h"
#include "fmod_symbols.h"
#include "gles_symbols.h"
#include "android_symbols.h"
#include "egl_symbols.h"
#include "hook.h"
#include "../hybris/include/hybris/dlfcn.h"
#include <EGL/egl.h>
#include <iostream>
#include <filesystem>
#include <random>
#include "../hybris/include/hybris/hook.h"
#include "../hybris/src/jb/linker.h"
extern "C" {

#include <eglut.h>
#include "../hybris/include/hybris/dlfcn.h"
#include "../hybris/include/hybris/hook.h"
#include "../hybris/src/jb/linker.h"

}
#include "LinuxAppPlatform.h"
#include "../mcpe/ScreenChooser.h"
#include "../mcpe/Multitouch.h"
#include "log.h"
//#include "../mcpe/MinecraftScreenModel.h"
#include "../mcpe/Keyboard.h"
#include "../mcpe/Mouse.h"
#include "KeyManager.h"
#include "Automation.h"
#include "Lists.h"
#include "../mcpe/GuiData.h"
#include "LevelSettings.h"
#include "ServerInstance.h"
#include "../server/network/ServerNetworkHandler.h"
#include "../server/player/ServerPlayer.h"
#include "../server/player/Player.h"
#include "../server/player/inventory/Inventory.h"
#include "../server/player/inventory/Container.h"
#include "../server/player/inventory/PlayerInventoryProxy.h"
#include "../server/player/inventory/FillingContainer.h"
#include "../server/statics.h"
#include "../server/eventing/MinecraftEventing.h"
#include "../server/network/packets/TextPacket.h"
#include "../server/network/packets/UpdateBlockPacket.h"
#include "../server/network/packets/MinecraftPackets.h"
#include "../server/level/Dimension.h"
#include "../server/level/Level.h"
#include "../server/raknet/RakNetServerLocator.h"
#include "../server/gameMode/GameMode.h"
#include "../server/gameMode/SurvivalMode.h"
#include "../server/item/ItemInstance.h"
#include "../server/item/FlintAndSteelItem.h"
#include "../server/math/vec3/Vec3.h"
#include "../server/math/vec2/Vec2.h"
#include "../server/math/aabb/AABB.h"
#include "../server/level/BlockSource.h"
#include "../server/block/Block.h"
#include "../server/item/Item.h"
#include "../server/network/networkHandler/Connection.h"
#include "../server/network/packets/MovePlayerPacket.h"
#include "../server/network/packets/SetTitlePacket.h"
#include "../server/player/certificate/Certificate.h"
#include "../server/network/packets/ContainerSetSlotPacket.h"
#include "../server/network/networkHandler/NetworkHandler.h"
#include "../server/network/networkHandler/RakNetInstance.h"
#include "../server/network/networkHandler/RakPeer.h"
#include "../server/network/networkPeer/EncryptedNetworkPeer.h"
#include "../server/network/networkPeer/BatchedNetworkPeer.h"
#include "../server/MinecraftObjectLayer.h"
#include "../server/whitelist/Whitelist.h"
#include "../server/entity/SynchedEntityData.h"
#include "../server/entity/monster/Monster.h"
#include "../server/entity/classes/Arrow.h"
#include "../server/entity/teleportComponent/TeleportComponent.h"
#include "../server/entity/mob/Mob.h"
#include "../server/entity/mob/MobEffectInstance.h"
#include "../server/level/chunk/ChunkPos.h"
#include "../server/level/chunk/ChunkSource.h"
#include "../server/commands/CommandOrigin.h"
#include "../server/commands/CommandPropertyBag.h"
#include "../server/commands/Command.h"
#include "../server/commands/ServerCommands.h"
#include "../server/commands/MinecraftCommands.h"
#include "../server/commands/PlayerCommandOrigin.h"
#include "../server/level/explodeComponent/ExplodeComponent.h"
#include "../serverGamemode/regionGuard/RegionGuard.h"
#include "../serverGamemode/spawnColors/SpawnColors.h"
#include "../serverGamemode/tpa/Tpa.h"
#include "../serverGamemode/bans/Bans.h"

void (*original_onChatMessage)(void* Hud, const std::string& str1);

void onChatMessage(void* Hud, const std::string& str1){
    std::cout << "CHAT: " << str1 << "\n";
    (*original_onChatMessage)(Hud, str1);
}

class sd {
	public:
	unsigned short port;

	char hostAddress[32];
	char filler [64];

};

void (*original_rak)(sd* inst, unsigned short, char*);
void (*original_rakpeer)(void* inst, unsigned int, sd*, unsigned int, int);
void rakpeer(void* inst, unsigned int s, sd* ss, unsigned int sss, int ssss){
	//sd* dat = new sd;
	//static unsigned short port = 9999;
	//original_rak(dat, ss->port, "194.58.33.88");
	char* ipp = std::getenv("BOTIP");
	if(ipp){
		std::string ip = ipp;
	for(int i = 0; i < ip.size(); i++)
	ss->hostAddress[i] = ip[i];
	for(int i = 0; i < 32 - ip.size(); i++) 
	ss->hostAddress[ip.size()+i] = '\0';
	}
	
	
	
	
	std::cout << "rakpeer " << ss->hostAddress << "\n";
	
	original_rakpeer(inst, s, ss, sss, ssss);
}

//_ZN6RakNet7RakPeer22SetOfflinePingResponseEPKcj
void (*original_SetOfflinePingResponse)(sd* inst, char* d, int l);
void SetOfflinePingResponse(sd* inst, char* d, int l){
    std::cout << d << "\n";
}

int ww = 720;
int hh = 420; 

BotInstance::BotInstance() {
    lock.lock();
    if(!std::getenv("GUI")){
    	ww = 1;
        hh = 1;
    }
    Logger::init();

    setenv("LC_ALL", "C", 1);
    if(!loaded) {
        //std::cout << "load fmod\n";
        glesLib = loadLibraryOS("libGLESv2.so", gles_symbols);
        fmodLib = loadLibraryOS(getCWD() + "libs/native/libfmod.so.8.2", fmod_symbols);
        stubSymbols(android_symbols, (void*) androidStub);
        stubSymbols(egl_symbols, (void*) eglStub);
        hybris_hook("eglGetProcAddress", (void*) eglGetProcAddress);
        hybris_hook("mcpelauncher_hook", (void*) hookFunction);
        hookAndroidLog();

        if (!loadLibrary("libc.so") || !loadLibrary("libstdc++.so") || !loadLibrary("libm.so") || !loadLibrary("libz.so"))
            return;
        // load stub libraries
        if (!loadLibrary("libandroid.so") || !loadLibrary("liblog.so") || !loadLibrary("libEGL.so") || !loadLibrary("libGLESv2.so") || !loadLibrary("libOpenSLES.so") || !loadLibrary("libfmod.so") || !loadLibrary("libGLESv1_CM.so"))
            return;
        if (!loadLibrary("libmcpelauncher_mod.so"))
            return;
    }
    if (glesLib == nullptr || fmodLib == nullptr)
        return;


    //std::cout << "loading MCPE\n";
    std::string copyName = getCWD() + "libs/libminecraftpe" + std::to_string(libCount++) + ".so";
    try {
        std::filesystem::remove(copyName);
    } catch(...){}
    std::filesystem::copy(getCWD() + "libs/libminecraftpe.so", copyName);
    handle = hybris_dlopen(copyName.c_str(), RTLD_NOW);
    //std::cout << copyName << "\n";

    if (handle == nullptr) {
        std::cout << "failed to load MCPE: " << hybris_dlerror() << "\n";
        lock.unlock();
        return;
    }
   // std::cout << handle << " is handle addr\n";
    addHookLibrary(handle, copyName);
    //std::filesystem::remove(copyName);
    unsigned int libBase = ((soinfo*) handle)->base;
    std::cout << "loaded MCPE (at " << libBase << ")\n";

   // appPlatform.hardwareInformation->deviceModel = "ssmodel";

    applyPatches();
    initialized = true;
   // startBot();
}

void BotInstance::applyPatches() {
    auto patchOff = (unsigned int) hybris_dlsym(handle, "_ZN12AndroidStore21createGooglePlayStoreERKSsR13StoreListener");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::createStoreHookFunc, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroidC2ER11HTTPRequest");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::constructLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid4sendEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::sendLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid5abortEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::abortLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat10threadpool16detach_from_javaEPv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::detachFromJavaStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat11get_jvm_envEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::getJVMEnvStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN3web4http6client7details22verify_X509_cert_chainERKSt6vectorISsSaISsEERKSs");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::verifyCertChainStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config24get_app_config_singletonEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::xboxGetAppConfigSingleton, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config11set_sandboxESs");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::xboxConfigSetSandboxStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config29set_title_telemetry_device_idERKSs");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::xboxConfigSetSandboxStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN15PatchNotesModel17preloadPatchNotesEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::patchNotesModelStub, true);

    Network::mceUUID::asString = (std::string (*)(Network::mceUUID const&)) hybris_dlsym(handle, "_ZNK3mce4UUID8asStringEv");

    std::cout << "apply patches3\n";
    ScreenChooser::construct = (void (*)(ScreenChooser *, MinecraftGame *, void *, bool)) hybris_dlsym(handle, "_ZN13ScreenChooserC2ER13MinecraftGameR14ClientInstanceb");

    gl::getOpenGLVendor = (std::string (*)()) hybris_dlsym(handle, "_ZN2gl15getOpenGLVendorEv");
    gl::getOpenGLRenderer = (std::string (*)()) hybris_dlsym(handle, "_ZN2gl17getOpenGLRendererEv");
    gl::getOpenGLVersion = (std::string (*)()) hybris_dlsym(handle, "_ZN2gl16getOpenGLVersionEv");
    gl::getOpenGLExtensions = (std::string (*)()) hybris_dlsym(handle, "_ZN2gl19getOpenGLExtensionsEv");
    mce::Platform::OGL::OGL_initBindings = (void (*)()) hybris_dlsym(handle, "_ZN3mce8Platform3OGL12InitBindingsEv");

    // init linux app platform
    AppPlatform::myVtable = (void**) hybris_dlsym(handle, "_ZTV11AppPlatform");
    AppPlatform::_singleton = (AppPlatform**) hybris_dlsym(handle, "_ZN11AppPlatform10mSingletonE");
    AppPlatform::AppPlatform_construct = (void (*)(AppPlatform*)) hybris_dlsym(handle, "_ZN11AppPlatformC2Ev");
    AppPlatform::AppPlatform_initialize = (void (*)(AppPlatform*)) hybris_dlsym(handle, "_ZN11AppPlatform10initializeEv");
    AppPlatform::AppPlatform__fireAppFocusGained = (void (*)(AppPlatform*)) hybris_dlsym(handle, "_ZN11AppPlatform19_fireAppFocusGainedEv");


    MinecraftGame::App_init = (void (*)(App*, AppContext&)) hybris_dlsym(handle, "_ZN3App4initER10AppContext");
    MinecraftGame::MinecraftGame_construct = (void (*)(MinecraftGame*, int, char**)) hybris_dlsym(handle, "_ZN13MinecraftGameC2EiPPc");
    MinecraftGame::MinecraftGame_update = (void (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame6updateEv");
    MinecraftGame::MinecraftGame_setRenderingSize = (void (*)(MinecraftGame*, int, int)) hybris_dlsym(handle, "_ZN13MinecraftGame16setRenderingSizeEii");
    MinecraftGame::MinecraftGame_setUISizeAndScale = (void (*)(MinecraftGame*, int, int, float)) hybris_dlsym(handle, "_ZN13MinecraftGame17setUISizeAndScaleEiif");
    MinecraftGame::MinecraftGame_getOptions = (Options* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame10getOptionsEv");
//Entity::Entity_getNameTag = (std::string* (*)(Entity&)) hybris_dlsym(handle, "_ZNK6Entity10getNameTagEv");
    MinecraftGame::MinecraftGame_getGuiData = (GuiData* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame10getGuiDataEv");
    MinecraftGame::MinecraftGame_getServerNetworkHandler = (ServerNetworkHandler* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame23getServerNetworkHandlerEv");
    MinecraftGame::MinecraftGame_getEventing = (MinecraftEventing* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZNK13MinecraftGame11getEventingEv");
    MinecraftGame::MinecraftGame_getMinecraft = (Minecraft* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame12getMinecraftEv");
    MinecraftGame::MinecraftGame_getAutomationClient = (AutomationClient* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZNK13MinecraftGame19getAutomationClientEv");



    //NetworkHandler::NetworkHandler_closeConnection = (void (*)(NetworkHandler*, NetworkIdentifier const&, std::string const&)) hybris_dlsym(handle, "_ZN14NetworkHandler15closeConnectionERK17NetworkIdentifierRKSs");
    hookFunction((void*) hybris_dlsym(handle, "_ZN7GuiData10addMessageERKSsS1_ibb"), (void*) &GuiData::addMessage, (void**) &GuiData::GuiData_addMessage);
    hookFunction((void*) hybris_dlsym(handle, "_ZN14ClientInstance6onTickEii"), (void*) &ClientInstance::onTick, (void**) &ClientInstance::ClientInstance_onTick);

    NetworkIdentifier::initHooks(handle);
    ServerNetworkHandler::initHooks(handle);
    Entity::initHooks(handle);
    Player::initHooks(handle);
    Inventory::initHooks(handle);
    PlayerInventoryProxy::initHooks(handle);
    FillingContainer::initHooks(handle);
    Vec3::initHooks(handle);
    Vec2::initHooks(handle);
    ServerPlayer::initHooks(handle);
    Container::initHooks(handle);
    SetTitlePacket::initHooks(handle);
    MinecraftEventing::initHooks(handle);
    Dimension::initHooks(handle);
    Level::initHooks(handle);
    TeleportComponent::initHooks(handle);
    RakNetServerLocator::initHooks(handle);
    GameMode::initHooks(handle);
    ItemInstance::initHooks(handle);
    FlintAndSteelItem::initHooks(handle);
    BlockSource::initHooks(handle);
    RakNetInstance::initHooks(handle);
    Bans::init();
    RakPeer::initHooks(handle);
    Block::initHooks(handle);
    Item::initHooks(handle);
    MinecraftPackets::initHooks(handle);
    NetworkHandler::Connection::initHooks(handle);
    NetworkHandler::NetworkHandler::initHooks(handle);
    MinecraftObjectLayer::initHooks(handle);
    BatchedNetworkPeer::initHooks(handle);
    MovePlayerPacket::initHooks(handle);
    Certificate::initHooks(handle);
    Whitelist::initHooks(handle);
    SynchedEntityData::initHooks(handle);
    Mob::initHooks(handle);
    Monster::initHooks(handle);
    AABB::initHooks(handle);
    ChunkPos::initHooks(handle);
    ChunkSource::initHooks(handle);

    TextPacket::initHooks(handle);
    UpdateBlockPacket::initHooks(handle);
    ExplodeComponent::initHooks(handle);
    MinecraftCommands::initHooks(handle);
    CommandPropertyBag::initHooks(handle);
    CommandOrigin::initHooks(handle);
    Command::initHooks(handle);
    PlayerCommandOrigin::initHooks(handle);
    ServerCommands::initHooks(handle);
    ContainerSetSlotPacket::initHooks(handle);
    Arrow::initHooks(handle);
    MobEffectInstance::initHooks(handle);

    RegionGuard::loadAllUsers();
    RegionGuard::scheduleAutoSave();
    //SpawnColors::loadBlocks();
    SpawnColors::initThreads();
    Tpa::init();
    //SpawnColors::scheduleAutoSave();


    if(!loaded) {
        basicPatches::linuxHttpRequestInternalVtable = (void **) ::operator new(8);
        basicPatches::linuxHttpRequestInternalVtable[0] = (void *) &basicPatches::LinuxHttpRequestInternal::destroy;
        basicPatches::linuxHttpRequestInternalVtable[1] = (void *) &basicPatches::LinuxHttpRequestInternal::destroy;
        // LinuxAppPlatform::initVtable(handle);
    }

    Mouse::feed = (void (*)(char, char, short, short, short, short)) hybris_dlsym(handle, "_ZN5Mouse4feedEccssss");
    Multitouch::feed = (void (*)(bool, char, short, short, int)) hybris_dlsym(handle, "_ZN10Multitouch4feedEccss");

    Keyboard::inputs = (std::vector<KeyboardAction>*) hybris_dlsym(handle, "_ZN8Keyboard7_inputsE");
    Keyboard::states = (int*) hybris_dlsym(handle, "_ZN8Keyboard7_statesE");
    Keyboard::Keyboard_feedText = (void (*)(const std::string&, bool, unsigned char)) hybris_dlsym(handle, "_ZN8Keyboard8feedTextERKSsbh");

    Options::Options_getFullscreen = (bool (*)(Options*)) hybris_dlsym(handle, "_ZNK7Options13getFullscreenEv");
    Options::Options_setFullscreen = (void (*)(Options*, bool)) hybris_dlsym(handle, "_ZN7Options13setFullscreenEb");
    // options.Options_setUsername = (void (*)(Options*, const std::string& name)) hybris_dlsym(handle, "_ZN7Options11setUsernameERKSs");
    Options::Options_setUsername = (void (*)(Options*, const std::string& name)) hybris_dlsym(handle, "_ZN7Options11setUsernameERKSs");

    void** ptr = (void**) hybris_dlsym(handle, "_ZN9crossplat3JVME");
    *ptr = (void*) 1; // this just needs not to be null

   // std::cout << "init app platform vtable\n";
    LinuxAppPlatform::initVtable(handle);


    LevelSettings::LevelSettings_construct =  (void (*)(LevelSettings*)) hybris_dlsym(handle, "_ZN13LevelSettingsC2Ev");
    LevelSummary::LevelSummary_construct =  (void (*)(LevelSummary*)) hybris_dlsym(handle, "_ZN12LevelSummaryC2Ev");
    LocalWorldInfo::LocalWorldInfo_construct2 =  (void (*)(LocalWorldInfo*, LevelSummary const&)) hybris_dlsym(handle, "_ZN14LocalWorldInfoC2ERK12LevelSummary");
  //  ServerInstance::initHooks(handle);
    LocalWorldInfo::LocalWorldInfo_getLevelSummary =  (LevelSummary& (*)(LocalWorldInfo*)) hybris_dlsym(handle, "_ZN14LocalWorldInfo15getLevelSummaryEv");
   // ServerPlayer::ServerPlayer_disconnect = (void(*)(ServerPlayer*)) hybris_dlsym(handle, "_ZN12ServerPlayer10disconnectEv");
    MinecraftScreenModel::MinecraftScreenModel_executeCommand = (void (*)(MinecraftScreenModel*, std::string const&)) hybris_dlsym(handle, "_ZN20MinecraftScreenModel14executeCommandERKSs");
    //MinecraftGame::MinecraftGame_startLocalServer = (void(*)(MinecraftGame*, std::string, std::string, std::string, std::string, LevelSettings)) hybris_dlsym(handle, "_ZN13MinecraftGame16startLocalServerESsSsSsSs13LevelSettings");
    hookFunction((void*) hybris_dlsym(handle, "_ZN13MinecraftGame16startLocalServerESsSsSsSs13LevelSettings"), (void*) &MinecraftGame::startLocalServer, (void**) &MinecraftGame::MinecraftGame_startLocalServer);
    hookFunction((void*) hybris_dlsym(handle, "_ZN20MinecraftScreenModel16startLocalServerERK12LevelSummary"), (void*) &MinecraftScreenModel::startLocalServer, (void**) &MinecraftScreenModel::MinecraftScreenModel_startLocalServer);
    hookFunction((void*) hybris_dlsym(handle, "_ZN20MinecraftScreenModelC2ER13MinecraftGameR14ClientInstance"), (void*) &MinecraftScreenModel::ctor, (void**) &MinecraftScreenModel::MinecraftScreenModel_ctor);
    //hookFunction((void*) hybris_dlsym(handle, "_ZN13LevelSettings15setGenerateDocsEb"), (void*) &LevelSettings::setGenerateDocs, (void**) &LevelSettings::LevelSettings_setGenerateDosc);


    //startLocalServer
   // Whitelist whitelist;
    //OpsList ops;



   // ServerInstance inst;
// ServerInstance::ServerInstance_construct(&instance, minecraftApp, whitelist, ops, &pathmgr, std::chrono::duration_cast<std::chrono::duration<long long>>(std::chrono::milliseconds(50)), /* world dir */ "o0ABALqqBgA=", /* world name */ "My World", mcpe::string(), skinPackKeyProvider, mcpe::string(), /* settings */ levelSettings, api, 22, true, /* (query?) port */ 19132, /* (maybe not) port */ 19132, /* max player count */ 5, /* requiresXboxLive */ false, {}, "normal", *mce::UUID::EMPTY, eventing, handler, resourcePackRepo, ctm, resourcePackManager, nullptr, [](mcpe::string const& s) {
//        std::cout << "??? " << s.c_str() << "\n";
//    });
   // ServerInstance::ServerInstance_construct(&instance, );

   // std::cout << "init app platform\n";

    /*while(true){
    client->update();
    usleep(10000);
    }*/
   // while(true);
    startBot();
}



bool BotInstance::isInitialized() const {
    return initialized;
}

void BotInstance::androidStub() {

}

void BotInstance::eglStub() {

}

int BotInstance::getMinecraftKeyCode(int keyCode) {
        if (keyCode == 65505)
            return 16;
        if (keyCode >= 97 && keyCode <= 122)
            return (keyCode + 65 - 97);
        if (keyCode >= 65470 && keyCode <= 65481)
            return (keyCode + 112 - 65470);

        return keyCode;
}

void BotInstance::startBot() {

    auto* platform = new LinuxAppPlatform();
    //std::cout << "app platform initialized\n";


    //linuxAppPlatform->Make();

    //std::cout << "init app platform vtable\n";
    //std::cout << "init app platform\n";

    // LinuxAppPlatform::initVtable(handle);
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long int> distr;
    //std::cout << "app platform initialized\n";


    eglutInitWindowSize(ww, hh);
    eglutInitAPIMask(EGLUT_OPENGL_ES2_BIT);
    char *keyword[10];
    eglutInit(0, keyword);


    auto winname = std::to_string(distr(eng));
    windowName = winname;
    eglutCreateWindow(winname.c_str());



    AppContext ctx{};
    ctx.platform = platform;
    ctx.doRender = true;

    //std::cout << "linuxAppPlatform->initialize();\n";
    platform->initialize();
    // std::cout << "linuxAppPlatform->initialize(); done\n";
    //oglInstance.initBindings();
    //if(!loaded) {
    // std::cout << "oglInstance.initBindings()\n";
    mce::Platform::OGL::initBindings();
    // std::cout << "oglInstance.initBindings() done\n";
    // }

    //std::cout << "new MinecraftGame(handle, 0, keyword);\n";
    Logger::INFO << "Запуск бота" << "\n";


        //UserAuthentication::uuidSeed = distr(eng);


    client = new MinecraftGame(0, keyword);


    // std::cout << "new MinecraftGame(handle, 0, keyword); done\n";
    //client->App_init = (void (*)(App*, AppContext&)) hybris_dlsym(handle, "_ZN3App4initER10AppContext");
    //client->Init(0, keyword);
    client->init(ctx);

   // std::uniform_int_distribution<unsigned long long int> distr2(100, 300);

    //unsigned long long int cid = distr(eng) * -distr(eng);

   // Logger::INFO << "CID будет " << cid << "\n";
   // UserAuthentication::cid = cid;

   // auto nick = "ahmed" + std::to_string(distr2(eng));

  //  Logger::INFO << "Никнейм будет " << nick << "\n";
    client->getOptions()->setUsername("");
   // botNickname = nick;
   // AppPlatform::hardwareInformation->deviceModel = device;
    (*AppPlatform::_singleton)->_fireAppFocusGained();
   // client->setServerToTransfer(currentServerAddress, currentServerPort);

    client->setRenderingSize(ww, hh);
    client->setUISizeAndScale(ww, hh, 2);
    statics::game = client;

    MinecraftGame::MinecraftGame_getAutomationClient(client)->requireEncryption = true;
    MinecraftScreenModel::startLocalServer();
    client->getServerNetworkHandler()->setMaxPlayers(70);

    //client->getServerNetworkHandler()->isTrial = true;
    //levelSettings.texturepacksRequired = false;
   // client->startLocalServer("3wIAAF9AAAA=", "My World", "", "", levelSettings);
    loaded = true;
    lock.unlock();

    static auto cli = client;
    eglutDisplayFunc([](){
        cli->update();
    });
    eglutIdleFunc([](){
        eglutPostRedisplay();
    });
    eglutKeyboardFunc([](char str[5], int action){
        if (strcmp(str, "\t") == 0)
            return;
        if (action == EGLUT_KEY_PRESS || action == EGLUT_KEY_REPEAT) {
            if (str[0] == 13) {
                str[0] = 10;
                str[1] = 0;
            }
            std::stringstream ss;
            ss << str;
            Keyboard::Keyboard_feedText(ss.str(), false, 0);
        }
    });
    eglutSpecialFunc([](int key, int action){
        if (key == 65480) { //f11
            return;
        }
        int mKey = getMinecraftKeyCode(key);
        std::cout << mKey << "\n";
        if (action == EGLUT_KEY_PRESS) {
            Keyboard::inputs->push_back({1, mKey});
            Keyboard::states[mKey] = 1;
        } else if (action == EGLUT_KEY_RELEASE) {
            Keyboard::inputs->push_back({0, mKey});
            Keyboard::states[mKey] = 0;
        }
    });
   eglutMouseButtonFunc([](int x, int y, int btn, int action){
        int mcBtn = (btn == 1 ? 1 : (btn == 2 ? 3 : (btn == 3 ? 2 : (btn == 5 ? 4 : btn))));
        Mouse::feed((char) mcBtn, (char) (action == EGLUT_MOUSE_PRESS ? (btn == 5 ? -120 : (btn == 4 ? 120 : 1)) : 0), x, y, 0, 0);
    });

    eglutMouseFunc([](int x, int y){
        if (LinuxAppPlatform::mousePointerHidden) {
            int cx = eglutGetWindowWidth() / 2;
            int cy = eglutGetWindowHeight() / 2;
            if (x != cy || y != cy) {
                Mouse::feed(0, 0, x, y, x - cx, y - cy);
                moveMouseToCenter = true;
            }
        } else {
            Mouse::feed(0, 0, x, y, 0, 0);
        }
    });

    //Multitouch::feed(true, 1, 50, 50, 0);
    //Multitouch::feed(true, 0, 50, 50, 0);

    std::thread([&]() {
        while(true){
        for (std::string cmd; std::getline(std::cin, cmd);) {
            std::cout << "Execute cmd: " << cmd << "\n";
            std::cout << "ClientInstance pointer: " << MinecraftScreenModel::inst->clientInstance << "\n";
            MinecraftScreenModel::MinecraftScreenModel_executeCommand(MinecraftScreenModel::inst, cmd);
        }
    }
    }).detach();

    eglutMainLoop();
    sleep(99999);
        while(true){

   	        //client->update();
             //  usleep(3000);
        }

}

void BotInstance::makeScreenshot(const std::string& outp) {
	if(!std::getenv("GUI")) return;
    std::string cmd = "import -window $(wmctrl -lp | awk '{print $1 \" \" $5}' | grep " + windowName + " | awk '{print $1}') " + outp + "";
    system(cmd.c_str());
}

