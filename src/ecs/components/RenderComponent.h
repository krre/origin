#pragma once
#include "ecs/Component.h"

class RenderComponent : public Component {

public:
    RenderComponent() = default;
    Type type() const override { return Component::Type::Render; }

    bool visible = true;
};
