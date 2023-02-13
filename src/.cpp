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
#include "../mcpe/MinecraftScreenModel.h"
#include "../mcpe/Keyboard.h"
#include "../mcpe/Mouse.h"
#include "KeyManager.h"

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

int ww = 720;
int hh = 420; 

BotInstance::BotInstance(const std::string &wname, const std::string &ip, int port, const BotInstance::loginData &data) {
    lock.lock();
    if(!std::getenv("GUI")){
    	ww = 1;
        hh = 1;
    }
    ldata = data;
    currentServerAddress = ip;
    currentServerPort = port;
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
    startBot();
}

void BotInstance::applyPatches() {
    //std::cout << "apply patches\n";

#define CALL_MEMBER_FN(object, ptrToMember)  ((object).*(ptrToMember))
std::cout << "apply patches\n";
    auto patchOff = (unsigned int) hybris_dlsym(handle, "_ZN12AndroidStore21createGooglePlayStoreERKSsR13StoreListener");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::createStoreHookFunc, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroidC2ER11HTTPRequest");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::constructLinuxHttpRequestInternal, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid4sendEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::sendLinuxHttpRequestInternal, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid5abortEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::abortLinuxHttpRequestInternal, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat10threadpool16detach_from_javaEPv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::detachFromJavaStub, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat11get_jvm_envEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::getJVMEnvStub, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN3web4http6client7details22verify_X509_cert_chainERKSt6vectorISsSaISsEERKSs");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::verifyCertChainStub, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config24get_app_config_singletonEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::xboxGetAppConfigSingleton, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config11set_sandboxESs");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::xboxConfigSetSandboxStub, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config29set_title_telemetry_device_idERKSs");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::xboxConfigSetSandboxStub, true);
std::cout << "apply patches\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN15PatchNotesModel17preloadPatchNotesEv");
    patchCallInstruction((void*) patchOff, (void*) &basicPatches::patchNotesModelStub, true);
std::cout << "apply patches\n";

    //patchOff = (unsigned int) hybris_dlsym(handle, "_ZN19HudScreenController19_pushNewChatMessageERKSs");
    //hookFunction((void*) patchOff, (void*) onChatMessage, (void**) &original_onChatMessage);

    //getHardwareInformation
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK11AppPlatform22getHardwareInformationEv");
   // auto callFgetHardwareInformation = AppPlatform::getHardwareInformation(((AppPlatform *)linuxAppPlatform));
    patchCallInstruction((void*) patchOff, (void*) &AppPlatform::getHardwareInformation, true);
std::cout << "apply patches2\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK18UserAuthentication17getClientRandomIdEv");
    //auto callFgetClientRandomId = UserAuthentication::getClientRandomId(&userAuthentication);
    patchCallInstruction((void*) patchOff, (void*) &UserAuthentication::getClientRandomId, true);
std::cout << "apply patches2\n";
    //_ZN20MinecraftScreenModel18displayChatMessageE


    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN18BatchedNetworkPeer10sendPacketESsN11NetworkPeer11ReliabilityEi");
    //auto callFsendPacket = Network::BatchedNetworkPeer::sendPacket(&batchedNetworkPeer);
    hookFunction((void*) patchOff, (void*) &Network::BatchedNetworkPeer::sendPacket, (void**) &Network::BatchedNetworkPeer::original_sendPacket);
std::cout << "apply patches2\n";
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN18BatchedNetworkPeer13receivePacketERSs");
   // auto callFhandlePacket = Network::BatchedNetworkPeer::handlePacket(&batchedNetworkPeer);
    hookFunction((void*) patchOff, (void*) &Network::BatchedNetworkPeer::handlePacket, (void**) &Network::BatchedNetworkPeer::original_handlePacket);
std::cout << "apply patches2\n";
    //patchOff = (unsigned int) hybris_dlsym(handle, "_ZN14ClientInstance4quitEv");
   // auto callFhandlePacket = Network::BatchedNetworkPeer::handlePacket(&batchedNetworkPeer);
    //hookFunction((void*) patchOff, (void*) &ClientInstance::quit, (void**) &ClientInstance::ClientInstance_quit);
std::cout << "apply patches2\n";
   // patchOff = (unsigned int) hybris_dlsym(handle, "_ZN14ClientInstanceC2ER13MinecraftGameR13IMinecraftAppR11SoundEngineRN9minecraft3api3ApiEP15FilePathManagerR17MinecraftEventing");
   // auto callFhandlePacket = Network::BatchedNetworkPeer::handlePacket(&batchedNetworkPeer);
  //  hookFunction((void*) patchOff, (void*) &ClientInstance::ctor, (void**) &ClientInstance::ClientInstance_ctor);
std::cout << "apply patches3\n";
    //_ZNK3mce4UUID8asStringEv
   // patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK3mce4UUID8asStringEv");
   // patchCallInstruction((void*) patchOff, (void*) &Network::mceUUID::asString, true); //segfault
    Network::mceUUID::asString = (std::string (*)(Network::mceUUID const&)) hybris_dlsym(handle, "_ZNK3mce4UUID8asStringEv");
std::cout << "apply patches3\n";
    //  patchOff = (unsigned int) hybris_dlsym(handle, "_ZN17ConnectionRequest6createER17PrivateKeyManagerRK11CertificateRKSsyS6_RKSt6vectorIhSaIhEE9InputModeiiS6_S6_6ADRole");
    // hookFunction((void*) patchOff, (void*) Network::ConnectionRequest::create, (void**) &Network::ConnectionRequest::original_create);

    //_ZN10KeyManagerC2ERKSsN6Crypto10Asymmetric6SystemE
   // patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK10KeyManager12getPublicKeyEv");
   // hookFunction((void*) patchOff, (void*) KeyManager::CryptoHash::getPublicKey, (void**) &KeyManager::CryptoHash::original_getPublicKey);
    //_ZN17PrivateKeyManagerC2EN6Crypto10Asymmetric6SystemE
   // patchOff = (unsigned int) hybris_dlsym(handle, "_ZN17PrivateKeyManagerC2EN6Crypto10Asymmetric6SystemE");
   // hookFunction((void*) patchOff, (void*) KeyManager::PrivateKeyManager::PrivateKeyManagerCtor, (void**) &KeyManager::PrivateKeyManager::original_PrivateKeyManagerCtor);

    //patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK17PrivateKeyManager4signERKSsN6Crypto4Hash8HashTypeE");
    //hookFunction((void*) patchOff, (void*) KeyManager::PrivateKeyManager::sign, (void**) &KeyManager::PrivateKeyManager::original_sign);

   // patchOff = (unsigned int) hybris_dlsym(handle, "_ZN13ScreenChooser19setDisconnectScreenERKSsS1_S1_");
  //  hookFunction((void*) patchOff, (void*) onDisconnect, (void**) &original_onDisconnect);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN13ScreenChooser19setDisconnectScreenERKSsS1_S1_");
    hookFunction((void*) patchOff, (void*) &ScreenChooser::onDisconnect, (void**) &ScreenChooser::setDisconnectScreen);
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
   // MinecraftGame::MinecraftGame_setUISizeAndScale = (void (*)(MinecraftGame*, int, int, float)) hybris_dlsym(handle, "_ZN13MinecraftGame17setUISizeAndScaleEiif");
   std::cout << "apply patches4\n";
    hookFunction((void*) hybris_dlsym(handle, "_ZN13MinecraftGame19setServerToTransferERKSss"), (void*) &MinecraftGame::onTransfer, (void**) &MinecraftGame::MinecraftGame_setServerToTransfer);
      std::cout << "apply patches4\n";
    hookFunction((void*) hybris_dlsym(handle, "_ZN13MinecraftGame30handleResourcePackConfirmationE20ResourcePackResponseb"), (void*) &MinecraftGame::handleResourcePackConfirmation, (void**) &MinecraftGame::MinecraftGame_handleResourcePackConfirmation);
      std::cout << "apply patches4\n";
    patchCallInstruction((void*) hybris_dlsym(handle, "_ZN13MinecraftGame14useTouchscreenEv"), (void*) &MinecraftGame::useTouchscreen, true);
    patchCallInstruction((void*) hybris_dlsym(handle, "_ZN17MinecraftEventing35fireGlobalResourcePackCrashRecoveryER12ResourcePackN3mce4UUIDEi"), (void*) &BotInstance::basicPatches::emptyStub1, true);
    patchCallInstruction((void*) hybris_dlsym(handle, "_ZN12ToastManager9pushToastE16ToastMessageTypeRKSsS2_S2_"), (void*) &BotInstance::basicPatches::emptyStub1, true);
    original_rak = (void(*)(sd*, unsigned short, char*)) hybris_dlsym(handle, "_ZN6RakNet16SocketDescriptorC2EtPKc");
    hookFunction((void*) hybris_dlsym(handle, "_ZN6RakNet7RakPeer7StartupEjPNS_16SocketDescriptorEji"), (void*) &rakpeer, (void**) &original_rakpeer);
MinecraftGame::MinecraftGame_getOptions = (Options* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame10getOptionsEv");
    MinecraftGame::MinecraftGame_getGuiData = (GuiData* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame10getGuiDataEv");

    //
    //_ZNK20MinecraftScreenModel31getResourcePackDownloadingStateEv

    //hookFunction((void*) hybris_dlsym(handle, "_ZN20MinecraftScreenModelC2ER13MinecraftGameR14ClientInstance"), (void*) &MinecraftScreenModel::MinecraftScreenModel, (void**) &MinecraftScreenModel::MinecraftScreenModel_construct);
    hookFunction((void*) hybris_dlsym(handle, "_ZNK20MinecraftScreenModel31getResourcePackDownloadingStateEv"), (void*) &MinecraftScreenModel::getResourcePackDownloadingState, (void**) &MinecraftScreenModel::MinecraftScreenModel_getResourcePackDownloadingState);
   // hookFunction((void*) hybris_dlsym(handle, "_ZN19ExtendedCertificate25createIdentityCertificateER17PrivateKeyManagerxxRKN3mce4UUIDERKSsS7_PKN4Json5ValueE"), (void*) &KeyManager::ExtendedCertificate::createIdentityCertificate, (void**) &KeyManager::ExtendedCertificate::ExtendedCertificate_createIdentityCertificate);
    hookFunction((void*) hybris_dlsym(handle, "_ZN18UserAuthentication20regenerateSelfSignedERKSs"), (void*) &UserAuthentication::regenerateSS, (void**) &UserAuthentication::UserAuthentication_regenerateSS);


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
   // std::cout << "init app platform\n";

    /*while(true){
    client->update();
    usleep(10000);
    }*/
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

    if(ldata.uuidSeed != 0){
        //std::cout << ldata.uuidSeed << "\n";
        UserAuthentication::uuidSeed = ldata.uuidSeed;
    } else {
        UserAuthentication::uuidSeed = distr(eng);
    }

    client = new MinecraftGame(0, keyword);


    // std::cout << "new MinecraftGame(handle, 0, keyword); done\n";
    //client->App_init = (void (*)(App*, AppContext&)) hybris_dlsym(handle, "_ZN3App4initER10AppContext");
    //client->Init(0, keyword);
    client->init(ctx);

    std::uniform_int_distribution<unsigned long long int> distr2(100, 300);

    unsigned long long int cid = distr(eng) * -distr(eng);
    if(ldata.cid != 0){
        cid = ldata.cid;
    }
    Logger::INFO << "CID будет " << cid << "\n";
    UserAuthentication::cid = cid;

    auto nick = "ahmed" + std::to_string(distr2(eng));
    if(!ldata.username.empty()){
        nick = ldata.username;
    }
    Logger::INFO << "Никнейм будет " << nick << "\n";
    client->getOptions()->setUsername(nick);
    botNickname = nick;

    std::string device = "XIAOMI MT7347672SG";
    if(!ldata.device.empty()){
        device = ldata.device;
    }
    AppPlatform::hardwareInformation->deviceModel = device;
    (*AppPlatform::_singleton)->_fireAppFocusGained();
    client->setServerToTransfer(currentServerAddress, currentServerPort);

    client->setRenderingSize(ww, hh);
    client->setUISizeAndScale(ww, hh, 2);
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
    if(std::getenv("GUI"))
        eglutMainLoop();
    else {
        while(true){
   	        client->update();
   	        usleep(3000);
        }
    }
}

void BotInstance::makeScreenshot(const std::string& outp) {
	if(!std::getenv("GUI")) return;
    std::string cmd = "import -window $(wmctrl -lp | awk '{print $1 \" \" $5}' | grep " + windowName + " | awk '{print $1}') " + outp + "";
    system(cmd.c_str());
}

