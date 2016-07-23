#pragma once
#include "../Component.h"
#include <glm/glm.hpp>

class LightComponent : public Component {

public:
    LightComponent() { type = ComponentType::Light; }
    glm::vec3 color = glm::vec3(1.0, 1.0, 1.0);
};
