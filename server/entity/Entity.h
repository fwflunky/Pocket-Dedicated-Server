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
class AngryComponent;

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
    static inline void (*Entity_drop)(Entity*, ItemInstance const&, bool) = nullptr; //_ZN6Entity4dropERK12ItemInstanceb
    static inline void (*Entity_setSitting)(Entity*, bool) = nullptr; //_ZN6Entity10setSittingEb
    static inline bool (*Entity_isSitting)(Entity*) = nullptr; //_ZNK6Entity9isSittingEv
    static inline Mob* (*Entity_getOwner)(Entity*) = nullptr; //_ZNK6Entity8getOwnerEv
    static inline bool (*Entity_isTame)(Entity*) = nullptr; //_ZNK6Entity6isTameEv
    static inline void (*Entity_setTarget)(Entity*, Entity*) = nullptr; //_ZN6Entity9setTargetEPS_
    static inline float (*Entity_distanceToE)(Entity*, Entity const&) = nullptr; //_ZNK6Entity10distanceToERKS_
    static inline float (*Entity_distanceToV)(Entity*, Vec3 const&) = nullptr; //_ZNK6Entity10distanceToERK4Vec3

    virtual ~Entity();
    char filler[40]; //4 - dtor
    int ownerUniqueId;
    char fillerr[34];
    float x; //84
    float y;
    float z;
    char fillerss[75];
    SynchedEntityData* entityData;
    char fillersss[68];
    int maybeEntityType; //244
    char fillerd[2780];
    AngryComponent* angryComponent;
    char fillerds[180];
    unsigned long long int runtimeId; //3212
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
    void drop(ItemInstance const& item, bool drag);
    void setSitting(bool sit);
    bool isSitting();
    Mob* getOwner();
    bool isTame();
    float distanceTo(const Entity& e);
    float distanceTo(const Vec3& vec);
    void setTarget(Entity* target);
};

#endif //MCPELAUNCHER_ENTITY_H
