#pragma once
#include "../Component.h"
#include "../Entity.h"

class MotionControllerComponent : public Component {

public:
    MotionControllerComponent() { type = Component::Type::MotionController; }
    EntityId moveTarget;
    EntityId rotateTarget;
};
