#pragma once

#include <iostream>

class UserAuthentication {
public:
    //UserAuthentication
    static inline unsigned long long int cid = 9999;

    static unsigned long long int getClientRandomId(void *ua) {
        return cid;
    };

    //int s1;
   // char filler[4];
    static inline unsigned long long int uuidSeed = 3464885859205597182;
    static inline void (*UserAuthentication_regenerateSS)(UserAuthentication *self, const std::string&) = nullptr;

    char filler[4];
    unsigned long long int someUuidShit;

    void regenerateSS(const std::string& str) {
        //std::cout << "regenerateSS\n";
       // std::cout << uuidSeed << " is reg\n";
       Logger::INFO << "Регенерация UUID: seed с " << someUuidShit << " в " << uuidSeed << "\n";
       someUuidShit = uuidSeed;
       // std::cout << this->reg5 << " is reg\n";
        //std::cout << this->s1 << " is s1\n";
      // this->reg = -918992897;
        //this->s1 = 32242424;
        UserAuthentication_regenerateSS(this, str);
        //std::cout << "regenerateSS done\n";
    };

};
