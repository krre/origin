#include <stdlib.h>
#include "Core/Game.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    Origin::Game game(argc, argv);
    game.run();
    return EXIT_SUCCESS;
}
