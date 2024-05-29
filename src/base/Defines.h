#pragma once
#include <config.h>

#ifndef NDEBUG
    #define DEVELOP_MODE
#endif

#ifdef DEVELOP_MODE
    #define CONSOLE_ENABLE
    #define DEBUG_HUD_ENABLE
#endif
