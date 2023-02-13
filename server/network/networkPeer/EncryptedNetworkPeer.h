//
// Created by user on 29.01.23.
//

#ifndef MCPELAUNCHER_ENCRYPTEDNETWORKPEER_H
#define MCPELAUNCHER_ENCRYPTEDNETWORKPEER_H


//#include "NetworkPeer.h"
#include "../../util/hmac/HMAC.h"
#include <string>
class __attribute__((packed)) EncryptedNetworkPeer  {
public:
   /* static void initHooks(void *handle);

    static inline void (*EncryptedNetworkPeer_sendPacket)(EncryptedNetworkPeer *, std::string, int, int) = nullptr; //
    static inline std::string(*hmac_sign)(void* hmac, std::string&, unsigned long long) = nullptr; //
    char filler[3];
    NetworkPeer* peer;
    char filler1[4];
    Crypto::Hash::HMAC::HMAC* hmac;
    unsigned int sentPacketsCount;
    void sendPacket(std::string, int, int);
    static std::string hmacSign(void* hmac, std::string&, unsigned long long);*/
    //void enableEncryption(std::string&);
};


#endif //MCPELAUNCHER_ENCRYPTEDNETWORKPEER_H
