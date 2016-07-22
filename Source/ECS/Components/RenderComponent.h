#pragma once
#include "../Component.h"

class RenderComponent : public Component {

public:
    RenderComponent() { type = ComponentType::Render; }
    bool visible = true;
};
