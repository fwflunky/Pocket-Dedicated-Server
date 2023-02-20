//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_PLAYER_H
#define MCPELAUNCHER_PLAYER_H


#include <unordered_map>
#include "../entity/mob/Mob.h"
#include "../network/NetworkIdentifier.h"
#include "../item/ItemInstance.h"
#include "inventory/PlayerInventoryProxy.h"
#include "../level/chunk/PlayerChunkSource.h"
#include "inventory/EnderChestContainer.h"
#include "inventory/IContainerManager.h"
#include "certificate/Certificate.h"

class Player : public Mob {
public:
    static void initHooks(void* handle);
    static inline std::unordered_map<std::string, std::pair<std::string, int>> ipsHolder;

    static inline void (*Player_addItem)(Player*, ItemInstance&) = nullptr;
    static inline void (*Player_sendInventory)(Player*) = nullptr;
    static inline bool (*Player_checkBed)(Player*, bool) = nullptr;
    static inline void (*Player_feed)(Player*, int) = nullptr;
    static inline void (*Player_eat)(Player*, int, float) = nullptr;
    static inline void (*Player_teleportTo)(Player*, Vec3 const&, int, int) = nullptr;
    static inline void (*Player_updateTeleportDestPos)(Player*) = nullptr;
    static inline Vec3 (*Player_getSpawnPosition)(Player*) = nullptr;
    static inline bool (*Player__hurt)(Player*, EntityDamageSource const&, int, bool, bool) = nullptr;
    static inline void (*Player_setContainerManager)(Player*, std::shared_ptr<IContainerManager>) = nullptr;
    static inline void (*Player_take)(Player*, Entity&, int) = nullptr;
    static inline std::shared_ptr<IContainerManager> (*Player_getContainerManager)(Player*) = nullptr;

    char filler[4016 - sizeof(Mob)];
    std::string nickname;
    char fillerr[32];
    NetworkIdentifier identifier; //144 size //4052 offset
    char filler1[26];
    Certificate* certificate;
    char filler6[30];
    PlayerChunkSource* playerChunkSource; //4260 (4259)
    char filler2[110];
    IContainerManager* openedContainerManager;
    char fillers[4];
    PlayerInventoryProxy* inventoryProxy; //4384 (4383)
    char fillersr[3];
    bool bedSome;
    char filler4[100];
    EnderChestContainer* enderChestContainer;
    char filler3[4624 - (4384 + 4 + 6 + 100 + 4)];
    void disconnect(const std::string& message, bool hide = false);
    void close();
    void addItem(ItemInstance& inst);
    void sendInventory();
    bool checkBed(bool);
    void sendMessage(const std::string& msg) const;
    void sendMessageTranslated(const std::string& tr, const std::vector<std::string>& vec) const;
    void sendPopup(const std::string& msg) const;
    void feed(int f);
    void eat(int f, float sat);
    void teleportTo(Vec3 const& vec, int, int);
    void updateTeleportDestPos();
    Vec3 getSpawnPosition();
    bool _hurt(EntityDamageSource const& s, int i, bool b, bool bb);
    void setContainerManager(std::shared_ptr<IContainerManager> cont);
    std::shared_ptr<IContainerManager> getContainerManager();
    void take(Entity& e, int i);
    std::pair<std::string, unsigned short> getFuckingIpPortWithAccessToFuckingRakNetBruh();
};


#endif //MCPELAUNCHER_PLAYER_H
