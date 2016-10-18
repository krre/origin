#pragma once
#include "../Component.h"

class PhisicsComponent : public Component {

public:
    PhisicsComponent() { type = ComponentType::Phisics; }
};
