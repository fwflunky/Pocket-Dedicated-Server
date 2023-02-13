//
// Created by user on 27.01.23.
//

#include "RakNetServerLocator.h"
#include "../../hybris/include/hybris/dlfcn.h"
void RakNetServerLocator::initHooks(void *handle) {
    RakNetServerLocator_announceServer = (void (*)(RakNetServerLocator *, std::string const&, std::string const&, int, int, int)) hybris_dlsym(handle, "_ZN19RakNetServerLocator14announceServerERKSsS1_8GameTypeii");
}

void RakNetServerLocator::announceServer(std::string const& a, std::string const& b, int c, int d, int e) {
    RakNetServerLocator_announceServer(this, a, b, c, d, e);
}
