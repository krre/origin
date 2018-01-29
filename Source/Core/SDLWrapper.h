#pragma once
#include "Core/Common.h"

namespace Origin {

namespace SDLWrapper {

    void init();
    void shutdown();

    Size getScreenSize();
    std::string getError();
    void showErrorMessageBox(const char* message);
    bool isInited();

} // SDLWrapper

} // Origin
