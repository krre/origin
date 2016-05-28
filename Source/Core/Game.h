#pragma once
#include <SDL.h>
#include "../UI/PlayerView.h"
#include "../EventManager/EventManager.h"
#include "Logic.h"
#include "screens/MainScreen.h"
#include "screens/GameScreen.h"

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
    PlayerView* playerView;
    Logic* logic;
    EventManager* eventManager;

    bool running = false;
    SDL_Window* window = nullptr;
    SDL_Surface* surface = nullptr;
    SDL_GLContext context;

    Screen* currentScreen;
    MainScreen mainScreen;
    GameScreen gameScreen;

    void windowResize(int width, int height);
};
