#pragma once
#include "../Component.h"
#include <glm/ext.hpp>

class TransformComponent : public Component {

public:
    TransformComponent();
    glm::mat4 localMatrix;
    glm::mat4 worldMatrix;
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale = glm::vec3(1.0);
    float yaw = 0;
    float pitch = 0;
    bool dirty = false;
};
