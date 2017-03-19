#pragma once
#include "../System.h"
#include <glm/glm.hpp>

class CameraSystem : public System {

public:
    CameraSystem();
    void process(float dt) override;
    glm::mat4 getView(Entity* entity);
private:
    void onWindowResize(int width, int height);
};
