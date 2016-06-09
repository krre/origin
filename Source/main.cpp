#include <stdlib.h>
#include "Core/App.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

App* app;
Event* event;

int main(int argc, char* argv[]) {
    ::event = new Event();
    ::app = new App(argc, argv);
    ::app->init();
    ::app->run();
    ::app->clean();
    delete ::event;
    delete ::app;
    return EXIT_SUCCESS;
}
