#pragma once
#include "Core/Common.h"

namespace Origin {

class SDLWrapper {

public:
    SDLWrapper() = delete;

    static void init();
    static void shutdown();

    static Size getScreenSize();
    static std::string getError();
    static void showErrorMessageBox(const char* message);
    static bool isInited() { return inited; }

private:
    static bool inited;
};

} // Origin
