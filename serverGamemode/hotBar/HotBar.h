//
// Created by user on 19.02.23.
//

#ifndef PDSERVER_HOTBAR_H
#define PDSERVER_HOTBAR_H


class HotBar {
public:
    static void scheduleUpdate();
    static inline std::string base = "";
    static inline std::string current;
    static inline bool needBlink = false;
    static inline int blinkTicks = 0;
    static inline int currentOffset = 0;
    static inline unsigned int maxOffset = base.length();
};


#endif //PDSERVER_HOTBAR_H