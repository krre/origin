#pragma once
#include "Singleton.h"
#include <SDL.h>
#include <vector>

class Screen;

class Game : public Singleton<Game> {

public:
    Game();
    void pushScreen(const std::shared_ptr<Screen>& screen);
    void popScreen();
    void setScreen(const std::shared_ptr<Screen>& screen);

    void update(float dt);
    void render(float dt);

    void load();
    void save();

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void toggleFullScreen();
    void saveScreenshot();

    std::vector<std::shared_ptr<Screen>> screens;
};
