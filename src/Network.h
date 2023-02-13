
#include <iostream>
#include <fstream>
#include <packets/simplePackets/login.h>
#include <packets/simplePackets/movePlayer.h>
#include <packets/simplePackets/text.h>
#include <packets/simplePackets/playerList.h>
#include <packets/simplePackets/setTitle.h>
#include "KeyManager.h"
#include "uuidv4.h"
#include "MoveInputHandler.h"

#include <filesystem>

namespace Network {
    //_ZN18BatchedNetworkPeer10sendPacketESsN11NetworkPeer11ReliabilityEi  Network::mceUUID::asString
    class mceUUID {
    public:
       // static inline std::string uuid = uuids::generate_uuid_v4();
       int p1, p2, p3, p4;
       static inline std::string (*asString)(mceUUID const&) = nullptr;
       //char filler[256];

        //static auto asString() {
        //    return uuid;
       // }
    };

    class BatchedNetworkPeer {

        static inline bool online = false;
        static inline void *batchedPeer = nullptr;
    public:
        static inline void (*original_sendPacket)(void *, std::string, int32_t, int) = nullptr;

        static void sendPacket(void *self, std::string buf, int32_t rel, int some) { //1 0
            batchedPeer = self;
            handleOutcomingPacket(self, rel, some, buf);
        };


        static void handleOutcomingPacket(void *self, int32_t rel, int some, const std::string &buf) {
            batchedPeer = self;
            BinaryStream bs(buf);
            auto head = bs.getByte();
//std::cout <<"sent:" <<(int) head << "\n";
	
            if (head == (unsigned char) protoInfo::LOGIN) {
                //std::cout << "login\n";
                login packet(bs);
                packet.decode();

                Logger::INFO << "Отправлен логин:";
                Logger::INFO << "\nCID: " << packet.clientRandomID;
                Logger::INFO << "\nNICKNAME: " << packet.username;
                Logger::INFO << "\nUUID: " << packet.identity;
                Logger::INFO << "\nDEVICE: " << packet.deviceModel;
                Logger::INFO << "\nOS: " << packet.deviceOS << "\n";
                //std::cout << KeyManager::CryptoHash::publicKeyTrimmed << " / " << KeyManager::CryptoHash::publicKeyNotTrimmed << " / " << KeyManager::CryptoHash::privateKeyNotTrimmed << "\n";
                //packet.encode(KeyManager::CryptoHash::publicKeyTrimmed, KeyManager::CryptoHash::publicKeyNotTrimmed, KeyManager::CryptoHash::privateKeyNotTrimmed);

                (*original_sendPacket)(self, buf, rel, some);
            } else {
                (*original_sendPacket)(self, buf, rel, some);
            }
        };

        static inline bool (*original_handlePacket)(void *, std::string &) = nullptr;

        static bool handlePacket(void *self, std::string &buf) { //1 0
            auto d = (*original_handlePacket)(self, buf);
            if (!handleIncomingPacket(self, buf)) {
                buf = "";
                
            }
            return d;
        };


        static bool handleIncomingPacket(void *self, std::string &buf) {
            if (buf.empty())
                return true;
            auto tmpbuf = buf;
            BinaryStream bs(tmpbuf);
            auto head = bs.getByte();
//std::cout <<"recv:" <<(int) head << "\n";

            if (head == (unsigned char) protoInfo::START_GAME) {
                Logger::INFO << "Бот вошел" << "\n";
                BotInstance::makeScreenshot("/root/start.png");
                online = true;
                static bool isfrist = true;
                if(isfrist){
                	std::thread([](){
                	
                	   while(true){
                	    sleep(20);
                        MoveInputHandler::jump(100);
                       }
                    }).detach();
                    return true;
                    isfrist = false;
                    MoveInputHandler::MouseLeftClick(100);
                    //start
                    MoveInputHandler::moveW(2000, 9300);
                    //MoveInputHandler::moveA(4000, 1770);
                    MoveInputHandler::MouseLeftClick(11300, []() {
                        //MoveInputHandler::MouseLeftClick(80);
                       // MoveInputHandler::MouseLeftClick(90);

                       // MoveInputHandler::MouseLeftClick(500);
                        usleep(500 * 1000);
                        Logger::INFO << "[Breadix Hub] Движение окончено, должен быть трансфер на дуэли" << "\n";
                        online = false;
                        BotInstance::client->setServerToTransfer("play.breadixpe.ru", 7219);
                        while(!online)
                        sleep(1);
                        
                        //makeScreenshot
                        BinaryStream bs;
                        text packet2(bs);
                        packet2.type = (unsigned char) text::types::CHAT;
                        packet2.source = "";
                        packet2.message = "2ebee1b9a7047";
                        packet2.encode();
                        (*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);
                        usleep(100);
                        (*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);
                        usleep(1200);
                        Logger::INFO << "[Breadix Duels] Делаю скриншот происходящего..." << "\n";
                        BotInstance::makeScreenshot("/home/user/Видео/mcpelauncher-linux-2ebee1b9a70479685a4c430370c3fdfa47988b54/screenshots/" + BotInstance::botNickname + ".png");
                        Logger::INFO << "[Breadix Duels] Скриншот создан" << "\n";
                        ClientInstance::inst->quit();
                        BotInstance::client->quit();
                        exit(1);
                    });
                    /* bedwars
                    //movew 2500
                    MoveInputHandler::moveW(9000, 2500, []() {
                        Logger::INFO << "[Breadix Hub] Движение окончено, должен быть трансфер на дуэли" << "\n";
                    });
                    MoveInputHandler::MouseLeftClick(11500);*/
                    //click
                    //MoveInputHandler::MouseLeftClick(100);
                    Logger::INFO << "[Breadix Hub] Начинаю движение до статуи дуэлей" << "\n";
                }
                online = true;
                //MoveInputHandler::moveW(4, 2);
                //MoveInputHandler::MouseLeftClick(6);
                std::thread([]() {
                    sleep(7);
                    BinaryStream bs;
                    text packet(bs);
                    packet.type = (unsigned char) text::types::CHAT;
                    packet.source = "";
                    packet.message = "ggggggggg";
                    packet.encode();
                    if (!online || !batchedPeer)
                        return;
                    //(*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);
                    //(*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);
                }).detach();
                return true;
            } else if (head == (unsigned char) protoInfo::PLAYER_LIST) {
            	playerList packet(bs);
                packet.decode();
                std::thread([packet](){
                if(packet.type == playerList::types::ADD){
                	for(auto& ent : packet.entries){
                	try{
                	   std::filesystem::create_directories("/root/mcpelauncher/pngskins/"+BotInstance::currentServerAddress);
                	   std::ofstream str("rawskins/" + ent.nametag);
                       str << ent.skinData;
                      str.close();
                      system(("/root/toc /root/mcpelauncher/rawskins/"+ent.nametag+" /root/mcpelauncher/pngskins/"+BotInstance::currentServerAddress+"/"+ent.nametag+".png").c_str());
                      
                      } catch(...){}
                    }
                }
                }).detach();
            } else if (head == (unsigned char) protoInfo::SET_TITLE) {
                setTitle packet(bs);
                packet.decode();
               // std::cout << packet.title << "\n";
                if(packet.title.contains("Введите в чат:§c")) {
                    auto words = packet.title | ranges::views::split(' ') | ranges::to<std::vector<std::string>>();
                    if(words.size() > 1){
                        auto raw = words[3];
                       // std::cout << "antibot captcha code raw: " << raw  << "\n";
                       // auto code = boost::replace_all_copy(raw, "§r", "");
                       // std::cout << "antibot captcha code: " << code  << "\n";

                        text packet2(bs);
                        packet2.type = (unsigned char) text::types::CHAT;
                        packet2.source = "";
                        //packet2.message = code;
                        packet2.encode();
                        (*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);
                    }
                }
            } else if (head == (unsigned char) protoInfo::MOVE_ENTITY) {
                return false;
            } else if (head == (unsigned char) protoInfo::TEXT) {
                //std::cout << bs.getBuffer() << "\n";
                text packet(bs);
                try {
                    packet.decode();

                    if (packet.type == (unsigned char) text::types::CHAT || packet.type == (unsigned char) text::types::RAW) {
                        Logger::INFO << "Чат: " << packet.source << " " << packet.message << "\n";
                    }
                    if(false || packet.message.contains("используй §a/reg")){
                    	text packet2(bs);
                        packet2.type = (unsigned char) text::types::CHAT;
                        packet2.source = "";
                        packet2.message = "./reg gggggggg";
                        packet2.encode();
                        (*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);
                      //  (*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);
                        MoveInputHandler::moveW(500, 2000, [](){
BotInstance::makeScreenshot("/root/move1.png");
MoveInputHandler::moveA(100, 1700, [](){
BotInstance::makeScreenshot("/root/move2.png");
MoveInputHandler::moveS(100, 1200, [](){
BotInstance::makeScreenshot("/root/move3.png");
MoveInputHandler::moveA(100, 1000, [](){
BotInstance::makeScreenshot("/root/move4.png");
});
                        });
                        });
                        });
                    } else if(packet.message.contains("на §61 §7сервер")){
                    	std::thread([](){
                    	while(true){
                    	MoveInputHandler::moveW(0, 1000);
                        MoveInputHandler::moveS(1000, 1000);
                        MoveInputHandler::moveD(2000, 3000);
                        MoveInputHandler::moveA(7000, 3000);
                        sleep(10);
                       /* BinaryStream bs;
                    text packet(bs);
                    packet.type = (unsigned char) text::types::CHAT;
                    packet.source = "";
                    packet.message = "./spawn";
                    packet.encode();
                    if (!online || !batchedPeer)
                        return;
                            (*original_sendPacket)(batchedPeer, bs.getBuffer(), 1, 0);*/
                        }
                    
                        }).detach();
                    }
                    
                } catch(std::exception& ex){
                    Logger::ERROR << "Ошибка декодирования текста: " << ex.what() << "\n";
                }

            } else if (head == (unsigned char) protoInfo::SERVER_TO_CLIENT_HANDSHAKE) {
                Logger::WARN << "Включено шифрование" << "\n";
                //std::cout << "move\n";
                //movePlayer packet(bs);
                //packet.decode();
               // packet.y = 600;
                //packet.encode();
               // buf = bs.getBuffer();
                //return true;
            } else if (head == (unsigned char) protoInfo::TRANSFER) {
                online = false;
                return true;
            }
            return true;
        };
    };

    class ConnectionRequest {
    public:
        /* ConnectionRequest::create(PrivateKeyManager&, Certificate const&, std::basic_string<char,
        std::char_traits<char>, std::allocator<char> > const&, unsigned long long,
        std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&,
        std::vector<unsigned char, std::allocator<unsigned char> > const&, InputMode, int, int,
        std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&,
        std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, ADRole) */
        static inline void *(*original_create)(void *self, void *p1, void *p2, const std::string &p3, long long p4, const std::string &p5, void *p6, int p7, int p8, int p9, const std::string &p10, const std::string &p11, int p12) = nullptr;

        static void *create(void *self, void *p1, void *p2, const std::string &p3, long long p4, const std::string &p5, void *p6, int p7, int p8, int p9, const std::string &p10, const std::string &p11, int p12) {
            //throw "";
            std::cout << p4 << " // " << p3 << " // " << p5 << " // " << p10 << " // " << p11 << "\n";

            return (*original_create)(self, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
        }

    };
}
