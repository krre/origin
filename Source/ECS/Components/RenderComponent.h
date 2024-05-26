#pragma once
#include "ECS/Component.h"

class RenderComponent : public Component {

public:
    RenderComponent() = default;
    Type getType() const override { return Component::Type::Render; }

    bool visible = true;
};
