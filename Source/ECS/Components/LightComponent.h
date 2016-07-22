#pragma once
#include "../Component.h"

class LightComponent : public Component {

public:
    LightComponent() { type = Component::Type::Light; }

};
