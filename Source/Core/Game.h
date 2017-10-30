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
    void render();

    void load();
    void save();

    void resize(uint32_t width, uint32_t height);

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void saveScreenshot();

    std::vector<std::shared_ptr<Screen>> screens;
};
