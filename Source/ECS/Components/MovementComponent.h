#pragma once
#include "../Component.h"

class MovementComponent : public Component {

public:
    MovementComponent() { type = ComponentType::Movement; }
    float moveSpeed = 0;
    float rotateSpeed = 0;
};
