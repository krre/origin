#pragma once
#include "ECS/Component.h"

class MovementComponent : public Component {

public:
    MovementComponent() { type = ComponentType::Movement; }
    float moveSpeed = 0;
    float rotateSpeed = 0;
    bool free = false;
};
