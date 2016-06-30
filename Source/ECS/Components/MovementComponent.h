#pragma once
#include "../Component.h"

class MovementComponent : public Component {

public:
    MovementComponent();
    float moveSpeed = 0;
    float rotateSpeed = 0;
};
