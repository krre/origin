#pragma once
#include "ECS/Component.h"
#include "ECS/Entity.h"

namespace Origin {

class MovementControllerComponent : public Component {

public:
    MovementControllerComponent() = default;
    Type getType() const override { return Component::Type::MovementController; }

    EntityId moveTarget;
    EntityId rotateTarget;
};

} // Origin
