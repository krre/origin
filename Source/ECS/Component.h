#pragma once
#include "../Core/Object.h"

enum class ComponentType {
    Camera,
    Empty,
    Light,
    Material,
    Mesh,
    MovementController,
    Movement,
    Node,
    Octree,
    Phisics,
    Render,
    Transform
};

class Component : public Object {

public:
    Component();
    ComponentType getType() const { return type; }
    bool enable = true;
    bool dirty = false;

protected:
    ComponentType type = ComponentType::Empty;
};
