#pragma once
#include "ecs/Component.h"
#include <glm/glm.hpp>

class LightComponent : public Component {
public:
    LightComponent() = default;
    Type type() const override { return Component::Type::Light; }

    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
};
