#pragma once
#include "../Component.h"
#include "../Graphics/Camera.h"

// Mark component
class InputComponent : public Component {

public:
    InputComponent() { type = Component::Type::Input; }
};
