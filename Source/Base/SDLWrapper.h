#pragma once
#include "Core/Common.h"
#include <string>

struct SDL_Window;

namespace SDL {
    struct Platform {
        void* handle;
        void* window;
    };

    void init();
    void shutdown();

    Core::Size getScreenSize();
    std::string getError();
    Platform getPlatform(SDL_Window* window);
    void showErrorMessageBox(const char* message);
    bool isInited();

}
