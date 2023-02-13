//
// Created by user on 27.01.23.
//

#ifndef MCPELAUNCHER_GAMEMODE_H
#define MCPELAUNCHER_GAMEMODE_H

#include "../player/Player.h"
#include "../item/ItemInstance.h"
#include "../level/BlockPos.h"
#include "../math/vec3/Vec3.h"

class  GameMode {
public:
    static void initHooks(void* handle);

    static inline bool (*GameMode_useItemOn)(GameMode*, Player&, ItemInstance&, BlockPos const&, char, Vec3 const&) = nullptr;
    static inline bool (*GameMode_useItem)(GameMode*, Player&, ItemInstance&) = nullptr;

    bool useItemOn(Player& p, ItemInstance& i, BlockPos const& pos, char c, Vec3 const& vec);
    bool useItem(Player& p, ItemInstance& i);
};


#endif //MCPELAUNCHER_GAMEMODE_H
