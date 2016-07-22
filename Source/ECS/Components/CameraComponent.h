#pragma once
#include "../Component.h"
#include "../Core/App.h"
#include <glm/ext.hpp>

class CameraComponent : public Component {

public:
    CameraComponent() {
        type = ComponentType::Camera;
        int width = App::getInstance()->getWidth();
        int height = App::getInstance()->getHeight();
        aspect = width * 1.0f / height;
    }
    float near = 0.1f;
    float far = 100.0f;
    float fov = glm::radians(50.0f);
    float aspect;
    glm::mat4 projection = glm::perspective(fov, aspect, near, far);
};
