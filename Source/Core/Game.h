#pragma once
#include "Object.h"
#include "../Graphics/Camera.h"
#include <list>
#include <glm/glm.hpp>
#include <SDL.h>

using namespace glm;

class Game : public Object {

public:
    Game();
    void create();
private:
    void cameraMove(float dt);
    void update(float dt);
    void keyPress(const SDL_KeyboardEvent& event);
    void toggleFullScreen();

    ivec2 prevMousePos;
    float yaw = 0;
    float pitch = 0;
    shared_ptr<Camera> camera;
};
