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
    uint64_t getSeed() { return seed; }

private:
    void create();
    void onKeyPressed(const SDL_KeyboardEvent& event);
    void toggleFullScreen();
    void saveScreenshot();
    void loadDevelopSettings();

    EntityId characterId;
    uint64_t seed;
};
