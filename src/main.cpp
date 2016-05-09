#include "Game.h"
#include <stdlib.h>
#undef main

int main() {
    Game game;
    game.init();
    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
    }
    game.clean();
    return EXIT_SUCCESS;
}
