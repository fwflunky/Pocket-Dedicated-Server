//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_LOADER_H
#define PDSERVER_LOADER_H


#include <memory>
#include "appPlatform/LinuxStore.h"
#include "ServerInstance.h"

class Loader {
public:
    static void initHooks(void* handle);

    static inline ServerInstance* instance = nullptr;
    static inline bool isShutdown = false;
    static inline time_t pleaseDontStopBeforeThis = 0;

    static void load(void* handle);
    static void handleCommand(const std::string& cmd);
    static void stop();
    static void registerCtrlCHandler();
    static void doOnStop();
    static void ctrlC(int);

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

    static void processCommands(char* lineBuffer, size_t& lineBufferOffset);
};


#endif //PDSERVER_LOADER_H
