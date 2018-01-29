#pragma once
#include "Core/Common.h"

namespace Origin {

namespace SDL {

    void init();
    void shutdown();

    Size getScreenSize();
    std::string getError();
    void showErrorMessageBox(const char* message);
    bool isInited();

} // SDL

} // Origin
