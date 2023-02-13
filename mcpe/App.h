#pragma once

class AppPlatform;
struct AppContext {
    char filler[0x10];
    AppPlatform* platform;
    bool doRender;
};

class App {

public:

    void** vtable = nullptr;
    static inline void (*App_init)(App*, AppContext&) = nullptr;

    void init(AppContext& ctx) {
       // std::cout << "app init start\n";
        App_init(this, ctx);
       // std::cout << "app init done\n";
    }

    void quit() {
        ((void (*)(App*)) vtable[23])(this);
    }

    bool wantToQuit() {
        return ((bool (*)(App*)) vtable[24])(this);
    }

};