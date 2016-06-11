#pragma once
#include "Object.h"
#include "../Graphics/Camera.h"
#include <list>
#include <glm/glm.hpp>

class Game : public Object {

public:
    Game();
    void create();
private:
    void cameraMove(float dt);
    void update(float dt);
    glm::ivec2 prevMousePos;
    float yaw = 0;
    float pitch = 0;
    shared_ptr<Camera> camera;
};
