#pragma once

class Options {

public:
    static inline bool (*Options_getFullscreen)(Options*) = nullptr;
    static inline void (*Options_setFullscreen)(Options*, bool) = nullptr;
    static inline void (*Options_setUsername)(Options*, const std::string&) = nullptr;

    bool getFullscreen() {
        return Options_getFullscreen(this);
    }
    void setFullscreen(bool b) {
        Options_setFullscreen(this, b);
    }

    void setUsername(const std::string& name) {
        Options_setUsername(this, name);
    }

};
