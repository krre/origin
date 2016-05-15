#pragma once
#include <SDL.h>
#include "core/Screen.h"

class Game {

public:
    Game();
    void init();
    void render();
    void update();
    void handleEvents();
    void clean();
    int run();

private:
    bool running = false;
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_GLContext context;

    Screen* currentScreen;
    Screen mainScreen;
    Screen gameScreen;

    void onWindowResize(int width, int height);
};
