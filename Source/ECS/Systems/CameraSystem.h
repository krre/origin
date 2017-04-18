#pragma once
#include "ECS/System.h"
#include <glm/glm.hpp>

class Entity;

class CameraSystem : public System {

public:
    CameraSystem();
    void process(float dt) override;
    glm::mat4 getView(Entity* entity);
private:
    void onWindowResize(int width, int height);
};
