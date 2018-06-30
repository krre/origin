#pragma once
#include "ECS/Component.h"

namespace Origin {

class RenderComponent : public Component {

public:
    RenderComponent() = default;
    Type getType() const override { return Component::Type::Render; }

    bool visible = true;
};

} // Origin
