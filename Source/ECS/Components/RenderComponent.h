#pragma once
#include "ECS/Component.h"

class RenderComponent : public Component {

public:
    RenderComponent() { type = ComponentType::Render; }
    bool visible = true;
};
