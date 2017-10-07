#pragma once
#include <Origin.h>

#define APP_NAME "Origin"
#define APP_VERSION_STR VERSION_STRING
#define APP_URL "https://github.com/krre/origin"
#define SETTINGS_NAME "origin.ini"

#define DEVELOP_MODE

#ifdef DEVELOP_MODE
    #define CONSOLE_ENABLE
    #define DEBUG_HUD_ENABLE
    #define DEVELOP_GAME_STATE
#endif
