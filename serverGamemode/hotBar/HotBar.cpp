//
// Created by user on 19.02.23.
//

#include <thread>
#include "HotBar.h"
#include "../../server/statics.h"
#include "../../server/level/Level.h"

void HotBar::scheduleUpdate() {
    std::thread([](){
        while(true){
            usleep(1000  * 800);
            if(!needBlink) {
                if (currentOffset > maxOffset) {
                    currentOffset = 0;
                    current.clear();
                    needBlink = true;
                } else {
                    current += base[currentOffset++];
                }
            } else {
                if(blinkTicks % 2 == 0)
                    current = base;
                else
                    current = "";

                if(blinkTicks++ > 3) {
                    needBlink = false;
                    blinkTicks = 0;
                    current.clear();
                }
            }
            TextPacket packet;
            packet.type = 4;
            packet.source = "";
            packet.message = "\n\n\n\n" + current;

            statics::runOnNextTick([packet](){
                for (auto *user: *statics::serverNetworkHandler->mainLevel->getUsers()) {
                    statics::serverNetworkHandler->networkHandler->send(user->identifier, packet);
                }
            });
        }
    }).detach();
}
