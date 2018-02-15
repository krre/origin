#pragma once
#include "Core/Common.h"
#include <SDL_syswm.h>
#include <string>

namespace Origin {

namespace SDL {

    void init();
    void shutdown();

    Size getScreenSize();
    std::string getError();
    SDL_SysWMinfo getSysWMinfo(SDL_Window* window);
    void showErrorMessageBox(const char* message);
    bool isInited();

} // SDL

} // Origin
