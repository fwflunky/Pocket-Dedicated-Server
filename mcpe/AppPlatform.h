#pragma once
#include <iostream>
class AppPlatform {

public:

    struct someHardwareInformation {
        std::string deviceModel;
        std::string data1;
        std::string data2;
        std::string data3;
        std::string data4;
        //int deviceOs; //.so patched for always 1
    };
    void** vtable;
    static inline AppPlatform** _singleton = nullptr;


    char filler2[0x1000];
    static inline void** myVtable = nullptr;
    static inline void (*AppPlatform_construct)(AppPlatform*) = nullptr ;
    static inline void (*AppPlatform_initialize)(AppPlatform*) = nullptr ;
    static inline void (*AppPlatform__fireAppFocusGained)(AppPlatform*) = nullptr ;
    static inline someHardwareInformation* (*AppPlatform_getHardwareInformation)(AppPlatform*) = nullptr;
    static inline someHardwareInformation* hardwareInformation = nullptr;

    static someHardwareInformation* getHardwareInformation(void* inst){
    	return hardwareInformation;
    }

    
    AppPlatform() {
        AppPlatform_construct(this);
    }


    void _fireAppFocusGained() {
        AppPlatform__fireAppFocusGained(this);
    }

    void initialize() {
        AppPlatform_initialize(this);
        hardwareInformation = new someHardwareInformation {
                .deviceModel = "XIAOMI MT834628JT",
        };
    }

};
