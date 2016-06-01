#include <stdlib.h>
#include "Core/App.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

extern App* app;

int main() {
    ::app = new App();
    app->init();
    app->run();
    app->clean();
    return EXIT_SUCCESS;
}
