//
// Created by user on 26.01.23.
//

#include "Level.h"
#include "../../thirdParty/hybris/include/hybris/dlfcn.h"
#include "../../src/hook.h"
#include "../statics.h"

void Level::initHooks(void *handle) {
    Level_getUsers = (std::vector<Player*>* (*)(Level*)) hybris_dlsym(handle, "_ZN5Level8getUsersEv");
    Level_setTime = (void (*)(Level*, int)) hybris_dlsym(handle, "_ZN5Level7setTimeEi");
    Level__syncTime = (void (*)(Level*, int)) hybris_dlsym(handle, "_ZN5Level9_syncTimeEi");
    Level_addParticle = (int (*)(Level*, int, Vec3 const&, Vec3 const&, int)) hybris_dlsym(handle, "_ZN5Level11addParticleE12ParticleTypeRK4Vec3S3_i");
    Level_broadcastLevelEvent = (void (*)(Level*, short, Vec3 const&, int, Player*)) hybris_dlsym(handle, "_ZN5Level19broadcastLevelEventE10LevelEventRK4Vec3iP6Player");
    Level_getDimension = (Dimension* (*)(Level*, int)) hybris_dlsym(handle, "_ZNK5Level12getDimensionE11DimensionId");
    Level_suspendPlayer = (void (*)(Level*, Player&)) hybris_dlsym(handle, "_ZN5Level13suspendPlayerER6Player");
    Level_resumePlayer = (void (*)(Level*, Player&)) hybris_dlsym(handle, "_ZN5Level12resumePlayerER6Player");
    Level_createDimension = (void (*)(Level*, int)) hybris_dlsym(handle, "_ZN5Level15createDimensionE11DimensionId");
    Level_saveGameData = (void (*)(Level*)) hybris_dlsym(handle, "_ZN5Level12saveGameDataEv");
    Level_forceFlushRemovedPlayers = (void (*)(Level*)) hybris_dlsym(handle, "_ZN5Level24forceFlushRemovedPlayersEv");
}

std::vector<Player *>* Level::getUsers() {
    return Level_getUsers(this);
}

void Level::_syncTime(int time) {
    Level__syncTime(this, time);
}

void Level::setTime(int time) {
    Level_setTime(this, time);
}

int Level::addParticle(int type, const Vec3 &pos, const Vec3 &size, int some) {
    return Level_addParticle(this, type, pos, size, some);
}

void Level::addParticleCustom(int type, int data, const Vec3 &pos) {
    broadcastLevelEvent((short) (0x4000 | (type & 0xFFF)), pos, data, nullptr);
}

void Level::broadcastLevelEvent(short id, const Vec3 &pos, int data, Player *p) {
    Level_broadcastLevelEvent(this, id, pos, data, p);
}

Dimension *Level::getDimension(int d) {
    return Level_getDimension(this, d);
}

void Level::suspendPlayer(Player &p) {
    Level_suspendPlayer(this, p);
}

void Level::resumePlayer(Player &p) {
    Level_resumePlayer(this, p);
}

void Level::createDimension(int id) {
    Level_createDimension(this, id);
}

void Level::saveGameData() {
    Level_saveGameData(this);
}

void Level::forceFlushRemovedPlayers() {
    Level_forceFlushRemovedPlayers(this);
}
