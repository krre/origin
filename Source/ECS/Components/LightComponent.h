#pragma once
#include "ECS/Component.h"
#include <glm/glm.hpp>

namespace Origin {

class LightComponent : public Component {

public:
    LightComponent() { type = Component::Type::Light; }
    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
};

} // Origin
