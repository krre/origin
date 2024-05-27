#pragma once
#include "ECS/Component.h"
#include <Core/Common.h>

class MovementControllerComponent : public Component {

public:
    MovementControllerComponent() = default;
    Type getType() const override { return Component::Type::MovementController; }

    Core::EntityId moveTarget;
    Core::EntityId rotateTarget;
};
