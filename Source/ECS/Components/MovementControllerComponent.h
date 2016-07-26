#pragma once
#include "../Component.h"
#include "../Entity.h"

class MovementControllerComponent : public Component {

public:
    MovementControllerComponent() { type = ComponentType::MovementController; }
    EntityId moveTarget;
    EntityId rotateTarget;
};
