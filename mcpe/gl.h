#pragma once

struct gl {
    static inline std::string (*getOpenGLVendor)();
    static inline std::string (*getOpenGLRenderer)();
    static inline std::string (*getOpenGLVersion)();
    static inline std::string (*getOpenGLExtensions)();
};

namespace mce::Platform {

        struct OGL {

            static inline void (*OGL_initBindings)() = nullptr;
            static void initBindings() { OGL_initBindings(); }

        };

    }