#pragma once

#include <iostream>

class GuiData {
public:
	/*
	 * GuiData::addMessage(std::basic_string<char, std::char_traits<char>, std::allocator<char> >
   const&, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&, int, bool,
   bool)*/
     static inline void (*GuiData_addMessage)(GuiData*, const std::string& user, const std::string& msg, int, bool, bool) = nullptr;
    
     void addMessage(const std::string& user, const std::string& msg, int p3, bool p4, bool p5) {
         if(!user.empty()){
             std::cout << "< " << user << " > => ";
         }
        std::cout << msg << "\n";
        GuiData_addMessage(this, user, msg, p3, p4, p5);
    }
};

