//
// Created by user on 07.01.23.
//

#ifndef MCPELAUNCHER_LOG_H
#define MCPELAUNCHER_LOG_H
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>

int lolfilter(std::istream &is);
int lolcat(std::istream &is);
int lolcat(const std::string& str);

class Loggers {
public:
    static void init(){
    }

    explicit Loggers(const std::string& namee){
        name = namee;
    }

    Loggers& operator<<(const std::string& str)
    {
        ss << str;
        if(str == "\n") {
            auto out = ss.str();
            std::stringstream().swap(ss);
            ss << "[ " << name << " ] " << out;
            //lolfilter(ss);
            //std::cout << ss.str() << ";;\n";
            lolcat(ss.str());

            std::stringstream().swap(ss);
        }
        return *this;
    }

    Loggers& operator<<(int in)
    {
        ss << in;
        return *this;
    }

    Loggers& operator<<(unsigned short in)
    {
        ss << in;
        return *this;
    }

    Loggers& operator<<(short in)
    {
        ss << in;
        return *this;
    }

    Loggers& operator<<(unsigned long long int in)
    {
        ss << in;
        return *this;
    }

    Loggers& operator<<(long long int in)
    {
        ss << in;
        return *this;
    }

private:
    static inline std::stringstream ss;
    std::stringstream tempss;
    std::string name;
    //static inline int ll(ss);
};

class Logger {
public:
    static inline Loggers INFO = Loggers("INFO");
    static inline Loggers WARN = Loggers("WARN");
    static inline Loggers NOTICE = Loggers("NOTICE");
    static inline Loggers ERROR = Loggers("ERROR");

    static void init(){
        Loggers::init();
    }
};

#endif //MCPELAUNCHER_LOG_H
