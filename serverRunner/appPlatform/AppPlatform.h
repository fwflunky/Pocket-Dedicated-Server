#pragma once

class AppPlatform {

public:
    void** vtable;
    static inline AppPlatform** _singleton = nullptr;


    char filler2[0x1000];
    static inline void** myVtable = nullptr;
    static inline void (*AppPlatform_construct)(AppPlatform*) = nullptr ;
    static inline void (*AppPlatform_initialize)(AppPlatform*) = nullptr ;
    static inline void (*AppPlatform__fireAppFocusGained)(AppPlatform*) = nullptr ;
    
    AppPlatform() {
        AppPlatform_construct(this);
    }


    void _fireAppFocusGained() {
        AppPlatform__fireAppFocusGained(this);
    }

    void initialize() {
        AppPlatform_initialize(this);
    }

};
