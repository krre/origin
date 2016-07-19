#pragma once
#include "../Component.h"
#include "../Entity.h"

class MotionControllerComponent : public Component {

public:
    MotionControllerComponent();
    EntityId moveTarget;
    EntityId rotateTarget;
};
