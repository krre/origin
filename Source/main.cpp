#include <stdlib.h>
#include "Core/App.h"
#include "Event/Input.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    new Event();
    new Input();
    new App(argc, argv);
    App::getInstance()->init();
    App::getInstance()->run();
    App::getInstance()->clean();
    Event::getInstance()->release();
    Input::getInstance()->release();
    App::getInstance()->release();
    return EXIT_SUCCESS;
}
