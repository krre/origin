#include "Base/Game.h"
#include <stdlib.h>
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    Game game(argc, argv);
    game.run();
    return EXIT_SUCCESS;
}
