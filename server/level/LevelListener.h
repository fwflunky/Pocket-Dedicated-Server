//
// Created by user on 04.02.23.
//

#ifndef MCPELAUNCHER_LEVELLISTENER_H
#define MCPELAUNCHER_LEVELLISTENER_H


class Vec3;
#include <string>
class Player;
class Entity;
class LevelChunk;

#include "BlockSourceListener.h"
class LevelListener : public BlockSourceListener {
public:
    virtual ~LevelListener() override = default;
    virtual void allChanged(){}; //bool?
    virtual int addParticle(int, Vec3 const&, Vec3 const&, int) {return 0;};
    virtual void playMusic(std::string const&, Vec3 const&, float){};
    virtual void playStreamingMusic(std::string const&, int, int, int){};
    virtual void onEntityAdded(Entity&){};
    virtual void onEntityRemoved(Entity&){};
    virtual void onNewChunkFor(Player&, LevelChunk&){};
    virtual void onChunkLoaded(LevelChunk&){};
    virtual void onChunkUnloaded(LevelChunk&){};
    virtual void onLevelDestruction(){};
    virtual void levelEvent(int, Vec3 const&, int){};
    virtual void levelSoundEvent(int, Vec3 const&, int, int, bool, bool){};
    virtual void levelSoundEvent(std::string const&, Vec3 const&, float, float){};
    virtual void stopSoundEvent(std::string const&){};
    virtual void stopAllSounds(){};
    virtual void playerListChanged(){};
};


#endif //MCPELAUNCHER_LEVELLISTENER_H
