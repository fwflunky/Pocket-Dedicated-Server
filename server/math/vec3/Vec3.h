//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_VEC3_H
#define MCPELAUNCHER_VEC3_H


class Vec3 {
public:
    static void initHooks(void* handle);

    static inline Vec3* ZERO = nullptr;

    Vec3(float xx, float yy, float zz);
    float x, y, z;
};


#endif //MCPELAUNCHER_VEC3_H
