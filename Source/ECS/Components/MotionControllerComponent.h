#pragma once
#include "../Component.h"
#include "../Entity.h"

class MotionControllerComponent : public Component {

public:
    MotionControllerComponent() { type = ComponentType::MotionController; }
    EntityId moveTarget;
    EntityId rotateTarget;
};
