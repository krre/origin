#pragma once
#include <SDL.h>
#include "../UI/PlayerView.h"
#include "../EventManager/EventManager.h"
#include "../Graphics3D/Renderer.h"
#include "Game.h"
#include "Object.h"

class App : public Object {

public:
    App();
    ~App();
    void init();
    void clean();
    int run();

private:
    PlayerView* playerView;
    Game* game;
    EventManager* eventManager;
    Renderer renderer;

    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_GLContext context;

    void windowResize(int width, int height);
    void handleEvents();
};
