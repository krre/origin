#pragma once
#include "../Core/Object.h"

enum class ComponentType {
    Empty,
    Transform,
    Camera,
    Node,
    Render
};

class Component : public Object {

public:
    Component();
    ComponentType getType() const { return type; }

protected:
    ComponentType type = ComponentType::Empty;
};
