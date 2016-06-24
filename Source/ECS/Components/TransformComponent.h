#pragma once
#include "../Component.h"
#include <glm/glm.hpp>

class TransformComponent : public Component {

public:
    TransformComponent();
    glm::mat4 localMatrix;
    glm::mat4 worldMatrix;
};
