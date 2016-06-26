#include <stdlib.h>
#include "Core/App.h"
#include "Event/Input.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

App* app;

int main(int argc, char* argv[]) {
    new Event();
    new Input();
    ::app = new App(argc, argv);
    ::app->init();
    ::app->run();
    ::app->clean();
    Event::getInstance()->release();
    Input::getInstance()->release();
    delete ::app;
    return EXIT_SUCCESS;
}
