#include <stdlib.h>
#include "Core/Application.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    new Application(argc, argv);
    Application::get()->run();
    Application::get()->release();
    return EXIT_SUCCESS;
}
