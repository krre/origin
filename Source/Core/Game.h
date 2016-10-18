#pragma once
#include "Singleton.h"
#include "../ECS/Entity.h"
#include <SDL.h>

class Game : public Singleton<Game> {

public:
    Game();
    void load();
    void save();
    EntityId getCharacterId() { return characterId; }

private:
    void create();
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void toggleFullScreen();
    void saveScreenshot();
    void loadDevelopSettings();

    EntityId characterId;
};
