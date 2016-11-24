#include <stdlib.h>
#include "Core/App.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    new App(argc, argv);
    App::get()->init();
    App::get()->run();
    App::get()->release();
    return EXIT_SUCCESS;
}
