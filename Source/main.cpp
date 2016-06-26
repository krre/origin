#include <stdlib.h>
#include "Core/App.h"
#include "Event/Input.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

App* app;
Input* input;

int main(int argc, char* argv[]) {
    new Event();
    ::input = new Input();
    ::app = new App(argc, argv);
    ::app->init();
    ::app->run();
    ::app->clean();
    Event::getInstance()->release();
    delete ::app;
    return EXIT_SUCCESS;
}
