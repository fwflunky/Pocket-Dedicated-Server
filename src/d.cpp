#include <iostream>
#include <dlfcn.h>
#include <stdarg.h>
#include <cstring>
#include <memory>
#include <string>
#include <random>
#include <vector>
#include <sstream>
#include <codecvt>
#include <locale>
#include <dirent.h>
#include "gles_symbols.h"
#include "android_symbols.h"
#include "egl_symbols.h"
#include "fmod_symbols.h"
#include "../mcpe/gl.h"
#include "../mcpe/AppPlatform.h"
#include "../mcpe/MinecraftGame.h"
#include "LinuxAppPlatform.h"
#include "LinuxStore.h"
#include "../mcpe/Mouse.h"
#include "../mcpe/Keyboard.h"
#include "../mcpe/Options.h"
#include "common.h"
#include "hook.h"
#include "Network.h"
#include "KeyManager.h"
#include <thread>
#include "UserAuthentication.h"
#include "MoveInputHandler.h"

extern "C" {

#include <eglut.h>
#include "../hybris/include/hybris/dlfcn.h"
#include "../hybris/include/hybris/hook.h"
#include "../hybris/src/jb/linker.h"

}

void androidStub() {
    //std::cout << "warn: android call\n";
}

void eglStub() {
   // std::cout << "warn: egl call\n";
}

std::unique_ptr<LinuxStore> createStoreHookFunc(const std::string& idk, StoreListener& listener) {
    //std::cout << "creating fake store <" << idk << ">\n";
    return std::make_unique<LinuxStore>();
}

class HTTPRequest;

class LinuxHttpRequestInternal {
public:
    void* vtable;
    int filler1;
    HTTPRequest* request;

    void destroy() {
        //std::cout << "destroying http request\n";
    }
};
void** linuxHttpRequestInternalVtable;

void constructLinuxHttpRequestInternal(LinuxHttpRequestInternal* requestInternal, HTTPRequest* request) {
    requestInternal->vtable = linuxHttpRequestInternalVtable;
    requestInternal->request = request;
}

void sendLinuxHttpRequestInternal(LinuxHttpRequestInternal* requestInternal) {
    //std::cout << "send http request\n";
    // TODO: Implement it
}

void abortLinuxHttpRequestInternal(LinuxHttpRequestInternal* requestInternal) {
    //std::cout << "abort http request\n";
    // TODO: Implement it
}

static MinecraftGame* client;
//_ZN20MinecraftScreenModel18displayChatMessageE
void (*original_onChatMessage)(void* Hud, const std::string& str1);

void onChatMessage(void* Hud, const std::string& str1){
	std::cout << "CHAT: " << str1 << "\n";
	(*original_onChatMessage)(Hud, str1);
}


void startBotTo(const std::string& ip, int port){
	client->setServerToTransfer(ip, port);
	std::cout << "Bot started to " << ip << ":" << port << "\n";
}

void onTransfer(void* mg, const std::string& ip, int port){
	client->setServerToTransfer(ip, port);
	std::cout << "Bot transfer to " << ip << ":" << port << "\n";
}

void (*original_onDisconnect)(void* screenchooser, const std::string& a, const std::string& b, const std::string& c);
void onDisconnect(void* screenchooser, const std::string& a, const std::string& b, const std::string& c) {
    std::cout << "disconnected: " << a << " / " << b << " / " << c << "\n";
    (*original_onDisconnect)(screenchooser, a, b, c);
   // exit(1);
}

int winId = 0;
bool moveMouseToCenter = false;

static void minecraft_idle() {
    if (client->wantToQuit()) {
        eglutDestroyWindow(winId);
        eglutFini();
        return;
    }
    int cx = eglutGetWindowWidth() / 2;
    int cy = eglutGetWindowHeight() / 2;
    if (moveMouseToCenter) {
        eglutWarpMousePointer(cx, cy);
        moveMouseToCenter = false;
    }
    eglutPostRedisplay();
}
int i = 0;
static void minecraft_draw() {
    client->update();
    if (client->wantToQuit()) {
        eglutDestroyWindow(winId);
        eglutFini();
        return;
    }
}
float pixelSize = 2.f;
static void minecraft_reshape(int w, int h) {
    client->setRenderingSize(w, h);
    client->setUISizeAndScale(w, h, pixelSize);
}
static void minecraft_mouse(int x, int y) {
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
}
static void minecraft_mouse_button(int x, int y, int btn, int action) {
    int mcBtn = (btn == 1 ? 1 : (btn == 2 ? 3 : (btn == 3 ? 2 : (btn == 5 ? 4 : btn))));
    Mouse::feed((char) mcBtn, (char) (action == EGLUT_MOUSE_PRESS ? (btn == 5 ? -120 : (btn == 4 ? 120 : 1)) : 0), x, y, 0, 0);
}

int getKeyMinecraft(int keyCode) {
    if (keyCode == 65505)
        return 16;
    if (keyCode >= 97 && keyCode <= 122)
        return (keyCode + 65 - 97);
    if (keyCode >= 65470 && keyCode <= 65481)
        return (keyCode + 112 - 65470);

    return keyCode;
}
static void minecraft_keyboard(char str[5], int action) {
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
}
static void minecraft_keyboard_special(int key, int action) {
    if (key == 65480) {
        if (action == EGLUT_KEY_PRESS) {
            client->getOptions()->setFullscreen(!client->getOptions()->getFullscreen());
        }
        return;
    }
    int mKey = getKeyMinecraft(key);
   // std::cout << mKey << "\n";
    if (action == EGLUT_KEY_PRESS) {
        Keyboard::inputs->push_back({1, mKey});
        Keyboard::states[mKey] = 1;
    } else if (action == EGLUT_KEY_RELEASE) {
        Keyboard::inputs->push_back({0, mKey});
        Keyboard::states[mKey] = 0;
    }
}
static void minecraft_close() {
    client->quit();
}

void detachFromJavaStub() {
    //std::cout << "detach from java\n";
}
void* getJVMEnvStub() {
   // std::cout << "getjvmenv\n";
    return nullptr;
}
bool verifyCertChainStub() {
    //std::cout << "verifycertchain\n";
    return true;
}
struct xboxSingleton {
    char filler[8];
};
xboxSingleton xboxGetAppConfigSingleton() {
  //  std::cout << "xbox get app config singleton\n";
    return xboxSingleton();
}
void xboxConfigSetSandboxStub() {
   // std::cout << "xbox config: set sandbox (stub)\n";
}
void patchNotesModelStub() {
   // std::cout << "fetch patch notes\n";
}

extern "C"
void pshufb(char* dest, char* src) {
    char new_dest[16];
    for (int i = 0; i < 16; i++)
        new_dest[i] = (src[i] & 0x80) ? 0 : dest[src[i] & 15];
    memcpy(dest, new_dest, 16);
}
extern "C"
void pshufb_xmm4_xmm0();
#include <functional>
#include <sys/mman.h>
#include <EGL/egl.h>
#include <stdlib.h>

using namespace std;
int main(int argc, char *argv[]) {
	if(sizeof(std::string("")) != 4){
		throw std::invalid_argument("sizeof(std::string()) != 4, size = " + std::to_string(sizeof(std::string(""))));
		return 0;
	}
    bool enableStackTracePrinting = true;
    bool workaroundAMD = false;

    int windowWidth = 720;
    int windowHeight = 480;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--scale") == 0) {
            i++;
            pixelSize = std::stof(argv[i]);
        } else if (strcmp(argv[i], "-sw") == 0 || strcmp(argv[i], "--width") == 0) {
            i++;
            windowWidth = std::stoi(argv[i]);
        } else if (strcmp(argv[i], "-sh") == 0 || strcmp(argv[i], "--height") == 0) {
            i++;
            windowHeight = std::stoi(argv[i]);
        } else if (strcmp(argv[i], "-ns") == 0 || strcmp(argv[i], "--no-stacktrace") == 0) {
            enableStackTracePrinting = false;
        } else if (strcmp(argv[i], "--pocket-guis") == 0) {
            enablePocketGuis = true;
        } else if (strcmp(argv[i], "--amd-fix") == 0) {
            std::cout << "--amd-fix: Enabling AMD Workaround.\n";
            workaroundAMD = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            std::cout << "Help\n";
            std::cout << "--help               Shows this help information\n";
            std::cout << "--scale <scale>      Sets the pixel scale\n";
            std::cout << "--width <width>      Sets the window width\n";
            std::cout << "--height <height>    Sets the window height\n";
            std::cout << "--pocket-guis        Switches to Pocket Edition GUIs\n";
            std::cout << "--no-stacktrace      Disables stack trace printing\n";
            std::cout << "--amd-workaround     Fixes crashes on pre-i686 and AMD CPUs\n\n";
            std::cout << "EGL Options\n";
            std::cout << "-display <display>  Sets the display\n";
            std::cout << "-info               Shows info about the display\n\n";
            std::cout << "MCPE arguments:\n";
            std::cout << "edu <true|false>\n";
            std::cout << "mcworld <world>\n";
            return 0;
        }
    }

    if (enableStackTracePrinting) {
        registerCrashHandler();
    }

    setenv("LC_ALL", "C", 1); // HACK: Force set locale to one recognized by MCPE so that the outdated C++ standard library MCPE uses doesn't fail to find one

    std::cout << "loading native libraries\n";
    void* glesLib = loadLibraryOS("libGLESv2.so", gles_symbols);
    void* fmodLib = loadLibraryOS(getCWD() + "libs/native/libfmod.so.8.2", fmod_symbols);
    if (glesLib == nullptr || fmodLib == nullptr)
        return -1;
    std::cout << "loading hybris libraries\n";
    stubSymbols(android_symbols, (void*) androidStub);
    stubSymbols(egl_symbols, (void*) eglStub);
    hybris_hook("eglGetProcAddress", (void*) eglGetProcAddress);
    hybris_hook("mcpelauncher_hook", (void*) hookFunction);
    hookAndroidLog();
    if (!loadLibrary("libc.so") || !loadLibrary("libstdc++.so") || !loadLibrary("libm.so") || !loadLibrary("libz.so"))
        return -1;
    // load stub libraries
    if (!loadLibrary("libandroid.so") || !loadLibrary("liblog.so") || !loadLibrary("libEGL.so") || !loadLibrary("libGLESv2.so") || !loadLibrary("libOpenSLES.so") || !loadLibrary("libfmod.so") || !loadLibrary("libGLESv1_CM.so"))
        return -1;
    if (!loadLibrary("libmcpelauncher_mod.so"))
        return -1;
    std::cout << "loading MCPE\n";
    std::string mcpePath = getCWD() + "libs/libminecraftpe.so";
    void* handle = hybris_dlopen(mcpePath.c_str(), RTLD_LAZY);
    if (handle == nullptr) {
        std::cout << "failed to load MCPE: " << hybris_dlerror() << "\n";
        return -1;
    }
    addHookLibrary(handle, mcpePath);

    unsigned int libBase = ((soinfo*) handle)->base;
    std::cout << "loaded MCPE (at " << libBase << ")\n";

    DIR *dir;
    struct dirent *ent;
    std::vector<void*> mods;
    if ((dir = opendir ("mods/")) != NULL) {
        std::cout << "loading mods\n";
        while ((ent = readdir (dir)) != NULL) {
            if (ent->d_name[0] == '.')
                continue;
            std::string fileName (ent->d_name);
            int len = fileName.length();
            if (len < 4 || fileName[len - 3] != '.' || fileName[len - 2] != 's' || fileName[len - 1] != 'o')
                continue;
            std::cout << "loading: " << fileName << "\n";
            void* mod = loadMod(fileName);
            if (mod != nullptr)
                mods.push_back(mod);
        }
        closedir(dir);
        std::cout << "loaded " << mods.size() << " mods\n";
    }

    std::cout << "apply patches\n";

    /*
    unsigned int patchOff = (unsigned int) hybris_dlsym(handle, "_ZN12StoreFactory11createStoreER13StoreListener") + 66;
    patchCallInstruction((void*) patchOff, (void*) &createStoreHookFunc, false);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN11HTTPRequestC2ERKSs") + 154;
    patchCallInstruction((void*) patchOff, (void*) &constructLinuxHttpRequestInternal, false);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN11HTTPRequest4sendEv") + 26;
    patchCallInstruction((void*) patchOff, (void*) &sendLinuxHttpRequestInternal, false);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN11HTTPRequest5abortEv") + 26;
    patchCallInstruction((void*) patchOff, (void*) &abortLinuxHttpRequestInternal, false);
     */
    auto patchOff = (unsigned int) hybris_dlsym(handle, "_ZN12AndroidStore21createGooglePlayStoreERKSsR13StoreListener");
    patchCallInstruction((void*) patchOff, (void*) &createStoreHookFunc, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroidC2ER11HTTPRequest");
    patchCallInstruction((void*) patchOff, (void*) &constructLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid4sendEv");
    patchCallInstruction((void*) patchOff, (void*) &sendLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid5abortEv");
    patchCallInstruction((void*) patchOff, (void*) &abortLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat10threadpool16detach_from_javaEPv");
    patchCallInstruction((void*) patchOff, (void*) &detachFromJavaStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat11get_jvm_envEv");
    patchCallInstruction((void*) patchOff, (void*) &getJVMEnvStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN3web4http6client7details22verify_X509_cert_chainERKSt6vectorISsSaISsEERKSs");
    patchCallInstruction((void*) patchOff, (void*) &verifyCertChainStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config24get_app_config_singletonEv");
    patchCallInstruction((void*) patchOff, (void*) &xboxGetAppConfigSingleton, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config11set_sandboxESs");
    patchCallInstruction((void*) patchOff, (void*) &xboxConfigSetSandboxStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config29set_title_telemetry_device_idERKSs");
    patchCallInstruction((void*) patchOff, (void*) &xboxConfigSetSandboxStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN15PatchNotesModel17preloadPatchNotesEv");
    patchCallInstruction((void*) patchOff, (void*) &patchNotesModelStub, true);
    
    //getHardwareInformation
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK11AppPlatform22getHardwareInformationEv");
    patchCallInstruction((void*) patchOff, (void*) &AppPlatform::getHardwareInformation, true);
    
     patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK18UserAuthentication17getClientRandomIdEv");
    patchCallInstruction((void*) patchOff, (void*) &UserAuthentication::getClientRandomId, true);
    
    //_ZN20MinecraftScreenModel18displayChatMessageE
	patchOff = (unsigned int) hybris_dlsym(handle, "_ZN19HudScreenController19_pushNewChatMessageERKSs");
    hookFunction((void*) patchOff, (void*) &onChatMessage, (void**) &original_onChatMessage);
    
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN18BatchedNetworkPeer10sendPacketESsN11NetworkPeer11ReliabilityEi");
    hookFunction((void*) patchOff, (void*) Network::BatchedNetworkPeer::sendPacket, (void**) &Network::BatchedNetworkPeer::original_sendPacket);
    
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN18BatchedNetworkPeer13receivePacketERSs");
    hookFunction((void*) patchOff, (void*) Network::BatchedNetworkPeer::handlePacket, (void**) &Network::BatchedNetworkPeer::original_handlePacket);
    
    //_ZNK3mce4UUID8asStringEv
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK3mce4UUID8asStringEv");
    patchCallInstruction((void*) patchOff, (void*) &Network::mceUUID::asString, true);
    
  //  patchOff = (unsigned int) hybris_dlsym(handle, "_ZN17ConnectionRequest6createER17PrivateKeyManagerRK11CertificateRKSsyS6_RKSt6vectorIhSaIhEE9InputModeiiS6_S6_6ADRole");
   // hookFunction((void*) patchOff, (void*) Network::ConnectionRequest::create, (void**) &Network::ConnectionRequest::original_create);
    
    //_ZN10KeyManagerC2ERKSsN6Crypto10Asymmetric6SystemE
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK10KeyManager12getPublicKeyEv");
    hookFunction((void*) patchOff, (void*) KeyManager::CryptoHash::getPublicKey, (void**) &KeyManager::CryptoHash::original_getPublicKey);
    //_ZN17PrivateKeyManagerC2EN6Crypto10Asymmetric6SystemE
    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN17PrivateKeyManagerC2EN6Crypto10Asymmetric6SystemE");
    hookFunction((void*) patchOff, (void*) KeyManager::PrivateKeyManager::PrivateKeyManagerCtor, (void**) &KeyManager::PrivateKeyManager::original_PrivateKeyManagerCtor);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZNK17PrivateKeyManager4signERKSsN6Crypto4Hash8HashTypeE");
    hookFunction((void*) patchOff, (void*) KeyManager::PrivateKeyManager::sign, (void**) &KeyManager::PrivateKeyManager::original_sign);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN13ScreenChooser19setDisconnectScreenERKSsS1_S1_");
    hookFunction((void*) patchOff, (void*) onDisconnect, (void**) &original_onDisconnect);
    
   // patchOff = (unsigned int) hybris_dlsym(handle, "d2i_AutoPrivateKey");
   // hookFunction((void*) patchOff, (void*) KeyManager::CryptoHash::d2i_AutoPrivateKey, (void**) &KeyManager::CryptoHash::original_d2i_AutoPrivateKey);
    
    linuxHttpRequestInternalVtable = (void**) ::operator new(8);
    linuxHttpRequestInternalVtable[0] = (void*) &LinuxHttpRequestInternal::destroy;
    linuxHttpRequestInternalVtable[1] = (void*) &LinuxHttpRequestInternal::destroy;

    if (workaroundAMD) {/*
        patchOff = (unsigned int) hybris_dlsym(handle, "_ZN21BlockTessallatorCache5resetER11BlockSourceRK8BlockPos") +
                   (0x40AD97 - 0x40ACD0);
        for (unsigned int i = 0; i < 0x40ADA0 - 0x40AD97; i++)
            ((char *) (void *) patchOff)[i] = 0x90;*/
        patchOff = (unsigned int) hybris_dlsym(handle, "_ZN21BlockTessallatorCache5resetER11BlockSourceRK8BlockPos") + (0x40AD9B - 0x40ACD0);
        patchCallInstruction((void*) patchOff, (void*) &pshufb_xmm4_xmm0, false);
    }
    std::cout << sizeof(std::string("")) << " sizeof string\n";

    std::cout << "patches applied!\n";

    // load symbols for gl
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
    //AppPlatform::AppPlatform_getHardwareInformation = (AppPlatform::someHardwareInformation* (*)(AppPlatform*)) hybris_dlsym(handle, "_ZNK11AppPlatform22getHardwareInformationEv");
    //_ZNK11AppPlatform22getHardwareInformationEv getHardwareInformation
    AppPlatform::AppPlatform__fireAppFocusGained = (void (*)(AppPlatform*)) hybris_dlsym(handle, "_ZN11AppPlatform19_fireAppFocusGainedEv");

    void** ptr = (void**) hybris_dlsym(handle, "_ZN9crossplat3JVME");
    *ptr = (void*) 1; // this just needs not to be null

    std::cout << "init app platform vtable\n";
    LinuxAppPlatform::initVtable(handle);
    std::cout << "init app platform\n";
    auto* platform = new LinuxAppPlatform();
    std::cout << "app platform initialized\n";

    Mouse::feed = (void (*)(char, char, short, short, short, short)) hybris_dlsym(handle, "_ZN5Mouse4feedEccssss");

    Keyboard::inputs = (std::vector<KeyboardAction>*) hybris_dlsym(handle, "_ZN8Keyboard7_inputsE");
    Keyboard::states = (int*) hybris_dlsym(handle, "_ZN8Keyboard7_statesE");
    Keyboard::Keyboard_feedText = (void (*)(const std::string&, bool, unsigned char)) hybris_dlsym(handle, "_ZN8Keyboard8feedTextERKSsbh");

    Options::Options_getFullscreen = (bool (*)(Options*)) hybris_dlsym(handle, "_ZNK7Options13getFullscreenEv");
    Options::Options_setFullscreen = (void (*)(Options*, bool)) hybris_dlsym(handle, "_ZN7Options13setFullscreenEb");
    Options::Options_setUsername = (void (*)(Options*, const std::string& name)) hybris_dlsym(handle, "_ZN7Options11setUsernameERKSs");

    std::cout << "init window\n";
    eglutInitWindowSize(windowWidth, windowHeight);
    eglutInitAPIMask(EGLUT_OPENGL_ES2_BIT);
    eglutInit(argc, argv);

	std::random_device rd;
  	std::mt19937_64 eng(rd());
  	std::uniform_int_distribution<unsigned long long int> distr;
  	
  	auto winname = std::to_string(distr(eng));
    std::cout << "window id " << eglutCreateWindow(winname.c_str()) << "\n";

    // init MinecraftGame
    App::App_init = (void (*)(App*, AppContext&)) hybris_dlsym(handle, "_ZN3App4initER10AppContext");
    MinecraftGame::MinecraftGame_construct = (void (*)(MinecraftGame*, int, char**)) hybris_dlsym(handle, "_ZN13MinecraftGameC2EiPPc");
    MinecraftGame::MinecraftGame_update = (void (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame6updateEv");
    MinecraftGame::MinecraftGame_setRenderingSize = (void (*)(MinecraftGame*, int, int)) hybris_dlsym(handle, "_ZN13MinecraftGame16setRenderingSizeEii");
    MinecraftGame::MinecraftGame_setUISizeAndScale = (void (*)(MinecraftGame*, int, int, float)) hybris_dlsym(handle, "_ZN13MinecraftGame17setUISizeAndScaleEiif");
    //MinecraftGame::MinecraftGame_setServerToTransfer = (void (*)(MinecraftGame*, const std::string&, short)) hybris_dlsym(handle, "_ZN13MinecraftGame19setServerToTransferERKSss");
    hookFunction((void*) hybris_dlsym(handle, "_ZN13MinecraftGame19setServerToTransferERKSss"), (void*) onTransfer, (void**) &MinecraftGame::MinecraftGame_setServerToTransfer);
    MinecraftGame::MinecraftGame_getOptions = (Options* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame10getOptionsEv");
    MinecraftGame::MinecraftGame_getGuiData = (GuiData* (*)(MinecraftGame*)) hybris_dlsym(handle, "_ZN13MinecraftGame10getGuiDataEv");
    
    GuiData::GuiData_addMessage = (void (*)(GuiData*, const std::string& user, const std::string& msg, int, bool, bool)) hybris_dlsym(handle, "_ZN7GuiData10addMessageERKSsS1_ibb");
    AppContext ctx{};
    ctx.platform = platform;
    ctx.doRender = true;

    platform->initialize();

    mce::Platform::OGL::initBindings();

    std::cout << "create minecraft client\n";
    client = new MinecraftGame(argc, argv);
   
    std::cout << "init minecraft client\n";
    client->init(ctx);
    std::cout << "initialized lib\n";
   /* auto dm = my_getDeviceModel((*AppPlatform::_singleton));
	std::cout << dm << "\n";
	std::cout << dm->data.size() << "\n";
	std::cout << dm->data1.size() << "\n";
	std::cout << dm->data2.size() << "\n";
	std::cout << dm->data3.size() << "\n";
	std::cout << dm->data4.size() << "\n";*/
	
	
    //if (client->getOptions()->getFullscreen())
    //    eglutToggleFullscreen();

    for (void* mod : mods) {
        auto initFunc = (void (*)(MinecraftGame*)) hybris_dlsym(mod, "mod_set_minecraft");
        if ((void*) initFunc != nullptr)
            initFunc(client);
    }
    
eglutDisplayFunc(minecraft_draw);
eglutIdleFunc(minecraft_idle);
    eglutReshapeFunc(minecraft_reshape);
    eglutKeyboardFunc(minecraft_keyboard);
   // eglutMouseFunc(minecraft_mouse);
    eglutMouseButtonFunc(minecraft_mouse_button);
     eglutSpecialFunc(minecraft_keyboard_special);

    std::uniform_int_distribution<unsigned long long int> distr2(100, 300);
    client->getOptions()->setUsername(std::to_string(distr2(eng)));
    
  	UserAuthentication::cid = distr(eng) * distr(eng);
  
    startBotTo("play.minenex.fun", 19132);
    

    // init
    (*AppPlatform::_singleton)->_fireAppFocusGained();
    client->setRenderingSize(windowWidth, windowHeight);
    client->setUISizeAndScale(windowWidth, windowHeight, pixelSize);
  
    eglutMainLoop();
    //while(true){
    //client->update();
    //usleep(10000);
    //}

    return 0;
}
