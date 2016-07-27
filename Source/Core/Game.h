#pragma once
#include "Singleton.h"
#include <list>
#include <glm/glm.hpp>
#include <SDL.h>

class Game : public Singleton<Game> {

public:
    Game();
    void load();
    void save();

    bool getWireframe() const { return wireframe; }

private:
    void create();
    void keyPress(const SDL_KeyboardEvent& event);
    void mouseButtonAction(const SDL_MouseButtonEvent& event);
    void toggleFullScreen();
    void saveScreenshot();
    std::string zeroFill(std::string number);

    bool wireframe = false; // TODO: Move to renderer
};
