#pragma once
#include "Singleton.h"
#include <SDL.h>
#include "../Scene/World/WorldScene.h"

class Game : public Singleton<Game> {

public:
    Game();
    void load();
    void save();
    void setWorldScene(WorldScene* worldScene);
    WorldScene* getWorldScene() const { return worldScene; }

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void toggleFullScreen();
    void saveScreenshot();

    WorldScene* worldScene = nullptr;
};
