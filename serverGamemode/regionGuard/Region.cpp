//
// Created by user on 01.02.23.
//

#include <algorithm>
#include "Region.h"

Region::Region(const std::string &owner, const std::string& region, const AABB &size, int dimId) {
    regionOwnerName = owner;
    regionName = region;
    box = size;
    dimensionId = dimId;
}

bool Region::addMember(const std::string &name) {
    std::string tname = name;
    std::transform(tname.begin(), tname.end(), tname.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    if(memberNames.contains(tname))
        return false;
    memberNames.insert(tname);
    return true;
}

bool Region::isMember(const std::string &name) const {
    std::string tname = name;
    std::transform(tname.begin(), tname.end(), tname.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return memberNames.contains(tname);
}

void Region::delMember(const std::string &name) {
    std::string tname = name;
    std::transform(tname.begin(), tname.end(), tname.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    memberNames.erase(tname);
}

bool Region::isOwner(const std::string &name) const {
    std::string tname = name;
    std::transform(tname.begin(), tname.end(), tname.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return regionOwnerName == tname;
}
