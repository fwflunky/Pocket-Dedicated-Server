//
// Created by user on 01.02.23.
//

#include "Region.h"

Region::Region(const std::string &owner, const std::string& region, const AABB &size, int dimId) {
    ownerName = owner;
    regionName = region;
    box = size;
    dimensionId = dimId;
}

bool Region::addMember(const std::string &name) {
    if(memberNames.contains(name))
        return false;
    memberNames.insert(name);
    return true;
}

bool Region::isMember(const std::string &name) const {
    return memberNames.contains(name);
}
