#pragma once
#include <core/Common.h>
#include <string>

struct SDL_Window;

namespace SDL {
    struct Platform {
        void* handle;
        void* window;
    };

    void init();
    void shutdown();

    Core::Size screenSize();
    std::string error();
    Platform platform(SDL_Window* window);
    void showErrorMessageBox(const char* message);
    bool isInited();
}
