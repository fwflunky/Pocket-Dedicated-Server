//
// Created by user on 05.01.23.
//

#ifndef MCPELAUNCHER_BOTINSTANCE_H
#define MCPELAUNCHER_BOTINSTANCE_H


#include <string>
#include <memory>
#include "LinuxStore.h"
#include "../mcpe/AppPlatform.h"
#include "../mcpe/MinecraftGame.h"
#include "UserAuthentication.h"
#include "../mcpe/gl.h"
#include "LinuxAppPlatform.h"
#include "../mcpe/Options.h"

static inline void* glesLib = nullptr;
static inline void* fmodLib = nullptr;
static inline bool loaded = false;
static inline int libCount = 0;

class BotInstance {
public:
    BotInstance();
    bool isInitialized() const;
    static inline std::mutex lock;
    static inline MinecraftGame* client= nullptr;
    static inline int canAutoAcceptRpTickCount = 0;
    static inline std::string windowName;
    static inline std::string botNickname;
    static inline std::string currentServerAddress;
    static inline unsigned short currentServerPort = 19132;
    static void makeScreenshot(const std::string& outp);
private:
    
    void* handle = nullptr;
    bool initialized = false;

    static int getMinecraftKeyCode(int key);

    struct basicPatches {
        class HTTPRequest;

        static std::unique_ptr<LinuxStore> createStoreHookFunc(const std::string& idk, StoreListener& listener) {
            return std::make_unique<LinuxStore>();
        }

        class LinuxHttpRequestInternal {
        public:
            void* vtable;
            int filler1;
            HTTPRequest* request;

            void destroy() {
            }
        };
        static inline void** linuxHttpRequestInternalVtable = nullptr ;

        static void constructLinuxHttpRequestInternal(LinuxHttpRequestInternal* requestInternal, HTTPRequest* request) {
            requestInternal->vtable = linuxHttpRequestInternalVtable;
            requestInternal->request = request;
        }

        static void sendLinuxHttpRequestInternal(LinuxHttpRequestInternal* requestInternal) {
        }

        static void abortLinuxHttpRequestInternal(LinuxHttpRequestInternal* requestInternal) {
        }

        static void detachFromJavaStub() {
        }

        static void* getJVMEnvStub() {
            return nullptr;
        }

        static bool verifyCertChainStub() {
            return true;
        }

        struct xboxSingleton {
            char filler[8];
        };

        static xboxSingleton xboxGetAppConfigSingleton() {
            return {};
        }

        static void xboxConfigSetSandboxStub() {
        }

        static void patchNotesModelStub() {
        }

        static void emptyStub1(void*, void*, void*, void*) {
        }

    };
    void applyPatches();
    void startBot();
    static void androidStub();
    static void eglStub();
};


#endif //MCPELAUNCHER_BOTINSTANCE_H
