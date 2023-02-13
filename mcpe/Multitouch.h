#pragma once

class Multitouch {

public:
    static inline void (*feed)(bool button, char type, short x, short y, int ss) = nullptr;

};