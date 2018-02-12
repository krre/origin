#pragma once
#include "ECS/Component.h"

namespace Origin {

class RenderComponent : public Component {

public:
    RenderComponent() { type = Component::Type::Render; }
    bool visible = true;
};

} // Origin
