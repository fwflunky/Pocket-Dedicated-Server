//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_VEC2_H
#define MCPELAUNCHER_VEC2_H


class __attribute__((packed)) Vec2 {
public:
    static void initHooks(void* handle);

    static inline Vec2* ZERO = nullptr;

    Vec2(float xx, float zz);
    float x, z;
};


#endif //MCPELAUNCHER_VEC2_H
