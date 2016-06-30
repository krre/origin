#pragma once
#include "../Core/Object.h"

enum class ComponentType {
    Camera,
    Empty,
    Input,
    Node,
    Render,
    Transform
};

class Component : public Object {

public:
    Component();
    ComponentType getType() const { return type; }
    bool enable = true;

protected:
    ComponentType type = ComponentType::Empty;
};
