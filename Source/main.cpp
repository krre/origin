#include <stdlib.h>
#include "Core/App.h"
#undef main // fix error: undefined reference to `WinMain@16'

int main() {
    App app;
    app.init();
    app.run();
    app.clean();
    return EXIT_SUCCESS;
}
