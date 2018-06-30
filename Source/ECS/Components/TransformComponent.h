#pragma once
#include "ECS/Component.h"
#include <glm/ext.hpp>

namespace Origin {

class TransformComponent : public Component {

public:
    TransformComponent() = default;
    Type getType( )const override { return Component::Type::Transform; }

    glm::mat4 objectToWorld = glm::mat4(1.0);
    glm::mat4 worldToObject = glm::mat4(1.0);
    glm::vec3 position;
    glm::quat rotation;
    float scale = 1.0;
    float yaw = 0;
    float pitch = 0;
};

} // Origin
