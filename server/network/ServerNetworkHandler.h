//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_SERVERNETWORKHANDLER_H
#define MCPELAUNCHER_SERVERNETWORKHANDLER_H


#include "../entity/Entity.h"
#include "../player/Player.h"
#include "../player/ServerPlayer.h"
#include "packets/TextPacket.h"
#include "ServerLocator.h"
#include "packets/UseItemPacket.h"
#include "networkHandler/NetworkHandler.h"
#include "packets/RemoveBlockPacket.h"
#include "packets/MovePlayerPacket.h"
#include "../commands/MinecraftCommands.h"
#include "packets/CommandStepPacket.h"
#include "packets/ContainerSetSlotPacket.h"
#include "packets/LoginPacket.h"


class ServerNetworkHandler {
public:
    static void initHooks(void* handle);

    static inline std::string serverMOTD = "§bAtmosphere §f'PE §b1.1§f";
    static inline std::string serverCore = "Vanilla Atmosphere";

    static inline void (*ServerNetworkHandler_onReady_ClientGeneration)(ServerNetworkHandler*, Player&, NetworkIdentifier const&) = nullptr;
    static inline void (*ServerNetworkHandler_disconnectClient)(ServerNetworkHandler*, NetworkIdentifier const&, std::string const&, bool) = nullptr;
    static inline void (*ServerNetworkHandler_onDisconnect)(ServerNetworkHandler*, NetworkIdentifier&, std::string const&, bool) = nullptr;
    static inline void (*ServerNetworkHandler_updateServerAnnouncement)(ServerNetworkHandler*) = nullptr;
   // static inline void (*ServerNetworkHandler_onPlayerReady)(ServerNetworkHandler*, Player&) = nullptr;
    static inline void (*ServerNetworkHandler__displayGameMessage)(ServerNetworkHandler*, const std::string&, const std::string&) = nullptr;
    static inline int (*ServerNetworkHandler__getActivePlayerCount)(ServerNetworkHandler*) = nullptr;
    static inline ServerPlayer* (*ServerNetworkHandler__getServerPlayer)(ServerNetworkHandler*, NetworkIdentifier const&) = nullptr;
    static inline void (*ServerNetworkHandler_handle_TextPacket)(ServerNetworkHandler*, NetworkIdentifier const&, TextPacket&) = nullptr;
    static inline void (*ServerNetworkHandler_handle_UseItemPacket)(ServerNetworkHandler*, NetworkIdentifier const&, UseItemPacket&) = nullptr;
    static inline void (*ServerNetworkHandler_handle_RemoveBlockPacket)(ServerNetworkHandler*, NetworkIdentifier const&, RemoveBlockPacket&) = nullptr;
    static inline void (*ServerNetworkHandler_handle_MovePlayerPacket)(ServerNetworkHandler*, NetworkIdentifier const&, MovePlayerPacket&) = nullptr;
    static inline void (*ServerNetworkHandler_handle_CommandStepPacket)(ServerNetworkHandler*, NetworkIdentifier const&, CommandStepPacket&) = nullptr;
    static inline void (*ServerNetworkHandler_handle_ContainerSetSlotPacket)(ServerNetworkHandler*, NetworkIdentifier const&, ContainerSetSlotPacket&) = nullptr;
    static inline void (*ServerNetworkHandler_handle_LoginPacket)(ServerNetworkHandler*, NetworkIdentifier const&, LoginPacket&) = nullptr;

    void _displayGameMessage(const std::string& pref, const std::string& msg);
    void onReady_ClientGeneration(Player& p, NetworkIdentifier& ne);
    //void onPlayerReady(Player& p);
    void disconnectClient(const NetworkIdentifier & id, const std::string& msg, bool s);
    int _getActivePlayerCount();
    ServerPlayer* _getServerPlayer(const NetworkIdentifier& i);
    void setMaxPlayers(int count);
    void updateServerAnnouncement() const;
    void handleTextPacket(NetworkIdentifier const& ident, TextPacket& pk);
    void handleUseItemPacket(NetworkIdentifier const& ident, UseItemPacket& pk);
    void handleRemoveBlockPacket(NetworkIdentifier const& ident, RemoveBlockPacket& pk);
    void handleMovePlayerPacket(NetworkIdentifier const& ident, MovePlayerPacket& pk);
    void handleCommandStepPacket(NetworkIdentifier const& ident, CommandStepPacket& pk);
    void handleContainerSetSlotPacket(NetworkIdentifier const& ident, ContainerSetSlotPacket& pk);
    void handleLoginPacket(NetworkIdentifier const& ident, LoginPacket& pk);


    char filler[11];
    Level* mainLevel;
    char filler1[4];
    NetworkHandler::NetworkHandler *networkHandler;
    char filler2[4];
    ServerLocator* serverLocator;
    //
    void* PacketSender;
    void* SkinInfoFactory;
    bool isWhitelistEnabled;
    void* WhiteList;
    void* OpsList;
    char filler3[152];
    MinecraftCommands* minecraftCommands;
    char filler4[62];
    int maxPlayersCount; //272
    char filler5[12];
    int currentPlayerCount;
};

#endif //MCPELAUNCHER_SERVERNETWORKHANDLER_H