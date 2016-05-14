#pragma once
#include <SDL.h>

class Game {

public:
    Game() {}
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

    void onWindowResize(int width, int height);
};
