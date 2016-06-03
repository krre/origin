#pragma once
#include <SDL.h>
#include "../UI/PlayerView.h"
#include "../EventManager/EventManager.h"
#include "../Graphics/Renderer.h"
#include "Game.h"
#include "Object.h"
#include "../SceneGraph/Viewport.h"

class App : public Object {

public:
    App();
    ~App();
    void init();
    void clean();
    int run();
    Viewport* getViewport() { return &viewport; }

    Signal<> render;
    Signal<double> update;

private:
    PlayerView* playerView;
    Game* game;
    EventManager* eventManager;
    Renderer renderer;
    Viewport viewport;

    bool isRunning = false;
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_GLContext context;

    void windowResize(int width, int height);
    void handleEvents();
};
