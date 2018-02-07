#include <stdlib.h>
#include "Core/Game.h"
#undef main // fix SDL error: undefined reference to `WinMain@16'

int main(int argc, char* argv[]) {
    Origin::Game::init(argc, argv);
    Origin::Game::run();
    Origin::Game::shutdown();
    return EXIT_SUCCESS;
}
