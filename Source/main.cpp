#include <stdlib.h>
#include "Core/App.h"
#include "Event/Input.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

App* app;
Event* event;
Input* input;

int main(int argc, char* argv[]) {
    ::event = new Event();
    ::input = new Input();
    ::app = new App(argc, argv);
    ::app->init();
    ::app->run();
    ::app->clean();
    delete ::event;
    delete ::input;
    delete ::app;
    return EXIT_SUCCESS;
}
