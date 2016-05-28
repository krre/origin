#pragma once
#include <SDL.h>
#include "../UI/PlayerView.h"
#include "../EventManager/EventManager.h"
#include "../Graphics3D/Renderer.h"
#include "Logic.h"

class App {

public:
    App();
    void init();
    void render();
    void update();
    void handleEvents();
    void clean();
    int run();

private:
    PlayerView* playerView;
    Logic* logic;
    EventManager* eventManager;
    Renderer renderer;

    bool running = false;
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_GLContext context;

    void windowResize(int width, int height);
};
