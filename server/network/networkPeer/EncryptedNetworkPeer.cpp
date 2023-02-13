//
// Created by user on 29.01.23.
//
/*
#include <iostream>
#include <atomic>
#include "EncryptedNetworkPeer.h"
#include "../../../hybris/include/hybris/dlfcn.h"
#include "../../../src/hook.h"
void EncryptedNetworkPeer::initHooks(void *handle) {
    //EncryptedNetworkPeer_sendPacket = (void (*)(EncryptedNetworkPeer *, std::string, int, int)) hybris_dlsym(handle, "_ZN20EncryptedNetworkPeer10sendPacketESsN11NetworkPeer11ReliabilityEi");
  // hookFunction((void *) hybris_dlsym(handle, "_ZN6Crypto4Hash4HMAC4signERKSsy"), (void *) &EncryptedNetworkPeer::hmacSign, (void **) &EncryptedNetworkPeer::hmac_sign);
 //  hookFunction((void *) hybris_dlsym(handle, "_ZN20EncryptedNetworkPeer10sendPacketESsN11NetworkPeer11ReliabilityEi"), (void *) &EncryptedNetworkPeer::sendPacket, (void **) &EncryptedNetworkPeer::EncryptedNetworkPeer_sendPacket);

}

void EncryptedNetworkPeer::sendPacket(std::string s, int i, int ii) {

    std::cout << "EncryptedNetworkPeer send " << i << " " << ii << "\n";
    std::cout << "EncryptedNetworkPeer this " << this << "\n";
    std::cout << "EncryptedNetworkPeer someint " << hmac << "\n";

   // sleep(1000);
    EncryptedNetworkPeer_sendPacket(this, s, i, ii);
}

std::string EncryptedNetworkPeer::hmacSign(void *hmac, std::string &s, unsigned long long int l) {
    std::cout << "hmacSign " << s.size() << " " << l << "\n";
    return hmac_sign(hmac, s, l);
}*/

/*
void EncryptedNetworkPeer::enableEncryption(std::string &) {
    std::cout << "EncryptedNetworkPeer enableEncryption" << "\n";
}*/
