//
// Created by user on 07.01.23.
//

#ifndef MCPELAUNCHER_SCREENCHOOSER_H
#define MCPELAUNCHER_SCREENCHOOSER_H
#include "../mcpe/MinecraftGame.h"
#include "../src/BotInstance.h"
#include "../src/log.h"
#include <range/v3/range.hpp>
#include <range/v3/view/split.hpp>
class ScreenChooser {
public:
    //_ZN13ScreenChooserC2ER13MinecraftGameR14ClientInstanceb
    static inline void (*construct)(ScreenChooser*, MinecraftGame *, void*, bool) = nullptr ;
    static inline void (*setDisconnectScreen)(ScreenChooser*, const std::string&, const std::string&, const std::string&) = nullptr ;
    char filler[0x1000]{};

    ScreenChooser(MinecraftGame *game, void* clientinst, bool ss){
        ScreenChooser::construct(this, game, clientinst, ss);
    }

    void onDisconnect(const std::string& s1, const std::string& s2, const std::string& s3) {
        Logger::WARN << "Отключен: " << s1 << " / " << s2 << " / " << s3 << "\n";
        BotInstance::canAutoAcceptRpTickCount = 0;
        if(s2.contains("на§b")){
        	auto words = s2 | ranges::views::split(' ') | ranges::to<std::vector<std::string>>();
            if(words.size() > 10){
            	auto port = std::stoi(words[12]);
                BotInstance::currentServerPort = port;
                Logger::WARN << "Трансфер на " << port << "\n";
            }
        }
        ScreenChooser::setDisconnectScreen(this, s1, s2, s3);
        std::thread([](){ sleep(10);
        BotInstance::client->setServerToTransfer(BotInstance::currentServerAddress, BotInstance::currentServerPort);
        }).detach();
                    
        
    }
};
#endif //MCPELAUNCHER_SCREENCHOOSER_H
