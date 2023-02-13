#include <iostream>
#include <dlfcn.h>
#include <stdarg.h>
#include <cstring>
#include <string>
#include "common.h"
#include <thread>
#include "BotInstance.h"


extern "C"
void pshufb(char *dest, char *src) {
    char new_dest[16];
    for (int i = 0; i < 16; i++)
        new_dest[i] = (src[i] & 0x80) ? 0 : dest[src[i] & 15];
    memcpy(dest, new_dest, 16);
}
extern "C"
void pshufb_xmm4_xmm0();

#include <functional>
#include <sys/mman.h>
#include <EGL/egl.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (sizeof(std::string("")) != 4) {
        throw std::invalid_argument("sizeof(std::string()) != 4, size = " + std::to_string(sizeof(std::string(""))));
        return 0;
    }
  //  freopen("/dev/null", "w", stderr);
   registerCrashHandler();
   //std::string ip = std::getenv("SIP");
  // int port = std::atoi(std::getenv("SPORT"));
  // std::cout << ip << ":" << port << "\n";
   
    BotInstance server;

    return 0;
}
