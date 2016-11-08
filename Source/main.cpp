#include <stdlib.h>
#include "Core/App.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    new App(argc, argv);
    if (argc > 1 && std::string(argv[1]) == "-opengl") {
        App::getInstance()->setBackend(App::OPENGL);
    }
    App::getInstance()->init();
    App::getInstance()->run();
    App::getInstance()->release();
    return EXIT_SUCCESS;
}
