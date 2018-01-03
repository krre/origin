#include <stdlib.h>
#include "Core/Application.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    new Origin::Application(argc, argv);
    Origin::Application::get()->run();
    Origin::Application::release();
    return EXIT_SUCCESS;
}
