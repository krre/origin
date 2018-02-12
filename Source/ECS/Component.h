#pragma once
#include "Core/Object.h"

namespace Origin {

class Component : public Object {

public:

    enum class Type {
        Camera,
        Empty,
        Light,
        Material,
        Mesh,
        MovementController,
        Movement,
        Node,
        Octree,
        Physics,
        Render,
        Transform
    };

    Component();
    Type getType() const { return type; }
    bool enable = true;
    bool dirty = false;

protected:
    Type type = Type::Empty;
};

} // Origin
