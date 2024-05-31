#pragma once
#include "ecs/Component.h"
#include <glm/glm.hpp>

class MaterialComponent : public Component {

public:
    MaterialComponent() = default;
    Type type() const override { return Component::Type::Material; }

    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
};
