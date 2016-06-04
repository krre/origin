#include <stdlib.h>
#include "Core/App.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

App* app;

int main(int argc, char* argv[]) {
    ::app = new App(argc, argv);
    ::app->init();
    ::app->run();
    ::app->clean();
    return EXIT_SUCCESS;
}
