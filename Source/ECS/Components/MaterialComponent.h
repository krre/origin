#pragma once
#include "ECS/Component.h"
#include <glm/glm.hpp>

class MaterialComponent : public Component {

public:
    MaterialComponent() { type = ComponentType::Material; }
    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
};
