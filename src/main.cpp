#include "Game.h"
#include <stdlib.h>
#undef main // fix error: undefined reference to `WinMain@16'

int main() {
    Game game;
    game.init();
    game.run();
    game.clean();
    return EXIT_SUCCESS;
}
