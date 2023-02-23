//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_DIMENSION_H
#define MCPELAUNCHER_DIMENSION_H



#include "../network/packets/Packet.h"
#include "LevelListener.h"
#include "SavedData.h"
#include "chunk/MainChunkSource.h"

class Player;
class Entity;
class ChunkSource;

class Dimension : public LevelListener, public SavedData {
public:
    static void initHooks(void* handle);

    ~Dimension() override = default;
    void purev_1() override{};
    void purev_2() override{};

    static inline void (*Dimension_sendPacketForEntity)(Dimension*, Entity&, Packet&, Player*) = nullptr;
    static inline void (*Dimension_sendPacketForPosition)(Dimension*, BlockPos const&, Packet const&, Player*) = nullptr;
    static inline ChunkSource* (*Dimension_getChunkSource)(Dimension*) = nullptr;

    char filler[104];
    int dimensionId;
    char filler1[74];
    MainChunkSource* mainChunkSource;

    void sendPacketForEntity(Entity&e, Packet&p, Player* pp);
    void sendPacketForPosition(BlockPos const &pos , Packet const&p, Player* pp);
    ChunkSource* getChunkSource();

    bool operator ==(Dimension* dimension) const;
    bool operator !=(Dimension* dimension) const;
};
#endif //MCPELAUNCHER_DIMENSION_H
