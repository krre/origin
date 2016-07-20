#pragma once
#include "../System.h"
#include "../Entity.h"
#include <glm/glm.hpp>

class CameraSystem : public System {

public:
    CameraSystem();
    void process(float dt) override;
    glm::mat4 getView(Entity* entity);
    glm::mat4 getProjection(Entity* entity);
};
