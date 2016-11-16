#include <stdlib.h>
#include "Core/App.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    new App(argc, argv);
    if (argc > 1) {
        if (std::string(argv[1]) == "-opengl") {
            App::get()->setBackend(App::OPENGL);
        } else if (std::string(argv[1]) == "-vulkan") {
            App::get()->setBackend(App::VULKAN);
        }
    }
    App::get()->init();
    App::get()->run();
    App::get()->release();
    return EXIT_SUCCESS;
}
