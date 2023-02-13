//
// Created by user on 10.02.23.
//

#ifndef MCPELAUNCHER_MOBEFFECTINSTANCE_H
#define MCPELAUNCHER_MOBEFFECTINSTANCE_H


class MobEffectInstance {
public:
    static void initHooks(void* handle);
    static inline void (*MobEffectInstance_ctor)(MobEffectInstance*, int, int, int) = nullptr;

    MobEffectInstance(int id, int duration, int ampf); //duration in ticks
    char filler[15];
};


#endif //MCPELAUNCHER_MOBEFFECTINSTANCE_H
