#pragma once
#include "ECS/Component.h"
#include <glm/glm.hpp>

namespace Origin {

class MaterialComponent : public Component {

public:
    MaterialComponent() = default;
    Type getType() const override { return Component::Type::Material; }

    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
};

} // Origin
