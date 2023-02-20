//
// Created by user on 01.02.23.
//

#include "AABB.h"
#include "../../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "range/v3/range.hpp"
#include "range/v3/view/split.hpp"

void AABB::initHooks(void *handle) {
    AABB_ctor0 = (void (*)(AABB*)) hybris_dlsym(handle, "_ZN4AABBC2Ev");
    AABB_fromPoint = (void (*)(AABB*, const Vec3 &, const Vec3 &)) hybris_dlsym(handle, "_ZN4AABB10fromPointsERK4Vec3S2_");
    AABB_intersects = (bool (*)(AABB*, const AABB &)) hybris_dlsym(handle, "_ZNK4AABB10intersectsERKS_");
    AABB_contains = (bool (*)(AABB*, const Vec3 &)) hybris_dlsym(handle, "_ZNK4AABB8containsERK4Vec3");
    AABB_distanceToSqr = (float (*)(AABB*, const AABB &)) hybris_dlsym(handle, "_ZNK4AABB13distanceToSqrERKS_");
    AABB_distanceTo = (float (*)(AABB*, const AABB &)) hybris_dlsym(handle, "_ZNK4AABB10distanceToERKS_");
}

AABB::AABB() {
    AABB_ctor0(this);
}

void AABB::fromPoint(const Vec3 &pos1, const Vec3 &pos2) {
    AABB_fromPoint(this, pos1, pos2);
}

bool AABB::intersects(const AABB &what) {
    return AABB_intersects(this, what);
}

bool AABB::contains(const Vec3 &what) {
    return AABB_contains(this, what);
}

std::string AABB::toString() const {
    std::string out;
    out += std::to_string(startX);
    out += ";";
    out += std::to_string(startY);
    out += ";";
    out += std::to_string(startZ);
    out += ";";
    out += std::to_string(endX);
    out += ";";
    out += std::to_string(endY);
    out += ";";
    out += std::to_string(endZ);
    out += ";";
    out += (isEmpty ? "1" : "0");
    return out;
}

bool AABB::fromString(const std::string& in) {
    auto words = in | ranges::views::split(';') | ranges::to<std::vector<std::string>>();
    startX = std::stof(words[0]);
    startY = std::stof(words[1]);
    startZ = std::stof(words[2]);

    endX = std::stof(words[3]);
    endY = std::stof(words[4]);
    endZ = std::stof(words[5]);

    isEmpty = std::stoi(words[6]) == 1;
}

float AABB::distanceToSqr(const AABB &aabb) {
    return AABB_distanceToSqr(this, aabb);
}

AABB::AABB(const Vec3 &pos1, const Vec3 &pos2) {
    AABB_ctor0(this);
    AABB_fromPoint(this, pos1, pos2);
}

float AABB::distanceTo(const AABB &aabb) {
    return AABB_distanceTo(this, aabb);
}

