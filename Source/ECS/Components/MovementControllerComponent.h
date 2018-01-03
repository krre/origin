#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"

namespace Origin {

class MovementControllerComponent : public Component {

public:
    MovementControllerComponent() { type = ComponentType::MovementController; }
    EntityId moveTarget;
    EntityId rotateTarget;
};

} // Origin
