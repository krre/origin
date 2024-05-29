#pragma once
#include "ecs/Component.h"
#include <core/Common.h>

class MovementControllerComponent : public Component {

public:
    MovementControllerComponent() = default;
    Type getType() const override { return Component::Type::MovementController; }

    Core::EntityId moveTarget;
    Core::EntityId rotateTarget;
};