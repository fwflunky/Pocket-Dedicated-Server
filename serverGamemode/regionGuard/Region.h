//
// Created by user on 01.02.23.
//

#ifndef MCPELAUNCHER_REGION_H
#define MCPELAUNCHER_REGION_H


#include "../../server/math/aabb/AABB.h"
#include <string>
#include <set>

class Region {
public:
    std::string ownerName;
    std::string regionName;
    int dimensionId;
    AABB box;
    //Vec3 door pos //to teleport player to door which are not member of region
    std::set<std::string> memberNames;
    bool monstersAllowed = true;
    bool explodesAllowed = true;
    bool pvPAllowed = true;
    bool pvEAllowed = true;
    bool enderChestAccess = false;
    bool chestAccess = false;
    bool furnaceAccess = false;
    bool boatPlaceOnWaterAllowed = true;
    bool breweryAccess = false;

    Region(const std::string& owner, const std::string& region, const AABB& size, int dimId);
    bool addMember(const std::string& name);
    bool isMember(const std::string& name) const;
};


#endif //MCPELAUNCHER_REGION_H
