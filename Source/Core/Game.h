#pragma once
#include "Singleton.h"
#include <SDL.h>

class Game : public Singleton<Game> {

public:
    Game();
    void load();
    void save();

    bool getWireframe() const { return wireframe; }

private:
    void create();
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void toggleFullScreen();
    void saveScreenshot();

    bool wireframe = false; // TODO: Move to renderer
};
