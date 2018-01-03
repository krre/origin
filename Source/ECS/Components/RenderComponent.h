#pragma once
#include "ECS/Component.h"

namespace Origin {

class RenderComponent : public Component {

public:
    RenderComponent() { type = ComponentType::Render; }
    bool visible = true;
};

} // Origin
