//
// Created by user on 16.02.23.
//

#ifndef PDSERVER_LOADER_H
#define PDSERVER_LOADER_H


#include <memory>
#include <functional>
#include "appPlatform/LinuxStore.h"
#include "ServerInstance.h"

class Loader {
private:
    static inline ServerInstance* instance = nullptr;
    static inline bool isShutdown = false;
    static inline time_t pleaseDontStopBeforeThis = 0;

    static inline std::vector<std::function<void(void* handle)>> callOnLoad;
    static inline std::vector<std::function<void(void* handle)>> callAfterLoad;
    static inline std::mutex callMux;

    static void processCommands(char* lineBuffer, size_t& lineBufferOffset);
    static void handleCommand(const std::string& cmd);

    static void registerCtrlCHandler();
    static void ctrlC(int);
    static void doOnStop();

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

public:
    static void initHooks(void* handle);

    static void load(void* handle);
    static void stop();

    static void registerCallOnLoad(std::function<void(void* handle)> fun);
    static void registerCallAfterLoad(std::function<void(void* handle)> fun);
    static void registerCallAfterLoad(std::function<void()> fun);
};


#endif //PDSERVER_LOADER_H
