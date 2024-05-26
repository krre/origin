#pragma once
#include "ECS/Component.h"

class MovementComponent : public Component {

public:
    MovementComponent() = default;
    Type getType() const override { return Component::Type::Movement; }

    float moveSpeed = 0;
    float rotateSpeed = 0;
    bool free = false;
};
