#pragma once
#include "Singleton.h"
#include <SDL.h>

class Game : public Singleton<Game> {

public:
    Game();
    void load();
    void save();

private:
    void create();
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void toggleFullScreen();
    void saveScreenshot();
};
