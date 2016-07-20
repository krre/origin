#pragma once
#include "../Component.h"

class MovementComponent : public Component {

public:
    MovementComponent() { type = Component::Type::Movement; }
    float moveSpeed = 0;
    float rotateSpeed = 0;
};
