#pragma once
#include "ECS/Component.h"

namespace Origin {

class MovementComponent : public Component {

public:
    MovementComponent() { type = Component::Type::Movement; }
    float moveSpeed = 0;
    float rotateSpeed = 0;
    bool free = false;
};

} // Origin
