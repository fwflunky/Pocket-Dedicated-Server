#include "PetHelper.h"
#include "../../server/player/ServerPlayer.h"

namespace PetHelper {
    bool PetHelper::Wolf::onDamage(Entity *wolf, Entity *damager, int cause) { //todo fix tamed wolf despawn
        if (wolf->isTame()) { //приручен
            if (cause == 2 || cause == 3) {
                auto *owner = (ServerPlayer *) wolf->getOwner();
               // wolf->setNameTag("Dinnerbone");
               // wolf->setNameTagVisible(true);
                if (owner == damager)
                    return true;

                if (!owner) {
                    //owner offline
                    if (damager && damager->maybeEntityType == 30)
                        ((ServerPlayer *) damager)->sendMessage("§l§7⋗ §r§cВы пытаетесь ударить волка, владелец которого не в сети.");
                    return false;
                } else if (damager && wolf->isSitting()) {
                    if (damager->maybeEntityType == 30)
                        ((ServerPlayer *) damager)->sendMessage("§l§7⋗ §r§cВы пытаетесь ударить сидящего волка.");
                    return false;
                } else if (damager && wolf->getDimension() != owner->getDimension() || wolf->distanceTo(*owner) > 30) {
                    std::string nick = "Кто-то";
                    if (damager->maybeEntityType == 30) {
                        nick = ((ServerPlayer *) damager)->nickname;
                        ((ServerPlayer *) damager)->sendMessage("§l§7⋗ §r§cВы пытаетесь ударить волка, владелец которого находится далеко от него.");
                    }

                    owner->sendMessage(nick + " пытается ударить вашего волка, но вы находитесь далеко от него. Урон отменен.");
                    return false;
                }
            } else if(cause == 6 || cause == 7 || cause == 8){ //burn
                //8 - in lava
                //7 - burn in flames
                //6 - in fire
                auto *owner = (ServerPlayer *) wolf->getOwner();

                if (!owner) {
                    ((Mob*) wolf)->addEffect({12, 20*60, 1});
                    return false;
                } else if (wolf->getDimension() != owner->getDimension() || wolf->distanceTo(*owner) > 30) { //todo change wolf dimension
                    if(cause == 7) { //don't spam
                        owner->sendMessage("§l§7⋗ §r§7Ваш волк горит, но вы находитесь далеко от него. Ему выдан эффект защиты от горения на минуту.");
                        ((Mob*) wolf)->addEffect({12, 20*60, 1});
                    }
                    return false;
                }
            }
        }
        return true;
    }
}