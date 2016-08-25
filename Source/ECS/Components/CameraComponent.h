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
        right = glm::vec3(view.y, -view.x, 0.0);
    }
    float near = 0.01f;
    float far = 100.0f;
    float fov = glm::radians(50.0f);
    float aspect;
    const float distance = 1.0f; // distance from camera to screen
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 view = glm::vec3(0.0, 0.0, -1.0);
    glm::vec3 right;
    glm::mat4 projection = glm::perspective(fov, aspect, near, far);
};
