#pragma once
#include "Scene3D.h"
#include "../ECS/Entity.h"
#include <SDL.h>
#include <glm/glm.hpp>

class WorldScene : public Scene3D {

    struct UBOfrag {
        int pageBytes;
        int blockInfoEnd;

        int frameWidth;
        int frameHeight;

        glm::vec3 backgroundColor;
        glm::vec3 lightColor;
        glm::vec3 lightPos;
        bool shadeless;

        float ambientStrength;
        float lod;
        int transformCount;

        glm::vec2 pickPixel;
    } uboFrag;

public:
    WorldScene();
    void init() override;
    void draw(float dt) override;
    void update(float dt) override;
    void create() override;
    EntityId getCharacterId() { return characterId; }
    uint64_t getSeed() { return seed; }

private:
    void onKeyPressed(const SDL_KeyboardEvent& event) override;
    EntityId characterId;
    uint64_t seed;
};
