//
// Created by user on 26.01.23.
//

#ifndef MCPELAUNCHER_NETWORKIDENTIFIER_H
#define MCPELAUNCHER_NETWORKIDENTIFIER_H
#include <string>
#include <netinet/in.h>

class NetworkIdentifier {
public:
    static void initHooks(void* handle);

    static inline void (*NetworkIdentifier_ctor1)(NetworkIdentifier*, std::string const&, unsigned short) = nullptr; //_ZN17NetworkIdentifierC2ERKSst
    static inline std::string* (*NetworkIdentifier_toString)(NetworkIdentifier*) = nullptr; //_ZNK17NetworkIdentifier10getAddressEv
    static inline void (*NetworkIdentifier__init)(NetworkIdentifier*, void* sa) = nullptr; //_ZNK17NetworkIdentifier10getAddressEv
    static inline char* (*SystemAddress_toString)(void*, bool) = nullptr; //_ZNK17NetworkIdentifier10getAddressEv
    static inline void* (*RakPeer_GetSystemAddressFromGuid)(void*, NetworkIdentifier) = nullptr; //_ZNK6RakNet7RakPeer24GetSystemAddressFromGuidENS_10RakNetGUIDE
    // RakNetInstance::_getPeer(RakNetInstance *this,NetworkIdentifier const&)
    unsigned long long id;
    void* ptr;
    void* ptr2;
    unsigned short port;
    sockaddr_in* in1;
    sockaddr_in* in2;
    char filler2[136 - 8 - 8 - 4]; //136
    NetworkIdentifier(std::string const& a, unsigned short b);
    NetworkIdentifier() = default;
    std::string satos(bool b);
    bool operator==(const NetworkIdentifier& idd) const;

    std::string toString();
    std::string getAddress();
};


#endif //MCPELAUNCHER_NETWORKIDENTIFIER_H
