#pragma once
#include "../Component.h"

class RenderComponent : public Component {

public:
    RenderComponent() { type = Component::Type::Render; }
    bool visible = true;
};
