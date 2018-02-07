#include <stdlib.h>
#include "Core/Application.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    Origin::Application::init(argc, argv);
    Origin::Application::run();
    Origin::Application::shutdown();
    return EXIT_SUCCESS;
}
