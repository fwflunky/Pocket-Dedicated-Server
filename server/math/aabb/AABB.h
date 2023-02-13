//
// Created by user on 01.02.23.
//

#ifndef MCPELAUNCHER_AABB_H
#define MCPELAUNCHER_AABB_H


#include "../vec3/Vec3.h"
#include <string>

class AABB { //first full class without fillers
public:
    static void initHooks(void* handle);
    static inline void (*AABB_fromPoint)(AABB*, Vec3 const& pos1, Vec3 const& pos2) = nullptr;
    static inline bool (*AABB_intersects)(AABB*, AABB const& what) = nullptr;
    static inline bool (*AABB_contains)(AABB*, Vec3 const& what) = nullptr;
    static inline void (*AABB_ctor0)(AABB*) = nullptr;
    static inline float (*AABB_distanceToSqr)(AABB*, const AABB &) = nullptr;
    static inline float (*AABB_distanceTo)(AABB*, const AABB &) = nullptr;

    float startX;
    float startY;
    float startZ;

    float endX;
    float endY;
    float endZ;

    bool isEmpty;

    AABB();
    AABB(Vec3 const& pos1, Vec3 const& pos2);
    void fromPoint(Vec3 const& pos1, Vec3 const& pos2);
    bool intersects(AABB const& what);
    bool contains(Vec3 const& what);
    std::string toString() const;
    bool fromString(const std::string& in);
    float distanceToSqr(const AABB& aabb);
    float distanceTo(const AABB& aabb);
};


#endif //MCPELAUNCHER_AABB_H
