#include <string>
#include <vector>

#include "AppPlatform.h"
/*
AppPlatform** AppPlatform::_singleton = nullptr;
void** AppPlatform::myVtable = nullptr;
void (*AppPlatform::AppPlatform_construct)(AppPlatform*);
void (*AppPlatform::AppPlatform__fireAppFocusGained)(AppPlatform*);
void (*AppPlatform::AppPlatform_initialize)(AppPlatform*);
*/
#include "App.h"

#include "MinecraftGame.h"
#include "Options.h"

//bool (*Options::Options_getFullscreen)(Options*);
//void (*Options::Options_setFullscreen)(Options*, bool);

#include "gl.h"


#include "Mouse.h"

void (*Mouse::feed)(char, char, short, short, short, short);

#include "Keyboard.h"

void (*Keyboard::Keyboard_feedText)(const std::string&, bool, unsigned char);
std::vector<KeyboardAction>* Keyboard::inputs;
int* Keyboard::states;