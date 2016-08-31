#pragma once
#include "../Component.h"
#include <glm/ext.hpp>

class TransformComponent : public Component {

public:
    TransformComponent() { type = ComponentType::Transform; }
    glm::mat4 objectToWorld = glm::mat4(1.0);
    glm::vec3 position;
    glm::quat rotation;
    float scale = 1.0;
    float yaw = 0;
    float pitch = 0;
};
