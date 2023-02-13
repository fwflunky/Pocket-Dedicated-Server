//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_ENTITY_H
#define MCPELAUNCHER_ENTITY_H
#include <string>
#include "../math/vec3/Vec3.h"
#include "../math/vec2/Vec2.h"
#include "../player/inventory/Inventory.h"

#include "../level/Dimension.h"
#include "SynchedEntityData.h"
#include "damageSource/EntityDamageSource.h"
#include "teleportComponent/TeleportComponent.h"

//class Dimension;
class Level;


class Entity {
public:
    static void initHooks(void* handle);

    static inline std::string* (*Entity_getNameTag)(Entity*) = nullptr;
    static inline void (*Entity_setNameTag)(Entity*, std::string const&) = nullptr;
    static inline void (*Entity_setNameTagVisible)(Entity*, bool) = nullptr;
    static inline Dimension* (*Entity_getDimension)(Entity*) = nullptr;
    static inline Level* (*Entity_getLevel)(Entity*) = nullptr;
    static inline bool (*Entity_isRemoved)(Entity*) = nullptr;
    static inline void (*Entity_burn)(Entity*, int, bool) = nullptr;
    static inline bool (*Entity_hurt)(Entity*, EntityDamageSource const&, int, bool, bool) = nullptr;
    static inline void (*Entity_moveTo)(Entity*, Vec3 const&, Vec2 const&) = nullptr;
    static inline void (*Entity_setPos)(Entity*, Vec3 const&) = nullptr;
    static inline void (*Entity_setOnFire)(Entity*, int) = nullptr;
    static inline TeleportComponent* (*Entity_getTeleportComponent)(Entity*) = nullptr;
    static inline unsigned long long int (*Entity_getUniqueId)(Entity*) = nullptr;
  //  static inline int (*Entity_getRuntimeId)(Entity*) = nullptr;
    static inline Inventory (*Entity_getInventory)(Entity*) = nullptr;
    static inline void (*Entity_remove)(Entity*) = nullptr; //_ZN6Entity6removeEv
    static inline void (*Entity_setSize)(Entity*, float, float) = nullptr; //_ZN6Entity6removeEv

    virtual ~Entity();
    char filler[59]; //4 - dtor
    char fillerr[19];
    float x;
    float y;
    float z;
    char fillerss[77];
    SynchedEntityData* entityData;
    char fillersss[3030];
    unsigned long long int runtimeId;
    char filler1[3296 - (92 + 77 + 4 + 3034 + 8) + 1 - 2]; //end of entity - before variables
    //ItemInstance* entityAsItem;

    std::string* getNameTag();
    void setNameTag(std::string const& tag);
    void setNameTagVisible(bool v);
    Dimension* getDimension();
    Level* getLevel();
    bool isRemoved();
    void burn(int hp, bool b);
    bool hurt(EntityDamageSource const& s, int i, bool b, bool bb);
    void setOnFire(int s);

    void moveTo(Vec3 const& vec, Vec2 const& vec2);
    void setPos(Vec3 const& vec);
    unsigned long long int getUniqueId();
    Inventory getInventory();
    TeleportComponent* getTeleportComponent();
    void remove();
    void setSize(float xx, float zz);
};

#endif //MCPELAUNCHER_ENTITY_H
