#pragma once
#include "../Component.h"
#include <glm/ext.hpp>

class TransformComponent : public Component {

public:
    TransformComponent() { type = Component::Type::Transform; }
    glm::mat4 localMatrix = glm::mat4(1.0);
    glm::mat4 worldMatrix = glm::mat4(1.0);
    glm::vec3 translation;
    glm::quat rotation;
    glm::vec3 scale = glm::vec3(1.0);
    float yaw = 0;
    float pitch = 0;
};
