#pragma once
#include "../Component.h"

class TransformComponent : public Component {

public:
    TransformComponent();

private:
    Type type = Component::Transform;

};
