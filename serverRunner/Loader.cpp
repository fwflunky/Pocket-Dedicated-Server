//
// Created by user on 16.02.23.
//

#include <iostream>
#include <thread>
#include <fcntl.h>
#include "Loader.h"
#include "minecraftGame/api/Api.h"
#include "../hybris/include/hybris/dlfcn.h"
#include "appPlatform/LinuxAppPlatform.h"
#include "level/LevelSettings.h"
#include "filePathManager/FilePathManager.h"
#include "../server/eventing/MinecraftEventing.h"
#include "resourcePack/ResourcePackManager.h"
#include "resourcePack/PackManifestFactory.h"
#include "resourcePack/ResourcePackRepository.h"
#include "entitlement/EntitlementManager.h"
#include "appPlatform/AppPlatform.h"
#include "userManager/UserManager.h"
#include "lists/OriginalOpsList.h"
#include "lists/OriginalWhiteList.h"
#include "../server/network/networkHandler/NetworkHandler.h"
#include "minecraftGame/DedicatedMinecraftApp.h"
#include "automation/Automation.h"
#include "uuid/UUID.h"
#include "ServerInstance.h"
#include "../src/common.h"
#include "../../src/hook.h"
#include "scheduler/Scheduler.h"
#include "minecraftGame/Minecraft.h"
#include "../server/statics.h"
#include "../server/level/Level.h"

void Loader::initHooks(void *handle) {
    auto patchOff = (unsigned int) hybris_dlsym(handle, "_ZN12AndroidStore21createGooglePlayStoreERKSsR13StoreListener");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::createStoreHookFunc, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroidC2ER11HTTPRequest");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::constructLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid4sendEv");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::sendLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN26HTTPRequestInternalAndroid5abortEv");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::abortLinuxHttpRequestInternal, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat10threadpool16detach_from_javaEPv");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::detachFromJavaStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN9crossplat11get_jvm_envEv");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::getJVMEnvStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN3web4http6client7details22verify_X509_cert_chainERKSt6vectorISsSaISsEERKSs");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::verifyCertChainStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config24get_app_config_singletonEv");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::xboxGetAppConfigSingleton, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config11set_sandboxESs");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::xboxConfigSetSandboxStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN4xbox8services20xbox_live_app_config29set_title_telemetry_device_idERKSs");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::xboxConfigSetSandboxStub, true);

    patchOff = (unsigned int) hybris_dlsym(handle, "_ZN15PatchNotesModel17preloadPatchNotesEv");
    patchCallInstruction((void *) patchOff, (void *) &basicPatches::patchNotesModelStub, true);

    Minecraft::Minecraft_getServerNetworkHandler = (ServerNetworkHandler *(*)(Minecraft *)) hybris_dlsym(handle, "_ZN9Minecraft23getServerNetworkHandlerEv");
    Minecraft::Minecraft_getLevel = (Level *(*)(Minecraft *)) hybris_dlsym(handle, "_ZNK9Minecraft8getLevelEv");
    Minecraft::Minecraft_disconnectClient = (void (*)(Minecraft *, NetworkIdentifier const &, std::string const &)) hybris_dlsym(handle, "_ZN9Minecraft16disconnectClientERK17NetworkIdentifierRKSs");


    FilePathManager::FilePathManager_construct = (void (*)(FilePathManager *, std::string, bool)) hybris_dlsym(handle, "_ZN15FilePathManagerC2ESsb");
    ResourcePackManager::ResourcePackManager_construct = (void (*)(ResourcePackManager *, std::function<std::string()>)) hybris_dlsym(handle, "_ZN19ResourcePackManagerC2ESt8functionIFSsvEE");
    ResourcePackManager::ResourcePackManager_setStack = (void (*)(ResourcePackManager *, std::unique_ptr<ResourcePackStack>, int, bool)) hybris_dlsym(handle, "_ZN19ResourcePackManager8setStackESt10unique_ptrI17ResourcePackStackSt14default_deleteIS1_EE21ResourcePackStackTypeb");
    ResourcePackStack::ResourcePackStack_add = (void (*)(ResourcePackStack *, ResourcePack *i, ResourcePackRepository const &r, bool b)) hybris_dlsym(handle, "_ZN17ResourcePackStack3addEP12ResourcePackRK22ResourcePackRepositoryb");
    ResourcePackStack::vtable_sym = (void **) hybris_dlsym(handle, "_ZTV17ResourcePackStack");
    PackManifestFactory::PackManifestFactory_construct = (void (*)(PackManifestFactory *, MinecraftEventing &)) hybris_dlsym(handle, "_ZN19PackManifestFactoryC2ER17MinecraftEventing");
    ResourcePackRepository::ResourcePackRepository_construct = (void (*)(ResourcePackRepository *, MinecraftEventing &, PackManifestFactory &, EntitlementManager *, FilePathManager *)) hybris_dlsym(handle, "_ZN22ResourcePackRepositoryC2ER17MinecraftEventingR19PackManifestFactoryP18EntitlementManagerP15FilePathManager");
    //ResourcePackRepository::ResourcePackRepository_getPackLoadingReport = (void (*)(ResourcePackRepository*, MinecraftEventing&, PackManifestFactory&, EntitlementManager*, FilePathManager*)) hybris_dlsym(handle, "_ZN22ResourcePackRepositoryC2ER17MinecraftEventingR19PackManifestFactoryP18EntitlementManagerP15FilePathManager");
    hookFunction((void *) hybris_dlsym(handle, "_ZNK22ResourcePackRepository20getPackLoadingReportEv"), (void *) &ResourcePackRepository::getPackLoadingReport, (void **) &ResourcePackRepository::ResourcePackRepository_getPackLoadingReport);


    EntitlementManager::EntitlementManager_construct = (void (*)(EntitlementManager *, MinecraftEventing &, Social::UserManager &)) hybris_dlsym(handle, "_ZN18EntitlementManagerC2ER17MinecraftEventingRN6Social11UserManagerE");
    LevelSettings::LevelSettings_construct = (void (*)(LevelSettings *)) hybris_dlsym(handle, "_ZN13LevelSettingsC2Ev");
    ServerInstance::ServerInstance_update = (void (*)(ServerInstance *)) hybris_dlsym(handle, "_ZN14ServerInstance6updateEv");
    ServerInstance::ServerInstance_stop = (void (*)(ServerInstance *)) hybris_dlsym(handle, "_ZN14ServerInstance4stopEv");
    ServerInstance::ServerInstance_construct = (void (*)(ServerInstance *, IMinecraftApp &app, OriginalWhiteList const &wl, OriginalOpsList const &opl,
                                                         FilePathManager *, std::chrono::duration<long long, std::ratio<1ll, 1ll> >,
                                                         std::string s1, std::string s2, std::string s3, std::string s4, std::string s5,
                                                         LevelSettings &ls, minecraft::api::Api &api, int i1, bool b1, int i2, int i3, int i4, bool b2,
                                                         std::vector<std::string> const &vs, std::string s6, bool b3, mce::UUID const &uuid,
                                                         MinecraftEventing &ev, ResourcePackRepository &rpr, ResourcePackManager &rpm, ResourcePackManager *rmpm)) hybris_dlsym(handle, "_ZN14ServerInstanceC2ER13IMinecraftAppRK9WhitelistRK7OpsListP15FilePathManagerNSt6chrono8durationIxSt5ratioILx1ELx1EEEESsSsSsSsSs13LevelSettingsRN9minecraft3api3ApiEibiiibRKSt6vectorISsSaISsEESsbRKN3mce4UUIDER17MinecraftEventingR22ResourcePackRepositoryR19ResourcePackManagerPSX_");
    Social::UserManager::UserManager_construct = (void (*)(Social::UserManager *)) hybris_dlsym(handle, "_ZN6Social11UserManagerC2Ev");
    Automation::AutomationClient::AutomationClient_ctor = (void (*)(Automation::AutomationClient *, IMinecraftApp &)) hybris_dlsym(handle, "_ZN10Automation16AutomationClientC2ER13IMinecraftApp");

    AppPlatform::myVtable = (void **) hybris_dlsym(handle, "_ZTV11AppPlatform");
    AppPlatform::_singleton = (AppPlatform **) hybris_dlsym(handle, "_ZN11AppPlatform10mSingletonE");
    AppPlatform::AppPlatform_construct = (void (*)(AppPlatform *)) hybris_dlsym(handle, "_ZN11AppPlatformC2Ev");
    AppPlatform::AppPlatform_initialize = (void (*)(AppPlatform *)) hybris_dlsym(handle, "_ZN11AppPlatform10initializeEv");
    AppPlatform::AppPlatform__fireAppFocusGained = (void (*)(AppPlatform *)) hybris_dlsym(handle, "_ZN11AppPlatform19_fireAppFocusGainedEv");


    mce::UUID::EMPTY = (mce::UUID *) hybris_dlsym(handle, "_ZN3mce4UUID5EMPTYE");
    mce::UUID::fromString = (mce::UUID (*)(std::string const &)) hybris_dlsym(handle, "_ZN3mce4UUID10fromStringERKSs");

    Scheduler::singleton = (Scheduler *(*)()) hybris_dlsym(handle, "_ZN9Scheduler9singletonEv");
    Scheduler::Scheduler_processCoroutines = (void (*)(Scheduler *, double)) hybris_dlsym(handle, "_ZN9Scheduler17processCoroutinesEd");
}

void Loader::load(void *handle) {

    statics::log::info("Initialize hooks");
    initHooks(handle);

    LinuxAppPlatform::initVtable(handle);
    auto *platform = new LinuxAppPlatform();
    platform->initialize();

    minecraft::api::Api api;
    {
        api.vtable = (void **) hybris_dlsym(handle, "_ZTVN9minecraft3api3ApiE") + 2;
        api.envPath = CWDD;
        api.playerIfaceVtable = (void **) hybris_dlsym(handle, "_ZTVN9minecraft3api15PlayerInterfaceE") + 2;
        api.networkIfaceVtable = (void **) hybris_dlsym(handle, "_ZTVN9minecraft3api16NetworkInterfaceE") + 2;
    }

    LevelSettings settings;
    {
        settings.seed = 4544467;
        settings.gameType = 0;
        settings.forceGameType = 0;
        settings.difficulty = 2;
        settings.dimension = 0;
        settings.generator = 1;
        settings.edu = false;
        settings.mpGame = true;
        settings.lanBroadcast = true;
        settings.commandsEnabled = true;
        settings.texturepacksRequired = true;
        settings.hasAchievementsDisabled = true;
    }

    FilePathManager filePathManager(CWDD, false);
    MinecraftEventing eventing(CWDD);

    ResourcePackManager resourcePackManager([]() {
        return CWDD;
    });

    PackManifestFactory packManifestFactory(eventing);

    Social::UserManager um;

    auto *entitlementManager = new EntitlementManager(eventing, um);
    ResourcePackRepository resourcePackRepo(eventing, packManifestFactory, entitlementManager, &filePathManager);

    if (!resourcePackRepo.vanillaBehaviorPack) {
        statics::log::error("Unable to find vanilla BehaviorPack");
        return workaroundShutdownCrash(handle);
    }
    std::unique_ptr<ResourcePackStack> stack(new ResourcePackStack());
    stack->add(resourcePackRepo.vanillaBehaviorPack, resourcePackRepo, false);
    resourcePackManager.setStack(std::move(stack), 3, false);

    OriginalOpsList ops;
    OriginalWhiteList wl;

    DedicatedMinecraftApp minecraftApp;

    Automation::AutomationClient aclient(minecraftApp);

    minecraftApp.automationClient = &aclient;


    statics::log::info("Starting server...");
    instance = new ServerInstance(minecraftApp, wl, ops, &filePathManager, std::chrono::duration_cast<std::chrono::duration<long long>>(std::chrono::seconds(10)), "SawAADYtAAA=", "My world", "", "", "", settings, api, 8, true, 19132, 19132, 1000 - 7, false, {}, "normal", false, *mce::UUID::EMPTY, eventing, resourcePackRepo, resourcePackManager, &resourcePackManager);
    statics::log::info("Server started");
    statics::serverNetworkHandler = instance->minecraft->getServerNetworkHandler();
    statics::minecraft = instance->minecraft;

    auto level = instance->minecraft->getLevel();
    level->createDimension(1);
    level->createDimension(2);

    auto tp = std::chrono::steady_clock::now();
    int updatesPerSecond = 100;

    int flags = fcntl(0, F_GETFL, 0);
    fcntl(0, F_SETFL, flags | O_NONBLOCK);
    char lineBuffer[1024 * 16];
    size_t lineBufferOffset = 0;


    while (!isShutdown) {
        processCommands(&lineBuffer[0], lineBufferOffset);
        auto tp2 = std::chrono::steady_clock::now();
        instance->update();
        {
            Scheduler::singleton()->processCoroutines((double) std::chrono::duration_cast<std::chrono::duration<long long>>(tp2 - tp).count());
            std::this_thread::sleep_until(tp2 + std::chrono::nanoseconds(1000000000L / updatesPerSecond));
        }
        statics::onTickLock.lock();
        if (statics::runFunc) {
            statics::runFunc();
        }
        if (statics::runFunc) {
            statics::runFunc = nullptr;
            statics::waitForFuncRuns.unlock();
        }
        statics::onTickLock.unlock();

        tp = tp2;
    }
    stop();
    workaroundShutdownCrash(handle);
    statics::log::info("Server stopped");
}

void Loader::processCommands(char *lineBuffer, size_t &lineBufferOffset) {
    ssize_t r;
    while ((r = read(0, &lineBuffer[lineBufferOffset], (1024 * 16) - lineBufferOffset)) > 0)
        lineBufferOffset += r;
    for (size_t i = 0; i < lineBufferOffset;) {
        if (i == (1024 * 16) - 1 || lineBuffer[i] == '\n') {
            std::string cmd = std::string(lineBuffer, i);
            memcpy(lineBuffer, &lineBuffer[i + 1], lineBufferOffset - i - 1);
            lineBufferOffset -= i + 1;

            if (!cmd.empty()) {
                std::cout << "\nExecute cmd: " << cmd << "\n";
                handleCommand(cmd);
            }
            i = 0;
        } else {
            i++;
        }
    }
}

void Loader::handleCommand(const std::string &cmd) {
    if (cmd == "stop") {
        isShutdown = true;
    }
}

void Loader::stop() {
    instance->stop();
}
