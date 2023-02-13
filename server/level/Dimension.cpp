//
// Created by user on 26.01.23.
//

#include "Dimension.h"
#include "../../hybris/include/hybris/dlfcn.h"

void Dimension::initHooks(void *handle) {
    Dimension_sendPacketForEntity = (void (*)(Dimension*, Entity&, Packet&, Player*)) hybris_dlsym(handle, "_ZN9Dimension19sendPacketForEntityERK6EntityRK6PacketPK6Player");
    Dimension_sendPacketForPosition = (void (*)(Dimension*, BlockPos const&, Packet const&, Player*)) hybris_dlsym(handle, "_ZN9Dimension21sendPacketForPositionERK8BlockPosRK6PacketPK6Player");
    Dimension_getChunkSource = (ChunkSource * (*)(Dimension*)) hybris_dlsym(handle, "_ZNK9Dimension14getChunkSourceEv");
}

void Dimension::sendPacketForEntity(Entity &e, Packet &p, Player *pp) {
    Dimension_sendPacketForEntity(this, e, p, pp);
}

ChunkSource *Dimension::getChunkSource() {
    return Dimension_getChunkSource(this);
}

void Dimension::sendPacketForPosition(BlockPos const&pos, Packet const&p, Player *pp) {
    Dimension_sendPacketForPosition(this, pos, p, pp);
}
