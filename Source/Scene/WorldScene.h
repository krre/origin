#pragma once
#include "Scene3D.h"
#include "../ECS/Entity.h"
#include <SDL.h>

class WorldScene : public Scene3D {

public:
    WorldScene();
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;
    EntityId getCharacterId() { return characterId; }
    uint64_t getSeed() { return seed; }

private:
    void onKeyPressed(const SDL_KeyboardEvent& event);
    EntityId characterId;
    uint64_t seed;
};
