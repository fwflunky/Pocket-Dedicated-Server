//
// Created by user on 28.01.23.
//

#ifndef MCPELAUNCHER_MovePlayerPacket_H
#define MCPELAUNCHER_MovePlayerPacket_H

#include "Packet.h"
#include "../../math/vec2/Vec2.h"
#include "../../math/vec3/Vec3.h"
class MovePlayerPacket : public Packet {
public:
    static void initHooks(void* handle);

    static inline void (*MovePlayerPacket_write)(MovePlayerPacket* move, void* bs) = nullptr;

    ~MovePlayerPacket() override = default;
    void write(void* bs) override;

    unsigned char getId() override;

    unsigned long long entityRuntimeId;
    Vec3 pos = *Vec3::ZERO;
    Vec2 yawPitch = *Vec2::ZERO;
    float bodyYaw;
    unsigned char mode;
    bool onGround;
    unsigned long long entityRuntimeId2;
    int itemId = 0,cause = 0;
};

#endif //MCPELAUNCHER_MovePlayerPacket_H
