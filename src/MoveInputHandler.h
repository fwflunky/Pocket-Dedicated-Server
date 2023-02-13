#pragma once

#include <iostream>
#include "../mcpe/Keyboard.h"
#include "../mcpe/Mouse.h"
#include <thread>
   class MoveInputHandler {
   public:
       static void moveW(int mstartafter, int mseconds, const std::function<void()>& onDone = nullptr){
           std::thread([mstartafter, mseconds, onDone](){
               //std::cout << "prepare move " <<startafter << "/" << seconds << " \n";
               usleep(mstartafter * 1000);
               //std::cout << "start move\n";
               Keyboard::inputs->push_back({1, 87});
               Keyboard::states[87] = 1;
               usleep(mseconds * 1000);
               //std::cout << "stop move\n";
               Keyboard::inputs->push_back({0, 87});
               Keyboard::states[87] = 0;
               if(onDone){
                   onDone();
               }
           }).detach();
       }

       static void moveA(int mstartafter, int mseconds, const std::function<void()>& onDone = nullptr){
           std::thread([mstartafter, mseconds, onDone](){
               //std::cout << "prepare move " <<startafter << "/" << seconds << " \n";
               usleep(mstartafter * 1000);
               //std::cout << "start move\n";
               Keyboard::inputs->push_back({1, 65});
               Keyboard::states[65] = 1;
               usleep(mseconds * 1000);
               //std::cout << "stop move\n";
               Keyboard::inputs->push_back({0, 65});
               Keyboard::states[65] = 0;
               if(onDone){
                   onDone();
               }
           }).detach();
       }
       
       static void moveS(int mstartafter, int mseconds, const std::function<void()>& onDone = nullptr){
           std::thread([mstartafter, mseconds, onDone](){
               //std::cout << "prepare move " <<startafter << "/" << seconds << " \n";
               usleep(mstartafter * 1000);
               //std::cout << "start move\n";
               Keyboard::inputs->push_back({1, 83});
               Keyboard::states[83] = 1;
               usleep(mseconds * 1000);
               //std::cout << "stop move\n";
               Keyboard::inputs->push_back({0, 83});
               Keyboard::states[83] = 0;
               if(onDone){
                   onDone();
               }
           }).detach();
       }
       
       static void moveD(int mstartafter, int mseconds, const std::function<void()>& onDone = nullptr){
           std::thread([mstartafter, mseconds, onDone](){
               //std::cout << "prepare move " <<startafter << "/" << seconds << " \n";
               usleep(mstartafter * 1000);
               //std::cout << "start move\n";
               Keyboard::inputs->push_back({1, 68});
               Keyboard::states[68] = 1;
               usleep(mseconds * 1000);
               //std::cout << "stop move\n";
               Keyboard::inputs->push_back({0, 68});
               Keyboard::states[68] = 0;
               if(onDone){
                   onDone();
               }
           }).detach();
       }
   		
   		static void MouseLeftClick(int mstartafter, const std::function<void()>& onDone = nullptr){
   			std::thread([mstartafter, onDone](){
   			//std::cout << "prepare move " <<startafter << "/" << seconds << " \n";
   				usleep(mstartafter * 1000);
   				//std::cout << "start move\n";
   				Mouse::feed((char) 1, (char) 1, 9, 9, 0, 0);
   				usleep(1000*100);
   				Mouse::feed((char) 1, (char) 0, 9, 9, 0, 0);
                if(onDone){
                    onDone();
                }
        	}).detach();
   		}
   
         static void jump(int mstartafter, const std::function<void()>& onDone = nullptr){
   			std::thread([mstartafter, onDone](){
   			//std::cout << "prepare move " <<startafter << "/" << seconds << " \n";
   				usleep(mstartafter * 1000);
   				//std::cout << "start move\n";
   				Keyboard::inputs->push_back({1, 32});
               Keyboard::states[32] = 1;
               usleep(160*1000);
               //std::cout << "stop move\n";
               Keyboard::inputs->push_back({0, 32});
               Keyboard::states[32] = 0;
               if(onDone){
                   onDone();
               }
        	}).detach();
   		}
  
};
