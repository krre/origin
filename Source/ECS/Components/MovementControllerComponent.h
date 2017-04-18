#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"

class MovementControllerComponent : public Component {

public:
    MovementControllerComponent() { type = ComponentType::MovementController; }
    EntityId moveTarget;
    EntityId rotateTarget;
};
