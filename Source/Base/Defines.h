#pragma once
#include <Origin.h>

#define APP_NAME "Origin"
#define APP_VERSION_STR VERSION_STRING
#define APP_URL "https://github.com/krre/origin"
#define APP_SETTINGS_NAME "settings.json"

#ifndef NDEBUG
    #define DEVELOP_MODE
#endif

#ifdef DEVELOP_MODE
    #define CONSOLE_ENABLE
    #define DEBUG_HUD_ENABLE
    #define DEVELOP_GAME_STATE
#endif
