//
// Created by user on 08.02.23.
//

#ifndef MCPELAUNCHER_ARROW_H
#define MCPELAUNCHER_ARROW_H

#include "../Entity.h"

class Player;

class Arrow : public Entity {
public:
    static void initHooks(void* handle);
    static inline void (*Arrow_playerTouch)(Arrow*, Player&) = nullptr;

    void playerTouch(Player& p);
};


#endif //MCPELAUNCHER_ARROW_H
