//
// Created by user on 26.01.23.
//

#include "Entity.h"
#include "../../hybris/include/hybris/dlfcn.h"

std::string *Entity::getNameTag() {
    return Entity_getNameTag(this);
}

Dimension *Entity::getDimension() {
    return Entity_getDimension(this);
}

void Entity::initHooks(void *handle) {
    Entity_getNameTag = (std::string* (*)(Entity*)) hybris_dlsym(handle, "_ZNK6Entity10getNameTagEv");
    Entity_setNameTag = (void (*)(Entity*, std::string const&)) hybris_dlsym(handle, "_ZN6Entity10setNameTagERKSs");
    Entity_setNameTagVisible = (void (*)(Entity*, bool)) hybris_dlsym(handle, "_ZN6Entity10setNameTagERKSs");
    Entity_getDimension = (Dimension* (*)(Entity*)) hybris_dlsym(handle, "_ZNK6Entity12getDimensionEv");
    Entity_getLevel = (Level* (*)(Entity*)) hybris_dlsym(handle, "_ZN6Entity8getLevelEv");
    Entity_isRemoved = (bool (*)(Entity*)) hybris_dlsym(handle, "_ZNK6Entity9isRemovedEv");
    Entity_burn = (void (*)(Entity*, int, bool)) hybris_dlsym(handle, "_ZN6Entity4burnEib");
    Entity_hurt = (bool (*)(Entity*, EntityDamageSource const&, int, bool, bool)) hybris_dlsym(handle, "_ZN6Entity4hurtERK18EntityDamageSourceibb");
    Entity_setOnFire = (void (*)(Entity*, int)) hybris_dlsym(handle, "_ZN6Entity9setOnFireEi");
    Entity_moveTo = (void (*)(Entity*, Vec3 const&, Vec2 const&)) hybris_dlsym(handle, "_ZN6Entity6moveToERK4Vec3RK4Vec2");
    Entity_setPos = (void (*)(Entity*, Vec3 const&)) hybris_dlsym(handle, "_ZN6Entity6setPosERK4Vec3");
    Entity_getUniqueId = (unsigned long long int (*)(Entity*)) hybris_dlsym(handle, "_ZNK6Entity11getUniqueIDEv");
    //Entity_getRuntimeId = (int (*)(Entity*)) hybris_dlsym(handle, "_ZNK6Entity12getRuntimeIDEv");
    Entity_getInventory = (Inventory (*)(Entity*)) hybris_dlsym(handle, "_ZN6Entity12getInventoryEv");
    Entity_getTeleportComponent = (TeleportComponent* (*)(Entity*)) hybris_dlsym(handle, "_ZNK6Entity20getTeleportComponentEv");
    Entity_remove = (void (*)(Entity*)) hybris_dlsym(handle, "_ZN6Entity6removeEv");
    Entity_setSize = (void (*)(Entity*, float, float)) hybris_dlsym(handle, "_ZN6Entity7setSizeEff");
}

bool Entity::isRemoved() {
    return Entity_isRemoved(this);
}

Level *Entity::getLevel() {
    return Entity_getLevel(this);
}

void Entity::burn(int hp, bool b) {
    Entity_burn(this, hp, b);
}

void Entity::setPos(Vec3 const& vec) {
    Entity_setPos(this, vec);
}

void Entity::setOnFire(int s) {
    Entity_setOnFire(this, s);
}

Inventory Entity::getInventory() {
    return Entity_getInventory(this);
}

void Entity::moveTo(const Vec3 &vec, const Vec2 &vec2) {
    Entity_moveTo(this, vec, vec2);
}

void Entity::setNameTag(const std::string &tag) {
    Entity_setNameTag(this, tag);
}

void Entity::setNameTagVisible(bool v) {
    Entity_setNameTagVisible(this, v);
}

bool Entity::hurt(const EntityDamageSource &s, int i, bool b, bool bb) {
    return Entity_hurt(this, s, i, b, bb);
}

unsigned long long int Entity::getUniqueId() {
    return Entity_getUniqueId(this);
}

TeleportComponent *Entity::getTeleportComponent() {
    return Entity_getTeleportComponent(this);
}

void Entity::remove() {
    Entity_remove(this);
}

void Entity::setSize(float xx, float zz) {
    Entity_setSize(this, xx, zz);
}


Entity::~Entity() = default;
